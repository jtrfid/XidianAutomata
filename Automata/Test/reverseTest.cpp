#include "DFA.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// reverse test
void reverseTest1()
{
	DFA_components dfa_com1;
	int i = 3;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}
	// StateSet S  开始状态集
	dfa_com1.S.set_domain(dfa_com1.Q.size());
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(dfa_com1.Q.size());
	dfa_com1.F.add(0);
	dfa_com1.F.add(1);


	dfa_com1.T.set_domain(dfa_com1.Q.size());
	dfa_com1.T.add_transition(0, 'a', 1);
	dfa_com1.T.add_transition(1, 'b', 2);


	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	DSDFARev rev(dfa_com1.F, &(dfa_com1.T), &(dfa_com1.S));
	cout << "rev:" << rev << endl;
	cout << "final:" << rev.final() << endl;
	cout << "out-T(a):" << rev.out_transition('a') << endl;
	cout << "out-T(b):" << rev.out_transition('b') << endl;
	cout << "out-label:" << rev.out_labels() << endl;

	cout << "dfa:" << dfa1 << endl;

	//construct_components(DSDFARev(F, &T, &S)));
	//DSDFARev::DSDFARev(const StateSet& rq, const DTransRel *rT, const StateSet *rS)

	dfa1.reverse();
	cout << "reverse:" << dfa1 << endl;

	dfa1.reverse();
	cout << "reverse().reverse():" << dfa1 << endl;
}

// reverse test
void reverseTest2()
{
	DFA_components dfa_com1;
	int i = 3;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}
	// StateSet S  开始状态集
	dfa_com1.S.set_domain(dfa_com1.Q.size());
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(dfa_com1.Q.size());
	dfa_com1.F.add(0);
	dfa_com1.F.add(1);


	dfa_com1.T.set_domain(dfa_com1.Q.size());
	dfa_com1.T.add_transition(0, 'a', 1);
	dfa_com1.T.add_transition(1, 'b', 2);
	

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	DSDFARev rev(dfa_com1.F, &(dfa_com1.T), &(dfa_com1.S));
	cout << "rev:" << rev << endl;
	cout << "final:" << rev.final() << endl;
	cout << "out-T(a):" << rev.out_transition('a') << endl;
	cout << "out-T(b):" << rev.out_transition('b') << endl;
	cout << "out-label:" << rev.out_labels() << endl;

	cout << "dfa:" << dfa1 << endl;
	
	//construct_components(DSDFARev(F, &T, &S)));
	//DSDFARev::DSDFARev(const StateSet& rq, const DTransRel *rT, const StateSet *rS)

	//dfa1.reverse();
	//cout << "reverse:" << dfa1 << endl;
}

// reverse test
void reverseTest3()
{
	DFA_components dfa_com1;
	int i = 3;
	while (i--)
	{
		dfa_com1.Q.allocate();
	}
	// StateSet S  开始状态集
	dfa_com1.S.set_domain(dfa_com1.Q.size());
	dfa_com1.S.add(0);

	// StateSet F  结束状态集
	dfa_com1.F.set_domain(dfa_com1.Q.size());
	dfa_com1.F.add(1);
	dfa_com1.F.add(2);


	dfa_com1.T.set_domain(dfa_com1.Q.size());
	dfa_com1.T.add_transition(0, 'a', 1);
	dfa_com1.T.add_transition(0, 'b', 2);
	dfa_com1.T.add_transition(1, 'b', 2);
	dfa_com1.T.add_transition(2, 'a', 1);

	//实例化一个DFA对象
	DFA dfa1(dfa_com1);
	cout << "\n************ DFA\n" << std::flush;
	cout << dfa1 << endl;

	dfa1.reverse();
	cout << "reverse:" << dfa1 << endl;
}

//#define TO_FILE

void reverseTest()
{
	cout << "start\n";
#ifdef TO_FILE
	// 重定向cout至file 
	fstream fs;
	fs.open("test.txt", ios::out);
	streambuf *stream_buffer_cout = cout.rdbuf(); // cout buffer
	streambuf *stream_buffer_file = fs.rdbuf(); // file buffer
	cout.rdbuf(stream_buffer_file);
#endif

	reverseTest1();
	//reverseTest2();
	//reverseTest3();

#ifdef TO_FILE
	// 恢复cout
	fs.close();
	std::cout.rdbuf(stream_buffer_cout);
#endif
}