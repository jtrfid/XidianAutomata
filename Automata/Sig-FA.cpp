/***********************************************************************************
The ¦²-algebra Reg<FA>
Implementation class: Reg<FA>
Files: Sig-FA. cpp
Uses: CharRange, Reg, FA, Sate

Description: The template instantiation Reg<FA> implements Thompson's ¦²-algebra of finite
automata, as defined in [Wat93a, Definition 4.1]. The operators can be used directly to
construct complex finite automata, or the Reg<FA> constructor from FA (the constructor
defined in class Reg) can be used to construct the homomorphic image of the regular
expression (the constructor uses these operators indirectly).

Implementation: The implementation follows directly from [Wat93a, Definition 4.1]. In some
places it is complicated by the management of domains of StateSets, StateRels, and TransRels.
 ***********************************************************************************/
#include "stdafx.h"
#include "CharRange.h"
#include "FA.h"
#include "Sigma.h"

// Implement the Sigma-algebra operators(Definition 4.29 of the Taxonomy).
Reg<FA>& Reg<FA>::epsilon() {
	// *this may have been something in a previous life.
	// Wipe out all previous components;
	reincarnate();

	State s(Q.allocate());
	State f(Q.allocate());

	S.set_domain(Q.size());
	S.add(s);

	F.set_domain(Q.size());
	F.add(f);
	
	Transitions.set_domain(Q.size());

	E.set_domain(Q.size());
	E.union_cross(s, f);

	current.set_domain(Q.size());

	assert(class_invariant());
	return(*this);
}

Reg<FA>& Reg<FA>::empty() {
	// See epsilon case.
	reincarnate();

	State s(Q.allocate());
	State f(Q.allocate());

	S.set_domain(Q.size());
	S.add(s);

	F.set_domain(Q.size());
	F.add(f);

	Transitions.set_domain(Q.size());
	
	E.set_domain(Q.size());
	
	current.set_domain(Q.size());
	
	assert(class_invariant());
	return(*this);
}

Reg<FA>& Reg<FA>::symbol(const CharRange r) {
	// See epsilon case.
	reincarnate();

	State s(Q.allocate());
	State f(Q.allocate());

	S.set_domain(Q.size());
	S.add(s);

	F.set_domain(Q.size());
	F.add(f);

	Transitions.set_domain(Q.size());
	Transitions.add_transition(s, r, f);

	E.set_domain(Q.size());

	current.set_domain(Q.size());

	assert(class_invariant());
	return(*this);
}

Reg<FA>& Reg<FA>::Or(const Reg<FA>& r) {
	assert(class_invariant());
	assert(r.class_invariant());
	// All state-related stuff in r must be adjusted.
	
	Q.incorporate(r.Q);
	State s(Q.allocate());
	State f(Q.allocate());
	S.disjointing_union(r.S);
	S.set_domain(Q.size());

	F.disjointing_union(r.F);
	F.set_domain(Q.size());

	Transitions.disjointing_union(r.Transitions);
	Transitions.set_domain(Q.size());

	E.disjointing_union(r.E);
	E.set_domain(Q.size());

	E.union_cross(s, S);
	E.union_cross(F, f);
	
	S.clear();
	S.add(s);

	F.clear();
	F.add(f);

	current.set_domain(Q.size());

	assert(class_invariant());
	return(*this);
}

Reg<FA>& Reg<FA>::concat(const Reg<FA>& r) {
	assert(class_invariant());
	assert(r.class_invariant());
	// See the or operator.
	// All state-related stuff in r must be adjusted.

	// Save the old domain().
	int olddom(Q.size());

	// Incorporate the other StatePool.
	Q.incorporate(r.Q);

	// Adjust the domain of the Start states.
	S.set_domain(Q.size());

	// Transitions are just unioned.
	Transitions.disjointing_union(r.Transitions);

	// The epsilon trans.are unioned and F times r.S are added.
	E.disjointing_union(r.E);
	F.set_domain(Q.size());

	// r.S will be needed for epsilon transitions.
	StateSet S1(r.S);
	// rename it to the new StatePool size.
	S1.st_rename(olddom);

	E.union_cross(F, S1);

	// F remains the Final states.
	F = r.F;
	F.st_rename(olddom);

	current.set_domain(Q.size());

	assert(class_invariant());
	return(*this);
}

Reg<FA>& Reg<FA>::star() {
	assert(class_invariant());

	// Create some new States, and adjust the domains.
	State s(Q.allocate());
	State f(Q.allocate());

	S.set_domain(Q.size());
	F.set_domain(Q.size());
	Transitions.set_domain(Q.size());
	E.set_domain(Q.size());
	current.set_domain(Q.size());

	E.union_cross(s, S);
	E.union_cross(s, f);
	E.union_cross(F, S);
	E.union_cross(F, f);

	S.clear();
	S.add(s);
	F.clear();
	F.add(f);

	assert(class_invariant());
	return(*this);
}

Reg<FA>& Reg<FA>::plus()
{
	assert(class_invariant());
	// Create some new States, and adjust the domains.
	State s(Q.allocate());
	State f(Q.allocate());

	S.set_domain(Q.size());
	F.set_domain(Q.size());
	Transitions.set_domain(Q.size());
	E.set_domain(Q.size());
	current.set_domain(Q.size());

	E.union_cross(s, S);
	E.union_cross(F, S);
	E.union_cross(F, f);

	S.clear();
	S.add(s);
	F.clear();
	F.add(f);

	assert(class_invariant());
	return(*this);
}

Reg<FA>& Reg<FA>::question() {
	assert(class_invariant());
	// Create some new States, and adjust the domains.
	State s(Q.allocate());
	State f(Q.allocate());

	S.set_domain(Q.size());
	F.set_domain(Q.size());
	Transitions.set_domain(Q.size());
	E.set_domain(Q.size());
	current.set_domain(Q.size());

	E.union_cross(s, S);
	E.union_cross(s, f);
	E.union_cross(F, f);

	S.clear();
	S.add(s);
	F.clear();
	F.add(f);

	assert(class_invariant());
	return(*this);
}