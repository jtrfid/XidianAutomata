/**************************************************************************

Description: Member function min_Watson implements the new minimization algorithm appearing 
    in [Wat93b, Sections 4.6-4.7]. The algorithm computes the equivalence relation E (on
	states) from below. The importance of this is explained in [Wat93b, P. 16]

Implementation: Function min_Waston is an implementation of Algorithm 4.10 (of [Wat93b]).
	The helper function are_eq is an implementation of the second algorithm appearing in Section
	4.6 of [Wat93b]. Function are_eq takes two parameters more than the version appearing in
	[Wat93b]: H (a StateEqRel) and Z (a SymRel). These parameters are used to discover
	equivalence (or distinguishability) of States earlier than the abstract algorithm would.

Performance: Memoizaton in function are_eq would provide a great speedup.

***************************************************************************/

/*(c) Copyright 1994 by Bruce W. Watson */
// $Revision 1.1 $
// $Date: 1994/05/02 15:59:06 $

#include "State.h"
#include "CRSet.h"
#include "SymRel.h"
#include "StateEqRel.h"
#include "DFA.h"
#include <assert.h>

// The following is function equiv from Section 4.6 of the min. taxonomy.
int DFA::are_eq(State p, State q, SymRel& S, const StateEqRel& H, const SymRel& Z) const
{
	if (S.contains_pair(p, q) || H.equivalent(p, q))
	{
		// P and q are definitely equivalent.
		return (1);
	}
	else if(!Z.contains_pair(p,q))
	{
		assert(!S.contains_pair(p, q));
		assert(!H.equivalent(p, q));
		// p and q are already compared (in the past) and found to be
		// inequivalent.
		return (0);
	}
	else
	{
		assert(!H.equivalent(p, q));
		assert(Z.contains_pair(p, q));

		// Now figure out all of the valid out-transition from p and q.
		CRSet C(T.out_labels(p));
		C.combine(T.out_labels(q));

		// Just make sure that p and q have the same out-transitions.
		int it;
		for (it = 0; !C.iter_end(it); it++)
		{
			if ((T.transition_on_range(p, C.iterator(it)) == Invalid) || (T.transition_on_range(q, C.iterator(it)) == Invalid))
			{
				// There's something that one transitions on, but
				// the other doesn't
				return (0);
			}  //if
		}  // for
		
		// p and q have out-transition on equivalent labels.
		// Keep track of whether checking needs to continue.
		S.add_pair(p, q);
		for (it = 0; !C.iter_end(it); it++)
		{
			State pdest(T.transition_on_range(p, C.iterator(it)));
			State qdest(T.transition_on_range(q, C.iterator(it)));
			if (!are_eq(pdest, qdest, S, H, Z))
			{
				S.remove_pair(p, q);
				return (0);
			}
		} // for

		// p and q have been found equivalent.
		S.remove_pair(p, q);
		return (1);
	} // if
}

//#define debug_min_Watson

/************ degug  */
#ifdef debug_min_Watson
using namespace std;

DFA& DFA::min_Watson()
{
	assert(class_invariant());
	// This algorithm requires that the DFA not have any final unreachable State. 
	// 此断言不是必须的,如果是非Usefulf(),算法执行后，使用usefulf()删除sink状态即可。
	// min_Hopcroft(),min_dragon(),min_Watson(),min_HopcroftUllman()同
	// assert(Usefulf()); 
	
	// (Symmetrical) State relation S is from p.14 of the min. taxonomy.
	SymRel S;
	S.set_domain(Q.size());
	cout << "Symmetrical) State relation S:" << S << endl; // 初始化S为|Q|个 empty set

	// H is used to accumulate equivalence relation E.
	StateEqRel H(Q.size());
	// Start with the identity since this approximation from below w.r.t refinement.
	H.identity(); // 每个state一个等价类，每个等价类中包含一个元素。
	cout << "identity equivalence relation E, H: " << H << endl;

	// Z is a SymRel containing pairs of States still to be considered.
	SymRel Z;
	Z.set_domain(Q.size());
	Z.identity();
	cout << "identity symmetrical state relation Z: " << Z << endl;
	// We will need the set of non-final States to initialize Z.
	StateSet nonfinal(F);
	nonfinal.complement();
	Z.add_pairs(F,nonfinal);
	cout << "F:" << F << ",Q\\F:" << nonfinal << endl;
	cout << "Z:{(F,Q\\F),(Q\\F,F)}:\n" << Z << endl;
	// Z now contains those pairs that identityly do noe used comparision.

	Z.complement();
	// Z initilialized properly now.
	cout << "Z is initialized to it's complement{(p,F-{p}),(q,Q\\F-{q})},p属于F，q属于Q\\F:\n" << Z << endl;

	State p;
	for (p = 0; p < Q.size(); p++)
	{
		State q;
		// Consider each q that p still needs to be compared to.
		cout << "for consider state " << p << " still needs to be compared to " << Z.image(p) << endl;

		for (Z.image(p).iter_start(q); !Z.image(p).iter_end(q); Z.image(p).iter_next(q))
		{
			cout << "states (" << p << "," << q << ") is equivalence? ";
			// Now compare p and q;
			if (are_eq(p, q, S, H, Z))
			{
				// p and q are equivalent.
				H.equivalize(p, q);
				cout << " yes\n";
				cout << "equivalence class H:" << H << endl;
			}
			else
			{
				// Don't do anything since we aren't computing
				// distinguishability explicity.
				cout << " no\n";
			}

			// Comparing q to p is the same as computing [q] and [p]
			// all at once
			// Mark them as much
			Z.remove_pairs(H.equiv_class(p), H.equiv_class(q));
			cout << "H.equiv_class(" << p << ")=" << H.equiv_class(p) << ",H.equiv_class(" << q << ")=" << H.equiv_class(q) << endl;
			cout << "Z.remove_pairs(H.equiv_class(" << p << "), H.equiv_class(" << q << ")):\n" << Z;

		} // for
	} // for

	cout << "before compress(H), H:" << H << endl;
	compress(H);
	assert(class_invariant());
	cout << "after compress(H), H:" << H << endl;

	return (*this);
}

#else

DFA& DFA::min_Watson()
{
	assert(class_invariant());
	// This algorithm requires that the DFA not have any final unreachable State. 
	// 此断言不是必须的,如果是非Usefulf(),算法执行后，使用usefulf()删除sink状态即可。
	// min_Hopcroft(),min_dragon(),min_Watson(),min_HopcroftUllman()同
	// assert(Usefulf()); 

	// (Symmetrical) State relation S is from p.14 of the min. taxonomy.
	SymRel S;
	S.set_domain(Q.size());

	// H is used to accumulate equivaence relation E.
	StateEqRel H(Q.size());
	// Start with the identity since this approximation from below
	// w.r.t refinement.
	H.identity();

	// Z is a SymRel containing pairs of States still to be considered.
	SymRel Z;
	Z.set_domain(Q.size());
	Z.identity();
	// We will need the set of non-final States to initialize Z.
	StateSet nonfinal(F);
	nonfinal.complement();
	Z.add_pairs(F, nonfinal);
	// Z now contains those pairs that identityly do noe used comparision.

	Z.complement();
	// Z initilized properly now.

	State p;
	for (p = 0; p < Q.size(); p++)
	{
		State q;
		// Consider each q that p still needs to be compared to.
		for (Z.image(p).iter_start(q); !Z.image(p).iter_end(q); Z.image(p).iter_next(q))
		{
			// Now compare p and q;
			if (are_eq(p, q, S, H, Z))
			{
				// p and q are equivalent.
				H.equivalize(p, q);
			}
			else
			{
				// Don't do anything since we aren't computing
				// distinguishability explicity.
			}

			// Comparing q to p is the same as computing [q] and [p]
			// all at once
			// Mark them as much
			Z.remove_pairs(H.equiv_class(p), H.equiv_class(q));
		} // for
	} // for

	compress(H);
	assert(class_invariant());

	return (*this);
}

#endif