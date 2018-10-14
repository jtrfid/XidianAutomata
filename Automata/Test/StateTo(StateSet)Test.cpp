//#include "../stdafx.h"  // fatal error C1010: �ڲ���Ԥ����ͷʱ����������ļ���β���Ƿ���������Դ����ӡ�#include "stdafx.h"��?
#include "stdafx.h"  // ��Ȼ��TestĿ¼���޴��ļ�������ȴƭȡ�˱�������������������
#include <iostream>
#include "../StateSet.h"
#include "../StateTo.h"

using namespace std;

/***************************************************************
   StateTo<T> ����state to T(eg. StateSet)��ӳ��(map)��ϵ��
   T *data; �ڲ�ʹ��data[state]��ʾ����ӳ���ϵ��
   set_domain(const int r)���ö�̬����data�Ĵ�С����ʾ�洢���ֹ�ϵ������,��*data�����˴洢�ռ䡣
   int howmany; ��ʾ��̬����data��С���������䲿��(expansion_extra����)
   int in_use; ��ʾʵ��ʹ�õ�data��С��
   ���������������Ƿ���state r to T��ӳ��(map),ǰ�߷���Not const T&���������ã����߷���const T&�����ڲ�ѯ��
   ���߾�û�и�data[r]��ֵ�������̳�����ɡ�
   T& map(const State r); retun data[r];  Not const���������ã�
   const T& lookup(const State r) return data[r]�����ڲ�ѯ�����������и�data[r]��ֵ�����ʹ�á�
 ***************************************************************/
void basicStateToStateSetTest()
{
	cout << "====basicStateToStateSetTest()\n";
	StateTo<StateSet> st;
	st.set_domain(5); // ��������
	cout << "domain(): " << st.domain() << endl;  // 5
	cout << "st: " << st << endl;

	// ���������������Ƿ���state r to T��ӳ��(map), ǰ�߷���Not const T&���������ã����߷���const T&�����ڲ�ѯ��
	// ���߾�û�и�data[r]��ֵ�������̳�����ɡ�
	// StateSet set1 = st.map(1);    
	// StateSet set2 = st.lookup(1); 
}

/***********************************************************
  StateTo<T>& StateTo<T>::disjointing_union(const StateTo<T>& r)
  �ϲ�this��r ==> this����֤���ص�, this.domain += r.domain;
 ***********************************************************/
void disjointing_unionTest()
{
	cout << "====disjointing_unionTest()\n";
	StateTo<StateSet> st1,st2;
	st1.set_domain(10); // ����st1����
	st2.set_domain(20); // ����st1����
	cout << "st1,st2 domain(): " << st1.domain() << "," << st2.domain() << endl;  // 10,20
	cout << "disjoining_union\n";
	st1.disjointing_union(st2);
	cout << "st1,st2 domain(): " << st1.domain() << "," << st2.domain() << endl;  // 30,20
}

void StateToStateSetTest()
{
	cout << "====StateToStateSetTest()====\n";
	basicStateToStateSetTest();
	disjointing_unionTest();
}