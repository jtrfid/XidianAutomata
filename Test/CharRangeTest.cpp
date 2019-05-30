#include<iostream>
#include"CharRange.h"

using namespace std;

class CharRangeTestClass
{
public:
	CharRangeTestClass();
	void InitialTest()
	{
		cout << "InitialTest:" << endl;
		CharRange cr1('a', 'd');
		cout << "cr1:" << cr1 << endl;//['a','d']
		cout << "cr1 contains 'a'? " << cr1.contains('b') << endl;//1
		cout << "cr1 contains 'e'? " << cr1.contains('e') << endl;//0
		cout << "cr1 upper character? " << cr1.high() << endl;//d
		cout << "cr1 lower character? " << cr1.low() << endl;//a
	}
	void AdvanceTest()
	{
		cout << "AdvanceTest" << endl;
		CharRange cr1('a', 'd');
		CharRange cr2('c', 'f');
		CharRange cr3('g');
		CharRange cr4('a', 'g');
		CharRange cr5('a', 'c');
		CharRange cr6('b', 'g');
		//�����ַ����Ƿ��ص�������
		cout << "cr1 overlap_or_adjacent with cr2? " << cr1.overlap_or_adjacent(cr2) << endl;//�ص�
		cout << "cr2 overlap_or_adjacent with cr3? " << cr2.overlap_or_adjacent(cr3) << endl;//����
		cout << "cr1 overlap_or_adjacent with cr3? " << cr1.overlap_or_adjacent(cr3) << endl;//�Ȳ��ص�Ҳ������
		//�����ַ����Ƿ�����ͬ����
		cout << "cr1 intercests with cr2? " << cr1.not_disjoint(cr2) << endl;//����ͬ����
		cout << "cr1 intercests with cr3? " << cr1.not_disjoint(cr3) << endl;//����ͬ����
		//��Խ�����һЩ������
		cout << "cr1-cr1��cr2: " << cr1.left_excess(cr2) << endl;//�˴�����cr1-cr1��cr2
		cout << "cr2-cr1��cr2: " << cr1.right_excess(cr2) << endl;//�˴�����cr2-cr1��cr2
		cout << "cr1= " << cr1 << endl;
		//���²�����ı�ԭ�ַ���
		cout << "cr2=cr2��cr3 " << cr2.merge(cr3) << endl;//�ϲ����������ַ�������ʱcr2=['c','g']
		cout << "cr1=cr1��cr3 " << cr1.merge(cr3) << endl;//�����Դ˳�Ա������ϲ����������ַ������Һϲ����ַ���cr1=['low(cr1��cr3)','high(cr1��cr3)'],��ʱcr1=['a','g']
		cout << "cr2=cr2��cr1 " << cr2.intersection(cr1) << endl;//cr2=cr2��cr1
		//ordering(CharRange& r):if *this==r,return 0;if *this.lo==r.lo&&*this>r,return>0;else return<0;
		cout << cr1.ordering(cr4) << endl;//return 0
		cout << cr1.ordering(cr5) << endl;//return>0
		cout << cr1.ordering(cr6) << endl;//return<0
		//�ַ����ȽϹ���
		CharRange cr7('a', 'g');
		CharRange cr8('a', 'c');
		cout << "cr1==cr7? " << cr1.operator==(cr7) << endl;//cr1=cr7
		cout << "cr1!=cr8? " << cr1.operator!=(cr8) << endl;//cr1!=cr8
		cout << "cr1<=cr8? " << cr1.operator<=(cr8) << endl;//cr1>=cr8
		cout << "cr1>=cr8? " << cr1.operator>=(cr8) << endl;//cr1>=cr8
	}
};

CharRangeTestClass::CharRangeTestClass()
{
	cout << "CharRangeTest:" << endl;
}

void CharRangeTest()
{
	CharRangeTestClass t;
	//t.InitialTest();
	t.AdvanceTest();
}