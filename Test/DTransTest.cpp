#include<iostream>
#include"DTrans.h"

using namespace std;

class DTransTestClass
{
public:
	void IOTest()
	{
		DTrans dt;
		CharRange cr('c', 'e');

		dt.add_transition('a', 1);
		dt.add_transition('b', 2);
		dt.add_transition(cr, 3);

		cout << "dt = " << dt << endl;//{'a'->1 'b'->2 ['c','e']->3}
	}

	void LabelsTest()
	{
		DTrans dt;
		CharRange cr('c', 'e');

		dt.add_transition('a', 1);
		dt.add_transition('b', 2);
		dt.add_transition(cr, 3);

		cout << "dt = " << dt << endl;//{'a'->1 'b'->2 ['c','e']->3}

		StateSet s;

		s.set_domain(5);
		s.add(1);//s = {1}

		cout << "labels into {1}: " << dt.labels_into(s) << endl;//{'a'}

		s.add(2);//s = {1,2}

		cout << "labels into {1,2}: " << dt.labels_into(s) << endl; //{'a','b'}
		cout << "what are all the labels: " << dt.out_labels() << endl;
	}

	void RangeTest()
	{
		DTrans dt;
		CharRange cr('c', 'e');

		dt.add_transition('a', 1);
		dt.add_transition('b', 2);
		dt.add_transition(cr, 3);

		cout << "dt = " << dt << endl;//{'a'->1 'b'->2 ['c','e']->3}

		cout << "what State corresponds with label 'a': " << dt.range_transition(CharRange('a')) << endl;//1
		cout << "what State corresponds with label ['c','e']: " << dt.range_transition(cr) << endl;//3
		cout << "what State corresponds with label ['a','b']: " << dt.range_transition(CharRange('a', 'b')) << endl;//-1 (means no state)
		cout << "State range: " << dt.range(5) <<endl;//{1,2,3} range函数参数不能低于*this中设置的状态最大值
	}

	void MapTest()
	{
		DTrans dt;
		CharRange cr('c', 'e');

		dt.add_transition('a', 1);
		dt.add_transition('b', 2);
		dt.add_transition(cr, 3);

		cout << "dt = " << dt << endl;//{'a'->1 'b'->2 ['c','e']->3}

		cout << "what state  label 'a' maps: " << dt.operator[]('a') << endl;//1
		cout << "what state  label 'd' maps: " << dt.operator[]('d') << endl;//3
	}

	void AssignmentTest()
	{
		DTrans dt1, dt2;
		CharRange cr('c', 'e');

		dt1.add_transition('a', 1);
		dt1.add_transition('b', 2);
		dt1.add_transition(cr, 3);
		dt2.add_transition('h', 4);
		dt2.add_transition('d', 5);

		cout << "dt1 = " << dt1 << endl;//{'a'->1 'b'->2 ['c','e']->3}
		cout << "dt2 = " << dt2 << endl;//{'h'->4 'd'->5}

		cout << "assign dt1 to dt2..." << endl;

		cout << "dt2 = " << dt2.operator=(dt1) << endl;//{'a'->1 'b'->2 ['c','e']->3}
	}

	void ReincarnateTest()
	{
		DTrans dt;
		CharRange cr('c', 'e');

		dt.add_transition('a', 1);
		dt.add_transition('b', 2);
		dt.add_transition(cr, 3);

		cout << "dt = " << dt << endl;//{'a'->1 'b'->2 ['c','e']->3}
		cout << "now reincarnate *this..." << endl;

		dt.reincarnate();

		cout << "dt = " << dt << endl;
	}
};

void DTransTest()
{
	DTransTestClass dtc;
	/*dtc.IOTest();
	dtc.LabelsTest();*/
	dtc.RangeTest();
	/*dtc.MapTest();
	dtc.AssignmentTest();
	dtc.ReincarnateTest();*/
}