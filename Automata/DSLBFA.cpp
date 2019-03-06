/***********************************************************************************
Implementation: A DSLBFA contains a StateSet, representing the set of LBFA States that make
up a DFA state in the subset construction. It also includes pointers to some components of
the LBFA that constructed it.
 ***********************************************************************************/

#include "DSLBFA.h"


 // A special constructor:
DSLBFA::DSLBFA(const StateSet& rq,
	const Trans *rQmap_inverse,
	const StateRel *rfollow,
	const StateSet *rF):
	which(rq),
	Qmap_inverse(rQmap_inverse),
	follow(rfollow),
	F(rF)
{
	assert(class_invariant());
}

CRSet DSLBFA::out_labels() const
{
	assert(class_invariant());
	// *Qmap_inverse contains the transitions _into_ State's.
	// So, we take the image of which under follow to get which!s out-trans
	return(Qmap_inverse->labels_into(follow->image(which)));
}
// Pretty much follow the stuff in LBFA.cpp
DSLBFA DSLBFA::out_transition(const CharRange a) const
{
	assert(class_invariant());
	return(DSLBFA(follow->image(which).intersection(
		Qmap_inverse->range_transition(a)),
		Qmap_inverse,
		follow,
		F));
}
