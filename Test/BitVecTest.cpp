#include<iostream>
#include"BitVec.h"

using namespace std;

class BitVecTestClass
{
public:
	BitVecTestClass();
	~BitVecTestClass();

	/************
	initialize test
	************/
	void InitializingTest()
	{
		cout << "set&clear&output test:" << endl;
		BitVec bit1;
		bit1.set_width(10);
		bit1.set_bit(0);
		bit1.set_bit(1);
		bit1.set_bit(2);
		bit1.set_bit(4);
		bit1.set_bit(3);
		//bit1.set_bit(10);
		cout << "bit1=" << bit1 << endl;//{0,1,2,3,4}
		bit1.unset_bit(0);
		bit1.unset_bit(2);
		bit1.unset_bit(5);
		//bit1.unset_bit(10);
		cout << "bit1=" << bit1 << endl;//{1,3,4}
		bit1.clear();
		cout << "bit1=" << bit1 << endl;//{}
	}

	/**********
	search function test
	**********/
	void SearchFunctionTest()
	{
		cout << "BasicFunctionTest:" << endl;
		BitVec bit1, bit2;

		bit1.set_width(10);
		bit2.set_width(10);

		bit1.set_bit(0);
		bit1.set_bit(1);
		bit1.set_bit(2);
		bit1.set_bit(3);
		bit1.set_bit(4);
		bit2.set_bit(1);
		bit2.set_bit(3);

		cout << "bit1=" << bit1 << endl;//bit1={0,1,2,3,4}
		cout << "bit2=" << bit2 << endl;//bit2={1,3}
		cout << "howmany bits in bit1 set to 1? " << bit1.bits_set() << endl;//(5)
		assert(bit1.bits_set() == 5);
		cout << "bit1 width? " << bit1.width() << endl;//(10)
		assert(bit1.width() == 10);
		cout << "the smallest bit in bit1 set to 1? " << bit1.smallest() << endl;//(0)
		assert(bit1.smallest() == 0);
		cout << "is any bit in bit1 sets to 1? " << bit1.something_set() << endl;//(1)
		assert(bit1.something_set() == 1);
		cout << "is the 2nd bit in bit1 sets to 1? " << bit1.contains(1) << endl;//(1)
		assert(bit1.contains(1) == 1);
		cout << "is the 5th bit in bit1 sets to 1? " << bit1.contains(5) << endl;//(0)
		assert(bit1.contains(5) == 0);
		cout << "bits in bit1 are set to 1 contains which bits in bit2 are set to 1? " << bit1.contains(bit2) << endl;//(1)
		assert(bit1.contains(bit2) == 1);
		cout << "bits are set to 1 in bit1 have something common with bits are set to 1 in bit2? " << bit1.something_common(bit2) << endl;//(1)
		assert(bit1.something_common(bit2) == 1);

		int i = 1;

		cout << bit1.iter_next(i) << endl;//
		cout << bit1.iter_start(i) << endl;//
		cout << i << endl;//
		cout << bit1.iter_end(i) << endl;//i==-1?1:0
	}

	/**********
	compute function test
	**********/
	void ComputeFunctionTest()
	{
		cout << "ComputeFunctionTest:" << endl;
		BitVec bit1, bit2, bit3;

		bit1.set_width(10);
		bit2.set_width(9);
		bit3.set_width(10);

		bit1.set_bit(0);
		bit1.set_bit(1);
		bit1.set_bit(2);
		bit1.set_bit(3);
		bit1.set_bit(4);
		bit2.set_bit(3);
		bit2.set_bit(4);
		bit3.set_bit(1);
		bit3.set_bit(2);

		cout << "bit1=" << bit1 << endl;//bit1={0,1,2,3,4}
		cout << "bit2=" << bit2 << endl;//bit2={3,4}
		cout << "bit3=" << bit3 << endl;//bit3={1,2}

		bit2.left_shift(1);//

		cout << "bit2= " << bit2 << endl;//bit2={3,4}->{4,5}
		cout << "bit1=: " << bit1.bitwise_and(bit2) << endl;//{4}
		cout << "bit1=: " << bit1.bitwise_or(bit2) << endl;//{4,5}
		cout << "bit1=: " << bit1.bitwise_complement() << endl;//{0,1,2,3,6,7,8,9}
		cout << "set bits in bit1 to 0 which are setting to 1 in bit2: " << bit1.bitwise_unset(bit3) << endl;//bit1-bit3={0,3,6,7,8,9}
		cout << "bit1=bit2+bit1 width corporated: " << bit1.append(bit2) << endl;//bit1={0,3,6,7,8,9,14,15}
		cout << "bit1 width: " << bit1.width() << endl;//20
		assert(bit1.width() == 20);
	}

	/************
	operator test
	************/
	void OperatorFunctionTest()
	{
		cout << "OperatorFunctionTest:" << endl;
		BitVec bit1, bit2;

		bit1.set_width(4);
		bit2.set_width(4);

		bit1.set_bit(0);
		bit1.set_bit(1);
		bit2.set_bit(0);

		cout << bit1 << endl;//bit1={0,1}
		cout << bit2 << endl;//bit2={0}
		cout << "bit1==bit2? " << bit1.operator==(bit2) << endl;//bit1!=bit2; return 0;
		assert(bit1.operator==(bit2) == 0);
		cout << "bit1!=bit2? " << bit1.operator!=(bit2) << endl;//bit1!=bit2; return 1;
		assert(bit1.operator!=(bit2) == 1);
		cout << "let bit1 = bit2 " << bit1.operator=(bit2) << endl;//{0}
	}

private:

};

BitVecTestClass::BitVecTestClass()
{
	cout << "BitVecTest" << endl;
}

BitVecTestClass::~BitVecTestClass()
{
}

void BitVecTest()
{
	BitVecTestClass t;
	t.InitializingTest();
	t.SearchFunctionTest();
	t.ComputeFunctionTest();
	t.OperatorFunctionTest();
}