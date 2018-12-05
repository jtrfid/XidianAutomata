/******************************************************************************
Automata constructions

Three header files contain (inline) definitions or prototypes of functions that take a regular expression
and construct a finite automaton accepting the language of the regular expression. These
functions implement all of the construction algorithms given in [Wat93aJ. They differ in the type
of finite automaton that is created:

The finite automata construction functions are functions which take an RE (or a pointer to an
RE) and return an automaton of some type (one of FA, RFA, LBFA, RBFA, or DFA).

//////////////////////////////////////////////////////////////////////////////////////////////////
Files Constrs.h and Constrs.cpp
contains those construction functions whose operation is based upon the structure of
a regular expression (the Sigma-algebra functions). These functions correspond to those given in [Wat93a, Section 4].
    Reg<RE> re1;
	//Reg<RE> re1 = Reg<RE>(); // 等效
	///////////////////////// Thompson's construction:
	// Thompson's Construction 4.5 (Top-down Thompson's)
	FA fa1(re1);
	//FA fa1 = FA(re1);   // 等效
	//FA fa1 = Thompson(re1);  // 等效

	// Thompson's Construction 4.3 (Thompson)
	Reg<FA> fa1(re1);
	//FA fa1 = Reg<FA>(re1);   // 等效
	//FA fa1 = Thompson_sigma(re1);  // 等效
/////////////////////////////////////////////////////////////////////////////////////////////////

File Dconstrs.h and Dconstrs.cpp
contains functions implementing Brzozowski's construction(and its variants).
These functions all produce a DFA, and correspond to those given in [Wat93a, Section 5.3].

Iconstrs.cpp and Iconstrs.h
contains the item set construction (and its variants). These functions all produce a DFA,
and correspond to those given in [Wat93a, Section 5.5].

All of the function declarations (or prototypes) are accompanied by their corresponding reference
in [Wat93a].
*******************************************************************************/
#pragma once
#include "RE.h"
#include "FA.h"
#include "RFA.h"
#include "LBFA.h"
#include "RBFA.h"
#include "Sigma.h"
#include "DFA.h"

/****************************************************************************************
// Thompson's construction: 由RE(Regular Expression)构造FA
//           use the functions Thompson or Thompson_sigma, or
//           FA Th(E);       // Construction 4.5 (Top-down Thompson's),更有效
//           Reg<FA> Th2(E); // Construction 4.3 (Top-down sigma-algebra Thompson)

	// Thompson's Construction 4.5 (Top-down Thompson's)
	FA fa1(re1);
	//FA fa1 = FA(re1);   // 等效，在FA.cpp中定义，递归函数：td(const State s, const RE& e, const State f);
	//FA fa1 = Thompson(re1);  // 等效,在Constrs.h中封装，FA Thompson(const RE& r)

	// Thompson's Construction 4.3 (Top-down sigma-algebra Thompson)
	Reg<FA> fa1(re1);
	//FA fa1 = Reg<FA>(re1);   // 等效，在Sigma.h中定义Reg(const RE& r),sigma-operator在Sig-FA.cpp中定义
	//FA fa1 = Thompson_sigma(re1);  // 等效，,在Constrs.h中封装，FA Thompson_sigma(const RE& r)
*****************************************************************************************/

// Construction 4.5, td(const State s, const RE& e, const State f);
inline FA Thompson(const RE& r)
{
	return(FA(r));
}

// Construction 4.3 (Top-down sigma-algebra Thompson): Thompson's construction is the (unique) homomorphism Th(The operators (with subscript Th, for Thompson))
// from RE to Thompson's Sigma-algebra of FA's.
// C(epsilon,Th),C(empty,Th),C(a,Th),C(.,Th([M0],[M1])),C(union,Th([M0],[M1])),C(star,Th([M])),C(star,Th([M])),C(plus,Th([M])),C(question,Th([M]))
inline FA Thompson_sigma(const RE& r)
{
	return(Reg<FA>(r));
}

//////////////// RFA constructions: 由RE(Regular Expression)构造RFA(Reduced FA)//////////////
//     use the functions, or
//     RFA R(E); // Definition 4.30
//     Reg<RFA> R2(E); // Definition 4.29 (Sigma-algebra of RFA's)
//     To DFA:
//         R.determinism()
//         R2.determinism();
//         R.determinism2();
//         R2.determinism2();

// Definition 4.30 (Homomorphism from RE to[RFA]) : We define rfa in RE--->[RFA],
// to be the unique homomorphism from REs to[RFA]
// RFA rfa1(re);     // 在RFA.h，RFA.cpp定义和实现RFA(const RE& e)
// RFA rfa1 = rfa(re); // 等效，在Constrs.h中封装，RFA rfa(const RE& r)
inline RFA rfa(const RE& r)
{
	return(RFA(r));
}

// Definition 4.29 (Sigma-algebra of RFA's): The carrier set is [RFA], p33-35
// RFA rfa1 = Reg<RFA>(re); // 在Sigma.h中定义Reg(const RE& r)，sigma-operator在Sig-RFA.cpp中定义
// RFA rfa1 = rfa_sigma(re);  // 等效,在Constrs.h封装，RFA rfa_sigma(const RE& r)
inline RFA rfa_sigma(const RE& r)
{
	return(Reg<RFA>(r));
}

// Construction 4.39 (variation of McNaughton-Yamada-Glushkov)
inline DFA MYG_shortcut(const RE& r)
{
	return(RFA(r).determinism2());
}

// Construction 4.50(variation of Aho-Sethi-Ullman)
inline DFA ASU_shortcut(const RE& r)
{
	return(RFA(r).determinism());
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
// LBFA constructions:
//       using RFA's.
// Construction 4.32
inline LBFA BerrySethi(const RE& r)
{
	return(RFA(r));  // RE -->RFA: rfa=RFA(r); RFA --> LBFA, lbfa = LBFA(rfa) 或 lbfa = lbfa.decode(rfa)
}

// LBFA constructions:
//       using RFA's.
// Construction 4.38
LBFA BS_variation(const RE& r);

// DFA from LBFA construction:
// Construction 4.39
inline DFA MYG(const RE& r)
{
	return(BerrySethi(r).determinism());
}

// RBFA constructions:
//      using RFAs'.
// Construction 4.45
inline RBFA BerrySethLdual(const RE& r)
{
	return(RFA(r));
}

// RBFA constructions:
//      using RFAs'.
// Construction 4.50
RBFA BS_variation_dual(const RE& r);

// Construction 4.50
inline DFA ASU(const RE& r)
{
	return(BS_variation_dual(r).determinism());
}

