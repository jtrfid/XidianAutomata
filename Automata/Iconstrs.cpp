#include "stdafx.h"
#include "Iconstrs.h"
#include "Dconstrs.h"
#include "DSIS.h"
#include "DSDeRemer.h"
#include "DSISopt.h"
#include "DFAseed.h"

DFA Iconstr(const RE *r) 
{
	assert(r->class_invariant());
	return(construct_components(DSIS(r)));
}

DFA DeRemer(const RE *r) 
{
	assert(r->class_invariant());
	return(construct_components(DSDeRemer(r)));
}

DFA Oconstr(const RE *r) {
	assert(r->class_invariant());
	return(construct_components(DSISopt(r)));
}
