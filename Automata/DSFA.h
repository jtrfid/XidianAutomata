/**********************************************************************************
 Implementation class: DSFA
Files: DSFA.h, DSFA.cpp
Uses: CharRange, CRSet, StateRel, StateSet, TransRel

Description: Class DSFA implements the abstract class interface required to construct a DFA
from an FA. A DSFA is constructed in the FA member function determinism, and then
passed to template function construct_components, which constructs the DFA components.
 **********************************************************************************/
//#pragma once


#ifndef AUTOMATA_DSFA_H
#define AUTOMATA_DSFA_H


#include <iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "State.h"
#include "StateSet.h"
#include "StateRel.h"
#include "TransRel.h"

// This class is used to represent abstract States in a DFA that is still under
// construction. It is used in the construction of a DFA from an FA. The behaviour
// of a DSFA follows the simulation behaviour of an FA as in the subset construction.
class DSFA
{
public:
	// Must always have an argument-less constructor.
	inline DSFA();

	inline DSFA(const DSFA& r);

	// A special constructor :
	DSFA(const StateSet& rq,
		const TransRel *fT,
		const StateRel *rE,
		const StateSet *rF);

	inline const DSFA& operator = (const DSFA& r);

	// The required member functions:

	inline int final() const;
	CRSet out_labels() const;
	DSFA out_transition(const CharRange a) const;
	inline int operator==(const DSFA& r) const;
	inline int operator != (const DSFA& r) const;

	inline friend std::ostream& operator<<(std::ostream& os, const DSFA& r);

	inline int class_invariant() const;

private:
	StateSet which;
	const TransRel *T;
	const StateRel *E;
	const StateSet *F;
};

// Must always have an argument-less constructor.
inline DSFA::DSFA() :which(), T(0), E(0), F(0)
{
	// No assertion of the class invariant, since it won't qualify.
}

inline DSFA::DSFA(const DSFA& r) : which(r.which), T(r.T), E(r.E), F(r.F)
{
	assert(class_invariant());
}

inline const DSFA& DSFA::operator = (const DSFA& r)
{
	assert(r.class_invariant());
	// *this may not satisfy its invariant yet.
	which = r.which;
	T = r.T;
	E = r.E;
	F = r.F;
	assert(class_invariant());
	return(*this);
}

inline int DSFA::final() const
{
	assert(class_invariant());
	return(which.not_disjoint(*F));
}

inline int DSFA::operator==(const DSFA& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(T == r.T && E == r.E && F == r.F);
	return(which == r.which);
}

inline int DSFA::operator != (const DSFA& r) const
{
	return(!operator==(r));
}

inline int DSFA::class_invariant() const
{
	return(T != 0
		&& E != 0
		&& F != 0
		&& which.domain() == T->domain()
		&& which.domain() == E->domain()
		&& which.domain() == F->domain()
		&& which == E->closure(which));
}

inline std::ostream& operator<<(std::ostream& os, const DSFA& r)
{
	os << "\nDSF\n" << r.which << *r.T << *r.E << *r.F << '\n';
	return(os);
}



#endif // !AUTOMATA_DSFA_H


