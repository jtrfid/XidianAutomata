#include<iostream>
#include"StateSet.h"

using namespace std;

class StateSetTest_NewClass
{
public:
	/**************************************************
				  ���估������״̬������
	���Ժ�����
	1.set_domain(const int r)   Ϊһ��StateSet������СΪr��״̬��
	2.domain()                  ���ط����״̬��
	**************************************************/
	void AllocatingTest()
	{
		cout << "AllocatingTest:" << endl;
		StateSet s;
		s.set_domain(5);

		cout << "domain:" << s.domain() << endl;
	}

	/************************************************
					���/ȥ��״̬����
	���Ժ���:
	1.add(const State r)          ���״̬r
	2.remove(const State r)       �Ƴ�״̬r
	3.remove(const StateSet& r)   �Ƴ�StateSet r�а�����״̬
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
							���״̬����
	���Ժ���:
	1.empty()                      ���״̬���
	2.size()				       ���״̬��Ŀ
	3.contains(state r)            �Ƿ������״̬r
	4.contains(StateSet &r)		   ��ӵ�״̬�Ƿ����StateSet r����ӵ�״̬
	5.not_disjoint(StateSet &r)    *this��r�Ƿ����ཻ��״̬�����ͬ����״̬
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
				  ����״̬���ܲ���
	���Ժ�����
	1.smallest()			  ���ر����С״̬
	2.iter_start(State &r)	  ��r=��ʼ����С��״̬��ţ�������
	3.iter_end(State &r)	  r�Ƿ�Ϊ����״̬
	4.iter_next(State &r)	  ״̬r����һ��״̬
	******************************************/
	void SearchStateTest()
	{
		cout << "SearchStateTest" << endl;
		StateSet s;

		s.set_domain(5);

		s.add(0).add(1).add(2);

		cout << "s smallese state number��" << s.smallest() << endl;//0
		assert(s.smallest() == 0);
		State i = 1;
		cout << "i=" << i << endl;
		cout << "s initial state number(s.iter_start(i))��" << s.iter_start(i) << endl;//0
		cout << "now i=" << i << endl;//0
		cout << "the next state of 0��" << s.iter_next(i) << endl;//1
		i = 2;
		cout << "the next state of 2��" << s.iter_next(i) << endl;//null
		cout << "end with state 2?" << s.iter_end(i) << endl;//1
		i = 1;
		cout << "end with state 1?" << s.iter_end(i) << endl;//0
	}

	/******************************************
					��������ܲ���
	���Ժ�����
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
				   ��ֵ���ܲ���
	���Ժ�����
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
						 ���㹦�ܲ���
	���Ժ�����
	1.complement()                            ����*this����
	2.set_union(const StateSet &r)            ����*this��r
	3.intersection(const StateSet &r)         ����*this��r
	4.disjointing_union(const StateSet &r)    �ϲ���{{*this},{r}}��
	5.st_rename(const int r)                  ���ƣ�����rλ
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
		cout << "s2��s3: " << s2.set_union(s3) << endl;
		cout << "s3��s4: " << s3.intersection(s4) << endl;
		cout << "s5 left_shift 4: " << s5.st_rename(4) << endl;
		cout << "s5 domain: " << s5.domain() << endl;
		cout << "s4 disjoint_union with s5: " << s4.disjointing_union(s5) << endl;
		cout << "s4 domain: " << s4.domain() << endl;
	}

	/******************************
			  ���չ��ܲ���
	���Ժ�����
	1.reincarnate()   ����StateSet r
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