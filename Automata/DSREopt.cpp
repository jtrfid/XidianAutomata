/***********************************************************************
Implementation: Redundant information is eliminated by calling RE member function reduce
in the constructor from an RE.

Performance: See DSRE.
 ***********************************************************************/

#include "DSREopt.h"

std::ostream& operator<<(std::ostream& os, const DSREopt& r)
{
	assert(r.class_invariant());
	return(os << "\nDSRE\n" << (const RE&)r);
}
