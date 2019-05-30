#include<iostream>
#include"CRSet.h"

using namespace std;

class CRSetTestClass
{
public:
	/****************************************************************************
										初始化测试
	测试函数：
	1.CRSet& add(const CharRange a)		 添加CharRange a
	2.CRSet& append(const CharRange& a)  附加CharRange a(不能与*this有重叠部分)
	3.CRSet& combine(const CRSet& r)	 合并*this与CharRange r
	****************************************************************************/
	void InitialTest()
	{
		CRSet c;
		c.add('b');
		CharRange r('a','d');
		c.add(r);
		cout << "c: " << c << endl;//{'b','a',['c','d']}

		CRSet c1, c2;
		CharRange r1('d','f');

		c1.add('a').add('b');
		c2.append(r1);

		cout << "c1: " << c1 << endl;//{'a','b'}
		cout << "c2: " << c2 << endl;//{['d','f']}

		cout << "combine cr&c2: " << c1.combine(c2) << endl;//{'a','b',['d','f']}
	}

	/*************************************************************************
									CheckTest
	测试函数:
	1.CharRange& iterator(const int it) const;		*this中第it'th个字符集
	2.int iter_end(const int it) const				*this是否第it'th个字符集结束
	3.int size() const								*this 字符集数目
	4.int equivalent_cover(const CRSet& r) const	*this 与r是否覆盖相同字符集
	*************************************************************************/
	void CheckTest()
	{
		CRSet c1, c2, c3;
		//CharRange r('a', 'd');
		c1.add('a').add('b');
		c2.add('a').add('b');
		c3.add('b').add('c');

		cout << "c1: " << c1 << endl;//{'a','b'}
		cout << "c2: " << c2 << endl;//{'a','b'}
		cout << "c3: " << c3 << endl;//{'b','c'}

		cout << "c1 covers the same with c2? " << c1.equivalent_cover(c2) << endl;//1
		cout << "c1 covers the same with c3? " << c1.equivalent_cover(c3) << endl;//0
		cout << "c1 size: " << c1.size() << endl;//2
		cout << "1st charrange in c1 " << c1.iterator(0) << endl;//'a'此处字符(集)没有理论上的“排序”
		//cout << "c1第三个字符: " << c1.iterator(2) << endl;(不能超过字符集数目上限)
		cout << "c1 ends with 3rd charrange? " << c1.iter_end(2) << endl;//1
	}

	/*********************************************
					  AssignTest
	测试函数:
	1.CRSet& operator=(const CRSet& r)	*this = r
	*********************************************/
	void AssignTest()
	{
		CRSet c1, c2;
		c1.add('a').add('b');
		c2.add('a').add('c');

		cout << "c1: " << c1 << endl;//{'a','b'}
		cout << "c2: " << c2 << endl;//{'a','c'}

		cout << "Assign c2 to c1: " << endl << "c1: " << c1.operator=(c2) << endl;
	}
};

void CRSetTest_New()
{
	CRSetTestClass t;
	t.InitialTest();
	t.CheckTest();
	t.AssignTest();
}