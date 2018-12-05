//#include "../stdafx.h"  // fatal error C1010: 在查找预编译头时遇到意外的文件结尾。是否忘记了向源中添加“#include "stdafx.h"”?
#include "stdafx.h"  // 虽然在Test目录下无此文件，但是却骗取了编译器，无上述错误了
#include <iostream>
#include "../Sigma.h"
#include "../FA.h"
#include "../Constrs.h"

using namespace std;

/*******************************************************************
	Reg<RE> re1;
	//Reg<RE> re1 = Reg<RE>(); // 等效

	Definition 4.30 (Homomorphism from RE to [RFA]): We define rfa in RE ---> [RFA],
	 to be the unique homomorphism from REs to [RFA]
	//RFA rfa1(re);     // 在RFA.h，RFA.cpp定义和实现RFA(const RE& e)
	RFA rfa1 = rfa(re); // 等效，在Constrs.h中封装，RFA rfa(const RE& r)

	Definition 4.29 (Sigma-algebra of RFA's): The carrier set is [RFA], p33-35
	//RFA rfa1 = Reg<RFA>(re); // 在Sigma.h中定义Reg(const RE& r)，sigma-operator在Sig-RFA.cpp中定义
	RFA rfa1 = rfa_sigma(re);  // 等效,在Constrs.h封装，RFA rfa_sigma(const RE& r)
   
 *******************************************************************/
class RFATestClass
{
public:
	/****************************************************************
	 Example 3.15 (A regular expression),P18：(a | epsilon) concat b* ，
	 Reg<RE> thest:
	 non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
	 unary operator(star,plus,question): this ==> left = this, right = 0
	 binary operator(union(or),concat(dot)): this ==> left(this) operator right
	 ****************************************************************/
	void reExample315(RE& re)
	{
		//cout << "=====reExample315=====\n";
		Reg<RE> left, right;

		//// RE =  a | epsilon
		left.symbol('a');
		right.epsilon();
		left.Or(right);
		//cout << left << endl;  // | 'a' 1(epsilon)

		// b *
		right.symbol('b');
		right.star();
		//cout << right << endl; // * 'b'

		// (a | epsilon) concat b* 
		left.concat(right);
		//cout << left << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)

		re = left;
	}

	/*************************************************************************
	 Definition 4.30 (Homomorphism from RE to [RFA]): We define rfa in RE ---> [RFA], 
	 to be the unique homomorphism from REs to [RFA]
	 //RFA rfa1(re);     // 在RFA.h，RFA.cpp定义和实现RFA(const RE& e)
	 RFA rfa1 = rfa(re); // 等效，在Constrs.h中封装，RFA rfa(const RE& r)
	 *************************************************************************/
	RFA re2RFA_homomorphismTest(const RE& re)
	{
		cout << "=====re2RFA_homomrphismTest=====\n";
		//RFA rfa1(re);     // 在RFA.h，RFA.cpp定义和实现RFA(const RE& e)
		RFA rfa1 = rfa(re); // 等效，在Constrs.h中封装，RFA rfa(const RE& r)
		return rfa1;
	}

	/*************************************************************************
	  Definition 4.29 (Sigma-algebra of RFA's): The carrier set is [RFA], p33-35
	  //RFA rfa1 = Reg<RFA>(re); // 在Sigma.h中定义Reg(const RE& r)，sigma-operator在Sig-RFA.cpp中定义
	  RFA rfa1 = rfa_sigma(re);  // 等效,在Constrs.h封装，RFA rfa_sigma(const RE& r)
	 *************************************************************************/
	RFA rfa_sigmaTest(const RE& re)
	{
		cout << "=====rfa_sigmaTest=====\n";
		//RFA rfa1 = Reg<RFA>(re); // 在Sigma.h中定义Reg(const RE& r)，sigma-operator在Sig-RFA.cpp中定义
		RFA rfa1 = rfa_sigma(re);  // 等效,在Constrs.h封装，RFA rfa_sigma(const RE& r)
		return rfa1;
	}

	/***************************************************************************
	  RE --> LBFA:
	  (1) RE --> RFA
	      RFA rfa = RFA(re); // 或sigma代数运算：Reg<RFA>(re)
	  (2) Specially construct from an RFA(see Definition 4.28). RFA --> LBFA
      //LBFA lbfa = LBFA(rfa); // 在LBFA.h,LBFA.cpp定义 LBFA(const RFA& r)

	  // 等效，由LBFA中的LBFA& decode(const RFA& r)函数完成
	  // LBFA lbfa; lbfa = lbfa.decode(rfa);

	  /////// 综合(1),(2)
	  // Construction 4.32 (Berry-Sethi): Construction BS 属于 RE --> LBFA
	  // lbfa(E) = BS(E) = decode o rfa(E)
	  // 等效，在Constrs.h中封装LBFA BerrySethi(const RE& r)
	  // RE -->RFA: rfa = RFA(re); RFA --> LBFA, lbfa = LBFA(rfa) 或 lbfa = lbfa.decode(rfa)
	  LBFA lbfa = BerrySethi(re); 
	 ***************************************************************************/
	LBFA RFA2LBFA(const RE& re)
	{
		cout << "=====RFA2LBFA=====\n";
		RFA rfa = re2RFA_homomorphismTest(re);
		// RFA rfa = rfa_sigmaTest(re); // 返回同样的rfa

		//LBFA lbfa = LBFA(rfa); // 在LBFA.h,LBFA.cpp定义 LBFA(const RFA& r)

		// 等效，由LBFA中的LBFA& decode(const RFA& r)函数完成
		LBFA lbfa; lbfa = lbfa.decode(rfa);

		// 等效，在Constrs.h中封装LBFA BerrySethi(const RE& r)
		// RE -->RFA: rfa=RFA(re), RFA --> LBFA, LBFA(rfa)
		//LBFA lbfa = BerrySethi(re); 
		return lbfa;
	}
};

void RFATest()
{
	cout << "=====RFATest=====\n";
	RFATestClass test;
	RFA rfa1,rfa2;
	LBFA lbfa;
	RE re;
	test.reExample315(re);
	cout << "reExample315: " << re << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
	
	rfa1 = test.re2RFA_homomorphismTest(re); 
	cout << rfa1 << endl;
	/** RFA
		Q = [0,2) first = { 0  1 } last = { 0  1 }
		Qmap_inverse = { 'a'->0  'b'->1 }
		follow = 0->{ 1 } 1->{ 1 }
		Nullable = true
		final = false
		current = {}
		**/
	rfa2 = test.rfa_sigmaTest(re);
	cout << rfa2 << endl; // 同上

	lbfa = test.RFA2LBFA(re);
	cout << lbfa << endl;
	/**
	 LBFA
	Q = [0,3) s = 2 F = { 0  1  2 } Qmap_inverse = { 'a'->0  'b'->1 }
    follow = 0->{ 1 } 1->{ 1 } 2->{ 0  1 } current = {}
	 **/
}


