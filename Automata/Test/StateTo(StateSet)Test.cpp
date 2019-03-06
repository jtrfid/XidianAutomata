#include <iostream>
#include "../StateSet.h"
#include "../StateTo.h"

using namespace std;

class StateToStateSetTestClass
{
public:
	/***************************************************************
	   StateTo<T> 描述state to T(eg. StateSet)的映射(map)关系。
	   T *data; 内部使用data[state]表示这种映射关系。
	   set_domain(const int r)设置动态数组data的大小，表示存储这种关系的容量,对*data分配了存储空间。
	   int howmany; 表示动态数组data大小，包含扩充部分(expansion_extra常量)
	   int in_use; 表示实际使用的data大小。
	   以下两个函数都是返回state r to T的映射(map),前者返回Not const T&，用于设置；后者返回const T&，用于查询。
	   二者均没有给data[r]赋值。留给继承类完成。
	   T& map(const State r); retun data[r];  Not const，用于设置；
	   const T& lookup(const State r) return data[r]，用于查询。在派生类中给data[r]赋值后才能使用。
	 ***************************************************************/
	void basicStateToStateSetTest()
	{
		cout << "====basicStateToStateSetTest()\n";
		StateTo<StateSet> st;
		st.set_domain(5); // 设置容量
		cout << "domain(): " << st.domain() << endl;  // 5
		cout << "st: " << st << endl;

		// 以下两个函数都是返回state r to T的映射(map), 前者返回Not const T&，用于设置；后者返回const T&，用于查询。
		// 二者均没有给data[r]赋值。留给继承类完成。
		// StateSet set1 = st.map(1);    
		// StateSet set2 = st.lookup(1); 
	}

	/***********************************************************
	  StateTo<T>& StateTo<T>::disjointing_union(const StateTo<T>& r)
	  合并this和r ==> this，保证不重叠, this.domain += r.domain;
	 ***********************************************************/
	void disjointing_unionTest()
	{
		cout << "====disjointing_unionTest()\n";
		StateTo<StateSet> st1, st2;
		st1.set_domain(10); // 设置st1容量
		st2.set_domain(20); // 设置st1容量
		cout << "st1,st2 domain(): " << st1.domain() << "," << st2.domain() << endl;  // 10,20
		cout << "disjoining_union\n";
		st1.disjointing_union(st2);
		cout << "st1,st2 domain(): " << st1.domain() << "," << st2.domain() << endl;  // 30,20
	}
};

void StateToStateSetTest()
{
	cout << "====StateToStateSetTest()====\n";
	StateToStateSetTestClass test;
	test.basicStateToStateSetTest();
	test.disjointing_unionTest();
}