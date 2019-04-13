/****************************************************************************************//*

Uses: CRSet, DFA, State, StateSet, SymRel
Description: This member function provides a very convoluted implementation of Algorithm 4.7
	of [Wat93b]. It computes the distinguishability relation (relation D in [Wat93b]).
Implementation: The algorithm is not quite the same as that presented in [Wat93b, Algorithm
	4.7]. The menmber function computes the equivalence relation (on States) by first computing
	distinguihsability relation D. Initially, the pairs of distinguishable States are those pairs p,q
	where one is final State and the other is not. Pairs of States that reach p,q are then also
	distinguishable (according to the efficiency improvement property given in [Wat93b, Section
	4.7, p. 16]). Iteration terminates when all distinguishable States have been considered.
Performance: This algorithm can be expected to run quite slowly, since it makes use of reverse
	transition in the deterministic transition relation (DTransRel). The transition relations
	(TransRel and DTransRel) are optimized for forward transitions.

*//****************************************************************************************/
/*(c) Copyright 1994 by Bruce W. Watson */
// $Revision 1.1 $
// $Date: 1994/05/02 15:59:06 $

#include "CRSet.h"
#include "State.h"
#include "StateSet.h"
#include "SymRel.h"
#include "DFA.h"

// Implement (a version of) Algorithm 4.7 of the minimization Taxonomy.
DFA& DFA::min_HopcroftUllman()
{
	assert(class_invariant());
	assert(Usefulf());

	// We need the combination of all transition labels, to iterate over
	// transitions
	State st;
	CRSet C;
	for (st = 0; st < Q.size(); st++)
	{
		C.combine(T.out_labels(st));
	}

	// First, figure out which are non-final States.
	StateSet nonfinal(F);
	nonfinal.complement();

	// Use Z to keep track of the pairs that still need to be considered for distinguishedness.
	SymRel Z;
	Z.set_domain(Q.size());

	// We begin with those pairs that are definitely distinguished.
	//    this inculude pairs with different parity.
	Z.add_pairs(F, nonfinal);

	// It also includes pairs with differing out-transitions.
	//         iterate over C (the CRSet) and check the haves and have-nots
	StateSet have;
	have.set_domain(Q.size());
	StateSet havenot;
	havenot.set_domain(Q.size());

	int it;
	for (it = 0; !C.iter_end(it); it++)
	{
		//have and havenot must be empty for the update to be correct.
		assert(have.empty() && havenot.empty());
		State p;
		// Iterate ove the States and check which have a transition.
		for (p = 0; p < Q.size(); p++)
		{
			// Does p have the transition?
			if (T.transition_on_range(p, C.iterator(it)) != Invalid)
			{
				have.add(p);
			}
			else
			{
				havenot.add(p);
			}
		}
		// have and havenot are distinguished from one another.
		//          (under the assumption that Useful() holds)
		Z.add_pairs(have, havenot);

		have.clear();
		havenot.clear();
	}

	// G will be use to accumulate the (distinguishability) relation D.
	SymRel G;
	G.set_domain(Q.size());

	// Now consider all of the pairs untils nothing changes.
	while (1)
	{
		State p;

		// Go looking for the next pair to do.
		for (p = 0; p < Q.size() && Z.image(p).empty(); p++);

		// There may be nothing left to do.
		if (p == Q.size())
		{
			break;
		}
		else
		{
			assert(!Z.image(p).empty());
			// Choose q such {p,q} is in Z.
			//          We know that such a q exists.
			State q(Z.image(p).smallest());
			assert(q != Invalid);

			// Move {p,q} from Z across to G.
			Z.remove_pair(p, q);
			G.add_pair(p, q);

			// Now check out the reverse transitions from p and q.
			int i;
			// Iterate over all of labels.
			for (i = 0; !C.iter_end(i); i++)
			{
				StateSet pprime(T.reverse_transition(p, C.iterator(i)));
				StateSet qprime(T.reverse_transition(q, C.iterator(i)));
				// pprime and qprime are all distinguished.
				// Iterate over both sets and flag them as distinguished.
				State pp;
				for (pprime.iter_start(pp); !pprime.iter_end(pp); pprime.iter_next(pp))
				{
					State qp;
					for (qprime.iter_start(qp); !qprime.iter_end(qp); qprime.iter_next(qp))
					{
						// Mark pp, qp for processing if they
						// haven't already been done.
						if (!G.contains_pair(pp, qp))
						{
							Z.add_pair(pp, qp);
						} //if
					} //for
				} //for	
			} //for
		} //if
	} //while

	// Now compute E from D
	G.complement();
	// And use it to compress the DFA.
	compress(G);

	assert(class_invariant());
	return (*this);
}