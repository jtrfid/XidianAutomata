//#include "../stdafx.h"  // fatal error C1010: �ڲ���Ԥ����ͷʱ����������ļ���β���Ƿ���������Դ����ӡ�#include "stdafx.h"��?
#include "stdafx.h"  // ��Ȼ��TestĿ¼���޴��ļ�������ȴƭȡ�˱�������������������
#include <iostream>
#include "../Trans.h"

using namespace std;

class TransTestClass
{
public:
	/****************************************************************
	   A Trans is a set of TransPairs (transitions) for use in transition relations. 
	   Map char(CharRange) to StateSet, using Translmpl.
	   class Trans :protected TransImpl

	   // set state (destinations of transition) is [0,r), i.e. StateSet domain()
	   void set_range(const int r);

	   // What are all of the labels on transitions in *this?
	   CRSet out_labels() const;
	   What are all transition labels with destination in r?
	   CRSet labels_into(const StateSet& r) const;
	 ****************************************************************/
	void basicTransTest()
	{
		cout << "===basicTransTest\n";
		Trans trans;
		// Change the range of States that can be transitioned to.
	    // This is used in determining the domain() of the StateSet's (which are destinations of transitions).
		// set state (destinations of transition) is [0,r)
		trans.set_range(4);
		cout << "StateSet domain(): " << trans.range() << endl; // 3

		CharRange cr('a', 'd');  
		trans.add_transition('a', 0); // �ڶ������� < 3; trans.set_range(3);
		trans.add_transition('a', 2);
		trans.add_transition('b', 3); 
		trans.add_transition(cr, 2);

		cout << "trans��" << trans << endl;  // trans��{ 'a'->0  ['a','d']->2  'b'->3 }

		StateSet st;
		st.set_domain(5);
		st.add(0).add(1).add(3);
		cout << "st: " << st << endl;  // {0 1 3}

		CRSet into = trans.labels_into(st);
		cout << "into: " << into << endl; // into: { 'a'  'b' }
		CRSet out = trans.out_labels();
		cout << "out: " << out << endl;  // out: { 'a'  'b' ['c', 'd'] }, ע��: ['a','d']��'b'����ʾΪ{ 'b'  'a'  ['c','d'] }
	}

	void basicTransTest1()
	{
		cout << "===basicTransTest1\n";
		Trans trans;
		trans.set_range(3);

		trans.add_transition('a', 0); // �ڶ������� < 3; trans.set_range(3);
		trans.add_transition('a', 2);
		trans.add_transition('b', 0); // ���һ�����ϲ�Ϊ['a' 'b'] to 0,��ڶ�����'a' to 2 ��ͻ
		
		cout << "trans��" << trans << endl; // trans��{ ['a','b']->0  'a'->2 }, ע�⣺a,b���ϲ�

		CRSet out = trans.out_labels();
		cout << "out: " << out << endl;  // out: { 'a'  'b' }
	}


};

void TransTest()
{
	cout << "===TransTest===\n";
	TransTestClass test;
	test.basicTransTest();
	//test.basicTransTest1();
}