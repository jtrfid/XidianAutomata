/************************************************************************************
Implementation: A DSRFA2 contains a StateSet, representing the set of RFA States that make
up a DFA state in the subset construction (under the left-biased interpretation of states).
It also contains an integer indicating if the abstract state is a final one.

Performance: For higher performance in constructing a DFA, use class DSRFA instead.
************************************************************************************/

#include "DSRFA2.h"

// Use the LBFA interpretation of State's (Section 4.2 of the Taxonomy).
// A special constructor(for use in constructing the start state):
DSRFA2::DSRFA2( const Trans *rQmap_inverse,
	const StateRel *rfollow,
	const StateSet *rfirst,
	const StateSet *rlast,
	const int rfinalness) :
	Qmap_inverse(rQmap_inverse),
	follow(rfollow),
	first(rfirst),
	last(rlast),
	finalness(rfinalness)
{
	// We assume that we receive the finalness magically as a parameter.
	
	which.set_domain(follow->domain());
	// The emptiness of which is the indicator of the start state.
	assert(which.empty());
	assert(class_invariant());
}

// Another special constructor, for use in out_transitions():
DSRFA2::DSRFA2(const StateSet& rq,
	const Trans *rQmap_inverse,
	const StateRel *rfollow,
	const StateSet *rfirst,
	const StateSet *rlast) :
	which(rq),
	Qmap_inverse(rQmap_inverse),
	follow(rfollow),
	first(rfirst),
	last(rlast)
{
	assert(!rq.empty());
	finalness = rq.not_disjoint(*last);
	assert(class_invariant());
}

CRSet DSRFA2::out_labels() const
{
	assert(class_invariant());
	// There are two cases to deal with, it's either the start state, or not.
	//             emptiness of which is indicator of start state.
		if (which.empty()) 
		{
			return(Qmap_inverse->labels_into(*first));
		} 
		else
		{
			return(Qmap_inverse->labels_into(follow->image(which)));
		}
}

// Pretty much follow the stuff in rbfa.cpp
DSRFA2 DSRFA2::out_transition(const CharRange a) const
{
	assert(class_invariant());
	// Again, two cases :
	StateSet t(which.empty() ? *first : follow->image(which));
	assert(!t.empty());
	return(DSRFA2(Qmap_inverse->range_transition(a).intersection(t),
		Qmap_inverse,
		follow,
		first,
		last));
}
