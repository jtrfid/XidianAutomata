/*************************************************************************
	As an example of an abstract state, consider class DSDFARev.
Implementation class: DSDFARev

Files: DSDFARev.h, SDDFARev.cpp

Uses: CharRange, CRSet, DTransRel, StateSet

Description: Class DSDFARev is used in the reversal of a DFA. It is an abstract state representing
a set of states, in the reversal of the deterministic automaton (the reversal of a
deterministic finite automaton is not necessarily deterministic). A DSDFARev is constructed
in the DFA member function reverse. Member functions support all of the required interface
of an abstract state.
 *************************************************************************/
//#pragma once

#ifndef AUTOMATA_DSDFAREV_H
#define AUTOMATA_DSDFAREV_H





#include <iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "DTransRel.h"

// This class is used to represent abstract States in a DFA that is still under
// construction. It is used in the reversal of a DFA.
// Objects of the class represent States in the subset construction of the
// reverse of a DFA.
class DSDFARev
{
public:
	// Must always have an argument-less constructor.
	inline DSDFARev();

	inline DSDFARev(const DSDFARev& r);

	// A special constructor:
	inline DSDFARev(const StateSet& rq, const DTransRel *rT, const StateSet *rS);

	inline const DSDFARev& operator = (const DSDFARev& r);

	// The required member functions :
	inline int final() const;
	CRSet out_labels() const;
	DSDFARev out_transition(const CharRange a) const;
	inline int operator == (const DSDFARev& r) const;
	inline int operator != (const DSDFARev& r) const;

	friend std::ostream& operator<<(std::ostream& os, const DSDFARev& r);

	inline int class_invariant() const;

private:
	StateSet which;
	const DTransRel *T;
	const StateSet *S;
};

// Must always have an argument-less constructor.
inline DSDFARev::DSDFARev() :which(), T(0), S(0)
{

}

inline DSDFARev::DSDFARev(const DSDFARev& r) : which(r.which), T(r.T), S(r.S)
{
	assert(class_invariant());
}

// A special constructor:
inline DSDFARev::DSDFARev(const StateSet& rq, const DTransRel *rT, const StateSet *rS)
	:which(rq), T(rT), S(rS)
{
	assert(class_invariant());
}

inline const DSDFARev& DSDFARev::operator = (const DSDFARev& r)
{
	assert(r.class_invariant());
	which = r.which;
	T = r.T;
	S = r.S;
	assert(class_invariant());
	return(*this);
}

// The required member functions :
inline int DSDFARev::final() const
{
	assert(class_invariant());
	return(which.not_disjoint(*S));
}

inline int DSDFARev::operator == (const DSDFARev& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(T == r.T && S == r.S);
	return(which == r.which);
}

inline int DSDFARev::operator != (const DSDFARev& r) const
{
	return(!operator==(r));
}

inline int DSDFARev::class_invariant() const
{
	return(T != 0 && S != 0 && which.domain() == T->domain()
		&& which.domain() == S->domain());
}



#endif // !AUTOMATA_DSDFAREV_H


