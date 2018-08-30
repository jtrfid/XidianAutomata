/************************************************************************
Implementation: All of the member functions are straight-forward implementations, with the
exception of the minimization and reversal member functions. Those are further described
later (the minimization member functions are discussed in Part IV). The constructor which
takes a DFA_components object is only provided because most C++ compilers do not support
template member functions yet. When these are fully supported, template function
construcLcomponents will be inlined in the constructor.

Performance: Use-counting the classes used in the automata (such as DTransRel and StateSet)
would improve performance on copy construction and assignment.
 ************************************************************************/
#include "stdafx.h"
#include "DFA.h"

// Member functions required by class FAabs :
int DFA::num_states() const
{
	assert(class_invariant());
	return(Q.size());
}

void DFA::restart()
{
	assert(class_invariant());
	// There really should be only one state in S.
	// this is ensured by the class invariant.
	current = S.smallest();
}

void DFA::advance(char a)
{
	assert(class_invariant());
	assert(a != Invalid);
	current = T.image(current, a);
}
int DFA::in_final() const
{
	assert(class_invariant());
	return(F.contains(current));
}

int DFA::stuck()
{
	assert(class_invariant());
	return(current == Invalid);
}
DFA DFA::determinism() const
{
	assert(class_invariant());
	// Keep it really simple!
	return(*this);
}

// A function to reverse *this.
DFA& DFA::reverse()
{
	// Make sure that *this is structurally sound.
	assert(class_invariant());
	// Now construct the DFA components from an abstract DFA state.
	reconstruct(construct_components(DSDFARev(F, &T, &S)));
	return(*this);
}

// Some minimization algorithms:
DFA& DFA::min_HopcroftUllman()
{

}
DFA& DFA::min_dragon()
{

}
DFA& DFA::min_Hopcroft()
{

}
DFA& DFA::min_Watson()
{

}

// Some member functions relating to useful State's.

// Can all States reach a final State ?
int DFA::usefulf() const
{

}

// Remove any States that cannot reach a final State.
DFA& DFA::usefulf()
{

}

// Given a minimizing equivalence relation, shrink the DFA.
DFA& DFA::compress(const StateEqRel& r)
{
	assert(class_invariant());
	// All of the components will be constructed into this structure:
	DFA_components ret;

	// Give each eq. class of r a State name:
	// newnames maps States to their new names after compression.
	StateTo<State> newnames;
	newnames.set_domain(Q.size());
	for (State st = 0; st < Q.size(); st++)
	{
		// If st is the representative of its class allocate a new name.
		State strep(r.eq_class_representative(st));
		if (st == strep) newnames.map(st) = ret.Q.allocate();
		else newnames.map(st) = newnames.lookup(strep);
	}
	// Construct the new transition relation.
	ret.T.set_domain(ret.Q.sizeO);
	ret.F.seLdomain(ret.Q.sizeO);
	
	CRSet a;
	for (State st = 0; st < Q.size; st++)
	{
		// If st is the representative, construct the transition.
		if (st == r.eq_class_representative(st))
		{
			State stprime(newnames.lookup(st));
			// What are st's out-transitions?
			CharRange b;
			a = T.out_labels(st);
			// The out-labels of any other element of [st]_r could have
			// been used instead. Some other choice may, indeed, lead
			// to a smaller DFA.This approach is used for simplicity.
			int it;
			// Iterate over the labels, constructing the transitions.
			for (it = 0; !a.iter_end(it); it++)
			{
				b = a.iterator(it);
				ret.T.add_transition(stprime, b, newnames.lookup(T.transition_on_range(st, b)));
			}
			// st's eq. class may be final.
			if (F.contains(st)) ret.F.add(stprime);
		}
	}

	// Set up the new start state.
	ret.set_domain(ret.Q.size());
	ret.S.add(newnames.lookup(S.smallest()));

	reconstruct(ret);
	assert(class_invariant());
	return(*this);
}

DFA& DFA::compress(const SymRel& r)
{

}

// Attempt to split the eq.class [p]_P w.r.t.[q]_P
// (Return 1 if it was split, 0 otherwise.)
State DFA::split(const State p, const State q, const CharRange a, StateEqRel& P) const
{

}

// A helper for min_ Watson.
int DFA::are_eq(State p, State q, SymRel& S, const StateEqRel& H, const SymRel& Z) const
{

}

std::ostream& operator<<(std::ostream& os, const DFA& r)
{

}
