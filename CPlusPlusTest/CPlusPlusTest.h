#pragma once
//#include "stdafx.h"
#include <iostream>
using namespace std;

class A
{
public:
	const int max = 100;
	A() :n(0)  // 默认构造函数
	{
		cout << "默认构造函数：" << n << endl;
	}
	A(int n) :n(n) // 自定义构造函数
	{
		cout << "自定义构造函数：" << n << endl;
	}
	A(const A& a) :n(a.n) // 复制构造函数
	{
		cout << "复制构造函数：" << n << endl;
	}
	const A& operator=(const A& r) // 重载操作符=
	{
		n = r.n;
		return(*this);
	}
	~A()
	{
		cout << "析构函数:" << n << endl;
	}
	int n;
};
