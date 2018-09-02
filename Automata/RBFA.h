/************************************************************************************
Right-biased finite automata
Implementation class: RBFA
Files: RBFA.h, RBFA.cpp
Uses: DFA, FAabs, RFA, State, StatePool, StateRel, StateSet, Trans

Description:Class RBFA implements right-biased finite automata, as defined in (Wat93a, Construction
4.43]. It inherits from FAabs, and implements the interface defined by abstract base
class FAabs. A constructor taking an RFA provides a method of (indirectly) constructing
an RBFA from regular-expressions. The constructor implements isomorphism R ▫ decode ▫ R
as defined in (Wat93a, p. 41]. A special member function takes a reference to an RFA and
implements the non-isomorphic mapping R ▫ convert ▫ R defined in (Wat93a, p. 43]. This
mapping provides an alternative way of constructing an RBFA from an RFA (see (Wat93a,
p. 42-43]).
************************************************************************************/

#pragma once
#include <iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "State.h"
#include "StatePool.h"
#include "RFA.h"
#include "StateRel.h"
#include "StateSet.h"
#include "TransRel.h"
#include "DFA.h"
#include "FAabs.h"

// Implement right-biased FA's (Construction 4.43 in the Taxonomy).
class RBFA : virtual public FAabs
{
public:
	// Constructors, destructors, operator=.

	// Default constructor must build the empty language acceptor.
	RBFA();

	// Default copy constructor, destr, operator= are okay.

	// Special constructor(from RFA) implementing R; decode; R(see
	// Construction 4·45 of the Taxonomy) :
	RBFA(const RFA& r);

	// Standard FAabs operators. Don't override acceptable():
	virtual int num_states() const;
	virtual void restart();
	virtual void advance(char a);
	virtual int in_final() const;
	virtual int stuck();
	virtual DFA determinism() const;

	// Some Sigma-algebra conversions:
	//      taken from Definitions 4.28 and 4.35
	virtual RBFA& decode(const RFA& r);
	virtual RBFA& convert(const RFA& r);

	// Special member functions:

	inline friend std::ostream& operator<<(std::ostream& os, const RBFA& r);

	inline int class_invariant() const;

protected:
	// Implementation stuff, protected for Reg<RBFA>:
	StatePool Q;
	StateSet S;
	// Single final state as required(Construction 4.43):
	State f;
	// See RFA.h and LBFA.h for explanation of Qmap_inverse :
	Trans Qmap_inverse;
	StateRel follow;

	// Simulation stuff:
	StateSet current;
};

inline int RBFA::class_invariant() const
{
	return(Q.contains(f)
		&& Q.size() == S.domain()
		&& Q.size() == Qmap_inverse.range()
		&& Q.size() == follow.domain()
		&& Q.size() == current.domain()
		&& S.class_invariant()
		&& Qmap_inverse.class_invariant()
		&& follow.class_invariant()
		&& current.class_invariant());
}

inline std::ostream& operator<<(std::ostream& os, const RBFA& r)
{
	assert(r.class_invariant());
	os << "\nRBFA\n";
	os << "Q = " << r.Q << '\n';
	os << "S = " << r.S << '\n';
	os << "f = " << r.f << '\n';
	os << "Qmap_inverse = " << r.Qmap_inverse << '\n';
	os << "follow = \n" << r.follow << '\n';
	os << "current = " << r.current << '\n';
	return(os);
}

