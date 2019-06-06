#include <iostream>
#include "DFA.h"
#include "TCTHelper.h"

using namespace std;

class ADSTestClass
{
public:
	void ADSTest1()
	{
		DFA_components dfa_com1;

		// StateSet S  开始状态集
		dfa_com1.S.set_domain(3);
		dfa_com1.S.add(0);
		//dfa_com1.S.add(1);

		// StateSet F  结束状态集
		dfa_com1.F.set_domain(3);
		dfa_com1.F.add(1);
		dfa_com1.F.add(2);
		/*dfa_com1.F.add();
		dfa_com1.F.add();*/
		int i = 3;
		while (i--)
		{
			dfa_com1.Q.allocate();
		}

		dfa_com1.T.set_domain(3);
		dfa_com1.T.add_transition(0, '0', 1);
		dfa_com1.T.add_transition(0, '1', 2);

		DFA dfa1(dfa_com1);
		cout << dfa1 << endl;
		TCTHelper my;
		my.perform(dfa1, "test.ads");
	}
};

void ADSTest()
{
	ADSTestClass test;
	test.ADSTest1();
}