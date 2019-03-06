/***********************************************************************************
	Reduced finite automata
	Implementation class: RFA
	Files: RFA.h, RFA.cpp
	Uses: DFA, FAabs, LBFA, RBFA, RE, StatePooi, StateRel, StateSet, Trans

	Description: Class RFA implements reduced finite automata, as defined in [Wat93a, Definition
	4.24]. It inherits from FAabs, and implements the interface defined by abstract base FAabs.
	A constructor taking an RE provides a very efficient top-down implementation of homomorphism
	RFA defined in [Wat93a, Definition 4.30].

	Definition 4.24 (RFA): A reduced FA (RFA) is a 7-tuple (Q, V, follow, first, last, null, Qmap) where
	• Q is a finite set of states,
    • V is a alphabet,
    • follow (in P(Q x Q)) is a follow relation (replacing the transition relation),
    • first (subset Q) is a set of initial states (replacing T(s) in an LBFA) ,
    • last (subset Q) is a set of final states,
    • null (in {true,false}) is a Boolean value (encoding s in F in an LBFA), and
    • Qmap (in P( Q x V)) maps each state to exactly one symbol (it is also viewed as Qmap in Q --> V, 
	  and its inverse as Qmap^-1 in V --/--> P(Q)[the set of all partial functions from V to P(Q)]).
 ***********************************************************************************/

//#pragma once


#ifndef AUTOMATA_RFA_H
#define AUTOMATA_RFA_H



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
#include "DFA.h"
#include "FAabs.h"

// The existence of LBFA and RBFA are needed, for friendship.
// Can't include LBFA.h or RBFA.h due to circularity.
class LBFA;
class RBFA;

// Implement RFA's (reduced finite automata -- Definition 4.24 of the Taxonomy)
// as It type of FAabs.
class RFA : virtual public FAabs
{
public:
	// Some constructors:
	RFA();
	// Need a copy constructor:
	RFA(const RFA& r);

	// The Sigma-homomorphism constructor(see Definition 4.30): RE --> RFA
	RFA(const RE& e);

	// Default destr, opemtor = are okay.

	// Normal FAabs member functions(don't override acceptable()):

	virtual int num_states() const;
	virtual void restart();
	virtual void advance(char a);
	virtual int in_final() const;
	virtual int stuck();
	virtual DFA determinism2() const;

	// An alternate implementation of determinism() using the LBFA interpretation.
	virtual DFA determinism() const;

	// Special members:

	inline friend std::ostream& operator<<(std::ostream& os, const RFA& r);

	// These two must be friends so that they can construct themselves properly.
	friend class LBFA;
	friend class RBFA;

	inline int class_invariant() const;

protected:
	// A helper: compute all of the components into place.
	//        for use in the constructor.

// Implement a top down version of Sigma homomorphism rfa(Definition 4.30): RE-->RFA
// 参见：Definition 4.29 (Sigma-algebra of RFA's): p33-35
// N: Nullable, {true,flase} ==> {1,0}
// Qm: V --> P(Q)
	void rfa_into(const RE& e,
		StatePool& Qp,
		StateSet& f,
		StateSet& l,
		Trans& Qm,
		StateRel& foll,
		int& N);

	// Recycle *this:
	void reincarnate();

	// Implementation details, protected for Reg<RFA> use.
	// Q is a finite set of states,
	StatePool Q;

	// first(subset Q) is a set of initial states(replacing T(s) in an LBFA),
	// last(subset Q) is a set of final states,
	StateSet first, last;

	// Qmap (in P( Q x V)) maps each state to exactly one symbol (it is also viewed as Qmap in Q --> V, 
	// and its inverse as Qmap^-1 in V --/-->P(Q)[the set of all partial functions from V to P(Q)]).
	// Trans用struct TransPair 表示:T(a) = { q | a in V，q in Q }, 而Qmap 属于P(Q x V),
	// 因此这里表示Qmap的inverse，V --> P(Q)
	Trans Qmap_inverse;

	// follow(in P(Q x Q)) is a follow relation(replacing the transition relation),
	StateRel follow;

	// null (in {true,false}) is a Boolean value (encoding s in F in an LBFA)
	// if epsilon属于LBFA, true; final set中包含s
	// {true, flase} == > {1, 0}
	int Nullable;

	// Some simulation stuff.
	int final;
	StateSet current;
};

inline int RFA::class_invariant() const
{
	return(Q.size() == first.domain()
		&& Q.size() == last.domain()
		&& Q.size() == Qmap_inverse.range()
		&& Q.size() == follow.domain()
		&& Q.size() == current.domain()
		&& first.class_invariant()
		&& last.class_invariant()
		&& Qmap_inverse.class_invariant()
		&& follow.class_invariant()
		&& current.class_invariant());
}

inline std::ostream& operator<<(std::ostream& os, const RFA& r)
{
	assert(r.class_invariant());
	os << "\nRFA\n";
	os << "Q = " << r.Q << '\n';
	os << "first = " << r.first << '\n';
	os << "last = " << r.last << '\n';
	os << "Qmap_inverse = " << r.Qmap_inverse << '\n';
	os << "follow = \n" << r.follow << '\n';
	os << "Nullable = " << (r.Nullable ? "true" : "false");
	os << "\nfinal = " << (r.final ? "true" : "false");
	os << "\ncurrent = " << r.current << '\n';
	return(os);
}


#endif // !AUTOMATA_RFA_H
