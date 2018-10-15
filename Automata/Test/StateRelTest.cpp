//#include "../stdafx.h"  // fatal error C1010: 在查找预编译头时遇到意外的文件结尾。是否忘记了向源中添加“#include "stdafx.h"”?
#include "stdafx.h"  // 虽然在Test目录下无此文件，但是却骗取了编译器，无上述错误了
#include <iostream>
#include "../StateRel.h"

using namespace std;

class StateRelTestClass
{
public:
  /*************************************************************
   class StateRel :protected StateTo<StateSet>实现binary relation on States
   在StateRel中的所有state编号一致，[0,domain())
   set_domain()设置relation容量，就是states的个数。每个state映射至StateSet集合。

   // Member functions union_cross(A,B) makes *this the union (relation-wise) of *this
   // with A times B(Cartesian cross product).
   // Map p to q. precondition: p,q = [0,this.domain())
   StateRel& union_cross(State p, State q);
   // Map a st also to StateSet S. precondition: this.domain() == S.domain(), st = [0,this.domain())
   StateRel& union_cross(State st, const StateSet& S);
   // Map all members of S to st as well. precondition: this.domain() == S.domain(), st = [0,this.domain())
   StateRel& StateRel::union_cross(const StateSet& S, State st);
   // Map A to B . precondition: this.domain() == A.domain() == B.domain()
   StateRel& union_cross(const StateSet& A, const StateSet& B);
   *************************************************************/
	void basicStateRelTest()
	{
		cout << "===basicStateRelTest\n";
		StateRel sr;
		sr.set_domain(5);

		// map: state p -> q
		sr.union_cross(0, 1);
		sr.union_cross(0, 2);
		cout << "map: state p -> q: " << sr << endl;  // 0->{ 1 2 }

		// map: state st -> StateSet set1
		StateSet set1;
		set1.set_domain(5);  // sr.domain() = set1.domain()
		set1.add(0).add(1);
		cout << "set1: " << set1 << endl;
		// map: state 1 to set1(include state 0,1)
		sr.union_cross(1, set1);
		cout << "map: state st -> StateSet set1: " << sr << endl;  // 0->{ 1 2 }, 1->{ 0 1}

		// map: StateSet set1 -> state st 
		sr.union_cross(set1, 2);
		cout << "map: StateSet set1 -> state st: " << sr << endl;  // 0->{ 1 2 }, 1->{ 0 1 2 }

		// map: StateSet set1 -> StateSet set2 
		StateSet set2;
		set2.set_domain(5); // sr.domain() = set1.domain() = set2.domain()
		set2.add(3).add(4);
		cout << "set2: " << set2 << endl;
		sr.union_cross(set1, set2);
		cout << "map: StateSet set1 -> StateSet set2: " << sr << endl;  // 0->{ 1 2 3 4 }, 1->{ 0 1 2 3 4}
	}

	/**********************************************************************
		// Note: map: states -> states(images)
		// Compute(Lookup) the image of r under *this. precondition: this.domain() = r.domain()
		StateSet image(const StateSet& r) const;

		// Compute(Lookup) the image of a single State. precondition: r = [0,this.domain())
		inline const StateSet& image(const State r) const;
	 **********************************************************************/
	void imageTest()
	{
		cout << "===imageTest\n";
		StateRel sr;
		sr.set_domain(5);

		// map: state p -> q
		sr.union_cross(0, 1);
		sr.union_cross(0, 2);
		cout << "map: state p -> q: " << sr << endl;  // 0->{ 1 2 }

		StateSet set1, set2;
		set1 = sr.image(0);
		set2 = sr.image(1);
		cout << "set1: " << set1 << "," << set1.domain() << "," << set1.empty() << endl;  // { 1 2 },5,0
		cout << "set2: " << set2 << "," << set2.domain() << "," << set2.empty() << endl;  // { },5,1

		set2.add(0);
		StateSet set3;
		set3 = sr.image(set2);
		cout << "set3: " << set3 << "," << set3.domain() << "," << set3.empty() << endl;  // { 1 2 },5,0
	}

	/******************************************************************
		// Compute the reflexive and transitive closure of r under *this.
		// return r union { image }, Note: map: states -> states(images)
		StateSet closure(const StateSet& r) const;
	 ******************************************************************/
	void closureTest()
	{
		cout << "===cloureTest\n";
		StateRel sr;
		sr.set_domain(5);

		// map: state p -> q
		sr.union_cross(0, 1);
		sr.union_cross(2, 0);
		cout << "map: state p -> q: " << sr << endl;  // 0->{ 1 } 2->{ 0 }

		StateSet set1, set2;
		set1.set_domain(5);
		set1.add(2);
		cout << "set1: " << set1 << "," << set1.domain() << "," << set1.empty() << endl;  // { 2 },5,0
		// set2.set_domain(5);
		set2 = sr.closure(set1);
		cout << "set2 = sr.closure(set1): " << set2 << "," << set2.domain() << "," << set2.empty() << endl;  // { 1 2 },5,0
	}

	/******************************************************************
		// Remove a pair of States from the relation.
		// Remove map: p->q and q->p
		StateRel& remove_pair(const State p, const State q);
	 ******************************************************************/
	void remove_pairTest()
	{
		cout << "===remove_pairTest\n";
		StateRel sr;
		sr.set_domain(5);

		// map: state p -> q
		sr.union_cross(0, 1);
		sr.union_cross(2, 0);
		sr.union_cross(3, 4);
		cout << "map: state p -> q: " << sr << endl;  // 0->{ 1 } 2->{ 0 } 3->{ 4 }

		sr.remove_pair(0, 1);
		cout << "sr.remove_pair(0, 1): " << sr << endl; // 0->{  } 2->{ 0 } 3->{ 4 }
	}

	/******************************************************************
		// Remove map: P -> Q
		StateRel& remove_pairs(const StateSet& P, const StateSet& Q);
	 ******************************************************************/
	void remove_pairsTest()
	{
		cout << "===remove_pairsTest\n";
		StateRel sr;
		sr.set_domain(10);

		// map: state p -> q
		sr.union_cross(0, 1);
		sr.union_cross(2, 0);
		sr.union_cross(3, 4);
		sr.union_cross(7, 6);
		sr.union_cross(5, 8);
		sr.union_cross(5, 3);
		cout << "map: state p -> q: " << sr << endl;  // 0->{ 1 } 2->{ 0 } 3->{ 4 } 5->{ 3 8 } 7->{6}

		StateSet set1, set2;
		set1.set_domain(10);
		set2.set_domain(10);
		set1.add(5);
		set1.add(6);
		set2.add(3);
		set2.add(7);
		sr.remove_pairs(set1, set2);
		cout << "sr.remove_pairs(set1, set2): " << sr << endl; // 0->{ 1 } 2->{ 0 } 3->{ 4 } 5->{ 8 } 7->{ 6 }
	}

	/******************************************************************
		// Clear out this relation, without changing the domain.
		void clear();
	 ******************************************************************/
	void clearTest()
	{
		cout << "===clearTest\n";
		StateRel sr;
		sr.set_domain(10);

		// map: state p -> q
		sr.union_cross(0, 1);
		sr.union_cross(2, 0);
		sr.union_cross(3, 4);
		sr.union_cross(7, 6);
		sr.union_cross(5, 8);
		sr.union_cross(5, 3);
		cout << "map: state p -> q: " << sr << endl;  // 0->{ 1 } 2->{ 0 } 3->{ 4 } 5->{ 3 8 } 7->{6}
		cout << sr.domain() << endl;  // 10
		sr.clear();
		cout << "map: state p -> q: " << sr << endl;  // { }
		cout << sr.domain() << endl;  // 10
	}

	/******************************************************************
		// Recycle this entire relation. domain() = 0
		void StateRel::reincarnate()
	 ******************************************************************/
	void reincarnateTest()
	{
		cout << "===reincarnateTest\n";
		StateRel sr;
		sr.set_domain(10);

		// map: state p -> q
		sr.union_cross(0, 1);
		sr.union_cross(2, 0);
		sr.union_cross(3, 4);
		sr.union_cross(7, 6);
		sr.union_cross(5, 8);
		sr.union_cross(5, 3);
		cout << "map: state p -> q: " << sr << endl;  // 0->{ 1 } 2->{ 0 } 3->{ 4 } 5->{ 3 8 } 7->{6}
		cout << sr.domain() << endl;  // 10
		sr.reincarnate();
		cout << "map: state p -> q: " << sr << endl;  // { }
		cout << sr.domain() << endl;  // 0
	}

	/******************************************************************
		// Recycle this entire relation. domain() = 0
		void StateRel::reincarnate()
	 ******************************************************************/
	void disjointing_unionTest()
	{
		cout << "===reincarnateTest\n";
		StateRel sr1, sr2;
		sr1.set_domain(10);
		sr2.set_domain(20);
		sr1.union_cross(0, 1);
		sr1.union_cross(2, 0);
		sr2.union_cross(0, 5);
		cout << "sr1: " << sr1 << endl;  // 0->{ 1 } 2->{0}
		cout << sr1.domain() << endl;  // 10
		cout << "sr2: " << sr2 << endl;  // 0->{ 5 }
		cout << sr2.domain() << endl;  // 20
		cout << "sr1.disjointing_union(sr2)\n";
		sr1.disjointing_union(sr2);
		cout << "sr1: " << sr1 << endl;  // 0->{ 1 } 2->{0} 10->{ 15 }
		cout << sr1.domain() << endl;  // 30
		cout << "sr2: " << sr2 << endl;  // 0->{ 5 }
		cout << sr2.domain() << endl;  // 20
	}
};

void StateRelTest()
{
	cout << "===StateRelTest===\n";
	StateRelTestClass test;
	test.basicStateRelTest();
	test.imageTest();
	test.closureTest();
	test.remove_pairTest();
	test.remove_pairsTest();
	test.clearTest();
	test.reincarnateTest();
	test.disjointing_unionTest();
}