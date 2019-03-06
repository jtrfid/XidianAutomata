/***********************************************************************
		Item sets
	Implementation class: ISImpl
	Files: ISImpl.h, ISImpl.cpp
	Uses: BitVec, CharRange, CRSet, RE

	Description: ISImpl is a base class implementing an item set [Wat93a, Definition 5.58]. It is
	used as a base class in abstract state classes DSIS, DSDeRemer, and DSIS_opt. It includes a
	constructor from a pointer to RE (the regular expression associated with the item set). The
	pointed-to RE is assumed to remain in existence while the DFA components are constructed
	by template function construct_components. Additionally, the abstract state members final
	and out_labels are defined. The member function move_dots takes a CharRange and provides
	the functionality of "derivatives of item sets" (as defined in [Wat93a, Definition 5.61]), while
	member function D implements the dot closure relation D defined in [Wat93a, Definition 5.63].
 ***********************************************************************/
//#pragma once

#ifndef AUTOMATA_ISIMPL_H
#define AUTOMATA_ISIMPL_H


#include <iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "RE.h"
#include "BitVec.h"

// This class is used to represent abstract States in a DFA that is still under
// construction.It is used as the base class in representing item sets, for the
// item set construction, DeRemer's construction, and the optimized item set
// construction. This implements Section 5.5 of the Taxonomy.
class ISImpl
{
public:
	// Must always have an argument-less constructor.
	inline ISImpl();

	// A special constructor :
	ISImpl(const RE *r);

	const ISImpl& operator=(const ISImpl& r);

	// The required member functions :
	inline int final() const;
	inline CRSet out_labels() const;

	inline int operator==(const ISImpl& r) const;
	inline int operator!=(const ISImpl& r) const;

	// Move the dots across sym nodes.
	inline void move_dots(const CharRange& r);

	friend std::ostream& operator<<(std::ostream& os, const ISImpl& r);

	inline int class_invariant() const;

	// Some implementation details:

	// Which RE is this with-respect-to:
	const RE *e;

	// Where are the dots:
	// The indices in the BitVec's are the pre-order traversal orders of
	// the nodes in *e.
	// before indicates the nodes with a dot before them;
	// after indicates the nodes with a dot after them.
	BitVec before;
	BitVec after;

private:
	// Some helpers:

	// Move the dots as far as possible.
	// This is named according to Definition 5.63 of the Taxonomy.
	void D(const RE& r, int& node_num);

	// Fetch the labels throughout the tree.
	// Helper to out_labels().
	CRSet traverse_labels(const RE& r, int& node_num) const;

	// Move the dots throughout the RE tree:
	// Helper to move_dots().
	void traverse_move_dots(const RE& r, const CharRange& a, int& node_num);
};

// Must always have an argument-less constructor.
//       The resulting ISImpl won't satisfy the class_invariant()
inline ISImpl::ISImpl() :e(0)
{

}

inline int ISImpl::final() const
{
	assert(class_invariant());
	// It will be final if there is a dot after the root(which is node 0
	// in the traversal order).
	// See construction 5.69 of the Taxonomy.
	return(after.contains(0));
}

inline CRSet ISImpl::out_labels() const
{
	assert(class_invariant());
	// Start at the root, node O.
	int node(0);
	return(traverse_labels(*e, node));

}

inline int ISImpl::operator==(const ISImpl& r) const
{
	assert(class_invariant() && r.class_invariant());
	// *this and r must be relative to the same RE.
	assert(e == r.e);
	// All dots must be in the same places.
	return((before == r.before) && (after == r.after));
}

inline int ISImpl::operator!=(const ISImpl& r) const
{
	return(!operator==(r));
}

// Move the dots across sym nodes.
inline void ISImpl::move_dots(const CharRange& r)
{
	assert(class_invariant());
	// Traverse the RE tree.
	// i maintains the node number.
	int i(0);
	// Start without dots after the nodes.
	after.clear();
	traverse_move_dots(*e, r, i);
	assert(i == e->num_operators());
	// Now go back to the root, and do the closure.
	i = 0;
	D(*e, i);
	assert(i == e->num_operators());
}

inline int ISImpl::class_invariant() const
{
	return(e->class_invariant()
		&& before.width() == e->num_operators()
		&& after.width() == before.width());
}



#endif // !AUTOMATA_ISIMPL_H
