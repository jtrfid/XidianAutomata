#include <iostream>
#include "Sigma.h"
#include "FA.h"
#include "Constrs.h"
#include "LBFA.h"
#include "RBFA.h"
#include "FiniteAutomata.h"

using namespace std;
class BSTestClass
{
public:
	/****************************************************************
	 Reg<RE> thest:
	 non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
	 unary operator(star,plus,question): this ==> left = this, right = 0
	 binary operator(union(or),concat(dot)): this ==> left(this) operator right
	 ****************************************************************/
	
	void Reg_RE_Test()
	{
		cout << "=====Reg_RE_Test=====\n";
		/////////////// non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
		// RE = epsilon
		Reg<RE> re1;
		//Reg<RE> re1 = Reg<RE>(); // 等效
		re1.epsilon();
		cout << re1 << endl; // 1  ==> op = EPSILON, left = right = 0

		// RE = empty
		Reg<RE> re2;
		re2.empty();
		cout << re2 << endl;  // 0  ==> op = EMPTY, left = right = 0

		//// RE = a
		Reg<RE> re3;

		re3.symbol('a');
		cout << re3 << endl; // a  ==> op = SYMBOL, left = right = 0 

		////////////////////// unary operator(star,plus,question): this ==> left = this, right = 0
		/////// RE = b *
		Reg<RE> re4;
		re4.symbol('b');
		re4.star();
		cout << re4 << endl;  // * 'b' ==> op = STAR, left = b, right = 0

		/////// RE = b +
		Reg<RE> re41;
		re41.symbol('b');
		re41.plus();
		cout << re41 << endl;  // + 'b' ==> op = PLUS, left = b, right = 0

		/////// RE = b ?
		Reg<RE> re42;

		re42.symbol('b');
		re42.question();

		cout << re42 << endl;  // ? 'b'  ==> op = QUESTION, left = b,right = 0
		cout << "\n" << endl;

		/////////////// binary operator(union(or),concat(dot)): this ==> left(this) operator right
		//// RE =  a | epsilon
		Reg<RE> left, right;
		left.symbol('a');
		right.epsilon();
		left.Or(right);
		cout << left << endl;  // | 'a' 1(epsilon) ==> op = Or, left = a, right = EPSILON
		cout << "\n" << endl;
		//// RE =  a concat epsilon
		left.symbol('a');
		right.epsilon();
		left.concat(right);
		cout << left << endl;  // . 'a' 1(epsilon) ==> op = CONCAT, left = a, right = EPSILON
		cout << "以上为八个基础运算符的RE输出\n" << endl;
		////////////////////////////// 综合应用
		// RE = (a | epsilon)b* 

		//// RE =  a | epsilon
		left.symbol('a');
		right.epsilon();
		left.Or(right);
		// b *
		right.symbol('b');
		right.star();
		// (a | epsilon) concat b* 
		left.concat(right);
		cout << left << "————这是(a | epsilon) concat b* \n" << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)

		//(01)新增测试样例：蒋宗礼版自动机教材p127页习题4中挑选最具代表性的表达式进行改造使其更复杂
		//得：r+(sr?t|r|1)*——1就是epsilon
		//按照自顶向下方法对表达式进行拆分然后构造每步运算
		/*cout << "\n\n——新增测试样例\n" << endl;
		Reg<RE> left0, right0, left1, right1;//避免与上面代码混乱采取新的变量名尾缀
		left0.symbol('s');
		right0.symbol('r');
		right0.question();
		left0.concat(right0);
		right0.symbol('t');
		left0.concat(right0);//构成括号里的srt
		cout << left0 << "    这是sr?t \n" << endl;
		right0.symbol('r');
		right0.Or(right1.epsilon());//构成括号里的r|1
		cout << right0 << "    这是r|1 \n" << endl;
		left0.Or(right0);
		cout << left0 << "    这是sr?t+r|1 \n" << endl;
		left1.symbol('r');
		left1.plus();
		left0.star();
		left1.concat(left0);
		cout << left1 << "    这是最后结果r+(sr?t|r|1)* \n" << endl;//最后结果
		*/
	}
	void reExample315(RE& re)
	{
		//cout << "=====reExample315=====\n";
		Reg<RE> left, right;
		///// RE = (a | epsilon)b* 

		// RE =  a | epsilon
		left.symbol('a');
		right.epsilon();
		left.Or(right);
		//cout << left << endl;  // | 'a' 1(epsilon)

		// b *
		right.symbol('b');
		right.star();
		cout << right << endl; // * 'b'

		// (a | epsilon) concat b* 
		left.concat(right);
		//cout << left<<"    输出应该是(a | epsilon) concat b*\n " << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
		re = left;
	}

	//  RE =  (a ∪ b)ab
	void reExample2_9noStar(RE& re)
	{
		//cout << "=====reExample2_9noStar=====\n";
		Reg<RE> left, right;
		cout << "\n————————测试点11111\n" << endl;
		//  RE =  (a ∪ b) ab
		//left.Or(right).concat(right.symbol('a')).concat(right.symbol('b')); // result error
		left.symbol('a');
		left.Or(right.symbol('b'));
		//cout << left << endl;  // | 'a' 'b'

		left.concat(right.symbol('a'));
		//cout << left << endl;  // . | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		cout << left << endl;  // . . | 'a' 'b' 'a' 'b'

		re = left;
	}

	//  RE =  (* (a ∪ b)) ab

	void reExample2_9Star(RE& re)
	{
		//cout << "=====reExample2_9Star=====\n";
		Reg<RE> left, right;

		//  RE =  (* (a ∪ b)) ab
		left.symbol('a');
		left.Or(right.symbol('b'));
		left.star();
		//cout << left << endl;  // * | 'a' 'b'

		left.concat(right.symbol('a'));
		//cout << left << endl;  // . * | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		cout << left << endl;  // . . * | 'a' 'b' 'a' 'b'

		re = left;

	}
	void ex4(RE& re)  //RE = (a + b)*a + (aa)*
	{
		//cout << "=====ex4=====\n";
		Reg<RE> left, right;
		left.symbol('a');
		right.symbol('b');
		left.Or(right);
		left.star();
		right.symbol('a');
		left.concat(right);
		right.symbol('a');
		right.concat(right);
		right.star();
		left.Or(right);
		cout << left << "    (a+b)*a+(aa)*\n" << endl;
		re = left;

	}
	void ex5(RE& re)  //RE=((a | epsilon)+)b?cd*|(empty())
	{
		//cout << "=====ex5=====\n";
		Reg<RE> left, right;
		left.symbol('a');
		right.epsilon();
		left.Or(right);
		left.plus();
		right.symbol('b');
		right.question();
		left.concat(right);
		right.symbol('c');
		left.concat(right);
		right.symbol('d');
		right.star();
		left.concat(right);
		right.empty();
		left.Or(right);
		cout << left << "    ((a | epsilon)+)b?cd*|(empty())\n" << endl;
		re = left;

	}
	//  RE =  ((a ∪ b*)) ab（为了研究与RE =  (* (a ∪ b)) ab的区别多设立的一个同等作用的函数）
	/**
	void reExample2extra_9Star(RE& re)
	{
		cout << "\n=====reExample2extra_9Star=====\n";
		Reg<RE> left, right;

		//  RE =  ((a ∪ b*)) ab
		left.symbol('a');
		right.symbol('b');
		right.star();
		left.Or(right);

		//cout << left << endl;  //  | 'a' *'b'

		left.concat(right.symbol('a'));
		//cout << left << endl;  // .  | 'a' *'b' 'a'
		left.concat(right.symbol('b'));
		cout << left << endl;  // . .  | 'a' *'b' 'a' 'b'

		re = left;
	}
	**/
	
	//出现错误的地方，如果想直接LBFA->DFA的话
	
	DFA LBFA2DFA(LBFA lbfa) //实际就是RE->RFA->LBFA->DFA(找不到别的直接从LBFA到DFA)
	{
		
		cout << "=====LBFA2DFA=====\n";
		DFA dfa=lbfa.determinism();
		return dfa;
	}
	
	/**
	这样写也是可以的，就是RE->RFA->LBFA->DFA，但是由于我们这个测试目的就是测试BerrySethi()，
	所以BerrySethi()函数单独提出来是完成转换：RE->LBFA，我们只需要建立一个LBFA->DFA的函数就可以了
	也不用像RFATest里面那样中途经过RFA，这也就是文档里说的BS是一个将较于rfa()+decode()来说更为高效的方式
	DFA DFAfromLBFA(const RE& re) //实际就是RE->RFA->LBFA->DFA
	{
		cout << "=====DFAfromLBFA=====\n";
		DFA dfa = BerrySethi(re).determinism();
		return dfa;
	}
	**/
};
	void BSTest1()
	{
		cout << "=====BSTest1=====\n";
		BSTestClass test;
		LBFA lbfa1,lbfa2;
		RBFA rbfa1, rbfa2;
		RE re;
		test.reExample315(re);
		cout << "样例1，RE=（a|epsilon) concat  b*: " << re << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)

		
		lbfa1 = BerrySethi(re); 
		lbfa2 = BS_variation(re);
		rbfa1 = BerrySethLdual(re);
		rbfa2 = BS_variation_dual(re);
		cout << "\n—————————LBFA1:\n" <<lbfa1 << endl;
		cout << "\n—————————LBFA2:\n" << lbfa2 << endl;
		cout << "\n—————————RBFA1:\n" << rbfa1 << endl;
		cout << "\n—————————RBFA2:\n" << rbfa2 << endl;
		/**
		 LBFA1————由状态转移图可得RE=(a|1)b*
		Q = [0,3) s = 2 F = { 0  1  2 } Qmap_inverse = { 'a'->0  'b'->1 }
		follow = 0->{ 1 } 1->{ 1 } 2->{ 0 1 }
		current = {}
		 LBFA2————
		 Q = [0,3) s = 0 F = { 0  1  2 } Qmap_inverse = { '$'->0  'a'->1  'b'->2 }
		follow = 0->{ 1 2 } 1->{ 2 } 2->{ 2 }
		current = {}
		 RBFA1————如果把s=0是入口是'a'算进去就是正确的，但是缺少1->2的转移条件？算空转移吗？加上'$'是完整的，代表什么？
	    Q = [0,3) S = { 0  1  2 } f = 2 Qmap_inverse = { 'a'->0  'b'->1 }
		follow = 0->{ 1 2 } 1->{ 1 2 }
		current = {}
		 RBFA2————
		Q = [0,3) S = { 2 } f = 2 Qmap_inverse = { 'a'->0  'b'->1  '$'->2 }
		follow = 0->{ 1 2 } 1->{ 1 2 } 
		current = {}
			 **/
		cout << "以下分别输出lbfa1和lbfa2各自转换的DFA和lbfa1通过另外一种方式输出的DFA\n" << endl;
		DFA BSTest1_dfa1 = lbfa1.determinism();
		cout << "————BSTest1_dfa1:" << BSTest1_dfa1 << endl;//——————————————————————成功转换成DFA
		DFA BSTest1_dfa2 = lbfa2.determinism();
		cout << "————BSTest1_dfa2:" << BSTest1_dfa2 << endl;//——————————————————————成功转换成DFA
		
		DFA BSTest1_dfa3 = test.LBFA2DFA(lbfa1);
		cout << "————BSTest1_dfa3:" << BSTest1_dfa3 << endl;
		/**
		DFA————由状态转移图可得RE=(a|1)b*
		Q = [0,3) S = { 0 } F = { 0  1  2 }
		Transitions = 0->{ 'a'->1  'b'->2 } 1->{ 'b'->2 } 2->{ 'b'->2 }
		current = -1
		**/
		FiniteAutomata ffa1;
		ffa1.perform(BSTest1_dfa1, "BSTest1_dfa1.ADS");
		FiniteAutomata ffa2;
		ffa2.perform(BSTest1_dfa2, "BSTest1_dfa2.ADS");
		FiniteAutomata ffa3;
		ffa3.perform(BSTest1_dfa3, "BSTest1_dfa3.ADS");
	}
	void BSTest2()
	{
		cout << "=====BSTest2=====\n";
		BSTestClass test;
		LBFA lbfa1, lbfa2;
		RBFA rbfa1, rbfa2;
		RE re;
		test.reExample2_9noStar(re);
		cout << "样例2，RE=（a∪b)ab: " << re << endl; // . . | 'a' 'b' 'a' 'b'

		lbfa1 = BerrySethi(re);
		lbfa2 = BS_variation(re);
		rbfa1 = BerrySethLdual(re);
		rbfa2 = BS_variation_dual(re);
		cout << "\n—————————LBFA1:\n" << lbfa1 << endl;
		cout << "\n—————————LBFA2:\n" << lbfa2 << endl;
		cout << "\n—————————RBFA1:\n" << rbfa1 << endl;
		cout << "\n—————————rBFA2:\n" << rbfa2 << endl;
		/**
	     LBFA1————画状态图得RE=（a∪b)ab
	     Q = [0,5) s = 4 F = { 3 }
	     Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
	     follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{} 4->{ 0  1 }
	     current = {}
		 LBFA2————
		 Q = [0,5) s = 0 F = { 4 }
		 Qmap_inverse = { '$'->1 'a'->1  'b'->2  'a'->3  'b'->4 }
		 follow = 0->{ 1 2 } 1->{ 3 } 2->{ 3 } 3->{ 4 } 4->{ }
		 current = {}
		 RBFA1————如果把s=0/1的入口'a''b'算进去就是正确的，但是缺少3->4的转移条件？算空转移吗？加上'$'是完整的，代表什么？
		 Q = [0,5) s = { 0 1 } F = 4
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
		 follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{ 4 } 
		 current = {}
		 RBFA2————
		 Q = [0,5) s = { 4 } F = 4
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 '$'->4 }
		 follow = 0->{ 2 } 1->{ 2 } 2->{ 3 } 3->{ 4 }
		 current = {}
			 **/
		cout << "以下分别输出lbfa1和lbfa2各自转换的DFA和lbfa1通过另外一种方式输出的DFA\n" << endl;
		DFA BSTest2_dfa1 = lbfa1.determinism();
		cout << "————BSTest2_dfa1:" << BSTest2_dfa1 << endl;//——————————————————————成功转换成DFA
		DFA BSTest2_dfa2 = lbfa2.determinism();
		cout << "————BSTest2_dfa2:" << BSTest2_dfa2 << endl;//——————————————————————成功转换成DFA
		
		DFA BSTest2_dfa3 = test.LBFA2DFA(lbfa1);
		cout << "————BSTest2_dfa3:" << BSTest2_dfa3 << endl;
		/**
	    DFA————画状态图得RE=（a∪b)ab
    	 Q = [0,5) 	S = { 0 } 	F = { 4 }
	     Transitions = 0->{ 'a'->1  'b'->2 }  1->{ 'a'->3 }	2->{ 'a'->3 } 3->{ 'b'->4 }
	     4->{} current = -1
	     **/
		FiniteAutomata ffa1;
		ffa1.perform(BSTest2_dfa1, "BSTest2_dfa1.ADS");
		FiniteAutomata ffa2;
		ffa2.perform(BSTest2_dfa2, "BSTest2_dfa2.ADS");
		FiniteAutomata ffa3;
		ffa3.perform(BSTest2_dfa3, "BSTest2_dfa3.ADS");
	}
	
	void BSTest3()
	{
		cout << "=====BSTest3=====\n";
		BSTestClass test;
		LBFA lbfa1, lbfa2;
		RBFA rbfa1, rbfa2;
		RE re;
		test.reExample2_9Star(re);
		cout << "样例3，RE=(（a∪b)*)ab: " << re << endl; // . . * | 'a' 'b' 'a' 'b'


		lbfa1 = BerrySethi(re);
		lbfa2 = BS_variation(re);
		rbfa1 = BerrySethLdual(re);
		rbfa2 = BS_variation_dual(re);
		cout << "\n—————————LBFA1:\n" << lbfa1 << endl;
		cout << "\n—————————LBFA2:\n" << lbfa2 << endl;
		cout << "\n—————————RBFA1:\n" << rbfa1 << endl;
		cout << "\n—————————rBFA2:\n" << rbfa2 << endl;
		/**
	     LBFA————由状态转移图可得RE=(a∪b)*ab————加了新的状态q4作为唯一起始状态使得 少了RFA中只有一个b的情况
	     Q = [0,5)  s = 4  F = { 3 }
	     Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
         follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{}   4 ->{ 0 1 2 }
	     current = {}
		 LBFA2————由状态转移图可得RE=(a∪b)*ab
		 Q = [0,5)  s = 0  F = { 4 }
		 Qmap_inverse = { '$'->0  'a'->1  'b'->2  'a'->3  'b'->4 }
		 follow = 0->{ 1  2  3 }   1->{ 1  2  3 }  2->{ 1  2  3 }  3->{ 4 }   4 ->{ }
		 current = {}


		 RBFA1————把输入算上也是对的，大致情况同上所述（记得按照上面改过的改+注释一下）
		 Q = [0,5)  s = { 0  1  2 }  F = 4
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3 }
		 follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{ 4 }   4 ->{ }
		 current = {}
		 RBFA2————大致情况同上所述（记得按照上面改过的改+注释一下）
		 Q = [0,5)  s = 4  F = { 4 }
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'b'->3  '$'->4  }
		 follow = 0->{ 0  1  2 }   1->{ 0  1  2 }  2->{ 3 }  3->{ 4 }   4 ->{ }
		 current = {}
			 **/
		cout << "以下分别输出lbfa1和lbfa2各自转换的DFA和lbfa1通过另外一种方式输出的DFA\n" << endl;
		DFA BSTest3_dfa1 = lbfa1.determinism();
		cout << "————BSTest3_dfa1:" << BSTest3_dfa1 << endl;//——————————————————————成功转换成DFA
		DFA BSTest3_dfa2 = lbfa2.determinism();
		cout << "————BSTest3_dfa2:" << BSTest3_dfa2 << endl;//——————————————————————成功转换成DFA
		
		DFA BSTest3_dfa3 = test.LBFA2DFA(lbfa1);
		cout << "————BSTest3_dfa3:" << BSTest3_dfa3 << endl;
		/**
		DFA from LBFA(————由状态转移图得出RE=(a∪b)*ab)
		Q = [0,4)  S = { 0 }   F = { 3 }
		Transitions =
		0->{ 'a'->1  'b'->2 }
		1->{ 'a'->1  'b'->3 }
		2->{ 'a'->1  'b'->2 }
		3->{ 'a'->1  'b'->2 }
		current = -1
		 **/
		FiniteAutomata ffa1;
		ffa1.perform(BSTest3_dfa1, "BSTest3_dfa1.ADS");
		FiniteAutomata ffa2;
		ffa2.perform(BSTest3_dfa2, "BSTest3_dfa2.ADS");
		FiniteAutomata ffa3;
		ffa3.perform(BSTest3_dfa3, "BSTest3_dfa3.ADS");
      }
	void BSTest4()
	{
		cout << "=====BSTest4=====\n";
		BSTestClass test;
		LBFA lbfa1, lbfa2;
		RBFA rbfa1, rbfa2;
		RE re;
		test.ex4(re);
		cout << "样例4，RE=(a+b)*a+(aa)*: " << re << endl; // | . * | 'a' 'b' 'a' * . 'a' 'a'

		lbfa1 = BerrySethi(re);
		lbfa2 = BS_variation(re);
		rbfa1 = BerrySethLdual(re);
		rbfa2 = BS_variation_dual(re);
		cout << "\n—————————LBFA1:\n" << lbfa1 << endl;
		cout << "\n—————————LBFA2:\n" << lbfa2 << endl;
		cout << "\n—————————RBFA1:\n" << rbfa1 << endl;
		cout << "\n—————————rBFA2:\n" << rbfa2 << endl;
		/**
		 LBFA1————画状态图得RE=(a+b)*a+(aa)*
		 Q = [0,6) s = 5 F = { 2 4 5 }
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'a'->3  'a'->4 }
		 follow = 0->{ 0 1 2 } 1->{ 0 1 2 } 2->{} 3->{ 4 } 4->{ 3 } 5->{ 0 1 2 3 }
		 current = {}
		 LBFA2————画状态图得RE=(a+b)*a+(aa)*
		 Q = [0,6) s = 0 F = { 0 3 5 }
		 Qmap_inverse = { '$'->0  'a'->1  'b'->2  'a'->3  'a'->4  'a'->5 }
		 follow = 0->{ 1 2 3 4 } 1->{ 1 2 3 } 2->{ 1 2 3 } 3->{} 4->{ 5 } 5->{ 4 } 
		 current = {}
		 RBFA1————RE=(a+b)*a+(aa)*
		 Q = [0,6) s = {  0 1 2 3 5 } F = 5
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'a'->3  'a'->4 }
		 follow = 0->{ 0 1 2 } 1->{ 0 1 2 } 2->{ 5 } 3->{ 4 } 4->{ 3 5 } 5->{ }
		 current = {}
		 RBFA2————RE=(a+b)*a+(aa)*
		 Q = [0,6) s = { 5 } F = 5
		 Qmap_inverse = { 'a'->0  'b'->1  'a'->2  'a'->3  'a'->4 '$'->5 }
		 follow = 0->{ 0 1 2 } 1->{ 0 1 2 } 2->{ 5 } 3->{ 4 } 4->{ 3 5 } 5->{ }
		 current = {}
			 **/
		cout << "以下分别输出lbfa1和lbfa2各自转换的DFA和lbfa1通过另外一种方式输出的DFA\n" << endl;
		DFA BSTest4_dfa1 = lbfa1.determinism();
		cout << "————BSTest4_dfa1:" << BSTest4_dfa1 << endl;//——————————————————————成功转换成DFA
		DFA BSTest4_dfa2 = lbfa2.determinism();
		cout << "————BSTest4_dfa2:" << BSTest4_dfa2 << endl;//——————————————————————成功转换成DFA
		
		DFA BSTest4_dfa3 = test.LBFA2DFA(lbfa1);
		cout << "————BSTest4_dfa3:" << BSTest4_dfa3 << endl;
		/**
		DFA————画状态图得RE=(a+b)*a+(aa)*
		 Q = [0,5) 	S = { 0 } 	F = { 0 1 3 4 }
		Transitions =
		0->{ 'a'->1  'b'->2 }
		1->{ 'a'->3  'b'->2 }
		2->{ 'a'->4  'b'->2 }
		3->{ 'a'->1  'b'->2 }
		4->{ 'a'->4  'b'->2 }
		current = -1
		 **/
		FiniteAutomata ffa1;
		ffa1.perform(BSTest4_dfa1, "BSTest4_dfa1.ADS");
		FiniteAutomata ffa2;
		ffa2.perform(BSTest4_dfa2, "BSTest4_dfa2.ADS");
		FiniteAutomata ffa3;
		ffa3.perform(BSTest4_dfa3, "BSTest4_dfa3.ADS");
	}
	void BSTest5()
	{
		cout << "=====BSTest5=====\n";
		BSTestClass test;
		LBFA lbfa1, lbfa2;
		RBFA rbfa1, rbfa2;
		RE re;
		test.ex5(re);
		cout << "样例5，RE=((a | epsilon)+)b?cd*|(empty()): " << re << endl; // | . . . + | 'a' 1 ? 'a' 'c' * 'd' 0

		lbfa1 = BerrySethi(re);
		lbfa2 = BS_variation(re);
		rbfa1 = BerrySethLdual(re);
		rbfa2 = BS_variation_dual(re);
		cout << "\n—————————LBFA1:\n" << lbfa1 << endl;
		cout << "\n—————————LBFA2:\n" << lbfa2 << endl;
		cout << "\n—————————RBFA1:\n" << rbfa1 << endl;
		cout << "\n—————————rBFA2:\n" << rbfa2 << endl;
		/**
	     LBFA1————画状态图得RE=((a | epsilon)+)b?cd*|(empty())
	     Q = [0,5) s = 4 F = { 2 3 }
	     Qmap_inverse = { 'a'->0  'b'->1  'c'->2  'd'->3  }
	     follow = 0->{ 0 1 2 }   1->{ 2 }  2->{ 3 }  3->{ 3 }  4->{ 0 1 2 }
	     current = {}
		 LBFA2————画状态图得RE=((a | epsilon)+)b?cd*|(empty())
		 Q = [0,5) s = 0 F = { 3 4 }
	     Qmap_inverse = { '$'->0  'a'->1  'b'->2  'c'->3  'd'->4  }
	     follow = 0->{ 1 2 3 }   1->{ 1  2  3 }  2->{ 3 }  3->{ 4 }  4->{ 4 }
	     current = {}
		 RBFA1————画状态图得RE=((a | epsilon)+)b?cd*|(empty())
		 Q = [0,5) s = { 0 1 2 } F = 4
	     Qmap_inverse = { 'a'->0  'b'->1  'c'->2  'd'->3  }
	     follow = 0->{ 0 1 2 }   1->{ 2 }  2->{ 3 4 }  3->{ 3 4 }  4->{}
	     current = {}
		 RBFA2————画状态图得RE=((a | epsilon)+)b?cd*|(empty())
		 Q = [0,5) s = { 4 } F = 4
	     Qmap_inverse = { 'a'->0  'b'->1  'c'->2  'd'->3  '$'->4 }
	     follow = 0->{ 0  1  2 }   1->{ 2 }  2->{ 3 4 }  3->{ 3 4 }  4->{}
	     current = {}
			 **/
		cout << "以下分别输出lbfa1和lbfa2各自转换的DFA和lbfa1通过另外一种方式输出的DFA\n" << endl;
		DFA BSTest5_dfa1 = lbfa1.determinism();
		cout << "————BSTest5_dfa1:" << BSTest5_dfa1 << endl;//——————————————————————成功转换成DFA
		DFA BSTest5_dfa2 = lbfa2.determinism();
		cout << "————BSTest5_dfa2:" << BSTest5_dfa2 << endl;//——————————————————————成功转换成DFA
		
		DFA BSTest5_dfa3 = test.LBFA2DFA(lbfa1);
		cout << "————BSTest5_dfa3:" << BSTest5_dfa3 << endl;
		/**
	     DFA————画状态图得RE=((a | epsilon)+)b?cd*|(empty())
	     Q = [0,5) 	S = { 0 } 	F = { 3 4 }
	     Transitions =
	     0->{ 'a'->1  'b'->2  'c'->3 }
	     1->{ 'a'->1  'b'->2  'c'->3 }
	     2->{ 'c'->3 }
	     3->{ 'd'->4 }
	     4->{ 'd'->4 }
	     current = -1
	      **/
		FiniteAutomata ffa1;
		ffa1.perform(BSTest5_dfa1, "BSTest5_dfa1.ADS");
		FiniteAutomata ffa2;
		ffa2.perform(BSTest5_dfa2, "BSTest5_dfa2.ADS");
		FiniteAutomata ffa3;
		ffa3.perform(BSTest5_dfa3, "BSTest5_dfa3.ADS");
	}
void BSTest()
{
	cout << "=====BSTest测试=====\n";
	//BSTestClass test;//Reg_RE_Test()用来测试RE构造是否正确；
	//从上往下依次为RE样例1-5
	//test.Reg_RE_Test();
	BSTest1();
	BSTest2();
	BSTest3();
	BSTest4();
	BSTest5();
}