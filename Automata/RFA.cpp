/************************************************************************************
Implementation: Most of the member functions are implemented in a straight-forward manner.
In implementing RFA, a choice must be made between the two interpretations of States:
the left-biased or the right-biased interpretation (see the bottom of p.73 in [Wat93a] for
a brief explanation of the different interpretations). 
The interpretation chosen here is the right-biased one, since it appears to be the most efficient one in practice.
 ************************************************************************************/
#include "stdafx.h"
#include "RFA.h"
#include "DSRFA.h"
#include "DSRFA2.h"
#include "DFAseed.h"


 // Construct an RFA accepting nothing
RFA::RFA() :Nullable(0)
{
	assert(class_invariant());
}

// Provide a copy constructor:
RFA::RFA(const RFA& r) :Q(r.Q),first(r.first),last(r.last),Qmap_inverse(r.Qmap_inverse),
follow(r.follow),Nullable(r.Nullable),final(r.final),current(r.current)
{
	assert(class_invariant());
}

// The Sigma-homomorphism constructor (see Definition 4.30):
RFA::RFA(const RE& e)
{
	assert(e.class_invariant());
	
	int size(e.num_symbols());
	first.set_domain(size);
	last.set_domain(size);
	Qmap_inverse.set_range(size);
	follow.set_domain(size);

	// Now compute all of the components into place in *this.
	rfa_into(e, Q, first, last, Qmap_inverse, follow, Nullable);
	current.set_domain(size);

	assert(class_invariant());
}

// Default operator= is okay.

///////////////////////////////////////////////////////////////
// Basic FAabs member functions (without overriding acceptable()):

// Return the number of stales(or some reasonably close measure).
int RFA::num_states() const
{
	return(Q.size());
}

// Reset the current state before beginning to process a string.
// The following functions make use of the RBFA interpretation of states
// (Section 4.3 of the Taxonomy).
void RFA::restart()
{
	assert(class_invariant());
	// Ready to see any char corresponding to a first.
	current = first;
	// Only acceptable if *this accepts epsilon {ie. Nullable is true}.
	final = Nullable;
	assert(class_invariant());
}

// Advance the current state by processing a character.
void RFA::advance(char a)
{
	assert(class_invariant());

	// Figure out which are valid out-transitions.
	current.intersection(Qmap_inverse[a]);

	// current is the set of States we can really be in to see a.
	// We're accepting if at least one of the current States is also a last.
	final = current.not_disjoint(last);
	current = follow.image(current);
	assert(class_invariant());
}

// Is the current state an accepting(final) one?
int RFA::in_final() const
{
	assert(class_invariant());
	return(final);
}

// Is the automaton stuck?
int RFA::stuck()
{
	assert(class_invariant());
	return(current.empty());
}
// Return a DFA accepting the same language as *this.
DFA RFA::determinism() const
{
	// Make sure that *this is structurally sound.
	assert(class_invariant());
	// Now construct the DFA components
	return(construct_components(DSRFA(first, &Qmap_inverse, &follow, &first,&last,Nullable)));
}

DFA RFA::determinism2() const
{
	// Make sure that *this is structurally sound.
	assert(class_invariant());
	// Now construct, using the right - biased interpretation.
	return(construct_components(DSRFA2(&Qmap_inverse, &follow, &first, &last, Nullable)));
}
///////////////////////////////////////////////////////

// Implement a top down version of Sigma homomorphism rfa(Definition 4.30)
void RFA::rfa_into(const RE& e,
	StatePool& Qp,
	StateSet& f,
	StateSet& l,
	Trans& Qm,
	StateRel& foll,
	int& N)
{
	assert(class_invariant());

	switch (e.root_operator()) 
	{
	case EPSILON:
		// Nothing to do, but make it nullable.
		N = 1;
		return;
	case EMPTY:
		N = 0;
		return;
	case SYMBOL:
		// There is a symbol here, so give it a State.
	{
		State q(Qp.allocate());
		f.add(q);
		l.add(q);
		Qm.add_transition(e.symbol(), q);
		// Nothing to do to follow.
		N = 0;
	}
	return;
	case OR:
	case CONCAT:
	// Lots of common code, so do the two together.
	{
		// Compute the rfa of e.left_subexpr() into *this.
		rfa_into(e.left_subexpr(), Qp, f, l, Qm, foll, N);
		
		// Use some locals to store the pieces of the RFA of
		// the right subexpression.
		StateSet fr;
		fr.set_domain(f.domain());
		StateSet lr;
		lr.set_domain(l.domain());
		Trans Qmr;
		Qmr.set_range(Qm.range());
		StateRel follr;
		follr.set_domain(foll.domain());
		int Nr;

		// Now compute the RFA components corresponding to the right subexpr.
		//         Note: states are still taken from Qp.
		rfa_into(e.right_subexpr(), Qp, fr, lr, Qmr, follr, Nr);

		Qm.set_union(Qmr);
		if (e.root_operator() == OR) {
			f.set_union(fr);
			l.set_union(lr);
			foll.set_union(follr);
			N = N || Nr;
		}
		else {
			// This is a CONCAT.
			assert(e.root_operator() == CONCAT);
			foll.set_union(follr);
			foll.union_cross(l, fr);
			if (N) {
				f.set_union(fr);
			}
			if (Nr) {
				l.set_union(lr);
			}
			else {
				l = lr;
			}
			N = N && Nr;
		}
	}
	return;
	case STAR:
	case PLUS:
		// First, do the subexpression.
		rfa_into(e.left_subexpr(), Qp, f, l, Qm, foll, N);
		foll.union_cross(l, f);
		if (e.root_operator() == STAR) {
			N = 1;
		}
		else {
			assert(e.root_operator() == PLUS);
		}
		return;
	case QUESTION:
		rfa_into(e.left_subexpr(), Qp, f, l, Qm, foll, N);
		N = 1;
		return;
	}
}

// recycle this RFA:
void RFA::reincarnate()
{
	Q.reincarnate();
	first.reincarnate();
	last.reincarnate();
	Qmap_inverse.reincarnate();
	follow.reincarnate();
	Nullable = final = 0;
	current.reincarnate();
}

