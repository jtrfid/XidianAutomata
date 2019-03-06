/***********************************************************************
	Implementation: StateSet inherits from BitVec for implementation. Most of the member functions
are inline dummies, calling the BitVec members.
	Performance: StateSet would benefit from use-counting in BitVec.
 ***********************************************************************/

#include "StateSet.h"

std::ostream& operator<<(std::ostream& os, const StateSet& r)
{
	return(os << (BitVec&)r);
}
