#pragma once
//#include "stdafx.h"
#include <iostream>
using namespace std;

class A
{
public:
	const int max = 100;
	A() :n(0)  // Ĭ�Ϲ��캯��
	{
		cout << "Ĭ�Ϲ��캯����" << n << endl;
	}
	A(int n) :n(n) // �Զ��幹�캯��
	{
		cout << "�Զ��幹�캯����" << n << endl;
	}
	A(const A& a) :n(a.n) // ���ƹ��캯��
	{
		cout << "���ƹ��캯����" << n << endl;
	}
	const A& operator=(const A& r) // ���ز�����=
	{
		n = r.n;
		return(*this);
	}
	~A()
	{
		cout << "��������:" << n << endl;
	}
	int n;
};
