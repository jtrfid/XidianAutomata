#include<iostream>
#include"Trans.h"

using namespace std;

class TransTestClass_New
{
public:
	TransTestClass_New()
	{
		cout << "**********************" << endl;
		cout << "      TransTest" << endl;
		cout << "**********************" << endl;
	}

	/******************************************
					SetRangeTest
	测试函数:
	1.void set_range(const int r)	设置状态数
	2.int range() const				输出状态数
	******************************************/
	void SetRangeTest()
	{
		Trans t;
		t.set_range(5);

		cout << "t range: " << t.range() << endl;//5
	}

	/********************************************************************
								AddTransTest
	测试函数:
	1.Trans& add_transition(const CharRange a, const State q)	添加变换V x Q
	********************************************************************/
	void AddTransTest()
	{
		Trans t;
		CharRange c('a','c');

		t.set_range(5);

		t.add_transition('a', 0);
		t.add_transition('b', 0);
		t.add_transition(c, 1);

		cout << "t: " << t << endl;//{['a','b']->0 ['a','c']->1}
	}

	/*****************************************************************************************
										 CheckTransTest
	测试函数:
	1.CRSet labels_into(const StateSet& r) const			*this中进入StateSet r的labels
	2.CRSet out_labels() const								*this中所有Transitions
	3.StateSet range_transition(const CharRange a) const	与transition a有联系的StateSet
	4.StateSet operator[](const char a) const				功能同上
	*****************************************************************************************/
	void CheckTransTest()
	{
		Trans t;
		CharRange c('b','c');

		t.set_range(5);

		t.add_transition('a', 0);
		t.add_transition('a', 1);
		t.add_transition('b', 1);
		t.add_transition('b', 3);
		t.add_transition('c', 1);

		cout << "t: " << t << endl;//{'a'->0  ['a','c']->1 'b'->3}

		StateSet s1,s2;

		s1.set_domain(5);
		s1.add(0);
		s2.set_domain(5);
		s2.add(1);

		//此处s1 domain设置不能小于*this range
		cout << "labels into 0: " << t.labels_into(s1) << endl;//{'a'}
		cout << "labels into 1: " << t.labels_into(s2) << endl;//{['a','c']}
		cout << "what are all the transition(s): " << t.out_labels() << endl;//{'a','b','c'}
		cout << "what are all the State(s) corresponds with Transition Range ['b','c']: " << t.range_transition(c) << endl;//{1}
		cout << "Again,using function operator[]('a'): " << t.operator[]('a') << endl;//{0,1}
	}

	/**************************************************************************
									 UnionTest
	测试函数:
	1.Trans& set_union(const Trans& r)	合并两Trans集，range必须相同且不相加
	**************************************************************************/
	void UnionTest()
	{
		Trans t1, t2;
		CharRange c('a', 'c');

		t1.set_range(5);
		t2.set_range(5);//t1 t2 range必须相同

		t1.add_transition('a', 0);
		t1.add_transition('b', 0);
		t1.add_transition(c, 1);
		t2.add_transition('d', 4);
		t2.add_transition('c', 3);

		cout << "t1: " << t1 << endl;//{['a','b']->0 ['a','c']->1}
		cout << "t2: " << t2 << endl;//{'d'->4 'c'->3}
		cout << "t1 unions with t2: " << t1.set_union(t2) << endl;//{['a','b']->0 ['a','c']->1 'd'->4 'c'->3}
	}

	/**************************************************************************************
										Disjointing_UnionTest
	测试函数:
	1.Trans& disjointing_union(const Trans& r)	合并两Trans集，range可以同且相加
	**************************************************************************************/
	void Disjointing_UnionTest()
	{
		Trans t1, t2, t3;
		CharRange c('a', 'c');

		t1.set_range(5);
		t2.set_range(5);
		t3.set_range(8);

		t1.add_transition('a', 0);
		t1.add_transition('b', 0);
		t1.add_transition(c, 1);
		t2.add_transition('d', 4);
		t2.add_transition('c', 3);
		t3.add_transition('a', 1);
		t3.add_transition('b', 5);

		cout << "t1: " << t1 << endl;//{['a','b']->0 ['a','c']->1}
		cout << "t1 range: " << t1.range() << endl;//5
		cout << "t2: " << t2 << endl;//{'d'->4 'c'->3}
		cout << "t2 range: " << t2.range() << endl;//5
		cout << "t3: " << t3 << endl;//{'a'->1 'b'->5}
		cout << "t3 range: " << t3.range() << endl;//8

		cout << "t1 disjointing_unions with t2: " << t1.disjointing_union(t2) << endl;//{['a','b']->0 ['a','c']->1 'd'->9 'c'->8}
		cout << "now t1 range: " << t1.range() << endl;//10
		cout << "t2 disjointing_unions with t3: " << t2.disjointing_union(t3) << endl;//{'d'->4 'c'->3 'a'->6 'b'->10}
		cout << "now t2 range: " << t2.range() << endl;//13
	}

	/****************************************************
							RenameTest
	测试函数:
	1.Trans& st_rename(const int r)	
	****************************************************/
	void RenameTest()
	{
		Trans t;

		t.set_range(5);

		t.add_transition('a', 0);
		t.add_transition('b', 0);

		cout << "t: " << t << endl;//{['a','b']->0}
		cout << "Rename all states such that none of them fall into the range[0,5): " << t.st_rename(5) << endl;//{['a','b']->5}
		cout << "now t range: " << t.range() << endl;//10
	}

	/***********************************************
					  AssignmentTest
	测试函数:
	1.Trans& operator=(const Trans& r) *this = r
	***********************************************/
	void AssignmentTest()
	{
		Trans t1, t2;

		t1.set_range(5);
		t2.set_range(6);

		t1.add_transition('a', 0);
		t1.add_transition('b', 0);
		t2.add_transition('d', 4);
		t2.add_transition('c', 3);

		cout << "t1: " << t1 << endl;//{['a','b']->0}
		cout << "t1 range: " << t1.range() << endl;//5
		cout << "t2: " << t2 << endl;//{'d'->4 'c'->3}
		cout << "t2 range: " << t2.range() << endl;//6
		cout << "let t1 = t2: " << t1.operator=(t2) << endl;//{['a','b']->0}
		cout << "now t1 range: " << t1.range() << endl;//6
	}

	/************************************************
					 ReincarnateTest
	测试函数:
	1.void reincarnate() 回收*this，但不会清空range
	************************************************/
	void ReincarnateTest()
	{
		Trans t;

		t.set_range(5);

		t.add_transition('a', 0);
		t.add_transition('b', 0);

		cout << "t: " << t << endl;//{['a','b']->0}
		cout << "t range: " << t.range() << endl;//5
		cout << "reincarnate t..." << endl;
		t.reincarnate();
		cout << "now t = " << t << endl;//{}
		cout << "now t range: " << t.range() << endl;//5
	}
};

void TransTest_New()
{
	TransTestClass_New t;
	t.SetRangeTest();
	t.AddTransTest();
	t.CheckTransTest();
	t.UnionTest();
	t.Disjointing_UnionTest();
	t.RenameTest();
	t.AssignmentTest();
	t.ReincarnateTest();
}