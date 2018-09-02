#pragma once
#include "RE.h"
#include "DFA.h"

// The numbers in parentheses refer to the Construction number in the Taxonomy.

// DFA constructions :
//        Brzozowski's constructions:
//        Normal(Construction 5.34)
DFA Brz(const RE& r);

//        With strong similarity(Construction 5.34 + Remark 5.32)
DFA Brz_optimized(const RE& r);

