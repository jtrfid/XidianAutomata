#include "stdafx.h"
#include <iostream>
#include "../StateSet.h"

using namespace std;

////////////// StateSet test /////////////////////

/**********************************************************************
   set_domain(const int r)������������״̬����state of index = [0,r)
   int domain()return �����������õ�����
   int size() return ״̬����this StateSet���Ѿ�bit�����õ�״̬�ܺ͡� states index = [0,size())
   add(const int r), r = [0,domain()),���״̬r 
   smallest(),������С״̬��index[0,domain())  
************************************************************************/
void basicStateSetTest()
{
	cout << "====basicStateSetTest()" << endl;
	StateSet st1;
	// set How many States can this set contain.
	// [O, domain()) can be contained in *this.
	// ����������5��״̬��StateSet
	st1.set_domain(5); // State index = 0,1��..., 4
	cout << "domain = " << st1.domain() << endl; // 5
	cout << "empty = " << st1.empty() << endl; // 0
	// inserts a State.[0,domain())
	st1.add(0);
	st1.add(2);
	st1.add(4);

	// ״̬������Ч״̬index = [0,size)
	cout << "number of states: " << st1.size() << endl;  // 3
	
	cout << "��С״̬index[0,domain()): " << st1.smallest() << endl; // 0
	cout << "st1 states: " << st1 << endl;  // {0,2,4}
}

/******************************************************
  int constins(const State r); r = [0,domain()),r״̬�Ƿ������this�С�  
  int contains(const StateSet &r); r�ġ�����״̬���Ƿ������this�С�precondition: this.domain() == r.domain
 ******************************************************/
void containsTest()
{
	cout << "====containsTest()" << endl;
	StateSet st1,st2,st3;
	st1.set_domain(5); 
	st2.set_domain(5);
	st3.set_domain(5);
	st1.add(0);
	st1.add(2);
	st1.add(4);
	st2.add(1);
	st3.add(0);
	st3.add(4);
	cout << "st1 states: " << st1 << endl;  // {0,2,4}
	cout << "st2 states: " << st2 << endl;  // {1}
	cout << "st3 states: " << st3 << endl;  // {0,4}

	// this�Ƿ���״̬ r = [0,domain())
	cout << "st1 ��״̬2: ? " << st1.contains(2) << endl;  // 1
	cout << "st1 ��״̬1: ��" << st1.contains(1) << endl;  // 0

	cout << "st1 contains st2: " << st1.contains(st2) << endl; // 0
	cout << "st1 contains st3: " << st1.contains(st3) << endl; // 1
	cout << "st3 contains st1: " << st3.contains(st1) << endl; // 0
}

/******************************************************
  // Does this set have something in common with r?
  // precondition: this.domain() == r.domain().
  int not_disjoint(const StateSet& r) const;
 ******************************************************/
void not_disjointTest()
{
	cout << "====not_disjointTest()" << endl;
	StateSet st1, st2, st3;
	st1.set_domain(5);
	st2.set_domain(5);
	st3.set_domain(5);
	st1.add(0);
	st1.add(2);
	st1.add(4);
	st2.add(1);
	st3.add(0);
	st3.add(4);
	cout << "st1 states: " << st1 << endl;  // {0,2,4}
	cout << "st2 states: " << st2 << endl;  // {1}
	cout << "st3 states: " << st3 << endl;  // {0,4}

	cout << "st1 not_disjoint st2: " << st1.not_disjoint(st2) << endl; // 0
	cout << "st1 not_disjoint st3: " << st1.not_disjoint(st3) << endl; // 1
	cout << "st3 not_disjoint st1: " << st3.not_disjoint(st1) << endl; // 1
}

/******************************************************
  // Set difference, precondition: this.domain() == r.domain(). this will be modified.
  StateSet& remove(const StateSet& r); this = this - r
 ******************************************************/
void removeTest()
{
	cout << "====removeTest()" << endl;
	StateSet st1, st2;
	st1.set_domain(5);
	st2.set_domain(5);
	st1.add(0);
	st1.add(2);
	st1.add(4);
	st2.add(1);
	st2.add(2);
	cout << "st1 states: " << st1 << endl;  // {0,2,4}
	cout << "st2 states: " << st2 << endl;  // {1,2}

	StateSet old_st1 = st1;
	cout << "st1 - st2: " << st1.remove(st2) << endl;     // { 0 4 }
	cout << "st2 - st1: " << st2.remove(old_st1) << endl; // { 1 }
}

// complement() this�Ĳ�����this�����޸�Ϊ���Ĳ��� 
void complementTest()
{
	cout << "====complementTest()" <<endl;
	StateSet st1;
	st1.set_domain(5); // State index = 0,1��..., 4
	st1.add(2);
	st1.add(4);
	cout << "st1:" << endl; // {2,4}

	StateSet old_st1 = st1;
	// st1���޸�Ϊ���Ĳ���
	cout << "st1 complement: " << st1.complement() << endl; // {0,1,3}
	cout << st1 << endl;  // {0,1,3}
	cout << old_st1 << endl; // {2,4}
}

// Set intersection. precondition: this.domain() == r.domain(). this will be modified.  
void intersectionTest()
{
	cout << "====intersectionTest" << endl;
	StateSet st1;
	st1.set_domain(5);
	st1.add(2);
	st1.add(4);
	cout << "st1: " << st1 << endl;  // {2,4}

	StateSet intersection_st12 = st1;
	StateSet intersection_st13 = st1;
	StateSet st2,st3;
	st2.set_domain(5);
	st3.set_domain(5);
	st2.add(1);
	st3.add(2);
	cout << "st2: " << st2 << endl;  // {1}
	cout << "st3: " << st3 << endl;  // {2}

	// Set intersection, precondition: this.domain() == r.domain(). this will be modified. 
	intersection_st12.intersection(st2);
	intersection_st13.intersection(st3);
	cout << "intersection_st12: " << intersection_st12 << endl;  // {2,4} intersection {1} ==> { }
	cout << "intersection_st12: " << intersection_st13 << endl;  // {2,4} intersection {2} ==> { 2 }
	cout << "st1: " << st1 << endl;  // {2,4}
}

/****************************************************************************
  set_union()��disjointing_union()���Ǽ�������StateSet���ϵĲ���
  set_union(const State& r) ����StateSet���ϵ�����(domain)���벻ͬ��״̬index�������ֱ��ϲ�, ״̬index����������
  disjointing_union(const State& r) ����StateSet���ϵ�����(domain)���Բ�ͬ��״̬index�����н������������ֲ��ϲ����������״̬index����������״̬���Ƕ��ߵĺ͡�
******************************************************************************/

// set_union(const DateSet& r); Set union, precondition: this.domain() == r.domain(). this will be modified. 
void set_unionTest1()
{
	cout << "====set_unionTest1(), ����StateSet��state�޽�����" << endl;
	StateSet st1;
	st1.set_domain(5); 
	st1.add(2);
	st1.add(4);
	cout << "st1: " << st1 << endl;  // {2,4}

	StateSet union_st12 = st1;
	StateSet st2;
	st2.set_domain(5);
	st2.add(1);
	cout << "st2: " << st2 << endl;  // {1}

	// Set union, precondition: this.domain() == r.domain(). this will be modified. 
	union_st12.set_union(st2);
	cout << "union_st12: " << union_st12 << endl;  // {2,4} union {1} ==> {1,2,4}
	cout << "st1: " << st1 << endl;  // {2,4}
}

// set_union(const DateSet& r); Set union, precondition: this.domain() == r.domain(). this will be modified. 
void set_unionTest2()
{
	cout << "====set_unionTest2()������StateSet��state�н�����" << endl;
	StateSet st1;
	st1.set_domain(5);
	st1.add(2);
	st1.add(4);
	cout << "st1: " << st1 << endl;  // {2,4}

	StateSet union_st12 = st1;
	StateSet st2;
	st2.set_domain(5);
	st2.add(2);
	cout << "st2: " << st2 << endl;  // {2}

	// Set union, precondition: this.domain() == r.domain(). this will be modified. 
	union_st12.set_union(st2);
	cout << "union_st12: " << union_st12 << endl;  // {2,4} union {2} ==> { 2,4 }
	cout << "st1: " << st1 << endl;  // {2,4}
}

// disjointing_union() test
void disjointing_unionTest1()
{
	cout << "====disjointing_unionTest(), ����StateSet��state�޽�����" << endl;
	StateSet st1, st2;
	// ok st1.domain() maybe != st2.domain()
	st1.set_domain(40);
	st2.set_domain(10);
	st1.add(2);
	st1.add(3);
	st2.add(1);
	st2.add(4);
	cout << "st1: " << st1 << endl;  // { 2,3 }
	cout << "st2: " << st2 << endl;  // { 1,4 }

	// Include another State Set into this one, renaming all the States.
	// this.domain() maybe != r.domain()
	st1.disjointing_union(st2); // { 2,3,5,8 }
	cout << "disjointing_union st1,st2: " << st1 << endl; // {2, 3, 5, 8}
	cout << st1.domain() << endl; // 9
}

// disjointing_union() test
void disjointing_unionTest2()
{
	cout << "====disjointing_unionTest(), ����StateSet��state�н�����" << endl;
	StateSet st1, st2;
	// ok st1.domain() maybe != st2.domain()
	st1.set_domain(40);
	st2.set_domain(10);
	st1.add(2);
	st1.add(3);
	st2.add(2);
	st2.add(4);
	cout << "st1: " << st1 << endl;  // { 2,3 }
	cout << "st2: " << st2 << endl;  // { 2,4 }

	// Include another State Set into this one, renaming all the States.
	// this.domain() maybe != r.domain()
	st1.disjointing_union(st2); // { 2,3,5,8 }
	cout << "disjointing_union st1,st2: " << st1 << endl; // {2, 3, 6, 8}
	cout << st1.domain() << endl; // 9
}

/******************************************************
  // Rename the elements of this StateSet so that they don't fall within StatePool r.
  // all states index in this ==> + r ==> left shift r
  // this.domain() += r 
  StateSet& st_rename(const int r);
 ******************************************************/
void st_renameTest()
{
	cout << "====st_renameTest" << endl;
	StateSet st1, st2;
	st1.set_domain(40);
	st2.set_domain(5);
	st1.add(0);
	st1.add(2);
	st1.add(4);
	st2.add(1);
	st2.add(2);
	cout << "st1 states: " << st1 << endl;  // {0,2,4}
	cout << "st2 states: " << st2 << endl;  // {1,2}
	cout << "st1.domain(),st2.domain(): " << st1.domain() << "," << st2.domain() << endl; // 40,5
	cout << "st1.size(),st2.size(): " << st1.size() << "," << st2.size() << endl; // 3,2
	cout << "st1.smallest(),st2.smallest(): " << st1.smallest() << "," << st2.smallest() << endl; // 0,1

	cout << "st1.st_rename(5): " << st1.st_rename(5) << endl;     // { 5 7 9 } index������5λ
	cout << "st2.st_rename(10): " << st2.st_rename(10) << endl; // { 11 12 } index������10λ

	cout << "st1.domain(),st2.domain(): " << st1.domain() << "," << st2.domain() << endl; // 45,15
	cout << "st1.size(),st2.size(): " << st1.size() << "," << st2.size() << endl; // 3,2
	cout << "st1.smallest(),st2.smallest(): " << st1.smallest() << "," << st2.smallest() << endl; // 5,11
}

/******************************************************
  // Make this set the emptyset.  Note: domain() not change. empty() = 1
  void clear();
 ******************************************************/
void clearTest()
{
	cout << "====clearTest" << endl;
	StateSet st1;
	st1.set_domain(40);
	st1.add(0);
	st1.add(2);
	st1.add(4);
	cout << "st1 states: " << st1 << endl;  // {0,2,4}
	cout << "st1.domain(): " << st1.domain() << endl; // 40
	cout << "st1.empty(): " << st1.empty() << endl; // 0
	cout << "clear st1\n";
	st1.clear();
	cout << "st1.domain(): " << st1.domain() << endl; // 0
	cout << "st1 states: " << st1 << endl;  // { }
	cout << "st1.empty(): " << st1.empty() << endl; // 1
	cout << "st1.smallest(): " << st1.smallest() << endl; // -1
}

/******************************************************
  // Recycle this StateSet. domain()=0, empty() = 1
  void reincarnate();
 ******************************************************/
void reincarnateTest()
{
	cout << "====reincarnateTest" << endl;
	StateSet st1;
	st1.set_domain(40);
	st1.add(0);
	st1.add(2);
	st1.add(4);
	cout << "st1 states: " << st1 << endl;  // {0,2,4}
	cout << "st1.domain(): " << st1.domain() << endl; // 40
	cout << "st1.empty(): " << st1.empty() << endl; // 0
	cout << "reincarnate st1\n";
	st1.reincarnate();
	cout << "st1.domain(): " << st1.domain() << endl; // 0
	cout << "st1 states: " << st1 << endl;  // { }
	cout << "st1.empty(): " << st1.empty() << endl; // 1
	cout << "st1.smallest(): " << st1.smallest() << endl; // -1
}

/******************************************************
  // Place the first State in the iteration in reference r.
  // r == Invalid if there is no first one.
  State iter_start(State& r) const;

   // Is r the last State in an iteration sequence.
  int iter_end(State r) const;

   // Place the next State, after r(in the iteration sequence), in reference r.
   inline State iter_next(State& r) const;
 ******************************************************/
void iterationTest()
{
	cout << "====iterationTest" << endl;
	StateSet st1;
	st1.set_domain(40);
	st1.add(0);
	st1.add(2);
	st1.add(4);
	cout << "st1 states: " << st1 << endl;  // {0,2,4}
	cout << "st1.domain(): " << st1.domain() << endl; // 40
	
	State st;
	int stateSize = st1.size(), i = 1;
	cout << "{ ";
	for (st1.iter_start(st); !st1.iter_end(st); st1.iter_next(st))
	{
		if (i < stateSize ) cout << st << ",";
		else cout << st << " }" << endl;
		i++;
	}
}

/******************************************************
  // Normal copy constructor.
  StateSet(const StateSet& r);
  const StateSet& operator=(const StateSet& r);
  int operator == (const StateSet& r) const;
  inline int operator != (const StateSet& r) const;
 ******************************************************/
void copyEqTest()
{
	cout << "====containsTest()" << endl;
	StateSet st1; // argument-less constructor
	st1.set_domain(10);
	st1.add(5);
	st1.add(2);
	st1.add(4);
	StateSet st2(st1);  // copy constructor.
	StateSet st3 = st1; // copy constructor.
	StateSet st4;
	st4 = st1;  // operator=
	cout << "st1 states: " << st1 << endl;  // {2,4,5}
	cout << "st2 states: " << st2 << endl;  // {2,4,5}
	cout << "st3 states: " << st3 << endl;  // {2,4,5}
	cout << "st4 states: " << st4 << endl;  // {2,4,5}
	cout << "domain(): " << st1.domain() << "," << st2.domain() << "," << st3.domain() << "," << st4.domain() << endl; // 10
	cout << "size(): " << st1.size() << "," << st2.size() << "," << st3.size() << "," << st4.size() << endl; // 3
	cout << "smallest(): " << st1.smallest() << "," << st2.smallest() << "," << st3.smallest() << "," << st4.smallest() << endl; // 2

	cout << "st1 == st2 == st3: " << (st1 == st2) << "," << (st2 == st3) << endl; // 1,1
	cout << "st1 != st2 != st3: " << (st1 != st2) << "," << (st2 != st3) << endl; // 0,0
	
	st3.remove(4);
	cout << "st3 states: " << st3 << endl;  // {2,5}
	cout << "st1 == st2 == st3: " << (st1 == st2) << "," << (st2 == st3) << endl; // 1,0
	cout << "st1 != st2 != st3: " << (st1 != st2) << "," << (st2 != st3) << endl; // 0,1
}

void StateSetTest()
{
	cout << "====StateSetTest()====" << endl;
	basicStateSetTest();
	containsTest();
	not_disjointTest();
	removeTest();
	complementTest(); 
	intersectionTest();
	set_unionTest1();
	set_unionTest2();
	disjointing_unionTest1();
	disjointing_unionTest2();
	st_renameTest();
	clearTest();
	reincarnateTest();
	iterationTest();
	copyEqTest();
}