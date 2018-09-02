/***********************************************************************************
Implementation: A DSRBFA contains a StateSet, representing the set of RBFA States that make
up a DFA state in the subset construction. It also includes pointers to some components of
the RBFA that constructed it.
***********************************************************************************/
#include "stdafx.h"
#include "DSRBFA.h"


// A special constructor:
DSRBFA::DSRBFA(const StateSet& rq,
	const Trans *rQmap_inverse,
	const StateRel *rfollow,
	const State rf) :
	which(rq),
	Qmap_inverse(rQmap_inverse),
	follow(rfollow),
	f(rf)
{
	assert(class_invariant());
}

CRSet DSRBFA::out_labels() const
{
	assert(class_invariant());
	return(Qmap_inverse->labels_into(which));
}
// Pretty much follow the stuff in RBFA.cpp
DSRBFA DSRBFA::out_transition(const CharRange a) const
{
	assert(class_invariant());
	return(DSRBFA(follow->image(which).intersection(
		Qmap_inverse->range_transition(a).intersection(which)),
		Qmap_inverse,
		follow,
		f));
}
