/***********************************************************************
	Implementation: The set of States in the reversed DFA is represented as a StateSet. A DSDFARev
maintains pointers to the components of the DFA from which it was created. 
	Two DSDFARevs are equal if their StateSets are equal.
 ***********************************************************************/

#include "DSDFARev.h"

CRSet DSDFARev::out_labels() const
{
	assert(class_invariant());
	CRSet a;
	// Go through all of the States to see which have transitions
	// into a State represented by this->which.
	State i;
	for( i = 0; i < which.domain(); i++ ) 
	{
		a.combine(T->labels_between(i, which));
	}
	return(a);
}

DSDFARev DSDFARev::out_transition(const CharRange a) const
{
	assert(class_invariant());
	
	StateSet result;
	// Set the correct domain.
	result.set_domain(which.domain());
	
	// Find the reverse transitions by going through all State's.
	State i;
	for (i = 0; i < which.domain(); i++)
	{
		State j(T->transition_on_range(i, a));
		// We know that there's a transition from i to j on a.
		if (which.contains(j)) 
		{
			// Then we want to add the reverse transition.
			result.add(i);
		}
	}
	assert(class_invariant());
	// Construct the abstract State on the way out of here:
	return(DSDFARev(result, T, S));
}

std::ostream& operator<<(std::ostream& os, const DSDFARev& r)
{
	os << "\nDSDFARev\n" << r.which << *r.T << *r.S << '\n';
	return(os);
}
