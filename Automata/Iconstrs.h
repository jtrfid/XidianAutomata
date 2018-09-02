#pragma once
#include "RE.h"
#include "DFA.h"

// The numbers in parentheses refer to the Construction number in the Taxonomy.

//  Item set constructions:
//  Iconstr(Construction 5.69)
DFA Iconstr(const RE *r);

//  DeRemer's (Construction 5.15)
DFA DeRemer(const RE *r);

//  Oconstr(Construction 5.82)
DFA Oconstr(const RE *r);

