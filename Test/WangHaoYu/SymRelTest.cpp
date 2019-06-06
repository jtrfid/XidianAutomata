#include<iostream>
#include"SymRel.h"

using namespace std;
//所谓对称关系，即存在映射0->{1}的同时，也存在映射1->{0}。
class SymRelTestClass
{
public:
	SymRelTestClass()
	{
		cout << "**********************" << endl;
		cout << "     SymRelTest" << endl;
		cout << "**********************" << endl;
	}

	/***********************************************************************
								Set Domain Test
	测试函数:
	1. void set_domain(const int r)									设置范围
	2.std::ostream& operator<<(std::ostream& os, const SymRel& r);  输出
	***********************************************************************/
	void SetDomainTest()
	{
		SymRel s;
		s.set_domain(5);

		cout << "s: " << endl << s << endl;
		/*输出函数原为内联，调用时出现error如下:

		SymRelTest.obj : error LNK2019: 无法解析的外部符号 
		"class std::basic_ostream<char,struct std::char_traits<char> > & __cdecl operator<<
		(class std::basic_ostream<char,struct std::char_traits<char> > &,class SymRel const &)" 
		(??6@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@std@@AEAV01@AEBVSymRel@@@Z)，
		该符号在函数 "public: void __cdecl SymRelTestClass::s1(void)" (?s1@SymRelTestClass@@QEAAXXZ) 中被引用

		取消其内联，则可以进行调用*/
		cout << "s domain: " << s.domain() << endl;//5
	}

	/*******************************************************************************************
										Add Pair(s) Test
	测试函数:
	1.SymRel& add_pair(const State p, const State q)			添加状态对：State X State
	2.SymRel& add_pairs(const StateSet& P, const StateSet& Q)	添加状态对：StateSet X StateSet
	*******************************************************************************************/
	void AddPairTest()
	{
		SymRel s;
		s.set_domain(5);

		s.add_pair(0, 1);
		s.add_pair(0, 2);//此处不能超过s domain

		cout << "s: " << endl << s << endl;//0->{1,2},1->{0},2->{0},3->{},4->{}

		SymRel s1;
		StateSet a1, a2;

		s1.set_domain(5);
		a1.set_domain(5);//此处SymRel Domain要与StateSet Domain相同
		a2.set_domain(5);

		a1.add(0).add(1);
		a2.add(2).add(3);

		cout << "s1: " << endl << s1.add_pairs(a1, a2) << endl;//0->{2,3},1->{2,3},2->{0,1},3->{0,1},4->{}
	}

	/*******************************************************************************************
										Remove Pair(s) Test
	测试函数:
	1.SymRel& remove_pair(const State p, const State q)				移除状态对：State X State
	2.SymRel& remove_pairs(const StateSet& P, const StateSet& Q)	移除状态对：StateSet X StateSet
	*******************************************************************************************/
	void RemovePairTest()
	{
		SymRel s;
		s.set_domain(5);

		s.add_pair(0, 1);
		s.add_pair(0, 2);

		cout << "s: " << endl << s << endl;//0->{1,2},1->{0},2->{0},3->{},4->{}
		cout << "now remove pair 0->{1}&symmetrically 1->{0}" << endl;
		cout << s.remove_pair(0, 1) << endl;//0->{2},1->{},2->{0},3->{},4->{}

		SymRel s1;
		StateSet a1, a2;

		s1.set_domain(5);
		a1.set_domain(5);//此处SymRel Domain要与StateSet Domain相同
		a2.set_domain(5);

		a1.add(0).add(1);
		a2.add(2).add(3);

		cout << "s1: " << endl << s1.add_pairs(a1, a2) << endl;//0->{2,3},1->{2,3},2->{0,1},3->{0,1},4->{}
		cout << "now remove pairs 0->{2,3},1->{2,3}&symmertrically 2->{0,1},3->{0,1}" << endl;
		cout << s.remove_pairs(a1, a2) << endl;//0->{},1->{},2->{},3->{},4->{}
	}

	/**************************************************************
								ImageTest
	测试函数:
	1.StateSet& image(const State p) const	返回p映射的StateSet
	**************************************************************/
	void ImageTest()
	{
		SymRel s;
		s.set_domain(5);

		s.add_pair(0, 1);
		s.add_pair(0, 2);

		cout << "s: " << endl << s << endl;//0->{1,2},1->{0},2->{0}
		cout << "image(0): " << s.image(0) << endl;//{1,2}
		cout << "image(1): " << s.image(1) << endl;//{0}
		cout << "image(4): " << s.image(4) << endl;//{}
		//cout << "image(5): " << s.image(5) << endl;超过s domain,报错
	}

	/***********************************************************************************
										ContainsTest
	测试函数：
	1.int contains_pair(const State p, const State q) const	检查*this中是否含有p->{q}
	***********************************************************************************/
	void ContainsTest()
	{
		SymRel s;
		s.set_domain(5);

		s.add_pair(0, 1);
		s.add_pair(0, 2);

		cout << "s: " << endl << s << endl;//0->{1,2},1->{0},2->{0}
		cout << "s contains 0->{1}? " << s.contains_pair(0, 1) << endl;//1
		cout << "s contains 2->{0}? " << s.contains_pair(2, 0) << endl;//1
		cout << "s contains 1->{3}? " << s.contains_pair(1, 3) << endl;//0
		//cout << "s contains 1->{3}? " << s.contains_pair(1, 5) << endl;此处不能超过s domain
	}

	/************************************************
					 ComplementTest
	测试函数:
	1.SymRel& complement()	返回映射关系的补集
	例：s domain: 2
	s:0->{0,1},1->{0}
	s complement:1->{1}
	************************************************/
	void ComplementTest()
	{
		SymRel s;
		s.set_domain(5);

		s.add_pair(0, 1);
		s.add_pair(0, 2);

		cout << "s: " << endl << s << endl;//0->{1,2},1->{0},2->{0}
		cout << "s complement: " << endl << s.complement() << endl;
	}

	/********************************************************
							IdentityTest
	测试函数:
	1.SymRel& identity()	迭代*this,使每个状态映射至其本身
	例：s domain:2
	s.identity():0->{0},1->{1}
	********************************************************/
	void IdentityTest()
	{
		SymRel s;
		s.set_domain(5);

		s.add_pair(0, 1);
		s.add_pair(0, 2);

		cout << "s: " << endl << s << endl;//0->{1,2},1->{0},2->{0}
		cout << "s identity: " << endl << s.identity() << endl;//0->{0},1->{1},2->{2},3->{3},4->{4}
	}

	/**********************************************
					AssignmentTest
	测试函数:
	1.SymRel& operator=(const SymRel& r)	*this = r
	**********************************************/
	void AssignmentTest()
	{
		SymRel s1, s2;
		s1.set_domain(5);
		s2.set_domain(6);
		

		s1.add_pair(0, 1);
		s1.add_pair(0, 2);
		s2.add_pair(1, 4);
		s2.add_pair(2, 3);

		cout << "s1 domain: " << s1.domain() << endl;//5
		cout << "s1: " << endl << s1 << endl;//0->{1,2},1->{0},2->{0}
		cout << "s2 domain: " << s2.domain() << endl;//6
		cout << "s2: " << endl << s2 << endl;//0->{},1->{4},2->{3},3->{2},4->{1},5->{}

		cout << "let s1 = s2: "  << endl;
		cout << "s1 domian: " << s1.domain() << endl;//6
		cout << "s1: " << endl << s1.operator=(s2) << endl;//0->{},1->{4},2->{3},3->{2},4->{1},5->{}
	}
};

void SymRelTest()
{
	SymRelTestClass t;
	t.SetDomainTest();
	t.AddPairTest();
	t.RemovePairTest();
	t.ImageTest();
	t.ContainsTest();
	t.ComplementTest();
	t.IdentityTest();
	t.AssignmentTest();
}