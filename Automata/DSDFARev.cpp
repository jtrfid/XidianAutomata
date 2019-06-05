﻿/***********************************************************************
	Implementation: The set of States in the reversed DFA is represented as a StateSet. A DSDFARev
maintains pointers to the components of the DFA from which it was created. 
	Two DSDFARevs are equal if their StateSets are equal.
 ***********************************************************************/

#include "DSDFARev.h"

// return  CRSet of (in-transitions of which)。进入(in)当前对象which的transitions的字符集将成为返回对象的out字符集，就是reverse语义。
CRSet DSDFARev::out_labels() const
{
	assert(class_invariant());
	CRSet a;
	// Go through all of the States to see which have transitions
	// into a State represented by this --> which.
	State i;
	for( i = 0; i < which.domain(); i++ ) 
	{
		a.combine(T->labels_between(i, which));
	}
	return(a);
}

// return which = {p | T(p,a)属于which },即进入“in”当前对象which的状态集,成为返回对象的“out”状态集，就是reverse语义。
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
		State j(T->transition_on_range(i, a)); // j=T(i,a)
		// We know that there's a transition from i to j on a.
		if (which.contains(j)) 
		{
			// Then we want to add the reverse transition.
			result.add(i);
		}
	}
	assert(class_invariant());
	// Construct the abstract State on the way out of here:
	return(DSDFARev(result, T, S)); // result= {q | T(q,a)属于which }= states of (in-transitions of which)
}

std::ostream& operator<<(std::ostream& os, const DSDFARev& r)
{
	//os << "\nDSDFARev\n" << r.which << *r.T << *r.S << '\n';
	os << " " << r.which << " ";
	return(os);
}
