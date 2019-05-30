#include<iostream>
#include"StateSet.h"

using namespace std;

class StateSetTest_NewClass
{
public:
	/**************************************************
				  分配及检查分配状态数测试
	测试函数：
	1.set_domain(const int r)   为一个StateSet类分配大小为r的状态池
	2.domain()                  返回分配的状态数
	**************************************************/
	void AllocatingTest()
	{
		cout << "AllocatingTest:" << endl;
		StateSet s;
		s.set_domain(5);

		cout << "domain:" << s.domain() << endl;
	}

	/************************************************
					添加/去除状态测试
	测试函数:
	1.add(const State r)          添加状态r
	2.remove(const State r)       移除状态r
	3.remove(const StateSet& r)   移除StateSet r中包含的状态
	*************************************************/
	void Add_RemoveTest()
	{
		StateSet s1, s2;

		s1.set_domain(5);
		s2.set_domain(5);

		s1.add(0);
		s1.add(1);
		s2.add(0);

		cout << "s1=" << s1 << endl;
		cout << "s2=" << s2 << endl;
		s1.remove(1);
		cout << "s1 remove 1 =" << s1 << endl;
		s1.remove(s2);
		cout << "s1 remove s2 =" << s1 << endl;
	}

	/***********************************************************
							检查状态测试
	测试函数:
	1.empty()                      添加状态与否
	2.size()				       添加状态数目
	3.contains(state r)            是否添加了状态r
	4.contains(StateSet &r)		   添加的状态是否包含StateSet r中添加的状态
	5.not_disjoint(StateSet &r)    *this与r是否有相交（状态编号相同）的状态
	***********************************************************/
	void CheckStateTest()
	{
		cout << "CheckStateTest" << endl;
		StateSet s1, s2, s3, s4;

		s1.set_domain(5);
		s2.set_domain(5);
		s3.set_domain(5);
		s4.set_domain(5);

		s1.add(0).add(1).add(2);
		s2.add(0).add(1);
		s4.add(2).add(3);

		cout << "s1=" << s1 << endl;//{0,1,2}
		cout << "s2=" << s2 << endl;//{0,1}
		cout << "s3=" << s3 << endl;//{}
		cout << "s4=" << s4 << endl;//{2,3}

		cout << "s1 is empty? " << s1.empty() << endl;//0
		assert(s1.empty() == 0);
		cout << "s3 is empty? " << s3.empty() << endl;//1
		assert(s3.empty() == 1);
		cout << "s1 size: " << s1.size() << endl;//3
		assert(s1.size() == 3);
		cout << "s3 size: " << s3.size() << endl;//0
		assert(s3.size() == 0);

		cout << "s1 contains state 1? " << s1.contains(1) << endl;//1
		assert(s1.contains(1) == 1);
		cout << "s1 contains state 4? " << s1.contains(4) << endl;//0
		assert(s1.contains(4) == 0);
		cout << "s1 contains StateSet s2? " << s1.contains(s2) << endl;//1
		assert(s1.contains(s2) == 1);
		cout << "s1 contains StateSet s3? " << s1.contains(s3) << endl;//1
		assert(s1.contains(s3) == 1);
		cout << "s1 contains StateSet s4? " << s1.contains(s4) << endl;//0
		assert(s1.contains(s4) == 0);
		cout << "s1 not disjoint with s2? " << s1.not_disjoint(s2) << endl;//1
		assert(s1.not_disjoint(s2) == 1);
		cout << "s1 not disjoint with s3? " << s1.not_disjoint(s3) << endl;//0
		assert(s1.not_disjoint(s3) == 0);
		cout << "s1 not disjoint with s4? " << s1.not_disjoint(s4) << endl;//1
		assert(s1.not_disjoint(s4) == 1);
	}

	/******************************************
				  查找状态功能测试
	测试函数：
	1.smallest()			  返回编号最小状态
	2.iter_start(State &r)	  令r=开始（最小）状态编号，并返回
	3.iter_end(State &r)	  r是否为结束状态
	4.iter_next(State &r)	  状态r的下一个状态
	******************************************/
	void SearchStateTest()
	{
		cout << "SearchStateTest" << endl;
		StateSet s;

		s.set_domain(5);

		s.add(0).add(1).add(2);

		cout << "s smallese state number：" << s.smallest() << endl;//0
		assert(s.smallest() == 0);
		State i = 1;
		cout << "i=" << i << endl;
		cout << "s initial state number(s.iter_start(i))：" << s.iter_start(i) << endl;//0
		cout << "now i=" << i << endl;//0
		cout << "the next state of 0：" << s.iter_next(i) << endl;//1
		i = 2;
		cout << "the next state of 2：" << s.iter_next(i) << endl;//null
		cout << "end with state 2?" << s.iter_end(i) << endl;//1
		i = 1;
		cout << "end with state 1?" << s.iter_end(i) << endl;//0
	}

	/******************************************
					运算符功能测试
	测试函数：
	1.operator ==(const StateSet &r)   *this==r?1:0
	2.operator !=(const StateSet &r)   *this!=r?1:0
	3.operator =(const StateSet &r)    *this=r
	******************************************/
	void CompareTest()
	{
		cout << "CompareTest" << endl;
		StateSet s1, s2, s3;

		s1.set_domain(5);
		s2.set_domain(5);
		s3.set_domain(5);

		s1.add(0).add(1);
		s2.add(0).add(1);
		s3.add(0);

		cout << "s1=" << s1 << endl;
		cout << "s2=" << s2 << endl;
		cout << "s3=" << s3 << endl;
		cout << "s1==s2? " << s1.operator==(s2) << endl;//1
		assert(s1.operator==(s2)==1);
		cout << "s1!=s2? " << s1.operator!=(s2) << endl;//0
		assert(s1.operator!=(s2)==0);
		cout << "s1==s3? " << s1.operator==(s3) << endl;//0
		assert(s1.operator==(s3)==0);
		cout << "s1!=s3? " << s1.operator!=(s3) << endl;//1
		assert(s1.operator!=(s3)==1);
		cout << "s1=s3..." << endl << "s1= " << s1.operator=(s3) << endl;
	}

	/*******************************************
				   赋值功能测试
	测试函数：
	1.operator = (const StateSet &r)   *this=r
	*******************************************/
	void AssignmentTest()
	{
		cout << "AssignmentTest" << endl;
		StateSet s1, s2;

		s1.set_domain(5);

		s1.add(1).add(3);

		cout << "s1=" << s1 << endl;
		cout << "s2=" << s2 << endl;
		cout << "after assignment(s2=s1): " << endl;
		s2.operator=(s1);
		cout << "s1=" << s1 << endl;
		cout << "s2=" << s2 << endl;
	}

	/******************************************************
						 运算功能测试
	测试函数：
	1.complement()                            返回*this补集
	2.set_union(const StateSet &r)            返回*this∪r
	3.intersection(const StateSet &r)         返回*this∩r
	4.disjointing_union(const StateSet &r)    合并（{{*this},{r}}）
	5.st_rename(const int r)                  左移（增大）r位
	*****************************************************/
	void ComputeTest()
	{
		cout << "ComputeTest" << endl;
		StateSet s1, s2, s3, s4, s5;

		s1.set_domain(5);
		s2.set_domain(5);
		s3.set_domain(5);
		s4.set_domain(5);
		s5.set_domain(6);

		s1.add(0).add(1).add(2);
		s2.add(2).add(3);
		s3.add(2).add(4);
		s4.add(0).add(2).add(4);
		s5.add(1).add(2).add(5);

		cout << "s1=" << s1 << endl;
		cout << "s2=" << s2 << endl;
		cout << "s3=" << s3 << endl;
		cout << "s4=" << s4 << endl;
		cout << "s5=" << s5 << endl;
		cout << "s1 domain: " << s1.domain() << endl;
		cout << "s2 domain: " << s2.domain() << endl;
		cout << "s3 domain: " << s3.domain() << endl;
		cout << "s4 domain: " << s4.domain() << endl;
		cout << "s5 domain: " << s5.domain() << endl;
		cout << "s1 complement: " << s1.complement() << endl;
		cout << "s2∪s3: " << s2.set_union(s3) << endl;
		cout << "s3∩s4: " << s3.intersection(s4) << endl;
		cout << "s5 left_shift 4: " << s5.st_rename(4) << endl;
		cout << "s5 domain: " << s5.domain() << endl;
		cout << "s4 disjoint_union with s5: " << s4.disjointing_union(s5) << endl;
		cout << "s4 domain: " << s4.domain() << endl;
	}

	/******************************
			  回收功能测试
	测试函数：
	1.reincarnate()   回收StateSet r
	******************************/
	void RecycleTest()
	{
		cout << "RecycleTest:" << endl;
		StateSet s;
		s.set_domain(5);

		s.add(0).add(1);

		cout << "s=" << s << endl;
		cout << "s domain: " << s.domain() << endl;
		s.reincarnate();
		cout << "s=" << s << endl;
		cout << "s domain: " << s.domain() << endl;
	}
};



void StateSetTest_New()
{
	StateSetTest_NewClass t;
	t.AllocatingTest();
	t.Add_RemoveTest();
	t.CheckStateTest();
	t.SearchStateTest();
	t.CompareTest();
	t.AssignmentTest();
	t.ComputeTest();
	t.RecycleTest();
}