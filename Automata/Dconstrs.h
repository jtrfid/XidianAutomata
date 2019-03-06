/***********************************************************************************
Automata constructions

Three header files contain (inline) definitions or prototypes of functions that take a regular expression
and construct a finite automaton accepting the language of the regular expression. These
functions implement all of the construction algorithms given in [Wat93aJ. They differ in the type
of finite automaton that is created:

The finite automata construction functions are functions which take an RE (or a pointer to an
RE) and return an automaton of some type (one of FA, RFA, LBFA, RBFA, or DFA). 

Files Constrs.h and Constrs.cpp 
contains those construction functions whose operation is based upon the structure of 
a regular expression (the Sigma-algebra functions). These functions correspond to those given in [Wat93a, Section 4].

File Dconstrs.h and Dconstrs.cpp
contains functions implementing Brzozowski's construction(and its variants). 
These functions all produce a DFA, and correspond to those given in [Wat93a, Section 5.3]. 

Iconstrs.cpp and Iconstrs.h
contains the item set construction (and its variants). These functions all produce a DFA, 
and correspond to those given in [Wat93a, Section 5.5].

All of the function declarations (or prototypes) are accompanied by their corresponding reference
in [Wat93a].
 ***********************************************************************************/

//#pragma once

#ifndef AUTOMATA_DCONSTRS_H
#define AUTOMATA_DCONSTRS_H




#include "RE.h"
#include "DFA.h"

 // The numbers in parentheses refer to the Construction number in the Taxonomy.

 // DFA constructions :
 //        Brzozowski's constructions:
 //        Normal(Construction 5.34)
DFA Brz(const RE& r);

// With strong similarity(Construction 5.34 + Remark 5.32)
DFA Brz_optimized(const RE& r);



#endif // !AUTOMATA_DCONSTRS_H


