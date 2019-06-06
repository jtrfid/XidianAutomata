#include<iostream>
#include"StateEqRel.h"
#include"StateSet.h"

using namespace std;

class StateEqRelTestClass
{
public:
	StateEqRelTestClass()
	{
		cout << "*************************" << endl;
		cout << "      StateEqRelTest" << endl;
		cout << "*************************" << endl;
	}

	void ss()
	{
		StateEqRel s(5);//domain = 5
		cout << "s domain: " << s.domain() << endl;
		cout << "s= " << s << endl;//{0,1,2,3,4}

		StateSet ss1, ss2;

		ss1.set_domain(5);//the same as StateEqRel s
		ss2.set_domain(5);

		ss1.add(0);
		ss2.add(1).add(2);

		cout << "ss1= " << ss1 << endl;//{0}
		cout << "ss2= " << ss2 << endl;//{1,2}

		cout << "split s with ss1 and ss2: " << s.split(ss1).split(ss2) << endl;//{0} {1,2} {3,4}
		cout << "what StateSet equivalize with State 1? " << s.equiv_class(1) << endl;//{2}
		cout << "what StateSet equivalize with State 3? " << s.equiv_class(3) << endl;//{4}
		cout << "state 0 eq_class_representative in s: " << s.eq_class_representative(0) << endl;//0
		cout << "state 2 eq_class_representative in s: " << s.eq_class_representative(2) << endl;//1
		
		cout << "are state 0 & 1 equivalent? " << s.equivalent(0, 1) << endl;//0
		assert(s.equivalent(0, 1)==0);
		cout << "are state 1 & 2 equivalent? " << s.equivalent(1, 2) << endl;//1
		assert(s.equivalent(1, 2)==1);
		s.equivalize(0, 1);
		cout << "equivalize state 0 & 1..." << endl;
		cout << "are state 0 & 1 equivalent? " << s.equivalent(0, 1) << endl;//1
		assert(s.equivalent(0, 1)==1);
		cout << "make *this identity..." << s.identity() << endl;
	}
};

void StateEqRelTest()
{
	StateEqRelTestClass t;
	t.ss();
}