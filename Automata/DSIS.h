/***********************************************************************
Implementation class: DSIS
Files: DSIS.h, DSIS.cpp
Uses: CharRange, CRSet, ISImpl, RE

Description: Class DSIS provides the full abstract state interface of an item set (see class ISImpl).
DSIS inherits from ISImpl for implementation. It only adds the out_transition member
function. It is used in the item set construction [Wat93a, Construction 5.69].
 ***********************************************************************/
//#pragma once

#ifndef AUTOMATA_DSIS_H
#define AUTOMATA_DSIS_H



#include <iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "RE.h"
#include "ISImpl.h"

// This class is used to represent abstract States in a DFA that is still under
// construction.It represents the item sets in the DSIS construction.
// See Construction [Wat93a, Construction 5.69].
// DSIS inherits from ISImpl for implementation.
class DSIS :protected ISImpl
{
public:
	// Must always have an argument-less constructor.
	inline DSIS();

	// A special constructor:
	inline DSIS(const RE *r);

	inline const DSIS& operator=(const DSIS& r);

	// The required member functions :
	inline int final() const;
	inline CRSet out_labels() const;
	DSIS out_transition(const CharRange a) const;
	inline int operator==(const DSIS& r) const;
	inline int operator!=(const DSIS& r) const;

	friend std::ostream& operator<<(std::ostream& os, const DSIS& r);
	inline int class_invariant() const;
};

// Must always have an argument-less constructor.
// The default constructor won't leave *this in a condition satisfying the
// class invariant.
inline DSIS::DSIS() :ISImpl()
{

}

inline DSIS::DSIS(const RE *r) : ISImpl(r)
{
	assert(r->class_invariant() && class_invariant());
}

inline const DSIS& DSIS::operator=(const DSIS& r)
{
	assert(r.class_invariant());
	ISImpl::operator=(r);
	// *this may not satisfy the invariant until after the assignment.
	assert(class_invariant());
	return(*this);
}

// The required member functions :
inline int DSIS::final() const
{
	assert(class_invariant());
	return(ISImpl::final());
}
inline CRSet DSIS::out_labels() const
{
	assert(class_invariant());
	return(ISImpl::out_labels());
}

inline int DSIS::operator==(const DSIS& r) const
{
	assert(class_invariant() && r.class_invariant());
	return(ISImpl::operator==(r));
}

inline int DSIS::operator!=(const DSIS& r) const
{
	return(!operator==(r));
}

inline int DSIS::class_invariant() const
{
	// Should really check that before and after are fully closed.
	return(ISImpl::class_invariant());
}




#endif // !AUTOMATA_DSIS_H



