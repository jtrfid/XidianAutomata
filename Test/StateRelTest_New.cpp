#include<iostream>
#include"StateRel.h"

using namespace std;

class StateRelTest_NewClass
{
public:
	/*****************************************************************************
									UnionCrossTest
	²âÊÔº¯Êý£º
	1.StateRel& union_cross(State p, State q)						map:State-->State
	2.StateRel& union_cross(State st, const StateSet& S)			map:State-->StateSet
	3.StateRel& union_cross(const StateSet& S, State st)			map:StateSet-->State
	4.StateRel& union_cross(const StateSet& A, const StateSet& B)   map:StateSet-->StateSet
	*****************************************************************************/
	void UnionCrossTest()
	{
		cout << "map:State-->State" << endl;
		StateRel sr;
		sr.set_domain(5);

		sr.union_cross(0, 1);
		sr.union_cross(1, 2);

		cout << "sr:" << sr << endl;//0->{1},1->{2}

		cout << "map:State-->StateSet" << endl;
		StateSet ss1;
		ss1.set_domain(5);
		ss1.add(0).add(1);

		sr.union_cross(1, ss1);

		cout << "ss1: " << ss1 <<endl;
		cout << "sr + 1 x ss1:" << sr << endl;//0->{1},1->{0,1,2}

		cout << "map:StateSet-->State" << endl;
		StateSet ss2;
		ss2.set_domain(5);
		ss2.add(4);

		sr.union_cross(ss2, 3);

		cout << "ss2: " << ss2 <<endl;
		cout << "sr + ss2 x 3:" << sr << endl;//0->{1},1->{0,1,2},4->{3}

		cout << "map:StateSet-->StateSet" << endl;

		sr.union_cross(ss1, ss2);

		cout << "sr + ss1 x ss2:" << sr << endl;//0->{1,4},1->{0,1,2,4},4->{3}
	}

	/*********************************************************************
								ImageTest
	²âÊÔº¯Êý£º
	1.StateSet image(const State& r) const        ·µ»Ø×´Ì¬0Ó³ÉäµÄStateSet
	2.StateSet image(const StateSet& r) const	  ·µ»ØStateSet rÖÐËùº¬×´Ì¬Ó³ÉäµÄStateSet
	*********************************************************************/
	void ImageTest()
	{
		cout << "ImageTest:" << endl;
		StateRel sr;
		sr.set_domain(5);

		sr.union_cross(0, 1);
		sr.union_cross(0, 2);
		sr.union_cross(0, 3);
		sr.union_cross(1, 3);
		sr.union_cross(1, 4);
		cout << "sr:" << sr << endl;

		StateSet ss1, ss2, ss3;
		ss3.set_domain(5);

		ss3.add(0).add(1);

		ss1 = sr.image(0);
		ss2 = sr.image(ss3);
		cout << "ss3:" << ss3 << endl;
		cout << "ss1 = sr image(0):" << ss1 << endl;//{1,2,3}
		cout << "ss2 = sr image(ss3):" << ss2 << endl;//{1,2,3,4}
	}

	/*
	closure(const StateSet& r) const ±Õ°ü:·µ»ØrÒÔ¼°ÆäÔÚ*thisÖÐÓ³ÉäµÄÄ¿±êStateSet
	*/
	void ClosureTest()
	{
		cout << "ClosureTest:" << endl;
		StateRel sr;
		sr.set_domain(5);

		// map: state p -> q
		sr.union_cross(0, 1);
		sr.union_cross(0, 2);
		sr.union_cross(0, 3);
		sr.union_cross(1, 3);
		sr.union_cross(1, 4);
		cout << "sr: " << endl << sr << endl;  

		StateSet ss1, ss2;
		ss1.set_domain(5);
		ss1.add(0);
		cout << "set1: " << ss1 << "," << ss1.domain() << "," << ss1.empty() << endl;  
		// set2.set_domain(5);
		ss2 = sr.closure(ss1);
		cout << "set2 = sr.closure(set1): " << ss2 << "," << ss2.domain() << "," << ss2.empty() << endl;  
	}

	/****************************************************************************
									ÒÆ³ýÓ³Éä²âÊÔ
	²âÊÔº¯Êý£º
	1.StateRel& remove_pair(const State p, const State q)			ÒÆ³ýÓ³Éä(State):p->q
	2.StateRel& remove_pairs(const StateSet& P, const StateSet& Q)	ÒÆ³ýÓ³Éä(StateSet):p->q
	****************************************************************************/
	void RemovePairTest()
	{
		cout << "RemovePairTest" << endl;
		StateRel sr;
		sr.set_domain(5);

		sr.union_cross(0, 1);
		sr.union_cross(0, 2);
		sr.union_cross(1, 2);
		sr.union_cross(1, 3);
		sr.union_cross(2, 3);
		sr.union_cross(2, 4);

		cout << "sr: " << sr << endl;
		cout << "remove pair(state)0->1:" << endl << sr.remove_pair(0, 1) << endl;

		StateSet s1, s2;
		s1.set_domain(5);
		s2.set_domain(5);

		s1.add(0).add(1);
		s2.add(2).add(3);

		cout << "remove pairs(StateSet)" << s1 << "->" << s2 << ":" << endl << sr.remove_pairs(s1, s2) << endl;
	}

	/*
	ÖØÖÃ²Ù×÷²âÊÔ
	*/
	void ClearAndReincarnateTest()
	{
		cout << "ClearAndReincarnateTest" << endl;
		StateRel sr;
		sr.set_domain(5);

		sr.union_cross(0, 1);
		sr.union_cross(0, 2);
		sr.union_cross(1, 2);

		cout << "sr: " << sr << endl;
		cout << "now clear sr" << endl;
		sr.clear();
		cout << "sr: " << sr << "sr domain: " << sr.domain() << endl;
		cout << "now reincarnate sr: " << endl;
		sr.reincarnate();
		cout << "sr: " << sr << "sr domain: " << sr.domain() << endl;
	}

	/*
	ºÏ²¢²âÊÔ
	*/
	void UnionAndDisjointingUnionTest()
	{
		cout << "UnionAndDisjointingUnionTest" << endl;
		StateRel sr1, sr2, sr3;
		sr1.set_domain(5);
		sr2.set_domain(5);
		sr3.set_domain(10);

		sr1.union_cross(0, 1);
		sr1.union_cross(0, 2);
		sr2.union_cross(1, 2);
		sr2.union_cross(1, 3);
		sr3.union_cross(5, 6);
		sr3.union_cross(7, 8);

		cout << "sr1: " << endl << sr1 << endl;
		cout << "sr2: " << endl << sr2 << endl;
		cout << "sr3: " << endl << sr3 << endl;

		sr1.set_union(sr2);
		cout << "sr1 union with sr2: " << endl << sr1 << "sr1 domain: " << sr1.domain() << endl;
		sr2.disjointing_union(sr3);
		cout << "sr2 disjointing union with sr3: " << endl << sr2 << "sr2 domain: " << sr2.domain() << endl;
	}
};

void StateRelTest_New()
{
	StateRelTest_NewClass t;
	/*t.UnionCrossTest();
	t.ImageTest();*/
	t.ClosureTest();
	/*t.RemovePairTest();
	t.ClearAndReincarnateTest();
	t.UnionAndDisjointingUnionTest();*/
}