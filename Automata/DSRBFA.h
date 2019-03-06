/***********************************************************************************
Implementation class : DSRBFA
Files : DSRBFA.h, DSRBFA.cpp
Uses : CharRange, CRSet, StateRel, StateSet, Trans

Description : Class DSRBFA implements the abstract class interface required to construct a DFA
from an RBFA. A DSRBFA is constructed in the RBFA member function determinism, and
then passed to template function construcLcomponents, which constructs the components of the DFA.
***********************************************************************************/
//#pragma once

#ifndef AUTOMATA_DSRBFA_H
#define AUTOMATA_DSRBFA_H



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
// construction.It is used in the construction of a DFA from an RBFA.The behaviour
// of a DSRBFA follows the simulation behaviour of an RBFA.
class DSRBFA
{
public:
	// Must always have an argument-less constructor.
	inline DSRBFA();

	inline DSRBFA(const DSRBFA& r);

	// A special constructor:
	DSRBFA(const StateSet& rq,
		const Trans *rQmap_inverse,
		const StateRel *rfollow,
		const State rf);

	inline const DSRBFA& operator=(const DSRBFA& r);

	// The required member functions :
	inline int final() const;
	CRSet out_labels() const;
	DSRBFA out_transition(const CharRange a) const;
	inline int operator==(const DSRBFA& r) const;
	inline int operator!=(const DSRBFA& r) const;

	inline friend std::ostream& operator<<(std::ostream& os, const DSRBFA& r);

	inline int class_invariant()const;

private:
	StateSet which;
	const Trans *Qmap_inverse;
	const StateRel *follow;
	State f;
};

// Must always have an argument-less constructor.
inline DSRBFA::DSRBFA() :
	which(),
	Qmap_inverse(0),
	follow(0),
	f(Invalid)
{
	// No assertion of the class invariant since it isn't satisfied yet.

}

inline DSRBFA::DSRBFA(const DSRBFA& r) :
	which(r.which),
	Qmap_inverse(r.Qmap_inverse),
	follow(r.follow),
	f(r.f)
{
	assert(class_invariant());
}

inline const DSRBFA& DSRBFA::operator=(const DSRBFA& r)
{
	assert(r.class_invariant());
	// *this does not satisfy the class invariant yet.
	which = r.which;
	Qmap_inverse = r.Qmap_inverse;
	follow = r.follow;
	f = r.f;
	assert(class_invariant());
	return(*this);
}

// The required member functions :
inline int DSRBFA::final() const
{
	assert(class_invariant());
	return(which.contains(f));
}

inline int DSRBFA::operator==(const DSRBFA& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(Qmap_inverse == r.Qmap_inverse && follow == r.follow && f == r.f);
	return(which == r.which);
}

inline int DSRBFA::operator!=(const DSRBFA& r) const
{
	return(!operator==(r));
}

inline std::ostream& operator<<(std::ostream& os, const DSRBFA& r)
{
	os << "\nDSRBFA\n" << r.which << *r.Qmap_inverse << *r.follow << r.f << '\n';
	return(os);
}

inline int DSRBFA::class_invariant()const
{
	return(Qmap_inverse != 0
		&& follow != 0
		&& 0 <= f
		&& f < follow->domain()
		&& which.domain() == Qmap_inverse->range()
		&& which.domain() == follow->domain());
}


#endif // !AUTOMATA_DSRBFA_H


