/***********************************************************************************
Automata constructions
The finite automata construction functions are functions which take an RE (or a pointer to an
RE) and return an automaton of some type (one of FA, RFA, LBFA, RBFA, or DFA). 

Functions implementing Brzozowski's construction [Wat93a, Section 5.3] are given in 
Dconstrs.cpp and Dconstrs.h. 

Functions implementing the item set constructions [Wat93a, Section 5.5] are given in 
Iconstrs.cpp and Iconstrs.h. 

Files Constrs.h and Constrs.cpp contain all of the remaining functions (from [Wat93a, Section 4]).

All of the function declarations (or prototypes) are accompanied by their corresponding reference
in [Wat93a].
 ***********************************************************************************/

#pragma once
#include "RE.h"
#include "FA.h"
#include "RFA.h"
#include "LBFA.h"
#include "RBFA.h"
#include "Sigma.h"
#include "DFA.h"

// Thompson's construction:
//           use the functions Thompson or Thompson_sigma, or
//           FA Th(E);
//           Reg<FA> Th2(E);

// Construction 4.5
inline FA Thompson(const RE& r)
{
	return(FA(r));
}

// Construction 4.3
inline FA Thompson_sigma(const RE& r)
{
	return(Reg<FA>(r));
}

// RFA constructions:
//     use the functions, or
//     RFA R(E);
//     Reg<RFA> R2(E);
//     To DFA:
//         R.determinism()
//         R2.determinism();
//         R.determinism2();
//         R2.determinism2();

// Definition 4.30 (variation)
inline RFA rfa(const RE& r) 
{
	return(RFA(r));
}

// Definition 4.30
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

// LBFA constructions:
//       using RFA's.

// Construction 4.32
inline LBFA BerrySethi(const RE& r) 
{
	return(RFA(r));
}

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

// Construction 4.48
RBFA BS_variation_dual(const RE& r);

// Construction 4.50
inline DFA ASU(const RE& r) 
{
	return(BS_variation_dual(r).determinism());
}