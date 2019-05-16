/****************************************************************************************//*

Uses: CharRange, DFA, State, StateEqRel, StateSet
Description: Member function split takes two States (p and q), a CharRange a, and a StateEgRel.
	The two States are assumed to be representatives in the StateEqRel. The equivalence class of
	p is then split into those States (equivalent to p) which transition on a to a State equivalent
	to q, and those that do not. If in fact there was a split (the equivalence class of p is split
	into two equivalence classes), p will still be the unique representative of one of the two new
	equivalence classes; in this case, the (unique) representative of the other equivalence class is
	returned. If no such split occurred, function split returns Invalid.
Implementation: The implementation is a simple, iterative one. It implement the equivalent
	of the assignment to Q'0 in Algorithm 4.4 of [Wat93b].

*//****************************************************************************************/
/*(c) Copyright 1994 by Bruce W. Watson */
// $Revision 1.1 $
// $Date: 1994/05/02 15:59:06 $

#include "CharRange.h"
#include "State.h"
#include "StateSet.h"
#include "StateEqRel.h"
#include "DFA.h"

// Attempt to split the eq. class [p] w.r.t.([q],a) in P
// P中的[p] is splitted into two parts: [p1] and [p2]. T([p1],a)属于[q], T([p2],a)不属于[q]. 
// 如果p是[p1]的代表元，返回[p2]的代表元，如果p是[p2]的代表元，返回[p1]的代表元
// 如果不能分离([p1] or [p2] is empty set)，返回Invalid.
State DFA::split(const State p, const State q, const CharRange a, StateEqRel & P) const
{
	assert(class_invariant());
	assert(P.class_invariant());

	// p and q must be representative of their eq. classes.
	assert(p == P.eq_class_representative(p));
	assert(q == P.eq_class_representative(q));

	//Split [p] with respect to ([q],CharRange a) into two parts: [p1] and [p2]
	StateSet part; // [p1]
	part.set_domain(Q.size());


	// Iterate over [p],and see whether each member transitions into [q]
	// on CharRange a;
	State st;
	for (P.equiv_class(p).iter_start(st); !P.equiv_class(p).iter_end(st); P.equiv_class(p).iter_next(st))
	{
		State dest(T.transition_on_range(st, a)); // dest=T(st,a) ===> dest=T([p],a)
		// It could be that dest == Invalid.
		//           if not, check if dest in [q].
		if (dest != Invalid && P.equivalent(dest, q)) // part = U{T([p],a)| T([p],a) 属于[q]}
		{
			part.add(st);
		}

	}

	// The following containment must hold after the splitting.
	assert(P.equiv_class(p).contains(part));

	// Return non-zero if something was split. 
	// [p] is splitted into [p1] and [p2]
	if ((part != P.equiv_class(p)) && !part.empty())
	{
		// Now figure out what the other piece is.
		StateSet otherpiece(P.equiv_class(p));  // [p2]
		otherpiece.remove(part);
		assert(!otherpiece.empty());

		P.split(part); 
		assert(class_invariant());

		// Now, we must return the representative of the newly created
		// equivalence class.
		State x(P.eq_class_representative(otherpiece.smallest()));  // [p2]
		assert(x != Invalid);
		// It could be that p is not in part.
		State y(P.eq_class_representative(part.smallest()));  // [p1]
		assert(y != Invalid);
		assert(x != y);

		if (p == x)  // p是[p2]的代表元,返回[p1]的代表元
		{
			// If p is the representative of 'otherpiece', then
			// return the representative of 'part'.
			assert(otherpiece.contains(p));
			return (y);  // [p1]
		}
		else  // p是[p2]的代表元,返回[p2]的代表元
		{
			// If p is the representative of 'part', then
			// return the representative of 'otherpiece'.
			assert(part.contains(p));
			return (x); // [p1]
		}

	}
	else
	{
		assert((part == P.equiv_class(p)) || (part.empty()));
		// No splitting to be done.
		return (Invalid);
	}

}