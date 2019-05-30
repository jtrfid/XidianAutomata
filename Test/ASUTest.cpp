#include <iostream>
#include "../Automata/Sigma.h"
#include "../Automata/FA.h"
#include "../Automata/Constrs.h"
#include "../Automata/LBFA.h"

using namespace std;
/**
// Construction 4.39 (variation of McNaughton-Yamada-Glushkov)
inline DFA ASU_shortcut(const RE& r)
{
	return(RFA(r).determinism2());
}
// DFA from LBFA construction:
// Construction 4.39
inline DFA ASU(const RE& r)
{
	return(BerrySethi(r).determinism());
}
**/
using namespace std;
class ASUTestClass
{
public:
	void Reg_RE_Test()
	{
		cout << "=====Reg_RE_Test=====\n";
		/////////////// non-basis operator(epsilon,empty,symbol): this ==> left = right = 0
		// RE = epsilon
		Reg<RE> re1;
		//Reg<RE> re1 = Reg<RE>(); // ��Ч
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
		cout << "����Ϊ�˸������������RE���\n" << endl;
		////////////////////////////// �ۺ�Ӧ��
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
		cout << left << "������������(a | epsilon) concat b* \n" << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)

		//(01)����������������������Զ����̲�p127ҳϰ��4����ѡ��ߴ����Եı���ʽ���и���ʹ�������
		//�ã�r+(sr?t|r|1)*����1����epsilon
		//�����Զ����·����Ա���ʽ���в��Ȼ����ÿ������
		/*cout << "\n\n����������������\n" << endl;
		Reg<RE> left0, right0, left1, right1;//���������������Ҳ�ȡ�µı�����β׺
		left0.symbol('s');
		right0.symbol('r');
		right0.question();
		left0.concat(right0);
		right0.symbol('t');
		left0.concat(right0);//�����������srt
		cout << left0 << "    ����sr?t \n" << endl;
		right0.symbol('r');
		right0.Or(right1.epsilon());//�����������r|1
		cout << right0 << "    ����r|1 \n" << endl;
		left0.Or(right0);
		cout << left0 << "    ����sr?t+r|1 \n" << endl;
		left1.symbol('r');
		left1.plus();
		left0.star();
		left1.concat(left0);
		cout << left1 << "    ���������r+(sr?t|r|1)* \n" << endl;//�����
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
		//cout << right << endl; // * 'b'

		// (a | epsilon) concat b* 
		left.concat(right);
		//cout << left<<"    ���Ӧ����(a | epsilon) concat b*\n " << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)
		re = left;
	}

	//  RE =  (a �� b)ab
	void reExample2_9noStar(RE& re)
	{
		//cout << "=====reExample2_9noStar=====\n";
		Reg<RE> left, right;
		//cout << "\n�������������������Ե�11111\n" << endl;
		//  RE =  (a �� b) ab
		//left.Or(right).concat(right.symbol('a')).concat(right.symbol('b')); // result error
		left.symbol('a');
		left.Or(right.symbol('b'));
		//cout << left << endl;  // | 'a' 'b'

		left.concat(right.symbol('a'));
		//cout << left << endl;  // . | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		//cout << left << endl;  // . . | 'a' 'b' 'a' 'b'

		re = left;
	}

	//  RE =  (* (a �� b)) ab

	void reExample2_9Star(RE& re)
	{
		//cout << "=====reExample2_9Star=====\n";
		Reg<RE> left, right;

		//  RE =  (* (a �� b)) ab
		left.symbol('a');
		left.Or(right.symbol('b'));
		left.star();
		//cout << left << endl;  // * | 'a' 'b'

		left.concat(right.symbol('a'));
		//cout << left << endl;  // . * | 'a' 'b' 'a'
		left.concat(right.symbol('b'));
		//cout << left << endl;  // . . * | 'a' 'b' 'a' 'b'

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
		//cout << left << "    (a+b)*a+(aa)*\n" << endl;
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
		//cout << left << "    ((a | epsilon)+)b?cd*|(empty())\n" << endl;
		re = left;

	}
	//  RE =  ((a �� b*)) ab��Ϊ���о���RE =  (* (a �� b)) ab�������������һ��ͬ�����õĺ�����
	/**
	void reExample2extra_9Star(RE& re)
	{
		cout << "\n=====reExample2extra_9Star=====\n";
		Reg<RE> left, right;

		//  RE =  ((a �� b*)) ab
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

	
	DFA ASU_shortcut(const RE& r)
	{
		//cout << "=====ASU_shortcut=====\n";
		return(RFA(r).determinism2());
	}
	DFA ASU(const RE& r)
	{
		//cout << "=====ASU=====\n";
		return(BerrySethi(r).determinism());
	}

};
void ASUTest1()
{
	cout << "=====ASUTest1=====\n";
	ASUTestClass test;
	LBFA lbfa1;
	RE re;
	test.reExample315(re);
	cout << "����1��RE=��a|epsilon) concat b*: " << re << endl; // . | 'a' 1(epsilon) * 'b'  ==> op = .,left = (| 'a' 1(epsilon)),right = (* b)

	/**
	 LBFA����������״̬ת��ͼ�ɵ�RE=(a|1)b*��������ֻΪ����֤LBFA��ȷ�ԣ���ʵ��ASUTest����û�й���������TEST2/3ʡ�Դ˻���
	Q = [0,3) s = 2 F = { 0  1 2 } Qmap_inverse = { 'a'->0  'b'->1 }
	follow = 0->{ 1 } 1->{ 1 } 2->{ 0 1 }
	current = {}
		 **/

	DFA dfa1 = test.ASU_shortcut(re);
	DFA dfa2 = test.ASU(re);
	cout << "DFA1__MYG_shortcut\n" << dfa1 << endl;
	cout << "DFA2__MYG\n" << dfa2 << endl;
	/**
	DFA1=DFA2����������״̬ת��ͼ�ɵ�RE=(a|1)b*
	Q = [0,3) S = { 0 } F = { 0  1  2 }
	Transitions = 0->{ 'a'->1  'b'->2 } 1->{ 'b'->2 } 2->{ 'b'->2 }
	current = -1
	�������������Ľ����һ����
	**/

	// ����������DFA������С��

	// �� dfa1 ������С��
	{
		DFA dfa1_1 = dfa1;
		std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

		DFA dfa1_2 = dfa1;
		std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

		DFA dfa1_3 = dfa1;
		std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

		DFA dfa1_4 = dfa1;
		std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

		DFA dfa1_5 = dfa1;
		std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
	}


	// �� dfa2 ������С��
	{
		DFA dfa1_1 = dfa2;
		std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

		DFA dfa1_2 = dfa2;
		std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

		DFA dfa1_3 = dfa2;
		std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

		DFA dfa1_4 = dfa2;
		std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

		DFA dfa1_5 = dfa2;
		std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
	}
}
void ASUTest2()
{
	cout << "=====ASUTest2=====\n";
	ASUTestClass test;
	RE re;
	test.reExample2_9noStar(re);
	cout << "����2��RE=��a��b)ab: " << re << endl; // . . | 'a' 'b' 'a' 'b'

	DFA dfa1 = test.ASU_shortcut(re);
	DFA dfa2 = test.ASU(re);
	cout << "DFA1__MYG_shortcut\n" << dfa1 << endl;
	cout << "DFA2__MYG\n" << dfa2 << endl;
	/**
	DFA1=DFA2����������״̬ͼ��RE=��a��b)ab
	 Q = [0,5) 	S = { 0 } 	F = { 4 }
	 Transitions = 0->{ 'a'->1  'b'->2 }  1->{ 'a'->3 }	2->{ 'a'->3 } 3->{ 'b'->4 }
	 4->{} 
	 current = -1
	 �������������Ľ����һ����
	 **/

	 // ����������DFA������С��

	 // �� dfa1 ������С��
	{
		DFA dfa1_1 = dfa1;
		std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

		DFA dfa1_2 = dfa1;
		std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

		DFA dfa1_3 = dfa1;
		std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

		DFA dfa1_4 = dfa1;
		std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

		DFA dfa1_5 = dfa1;
		std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
	}


	// �� dfa2 ������С��
	{
		DFA dfa1_1 = dfa2;
		std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

		DFA dfa1_2 = dfa2;
		std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

		DFA dfa1_3 = dfa2;
		std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

		DFA dfa1_4 = dfa2;
		std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

		DFA dfa1_5 = dfa2;
		std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
	}

}
void ASUTest3()
{
	cout << "=====ASUTest3=====\n";
	ASUTestClass test;
	RE re;
	test.reExample2_9Star(re);
	cout << "����3��RE=(a��b)*ab: " << re << endl; // . . * | 'a' 'b' 'a' 'b'

	DFA dfa1 = test.ASU_shortcut(re);
	DFA dfa2 = test.ASU(re);
	cout << "DFA1__MYG_shortcut\n" << dfa1 << endl;
	cout << "DFA2__MYG\n" << dfa2 << endl;
	/**
	DFA1=DFA2����������״̬ת��ͼ�ó�RE=(a��b)*ab
	Q = [0,4)  S = { 0 }   F = { 3 }
	Transitions =
	0->{ 'a'->1  'b'->2 }
	1->{ 'a'->1  'b'->3 }
	2->{ 'a'->1  'b'->2 }
	3->{ 'a'->1  'b'->2 }
	current = -1
	�������������Ľ����һ����
	 **/

	 // ����������DFA������С��

	 // �� dfa1 ������С��
	{
		DFA dfa1_1 = dfa1;
		std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

		DFA dfa1_2 = dfa1;
		std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

		DFA dfa1_3 = dfa1;
		std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

		DFA dfa1_4 = dfa1;
		std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

		DFA dfa1_5 = dfa1;
		std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
	}


	// �� dfa2 ������С��
	{
		DFA dfa1_1 = dfa2;
		std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

		DFA dfa1_2 = dfa2;
		std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

		DFA dfa1_3 = dfa2;
		std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

		DFA dfa1_4 = dfa2;
		std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

		DFA dfa1_5 = dfa2;
		std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
	}
}
void ASUTest4()
{
	cout << "=====ASUTest4=====\n";
	ASUTestClass test;
	RE re;
	test.ex4(re);
	cout << "����4��RE=(a+b)*a+(aa)*: " << re << endl; // | . * | 'a' 'b' 'a' * . 'a' 'a'

	DFA dfa1 = test.ASU_shortcut(re);
	DFA dfa2 = test.ASU(re);
	cout << "DFA1__MYG_shortcut\n" << dfa1 << endl;
	cout << "DFA2__MYG\n" << dfa2 << endl;
	/**
	DFA1=DFA2����������״̬ͼ��RE=(a+b)*a+(aa)*
	Q = [0,5)  S = { 0 }   F = { 0  1  3  4 }
	Transitions =
	0->{ 'a'->1  'b'->2 }
	1->{ 'a'->3  'b'->2 }
	2->{ 'a'->4  'b'->2 }
	3->{ 'a'->1  'b'->2 }
	4->{ 'a'->4  'b'->2 }
	current = -1
	�������������Ľ����һ����
	 **/

	 // ����������DFA������С��

	 // �� dfa1 ������С��
	{
		DFA dfa1_1 = dfa1;
		std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

		DFA dfa1_2 = dfa1;
		std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

		DFA dfa1_3 = dfa1;
		std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

		DFA dfa1_4 = dfa1;
		std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

		DFA dfa1_5 = dfa1;
		std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
	}


	// �� dfa2 ������С��
	{
		DFA dfa1_1 = dfa2;
		std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

		DFA dfa1_2 = dfa2;
		std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

		DFA dfa1_3 = dfa2;
		std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

		DFA dfa1_4 = dfa2;
		std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

		DFA dfa1_5 = dfa2;
		std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
	}

}
void ASUTest5()
{
	cout << "=====ASUTest5=====\n";
	ASUTestClass test;
	RE re;
	test.ex5(re);
	cout << "����5��RE=((a | epsilon)+)b?cd*|(empty()): " << re << endl; // | . . . + | 'a' 1 ? 'a' 'c' * 'd' 0

	DFA dfa1 = test.ASU_shortcut(re);
	DFA dfa2 = test.ASU(re);
	cout << "DFA1__MYG_shortcut\n" << dfa1 << endl;
	cout << "DFA2__MYG\n" << dfa2 << endl;
	/**
	 DFA1=DFA2����������״̬ͼ��RE=((a | epsilon)+)b?cd*|(empty())
     Q = [0,5) 	S = { 0 } 	F = { 3 4 }
	 Transitions =
	 0->{ 'a'->1  'b'->2  'c'->3 }
	 1->{ 'a'->1  'b'->2  'c'->3 }
	 2->{ 'c'->3 }
	 3->{ 'd'->4 }
	 4->{ 'd'->4 }
	 current = -1
	�������������Ľ����һ����
	 **/

	 // ����������DFA������С��

	 // �� dfa1 ������С��
	{
		DFA dfa1_1 = dfa1;
		std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

		DFA dfa1_2 = dfa1;
		std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

		DFA dfa1_3 = dfa1;
		std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

		DFA dfa1_4 = dfa1;
		std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

		DFA dfa1_5 = dfa1;
		std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
	}


	// �� dfa2 ������С��
	{
		DFA dfa1_1 = dfa2;
		std::cout << "-------------min by Brzozowski" << dfa1_1.min_Brzozowski() << std::endl;

		DFA dfa1_2 = dfa2;
		std::cout << "-------------min by dragon" << dfa1_1.min_dragon() << std::endl;

		DFA dfa1_3 = dfa2;
		std::cout << "-------------min by Hopcroft" << dfa1_1.complete().min_Hopcroft().usefulf() << std::endl;

		DFA dfa1_4 = dfa2;
		std::cout << "-------------min by HopcroftUllman" << dfa1_1.min_HopcroftUllman() << std::endl;

		DFA dfa1_5 = dfa2;
		std::cout << "-------------min by Watson" << dfa1_1.min_Watson() << std::endl;
	}
}
void ASUTest()
{
	cout << "=====ASUTest����11111=====\n";
	ASUTestClass test; //Reg_RE_Test()��������RE�����Ƿ���ȷ��
	//test.Reg_RE_Test();
	ASUTest1();
	ASUTest2();
	ASUTest3();
	ASUTest4();
	ASUTest5();
}