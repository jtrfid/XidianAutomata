#include "stdafx.h"
#include "Constrs.h"

// LBFA constructions:
//       using RFA's.
// Construction 4.38
LBFA BS_variation(const RE& r)
{
	assert(r.class_invariant());

	// Construct the homomorphic image of r.
	RFA I(r);

	// Construct the begin-marker.
	Reg<RFA> m;
	m.symbol('$');

	// Attach the begin marker.
	m.concat((const Reg<RFA>&)I);

	// Construct the dummy LBFA, for use with the non-homomorphic mapping
	// convert(Defn. 4.35 of the Taxonomy)
	LBFA LB;

	return(LB.convert(m));
}

// RBFA constructions:
//      using RFAs'.
// Construction 4.50
RBFA BS_variation_dual(const RE& r)
{
	// See above.
	assert(r.class_invariant());

	RFA I(r);

	//Construct the end-marker.
	Reg<RFA> m;
	m.symbol('$');

	// Attach the end-marker.
	((Reg<RFA>&)I).concat(m);

	RBFA RB;
	return(RB.convert(I));
}