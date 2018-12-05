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

// The Sigma-homomorphism constructor (see Definition 4.30): RE -- >RFA
RFA::RFA(const RE& e)
{
	assert(e.class_invariant());
	
	// The number of states in M equals the number of(not necessarily distinct) symbols(of V) occuring in E. P34
	int size(e.num_symbols()); // How many SYMBOL nodes in this regular expression?
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

// Implement a top down version of Sigma homomorphism rfa(Definition 4.30): RE --> RFA
// Definition 4.29 (Sigma-algebra of RFA's): p33-35
// N: Nullable, {true,flase} ==> {1,0}
// Qm: V --> P(Q)
void RFA::rfa_into(const RE& e,
	StatePool& Qp,
	StateSet& f,
	StateSet& l,
	Trans& Qm,
	StateRel& foll,
	int& N)
{
	assert(e.class_invariant());

	switch (e.root_operator()) 
	{
	case EPSILON:
		// Nothing to do, but make it nullable.
		N = 1;  // Nullable = true
		return;
	case EMPTY:
		N = 0; // Nullable = false
		return;
	case SYMBOL:
		// There is a symbol here, so give it a State.
	{
		State q(Qp.allocate()); // q be a new state
		f.add(q); // first=last={q}
		l.add(q);
		Qm.add_transition(e.symbol(), q);
		// Nothing to do to follow.
		N = 0; // Nullable = false
	}
	return;
	case OR:
	case CONCAT:
	// Lots of common code, so do the two together.
	{
		// Compute the rfa of e.left_subexpr() into *this.
		rfa_into(e.left_subexpr(), Qp, f, l, Qm, foll, N);  // M0
		
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
		rfa_into(e.right_subexpr(), Qp, fr, lr, Qmr, follr, Nr); // M1

		Qm.set_union(Qmr); // Q = Q0 ∪ Q1
		if (e.root_operator() == OR) {   
			f.set_union(fr); // first = first0 ∪ first1;
			l.set_union(lr); // last = last0 ∪ last1;
			foll.set_union(follr); // follow = follow0 ∪ follow1;
			N = N || Nr; // null = null0 ∨ null1
		}
		else {
			// This is a CONCAT.
			assert(e.root_operator() == CONCAT);
			foll.set_union(follr); // follow = follow0 ∪ follow1 ∪ (last0 × first1);
			foll.union_cross(l, fr);
			if (N) { 
				f.set_union(fr); // first = first0 ∪ if(null0) first1;
			}  // 不用考虑else吗？
			if (Nr) {
				l.set_union(lr); // last = last1 ∪ if(null1) last0;
			}
			else { // if null1 = flase, last = last1
				l = lr; // last = last1
			}
			N = N && Nr; // null = null0 ∧ null1
		}
	}
	return;
	case STAR:
	case PLUS:
		// First, do the subexpression.
		rfa_into(e.left_subexpr(), Qp, f, l, Qm, foll, N); // M
		foll.union_cross(l, f); // follow = last × first
		if (e.root_operator() == STAR) {
			N = 1; // null = true
		}
		else { // plus: null值取决于M的null
			assert(e.root_operator() == PLUS);
		}
		return;
	case QUESTION:
		rfa_into(e.left_subexpr(), Qp, f, l, Qm, foll, N); // M
		N = 1;  // null = true
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

