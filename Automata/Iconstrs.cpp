#include "stdafx.h"
#include "Iconstrs.h"
#include "Dconstrs.h"
#include "DSIS.h"
#include "DSDeRemer.h"
#include "DSISopt.h"
#include "DFAseed.h"

//  Item set constructions:
//  Iconstr(Construction 5.69)
DFA Iconstr(const RE *r) 
{
	assert(r->class_invariant());
	return(construct_components(DSIS(r)));
}

//  DeRemer's (Construction 5.15)
DFA DeRemer(const RE *r) 
{
	assert(r->class_invariant());
	return(construct_components(DSDeRemer(r)));
}

//  Oconstr(Construction 5.82)
DFA Oconstr(const RE *r) {
	assert(r->class_invariant());
	return(construct_components(DSISopt(r)));
}
