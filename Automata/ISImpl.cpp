/************************************************************************
Implementation: As explained in [Wat93a, Section 5.5], a dot (an item in an item set) can occur
either before or after a regular expression) or any of its subexpressions. The subexpressions
of the associated regular expression (including the expression itself) are encoded by their
node number (starting at 0) in a prefix traversal of the RE expression tree. The dots before
sub expressions are stored as bits in a BitVec called before, while the dots after subexpressions
are store as bits in a BitVee, called after (in both cases, the bits indicate if the corresponding
dot is present). Two ISImpls are equal if these two BitVecs are equal, i.e. their dots before
and after are equal. The member functions move_dots and D both make prefix traversals of
the RE expression tree, keeping track of the prefix number of each subexpression.
 ************************************************************************/

#include "ISImpl.h"

// A special constructor :
ISImpl::ISImpl(const RE *r) :e(r)
{
	assert(r->class_invariant());
	int i(r->num_operators());
	before.set_width(i);
	after.set_width(i);
	assert(!(before.something_set() || after.something_set()));
	
	// Now put a dot before the root of *e.
	before.set_bit(0);
	
	// Now propagate the dots.
	int nodes(0);
	D(*r, nodes);
	assert(nodes == r->num_operators());
	assert(class_invariant());
}

const ISImpl& ISImpl::operator=(const ISImpl& r)
{
	assert(class_invariant());
	e = r.e;
	before = r.before;
	after = r.after;
	assert(class_invariant());
	return(*this);
}

// Move the dots as far as possible.
// This is named according to Definition 5.63 of the Taxonomy.
// node_num is the preorder number of r(in the associated RE).
void ISImpl::D(const RE& r, int& node_num)
{
	// Need to remember if there was a dot in front of this node, and what the preorder
	// number of this node is.
	int b;
	int nn;
	int node_right;
	int sub_parity;

	switch (r.root_operator())
	{
	case EPSILON:
		// The dot always moves through an EPSILON.
		if (before.contains(node_num)) {
			after.set_bit(node_num);
		}
		node_num++;
		break;
	case EMPTY:
	case SYMBOL:
		// The dot never moves through EMPTY or SYMBOL.
		// Just advance to the next preorder number.
		node_num++;
		break;
	case OR:
		// Is there one before this node?
		b = before.contains(node_num);
		nn = node_num++;
		// If b, the propagate the dot inside the(left of the) OR too.
		if (b) {
			// node_num is now the node num of the left subexpr.
			before.set_bit(node_num);
		}
		// Propagate through the left subexpression.
		D(r.left_subexpr(), node_num);
		// If the dot is after the left subexpr, then propagate out of the OR.
		if (after.contains(nn + 1)) {
			after.set_bit(nn);
		}
			// If b, propagate the dot to the right of the OR.
		if (b) {
			before.set_bit(node_num);
		}
		// Save the node number of the right subexpr.
		node_right = node_num;
		// Propagate through the right subexpr.
		D(r.right_subexpr(), node_num);
		// If the dot is after the right, then propagate it out of the OR.
		if (after.contains(node_right)) {
			after.set_bit(nn);
		}
		break;
	case CONCAT:
		nn = node_num++;
		// If there's a dot before the CONCAT, propagate it into the left subexpr.
		if (before.contains(nn)) {
			before.set_bit(node_num);
		}
		// Propagate through the left subexpr.
		D(r.left_subexpr(), node_num);
		// If the dot is after the left subexpr, move it before the right one.
		if (after.contains(nn + 1)) {
			before.set_bit(node_num);
		}

		// Save the node number of the right subexpr.
		node_right = node_num;

		// Propagate through the right.
		D(r.right_subexpr(), node_num);
		// If the dot is after the right subexpT, move it behind the CONCAT.
		if (after.contains(node_right)) {
			after.set_bit(nn);
		}
		break;
	case STAR:
		// A dot before the expression means that it moves after too.
		if (before.contains(node_num)) {
			after.set_bit(node_num);
		}
		// Fall through here.
	case PLUS:
		// The fall through from the STAR is correct!
		nn = node_num++;
		// If there's a dot before the STAR/PLUS and into the subexpr.
		if (before.contains(nn)) {
			before.set_bit(node_num);
		}
		// Remember if there's already a dot before the subexpr.
		sub_parity = before.contains(node_num);

		// Propagate through the subexpr.
		D(r.left_subexpr(), node_num);

		// Check if a dot is after the subexpr.
		if (after.contains(nn + 1))
		{
			// Move the dot out.
			after.set_bit(nn);
			// and move the bit around before the subexpr.
			// if it wasn't already there before.
			if (!sub_parity)
			{
				// Re-propagate the dots.
				//        nn + 1 is the node num of the subexpr.
				before.set_bit(++nn);
				D(r.left_subexpr(), nn);
			}
		}
		break;
	case QUESTION:
		nn = node_num++;
		// If there's a dot before the QUESTION, move it after, and into the subexpr.
		if (before.contains(nn))
		{
			after.set_bit(nn);
			before.set_bit(node_num);
		}
		// Propagate through the subexpr.
		D(r.left_subexpr(), node_num);

		// If there's a dot after the subexpr, propagate it out.
		if (after.contains(nn + 1)) {
			after.set_bit(nn);
		}
		break;
	}
}

// Fetch the labels throughout the tree.
// Helper to out_labels().
CRSet ISImpl::traverse_labels(const RE& r, int& node_num) const
{
	// assume that the root of r is node number node_num.
	assert(class_invariant() && r.class_invariant());

	CRSet b;
	switch (r.root_operator()) {
	case EPSILON:
	case EMPTY:
		node_num++;
		break;
	case SYMBOL:
		// Check if this node has a dot before it.
		if (before.contains(node_num)) {
			b.append(r.symbol());
		}
		node_num++;
		break;
	case OR:
	case CONCAT:
		node_num++;
		b = traverse_labels(r.left_subexpr(), node_num);
		b.combine(traverse_labels(r.right_subexpr(), node_num));
		break;
	case STAR:
	case PLUS:
	case QUESTION:
		node_num++;
		b = traverse_labels(r.left_subexpr(), node_num);
	}
	return(b);
}

// Move the dots throughout the RE tree:
// Only dots in front a SYMBOL node, matching CharRange a, can advance.
// Helper to move_dots().
void ISImpl::traverse_move_dots(const RE& r, const CharRange& a, int& node_num)
{
	assert(r.class_invariant());
	// node_num is the preorder number of the associated regular expression.
	switch (r.root_operator())
	{
	case EPSILON:
	case EMPTY:
		// Remove any dot that may be before.
		before.unset_bit(node_num);
		node_num++;
		break;
	case SYMBOL:
		// if there's a match) advance the bit.
		if ((a <= r.symbol()) && before.contains(node_num))
		{
			after.set_bit(node_num);
		}
		before.unset_bit(node_num);
		node_num++;
		break;
	case OR:
	case CONCAT:
		before.unset_bit(node_num);
		node_num++;
		traverse_move_dots(r.left_subexpr(), a, node_num);
		traverse_move_dots(r.right_subexpr(), a, node_num);
		break;
	case STAR:
	case PLUS:
	case QUESTION:
		before.unset_bit(node_num);
		node_num++;
		traverse_move_dots(r.left_subexpr(), a, node_num);
		break;
	}
}

std::ostream& operator<<(std::ostream& os, const ISImpl& r)
{
	assert(r.class_invariant());
	return(os << "\nISImpl\n" << *(r.e) << "\nbefore: " << r.before 
		<< "\nafter: " << r.after << '\n');
}
