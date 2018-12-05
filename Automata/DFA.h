/************************************************************************
	Deterministic FAs
Implementation class: DFA
Files: DFA.h, DFA.cpp
Uses: DFA_components, DSDFARev, DTransRel, FAabs, State, StateSet, StateEqRel, SymRel
Description: A DFA is a deterministic finite automaton (see (Wat93a, Property 2.25] for the
definition of DFA). It implements the interface required by the abstract class FAabs. Additionally,
it also provides member functions to reverse the automaton, and to minimize it
(the minimization functions are described later). A special constructor is provided, which
takes a structure containing the essential components of a DFA, and uses those components
to construct the automaton; this constructor is used in several DFA constructions involving
the subset construction (see (Wat93a, p. 12-13] for the subset construction).
 ************************************************************************/
#pragma once
#include<iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "FAabs.h"
#include "State.h"
#include "StateSet.h"
#include "StateEqRel.h"
#include "SymRel.h"
#include "DTransRel.h"
#include "StatePool.h"
#include "DSDFARev.h"
#include "DFA_components.h"
#include "DFAseed.h"

// Deterministic finite automata: 
// can be constructed from non-det. finite automata, can be minimized.
class DFA : virtual public FAabs
{
public:
	// Constructors, destructors, operator=:
	
	// Default copy constructor, destructor, operator= are okay.
	inline DFA();

	// A special constructor used for subset construction etc.
	inline DFA(const DFA_components& r);
	
	// Some member functions :
    
	// A special one, to reconstruct a DFA, given new components, etc.
	inline DFA& reconstruct(const DFA_components& r);
	
	// Member functions required by class FAabs :
	virtual int num_states() const;
	virtual void restart();
	virtual void advance(char a);
	virtual int in_final() const;
	virtual int stuck();
	virtual DFA determinism() const;
	
	// A function to reverse *this.
	DFA& reverse();

	// Some minimization algorithms:
	inline DFA& min_Brzozowski();
	DFA& min_HopcroftUllman();
	DFA& min_dragon();
	DFA& min_Hopcroft();
	DFA& min_Watson();

	// Some member functions relating to useful State's.
	
	// Can all States reach a final State?
	// Implement Definition 2.23
	int Usefulf() const;
	
	// Remove any States that cannot reach a final State.
	// (This is a last step in minimization, since some of the min. algorithms may yield 
	// a DFA with a sink state.)
	// Implement Remark 2.39  removing states that are not final - reachable.
	DFA& usefulf();

	// Special member functions :
	
	friend std::ostream& operator<<(std::ostream& os, const DFA& r);
	
	inline int class_invariant() const;

protected:
	// Given a minimizing equivalence relation, shrink the DFA.
	DFA& compress(const StateEqRel& r);
	DFA& compress(const SymRel& r);

	// Attempt to split the eq.class [p]_P w.r.t.[q]_P
    // (Return 1 if it was split, 0 otherwise.)
	State split(const State p, const State q, const CharRange a, StateEqRel& P) const;

	// A helper for min_ Watson.
	int are_eq(State p, State q, SymRel& S, const StateEqRel& H, const SymRel& Z) const;

	// Implementation details:
	
	StatePool Q;
	// S must be a singleton set, or empty. |S| <= 1
	StateSet S;
	StateSet F;  // final states
	DTransRel T;

	// Some simulation details:
	State current;
};

// Create a DFA with no State's, accepting nothing.
inline DFA::DFA() :Q(), S(), F(), T(), current(Invalid)
{
	assert(class_invariant());
}

// A special constructor used for subset construction etc.
// A DFA constructed this way will always have a start State.
inline DFA::DFA(const DFA_components& r) :Q(r.Q), S(r.S), T(r.T), F(r.F)
{
	current = Invalid;
	assert(class_invariant());
}

// A special one, to reconstruct a DFA, given new components, etc.
inline DFA& DFA::reconstruct(const DFA_components& r)
{
	Q = r.Q;
	S = r.S;
	T = r.T;
	F = r.F;
	current = Invalid;
	assert(class_invariant());
	return(*this);
}

// Some minimization algorithms:
// See Section 2 (p.5) of the minimization Taxonomy.
inline DFA& DFA::min_Brzozowski()
{
	assert(class_invariant());
	return(reverse().reverse());
}

inline int DFA::class_invariant() const
{
	return(Q.size() == S.domain()
		&& Q.size() == F.domain()
		&& Q.size() == T.domain()
		&& current < Q.size()
		&& S.size() <= 1);
}

