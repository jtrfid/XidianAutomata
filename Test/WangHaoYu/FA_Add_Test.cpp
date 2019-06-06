#include<iostream>
#include "FA_Add.h"

using namespace std;

class FA_Add_TestClass
{
public:
	FA_Add_TestClass()
	{
		cout << "**********************" << endl;
		cout << "      FA_Add_Test" << endl;
		cout << "**********************" << endl;
	}

	void FA_Add_Test()
	{
		FA_Add ad;
		ad.set_domain(5);
		ad.start(0);
		ad.final(4);
		ad.add_transition(0, 'a', 1);
		ad.add_transition(1, 'b', 2);
		ad.add_transition(2, 'c', 3);
		ad.add_transition(2, 'd', 4);
		//ad.add_epsilon(1, 2);
		cout << "ad= " << ad << endl;

		cout << "States number: " << ad.num_states() << endl;//5

		ad.restart();
		char c[] = "abc";
		cout << ad.acceptable(c) << endl;
		ad.restart();
		ad.advance('a');
		cout << "is FA stucked? " << ad.stuck() << endl;
		ad.advance('b');
		ad.advance('d');
		cout << ad << endl;
		cout << "FA in final State? " << ad.in_final() << endl;

		ad.restart();
		ad.advance('a');
		ad.advance('b');
		ad.advance('c');

		cout << "whats current state? " << ad.whatscurrent() << endl;
		cout << "FA in final State? " << ad.in_final() << endl;
		cout << "is FA stucked? " << ad.stuck() << endl;

		ad.restart();
		ad.advance('a');
		ad.advance('b');
		ad.advance('c');
		ad.advance('e');

		cout << "whats current state? " << ad.whatscurrent() << endl;
		cout << "FA in final State? " << ad.in_final() << endl;
		cout << "is FA stucked? " << ad.stuck() << endl;
	}
};

void FAAddTest()
{
	FA_Add_TestClass faatc;
	faatc.FA_Add_Test();
}