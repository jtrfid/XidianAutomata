#include "DFA.h"
#include <iostream>
using namespace std;
void DFATest1()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(10);
	dfa_com1.S.add(0);
	//dfa_com1.S.add(1);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(10);
	dfa_com1.F.add(3);
	/*dfa_com1.F.add();
	dfa_com1.F.add();*/
	int i = 10;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}
	
	dfa_com1.T.set_domain(10);
	dfa_com1.T.add_transition(0, '0', 1);
	dfa_com1.T.add_transition(1, '0', 2);
	dfa_com1.T.add_transition(2, '0', 3);
	dfa_com1.T.add_transition(3, '0', 3);
	dfa_com1.T.add_transition(0, '1', 0);
	dfa_com1.T.add_transition(1, '1', 0);
	dfa_com1.T.add_transition(2, '1', 0);
	dfa_com1.T.add_transition(3, '1', 0);

	DFA dfa1(dfa_com1);
	cout << dfa1 << endl;
	dfa1.min_Brzozowski();
	cout << dfa1 << endl;/*
	const DFA dfa2(dfa_com1);

	cout << dfa2.Usefulf() << endl;*/

	//cout << /*dfa1.S*/ << endl;

}

void DFATest2()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(10);
	dfa_com1.S.add(0);
	//dfa_com1.S.add(1);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(10);
	dfa_com1.F.add(1);
	/*dfa_com1.F.add();
	dfa_com1.F.add();*/
	int i = 10;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(10);
	dfa_com1.T.add_transition(0, '0', 1);
	dfa_com1.T.add_transition(1, '0', 1);
	dfa_com1.T.add_transition(0, '1', 0);
	dfa_com1.T.add_transition(1, '1', 0);

	DFA dfa1(dfa_com1);
	cout << dfa1 << endl;
	//dfa1.reverse();
	//dfa1.reverse();
	dfa1.min_Brzozowski();
	cout << dfa1 << endl;/*
	const DFA dfa2(dfa_com1);

	cout << dfa2.Usefulf() << endl;*/

	//cout << /*dfa1.S*/ << endl;

}

void DFATest3()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(3);
	dfa_com1.S.add(0);
	//dfa_com1.S.add(1);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(3);
	dfa_com1.F.add(1);
	dfa_com1.F.add(2);
	/*dfa_com1.F.add();
	dfa_com1.F.add();*/
	int i = 3;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(3);
	dfa_com1.T.add_transition(0, '0', 1);
	dfa_com1.T.add_transition(0, '1', 2);

	DFA dfa1(dfa_com1);
	cout << dfa1 << endl;
	//dfa1.reverse();
	//dfa1.reverse();
	dfa1.min_Brzozowski();
	cout << dfa1 << endl;/*
	const DFA dfa2(dfa_com1);

	cout << dfa2.Usefulf() << endl;*/

	//cout << /*dfa1.S*/ << endl;

}

void DFATest()
{
	//DFATest1();
	//DFATest2();
	DFATest3();
}