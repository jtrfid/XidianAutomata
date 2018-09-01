/**********************************************************************************
Implementation class: DSRFA2
Files: DSRFA2.h, DSRFA2.cpp
Uses: CharRange, CRSet, StateRel, StateSet, Trans

Description: Class DSRFA2 implements the abstract class interface required to construct a DFA
from an RFA. DSRFA2 is an alternative to DSRFA, using the left-biased interpretation of
RFA States, instead of the right-biased interpretation used in DSRFA. A DSRFA2 is constructed
in the RFA member function determinism2, and then passed to template function
construcLcomponents, which constructs the components of the DFA.
**********************************************************************************/
#pragma once
#include <iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "StateRel.h"
#include "StateSet.h"
#include "Trans.h"

// This class is used to represent abstract States in a DFA that is still under
// construction.It is used in the construction of a DFA from an RFA.The behaviour
// of a DSRFA2 follows the left-biased interpretation of RFA 's (unlike DSRFA, which
// follows the right-biased interpretation).See the last item on p.73 of the Taxonomy.
class DSRFA2
{
public:
	// Must always have an argument-less constructor.
	inline DSRFA2();

	inline DSRFA2(const DSRFA2& r);

	// A special constructor(for use in constructing the start state):
	DSRFA2(const Trans *rQmap_inverse,
		const StateRel *rfollow,
		const StateSet *rfirst,
		const StateSet *rlast,
		const int rfinalness);

	inline const DSRFA2& operator = (const DSRFA2& r);

	// The required member functions:
	inline int final() const;
	CRSet out_labels() const;

	DSRFA2 out_transition(const CharRange a) const;
	inline int operator==(const DSRFA2& r) const;
	inline int operator!=(const DSRFA2& r) const;

	inline friend std::ostream& operator<<(std::ostream& os, const DSRFA2& r);

	inline int class_invariant() const;

private:
	// Another special constructor, for use in out_transitions():
	DSRFA2( const StateSet& rq,
		const Trans *rQmap_inverse,
		const StateRel *rfollow,
		const StateSet *rfirst,
		const StateSet *rlast);

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
inline DSRFA2::DSRFA2() :
	which(),
	Qmap_inverse(0),
	follow(0),
	first(0),
	last(0),
	finalness(0)
{
	// No assert since it won't satisfy the class invariant
}

inline DSRFA2::DSRFA2(const DSRFA2& r) :
	which(r.which),
	Qmap_inverse(r.Qmap_inverse),
	follow(r.follow),
	first(r.first),
	last(r.last),
	finalness(r.finalness)
{
	assert(class_invariant());
}

inline const DSRFA2& DSRFA2::operator = (const DSRFA2& r)
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
inline int DSRFA2::final() const
{
	assert(class_invariant());
	return(finalness);
}

inline int DSRFA2::operator==(const DSRFA2& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(Qmap_inverse == r.Qmap_inverse
		&& follow == r.follow
		&& first == r.first
		&& last == r.last);
	return(which == r.which && finalness == r.finalness);
}

inline int DSRFA2::operator!=(const DSRFA2& r) const
{
	return(!operator==(r));
}
inline int DSRFA2::class_invariant() const
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

inline std::ostream& operator<<(std::ostream& os, const DSRFA2& r)
{
	os << "\nDSRFA2\n" << r.which << *r.Qmap_inverse << *r.follow
		<< *r.first << *r.last << r.finalness << '\n';
	return(os);
}
