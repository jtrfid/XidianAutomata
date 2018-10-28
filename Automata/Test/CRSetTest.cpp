//#include "../stdafx.h"  // fatal error C1010: �ڲ���Ԥ����ͷʱ����������ļ���β���Ƿ���������Դ����ӡ�#include "stdafx.h"��?
#include "stdafx.h"  // ��Ȼ��TestĿ¼���޴��ļ�������ȴƭȡ�˱�������������������
#include <iostream>
#include "../CRSet.h"

using namespace std;

class CRSetTestClass
{
public:
	/******************************************************
	  A data-structure to hold sets of CharRange's. The CharRange's are kept pair wise disjoint.
	  When a new CharRange is added to a CRSet, some CharRanges may be split to ensure that the disjointness property is preserved.
	 ******************************************************/
	void basicCRSetTest()
	{
		cout << "===basicCRSetTest\n";
		CRSet set1;
		set1.add('a');
		CharRange cr('a', 'b');
		cout << cr << endl; // [ 'a' 'b' ]
		cout << cr.not_disjoint('a') << endl;  // 1, ��ʾcr��'a'�ཻ
		set1.add(cr); 
		cout << set1 << endl;  // { 'a' 'b' }
	}

	void basicCRSetTest1()
	{
		cout << "===basicCRSetTest1\n";
		CRSet set1;
		CharRange cr('b', 'd');
		cout << cr << endl; // [ 'b' 'd' ]
		cout << cr.not_disjoint('c') << endl;  // 1, ��ʾcr��'a'�ཻ
		set1.add(cr);
		set1.add('c');
		cout << set1 << endl;   // { 'c' 'b' 'd' }
	}

	void basicCRSetTest2()
	{
		cout << "===basicCRSetTest2\n";
		CRSet set1;
		CharRange cr('a', 'd');
		cout << cr << endl; // [ 'a' 'd' ]
		cout << cr.not_disjoint('b') << endl;  // 1, ��ʾcr��'a'�ཻ
		set1.add(cr);
		set1.add('b');
		cout << set1 << endl;   // { 'b'  'a'  ['c','d'] }
	}
};

void CRSetTest()
{
	cout << "===CRSetTest===\n";
	CRSetTestClass test;
	test.basicCRSetTest();
	test.basicCRSetTest1();
	test.basicCRSetTest2();
}