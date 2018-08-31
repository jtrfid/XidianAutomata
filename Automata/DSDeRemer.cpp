/***********************************************************************
Implementation: The implementation is largely provided by the base class ISImpl. The member
function opt (with helper traverse_opt) implements DeRemer's dot filter function X as
defined in [Wat93a, Definition 5.72]. The filter function makes a single prefix traversal of the
RE expression tree. By applying the filter, it becomes more likely that template function
construct_components will find two item sets (denoting the same language) to be equal (this
will result in fewer states in the constructed DFA).
***********************************************************************/
#include "stdafx.h"
#include "DSDeRemer.h"

DSDeRemer DSDeRemer::out_transition(const CharRange a) const
{
	assert(class_invariant());
	DSDeRemer ret(*this);
	ret.move_dots(a);
	ret.opt();
	return(ret);
}

void DSDeRemer::traverse_opt(const RE& r, int& node_num)
{
	assert(class_invariant());
	assert(r.class_invariant());
	// Recursively traverse r and apply the optimizations of Defn. 5.72
	// (function X) of the Taxonomy.
	switch (r.root_operator())
	{
	case EPSILON:
	case EMPTY:
	case SYMBOL:
		node_num++;
		break;
	case OR:
		before.unset_bit(node_num);
		// Fall through is good.
	case CONCAT:
		node_num++;
		traverse_opt(r.left_subexpr(), node_num);
		traverse_opt(r.right_subexpr(), node_num);
		break;
	case STAR:
		before.unset_bit(node_num);
		node_num++;
		after.unset_bit(node_num);
		traverse_opt(r.left_subexpr(), node_num);
		break;
	case PLUS:
	case QUESTION:
		node_num++;
		traverse_opt(r.left_subexpr(), node_num);
		break;
	}
}

std::ostream& operator<<(std::ostream& os, const DSDeRemer& r)
{
	assert(r.class_invariant());
	return(os << "\nDSDeRemer\n" << (const ISImpl&)r);
}
