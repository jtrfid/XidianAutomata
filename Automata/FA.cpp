/***********************************************************************************
Implementation: Most of the member functions are implemented in a straight-forward manner.
The constructor from an RE makes a traversal of the RE to determine the number of States
to allocate before-hand.

Performance: Since Thompson's construction yields finite automata with certain structural
properties (see [Wat93a, end of Definition 4.1]), a special "Thompson's construction" automata
class could be efficiently implemented, instead of the general finite automaton structure
defined in FA.
 ***********************************************************************************/
#include "stdafx.h"
#include "FA.h"
#include "DFAseed.h"
#include "DSFA.h"
#include "DFA.h"


// Construct an FA accepting nothing
FA::FA() :Q()
{
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
}

// Provide a copy constructor:
FA::FA(const FA& r) :Q(r.Q), S(r.S), F(r.F),
					Transitions(r.Transitions), E(r.E), current(r.current)
{
	assert(class_invariant());
}

// A special constructor, implementing the Thompson's top-down construction
// (see Construction 4.5).
FA::FA(const RE& e)
{
	// First, allocate enough states by setting up the domains.
	// See Section 4.1.1 of the Taxonomy.
	int states_required(states_reqd(e));
	S.set_domain(states_required);
	F.set_domain(states_required);
	Transitions.set_domain(states_required);
	E.set_domain(states_required);
	current.set_domain(states_required);
	
	State s(Q.allocate());
	State f(Q.allocate());
	S.add(s);
	F.add(f);
	td(s, e, f);
	assert(class_invariant());
}

// Default operator= is okay.

///////////////////////////////////////////////////////////////
// Basic FAabs member functions (without overriding acceptable()):

// Return the number of stales(or some reasonably close measure).
int FA::num_states() const
{
	return(Q.size());
}

// Reset the current state (to start stsates) before beginning to process a string.
// This is not the default condition for most of the derived classes.
void FA::restart()
{
	assert(class_invariant());
	current = E.closure(S);
	assert(class_invariant());
}

// Advance the current state by processing a character.
// advance the automaton by one char in the input string
void FA::advance(char a)
{
	assert(class_invariant());
	// Computer the epsilon-closure.
	current = E.closure(Transitions.image(current, a));
	assert(current == E.closure(current));
	assert(class_invariant());
}

// Is the current state an accepting(final) one?
int FA::in_final() const
{
	assert(class_invariant());
	return(current.not_disjoint(F));
}

// Is the automaton stuck(unable to make further transitions)?
int FA::stuck()
{
	assert(class_invariant());
	return(current.empty());
}
// Return a DFA accepting the same language as *this.
DFA FA::determinism() const
{
	// Make sure that *this is structurally sound.
	assert(class_invariant());
	// Now construct the DFA components
	return(DFA(construct_components(DSFA(S, &Transitions, &E, &F))));
}
///////////////////////////////////////////////////////

// Functions states_reqd, td(see Construction 4.5) for use in the constructor from RE.
// The following follows directly from inspecting Thompson's construction (Definition 4.1).

// compute states_required in fa from RE
int FA::states_reqd(const RE& e)
{
	assert(e.class_invariant());
	int ret;
	switch (e.root_operator()) {
	case EPSILON: // new states: q0,q1
	case EMPTY:   
	case SYMBOL:  
		ret = 2;  
		break;
	case OR: // (new states: q0,q1) + left_subexpr and right_subxpr
		ret = 2 + states_reqd(e.left_subexpr()) + states_reqd(e.right_subexpr());
		break;
	case CONCAT: // left_subexpr and right_subxpr
		ret = states_reqd(e.left_subexpr()) + states_reqd(e.right_subexpr());
		break;
	case STAR:      // (new states: q0,q1) + left_subexpr
	case PLUS:
	case QUESTION:
		ret = 2 + states_reqd(e.left_subexpr());
		break;
	}
	return(ret);
}

// Thompson's top-down construction [Wat93a, Construction 4.5]
void FA::td(const State s, const RE& e, const State f)
{
	assert(e.class_invariant());
	// Implement function td(of Construction 4.5).
	// Construct an FA to accept the language of e, between s and f.
	// FA = (Q,V,T,E,S,T), td = Q x RE x Q ---> FA
	switch (e.root_operator())
	{
	case EPSILON:  // td(s,epsilon,f) = {{s,f},V,empty,{(s,f)}},{s},{f}}
		E.union_cross(s, f);
		break;
	case EMPTY: // td(s,empty,f) = {{s,f},V,empty,empty,{s},{f}}
		break;
	case SYMBOL: // td(s,a,f) = {{s,f},V,{(s,a,f)},empty,{s},{f}} (for all a in V)
		Transitions.add_transition(s, e.symbol(), f);
		break;
	case OR:  // td(s,E0 union E1,f)
	{
		State p(Q.allocate());
		State q(Q.allocate());
		td(p, e.left_subexpr(), q);
		State r(Q.allocate());
		State t(Q.allocate());
		td(r, e.right_subexpr(), t);

		E.union_cross(s, p);
		E.union_cross(s, r);

		E.union_cross(q, f);
		E.union_cross(t, f);
	}
	break;
	case CONCAT: // td(s,E0 concat E1,f)
	{
		State p(Q.allocate());
		State q(Q.allocate());
		td(s, e.left_subexpr(), p);
		td(q, e.right_subexpr(), f);

		E.union_cross(p, q);
	}
	break;
	case STAR: // td(s,star,f)
	{
		State p(Q.allocate());
		State q(Q.allocate());
		td(p, e.left_subexpr(), q);

		E.union_cross(s, p);
		E.union_cross(q, p);
		E.union_cross(q, f);
		E.union_cross(s, f);
	}
	break;
	case PLUS: // td(s,plus,f)
	{
		State p(Q.allocate());
		State q(Q.allocate());
		td(p, e.left_subexpr(), q);
		E.union_cross(s, p);
		E.union_cross(q, p);
		E.union_cross(q, f);
	}
	break;
	case QUESTION: // td(s,question,f)
	{
		State p(Q.allocate());
		State q(Q.allocate());
		td(p, e.left_subexpr(), q);

		E.union_cross(s, p);
		E.union_cross(q, f);
		E.union_cross(s, f);
	}
	break;
	}
}

// recycle this FA:
void FA::reincarnate()
{
	Q.reincarnate();
	S.reincarnate();
	F.reincarnate();
	Transitions.reincarnate();
	E.reincarnate();
	current.reincarnate();
}

