#include<iostream>
#include"DTransRel.h"

using namespace std;

class DTransRelTestClass
{
public:

	void BasicFuncTest()
	{
		DTransRel dtr;
		dtr.set_domain(5);

		dtr.add_transition(0, 'a', 4);//��һ��State�������ܳ���֮ǰ���õ�domain,����������ԣ���������������������domain��labels_between()�����ᱨ��
		dtr.add_transition(1, 'a', 5);
		dtr.add_transition(0, 'b', 4);
		dtr.add_transition(2, 'b', 6);
		dtr.add_transition(0, 'c', 4);
		dtr.add_transition(2, 'c', 6);

		cout << "dtr: " << endl << dtr << endl;
		cout << "dtr domain: " << dtr.domain() << endl;//5

		cout << "T(0,a) = " << dtr.image(0, 'a') << endl;//4(�˴���һ��State�������ܳ���֮ǰ���õ�domain)
		cout << "T(2,b) = " << dtr.image(2, 'b') << endl;//6
		cout << "T(3,c) = " << dtr.image(1, 'c') << endl;//-1(means no such state)

		//lookup()����ѯ���ܣ�map()���޸Ĺ���
	}

	void LabelsTest()
	{
		DTransRel dtr;
		dtr.set_domain(5);

		dtr.add_transition(0, 'a', 2);//��һ��State�������ܳ���֮ǰ���õ�domain,����������ԣ���������������������domain��labels_between()�����ᱨ��
		dtr.add_transition(1, 'a', 0);
		dtr.add_transition(0, 'b', 3);
		dtr.add_transition(2, 'b', 4);
		dtr.add_transition(0, 'c', 4);
		dtr.add_transition(2, 'c', 4);

		cout << "dtr: " << endl << dtr << endl;
		cout << "dtr domain: " << dtr.domain() << endl;//5

		cout << "out labels of state 0: " << dtr.out_labels(0) << endl;//{'a','b','c'}
		cout << "out labels of state 1: " << dtr.out_labels(1) << endl;//{'a'}
		cout << "out labels of state 3: " << dtr.out_labels(3) << endl;//{}

		StateSet s;
		s.set_domain(5);//�˴�s.domain() == dtr.domian()

		s.add(2);//{2}

		cout << "labels between state 0 and stateset {2}: " << dtr.labels_between(0, s) << endl; //{'a'}

		s.add(3); //{2,3}

		cout << "labels between state 0 and stateset {2,3}: " << dtr.labels_between(0, s) << endl;//{'a','b'}

		s.add(4); //{2,3,4}

		cout << "labels between state 0 and stateset {2,3,4}: " << dtr.labels_between(0, s) << endl;//{'a','b','c'}

		s.remove(2).remove(3).remove(4).add(1);//{1}

		cout << "labels between state 0 and stateset {1}: " << dtr.labels_between(0, s) << endl;//{}
	}

	void TransRangeTest()
	{
		DTransRel dtr;
		dtr.set_domain(5);

		dtr.add_transition(0, 'a', 4);//��һ��State�������ܳ���֮ǰ���õ�domain,����������ԣ���������������������domain��labels_between()�����ᱨ��
		dtr.add_transition(1, 'a', 3);
		dtr.add_transition(0, 'b', 4);
		dtr.add_transition(2, 'b', 1);
		dtr.add_transition(0, 'c', 4);
		dtr.add_transition(2, 'c', 1);

		cout << "dtr: " << endl << dtr << endl;
		cout << "dtr domain: " << dtr.domain() << endl;//5

		//�˴���һ������ҪС��֮ǰ���õ�dtr.domain
		cout << "reverse transition 4->{['a','b']}: " << dtr.reverse_transition(4, CharRange('a', 'b')) << endl; //{0}
		cout << "reverse transition 1->{['b','c']}: " << dtr.reverse_transition(1, CharRange('b', 'c')) << endl; //{2}

		cout << "T(0,{['a','c']}) = " << dtr.transition_on_range(0, CharRange('a', 'c')) << endl;//1
		cout << "T(2,{['b','c']}) = " << dtr.transition_on_range(2, CharRange('b', 'c')) << endl;//4
		cout << "T(1,{['a','c']}) = " << dtr.transition_on_range(1, CharRange('a', 'c')) << endl;//-1(means no such state)

		StateSet s;
		s.set_domain(5);//�˴�s.domain() == dtr.domian()

		s.add(1);//{1}

		cout << "reverse closure of stateset {1}: " << dtr.reverse_closure(s) << endl;//{1,2}

		s.add(3);//{1,3}

		cout << "reverse closure of stateset {1,3}: " << dtr.reverse_closure(s) << endl;//{1,2,3
	
	}

	void ReincarnateTest()
	{
		DTransRel dtr;
		dtr.set_domain(5);

		dtr.add_transition(0, 'a', 4);//��һ��State�������ܳ���֮ǰ���õ�domain,����������ԣ���������������������domain��labels_between()�����ᱨ��
		dtr.add_transition(1, 'a', 3);
		dtr.add_transition(0, 'b', 4);
		dtr.add_transition(2, 'b', 1);
		dtr.add_transition(0, 'c', 4);
		dtr.add_transition(2, 'c', 1);

		cout << "dtr: " << endl << dtr << endl;
		cout << "dtr domain: " << dtr.domain() << endl;//5

		cout << "reincarnate *this..." << endl;

		dtr.reincarnate();

		cout << "dtr = " << endl << dtr << endl;//null
		cout << "dtr domain: " << dtr.domain() << endl;//0
	}
};

void DTransRelTest()
{
	DTransRelTestClass t;
	
	t.BasicFuncTest();
	t.LabelsTest();
	t.TransRangeTest();
	t.ReincarnateTest();
}