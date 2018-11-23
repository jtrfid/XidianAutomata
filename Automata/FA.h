/***********************************************************************************
	Implementation class: FA

	Files: FA.h, FA.cpp

	Uses: FAabs, RE, State, StatePool, StateRel, StateSet, TransRel

	Description: Class FA implements finite automata as defined in [Wat93a, Definition 2.1]. It
	inherits from FAabs, and implements the interface defined there. A constructor taking an
	RE is provided, implementing Thompson's top-down construction [Wat93a, Construction 4.5]. 
	This constructor can be more efficient than using the Σ- algebra Reg<FA>.

	Definition 2.1 (Finite automaton): A finite automaton (an FA) is a 6-tuple (Q,V,T,E,S,F)
 ***********************************************************************************/
#pragma once
#include <iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "State.h"
#include "StatePool.h"
#include "RE.h"
#include "StateRel.h"
#include "StateSet.h"
#include "TransRel.h"
#include "FAabs.h"

// Implement general finite automata(Definition 2.1 of the Taxonomy).
// These can be constructed by the Sigma-algebra(see Sig-fa.cpp) or using
// the special constructor from RE's.
class FA : virtual public FAabs
{
public:
	// Constructors, destructors, operator=:
	FA();

	// Provide a copy constructor:
	FA(const FA& r);
	
	// A special constructor, implementing the Thompson's top-down construction
	// (see Construction 4.5).  td(const State s, const RE& e, const State f);
	// This constructor can be more efficient than using the Σ- algebra Reg<FA>.
	FA(const RE& e);
	
	// Default operator= is okay.

	///////////////////////////////////////////////////////////////
	// Basic FAabs member functions (without overriding acceptable()):

	// Return the number of stales(or some reasonably close measure).
	virtual int num_states() const;
	
	// Reset the current state  (to start stsates) before beginning to process a string.
	// This is not the default condition for most of the derived classes.
	virtual void restart();

	// Advance the current state by processing a character.
	// advance the automaton by one char in the input string
	virtual void advance(char a);

	// Is the current state an accepting(final) one?
	virtual int in_final() const;

	// Is the automaton stuck(unable to make further transitions)?
	virtual int stuck();
	// Return a DFA accepting the same language as *this.
	virtual DFA determinism() const;
	///////////////////////////////////////////////////////

	// Special member functions:
	inline friend std::ostream& operator<<(std::ostream& os, const FA& r);
	
	inline int class_invariant() const;

protected:
	// Functions states_reqd, td(see Construction 4.5) for use in the constructor from RE.
	// The following follows directly from inspecting Thompson's construction (Definition 4.1).

	// compute states_required in fa from RE
	int states_reqd(const RE& e);

	/**
	 Thompson's top-down construction [Wat93a, Construction 4.5](Top-down Thompson's):
	 We assume a universe of available states U, to define function
		td in U x RE x U --> FA
	 [ Definition 2.1 (Finite automaton): A finite automaton (an FA) is a 6-tuple (Q,V,T,E,S,F) ]
	 The function is defined recursively on the structure of regular expressions:
	 td(s,epsilon,f) = ({s,f},V,empty,{(s,f)},{s},{f}); E.union_cross(s, f);
	 td(s,empty,f) = ({s,f},V,empty,empty,{s},{f})
	 td(s,a,f) = ({s,f},V,{(s,a,f)},empty,{s},{f}) (for all a in V); Transitions.add_transition(s, e.symbol(), f);
	 td(s,E0 concat E1,f) = td(s,e.left_subexpr(),p); td(q, e.right_subexpr(),f);  E.union_cross(p, q); E0 = e.left_subexpr(); E1 = e.right_subexpr();
	 td(s,E0 union(or) E1,f) = td(p, e.left_subexpr(), q); td(r, e.right_subexpr(), t);	E0 = e.left_subexpr(); E1 = e.right_subexpr();
							   E.union_cross(s, p); E.union_cross(s, r); E.union_cross(q, f); E.union_cross(t, f);
	 td(s,E0 star,f) = td(s,e.left_subexpr(),p); E.union_cross(s, p); E.union_cross(q, p); E.union_cross(q, f); E.union_cross(s, f);E0 = e.left_subexpr();
	 td(s,E0 plus,f) = td(s,e.left_subexpr(),p); E.union_cross(s, p); E.union_cross(q, p); E.union_cross(q, f);E0 = e.left_subexpr();
	 td(s,E0 question,f) = td(s,e.left_subexpr(),p); E.union_cross(s, p); E.union_cross(q, f); E.union_cross(s, f);E0 = e.left_subexpr();
	 **/
	void td(const State s, const RE& e, const State f);

	// recycle this FA:
	void reincarnate();

	// Implementation details:

	// A finite automaton (an FA) is a 6-tuple (Q,V,T,E,S,F)
	// Q is a finite set of states
	StatePool Q;    

	// S is a set of start states, F is a set of final states
	StateSet S, F;  
	
	// Transitions maps each State to its out-transitions.
	TransRel Transitions;
	
	// E is the epsilon transition relation.
	StateRel E;
	
	// Simulation stuff:
	StateSet current;
};

inline int FA::class_invariant() const
{
	// Should also check that current is E-closed.
	return(Q.size() == S.domain()
		&& Q.size() == F.domain()
		&& Q.size() == Transitions.domain()
		&& Q.size() == E.domain()
		&& Q.size() == current.domain()
		&& S.class_invariant()
		&& F.class_invariant()
		&& Transitions.class_invariant()
		&& E.class_invariant()
		&& current.class_invariant());
}

inline std::ostream& operator<<(std::ostream& os, const FA& r)
{
	assert(r.class_invariant());
	os << "\nFA\n";
	os << "Q = " << r.Q << '\n';
	os << "S = " << r.S << '\n';
	os << "F = " << r.F << '\n';
	os << "Transitions = \n" << r.Transitions << '\n';
	os << "E = \n" << r.E << '\n';
	os << "current = " << r.current << '\n';
	return(os);
}

