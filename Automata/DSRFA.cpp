/************************************************************************************
Implementation: A DSRFA contains a StateSet, representing the set of RFA States that make
up a DFA state in the subset construction (under the right-biased interpretation of states).
It also contains an integer indicating if the abstract state is a final one.
 ************************************************************************************/
#include "stdafx.h"
#include "DSRFA.h"

// Use the RBFA interpretation of State's (Section 4.3 of the Taxonomy).
// A special constructor:
DSRFA::DSRFA(const StateSet& rq,
	const Trans *rQmap_inverse,
	const StateRel *rfollow,
	const StateSet *rfirst,
	const StateSet *rlast,
	const int rfinalness):
	which(rq),
	Qmap_inverse(rQmap_inverse),
	follow(rfollow),
	first(rfirst),
	last(rlast),
	finalness(rfinalness)
{
	assert(class_invariant());
}

CRSet DSRFA::out_labels() const
{
	assert(class_invariant());
	return(Qmap_inverse->labels_into(which));
}

// Pretty much follow the stuff in rbfa.cpp
DSRFA DSRFA::out_transition(const CharRange a) const
{
	assert(class_invariant());
	StateSet t(Qmap_inverse->range_transition(a).intersection(which));
	return(DSRFA(follow->image(t),
		Qmap_inverse,
		follow,
		first,
		last,
		t.not_disjoint(*last)));
}
