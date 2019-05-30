#include "DFA.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/****************************************************************
DFA::min_Hopcroft()最小化算法的：前提条件: (1) start-reachable, Useful(s)
				                           (2) Complete
必要时，添加sink状态，使其成为完全自动机。
算法完成后，调用usefulf()，删除sink。

其他算法不必要求是Complete。
 ****************************************************************/

// 形式语言与自动机理论,pg. 141 fig. 5-4
void minDFATest1()
{
	/*
		初始化这样一个DFA (此表格的意义可以查看《形式语言与自动机理论》（ISBN 978-7-302-31802-6）pg. 73)
		状态说明   状态    输入字符 (《形式语言与自动机理论》（ISBN 978-7-302-31802-6）pg. 141 fig. 5-4)
							0      1
			start	q0      q1     q2
					q1      q0     q3
			accept  q2      q4     q5
			accept  q3      q4     q5
			accept  q4      q4     q5
			sink	q5      q5     q5


		预期结果 《形式语言与自动机理论》（ISBN 978-7-302-31802-6）pg. 153 fig. 5-6

		状态说明   状态        输入字符
							  0         1
			start	q0        q0        q1
			accept  q1        q1        

	*/

	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(6);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(6);
	dfa_com1.F.add(2);
	dfa_com1.F.add(3);
	dfa_com1.F.add(4);

	int i = 6;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	//dfa_com1.Q.set_domain(6);

	dfa_com1.T.set_domain(6);
	dfa_com1.T.add_transition(0, '0', 1);
	dfa_com1.T.add_transition(0, '1', 2);
	dfa_com1.T.add_transition(1, '0', 0);
	dfa_com1.T.add_transition(1, '1', 3);
	dfa_com1.T.add_transition(2, '0', 4);
	dfa_com1.T.add_transition(2, '1', 5);
	dfa_com1.T.add_transition(3, '0', 4);
	dfa_com1.T.add_transition(3, '1', 5);
	dfa_com1.T.add_transition(4, '0', 4);
	dfa_com1.T.add_transition(4, '1', 5);
	dfa_com1.T.add_transition(5, '0', 5);
	dfa_com1.T.add_transition(5, '1', 5);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n\n****************************************************\n\n" << std::flush;
	cout << dfa1 << endl;


	// 最小化并不要求是dfa1.Usefulf()
	// Can all States reach a final State?
	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;

	cout << "\n************ min_Hopcroft()***********\n";
	dfa1.min_Hopcroft();
	cout << "\n************ min_Hopcroft()\n"<< std::flush;
	cout << dfa1 << endl;

	if (dfa1.Usefulf() == 0) {
		dfa1.usefulf();
		cout << "After delete unreach final states:" << dfa1 << endl;
	}

	cout << "\n************min_dragon()****************\n";
	DFA dfa2(dfa_com1);
	dfa2.min_dragon();
	cout << "\n************min_dragon()\n"<< std::flush;
	cout << dfa2 << endl;
	if (dfa2.Usefulf() == 0) {
		dfa2.usefulf();
		cout << "After delete unreach final states:" << dfa2 << endl;
	}

	cout << "\n************min_HopcroftUllman()****************\n";
	DFA dfa3(dfa_com1);
	dfa3.min_HopcroftUllman();
	cout << "\n************min_HopcroftUllman()\n" << std::flush;
	cout << dfa3 << endl;
	if (dfa3.Usefulf() == 0) {
		dfa3.usefulf();
		cout << "After delete unreach final states:" << dfa3 << endl;
	}

	cout << "\n************min_Watson()****************\n";
	DFA dfa4(dfa_com1);
	dfa4.min_Watson();
	cout << "\n************min_Watson()\n" << std::flush;
	cout << dfa4 << endl;
	if (dfa4.Usefulf() == 0) {
		dfa4.usefulf();
		cout << "After delete unreach final states:" << dfa4 << endl;
	}
}

// 0: 0->1->2->3->4->5
void minDFATest2()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(6);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(6);
	dfa_com1.F.add(5);

	int i = 6;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	//dfa_com1.Q.set_domain(6);

	dfa_com1.T.set_domain(6);
	dfa_com1.T.add_transition(0, '0', 1);
	dfa_com1.T.add_transition(1, '0', 2);
	dfa_com1.T.add_transition(2, '0', 3);
	dfa_com1.T.add_transition(3, '0', 4);
	dfa_com1.T.add_transition(4, '0', 5);
	dfa_com1.T.add_transition(5, '0', 5);
	dfa_com1.T.add_transition(0, '1', 0);
	dfa_com1.T.add_transition(1, '1', 1);
	dfa_com1.T.add_transition(2, '1', 2);
	dfa_com1.T.add_transition(3, '1', 3);
	dfa_com1.T.add_transition(4, '1', 4);
	dfa_com1.T.add_transition(5, '1', 5);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;
	
	dfa1.min_Hopcroft();
	cout << "\n************ minDFA\n" << std::flush;
	cout << dfa1 << endl;
}

// useful测试，usefulf()应该删除1,3状态，但是没有删除,因此结果错误。
void minDFATest3()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(5);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(5);
	dfa_com1.F.add(3);
	dfa_com1.F.add(4);

	int i = 5;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(5);
	dfa_com1.T.add_transition(0, '0', 4);
	dfa_com1.T.add_transition(0, '1', 2);
	dfa_com1.T.add_transition(1, '0', 2);
	dfa_com1.T.add_transition(1, '1', 2);
	dfa_com1.T.add_transition(2, '0', 4);
	dfa_com1.T.add_transition(2, '1', 2);
	dfa_com1.T.add_transition(3, '0', 2);
	dfa_com1.T.add_transition(3, '1', 3);
	dfa_com1.T.add_transition(4, '0', 4);
	dfa_com1.T.add_transition(4, '1', 4);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	dfa1.usefulf();  // 没有删除1,3 ？
	cout << dfa1 << endl;
	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;

	dfa1.min_Hopcroft();
	cout << "\n************ minDFA\n" << std::flush;
	cout << dfa1 << endl;
}

// useful测试，删除1,3状态，再最小化，结果正确。
void minDFATest3_1()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(3);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(3);
	dfa_com1.F.add(2);

	int i = 3;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(3);
	dfa_com1.T.add_transition(0, '0', 2);
	dfa_com1.T.add_transition(0, '1', 1);
	dfa_com1.T.add_transition(1, '0', 2);
	dfa_com1.T.add_transition(1, '1', 1);
	dfa_com1.T.add_transition(2, '0', 2);
	dfa_com1.T.add_transition(2, '1', 2);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;

	dfa1.min_Hopcroft();
	cout << "\n************ minDFA\n" << std::flush;
	cout << dfa1 << endl;
}

// 形式语言与自动机理论,pg. 154 fig. 5-7
void minDFATest4()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(10);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(10);
	dfa_com1.F.add(4);
	dfa_com1.F.add(8);

	int i = 10;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(10);
	dfa_com1.T.add_transition(0, '0', 1);
	dfa_com1.T.add_transition(0, '1', 5);
	dfa_com1.T.add_transition(1, '0', 5);
	dfa_com1.T.add_transition(1, '1', 2);
	dfa_com1.T.add_transition(2, '0', 3);
	dfa_com1.T.add_transition(2, '1', 6);
	dfa_com1.T.add_transition(3, '0', 2);
	dfa_com1.T.add_transition(3, '1', 4);
	dfa_com1.T.add_transition(4, '0', 8);
	dfa_com1.T.add_transition(4, '1', 1);
	dfa_com1.T.add_transition(5, '0', 1);
	dfa_com1.T.add_transition(5, '1', 6);
	dfa_com1.T.add_transition(6, '0', 7);
	dfa_com1.T.add_transition(6, '1', 2);
	dfa_com1.T.add_transition(7, '0', 6);
	dfa_com1.T.add_transition(7, '1', 8);
	dfa_com1.T.add_transition(8, '0', 5);
	dfa_com1.T.add_transition(8, '1', 4);
	dfa_com1.T.add_transition(9, '0', 7);
	dfa_com1.T.add_transition(9, '1', 5);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;

	cout << "\n************ min_Hopcroft()***********\n";
	dfa1.min_Hopcroft();
	cout << "\n************ min_Hopcroft()\n" << std::flush;
	cout << dfa1 << endl;

	if (dfa1.Usefulf() == 0) {
		dfa1.usefulf();
		cout << "After delete unreach final states:" << dfa1 << endl;
	}

	cout << "\n************min_dragon()****************\n";
	DFA dfa2(dfa_com1);
	dfa2.min_dragon();
	cout << "\n************min_dragon()\n" << std::flush;
	cout << dfa2 << endl;
	if (dfa2.Usefulf() == 0) {
		dfa2.usefulf();
		cout << "After delete unreach final states:" << dfa2 << endl;
	}

	cout << "\n************min_HopcroftUllman()****************\n";
	DFA dfa3(dfa_com1);
	dfa3.min_HopcroftUllman();
	cout << "\n************min_HopcroftUllman()\n" << std::flush;
	cout << dfa3 << endl;
	if (dfa3.Usefulf() == 0) {
		dfa3.usefulf();
		cout << "After delete unreach final states:" << dfa3 << endl;
	}

	cout << "\n************min_Watson()****************\n";
	DFA dfa4(dfa_com1);
	dfa4.min_Watson();
	cout << "\n************min_Watson()\n" << std::flush;
	cout << dfa4 << endl;
	if (dfa4.Usefulf() == 0) {
		dfa4.usefulf();
		cout << "After delete unreach final states:" << dfa4 << endl;
	}

	cout << "\n************min_Brzozowski()****************\n";
	DFA dfa5(dfa_com1);
	dfa5.min_Brzozowski();
	cout << "\n************ min_Brzozowski()\n" << std::flush;
	cout << dfa5 << endl;
	if (dfa5.Usefulf() == 0) {
		dfa5.usefulf();
		cout << "After delete unreach final states:" << dfa5 << endl;
	}
}

// 形式语言与自动机理论,pg. 154 fig. 5-7(删除不可达p9)
void minDFATest5()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(9);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(9);
	dfa_com1.F.add(4);
	dfa_com1.F.add(8);

	int i = 9;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(9);
	dfa_com1.T.add_transition(0, '0', 1);
	dfa_com1.T.add_transition(0, '1', 5);
	dfa_com1.T.add_transition(1, '0', 5);
	dfa_com1.T.add_transition(1, '1', 2);
	dfa_com1.T.add_transition(2, '0', 3);
	dfa_com1.T.add_transition(2, '1', 6);
	dfa_com1.T.add_transition(3, '0', 2);
	dfa_com1.T.add_transition(3, '1', 4);
	dfa_com1.T.add_transition(4, '0', 8);
	dfa_com1.T.add_transition(4, '1', 1);
	dfa_com1.T.add_transition(5, '0', 1);
	dfa_com1.T.add_transition(5, '1', 6);
	dfa_com1.T.add_transition(6, '0', 7);
	dfa_com1.T.add_transition(6, '1', 2);
	dfa_com1.T.add_transition(7, '0', 6);
	dfa_com1.T.add_transition(7, '1', 8);
	dfa_com1.T.add_transition(8, '0', 5);
	dfa_com1.T.add_transition(8, '1', 4);
	//dfa_com1.T.add_transition(9, '0', 7);
	//dfa_com1.T.add_transition(9, '1', 5);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;

	//cout << "\n************ min_Hopcroft()***********\n";
	//dfa1.min_Hopcroft();
	//cout << "\n************ min_Hopcroft()\n" << std::flush;
	//cout << dfa1 << endl;

	//if (dfa1.Usefulf() == 0) {
	//	dfa1.usefulf();
	//	cout << "After delete unreach final states:" << dfa1 << endl;
	//}

	//cout << "\n************min_dragon()****************\n";
	//DFA dfa2(dfa_com1);
	//dfa2.min_dragon();
	//cout << "\n************min_dragon()\n" << std::flush;
	//cout << dfa2 << endl;
	//if (dfa2.Usefulf() == 0) {
	//	dfa2.usefulf();
	//	cout << "After delete unreach final states:" << dfa2 << endl;
	//}

	//cout << "\n************min_HopcroftUllman()****************\n";
	//DFA dfa3(dfa_com1);
	//dfa3.min_HopcroftUllman();
	//cout << "\n************min_HopcroftUllman()\n" << std::flush;
	//cout << dfa3 << endl;
	//if (dfa3.Usefulf() == 0) {
	//	dfa3.usefulf();
	//	cout << "After delete unreach final states:" << dfa3 << endl;
	//}

	//cout << "\n************min_Watson()****************\n";
	//DFA dfa4(dfa_com1);
	//dfa4.min_Watson();
	//cout << "\n************min_Watson()\n" << std::flush;
	//cout << dfa4 << endl;
	//if (dfa4.Usefulf() == 0) {
	//	dfa4.usefulf();
	//	cout << "After delete unreach final states:" << dfa4 << endl;
	//}

	cout << "\n************min_Brzozowski()****************\n";
	DFA dfa5(dfa_com1);
	dfa5.min_Brzozowski();
	//dfa5.reverse();
	cout << "\n************ min_Brzozowski()\n" << std::flush;
	cout << dfa5 << endl;
	if (dfa5.Usefulf() == 0) {
		dfa5.usefulf();
		cout << "After delete unreach final states:" << dfa5 << endl;
	}
}

// 非complete DFA, mini合并状态{1,2}正确，但由于是非complete DFA，其中的compress(P)错误。
void minDFATest6()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(3);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(3);
	dfa_com1.F.add(1);
	dfa_com1.F.add(2);

	int i = 3;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(3);
	dfa_com1.T.add_transition(0, 'a', 1);
	dfa_com1.T.add_transition(0, 'b', 2);
	dfa_com1.T.add_transition(1, 'a', 2);
	dfa_com1.T.add_transition(2, 'b', 1);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;

	dfa1.min_Hopcroft();
	cout << "\n************ minDFA\n" << std::flush;
	cout << dfa1 << endl;
}

//  把minDFATest6的DFA 增加一个sink, 成为complete DFA, mini结果正确。
void minDFATest7()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(4);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(4);
	dfa_com1.F.add(1);
	dfa_com1.F.add(2);

	int i = 4;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(4);
	dfa_com1.T.add_transition(0, 'a', 1);
	dfa_com1.T.add_transition(0, 'b', 2);
	dfa_com1.T.add_transition(1, 'a', 2);
	dfa_com1.T.add_transition(1, 'b', 3);
	dfa_com1.T.add_transition(2, 'b', 1);
	dfa_com1.T.add_transition(2, 'a', 3);
	dfa_com1.T.add_transition(3, 'a', 3);
	dfa_com1.T.add_transition(3, 'b', 3);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	//dfa1.usefulf();
	cout << dfa1 << endl;
	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;

	dfa1.min_Hopcroft();
	cout << "\n************ minDFA\n" << std::flush;
	cout << dfa1 << endl;
}

// Sink, 每个状态就是一个等价类
void minDFATest8()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(10);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(10);
	dfa_com1.F.add(6);
	dfa_com1.F.add(7);
	dfa_com1.F.add(8);

	int i = 10;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(10);
	dfa_com1.T.add_transition(0, 'a', 1);
	dfa_com1.T.add_transition(0, 'b', 8);
	dfa_com1.T.add_transition(1, 'a', 2);
	dfa_com1.T.add_transition(1, 'b', 4);
	dfa_com1.T.add_transition(2, 'a', 2);
	dfa_com1.T.add_transition(2, 'b', 6);
	dfa_com1.T.add_transition(3, 'a', 4);
	dfa_com1.T.add_transition(3, 'b', 7);
	dfa_com1.T.add_transition(4, 'a', 6);
	dfa_com1.T.add_transition(4, 'b', 6);
	dfa_com1.T.add_transition(5, 'a', 7);
	dfa_com1.T.add_transition(5, 'b', 7);
	dfa_com1.T.add_transition(6, 'a', 9);
	dfa_com1.T.add_transition(6, 'b', 9);
	dfa_com1.T.add_transition(7, 'a', 6);
	dfa_com1.T.add_transition(7, 'b', 6);
	dfa_com1.T.add_transition(8, 'a', 5);
	dfa_com1.T.add_transition(8, 'b', 3);
	dfa_com1.T.add_transition(9, 'a', 9);
	dfa_com1.T.add_transition(9, 'b', 9);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;


	// 最小化并不要求是dfa1.Usefulf()
	// Can all States reach a final State?
	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;

	cout << "\n************ min_Hopcroft()***********\n";
	dfa1.min_Hopcroft();
	cout << "\n************ min_Hopcroft()\n" << std::flush;
	cout << dfa1 << endl;

	if (dfa1.Usefulf() == 0) {
		dfa1.usefulf();
		cout << "After delete unreach final states:" << dfa1 << endl;
	}

	cout << "\n************min_dragon()****************\n";
	DFA dfa2(dfa_com1);
	dfa2.min_dragon();
	cout << "\n************min_dragon()\n" << std::flush;
	cout << dfa2 << endl;
	if (dfa2.Usefulf() == 0) {
		dfa2.usefulf();
		cout << "After delete unreach final states:" << dfa2 << endl;
	}

}

// NoSink，但，它是完全自动机，验证了eq.class {4，5},{6,7}
void minDFATest9()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(9);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(9);
	dfa_com1.F.add(6);
	dfa_com1.F.add(7);
	dfa_com1.F.add(8);

	int i = 9;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(9);
	dfa_com1.T.add_transition(0, 'a', 1);
	dfa_com1.T.add_transition(0, 'b', 8);
	dfa_com1.T.add_transition(1, 'a', 2);
	dfa_com1.T.add_transition(1, 'b', 4);
	dfa_com1.T.add_transition(2, 'a', 2);
	dfa_com1.T.add_transition(2, 'b', 6);
	dfa_com1.T.add_transition(3, 'a', 4);
	dfa_com1.T.add_transition(3, 'b', 7);
	dfa_com1.T.add_transition(4, 'a', 6);
	dfa_com1.T.add_transition(4, 'b', 6);
	dfa_com1.T.add_transition(5, 'a', 7);
	dfa_com1.T.add_transition(5, 'b', 7);
	dfa_com1.T.add_transition(6, 'a', 6);
	dfa_com1.T.add_transition(6, 'b', 6);
	dfa_com1.T.add_transition(7, 'a', 6);
	dfa_com1.T.add_transition(7, 'b', 6);
	dfa_com1.T.add_transition(8, 'a', 5);
	dfa_com1.T.add_transition(8, 'b', 3);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;


	cout << "\n************ min_Hopcroft()***********\n";
	dfa1.min_Hopcroft();
	cout << "\n************ min_Hopcroft()\n" << std::flush;
	cout << dfa1 << endl;

	if (dfa1.Usefulf() == 0) {
		dfa1.usefulf();
		cout << "After delete unreach final states:" << dfa1 << endl;
	}

	cout << "\n************min_dragon()****************\n";
	DFA dfa2(dfa_com1);
	dfa2.min_dragon();
	cout << "\n************min_dragon()\n" << std::flush;
	cout << dfa2 << endl;
	if (dfa2.Usefulf() == 0) {
		dfa2.usefulf();
		cout << "After delete unreach final states:" << dfa2 << endl;
	}

	cout << "\n************min_HopcroftUllman()****************\n";
	DFA dfa3(dfa_com1);
	dfa3.min_HopcroftUllman();
	cout << "\n************min_HopcroftUllman()\n" << std::flush;
	cout << dfa3 << endl;
	if (dfa3.Usefulf() == 0) {
		dfa3.usefulf();
		cout << "After delete unreach final states:" << dfa3 << endl;
	}

}

void minDFATest10()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(5);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(5);
	dfa_com1.F.add(3);
	dfa_com1.F.add(4);

	int i = 5;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(5);
	dfa_com1.T.add_transition(0, '0', 3);
	dfa_com1.T.add_transition(0, '1', 2);
	dfa_com1.T.add_transition(1, '0', 2);
	dfa_com1.T.add_transition(1, '1', 2);
	dfa_com1.T.add_transition(2, '0', 3);
	dfa_com1.T.add_transition(2, '1', 2);
	dfa_com1.T.add_transition(3, '0', 3);
	dfa_com1.T.add_transition(3, '1', 3);
	dfa_com1.T.add_transition(4, '0', 2);
	dfa_com1.T.add_transition(4, '1', 4);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;


	dfa1.min_Hopcroft();
	cout << "\n************ minDFA\n" << std::flush;
	cout << dfa1 << endl;
}

// SINK
void minDFATest11()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(16);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(16);
	dfa_com1.F.add(1);
	dfa_com1.F.add(6);
	dfa_com1.F.add(8);
	dfa_com1.F.add(9);
	dfa_com1.F.add(10);

	int i = 16;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(16);
	dfa_com1.T.add_transition(0, '0', 1);
	dfa_com1.T.add_transition(0, '1', 2);
	dfa_com1.T.add_transition(1, '0', 3);
	dfa_com1.T.add_transition(1, '1', 4);
	dfa_com1.T.add_transition(2, '0', 5);
	dfa_com1.T.add_transition(2, '1', 6);
	dfa_com1.T.add_transition(3, '0', 7);
	dfa_com1.T.add_transition(3, '1', 8);
	dfa_com1.T.add_transition(4, '0', 9);
	dfa_com1.T.add_transition(4, '1', 10);
	dfa_com1.T.add_transition(5, '0', 11);
	dfa_com1.T.add_transition(5, '1', 12);
	dfa_com1.T.add_transition(6, '0', 13);
	dfa_com1.T.add_transition(6, '1', 14);
	dfa_com1.T.add_transition(7, '0', 15);
	dfa_com1.T.add_transition(7, '1', 15);
	dfa_com1.T.add_transition(8, '0', 15);
	dfa_com1.T.add_transition(8, '1', 15);
	dfa_com1.T.add_transition(9, '0', 15);
	dfa_com1.T.add_transition(9, '1', 15);
	dfa_com1.T.add_transition(10, '0', 15);
	dfa_com1.T.add_transition(10, '1', 15);
	dfa_com1.T.add_transition(11, '0', 15);
	dfa_com1.T.add_transition(11, '1', 15);
	dfa_com1.T.add_transition(12, '0', 15);
	dfa_com1.T.add_transition(12, '1', 15);
	dfa_com1.T.add_transition(13, '0', 15);
	dfa_com1.T.add_transition(13, '1', 15);
	dfa_com1.T.add_transition(14, '0', 15);
	dfa_com1.T.add_transition(14, '1', 15);
	dfa_com1.T.add_transition(15, '0', 15);
	dfa_com1.T.add_transition(15, '1', 15);


	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;


	dfa1.min_Hopcroft();
	cout << "\n************ minDFA\n" << std::flush;
	cout << dfa1 << endl;
}

// NOSINK，不正确的做法，min_Hopcroft()需要完全自动机
void minDFATest12()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(15);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(15);
	dfa_com1.F.add(1);
	dfa_com1.F.add(6);
	dfa_com1.F.add(8);
	dfa_com1.F.add(9);
	dfa_com1.F.add(10);

	int i = 15;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(15);
	dfa_com1.T.add_transition(0, '0', 1);
	dfa_com1.T.add_transition(0, '1', 2);
	dfa_com1.T.add_transition(1, '0', 3);
	dfa_com1.T.add_transition(1, '1', 4);
	dfa_com1.T.add_transition(2, '0', 5);
	dfa_com1.T.add_transition(2, '1', 6);
	dfa_com1.T.add_transition(3, '0', 7);
	dfa_com1.T.add_transition(3, '1', 8);
	dfa_com1.T.add_transition(4, '0', 9);
	dfa_com1.T.add_transition(4, '1', 10);
	dfa_com1.T.add_transition(5, '0', 11);
	dfa_com1.T.add_transition(5, '1', 12);
	dfa_com1.T.add_transition(6, '0', 13);
	dfa_com1.T.add_transition(6, '1', 14);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;


	dfa1.min_Hopcroft();
	cout << "\n************ minDFA\n" << std::flush;
	cout << dfa1 << endl;
}

// 郑浩雨
void minDFATest13()
{
	DFA_components dfa_com1;

	// StateSet S  开始状态集
	dfa_com1.S.set_domain(5);
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(5);
	dfa_com1.F.add(0);
	dfa_com1.F.add(1);
	dfa_com1.F.add(3);
	dfa_com1.F.add(4);

	int i = 5;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}

	dfa_com1.T.set_domain(5);
	dfa_com1.T.add_transition(0, '1', 1);
	dfa_com1.T.add_transition(0, '2', 2);
	dfa_com1.T.add_transition(1, '1', 3);
	dfa_com1.T.add_transition(1, '2', 2);
	dfa_com1.T.add_transition(2, '1', 4);
	dfa_com1.T.add_transition(2, '2', 2);
	dfa_com1.T.add_transition(3, '1', 1);
	dfa_com1.T.add_transition(3, '2', 2);
	dfa_com1.T.add_transition(4, '1', 4);
	dfa_com1.T.add_transition(4, '2', 2);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;


	cout << "\n************ min_Hopcroft()***********\n";
	dfa1.min_Hopcroft();
	cout << "\n************ min_Hopcroft()\n" << std::flush;
	cout << dfa1 << endl;

	if (dfa1.Usefulf() == 0) {
		dfa1.usefulf();
		cout << "After delete unreach final states:" << dfa1 << endl;
	}

	cout << "\n************min_dragon()****************\n";
	DFA dfa2(dfa_com1);
	dfa2.min_dragon();
	cout << "\n************min_dragon()\n" << std::flush;
	cout << dfa2 << endl;
	if (dfa2.Usefulf() == 0) {
		dfa2.usefulf();
		cout << "After delete unreach final states:" << dfa2 << endl;
	}

	cout << "\n************min_HopcroftUllman()****************\n";
	DFA dfa3(dfa_com1);
	dfa3.min_HopcroftUllman();
	cout << "\n************min_HopcroftUllman()\n" << std::flush;
	cout << dfa3 << endl;
	if (dfa3.Usefulf() == 0) {
		dfa3.usefulf();
		cout << "After delete unreach final states:" << dfa3 << endl;
	}

	cout << "\n************min_Watson()****************\n";
	DFA dfa4(dfa_com1);
	dfa4.min_Watson();
	cout << "\n************min_Watson()\n" << std::flush;
	cout << dfa4 << endl;
	if (dfa4.Usefulf() == 0) {
		dfa4.usefulf();
		cout << "After delete unreach final states:" << dfa4 << endl;
	}

	cout << "\n************min_Brzozowski()****************\n";
	DFA dfa5(dfa_com1);
	dfa5.min_Brzozowski();  
	cout << "\n************ min_Brzozowski()\n" << std::flush;
	cout << dfa5 << endl;
	if (dfa5.Usefulf() == 0) {
		dfa5.usefulf();
		cout << "After delete unreach final states:" << dfa5 << endl;
	}
}

// min_Hopcroft()与其他算法结果不一致，分析结论：min_Hopcroft算法的前提条件是必须是完全自动机。
void minDFATest14()
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
	dfa_com1.F.add(1);
	dfa_com1.F.add(2);


	dfa_com1.T.set_domain(dfa_com1.Q.size());
	dfa_com1.T.add_transition(0, 'a', 1);
	dfa_com1.T.add_transition(0, 'b', 2);
	dfa_com1.T.add_transition(1, 'b', 2);
	dfa_com1.T.add_transition(2, 'a', 1);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	cout << " is the DFA Usefulf ?: " << dfa1.Usefulf() << endl;

	cout << "\n************ min_Hopcroft()***********\n";
	dfa1.min_Hopcroft();
	cout << "\n************ min_Hopcroft()\n" << std::flush;
	cout << dfa1 << endl;

	if (dfa1.Usefulf() == 0) {
		dfa1.usefulf();
		cout << "After delete unreach final states:" << dfa1 << endl;
	}

	cout << "\n************min_dragon()****************\n";
	DFA dfa2(dfa_com1);
	dfa2.min_dragon();
	cout << "\n************min_dragon()\n" << std::flush;
	cout << dfa2 << endl;
	if (dfa2.Usefulf() == 0) {
		dfa2.usefulf();
		cout << "After delete unreach final states:" << dfa2 << endl;
	}

	cout << "\n************min_HopcroftUllman()****************\n";
	DFA dfa3(dfa_com1);
	dfa3.min_HopcroftUllman();
	cout << "\n************min_HopcroftUllman()\n" << std::flush;
	cout << dfa3 << endl;
	if (dfa3.Usefulf() == 0) {
		dfa3.usefulf();
		cout << "After delete unreach final states:" << dfa3 << endl;
	}

	cout << "\n************min_Watson()****************\n";
	DFA dfa4(dfa_com1);
	dfa4.min_Watson();
	cout << "\n************min_Watson()\n" << std::flush;
	cout << dfa4 << endl;
	if (dfa4.Usefulf() == 0) {
		dfa4.usefulf();
		cout << "After delete unreach final states:" << dfa4 << endl;
	}

	cout << "\n************min_Brzozowski()****************\n";
	DFA dfa5(dfa_com1);
	dfa5.min_Brzozowski();
	cout << "\n************ min_Brzozowski()\n" << std::flush;
	cout << dfa5 << endl;
	if (dfa5.Usefulf() == 0) {
		dfa5.usefulf();
		cout << "After delete unreach final states:" << dfa5 << endl;
	}
}

//#define TO_FILE

void minDFATest()
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

	//minDFATest1();
	//minDFATest2();
	//minDFATest3();
	//minDFATest3_1();
	//minDFATest4();
	//minDFATest5();

	//minDFATest6(); // error, 非完全自动机，导致mini错误
	//minDFATest7();   //  把minDFATest6的DFA 增加一个sink, 成为complete DFA, mini结果正确。

	// minDFATest8();    // 全函数，有sink state, 每个状态一个等价类
	//minDFATest9(); // NoSink，但，它完全自动机，验证了eq.class {4，5},{6,7}

	//minDFATest10();

	
	//minDFATest11(); // 同TCT, 有Sink
	//minDFATest12(); // 无sink, 同上，应该是碰巧

	//minDFATest13();

	minDFATest14();

#ifdef TO_FILE
	// 恢复cout
	fs.close();
	std::cout.rdbuf(stream_buffer_cout);
#endif
}