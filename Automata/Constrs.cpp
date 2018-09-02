#include "stdafx.h"
#include "Constrs.h"
#include "Dconstrs.h"
#include "DSRE.h"
#include "DSREopt.h"
#include "DFAseed.h"

DFA Brz(const RE& r) 
{
	assert(r.class_invariant());
	return(construct_components(DSRE(r)));
}

//DFA Brz_optimized(const RE& r) {
//	assert(r.class_invariant());
//	//return(construct_components(DSREopt(r)));
//	return(construct_components<DSREopt>(r));  // ��Ч
//}