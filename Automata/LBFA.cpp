/***********************************************************************************
Implementation: Class LBFA is a friend of class RFA. Most of the member functions are
implemented in a straight-forward manner.
 ***********************************************************************************/
#include "stdafx.h"
#include "DSLBFA.h"
#include "DFAseed.h"
#include "LBFA.h"


// Default constructor must build the empty language acceptor.
LBFA::LBFA()
{
	// Ensure that *this has the LBFA properties.
	// a single start State, with no in-transitions.
	s = Q.allocate();
	F.set_domain(Q.size());
	Qmap_inverse.set_range(Q.size());
	follow.set_domain(Q.size());
	current.set_domain(Q.size());
	assert(class_invariant());
}

// Specially construct from an RFA(see Definition 4.28).
LBFA::LBFA(const RFA& r) :Q(r.Q), F(r.last), Qmap_inverse(r.Qmap_inverse), follow(r.follow)
{
	assert(r.class_invariant());
	// The new start state:
	s = Q.allocate();
	F.set_domain(Q.size());
	Qmap_inverse.set_range(Q.size());
	follow.set_domain(Q.size());
	current.set_domain(Q.size());

	// ...which is final if the RFA is nullable.
	if (r.Nullable) {
		F.add(s);
	}
	StateSet fst(r.first);
	fst.set_domain(Q.size());
	follow.union_cross(s, fst);
	//////////////////////////////////////////////////////////////////
	assert(r.class_invariant());  // Why use r.class_invariant()
}

// Standard FAabs operators. Don't override acceptable():
int LBFA::num_states() const
{
	assert(class_invariant());
	return(Q.size());
}

void LBFA::restart()
{
	assert(class_invariant());
	current.clear();
	current.add(s);
	assert(class_invariant());
}

void LBFA::advance(char a)
{
	assert(class_invariant());
	// There are two possible ways to implement this. It's not clear which is
	// more efficient.
	// current = Qmap_inverse[a].intersection(follow.imager current));
	current = follow.image(current).intersection(Qmap_inverse[a]);

	assert(class_invariant());
}

int LBFA::in_final() const
{
	return (current.not_disjoint(F));
}

int LBFA::stuck()
{
	return (current.empty());
}

DFA LBFA::determinism() const
{
	// Make sure that *this is structurally sound.
	assert(class_invariant());

	// Need s as a singleton StateSet.
	StateSet S;
	S.set_domain(Q.size());
	S.add(s);
	// Now construct the DFA components.
	return(construct_components(DSLBFA(S, &Qmap_inverse, &follow, &F)));
}

// Implement homomorphism decode(Definition 4.28).
LBFA& LBFA::decode(const RFA& r)
{
	// Implement Definition 4.28 of the Taxonomy.
	assert(r.class_invariant());
	Q = r.Q;
	F = r.last;
	Qmap_inverse = r.Qmap_inverse;
	follow = r.follow;

	// The new start state:
	s = Q.allocate();
	F.set_domain(Q.size());
	Qmap_inverse.set_range(Q.size());
	follow.set_domain(Q.size());
	current.set_domain(Q.size());
	// ...which is final if the RFA is nullable.
	if (r.Nullable) {
		F.add(s);
	}
	StateSet fst(r.first);
	fst.set_domain(Q.size());
	follow.union_cross(s, fst);

	assert(class_invariant());
	return(*this);
}

// Implement non-homomorphic RFA->LBFA mapping convert(Defn. 4.35).
LBFA& LBFA::convert(const RFA& r)
{
	// Implement Definition 4.35 of the Taxonomy.
	assert(r.class_invariant());
	Q = r.Q;
	// r.first must be a singleton set for this to work properly!
	// (See Property 4.37)
	assert(r.first.size() == 1);
	s = r.first.smallest();

	F = r.last;
	Qmap_inverse = r.Qmap_inverse;
	follow = r.follow;
	
	current = r.current;

	assert(class_invariant());
	return(*this);
}
