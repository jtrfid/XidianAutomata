/***********************************************************************
Implementation: A DSRE inherits from RE. The interface required of abstract states (such as
member functions final, out_labels, and out_transition) is provided through the use of the RE
member functions such as Null, First, and derivative (respectively). When a new DSRE is
constructed, it is put into similarity normal form, to ensure that there will only be finitely
many DSREs (see [Wat93a, Theorem 5.31]).

Performance: RE member function derivative returns an RE by value, which is then passed to
the DSRE constructor. Use-counting RE could eliminate the overhead of copy constructor
and destructor calls.
 ***********************************************************************/
#include "stdafx.h"
#include "DSRE.h"


std::ostream& operator<<(std::ostream& os, const DSRE& r)
{
	assert(r.class_invariant());
	return(os << "\nDSRE\n" << (const RE&)r);
}
