#include<iostream>
#include "WangHaoYu/StateToState.h"

class StateToStateTestClass
{
public:
	void basictest()
	{
		StateToState sti;
		sti.set_domain(5);

		sti.add(0, 1);
		sti.add(1, 2);
		sti.add(2, 3);

		cout << "sti = " << sti << endl;
		cout << "state 0 maps..." << sti.image(0) << endl;
		cout << "sti domain = " << sti << endl;

		sti.remove(0, 1);

		cout << "remove the map 0->1..." << endl;
		cout << "sti = " << sti <<endl;
	}
};

void StateToStateTest()
{
	StateToStateTestClass t;
	t.basictest();
}