/************************************************************************************
Left-biased finite automata
Implementation class: LBFA
Files: LBFA.h, LBFA.cpp
Uses: DFA, FAabs, RFA, State, StatePool, StateRel, StateSet, Trans

Description: Class LBFA implements left-biased finite automata, as defined in [Wat93a, Definition 4.20]. 
It inherits from FAabs, and implements the interface defined by abstract base FAabs. 
A constructor taking an RFA provides a method of (indirectly) constructing an
LBFA from regular expressions. The constructor implements isomorphism decode as defined
in [Wat93a, Definition 4.28]. A special member function takes an an RFA and implements
the non-isomorphic mapping convert defined in [Wat93a, Definition 4.35]. This mapping
provides an alternative way of constructing an LBFA from an RFA (see [Wat93a, p.36-37)).

//////////////////////////////////////////////////////////////////////////////////
	RE --> LBFA:
	(1) RE --> RFA
		RFA rfa = RFA(re); // 或sigma代数运算：Reg<RFA>(re)
	(2) Specially construct from an RFA(see Definition 4.28). RFA --> LBFA
	//LBFA lbfa = LBFA(rfa); // 在LBFA.h,LBFA.cpp定义 LBFA(const RFA& r)

	// 等效，由LBFA中的LBFA& decode(const RFA& r)函数完成
	// LBFA lbfa; lbfa = lbfa.decode(rfa);

	/////// 综合(1),(2)
	// Construction 4.32 (Berry-Sethi): Construction BS 属于 RE --> LBFA
	// lbfa(E) = BS(E) = decode o rfa(E)
	// 等效，在Constrs.h中封装LBFA BerrySethi(const RE& r)
	// RE -->RFA: rfa = RFA(re); RFA --> LBFA, lbfa = LBFA(rfa) 或 lbfa = lbfa.decode(rfa)
	LBFA lbfa = BerrySethi(re);
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

class LBFA : virtual public FAabs
{
public:
	// Constructors, destructors, operator=.

	// Default constructor must build the empty language acceptor.
	LBFA();

	// Default copy constructor, destr, operator= are okay.

	// Specially construct from an RFA(see Definition 4.28). RFA --> LBFA
	// LBFA& decode(const RFA& r)完成同样的功能
	LBFA(const RFA& r);

	// Standard FAabs operators. Don't override acceptable():
	virtual int num_states() const;
	virtual void restart();
	virtual void advance(char a);
	virtual int in_final() const;
	virtual int stuck();
	virtual DFA determinism() const;

	// Some Sigma-algebra conversions:

	// Implement homomorphism decode(Definition 4.28). RFA--> LBFA
	// 构造函数LBFA(const RFA& r)完成同样的功能
	virtual LBFA& decode(const RFA& r);

	// Implement non-homomorphic RFA->LBFA mapping convert(Defn. 4.35).
	virtual LBFA& convert(const RFA& r);

	// Special member functions:

	inline friend std::ostream& operator<<(std::ostream& os, const LBFA& r);

	inline int class_invariant() const;

protected:
	// Implementation stuff, protected for Reg<LBFA>:

	// Q is a finite set of states,
	StatePool Q;

	// Single start state.
	State s;

	// F (subset Q) is a set of final states,
	StateSet F;

	// Qmap(see Definition 4.24) stored as its inverse.
	// Qmap (in P( Q x V)) maps each state to exactly one symbol (it is also viewed as Qmap in Q --> V, 
	// and its inverse as Qmap^-1 in V--/-- > P(Q)[the set of all partial functions from V to P(Q)]).
	// Trans用struct TransPair 表示:T(a) = { q | a in V，q in Q }, 而Qmap 属于P(Q x V),
	// 因此这里表示Qmap的inverse，V --> P(Q)
	Trans Qmap_inverse;

	// follow(in P(Q x Q)) is a follow relation(replacing the transition relation),
	StateRel follow;

	// Simulation stuff:
	StateSet current;
};

inline int LBFA::class_invariant() const
{
	return(Q.size() == F.domain()
		&& Q.size() == Qmap_inverse.range()
		&& Q.size() == follow.domain()
		&& Q.size() == current.domain()
		&& F.class_invariant()
		&& Qmap_inverse.class_invariant()
		&& follow.class_invariant()
		&& current.class_invariant());
}

inline std::ostream& operator<<(std::ostream& os, const LBFA& r)
{
	assert(r.class_invariant());
	os << "\nLBFA\n";
	os << "Q = " << r.Q << '\n';
	os << "s = " << r.s << '\n';
	os << "F = " << r.F << '\n';
	os << "Qmap_inverse = " << r.Qmap_inverse << '\n';
	os << "follow = \n" << r.follow << '\n';
	os << "current = " << r.current << '\n';
	return(os);
}

