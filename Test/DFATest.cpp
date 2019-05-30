#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include "DFA.h"
#include "FiniteAutomata.h"

using namespace std;


//  A.1(a) 与 A.1(b)
//  最小化功能测试
void DFATest1();

//  A.2(a) 与 A.2(b)
//  最小化功能测试
void DFATest2();

// A.3(a) 与 A.3(b)
// 最小化功能测试
void DFATest3();

// A.4(a) 与 A.4(b)
void DFATest4();

// A.5(a) 与 A.5(b)
void DFATest5();

// A.6(a)  含有开始不可达状态
void DFATest6();

// A.7(a)  含有开始不可达状态
void DFATest7();

// 此测试专门针对 Hopcroft 算法，验证构造完全自动机(数据为A.8 五个 DFA)
void DFATest8();

// A.9(a) 和 A.9(b)
void DFATest9();

// 老师给的一个含有开始不可达，并且是结束状态的例子
// 运行usefuls即可去除，测试结果表明，5个最小化算法均正确。
void aspecialDFA();

void DFATest()
{
	cout << "\n\n\n" << endl;
	cout << "##################################################################" << endl;
	cout << "###    Now Test the minimization algorithms in the class DFA   ###" << endl; 
	cout << "##################################################################" << endl;
	DFATest1();
	DFATest2();
	DFATest3();
	DFATest4();
	DFATest5();
	DFATest6();
	DFATest7();
	DFATest8();
	DFATest9();
	aspecialDFA();
}

//  A.1(a)与 A.1(b)
void DFATest1()
{
	/************************************************************/
	// 预期输出结果1： A.1(c)
	DFA_components dfa_comresult1;

	int i = 3;
	while (i--)
	{
		dfa_comresult1.Q.allocate();
	}

	// StateSet S  开始状态集
	dfa_comresult1.S.set_domain(dfa_comresult1.Q.size());
	dfa_comresult1.S.add(0);

	// StateSet F  结束状态集
	dfa_comresult1.F.set_domain(dfa_comresult1.Q.size());
	dfa_comresult1.F.add(1);

	dfa_comresult1.T.set_domain(dfa_comresult1.Q.size());
	dfa_comresult1.T.add_transition(0, '0', 0);
	dfa_comresult1.T.add_transition(0, '1', 1);
	dfa_comresult1.T.add_transition(1, '0', 1);
	dfa_comresult1.T.add_transition(1, '1', 2);
	dfa_comresult1.T.add_transition(2, '1', 2);//陷阱状态 2
	dfa_comresult1.T.add_transition(2, '0', 2);

	DFA dfares1(dfa_comresult1);
	stringstream ss1;
	ss1 << dfares1;
	FiniteAutomata result1(ss1.str());
	//cout << result1.FA() << endl;
	result1.perform("A-1-c.ADS");



	/************************************************************/
	// 预期输出结果2： A.1(d)
	DFA_components dfa_comresult2;

	i = 2;
	while (i--)
	{
		dfa_comresult2.Q.allocate();
	}

	// StateSet S  开始状态集
	dfa_comresult2.S.set_domain(dfa_comresult2.Q.size());
	dfa_comresult2.S.add(0);

	// StateSet F  结束状态集
	dfa_comresult2.F.set_domain(dfa_comresult2.Q.size());
	dfa_comresult2.F.add(1);

	dfa_comresult2.T.set_domain(dfa_comresult2.Q.size());
	dfa_comresult2.T.add_transition(0, '1', 1);
	dfa_comresult2.T.add_transition(0, '0', 0);
	dfa_comresult2.T.add_transition(1, '0', 1);

	DFA dfares2(dfa_comresult2);
	FiniteAutomata result2(dfares2);
	//cout << result2.FA() << endl;
	result2.perform("A-1-d.ADS");


	// 测试数据
	// A.1(a)  含有 sink 状态 q5
	{
		DFA_components dfa_com1;

		int i = 6;
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
		dfa_com1.F.add(3);
		dfa_com1.F.add(4);

		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 2);
		dfa_com1.T.add_transition(1, '1', 3);
		dfa_com1.T.add_transition(1, '0', 0);
		dfa_com1.T.add_transition(2, '0', 4);
		dfa_com1.T.add_transition(2, '1', 5);
		dfa_com1.T.add_transition(3, '0', 4);
		dfa_com1.T.add_transition(3, '1', 5);
		dfa_com1.T.add_transition(4, '0', 4);
		dfa_com1.T.add_transition(4, '1', 5);
		dfa_com1.T.add_transition(5, '0', 5);
		dfa_com1.T.add_transition(5, '1', 5);



		stringstream ss;
		/*string temp;*/
		FiniteAutomata temp;

		DFA dfa1;

		cout << "Now Test A.1(a) " << endl;
		dfa1.reconstruct(dfa_com1);
		ss << dfa1;
		temp.reconstruct(ss.str());
		ss.str("");
		//cout << temp << endl;
		//temp.perform("A-1-a.ADS");

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "original DFA" << dfa1;
		cout << "minimized by Brzozowski" << endl;
		dfa1.min_Brzozowski();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1 || temp == result2) << endl;
		//temp.perform("A-1-a-Brzozowski.ADS");
		ss.str("");
		temp.clear();


		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by Hopcroft" << endl;
		dfa1.min_Hopcroft();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1 || temp == result2) << endl;
		ss.str("");
		temp.clear();

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by HopcroftUllman" << endl;
		dfa1.min_HopcroftUllman();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1 || temp == result2) << endl;
		//temp.perform("A-1-a-HopcroftUllman.ADS");
		ss.str("");
		temp.clear();


		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by dragon" << endl;
		dfa1.min_dragon();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1 || temp == result2) << endl;
		//temp.perform("A-1-a-dragon.ADS");
		ss.str("");
		temp.clear();

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by Watson" << endl;
		dfa1.min_Watson();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1 || temp == result2) << endl;
		//temp.perform("A-1-a-Watson.ADS");
		ss.str("");
		temp.clear();
	}

	cout << "\n---------------------------------------------------------\n" << std::flush;

	// 测试数据
	// A.1(b)  
	{
		DFA_components dfa_com1;

		int i = 5;
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
		dfa_com1.F.add(3);
		dfa_com1.F.add(4);

		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 2);
		dfa_com1.T.add_transition(1, '1', 3);
		dfa_com1.T.add_transition(1, '0', 0);
		dfa_com1.T.add_transition(2, '0', 4);
		//dfa_com1.T.add_transition(2, '1', 5);
		dfa_com1.T.add_transition(3, '0', 4);
		//dfa_com1.T.add_transition(3, '1', 5);
		dfa_com1.T.add_transition(4, '0', 4);
		//dfa_com1.T.add_transition(4, '1', 5);
		//dfa_com1.T.add_transition(5, '0', 5);
		//dfa_com1.T.add_transition(5, '1', 5);



		stringstream ss;
		/*string temp;*/
		FiniteAutomata temp;

		DFA dfa1;

		cout << "Now Test A.1(b) " << endl;
		dfa1.reconstruct(dfa_com1);
		ss << dfa1;
		temp.reconstruct(ss.str());
		ss.str("");
		//temp.perform("A-1-b.ADS");

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "original DFA" << dfa1;
		cout << "minimized by Brzozowski" << endl;
		dfa1.min_Brzozowski();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1 || temp == result2) << endl;
		//temp.perform("A-1-b-Brzozowski.ADS");
		ss.str("");
		temp.clear();


		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by Hopcroft" << endl;
		dfa1.min_Hopcroft();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1 || temp == result2) << endl;
		//temp.perform("A-1-b-Hopcroft.ADS");
		ss.str("");
		temp.clear();

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by HopcroftUllman" << endl;
		dfa1.min_HopcroftUllman();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1 || temp == result2) << endl;
		//temp.perform("A-1-b-HopcroftUllman.ADS");
		ss.str("");
		temp.clear();


		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by dragon" << endl;
		dfa1.min_dragon();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1 || temp == result2) << endl;
		//temp.perform("A-1-b-dragon.ADS");
		ss.str("");
		temp.clear();

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by Watson" << endl;
		dfa1.min_Watson();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1 || temp == result2) << endl;
		//temp.perform("A-1-b-Watson.ADS");
		ss.str("");
		temp.clear();
	}

	cout << "\n---------------------------------------------------------\n" << std::flush;
}


//  A.1(a)与 A.1(b)
void DFATest2()
{
	/************************************************************/
	// A.2(a) 预期输出结果： A.2(c) 
	DFA_components dfa_comresult1;

	int i = 2;
	while (i--)
	{
		dfa_comresult1.Q.allocate();
	}

	// StateSet S  开始状态集
	dfa_comresult1.S.set_domain(dfa_comresult1.Q.size());
	dfa_comresult1.S.add(0);

	// StateSet F  结束状态集
	dfa_comresult1.F.set_domain(dfa_comresult1.Q.size());
	dfa_comresult1.F.add(1);

	// a:=0   b:=1
	dfa_comresult1.T.set_domain(dfa_comresult1.Q.size());
	dfa_comresult1.T.add_transition(0, '0', 1);
	dfa_comresult1.T.add_transition(0, '1', 1);
	dfa_comresult1.T.add_transition(1, '1', 1);
	dfa_comresult1.T.add_transition(1, '0', 1);

	DFA dfares1(dfa_comresult1);
	FiniteAutomata result1(dfares1);
	result1.perform("A-2-c.ADS");



	/************************************************************/
	// A.2(b) 预期输出结果 A.2(b)
	DFA_components dfa_comresult2;

	i = 3;
	while (i--)
	{
		dfa_comresult2.Q.allocate();
	}

	// StateSet S  开始状态集
	dfa_comresult2.S.set_domain(dfa_comresult2.Q.size());
	dfa_comresult2.S.add(0);

	// StateSet F  结束状态集
	dfa_comresult2.F.set_domain(dfa_comresult2.Q.size());
	dfa_comresult2.F.add(1);
	dfa_comresult2.F.add(2);

	// a:=0   b:=1
	dfa_comresult2.T.set_domain(dfa_comresult2.Q.size());
	dfa_comresult2.T.add_transition(0, '0', 1);
	dfa_comresult2.T.add_transition(0, '1', 2);
	dfa_comresult2.T.add_transition(1, '0', 2);
	dfa_comresult2.T.add_transition(2, '1', 1);

	DFA dfares2(dfa_comresult2);
	FiniteAutomata result2(dfares2);
	result2.perform("A-2-b.ADS");


	// 测试数据
	// A.2(a)  是一个可以被最小化的完全DFA，预期结果是 A.2(c)
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
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 2);
		dfa_com1.T.add_transition(1, '1', 1);
		dfa_com1.T.add_transition(1, '0', 2);
		dfa_com1.T.add_transition(2, '0', 2);
		dfa_com1.T.add_transition(2, '1', 1);



		stringstream ss;
		FiniteAutomata temp;

		DFA dfa1;

		cout << "Now Test A.2(a) " << endl;
		/*dfa1.reconstruct(dfa_com1);
		ss << dfa1;
		temp.reconstruct(ss.str());
		ss.str("");
		cout << temp.FA() << endl;
		temp.perform("A-2-a.ADS");*/

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "original DFA" << dfa1;
		cout << "minimized by Brzozowski" << endl;
		dfa1.min_Brzozowski();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1) << endl;
		//temp.perform("A-1-a-Brzozowski.ADS");
		ss.str("");
		temp.clear();


		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by Hopcroft" << endl;
		dfa1.min_Hopcroft();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1) << endl;
		ss.str("");
		temp.clear();

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by HopcroftUllman" << endl;
		dfa1.min_HopcroftUllman();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1) << endl;
		//temp.perform("A-1-a-HopcroftUllman.ADS");
		ss.str("");
		temp.clear();


		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by dragon" << endl;
		dfa1.min_dragon();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1) << endl;
		//temp.perform("A-1-a-dragon.ADS");
		ss.str("");
		temp.clear();

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by Watson" << endl;
		dfa1.min_Watson();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result1) << endl;
		//temp.perform("A-1-a-Watson.ADS");
		ss.str("");
		temp.clear();
	}

	cout << "\n---------------------------------------------------------\n" << std::flush;

	// 测试数据
	// A.2(b)  是一个最小的不完全 DFA  此例在 Hopcroft 算法中将输出错误结果
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
		dfa_com1.F.add(1);

		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 2);
		//dfa_com1.T.add_transition(1, '1', 1);
		dfa_com1.T.add_transition(1, '0', 2);
		//dfa_com1.T.add_transition(2, '0', 2);
		dfa_com1.T.add_transition(2, '1', 1);



		stringstream ss;
		/*string temp;*/
		FiniteAutomata temp;

		DFA dfa1;

		cout << "Now Test A.2(b) " << endl;

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "original DFA" << dfa1;
		cout << "minimized by Brzozowski" << endl;
		dfa1.min_Brzozowski();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result2) << endl;
		//temp.perform("A-2-a-Brzozowski.ADS");
		ss.str("");
		temp.clear();


		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by Hopcroft" << endl;
		dfa1.complete();
		dfa1.min_Hopcroft();
		dfa1.usefulf();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result2) << endl;
		//temp.perform("A-2-a-Hopcroft.ADS");
		ss.str("");
		temp.clear();

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by HopcroftUllman" << endl;
		dfa1.min_HopcroftUllman();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result2) << endl;
		//temp.perform("A-2-a-HopcroftUllman.ADS");
		ss.str("");
		temp.clear();


		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by dragon" << endl;
		dfa1.min_dragon();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result2) << endl;
		//temp.perform("A-2-a-dragon.ADS");
		ss.str("");
		temp.clear();

		//////////////////////////////////////////////////////////////////////////////
		dfa1.reconstruct(dfa_com1);
		cout << "---------------minimized by Watson" << endl;
		dfa1.min_Watson();
		ss << dfa1;
		temp.reconstruct(ss.str());
		cout << "anwser is right?:  " << (temp == result2) << endl;
		//temp.perform("A-2-a-Watson.ADS");
		ss.str("");
		temp.clear();
	}

	cout << "\n---------------------------------------------------------\n" << std::flush;
}


void DFATest3()
{
	{
		// A.3(a) 预期结果为 A.3(c)
		DFA_components dfa_com1;

		int i = 9;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(4);
		dfa_com1.F.add(8);

		// 转移关系
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 5);
		dfa_com1.T.add_transition(1, '1', 2);
		dfa_com1.T.add_transition(5, '1', 6);
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(6, '0', 7);
		dfa_com1.T.add_transition(3, '1', 4);
		dfa_com1.T.add_transition(7, '1', 8);
		dfa_com1.T.add_transition(4, '1', 4);
		dfa_com1.T.add_transition(4, '0', 8);
		dfa_com1.T.add_transition(8, '0', 8);
		dfa_com1.T.add_transition(8, '1', 4);

		cout << "#####################################################" << endl;
		cout << "Now test A.3(a), respect anwser A.3(c)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
	}

	{
		// A.3(b) 预期结果为 A.3(b)
		DFA_components dfa_com1;

		int i = 9;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(4);
		dfa_com1.F.add(8);

		// 转移关系
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 5);
		dfa_com1.T.add_transition(1, '1', 2);
		dfa_com1.T.add_transition(5, '1', 6);
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(6, '0', 7);
		dfa_com1.T.add_transition(3, '1', 4);
		dfa_com1.T.add_transition(7, '1', 8);
		//dfa_com1.T.add_transition(4, '1', 4);
		dfa_com1.T.add_transition(4, '0', 8);
		//dfa_com1.T.add_transition(8, '0', 8);
		dfa_com1.T.add_transition(8, '1', 4);

		cout << "#####################################################" << endl;
		cout << "Now test A.3(b), respect anwser A.3(b)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
	}

}

void DFATest4()
{
	{
		// A.4(a) (完全自动机) 预期结果为 A.4(c)
		DFA_components dfa_com1;

		int i = 7;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(3);
		dfa_com1.F.add(6);
		dfa_com1.F.add(2);
		dfa_com1.F.add(5);

		// 转移关系  a=0  b=1
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 4);
		dfa_com1.T.add_transition(1, '1', 4);
		dfa_com1.T.add_transition(1, '0', 2);
		dfa_com1.T.add_transition(2, '0', 2);
		dfa_com1.T.add_transition(2, '1', 3);
		dfa_com1.T.add_transition(3, '0', 6);
		dfa_com1.T.add_transition(3, '1', 3);
		dfa_com1.T.add_transition(4, '0', 1);
		dfa_com1.T.add_transition(4, '1', 5);
		dfa_com1.T.add_transition(5, '0', 6);
		dfa_com1.T.add_transition(5, '1', 5);
		dfa_com1.T.add_transition(6, '0', 2);
		dfa_com1.T.add_transition(6, '1', 3);

		cout << "#####################################################" << endl;
		cout << "Now test A.4(a), respect anwser A.4(c)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
	}

	{
		// A.4(b) 预期结果为 A.4(b)
		DFA_components dfa_com1;

		int i = 7;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(3);
		dfa_com1.F.add(6);
		dfa_com1.F.add(2);
		dfa_com1.F.add(5);

		// 转移关系  a=0  b=1
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 4);
		dfa_com1.T.add_transition(1, '1', 4);
		dfa_com1.T.add_transition(1, '0', 2);
		dfa_com1.T.add_transition(2, '0', 2);
		dfa_com1.T.add_transition(2, '1', 3);
		dfa_com1.T.add_transition(3, '0', 6);
		//dfa_com1.T.add_transition(3, '1', 3);
		dfa_com1.T.add_transition(4, '0', 1);
		dfa_com1.T.add_transition(4, '1', 5);
		dfa_com1.T.add_transition(5, '0', 6);
		dfa_com1.T.add_transition(5, '1', 5);
		dfa_com1.T.add_transition(6, '0', 2);
		dfa_com1.T.add_transition(6, '1', 3);

		cout << "#####################################################" << endl;
		cout << "Now test A.4(b), respect anwser A.4(b)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;

		/*FiniteAutomata ffa;
		ffa.perform(dfa1, "A-4-b-min-hopcroft.ADS");*/
	}

}

// usefulf 测试
// 不改变最小的 DFA 测试
void DFATest5()
{
	{
		// A.5(a) (完全自动机) 预期结果为 A.5(a) 或 A.5(b)
		DFA_components dfa_com1;

		int i = 4;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(3);

		// 转移关系  
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 2);
		dfa_com1.T.add_transition(0, '1', 1);
		dfa_com1.T.add_transition(2, '1', 1);
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(3, '0', 3);
		dfa_com1.T.add_transition(3, '1', 1);

		cout << "#####################################################" << endl;
		cout << "Now test A.5(a)(with sink), respect anwser A.5(a) or A.5(b)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------usefulf function" << dfa1.usefulf() << endl;
	}

	{
		// A.5(b) (完全自动机) 预期结果为 A.5(b)
		DFA_components dfa_com1;

		int i = 4;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(3);

		// 转移关系  
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 2);
		//dfa_com1.T.add_transition(0, '1', 1);
		//dfa_com1.T.add_transition(2, '1', 1);
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(3, '0', 3);
		//dfa_com1.T.add_transition(3, '1', 1);

		cout << "#####################################################" << endl;
		cout << "Now test A.5(a)(with sink), respect anwser A.5(a) or A.5(b)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
	}
}


void DFATest6()
{
	{
		// A.6(a) (最小的DFA，含有开始不可达状态) 预期结果为 A.6(a) 或 A.6(b) 
		DFA_components dfa_com1;

		int i = 5;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(4);

		// 转移关系  
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 0);
		dfa_com1.T.add_transition(1, '0', 0); // 开始不可达状态
		dfa_com1.T.add_transition(1, '1', 3); // 开始不可达状态
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(2, '1', 0);
		dfa_com1.T.add_transition(3, '0', 4);
		dfa_com1.T.add_transition(3, '1', 0);
		dfa_com1.T.add_transition(4, '0', 4);
		dfa_com1.T.add_transition(4, '1', 0);

		cout << "#####################################################" << endl;
		cout << "Now test A.6(a)(with start-unreachable), respect anwser A.6(a) or A.6(b)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
		
		dfa1.reconstruct(dfa_com1);
		cout << "------------usefuls function" << dfa1.usefuls() << endl;
	}
}


void DFATest7()
{
	{
		// A.7(a) (最小的DFA，含有开始不可达状态) 预期结果为 A.7(a) 或 A.7(b) 
		DFA_components dfa_com1;

		int i = 6;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(4);
		dfa_com1.F.add(3);

		// 转移关系  
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 0);
		dfa_com1.T.add_transition(1, '0', 2); 
		dfa_com1.T.add_transition(1, '1', 0); 
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(2, '1', 4);
		dfa_com1.T.add_transition(3, '0', 0);
		dfa_com1.T.add_transition(3, '1', 4);
		dfa_com1.T.add_transition(4, '0', 1);
		dfa_com1.T.add_transition(4, '1', 0);
		dfa_com1.T.add_transition(5, '0', 3);
		dfa_com1.T.add_transition(5, '1', 1);

		cout << "#####################################################" << endl;
		cout << "Now test A.7(a)(with start-unreachable), respect anwser A.7(a) or A.7(b)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------usefuls function" << dfa1.usefuls() << endl;
	}
}

// 此测试专门针对 Hopcroft，验证构造完全自动机的算法的正确性
void DFATest8()
{
	{
		// A.8(a) (最小的DFA) 预期结果为 A.8(a)
		DFA_components dfa_com1;

		int i = 5;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(4);
		dfa_com1.F.add(3);
		dfa_com1.F.add(2);

		// 转移关系  a=0 b=1
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 2);
		dfa_com1.T.add_transition(1, '0', 3);
		dfa_com1.T.add_transition(2, '1', 3);
		dfa_com1.T.add_transition(3, '1', 4);

		cout << "#####################################################" << endl;
		cout << "******* test the new function: complete" << endl;
		cout << "Now test A.8(a)(with start-unreachable), respect anwser A.8(a)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------after complete " << dfa1.complete() << endl;
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
		cout << "------------after usefulf " << dfa1.usefulf() << endl;
	}

	{
		// A.8(b) (最小的DFA) 预期结果为 A.8(b)
		DFA_components dfa_com1;

		int i = 3;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(2);
		dfa_com1.F.add(1);

		// 转移关系  a=0 b=1
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 2);
		dfa_com1.T.add_transition(1, '1', 2);
		dfa_com1.T.add_transition(2, '0', 1);

		cout << "#####################################################" << endl;
		cout << "******* test the new function: complete" << endl;
		cout << "Now test A.8(b), respect anwser A.8(b)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------after complete " << dfa1.complete() << endl;
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
		cout << "------------after usefulf " << dfa1.usefulf() << endl;
	}

	{
		// A.8(c) (最小的DFA) 预期结果为 A.8(c)
		DFA_components dfa_com1;

		int i = 4;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(3);

		// 转移关系  a=0 b=1
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(1, '1', 2);
		dfa_com1.T.add_transition(2, '0', 3);

		cout << "#####################################################" << endl;
		cout << "******* test the new function: complete" << endl;
		cout << "Now test A.8(c), respect anwser A.8(c)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------after complete " << dfa1.complete() << endl;
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
		cout << "------------after usefulf " << dfa1.usefulf() << endl;
	}

	{
		// A.8(d) (最小的DFA) 预期结果为 A.8(d)
		DFA_components dfa_com1;

		int i = 5;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(3);
		dfa_com1.F.add(4);
		dfa_com1.F.add(2);

		// 转移关系  a=0 b=1
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(1, '1', 2);
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(3, '1', 4);

		cout << "#####################################################" << endl;
		cout << "******* test the new function: complete" << endl;
		cout << "Now test A.8(d), respect anwser A.8(d)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------after complete " << dfa1.complete() << endl;
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
		cout << "------------after usefulf " << dfa1.usefulf() << endl;
	}

	{
		// A.8(d) (最小的DFA) 预期结果为 A.8(d)
		DFA_components dfa_com1;

		int i = 5;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(3);
		dfa_com1.F.add(4);

		// 转移关系  a=0 b=1
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(1, '1', 2);
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(3, '1', 4);

		cout << "#####################################################" << endl;
		cout << "******* test the new function: complete" << endl;
		cout << "Now test A.8(e), respect anwser A.8(e)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------after complete " << dfa1.complete() << endl;
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
		cout << "------------after usefulf " << dfa1.usefulf() << endl;
	}
}


void DFATest9()
{
	{
		// A.9(a) (最小的DFA，含有开始不可达状态) 预期结果为 A.9(a) 或 A.9(b) 
		// 此例导致 Brzozowski 算法错误
		DFA_components dfa_com1;

		int i = 10;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(4);
		dfa_com1.F.add(8);

		// 转移关系  
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 5);
		dfa_com1.T.add_transition(1, '1', 2);
		dfa_com1.T.add_transition(1, '0', 5);
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(2, '1', 6);
		dfa_com1.T.add_transition(3, '0', 2);
		dfa_com1.T.add_transition(3, '1', 4);
		dfa_com1.T.add_transition(4, '0', 8);
		dfa_com1.T.add_transition(4, '1', 1);
		dfa_com1.T.add_transition(5, '0', 1);
		dfa_com1.T.add_transition(5, '1', 6);
		dfa_com1.T.add_transition(6, '1', 2);
		dfa_com1.T.add_transition(6, '0', 7);
		dfa_com1.T.add_transition(7, '1', 8);
		dfa_com1.T.add_transition(7, '0', 6);
		dfa_com1.T.add_transition(8, '1', 4);
		dfa_com1.T.add_transition(8, '0', 5);
		dfa_com1.T.add_transition(9, '0', 7);
		dfa_com1.T.add_transition(9, '1', 5);

		cout << "#####################################################" << endl;
		cout << "Now test A.9(a)(with start-unreachable), respect anwser A.9(a) or A.9(b)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------after usefuls" << dfa1.usefuls() << endl;
	}

	{
		// A.9(b) (最小的DFA，不含开始不可达状态) 预期结果为 A.9(b)
		// 此例导致 Brzozowski 算法错误
		DFA_components dfa_com1;

		int i = 9;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(4);
		dfa_com1.F.add(8);

		// 转移关系  
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 5);
		dfa_com1.T.add_transition(1, '1', 2);
		dfa_com1.T.add_transition(1, '0', 5);
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(2, '1', 6);
		dfa_com1.T.add_transition(3, '0', 2);
		dfa_com1.T.add_transition(3, '1', 4);
		dfa_com1.T.add_transition(4, '0', 8);
		dfa_com1.T.add_transition(4, '1', 1);
		dfa_com1.T.add_transition(5, '0', 1);
		dfa_com1.T.add_transition(5, '1', 6);
		dfa_com1.T.add_transition(6, '1', 2);
		dfa_com1.T.add_transition(6, '0', 7);
		dfa_com1.T.add_transition(7, '1', 8);
		dfa_com1.T.add_transition(7, '0', 6);
		dfa_com1.T.add_transition(8, '1', 4);
		dfa_com1.T.add_transition(8, '0', 5);
		//dfa_com1.T.add_transition(9, '0', 7);
		//dfa_com1.T.add_transition(9, '1', 5);

		cout << "#####################################################" << endl;
		cout << "Now test A.9(b), respect anwser A.9(b)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;
	}

	{
		// A.9(c) (最小的DFA) 预期结果为 A.9(c) 
		// 此例下 Brzozowski 算法正确
		DFA_components dfa_com1;

		int i = 10;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		// 开始状态集
		dfa_com1.S.set_domain(dfa_com1.Q.size());
		dfa_com1.S.add(0);

		// 结束状态集
		dfa_com1.F.set_domain(dfa_com1.Q.size());
		dfa_com1.F.add(4);
		dfa_com1.F.add(8);

		// 转移关系  
		dfa_com1.T.set_domain(dfa_com1.Q.size());
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 5);
		dfa_com1.T.add_transition(1, '1', 2);
		dfa_com1.T.add_transition(1, '0', 5);
		dfa_com1.T.add_transition(2, '0', 3);
		dfa_com1.T.add_transition(2, '1', 6);
		//dfa_com1.T.add_transition(3, '0', 2);
		dfa_com1.T.add_transition(3, '1', 4);
		dfa_com1.T.add_transition(4, '0', 8);
		//dfa_com1.T.add_transition(4, '1', 1);
		dfa_com1.T.add_transition(5, '0', 1);
		dfa_com1.T.add_transition(5, '1', 6);
		dfa_com1.T.add_transition(6, '1', 2);
		dfa_com1.T.add_transition(6, '0', 7);
		dfa_com1.T.add_transition(7, '1', 8);
		//dfa_com1.T.add_transition(7, '0', 6);
		dfa_com1.T.add_transition(8, '1', 4);
		//dfa_com1.T.add_transition(8, '0', 5);
		dfa_com1.T.add_transition(9, '0', 7);
		dfa_com1.T.add_transition(9, '1', 5);

		cout << "#####################################################" << endl;
		cout << "Now test A.9(c)(with start-unreachable), respect anwser A.9(c)" << endl;
		DFA dfa1;

		dfa1.reconstruct(dfa_com1);
		cout << "original DFA\n" << dfa1 << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Brzozowski" << dfa1.min_Brzozowski() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by dragon" << dfa1.min_dragon() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by HopcroftUllman" << dfa1.min_HopcroftUllman() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Watson" << dfa1.min_Watson() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------min by Hopcroft" << dfa1.min_Hopcroft() << endl;

		dfa1.reconstruct(dfa_com1);
		cout << "------------after usefuls" << dfa1.usefuls() << endl;
	}
}

//此例是含有一个开始不可达的结束状态。
void aspecialDFA()
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
	cout << "original DFA :" << endl;
	cout << dfa1 << endl;

	dfa1.usefuls();  // 
	cout << "after usefuls " << dfa1 << endl;
	dfa1.complete();
	cout << "after complete " << dfa1 << endl;

	dfa1.min_Hopcroft();
	cout << "\n************ minDFA\n" << std::flush;
	cout << dfa1 << endl;
}


//  A.3(a)与 A.3(b)
//void DFATest3()
//{
//	/************************************************************/
//	// A.3(a) 预期输出结果： A.3(c) 
//	DFA_components dfa_comresult1;
//
//	int i = 5;
//	while (i--)
//	{
//		dfa_comresult1.Q.allocate();
//	}
//
//	// StateSet S  开始状态集
//	dfa_comresult1.S.set_domain(dfa_comresult1.Q.size());
//	dfa_comresult1.S.add(0);
//
//	// StateSet F  结束状态集
//	dfa_comresult1.F.set_domain(dfa_comresult1.Q.size());
//	dfa_comresult1.F.add(4);
//
//	// a:=0   b:=1
//	dfa_comresult1.T.set_domain(dfa_comresult1.Q.size());
//	dfa_comresult1.T.add_transition(0, '0', 1);
//	dfa_comresult1.T.add_transition(0, '1', 1);
//	dfa_comresult1.T.add_transition(1, '1', 2);
//	dfa_comresult1.T.add_transition(2, '0', 3);
//	dfa_comresult1.T.add_transition(3, '1', 4);
//	dfa_comresult1.T.add_transition(4, '0', 4);
//	dfa_comresult1.T.add_transition(4, '1', 4);
//
//	DFA dfares1(dfa_comresult1);
//	FiniteAutomata result1(dfares1);
//	cout << result1.FA() << endl;
//	result1.perform("A-3-c.ADS");
//
//
//
//	/************************************************************/
//	// A.3(b) 预期输出结果 A.3(b)
//	DFA_components dfa_comresult2;
//
//	i = 9;
//	while (i--)
//	{
//		dfa_comresult2.Q.allocate();
//	}
//
//	// StateSet S  开始状态集
//	dfa_comresult2.S.set_domain(dfa_comresult2.Q.size());
//	dfa_comresult2.S.add(0);
//
//	// StateSet F  结束状态集
//	dfa_comresult2.F.set_domain(dfa_comresult2.Q.size());
//	dfa_comresult2.F.add(4);
//	dfa_comresult2.F.add(8);
//
//	// a:=0   b:=1
//	dfa_comresult2.T.set_domain(dfa_comresult2.Q.size());
//	dfa_comresult2.T.add_transition(0, '0', 1);
//	dfa_comresult2.T.add_transition(0, '1', 5);
//	dfa_comresult2.T.add_transition(1, '1', 2);
//	dfa_comresult2.T.add_transition(5, '1', 6);
//	dfa_comresult2.T.add_transition(2, '0', 3);
//	dfa_comresult2.T.add_transition(6, '0', 7);
//	dfa_comresult2.T.add_transition(3, '1', 4);
//	dfa_comresult2.T.add_transition(7, '1', 8);
//	dfa_comresult2.T.add_transition(4, '0', 8);
//	dfa_comresult2.T.add_transition(8, '1', 4);
//
//	DFA dfares2(dfa_comresult2);
//	FiniteAutomata result2(dfares2);
//	cout << result2.FA() << endl;
//	result2.perform("A-3-b.ADS");
//
//
//	// 测试数据
//	// A.3(a)  是一个可以被最小化的完全DFA，预期结果是 A.3(c)
//	{
//		DFA_components dfa_com1;
//
//		int i = 9;
//		while (i--)
//		{
//			dfa_com1.Q.allocate();
//		}
//
//		// StateSet S  开始状态集
//		dfa_com1.S.set_domain(dfa_com1.Q.size());
//		dfa_com1.S.add(0);
//
//		// StateSet F  结束状态集
//		dfa_com1.F.set_domain(dfa_com1.Q.size());
//		dfa_com1.F.add(1);
//		dfa_com1.F.add(2);
//
//		dfa_com1.T.set_domain(dfa_com1.Q.size());
//		dfa_com1.T.add_transition(0, '0', 1);
//		dfa_com1.T.add_transition(0, '1', 5);
//		dfa_com1.T.add_transition(1, '1', 2);
//		dfa_com1.T.add_transition(5, '1', 6);
//		dfa_com1.T.add_transition(2, '0', 3);
//		dfa_com1.T.add_transition(6, '0', 7);
//		dfa_com1.T.add_transition(3, '1', 4);
//		dfa_com1.T.add_transition(7, '1', 8);
//		dfa_com1.T.add_transition(4, '0', 8);
//		dfa_com1.T.add_transition(8, '0', 8);
//		dfa_com1.T.add_transition(8, '1', 4);
//		dfa_com1.T.add_transition(4, '1', 4);
//
//
//
//		stringstream ss;
//		FiniteAutomata temp;
//
//		DFA dfa1;
//
//		cout << "Now Test A.2(a) " << endl;
//		/*dfa1.reconstruct(dfa_com1);
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		ss.str("");
//		cout << temp.FA() << endl;
//		temp.perform("A-2-a.ADS");*/
//
//		//////////////////////////////////////////////////////////////////////////////
//		dfa1.reconstruct(dfa_com1);
//		cout << "original DFA" << dfa1;
//		cout << "minimized by Brzozowski" << endl;
//		dfa1.min_Brzozowski();
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		cout << temp.FA() << endl;
//		cout << "anwser is right?:  " << (temp == result1) << endl;
//		//temp.perform("A-1-a-Brzozowski.ADS");
//		ss.str("");
//		temp.clear();
//
//
//		//////////////////////////////////////////////////////////////////////////////
//		dfa1.reconstruct(dfa_com1);
//		cout << "---------------minimized by Hopcroft" << endl;
//		dfa1.min_Hopcroft();
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		cout << temp.FA() << endl;
//		cout << "anwser is right?:  " << (temp == result1) << endl;
//		ss.str("");
//		temp.clear();
//
//		//////////////////////////////////////////////////////////////////////////////
//		dfa1.reconstruct(dfa_com1);
//		cout << "---------------minimized by HopcroftUllman" << endl;
//		dfa1.min_HopcroftUllman();
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		cout << temp.FA() << endl;
//		cout << "anwser is right?:  " << (temp == result1) << endl;
//		//temp.perform("A-1-a-HopcroftUllman.ADS");
//		ss.str("");
//		temp.clear();
//
//
//		//////////////////////////////////////////////////////////////////////////////
//		dfa1.reconstruct(dfa_com1);
//		cout << "---------------minimized by dragon" << endl;
//		dfa1.min_dragon();
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		cout << temp.FA() << endl;
//		cout << "anwser is right?:  " << (temp == result1) << endl;
//		//temp.perform("A-1-a-dragon.ADS");
//		ss.str("");
//		temp.clear();
//
//		//////////////////////////////////////////////////////////////////////////////
//		dfa1.reconstruct(dfa_com1);
//		cout << "---------------minimized by Watson" << endl;
//		dfa1.min_Watson();
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		cout << temp.FA() << endl;
//		cout << "anwser is right?:  " << (temp == result1) << endl;
//		//temp.perform("A-1-a-Watson.ADS");
//		ss.str("");
//		temp.clear();
//	}
//
//	cout << "\n---------------------------------------------------------\n" << std::flush;
//
//	// 测试数据
//	// A.3(b)  是一个最小的不完全 DFA ，预期结果为它自己。
//	{
//		DFA_components dfa_com1;
//
//		int i = 3;
//		while (i--)
//		{
//			dfa_com1.Q.allocate();
//		}
//
//		// StateSet S  开始状态集
//		dfa_com1.S.set_domain(dfa_com1.Q.size());
//		dfa_com1.S.add(0);
//
//		// StateSet F  结束状态集
//		dfa_com1.F.set_domain(dfa_com1.Q.size());
//		dfa_com1.F.add(2);
//		dfa_com1.F.add(1);
//
//		dfa_com1.T.set_domain(dfa_com1.Q.size());
//		dfa_com1.T.add_transition(0, '0', 1);
//		dfa_com1.T.add_transition(0, '1', 5);
//		dfa_com1.T.add_transition(1, '1', 2);
//		dfa_com1.T.add_transition(5, '1', 6);
//		dfa_com1.T.add_transition(2, '0', 3);
//		dfa_com1.T.add_transition(6, '0', 7);
//		dfa_com1.T.add_transition(3, '1', 4);
//		dfa_com1.T.add_transition(7, '1', 8);
//		dfa_com1.T.add_transition(4, '0', 8);
//		dfa_com1.T.add_transition(8, '0', 8);
//		dfa_com1.T.add_transition(8, '1', 4);
//		dfa_com1.T.add_transition(4, '1', 4);
//
//
//
//		stringstream ss;
//		/*string temp;*/
//		FiniteAutomata temp;
//
//		DFA dfa1;
//
//		cout << "Now Test A.2(b) " << endl;
//
//		//////////////////////////////////////////////////////////////////////////////
//		dfa1.reconstruct(dfa_com1);
//		cout << "original DFA" << dfa1;
//		cout << "minimized by Brzozowski" << endl;
//		dfa1.min_Brzozowski();
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		cout << temp.FA() << endl;
//		cout << "anwser is right?:  " << (temp == result2) << endl;
//		//temp.perform("A-2-a-Brzozowski.ADS");
//		ss.str("");
//		temp.clear();
//
//
//		//////////////////////////////////////////////////////////////////////////////
//		dfa1.reconstruct(dfa_com1);
//		cout << "---------------minimized by Hopcroft" << endl;
//		dfa1.complete();
//		dfa1.min_Hopcroft();
//		dfa1.usefulf();
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		cout << temp.FA() << endl;
//		cout << "anwser is right?:  " << (temp == result2) << endl;
//		//temp.perform("A-2-a-Hopcroft.ADS");
//		ss.str("");
//		temp.clear();
//
//		//////////////////////////////////////////////////////////////////////////////
//		dfa1.reconstruct(dfa_com1);
//		cout << "---------------minimized by HopcroftUllman" << endl;
//		dfa1.min_HopcroftUllman();
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		cout << temp.FA() << endl;
//		cout << "anwser is right?:  " << (temp == result2) << endl;
//		//temp.perform("A-2-a-HopcroftUllman.ADS");
//		ss.str("");
//		temp.clear();
//
//
//		//////////////////////////////////////////////////////////////////////////////
//		dfa1.reconstruct(dfa_com1);
//		cout << "---------------minimized by dragon" << endl;
//		dfa1.min_dragon();
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		cout << temp.FA() << endl;
//		cout << "anwser is right?:  " << (temp == result2) << endl;
//		//temp.perform("A-2-a-dragon.ADS");
//		ss.str("");
//		temp.clear();
//
//		//////////////////////////////////////////////////////////////////////////////
//		dfa1.reconstruct(dfa_com1);
//		cout << "---------------minimized by Watson" << endl;
//		dfa1.min_Watson();
//		ss << dfa1;
//		temp.reconstruct(ss.str());
//		cout << temp.FA() << endl;
//		cout << "anwser is right?:  " << (temp == result2) << endl;
//		//temp.perform("A-2-a-Watson.ADS");
//		ss.str("");
//		temp.clear();
//	}
//
//	cout << "\n---------------------------------------------------------\n" << std::flush;
//}
