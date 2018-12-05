/***********************************************************************************
The Σ-algebra Reg<FA>
Implementation class: Reg<FA>
Files: Sig-FA. cpp
Uses: CharRange, Reg, FA, Sate

Description: The template instantiation Reg<FA> implements Thompson's Σ-algebra of finite
automata, as defined in [Wat93a, Definition 4.1]. The operators can be used directly to
construct complex finite automata, or the Reg<FA> constructor from FA (the constructor
defined in class Reg) can be used to construct the homomorphic image of the regular
expression (the constructor uses these operators indirectly).

Implementation: The implementation follows directly from [Wat93a, Definition 4.1]. In some
places it is complicated by the management of domains of StateSets, StateRels, and TransRels.

M0 = {Q0,V,T0,E0,S0,F0}, M1 = {Q1,V,T1,E1,S1,F1}
// Definition 4.1 (Thompson'Sigma-algebra of FA's)
// Construction 4.3 (Thompson): Thompson's construction is the (unique) homomorphism Th(The operators (with subscript Th, for Thompson))
// from RE to Thompson's Sigma-algebra of FA's.
// C(epsilon,Th),C(empty,Th),C(a,Th),C(.,Th([M0],[M1])),C(union,Th([M0],[M1])),C(star,Th([M])),C(star,Th([M])),C(plus,Th([M])),C(question,Th([M]))
// Construct the homomorphic image of regular expression r, using the Sigma-algebra operators
// (corresponding to the operators of the regular expression).
// A constructor from RE (a regular expression). Given that regular expressions are the Sigma-term algebra,
// this constructor constructs the homomorphic image of the regular expression in the Sigma-algebra of T.
// Definition 2.6 (Isomorphism of FA's)
// Definition 3.7 (Sigma-homomorphism): Given E-a1gebras (V,F) and (W,G), a Sigma-homomorphism from(V, F) to(W, G)
 ***********************************************************************************/
#include "stdafx.h"
#include "CharRange.h"
#include "FA.h"
#include "Sigma.h"

// Implement the Sigma-algebra operators(Definition 4.1 of the Taxonomy).
// *this: add new states for start and final state(s,f), E: {s,f}
Reg<FA>& Reg<FA>::epsilon() {
	// *this may have been something in a previous life.
	// Wipe out all previous components;
	reincarnate();

	State s(Q.allocate());  // new states for start and final state
	State f(Q.allocate());

	S.set_domain(Q.size()); // 增加了两个新状态，需要调整S,F,E,Transitions的domain
	S.add(s);

	F.set_domain(Q.size());
	F.add(f);
	
	Transitions.set_domain(Q.size());

	E.set_domain(Q.size());
	E.union_cross(s, f); // E: {s}×{f}

	current.set_domain(Q.size());

	assert(class_invariant());
	return(*this);
}

// *this: add new states for start and final state
Reg<FA>& Reg<FA>::empty() {
	// See epsilon case.
	reincarnate();

	State s(Q.allocate()); // new states for start and final state
	State f(Q.allocate());

	S.set_domain(Q.size()); // 增加了两个新状态，需要调整S,F,E,Transitions的domain
	S.add(s);

	F.set_domain(Q.size());
	F.add(f);

	Transitions.set_domain(Q.size());
	
	E.set_domain(Q.size());
	
	current.set_domain(Q.size());
	
	assert(class_invariant());
	return(*this);
}

// *this: add new states for start and final state; T(s) = {(r,f)}
Reg<FA>& Reg<FA>::symbol(const CharRange r) {
	// See epsilon case.
	reincarnate();

	State s(Q.allocate()); // new states for start and final state
	State f(Q.allocate());

	S.set_domain(Q.size()); // 增加了两个新状态，需要调整S,F,E,Transitions的domain
	S.add(s);

	F.set_domain(Q.size());
	F.add(f);

	Transitions.set_domain(Q.size());
	Transitions.add_transition(s, r, f);  // T(s) = {(r,f)}

	E.set_domain(Q.size());

	current.set_domain(Q.size());

	assert(class_invariant());
	return(*this);
}

// *this = *this union r
// set new states for start and final state
// binary operator，Q0和Q1无交集，disjoint state sets
Reg<FA>& Reg<FA>::Or(const Reg<FA>& r) {
	assert(class_invariant());
	assert(r.class_invariant());
	// All state-related stuff in r must be adjusted.
	
	//binary operator，Q0和Q1无交集，disjoint state sets
	// Q = Q0 ∪ Q1 ∪ {q0,q1}
	Q.incorporate(r.Q); // Incorporate another StatePool by making it disjoint
	// new states for start and final state
	State s(Q.allocate());
	State f(Q.allocate());

	S.disjointing_union(r.S); // S0 ∪ S1
	S.set_domain(Q.size());   // 并集后，调整domain

	F.disjointing_union(r.F); // F0 ∪ F1
	F.set_domain(Q.size());   // 并集后，调整domain

	Transitions.disjointing_union(r.Transitions); // T0 ∪ T1
	Transitions.set_domain(Q.size()); // 并集后，调整domain

	// E = E0 ∪ E1 ∪ ({q0} × (S0 ∪ S1)) ∪ ((F0 ∪ F1) × {q1})
	E.disjointing_union(r.E); // E0 ∪ E1
	E.set_domain(Q.size());   // 并集后，调整domain
	E.union_cross(s, S);  // {q0} × (S0 ∪ S1), map(s).add(S)
	E.union_cross(F, f);  // (F0 ∪ F1) × {q1}, map(F).add(f)
	
	S.clear();  // 清除以前的S
	S.add(s);   // S = { q0 }

	F.clear(); // 清除以前的S
	F.add(f);  // F = { q1 }

	current.set_domain(Q.size());

	assert(class_invariant());
	return(*this);
}

// *this = *this concatenate r
// binary operator，Q0和Q1无交集，disjoint state sets
Reg<FA>& Reg<FA>::concat(const Reg<FA>& r) {
	assert(class_invariant());
	assert(r.class_invariant());
	// Q = Q0 ∪ Q1，T = T0 ∪ T1, E = E0 ∪ E1 ∪ (F0 × S1)，S = S0, F = F1

	// See the or operator.
	// All state-related stuff in r must be adjusted.
	// Save the old domain().
	int olddom(Q.size());

	// Incorporate the other StatePool.
	Q.incorporate(r.Q);  // Q状态池 + r.Q

	// Adjust the domain of the Start states.
	S.set_domain(Q.size());

	// Transitions are just unioned.调整domain + r.domain,确保无交集
	Transitions.disjointing_union(r.Transitions); // T0 ∪ T1

	// The epsilon trans.are unioned and F times r.S are added. F0 X S1
	E.disjointing_union(r.E); // 调整domain + r.domain,确保无交集
	F.set_domain(Q.size());

	// r.S will be needed for epsilon transitions.
	StateSet S1(r.S);
	// rename it to the new StatePool size.
	S1.st_rename(olddom); // 修改编号+olddom

	E.union_cross(F, S1); // F0×S1, map(F0).add(S1)

	// F remains the Final states.
	F = r.F; // final state
	F.st_rename(olddom); // 修改编号+olddom

	current.set_domain(Q.size());

	assert(class_invariant());
	return(*this);
}

// *this重复0次或多次，表示Kleene闭包, 包含epsilon语言
// *this: add new states for start and final state
Reg<FA>& Reg<FA>::star() {
	assert(class_invariant());

	// Q = Q∪{q0,q1}，T, E = E∪({q0}×S)∪(F×S)∪(F×{q1})∪{(q0,q1)，S = {q0}, F = {q1}

	// Create some new States, and adjust the domains.
	State s(Q.allocate()); // new states for start and final state
	State f(Q.allocate());

	S.set_domain(Q.size()); // 增加了两个新状态，需要调整S,F,E,Transitions的domain
	F.set_domain(Q.size());
	Transitions.set_domain(Q.size());
	E.set_domain(Q.size());
	current.set_domain(Q.size());

	E.union_cross(s, S); // {q0}×S, map(s).add(S)
	E.union_cross(s, f); // {(q0,q1)}包含epsilon, 0次执行*this，map(s).add(f)
	E.union_cross(F, S); // F×S, 一次或多次执行*this，map(F).add(S)
	E.union_cross(F, f); // F×{q1}，map(F).add(f)

	S.clear(); // 清除以前的S
	S.add(s);
	F.clear(); // 清除以前的F
	F.add(f);

	assert(class_invariant());
	return(*this);
}

// *this至少重复1次，不包含epsilon语言
// *this: set new states for start and final state
Reg<FA>& Reg<FA>::plus()
{
	assert(class_invariant());
	// Q = Q∪{q0,q1}，T, E = E∪({q0}×S)∪(F×S)∪(F×{q1})，S = {q0}, F = {q1}

	// Create some new States, and adjust the domains.
	State s(Q.allocate()); // new states for start and final state
	State f(Q.allocate());

	S.set_domain(Q.size()); // 增加了两个新状态，需要调整S,F,E,Transitions的domain
	F.set_domain(Q.size());
	Transitions.set_domain(Q.size());
	E.set_domain(Q.size());
	current.set_domain(Q.size());

	E.union_cross(s, S); // {q0}×S, map(s).add(S)
	E.union_cross(F, S); // F×S, map(F).add(S)
	E.union_cross(F, f); // F×{q1}, map(F).add(f)

	S.clear(); // 清除以前的S
	S.add(s);
	F.clear(); // 清除以前的F
	F.add(f);

	assert(class_invariant());
	return(*this);
}

// *this重复0次或1次，包含epsilon语言
// *this: set new states for start and final state
Reg<FA>& Reg<FA>::question() {
	assert(class_invariant());
	// Q = Q∪{q0,q1}，T, E = E∪({q0}×S)∪(F×{q1})∪{(q0,q1)}，S = {q0}, F = {q1}

	// Create some new States, and adjust the domains.
	State s(Q.allocate()); // new states for start and final state
	State f(Q.allocate());

	S.set_domain(Q.size()); // 增加了两个新状态，需要调整S,F,E,Transitions的domain
	F.set_domain(Q.size());
	Transitions.set_domain(Q.size());
	E.set_domain(Q.size());
	current.set_domain(Q.size());

	E.union_cross(s, S); // {s}×S, map(s).add(S)
	E.union_cross(s, f); // {s}×{f},包含epsilon语言，重复*this 0次，map(s).add(f)
	E.union_cross(F, f); // F×{f},map(F).add(f)

	S.clear(); // 清除以前的S
	S.add(s);
	F.clear(); // 清除以前的F
	F.add(f);

	assert(class_invariant());
	return(*this);
}