#include <iostream>
#include "Trans.h"

using namespace std;

class TransTestClass
{
public:
	/****************************************************************
	   A Trans is a set of TransPairs (transitions) for use in transition relations. 
	   Map char(CharRange) to StateSet, using Translmpl.
	   class Trans :protected TransImpl

	   Trans::destination_range; // The domain() of the associated State Pool.
	   TransImpl::in_use;  // How many transitions are there. [0,in_use) index of TransPair *data, it is is managed in add_transition()

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
		cout << "StateSet domain(): " << trans.range() << endl; // 4

		CharRange cr('a', 'd');  
		trans.add_transition('a', 0); // 第二个参数 < 4; trans.set_range(4);
		trans.add_transition('a', 2);
		trans.add_transition('b', 3); 
		trans.add_transition(cr, 2);

		cout << "trans：" << trans << endl;  // trans：{ 'a'->0  ['a','d']->2  'b'->3 }

		StateSet st;
		st.set_domain(5);
		st.add(0).add(1).add(3);
		cout << "st: " << st << endl;  // {0 1 3}

		CRSet into = trans.labels_into(st);
		cout << "into: " << into << endl; // into: { 'a'  'b' }
		CRSet out = trans.out_labels();
		cout << "out: " << out << endl;  // out: { 'a'  'b' ['c', 'd'] }, 注意: ['a','d']和'b'被表示为{ 'b'  'a'  ['c','d'] }
	}

	void basicTransTest1()
	{
		cout << "===basicTransTest1\n";
		Trans trans;
		trans.set_range(3);

		trans.add_transition('a', 0); // 第二个参数 < 3; trans.set_range(3);
		trans.add_transition('a', 2);
		trans.add_transition('b', 0); // 与第一条将合并为['a' 'b'] to 0
		
		cout << "trans：" << trans << endl; // trans：{ ['a','b']->0  'a'->2 }, 注意：a,b被合并

		CRSet out = trans.out_labels();
		cout << "out: " << out << endl;  // out: { 'a'  'b' }
	}

	void range_transitionTest()
	{
		cout << "===range_transitionTest\n";
		Trans trans;
		trans.set_range(3);

		trans.add_transition('a', 0); // 第二个参数 < 3; trans.set_range(3);
		trans.add_transition('a', 2);
		trans.add_transition('b', 0); // 与第一条将合并为['a' 'b'] to 0
		trans.add_transition('c', 2);

		cout << "trans：" << trans << endl; // trans：{ ['a','b']->0  'a'->2  'c'->2 }, 注意：a,b被合并

		CRSet out = trans.out_labels();
		cout << "out: " << out << endl;  // out: { 'a'  'b' 'c'}

		StateSet set;
		cout << "StateSet: " << trans.range_transition(CharRange('a', 'b')) << endl; // { 0 2 }
	}

	void set_unionTest()
	{
		cout << "===set_unionTest\n";
		Trans trans1;
		trans1.set_range(3);

		trans1.add_transition('a', 0); // 第二个参数 < 3; trans.set_range(3);
		trans1.add_transition('a', 2);
		trans1.add_transition('b', 0); // 与第一条将合并为['a' 'b'] to 0
		trans1.add_transition('c', 2);

		Trans trans2;
		trans2.set_range(3);

		trans2.add_transition('a', 1); 
		trans2.add_transition('c', 1);

		cout << "trans1：" << trans1 << endl; // trans1：{ ['a','b']->0  'a'->2  'c'->2 }, 注意：a,b被合并
		cout << "trans2：" << trans2 << endl; // trans2：{ 'a'->1  'c'->1 }
		
		cout << "set_union: " << trans1.set_union(trans2) << endl; // { ['a','b']->0  'a'->2  'c'->2  'a'->1  'c'->1 }
		cout << "StateSet domain(): " << trans1.range() << endl; // 3
	}

	void disjointing_unionTest()
	{
		cout << "===disjointing_unionTest\n";
		Trans trans1;
		trans1.set_range(3);

		trans1.add_transition('a', 0); // 第二个参数 < 3; trans.set_range(3);
		trans1.add_transition('a', 2);
		trans1.add_transition('b', 0); // 与第一条将合并为['a' 'b'] to 0
		trans1.add_transition('c', 2);

		Trans trans2;
		trans2.set_range(2);

		trans2.add_transition('a', 1);
		trans2.add_transition('c', 1);

		cout << "trans1：" << trans1 << endl; // trans1：{ ['a','b']->0  'a'->2  'c'->2 }, 注意：a,b被合并
		cout << "trans2：" << trans2 << endl; // trans2：{ 'a'->1  'c'->1 }

		cout << "disjointing_union: " << trans1.disjointing_union(trans2) << endl; // { ['a','b']->0  'a'->2  'c'->2  'a'->4  'c'->4 }
		cout << "StateSet domain(): " << trans1.range() << endl; // 5
	}

	void st_renameTest()
	{
		cout << "===st_renameTest\n";
		Trans trans1;
		trans1.set_range(3);

		trans1.add_transition('a', 0); // 第二个参数 < 3; trans.set_range(3);
		trans1.add_transition('a', 2);
		trans1.add_transition('b', 0); // 与第一条将合并为['a' 'b'] to 0
		trans1.add_transition('c', 2);

		cout << "trans1：" << trans1 << endl; // trans1：{ ['a','b']->0  'a'->2  'c'->2 }, 注意：a,b被合并

		cout << "StateSet domain(): " << trans1.range() << endl; // 3
		cout << "st_rename: " << trans1.st_rename(10) << endl; // { ['a','b']->10  'a'->12  'c'->12 }
		cout << "StateSet domain(): " << trans1.range() << endl; // 13
	}

	void reincarnateTest()
	{
		cout << "===reincarnateTest\n";
		Trans trans1;
		trans1.set_range(3);

		trans1.add_transition('a', 0); // 第二个参数 < 3; trans.set_range(3);
		trans1.add_transition('a', 2);
		trans1.add_transition('b', 0); // 与第一条将合并为['a' 'b'] to 0
		trans1.add_transition('c', 2);

		cout << "trans1：" << trans1 << endl; // trans1：{ ['a','b']->0  'a'->2  'c'->2 }, 注意：a,b被合并

		cout << "StateSet domain(): " << trans1.range() << endl; // 3
		trans1.reincarnate();  
		cout << "trans1：" << trans1 << endl; // { }
		cout << "StateSet domain(): " << trans1.range() << endl; // 3
	}
};

void TransTest()
{
	cout << "===TransTest===\n";
	TransTestClass test;
	test.basicTransTest();
	test.basicTransTest1();
	test.range_transitionTest();
	test.set_unionTest();
	test.disjointing_unionTest();
	test.set_unionTest();
	test.st_renameTest();
	test.reincarnateTest();
}