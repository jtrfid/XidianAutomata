/***********************************************************************
Implementation: Most of the implementation is provided by class ISImpl.
 ***********************************************************************/
#include "stdafx.h"
#include "DSIS.h"

DSIS DSIS::out_transition(const CharRange a) const
{
	assert(class_invariant());
	DSIS ret(*this);
	ret.move_dots(a);
	return(ret);
}

std::ostream& operator<<(std::ostream& os, const DSIS& r)
{
	assert(r.class_invariant());
	return(os << "\nDSIS\n" << (const ISImpl&)r);
}
