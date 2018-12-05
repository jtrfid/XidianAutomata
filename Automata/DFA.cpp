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

// Some member functions relating to useful State's.

// Can all States reach a final State?
// Implement Definition 2.23
int DFA::Usefulf() const
{
	assert(class_invariant());
	StateSet r(T.reverse_closure(F));
	return(r.complement().empty());
}

// Remove any States that cannot reach a final State.
// (This is a last step in minimization, since some of the min. algorithms may yield 
// a DFA with a sink state.)
// Implement Remark 2.39  removing states that are not final - reachable.
DFA& DFA::usefulf()
{
	assert(class_invariant());
	StateSet freachable(T.reverse_closure(F));
	StateTo<State> newnames;
	newnames.set_domain(Q.size());
	
	// All components will be constructed into a special structure :
	DFA_components ret;
	State st;
	for (st = 0; st < Q.size(); st++)
	{
		// If this is a Usefulf State, carry it over by giving it a name
		// in the new DFA.
		if (freachable.contains(st)) newnames.map(st) = ret.Q.allocate();
	}

	// It is possible that nothing needs to be done(ie.the all States were
	// already F useful).
	if (Q.size() != ret.Q.size())
	{
		ret.T.set_domain(ret.Q.size());
		ret.F.set_domain(ret.Q.size());

		CRSet a;
		for (st = 0; st < Q.size(); st++)
		{
			// Only construct the transitions if st is final reachable.
			if (freachable.contains(st))
			{
				a = T.out_labels(st);
				State stprime(newnames.lookup(st));

				CharRange b;
				int it;
				// Construct the transitions.
				for (it = 0; !a.iter_end(it); it++)
				{
					b = a.iterator(it);
					ret.T.add_transition(stprime, b, newnames.lookup(T.transition_on_range(st, b)));
				}
				// This may be a final State.
				if (F.contains(st)) ret.F.add(stprime);
			}
		}
		ret.S.set_domain(ret.Q.size());

		// Add a start State only if the original one was final reachable.
		if (S.not_disjoint(freachable)) ret.S.add(newnames.lookup(S.smallest()));
		reconstruct(ret);
	}
	assert(class_invariant());
	return(*this);
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
	ret.T.set_domain(ret.Q.size());
	ret.F.set_domain(ret.Q.size());
	
	CRSet a;
	for (State st = 0; st < Q.size(); st++)
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
	ret.S.set_domain(ret.Q.size());
	ret.S.add(newnames.lookup(S.smallest()));

	reconstruct(ret);
	assert(class_invariant());
	return(*this);
}

DFA& DFA::compress(const SymRel& r)
{
	assert(class_invariant());

	// All of the components ret;
	DFA_components ret;

	// Give each eq. class of r a State name:
	// newnames maps States to their new names after compression.
	StateTo<State> newnames;
	newnames.set_domain(Q.size());

	StateSet consider;
	consider.set_domain(Q.size());
	consider.complement();

	// Bulid the set of representatives.
	StateSet repr;
	repr.set_domain(Q.size());

	State st;
	for (consider.iter_start(st); !consider.iter_end(st); consider.iter_next(st))
	{
		// st will always be the reprenstative of its class.
		repr.add(st);

		// give st the new name
		State n(ret.Q.allocate());
		newnames.map(st) = n;

		// Go over [st], and give them all the new name.
		State z;
		for (r.image(st).iter_start(z); !r.image(st).iter_end(z);r.image(st).iter_next(z))
		{
			newnames.map(z) = n;
		}

		// Now mark [st] as having been done already.
		consider.remove(r.image(st));
		// The outer iterator should still work okay.
	}

	// Construct the new transition relation.
	ret.T.set_domain(ret.Q.size());
	ret.F.set_domain(ret.Q.size());

	CRSet a;
	// Go over all of the representatives (eq. classes),constructing the transitions.
	for (repr.iter_start(st); !repr.iter_end(st); repr.iter_next(st))
	{
		State stprime(newnames.lookup(st));

		// What are st's out-transitions?
		CharRange b;

		a = T.out_labels(st);
		// The out_labels of any other element of [st]_r could have
		// been used instead. Some other choice may,indeed,lead to a
		// smaller DFA. This approach is used for simplicity.
		int it;
		// Iterate over the labels,constructiong the transitions.
		for (it = 0; !a.iter_end(it); it++)
		{
			b = a.iterator(it);
			ret.T.add_transition(stprime, b, newnames.lookup(T.transition_on_range(st, b)));
		}

		// st's eq. class may be final.
		if (F.contains(st)) ret.F.add(stprime);
	}

	// Set up the new start state;
	ret.S.set_domain(ret.Q.size());
	ret.S.add(newnames.lookup(S.smallest()));

	reconstruct(ret);
	assert(class_invariant());
	return(*this);
}

std::ostream& operator<<(std::ostream& os, const DFA& r)
{
	os << "\nDFA\n";
	os << "Q = " << r.Q << '\n';
    os <<  "S = " << r.S << '\n';
	os << "F = " << r.F << '\n';
	os << "Transitions = \n" << r.T << '\n';
	os << "current = " << r.current << '\n';
	return(os);
}

/*****************************************************************TODO:
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

// Attempt to split the eq.class [p]_P w.r.t.[q]_P
// (Return 1 if it was split, 0 otherwise.)
State DFA::split(const State p, const State q, const CharRange a, StateEqRel& P) const
{

}

// A helper for min_ Watson.
int DFA::are_eq(State p, State q, SymRel& S, const StateEqRel& H, const SymRel& Z) const
{

}
************************************************/