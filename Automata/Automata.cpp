// Automata.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdlib>
#include "CharRange.h"
#include "TransRel.h"
#include "StateTo.h"
#include "DTransRel.h"

using namespace std;

int main()
{
	//CharRange cr('a', 'x');
	//cout << cr << endl;
	//cout << cr.low() << "," << cr.high() << endl;
	
	TransRel tr;
	tr.set_domain(20);
	cout << tr << endl;

	DTransRel dr;
	dr.set_domain(10);
	cout << dr << endl;

	//StateTo<Trans> st;
	//st.set_domain(10);
	//st.map(1);
	//cout << st;

	//Trans t;
	//cout << t << endl;  // ok
	
	



	system("pause");
	return 0;
}

