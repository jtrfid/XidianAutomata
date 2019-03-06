/***********************************************************************************
Implementation: Class RBFA is a friend of class RFA. Most of the member functions are
implemented in a straight-forward manner.
***********************************************************************************/

#include "DSRBFA.h"
#include "DFAseed.h"
#include "RBFA.h"


// Default constructor must build the empty language acceptor.
RBFA::RBFA()
{
	// Give * this the properties required of Construction 4.43
	f = Q.allocate();
	S.set_domain(Q.size());
	Qmap_inverse.set_range(Q.size());
	follow.set_domain(Q.size());
	current.set_domain(Q.size());
	assert(class_invariant());
}

// Implement R; decode; R(Construction 4.45 of the Taxonomy):
RBFA::RBFA(const RFA& r) :Q(r.Q), S(r.first), Qmap_inverse(r.Qmap_inverse), follow(r.follow)
{
	assert(r.class_invariant());
	
	// Create the new final state.
	f = Q.allocate();
	S.set_domain(Q.size());
	Qmap_inverse.set_range(Q.size());
	follow.set_domain(Q.size());
	current.set_domain(Q.size());

	// ...which is final if the RFA is nullable.
	if (r.Nullable) {
		S.add(f);
	}
	StateSet la(r.last);
	la.set_domain(Q.size());
	follow.union_cross(la, f);
	assert(class_invariant()); 
}

// Standard FAabs operators. Don't override acceptable():
int RBFA::num_states() const
{
	assert(class_invariant());
	return(Q.size());
}

void RBFA::restart()
{
	assert(class_invariant());
	current = S;
	assert(class_invariant());
}

void RBFA::advance(char a)
{
	assert(class_invariant());
	// Compute which states we can even transition out of, then
	// transition out of them.
	// current = follow.image(current).intersection(Qmap_inverse[a]);  // in LBFA::advance()
	current = follow.image(current.intersection(Qmap_inverse[a]));
	assert(class_invariant());
}

int RBFA::in_final() const
{
	return (current.contains(f));
}

int RBFA::stuck()
{
	assert(class_invariant());
	return (current.empty());
}

DFA RBFA::determinism() const
{
	// Make sure that *this is structurally sound.
	assert(class_invariant());

	// Now construct the DFA components.
	return(construct_components(DSRBFA(S, &Qmap_inverse, &follow, f)));
}

// Implement homomorphism R; decode ;R(Construction 4.45):
RBFA& RBFA::decode(const RFA& r)
{
	// Implement R ; decode ; R of the Taxonomy (p.41).
	assert(r.class_invariant());
	Q = r.Q;
	S = r.first;
	Qmap_inverse = r.Qmap_inverse;
	follow = r.follow;

	// Allocate the new final state.
	f = Q.allocate();
	S.set_domain(Q.size());
	Qmap_inverse.set_range(Q.size());
	follow.set_domain(Q.size());

	current.set_domain(Q.size());
	current.clear();

	if (r.Nullable) {
		S.add(f);
	}
	StateSet la(r.last);
	la.set_domain(Q.size());
	follow.union_cross(la, f);

	assert(class_invariant());
	return(*this);
}

// Implement non-homomorphic RFA->RBFA mapping R ;conver; R (see
// page 43 of the Taxonomy):
RBFA& RBFA::convert(const RFA& r)
{
	// Implement R; convert; R of the Taxonomy (p. 43).
	assert(r.class_invariant());
	Q = r.Q;
	// r.last must be a singleton set for this to work properly!
	// (See Property 4.37)
	f = r.last.smallest();
	assert(r.last.size() == 1);

	S = r.last;
	Qmap_inverse = r.Qmap_inverse;
	follow = r.follow;

	current = r.current;

	assert(class_invariant());
	return(*this);
}