/***********************************************************************************
The Σ-algebra Reg<RFA>
Implementation class: Reg<RFA>
Files: Sig-RFA. cpp
Uses: CharRange, Reg, RFA, Sate

Description: The template instantiation Reg<RFA> implements the Σ-algebra of reduced finite
automata, as defined in [Wat93a, Definition 4.29]. The operators can be used directly to construct
complex RFAs, or the Reg<RFA> constructor from RE (which is defined in template
class Reg) can be used to construct the homomorphic image of the regular expression.

Implementation: The implementation follows directly from [Wat93a, Definition 4.29].
***********************************************************************************/
#include "stdafx.h"
#include "CharRange.h"
#include "RFA.h"
#include "Sigma.h"

// Implement the Sigma-algebra operators(Definition 4.29 of the Taxonomy).
// Definition 4.29 (Sigma-algebra of RFA's): The carrier set is [RFA], p33-35
Reg<RFA>& Reg<RFA>::epsilon() {
	// This RFA may have been something in a previous life.
	// Wipe out all previous info in this components;
	reincarnate();

	Nullable = 1;

	assert(class_invariant());
	return(*this);
}

Reg<RFA>& Reg<RFA>::empty() {
	// See epsilon case.
	reincarnate();

	assert(Nullable == 0);

	assert(class_invariant());
	return(*this);
}

Reg<RFA>& Reg<RFA>::symbol(const CharRange r) {
	// See epsilon case.
	reincarnate();

	State q(Q.allocate());

	first.set_domain(Q.size());
	first.add(q);

	last.set_domain(Q.size());
	last.add(q);

	Qmap_inverse.set_range(Q.size());
	Qmap_inverse.add_transition(r, q);

	follow.set_domain(Q.size());
	// Nothing to add to follow.
	
	Nullable = 0;

	current.set_domain(Q.size());

	assert(class_invariant());
	return(*this);
}

Reg<RFA>& Reg<RFA>::Or(const Reg<RFA>& r) {
	assert(class_invariant());
	assert(r.class_invariant());
	// All state-related stuff in r must be adjusted.

	Q.incorporate(r.Q);

	first.disjointing_union(r.first); 
	
	last.disjointing_union(r.last);
	
	Qmap_inverse.disjointing_union(r.Qmap_inverse);
	
	follow.disjointing_union(r.follow);
	
	Nullable = Nullable || r.Nullable;
	
	current.set_domain(Q.size());
	assert(class_invariant());
	return(*this);
}

Reg<RFA>& Reg<RFA>::concat(const Reg<RFA>& r) {
	assert(class_invariant());
	assert(r.class_invariant());
	// See the or operator.
	// All state-related stuff in r must be adjusted.
	// First, incorporate the follow sets.

	follow.disjointing_union(r.follow);
	// Rename the incoming StateSet's first and last StateSets.
	StateSet fi1(r.first);
	fi1.st_rename(Q.size());
	StateSet la1(r.last);
	la1.st_rename(Q.size());

	Q.incorporate(r.Q);
	// Adjust last as well.
	last.set_domain(Q.size());
	follow.union_cross(last, fi1);

	first.set_domain(Q.size());
	if (Nullable) {
		first.set_union(fi1);
	}
	if (r.Nullable) {
		last.set_union(la1);
	}
	else {
		last = la1;
	}
	Qmap_inverse.disjointing_union(r.Qmap_inverse);

	Nullable = Nullable && r.Nullable;

	current.set_domain(Q.size());
	assert(class_invariant());
	return(*this);
}

Reg<RFA>& Reg<RFA>::star() {
	assert(class_invariant());
	
	// Nothing to do to Q, first, last, Qmap_inverse.
	follow.union_cross(last, first);
	Nullable = 1;
	assert(class_invariant());
	return(*this);
}

Reg<RFA>& Reg<RFA>::plus()
{
	assert(class_invariant());
	
	// Don't change Q, first, last, Qmap_inverse, Nullable.
	follow.union_cross(last, first);
	assert(class_invariant());
	return(*this);
}

Reg<RFA>& Reg<RFA>::question() {
	assert(class_invariant());
	
	// Don't change Q, first, last, Qmap_inverse, follow.
	Nullable = 1;
	assert(class_invariant());
	return(*this);
}