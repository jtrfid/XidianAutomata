#include "DFA.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// reverse test
void reverseTest1()
{
	DFA_components dfa_com1;
	int i = 3;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}
	// StateSet S  开始状态集
	dfa_com1.S.set_domain(dfa_com1.Q.size());
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(dfa_com1.Q.size());
	dfa_com1.F.add(0);
	dfa_com1.F.add(1);


	dfa_com1.T.set_domain(dfa_com1.Q.size());
	dfa_com1.T.add_transition(0, 'a', 1);
	dfa_com1.T.add_transition(1, 'b', 2);


	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;
	/**
	 Q = [0,3) S = { 0 } F = { 0  1 }
	Transitions = 0->{ 'a'->1 } 1->{ 'b'->2 } 2->{}
	 **/

	DSDFARev rev(dfa_com1.F, &(dfa_com1.T), &(dfa_com1.S));
	cout << "rev:" << rev << endl;
	/** 表示which是{0,1},T和S保持不变
	{ 0  1 } 0->{ 'a'->1 } 1->{ 'b'->2 } 2->{}
	{ 0 }
	 **/
	cout << "final:" << rev.final() << endl; // 1, F与S有交集
	cout << "out-T(a):" << rev.out_transition('a') << endl; 
	/** 当前对象which的"in"成为返回对象的"out"
	{ 0 } 0->{ 'a'->1 } 1->{ 'b'->2 } 2->{}
	{ 0 }
	 **/
	cout << "out-T(b):" << rev.out_transition('b') << endl;  // 返回对象无which
	cout << "out-label:" << rev.out_labels() << endl; // {'a'}进入which的labels，将变为out-transition of which

	cout << "dfa:" << dfa1 << endl; // 经过DSDFARev构造后，无变化
	/**
	 Q = [0,3) S = { 0 } F = { 0  1 }
	 Transitions = 0->{ 'a'->1 } 1->{ 'b'->2 } 2->{}
	 **/

	//construct_components(DSDFARev(F, &T, &S)));
	//DSDFARev::DSDFARev(const StateSet& rq, const DTransRel *rT, const StateSet *rS)

	dfa1.reverse(); // // 原来进入"in" F的transitions成为"out" F的transitions，F与S互换，删除不能进入原来F的状态集。由F to S, 依次"reverse"。
	cout << "reverse:" << dfa1 << endl;
	/**
	 Q = [0,2) S = { 0 } F = { 0  1 }
	 Transitions = 0->{ 'a'->1 } 1->{}
	 **/

	dfa1.reverse(); // 还原dfa,但是删除了不能到达final的状态集。
	cout << "reverse().reverse():" << dfa1 << endl;
	/**
	 Q = [0,2) S = { 0 } F = { 0  1 }
	 Transitions = 0->{ 'a'->1 } 1->{}
	 **/
}

// reverse test
void reverseTest2()
{
	DFA_components dfa_com1;
	int i = 3;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}
	// StateSet S  开始状态集
	dfa_com1.S.set_domain(dfa_com1.Q.size());
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(dfa_com1.Q.size());
	dfa_com1.F.add(2);


	dfa_com1.T.set_domain(dfa_com1.Q.size());
	dfa_com1.T.add_transition(0, 'a', 1);
	dfa_com1.T.add_transition(1, 'b', 2);


	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;
	/**
	Q = [0,3) S = { 0 } F = { 2 }
	Transitions =	0->{ 'a'->1 }	1->{ 'b'->2 }	2->{}
	 **/

	DSDFARev rev(dfa_com1.F, &(dfa_com1.T), &(dfa_com1.S));
	cout << "rev:" << rev << endl;
	/** 表示which是{2},T和S保持不变
	{ 2 } 0->{ 'a'->1 } 1->{ 'b'->2 } 2->{}
	{ 0 }
	 **/
	cout << "final:" << rev.final() << endl; // 0, F与S无交集
	cout << "out-T(a):" << rev.out_transition('a') << endl; // 返回对象无which
	cout << "out-T(b):" << rev.out_transition('b') << endl;  
	/** 当前对象which的"in"成为返回对象的"out"
	{ 1 } 0->{ 'a'->1 } 1->{ 'b'->2 } 2->{}
	{ 0 }
	 **/
	cout << "out-label:" << rev.out_labels() << endl; // {'b'}进入which的labels，将变为out-transition of which

	cout << "dfa:" << dfa1 << endl; // 经过DSDFARev构造后，无变化

	//construct_components(DSDFARev(F, &T, &S)));
	//DSDFARev::DSDFARev(const StateSet& rq, const DTransRel *rT, const StateSet *rS)

	dfa1.reverse(); // 原来进入"in" F的transitions成为"out" F的transitions，F与S互换，删除不能进入原来F的状态集。由F to S, 依次"reverse"。
	cout << "reverse:" << dfa1 << endl;
	/**
	 Q = [0,3)  S = { 0 } F = { 2 } Transitions = 0->{ 'b'->1 } 1->{ 'a'->2 }
     2->{}
	 **/

	dfa1.reverse(); // 还原dfa,但是删除了不能到达final的状态集。
	cout << "reverse().reverse():" << dfa1 << endl;
	/**
	Q = [0,3) S = { 0 } F = { 2 }
	Transitions =	0->{ 'a'->1 }	1->{ 'b'->2 }	2->{}
	 **/
}

//#define TO_FILE

void reverseT()
{
	cout << "start\n";
#ifdef TO_FILE
	// 重定向cout至file 
	fstream fs;
	fs.open("test.txt", ios::out);
	streambuf *stream_buffer_cout = cout.rdbuf(); // cout buffer
	streambuf *stream_buffer_file = fs.rdbuf(); // file buffer
	cout.rdbuf(stream_buffer_file);
#endif

	reverseTest1();
	//reverseTest2();
	//reverseTest3();

#ifdef TO_FILE
	// 恢复cout
	fs.close();
	std::cout.rdbuf(stream_buffer_cout);
#endif
}