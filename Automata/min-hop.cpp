/****************************************************************************************//*

Uses: CRSet, DFA, State, StateEqRel, SymRel
Description: Member function min_Hopcroft implements Hopcroft's n log n minimization algo-
	rithm, as presented in [Wat93b, Algorithm 4.8]

Implementation: The member function uses some encoding tricks to effectively implement the
	abstract algorithm. The combination of the out-transitions of all of the States is stored in a
	CRSet C. Set L from the abstract algorithm is implemented as a mapping from States to int 
	(an array of int is used). Array L should be interpreted as follows: if State [q] a representative,
	then the following pairs still require processing (are still in abstract set L):
	          ([q],C_0),([q],C_1),...,([q],C_(L(q)-1))
	The remaining pairs do not require processing:
			  ([q],C_(L(q))),...,([q],C_(|C|-1))
	This implementation facilities quick scanning of L for the next valid State-CharRange pair.

*//****************************************************************************************/
/*(c) Copyright 1994 by Bruce W. Watson */
// $Revision 1.1 $
// $Date: 1994/05/02 15:59:06 $

#include "CRSet.h"
#include "State.h"
#include "StateSet.h"
#include "StateEqRel.h"
#include "DFA.h"


/************ degug
using namespace std;

void printL(int *L, int n)
{
	cout << "L:\n";
	for (int i = 0; i < n; i++)
	{
		if (i < n-1) cout << i << " ";
		else cout << i << endl;
	}
	for (int i = 0; i < n; i++)
	{
		if (i < n - 1) cout << L[i] << " ";
		else cout << L[i] << endl;
	}
}

// Implemeta Algorithm 4.8 (Hopcroft O(n log n) algorithm)
DFA& DFA::min_Hopcroft()
{
	assert(class_invariant());

	// This algorithm requires that the DFA not have any final unreachable
	// State.
	//assert(Usefulf());

	State q;

	// Keep track of the combination fo all the out labels of State's.
	CRSet C;
	for (q = 0; q < Q.size(); q++)
	{
		C.combine(T.out_labels(q));
	}
	cout << "\nThe combination for all the out labels of State's：C = " << C << endl;

	// Encode set L as a mapping from State to [0,|C|] where:
	//            if q is a representative of a class in the partition P, then
	//            L(the abstract list) contains
	//                     ([q],C_0),([q],C_1),...,([q],C_(L(q)_1))
	//            but not
	//                     ([q],C_(L(q))),...,([q],C_(|C|_1))
	int *const L(new int[Q.size()]);
	for (q = 0; q < Q.size(); q++)
	{
		L[q] = 0;
	}
	
	printL(L, Q.size());

	// Initialize P to be total equivalence relation.
	StateEqRel P(Q.size()); // 等价类的个数不大于|Q|
	// Now set P to be E_0 = {F,Q\F}
	P.split(F); 
	cout << "Initialize partitions, E0:" << P << endl;

	// Now, build the set of equivalentatives and initialize L.
	StateSet repr(P.representatives());
	if (F.size() <= (Q.size() - F.size()))
	{
		repr.intersection(F);
		cout << "Initialize L repr = {F}:\n" << repr << endl;
	}
	else
	{
		repr.remove(F);
		cout << "Initialize L repr = {Q\F}:\n" << repr << endl;
	}

	// Do the final set up of L
	for (repr.iter_start(q); !repr.iter_end(q); repr.iter_next(q))
	{
		L[q] = C.size();
	}

	printL(L, Q.size());

	int k = 1;
	// Use a break to get of this loop
	while (1)
	{
		// Find the first pair in L that still needs processing.
		for (q = 0; q < Q.size() && !L[q]; q++);
		
		// It may be that we're at the end of the processing.
		if (q == Q.size())
		{
			break;
			cout << "--- end!";
		}
		else
		{
			// mark this element of L as processed.
			L[q]--;
			CharRange c = C.iterator(L[q]); // 记录正在处理的c。
			
			// Iterate over all eq. classes, and try to split them.
			State p;
			repr = P.representatives(); // current all partitions(eq.classes) repr
			
			cout << "=========================== Iterate: k = " << k++ << endl;
			printL(L, Q.size());
			cout << "Partitions:" << P << endl;
			cout << "pick [q] in L:([q],a)=([" << q << "]," << c << ")" << endl;
			cout << "split [p] w.r.t ([" << q << "]," << c << ")" << endl;
			
			for (repr.iter_start(p); !repr.iter_end(p); repr.iter_next(p))
			{
				cout << "===split[" << p << "] w.r.t ([" << q << "]," << c << ")" << endl;

				// Now split [p] w.r.t ([q], C_(L[q]))
				//State r(split(p, q, C.iterator(L[q]), P)); // L[q]是变化的，因此使用记录的c。
				State r(split(p, q, c, P)); 

				// r is the representative of the new split of the 
				// eq. class that was represented by p.

				cout << "new split of [" << p << "] is [" << r << "]" << endl;
				
				if (r != Invalid)
				{
					cout << "[p]=" << P.equiv_class(p) << endl;
					cout << "[r]=" << P.equiv_class(r) << endl;
					// p and r are the new representatives.
					// Now update L with the smallest of
					// [p] and [r]
					cout << "p and r are the new representatives. Now update L with the smallest of [" 
						<< p << "] and [" << r << "]" << endl;
					// [p]被分成两部分: 新的[p] 和 [r]
					if (P.equiv_class(p).size() <= P.equiv_class(r).size())
					{
						L[r] = L[p];      // [r]待处理L[p]剩下的字符
						L[p] = C.size();  // 新的[p], 待处理C[0]...C[C.size()-1]
						cout << "using [p] = [" << p << "],L[r]=L[p]; L[p]=C.size();" << endl;
					}
					else
					{
						L[r] = C.size(); // 新的[r]，待处理C[0]...C[C.size()-1]
						cout << "using [r] = [" << r << "],L[r]=C.size();" << endl;
					} // if
					cout << "after update L: " << endl;
					printL(L, Q.size());
				}  // if
			} // for
		} // if
	} // while

	// L is no longer needed.
	delete L;

	// we can now use P to compress the DFA.
	compress(P);

	assert(class_invariant());
	return (*this);
}
************************************/

DFA& DFA::min_Hopcroft()
{
	assert(class_invariant());

	// This algorithm requires that the DFA not have any final unreachable
	// State.
	//assert(Usefulf());

	State q;

	// Keep track of the combination fo all the out labels of State's.
	CRSet C;
	for (q = 0; q < Q.size(); q++)
	{
		C.combine(T.out_labels(q));
	}

	// Encode set L as a mapping from State to [0,|C|] where:
	//            if q is a representative of a class in the partition P, then
	//            L(the abstract list) contains
	//                     ([q],C_0),([q],C_1),...,([q],C_(L(q)_1))
	//            but not
	//                     ([q],C_(L(q))),...,([q],C_(|C|_1))
	int *const L(new int[Q.size()]);
	for (q = 0; q < Q.size(); q++)
	{
		L[q] = 0;
	}

	// Initialize P to be total equivalence relation.
	StateEqRel P(Q.size()); // 等价类的个数不大于|Q|
	// Now set P to be E_0.
	P.split(F);

	// Now, build the set of equivalentatives and initialize L.
	StateSet repr(P.representatives());
	if (F.size() <= (Q.size() - F.size()))
	{
		repr.intersection(F);
	}
	else
	{
		repr.remove(F);
	}

	// Do the final set up of L, 将会处理等价类[q]的out labels: C[0],...,C[|C|-1]，记录在L[q]
	for (repr.iter_start(q); !repr.iter_end(q); repr.iter_next(q))
	{
		L[q] = C.size();
	}

	// Use a break to get of this loop
	while (1)
	{
		// Find the first pair in L that still needs processing.
		for (q = 0; q < Q.size() && !L[q]; q++);

		// It may be that we're at the end of the processing.
		if (q == Q.size())
		{
			break;
		}
		else
		{
			// mark this element of L as processed. ([q],c)
			L[q]--;
			CharRange c = C.iterator(L[q]); // 记录正在处理的c

			// Iterate over all eq. classes, and try to split them.
			State p;
			repr = P.representatives(); // all partitions(eq.classes)

			for (repr.iter_start(p); !repr.iter_end(p); repr.iter_next(p))
			{
				// Now split [p] w.r.t (q, C_(L[q]))
				//State r(split(p, q, C.iterator(L[q]), P)); // L[q]是变化的，因此使用记录的c。
				State r(split(p, q, c, P));

				// r is the representative of the new split of the 
				// eq. class that was represented by p.

				if (r != Invalid)
				{
					// p and r are the new representatives.
					// Now update L with the smallest of
					// [p] and [r]
					// [p]被分成两部分: 新的[p] 和 [r]
					if (P.equiv_class(p).size() <= P.equiv_class(r).size())
					{
						L[r] = L[p];
						L[p] = C.size();
					}
					else
					{
						L[r] = C.size();
					} // if
				}  // if
			} // for
		} // if
	} // while

	// L is no longer needed.
	delete L;

	// we can now use P to compress the DFA.
	compress(P);

	assert(class_invariant());
	return (*this);
}
