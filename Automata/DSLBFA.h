/***********************************************************************************
	Implementation class : DSLBFA
	Files : DSLBFA.h, DSLBFA.cpp
	Uses : CharRange, CRSet, StateRel, StateSet, Trans

	Description : Class DSLBFA implements the abstract class interface required to construct a DFA
	from an LBFA. A DSLBFA is constructed in the LBFA member function determinism, and
	then passed to template function construcLcomponents, which constructs the components of the DFA.
 ***********************************************************************************/
#pragma once
#include <iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "State.h"
#include "StateSet.h"
#include "StateRel.h"
#include "TransRel.h"

// This class is used to represent abstract States in a DFA that is still under
// construction.It is used in the construction of a DFA from an LBFA.The behaviour
// of a DSLBFA follows the simulation behaviour of an LBFA.
class DSLBFA
{
public:
	// Must always have an argument-less constructor.
	inline DSLBFA();

	inline DSLBFA(const DSLBFA& r);
	
	// A special constructor:
	DSLBFA(const StateSet& rq,
		const Trans *rQmap_inverse,
		const StateRel *rfollow,
		const StateSet *rF);

	inline const DSLBFA& operator=(const DSLBFA& r);
	
	// The required member functions :
	inline int final() const;
	CRSet out_labels() const;
	DSLBFA out_transition(const CharRange a) const;
	inline int operator==(const DSLBFA& r) const;
	inline int operator!=(const DSLBFA& r) const;
	
	inline friend std::ostream& operator<<(std::ostream& os, const DSLBFA& r );
	
	inline int class_invariant()const;

private:
	StateSet which;
	const Trans *Qmap_inverse;
	const StateRel *follow;
	const StateSet *F;
};

// Must always have an argument-less constructor.
inline DSLBFA::DSLBFA() :
	which(),
	Qmap_inverse(0),
	follow(0),
	F(0)
{
	// No assertion of the class invariant since it isn't satisfied yet.

}

inline DSLBFA::DSLBFA(const DSLBFA& r):
	which(r.which),
	Qmap_inverse(r.Qmap_inverse),
	follow(r.follow),
	F(r.F)
{
	assert(class_invariant());
}

inline const DSLBFA& DSLBFA::operator=(const DSLBFA& r)
{
	assert(r.class_invariant());
	// *this does not satisfy the class invariant yet.
	which = r.which;
	Qmap_inverse = r.Qmap_inverse;
	follow = r.follow;
	F = r.F;
	assert(class_invariant());
	return(*this);
}

// The required member functions :
inline int DSLBFA::final() const
{
	assert(class_invariant());
	return(which.not_disjoint(*F));
}

inline int DSLBFA::operator==(const DSLBFA& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(Qmap_inverse == r.Qmap_inverse && follow == r.follow && F == r.F);
	return(which == r.which);
}

inline int DSLBFA::operator!=(const DSLBFA& r) const
{
	return(!operator==(r));
}

inline std::ostream& operator<<(std::ostream& os, const DSLBFA& r)
{
	os << "\nDSLBFA\n" << r.which << *r.Qmap_inverse << *r.follow << *r.F << '\n';
	return(os);
}

inline int DSLBFA::class_invariant()const
{
	return(Qmap_inverse != 0
		&& follow != 0
		&& F != 0
		&& which.domain() == Qmap_inverse->range()
		&& which.domain() == follow->domain()
		&& which.domain() == F->domain());
}
