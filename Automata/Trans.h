/****************************************************************************
	Implementation class: Trans
	Files: trans. h, trans. cpp
	Uses: CharRange, CRSet, State, StateSet, Translmpl, TransPair
	Description: A Trans is a set of TransPairs (transitions) for use in transition relations. 
		Transitions	can be added to the set, but not removed. Member functions are provided to compute
		the destination of the transition set, on a particular character or on a CharRange (the destination
		is returned as a StateSet). Since a StateSet is returned, Trans has a range (which is
		one more than the maximum State that can occur as a transition destination) which is managed
		by the client and is used to determine the domain of the returned StateSet. 
		Another	member function computes the set of all transition labels, returning a CRSet.
 ****************************************************************************/
//#pragma once


#ifndef AUTOMATA_TRANS_H
#define AUTOMATA_TRANS_H


#include<iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "CRSet.h"
#include "State.h"
#include "StateSet.h"
#include "TransPair.h"
#include "TransImpl.h"

// Map char(CharRange) to StateSet, using Translmpl.
// Trans::destination_range; // The domain() of the associated State Pool.
// TransImpl::in_use;  // How many transitions are there. [0,in_use) index of TransPair *data, it is is managed in add_transition()
// Implement the transitions for one state, or for the inverse of Qmap
// (in RFA's, LBFA's, and RBFA's).
class Trans :protected TransImpl
{
public:
	// Constructors, destructors, operator=:

	// Assume that delete[] 0 is okay.
	inline Trans();

	// Copy constructor allocates more memory.Should use(use-counting) for efficiency.
	inline Trans(const Trans& r);

	// operator=() must copy the memory.
	inline const Trans& operator=(const Trans& r);

	// Some member functions for making transitions:
	// Map a char to the corresponding StateSet.
	StateSet operator[](const char a) const;

	// Map a CharRange to the corresponding StateSet
	// assuming that the CharRange is entirely contained in the label of a transition.
	StateSet range_transition(const CharRange a) const;

	// What are all of the transitions in *this?
	inline CRSet out_labels() const;

	// What are all transition labels into StateSet r?
	inline CRSet labels_into(const StateSet& r) const;

	// Some special member functions:

	// Clear out all prev transitions, and zero the domain.
	// do'not change the domain() of the associated State Pool.
	inline void reincarnate();

	// The range of States that can be transitioned to. i.e. StateSet domain()
	inline int range() const;

	// Change the range of States that can be transitioned to.
	// This is used in determining the domain() of the StateSet's (which are destinations of transitions).
	// set state (destinations of transition) is [0,r), i.e. StateSet domain()
	inline void set_range(const int r);

	// Add one more transition to the set.
	inline Trans& add_transition(const CharRange a, const State q);

	// Do normal set union.
	Trans& set_union(const Trans& r);

	// Incorporate another Trans, while renaming all of the states.
	Trans& disjointing_union(const Trans& r);

	// Rename all of the States(that are destinations of some transition)
	// such that none of them fall in the range[0,r).
	Trans& st_rename(const int r);

	// Output the transitions.
	friend std::ostream& operator<<(std::ostream& os, const Trans& r);

	// Maintain the class invariant.
	inline int class_invariant() const;

private:
	// Implementation details:
	// The domain() of the associated State Pool.
	int destination_range;
};

// Some inline members:

// Assume that delete[] 0 is okay.
inline Trans::Trans() :
	TransImpl(), destination_range(0)
{
	assert(class_invariant());
}

// Copy constructor allocates more memory.Should use(use-counting) for efficiency.
inline Trans::Trans(const Trans& r) :
	TransImpl((TransImpl&)(r)), destination_range(r.destination_range)
{
	assert(class_invariant());
}

// operator=() must copy the memory.
inline const Trans& Trans::operator=(const Trans& r)
{
	assert(class_invariant() && r.class_invariant());
	TransImpl::operator=((TransImpl&)r);
	destination_range = r.destination_range;
	assert(class_invariant());
	return(*this);
}

// What are all of the transitions in *this?
inline CRSet Trans::out_labels() const
{
	assert(class_invariant());
	return(TransImpl::out_labels());
}

// What are all transition labels into StateSet r?
inline CRSet Trans::labels_into(const StateSet& r) const
{
	assert(class_invariant());
	return(TransImpl::labels_into(r));
}

// Clear out all prev transitions, and zero the domain.
// do'not change the domain() of the associated State Pool.
inline void Trans::reincarnate()
{
	assert(class_invariant());
	TransImpl::reincarnate();
	assert(class_invariant());
}

// The range of States that can be transitioned to. i.e. StateSet domain()
inline int Trans::range() const
{
	assert(class_invariant());
	return(destination_range);
}

// Change the range of States that can be transitioned to.
// This is used in determining the domain() of the StateSet's (which are destinations of transitions).
// set state (destinations of transition) is [0,r), i.e. StateSet domain()
inline void Trans::set_range(const int r)
{
	assert(class_invariant());
	destination_range = r;
	assert(class_invariant());
}

// Add one more transition to the set.
inline Trans& Trans::add_transition(const CharRange a, const State q)
{
	assert(class_invariant());
	TransImpl::add_transition(a, q);
	assert(class_invariant());
	return(*this);
}

// Maintain the class invariant.
inline int Trans::class_invariant() const
{
	int ret = 1;
	for (int i = 0; i < in_use && ret; i++)
	{
		ret = (0 <= transitions(i).transition_destination)
			&& (transitions(i).transition_destination < destination_range);
	}
	return(ret);
}


#endif // !AUTOMATA_TRANS_H
