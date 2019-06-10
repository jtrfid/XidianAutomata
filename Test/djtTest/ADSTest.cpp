#include <iostream>
#include "DFA.h"
#include "TCTHelper.h"

using namespace std;

class ADSTestClass
{
public:
	DFA DfaInstance()
	{
		DFA_components dfa_com1;

		int stateNum = 20;
		while (stateNum--)
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
		dfa_com1.T.add_transition(0, 'd', 1);
		dfa_com1.T.add_transition(0, '1', 2);
		dfa_com1.T.add_transition(10, 'b', 19);
		dfa_com1.T.add_transition(10, '9', 12);
		dfa_com1.T.add_transition(10, 'd', 8);
		CharRange cr1('C', 'E');
		dfa_com1.T.add_transition(15, cr1, 8);
		CharRange cr2('c', 'e');
		dfa_com1.T.add_transition(15, cr2, 9);
		dfa_com1.T.add_transition(10, cr2, 9);
		dfa_com1.T.add_transition(15, 'f', 12);
		dfa_com1.T.add_transition(19, '8', 0);

		DFA dfa1(dfa_com1);

		return dfa1;
	}

	void ADSTest1()
	{
		DFA dfa1 = DfaInstance(); // DFA对象实例
		cout << "dfa1:" << dfa1 << endl;

		// 为了与TCT对应，TCTHelper数据成员中字母表是以下约定的整数值，使用这些基本信息生成ADS文件。
		/******************
		按照约定，DFA转移表字母的整数值:
		 case 1: ['0', '9'] == > [0, 9]
		 case 2: ['a', 'z'] == > [10, 35]
		 case 3: ['A', 'Z'] == > [36, 61]
		 other case is illegal.
		 ******************/
		TCTHelper tct1;
		// 由DFA对象生成ADS/test.ADS文件
		tct1.perform(dfa1, "test.ads");
		cout << "tct1:" << tct1 << endl;

		// 当前对象转换为DFA
		DFA_components dfa_com1 = tct1.getDFA();
		DFA dfa2(dfa_com1);
		cout << "dfa2:" << dfa2 << endl; 

		// 依据ADS/test.ADS文件，生成当前对象
		TCTHelper tct2;
		tct2.adsToDFA("test.ads");
		cout << "tct2:" << tct2 << endl;

		// 判断两个tct对象是否相同，即代表同样一个DFA
		cout << "tct1 == tct2 ? " << (tct1 == tct2) << endl;
		assert(tct1 == tct2);

		// 键盘键入DFA，生成ADS文件
		cout << "键盘键入DFA\n";
		TCTHelper tct3;
		cin >> tct3;
		tct3.perform("DFATest.ADS"); //生成DFATest.ADS文件
		cout << "tct3:" << tct3 << endl;

		DFA_components dfa_com3 = tct3.getDFA();
		DFA dfa3(dfa_com3);
		cout << "dfa3:" << dfa3 << endl;
	}

};

void ADSTest()
{
	ADSTestClass test;
	test.ADSTest1();
}