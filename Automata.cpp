// Automata.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cstdlib>
#include "CharRange.h"
using namespace std;

int main()
{
	
	CharRange cr('a', 'x');

	cout << cr.low() << "," << cr.high() << endl;

	system("pause");
	return 0;
}

