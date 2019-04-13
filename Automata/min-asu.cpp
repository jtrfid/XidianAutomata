/****************************************************************************************//*

Uses: CRSet, DFA, State, StateEqRel, StateSet
Description: Member function min_dragon is an implementation of Algorithm 4.6 in [Wat93b].
	It is named the "dragon" function after Aho, Sethi, and Ullman's "dragon book" [ASU86]
Implementation: The algorithm begins with the approximation E_0 to the State equivalence
	relation E. It then repreatedly partition the equivalence classes until the greatest fixed
	point (E) is reached.

*//****************************************************************************************/



/*(c) Copyright 1994 by Bruce W. Watson */
// $Revision 1.1 $
// $Date: 1994/05/02 15:59:06 $

#include "CRSet.h"
#include "State.h"
#include "StateSet.h"
#include "StateEqRel.h"
#include "DFA.h"

// Implement Algorithm 4.6  of the taxonomy.

DFA& DFA::min_dragon()
{
	assert(class_invariant());
	assert(Usefulf());

	// We'll need the combination of all of the out-transition of all of the
	// States, when splitting equivalence classes.
	CRSet C;
	State st;
	for (st = 0; st < Q.size(); st++)
	{
		C.combine(T.out_labels(st));
	}

	// P is the equivalence approximation to E. It is initialized
	// to the total relation with domain Q.size().
	StateEqRel P(Q.size());
	// We now initialize it to E_0
	P.split(F);

	// reps is the set of representatives of P.
	StateSet reps(P.representatives());

	// [st] is going to e split w.r.t. something.

	// The following is slighting convoluted.
	reps.iter_start(st);
	while (!reps.iter_end(st))
	{
		// Try to split [st] w.r.t. every class[q].
		State q;

		// Keep track of whether something was indeed split.
		//        Having to use this variable could be avoided with a goto
		int something_split(0);

		// Iterate over all q, and try to split [st] w.r.t. all other
		// equivalence classes [q].
		// Stop as early as possible.
		for (reps.iter_start(q); !reps.iter_end(q) && !something_split ; reps.iter_next(q))
		{
			// Iterate over the possible transition labels, and
			// do a split if possible.
			int i;
			for (i = 0; !C.iter_end(i) && !something_split; i++)
			{
				something_split = (split(st, q, C.iterator(i), P) != Invalid);
			}
		}

		// If something was split, restart the outer repetition.
		if (something_split)
		{
			// The set of representative will have changed due to
			// the split.
			reps = P.representatives();
			reps.iter_start(st);
			// Now continue the outer repetition with restarted
			// representatives.
		}
		else
		{
			// Just go on as usual.
			reps.iter_next(st);
		}
	}

	compress(P);
	assert (class_invariant());
	return (*this);
}