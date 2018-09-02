// Automata.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdlib>
#include <string>
#include <sstream>
#include "CharRange.h"
#include "TransRel.h"
#include "StateTo.h"
#include "DTransRel.h"
#include "Dconstrs.h"

using namespace std;

int main()
{
	RE r;
	cout << "input regular expression(RE):";
	cin >> r;
	cout << "your RE:" << r << endl;

	istringstream is("a+b cd");
	string s1, s2;
	is >> s1 >> s2;
	cout << s1 << ',' << s2 << endl;
	/*  
	DFA dfa;
	dfa = ASU(r);
	cout << dfa << endl;*/

	//CharRange cr('a', 'x');
	//cout << cr << endl;
	//cout << cr.low() << "," << cr.high() << endl;
	
	//TransRel tr;
	//tr.set_domain(20);
	//cout << tr << endl;

	//DTransRel dr;
	//dr.set_domain(10);
	//cout << dr << endl;

	//StateTo<Trans> st;
	//st.set_domain(10);
	//st.map(1);
	//cout << st;

	//Trans t;
	//cout << t << endl;  // ok
	
	



	system("pause");
	return 0;
}

