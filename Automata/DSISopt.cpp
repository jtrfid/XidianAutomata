/***********************************************************************
Implementation: The implementation is largely provided by the base class ISImpl. The member
function opt (with helper traverse_opt) implements the optimized dot filter function Y as
defined in [Wat93a, Definition 5.79]. The filter function makes a single prefix traversal of the
RE expression tree. By applying the filter, it becomes more likely that template function
construct_components will find two item sets (denoting the same language) to be equal.
The reason why the optimized item set construction yields smaller DFAs than DeRemer's
construction is that the Y filter is more effective at removing redundant information than
the X filter used in DeRemer's construction (see [Wat93a, Remark 5.81]).
***********************************************************************/
#include "stdafx.h"
#include "DSISopt.h"

DSISopt DSISopt::out_transition(const CharRange a) const
{
	assert(class_invariant());
	DSISopt ret(*this);
	ret.move_dots(a);
	ret.opt();
	return(ret);
}

// Implement Definition 5.79
void DSISopt::traverse_opt(const RE& r, int& node_num)
{
	assert(class_invariant());
	assert(r.class_invariant());
	// Recursively traverse r and apply the optimizations of Defn. 5.79
	// (function Y) of the Taxonomy.
	// After will already have been cleared by DSISopt::opt()
	switch (r.root_operator())
	{
	case EPSILON:
	case EMPTY:
		before.unset_bit(node_num);
		node_num++;
		break;
	case SYMBOL:
		// Don't remove a bit before -- see Defintion 5.79
		node_num++;
		break;
	case OR:
	case CONCAT:
		before.unset_bit(node_num);
		node_num++;
		traverse_opt(r.left_subexpr(), node_num);
		traverse_opt(r.right_subexpr(), node_num);
		break;
	case STAR:
	case PLUS:
	case QUESTION:
		before.unset_bit(node_num);
		node_num++;
		traverse_opt(r.left_subexpr(), node_num);
		break;
	}
}

std::ostream& operator<<(std::ostream& os, const DSISopt& r)
{
	assert(r.class_invariant());
	return(os << "\nDSISopt\n" << (const ISImpl&)r);
}
