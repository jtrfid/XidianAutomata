/************************************************************************
	Implementation class: Translmpl
	Files: TransIml.h, TansIml.cpp
	Uses: CharRange, CRSet, State, StateSet, TransPair
	Description: A TransImpl is a set of TransPairs. It is used as a base class for Trans and DTrans,
	which are used to implement transition relations. TransPairs can be added, but not removed
	from the set. When a new TransPair is added, if its CharRange is adjacent to the CharRange
	of a TransPair already in the set, and the destination State of the two TransPairs is the
	same, then the two TransPairs are merged into one.
 ************************************************************************/
//#pragma once

#ifndef AUTOMATA_TRANSIMPL_H
#define AUTOMATA_TRANSIMPL_H


#include<iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "CRSet.h"
#include "State.h"
#include "StateSet.h"
#include "TransPair.h"

// Implement the basics of a char to StateSet map (a set of TransPair's).
// It is used by DTrans and Trans.
class TransImpl
{
protected:
	// Constructors, destructors, operator=

	// Assume that delete[] 0 is okay.
	inline TransImpl();

	// Copy constructor allocates more memory.Should use(use-counting) for efficiency.
	TransImpl(const TransImpl& r);

	// Destructor is virtual, simple.
	virtual ~TransImpl();

	// operator=() must copy the memory.
	const TransImpl& operator=(const TransImpl& r);

	// Some member functions for making transitions:

	// What are all of the labels on transitions in *this?
	CRSet out_labels() const;

	// What are all transition labels with destination in r?
	CRSet labels_into(const StateSet& r) const;

	//Some special member functions :

	// Clear out all previous transitions, and zero the domain.
	inline void reincarnate();

	// Add a transition to the set.
	TransImpl& add_transition(const CharRange a, const State q);

	// Allow classes that inherit from TransImpl to have access to the real data:
	inline TransPair& transitions(const int i) const;

	// Output the transitions.
	friend std::ostream& operator<<(std::ostream& os, const TransImpl& r);

	// Maintain the class invariant.
	inline int class_invariant() const;

	// Helpers
	void ensure_min_size(int w);

	// Implementation details:

	// How many transitions are there.index of TransPair *data (include expansion_extra)
	int howmany;

	// How many transitions are there. [0,in_use) index of TransPair *data, it is is managed in add_transition()
	int in_use;

	// A dynamically allocated array of(CharRange, State) pairs(transitions). V × Q
	// struct TransPair表示:T(a) = { q | a in V，q in Q }
	TransPair *data;

	// For efficiency of the expansion helper function.
	enum { expansion_extra = 5 };
};

// Some inline members:

// Assume that delete[] 0 is okay.
inline TransImpl::TransImpl() :
	howmany(0),
	in_use(0),
	data(0)
{
	assert(class_invariant());
}

// Clear out all previous transitions, and zero the domain.
inline void TransImpl::reincarnate()
{
	assert(class_invariant());
	in_use = 0;
	assert(class_invariant());
}

// Allow classes that inherit from TransImpl to have access to the real data:
inline TransPair& TransImpl::transitions(const int i) const
{
	assert(class_invariant());
	// i can be greater than in_use in some weird case where the
	// transitions are still being set up.
	assert(0 <= i);
	return(data[i]);
}

// Maintain the class invariant.
inline int TransImpl::class_invariant() const
{
	int ret = 1;
	for (int i = 0; i < in_use && ret; i++)
	{
		ret = (data[i].transition_destination >= 0);
	}
	ret = ret && in_use <= howmany;
	return(ret);
}



#endif // !AUTOMATA_TRANSIMPL_H
