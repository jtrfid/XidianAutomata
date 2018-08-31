/****************************************************************************
	Implementation class: DTrans
	Files: dtrans. h, dtrans. cpp
	Uses: CharRange, CRSet, State, StateSet, TransImpl, TransPair
	Description: A DTrans is a set of TransPairs, with one restriction: the transition labels (CharRanges)
	are pairwise disjoint. (They are pairwise disjoint, since DTrans is used to implement
	deterministic transition functions.) The client must ensure that only transitions with disjoint
	labels are added. Member functions are provided to compute the destination of a transition,
	on a particular character or CharRange, returning a State (which is Invalid if there is no
	applicable transition). A State is returned (instead of a StateSet), since DTrans implement
	deterministic transition sets. A member function computes the set of all transition labels,
	returning a CRSet. Another member takes a StateSet and returns the set of all transition
	labels on transitions with the destination in the StateSet.
****************************************************************************/
#pragma once
#include<iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "State.h"
#include "StateSet.h"
#include "TransPair.h"
#include "TransImpl.h"

// Implement a DFA's transition function for one State.
// Map a char to a unique next State, using TransImpl
class DTrans :protected TransImpl
{
public:
	// Constructors, destructors, operator=:
	
	// By default, don't introduce any transitions.
	inline DTrans();
	
	// Copy constructor does a dynamic memory copy.
	inline DTrans(const DTrans& r);
	inline const DTrans& operator=(const DTrans& r);
	
	// Normal member functions :
	
	// Map a char to the unique next state.
	State operator[](const char a) const;

	// Map a CharRange to the corresponding State
	// assuming that the CharRange is entirely contained in the label of a transition.
	State range_transition(const CharRange a) const;
	
	// What are the labels of transitions out of *this.
	inline CRSet out_labels() const;

	// What are all transition labels into StateSet r?
	inline CRSet labels_into(const StateSet& r) const;

	// Is there a valid out-transition on a?
	int valid_out_transition(const CharRange a) const;

	// What is the range(States) of this map?
	// return a StateSet with domain dom.
	StateSet range(int dom) const;
	
	// Special member functions:
	
	// Recycle this entire structure.
	inline void reincarnate();

	// Create a new out-transition.
	inline DTrans& add_transition(const CharRange a, const State q);
	
	friend std::ostream& operator<<(std::ostream& os, const DTrans& r);

	inline int class_invariant() const;
};

// Inlines(mostly calling the base class):
// By default, don't introduce any transitions.
inline DTrans::DTrans():TransImpl()
{
	assert(class_invariant());
}

// Copy constructor does a dynamic memory copy.
inline DTrans::DTrans(const DTrans& r):TransImpl(r)
{
	assert(class_invariant());
}

inline const DTrans& DTrans::operator=(const DTrans& r)
{
	assert(class_invariant() && r.class_invariant());
	TransImpl::operator=(r);
	assert(class_invariant());
	return(*this);
}

// What are the labels of transitions out of *this.
inline CRSet DTrans::out_labels() const
{
	assert(class_invariant());
	return(TransImpl::out_labels());
}

// What are all transition labels into StateSet r?
inline CRSet DTrans::labels_into(const StateSet& r) const
{
	assert(class_invariant());
	return(TransImpl::labels_into(r));
}

// Recycle this entire structure.
inline void DTrans::reincarnate()
{
	assert(class_invariant());
	TransImpl::reincarnate();
}

// Create a new out-transition.
inline DTrans& DTrans::add_transition(const CharRange a, const State q)
{
	assert(class_invariant());
	TransImpl::add_transition(a, q);
	return(*this);
}

inline int DTrans::class_invariant() const
{
	// should also check that all transitions are on diffenert symbols.
	return(TransImpl::class_invariant());
}
