#include<iostream>
#include"StatePool.h"

using namespace std;

class StatePoolTestClass {
public:
	void InitialTest()
	{
		StatePool sp;
		StatePool sp1;

		sp.allocate();//sp=[0,1)
		sp.allocate();//sp=[0,2)

		cout << "sp size: " << sp.size() << endl;//2
		assert(sp.size()==2);
		cout << "sp= " << sp << endl;//[0,2)
		cout << "is state 0 in sp? " << sp.contains(1) << endl;//1
		assert(sp.contains(1)==1);
		cout << "is state 3 in sp? " << sp.contains(3) << endl;//0
		assert(sp.contains(3)==0);

		sp1.allocate();//sp1=[0,1)

		cout << "sp1= " << sp1 <<endl;
		cout << "sp incorporate with sp1= " << sp.incorporate(sp1) << endl;//sp=[0,3)
	}
};

void StatePoolTest()
{
	cout << "StatePoolTest:" << endl;
	StatePoolTestClass t;
	t.InitialTest();
}