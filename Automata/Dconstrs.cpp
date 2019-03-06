#include "Dconstrs.h"
//#include "Constrs.h"
//#include "Dconstrs.h"
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
//	//return(construct_components(DSREopt(r)));  // 编译出错
//	return(construct_components<DSREopt>(r));  // 等效
//}