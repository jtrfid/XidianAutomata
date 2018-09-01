/**********************************************************************************
Implementation class: DSRFA
Files: DSRFA.h, DSRFA.cpp
Uses: CharRange, CRSet, StateRel, StateSet, Trans

Description: Class DSRFA implements the abstract class interface required to construct a DFA
from an RFA. A DSRFA is constructed in the RFA member function determinism, and then
passed to template function construc_components, which constructs the components of the
DFA.
 **********************************************************************************/
#pragma once
#include <iostream>
 // ȥ����ע������� assert()
 // #define NDEBUG
#include <cassert>  // �������
#include "CharRange.h"
#include "CRSet.h"
#include "StateRel.h"
#include "StateSet.h"
#include "Trans.h"

// This class is used to represent abstract States in a DFA that is still under
// construction.It is used in the construction of a DFA from an RFA.The behaviour
// of a DSRFA follows the simulation behaviour of an RFA.
class DSRFA
{
public:
	// Must always have an argument-less constructor.
	inline DSRFA();

	inline DSRFA(const DSRFA& r);

	// A special constructor:
	DSRFA(const StateSet& rq,
		const Trans *rQmap_inverse,
		const StateRel *rfollow,
		const StateSet *rfirst,
		const StateSet *rlast,
		const int rfinalness);

	inline const DSRFA& operator = (const DSRFA& r);

	// The required member functions:
	inline int final() const;
	CRSet out_labels() const;

	DSRFA out_transition(const CharRange a) const;
	inline int operator==(const DSRFA& r) const;
	inline int operator!=(const DSRFA& r) const;

	inline friend std::ostream& operator<<(std::ostream& os, const DSRFA& r);

	inline int class_invariant() const;

private:
	// This stuff may vary from object to object.
	StateSet which;
	int finalness;

	// This stuff should be the same for all objects corresponding
	// to a particular RFA.
	const Trans *Qmap_inverse;
	const StateRel *follow;
	const StateSet *first;
	const StateSet *last;
};

// Must always have an argument-less constructor.
inline DSRFA::DSRFA() :
	which(),
	Qmap_inverse(0),
	follow(0),
	first(0),
	last(0),
	finalness(0)
{
	// No assert since it won't satisfy the class invariant
}

inline DSRFA::DSRFA(const DSRFA& r) :
	which(r.which),
	Qmap_inverse(r.Qmap_inverse),
	follow(r.follow),
	first(r.first),
	last(r.last),
	finalness(r.finalness)
{
	assert(class_invariant());
}

inline const DSRFA& DSRFA::operator = (const DSRFA& r)
{
	assert(r.class_invariant());
    // *this may not satisfy the class invariant yet.
	which = r.which;
	Qmap_inverse = r.Qmap_inverse;
	follow = r.follow;
	first = r.first;
	last = r.last;
	finalness = r.finalness;
	assert(class_invariant());
	return(*this);
}

// The required member functions:
inline int DSRFA::final() const
{
	assert(class_invariant());
	return(finalness);
}

inline int DSRFA::operator==(const DSRFA& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(Qmap_inverse == r.Qmap_inverse
		&& follow == r.follow
		&& first == r.first
		&& last == r.last);
	return(which == r.which && finalness == r.finalness);
}

inline int DSRFA::operator!=(const DSRFA& r) const
{
	return(!operator==(r));
}
inline int DSRFA::class_invariant() const
{
	return(Qmap_inverse != 0
		&& follow != 0
		&& first != 0
		&& last != 0
		&& which.domain() == Qmap_inverse->range()
		&& which.domain() == follow->domain()
		&& which.domain() == first->domain()
		&& which.domain() == last->domain());
}

inline std::ostream& operator<<(std::ostream& os, const DSRFA& r)
{
	os << "\nDSRFA\n" << r.which << *r.Qmap_inverse << *r.follow
		<< *r.first << *r.last << r.finalness << '\n';
	return(os);
}

