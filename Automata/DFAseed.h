/************************************************************************
Abstract states and the subset construction

An abstract state is a certain type of object used in the construction of a DFA. They are essentially
states in the subset construction (see [Wat93a, p. 12-13]) with some extra information.
The template function construct_components uses the extra information to construct a DFA. All
abstract states in FIRE engine are implemented using classes with names beginning with DS,
such as DSDFARev. An abstract state must have the following member functions:
	• an argumentless constructor, a copy constructor, an assignment operator, and equality and
	inequality operators;

	• final -- returns 1 if the abstract state is an accepting (final) state, 0 otherwise;

	• out_labels -- returns a CRSet representing the set of labels of out-transitions from the abstract
	state; and

	• out_transition -- takes a CharRange (which is an element ofthe CRSet returned by out_labels),
	and returns the abstract state resulting from a transition on the CharRange.
=======================================================================================
Implementation function: construct_components

Files: DFAseed.h

Uses: CharRange, CRSet, DFA_components, State, StateTo

Description: Template function construct_components implements the subset construction, with
useless state removal [Wat93a, p. 12-13]. It takes an "abstract state" and constructs the
components of a DFA (using the abstract state argument as the start state), returning them
in a DFA_components structure. It does this by encoding the abstract states as States,
using a 【breadth-first traversal】 of the start-reachable abstract states. During the traversal,
the deterministic transition relation (a DTransRel) is also constructed. As a result of using
a traversal starting at the start state, only reachable States and the reachable part of the
deterministic transition relation are constructed.

Implementation: This template function should really appear as a template constructor of class
DFA. It is implemented separately, as template member functions have only recently been
incorporated into the draft of the C++ language standard. The function implements the
subset construction (see [Wat93a, pp. 12, 13]). Each abstract state is assigned a State,
using a StateTo to keep track of the names assigned. The out-transitions from each State
are constructed, using the StateTo to lookup the encoding of an abstract state. The abstract
state classes are to be written in such a way that there are only finitely many of them,
thereby ensuring termination of the function. The useless state removal is hidden in the fact
that, by starting with the start state, only reachable States are constructed.
 ************************************************************************/
//#pragma once



#ifndef AUTOMATA_DFASEED_H
#define AUTOMATA_DFASEED_H



#include<iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "State.h"
#include "StateTo.h"
#include "CharRange.h"
#include "CRSet.h"
#include "DFA_components.h"

// A template function, representing an abstract DFA, used in the construction
// of real DFA's.
// It is assumed that class T is a DS??? class (constrained genericity).
// See DSfa.h or DSdfarev.h for examples of a DS??? class.

// Takes a T(an abstract start State), and constructs a DFA.
template<class T>
DFA_components construct_components(const T& abs_start)
{
	DFA_components ret;

	// Map each of the State's to a unique T, and vice-versa.
	StateTo<T> names;

	// Allocate a name for the new start State, and insert it into the namer.
	State s(ret.Q.allocate());

	names.set_domain(ret.Q.size());
	names.map(s) = abs_start;   // map: s --> abs_start
	ret.T.set_domain(ret.Q.size());
	ret.F.set_domain(ret.Q.size());

	// As invariant:
	//    ret.T.domain() == ret.Q.size() && ret.F.domain() == ret.Q.size()
	//    and all States < current are already done.

	State current;
	// Now construct the transitions, and finalness of each of the States.
	//    ret.Q grows as we go.
	for (current = 0; current < ret.Q.size(); current++)
	{
		// If the abstract state associated with current says it's final, then
		// current is too.
		if (names.lookup(current).final()) ret.F.add(current);

		// Now go through all of the out-transitions of the abstract
		// state associated with current(ie.names.lookup(current)).
		CRSet a(names.lookup(current).out_labels());

		CharRange b;
		int it;
		for (it = 0; !a.iter_end(it); it++)
		{
			b = a.iterator(it);

			// Do something with the destination of the transition.
			T dest(names.lookup(current).out_transition(b));

			// See if dest already has a name(by linear search).
			State i;
			for (i = 0; i < ret.Q.size() && (names.lookup(i) != dest); i++)
			{
			}

			// The abstract state may not have a name yet, so we may need
			// to allocate one.
			if (i == ret.Q.size())
			{
				// Associate i with dest.
				// And maintain the invariant.
				State j(ret.Q.allocate());
				assert(i == j);
				names.set_domain(ret.Q.size());
				ret.T.set_domain(ret.Q.size());
				ret.F.set_domain(ret.Q.size());
				names.map(i) = dest;
			}

			// Now i is the name of dest.
			assert(dest == names.lookup(i));
			// Create the actual transition.
			ret.T.add_transition(current, b, i);
		}
		// That's all for current.
	}

	// Time to resynchronize the domain() of ret.S with ret.Q.size() :
	ret.S.set_domain(ret.Q.size());
	// Add the start State now.
	ret.S.add(s);
	// Return, constructing the DFA on the way out.
	return(ret);
}



#endif // !AUTOMATA_DFASEED_H


