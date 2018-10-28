#pragma once
#include <iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"

/***********************************************************
 A data-structure to hold sets of CharRange's. The CharRange's are kept pair wise disjoint.
 These are generally used in the construction of DFA's, and in DFA minimization.
 Files: CRSet.h, CRSet.cpp
 Uses: CharRange
 Description: A CRSet is a set of CharRanges, with a restriction: all CharRanges in a CRSet are
 pairwise disjoint. When a new CharRange is added to a CRSet, some CharRanges may be
 split to ensure that the disjointness property is preserved. Members are provided to check
 if two CRSets cover the same characters, and to combine two CRSets.
 eg.
 CRSet set1; CharRange cr('a', 'd');
 cout << cr << endl; // [ 'a' 'd' ]
 cout << cr.not_disjoint('b') << endl;  // 1, 表示cr与'a'相交
 set1.add(cr);
 set1.add('b');
 cout << set1 << endl;   // { 'b'  'a'  ['c','d'] }
 ***********************************************************/
class CRSet
{
public:
	// Some basic constructors.
	// Create the emptyset:
	inline CRSet();
	// The singleton set :
	CRSet(const CharRange& a);
	CRSet(const CRSet& r);

	// Also need a destructor and an operator=
	inline ~CRSet();

	const CRSet& operator=(const CRSet& r);

	// Some basic operations.

	// Add a CharRange to this set, splitting it as required.
	// It's not possible to add the empty CharRange to a CRSet!
	inline CRSet& add(const CharRange a);

	// Append a CharRange onto the end of this set, knowing that a is disjoint with
	// any others in the set.
	inline CRSet& append(const CharRange& a);

	// Combine two CRSet's, splitting CharRange's to maintain their pairwise disjointness.
	CRSet& combine(const CRSet& r);

	// Does *this and r cover the same set of characters?
	int equivalent_cover(const CRSet& r) const;

	// How many CharRanges are in *this? 
	inline int size() const;

	// Some iterators :
    
	// Fetch the it'th CharRange in *this.
	inline const CharRange& iterator(const int it) const;

	// Is there even in it'th CharRange?
	inline int iter_end(const int it) const;
	
	//Some special members :
	inline int class_invariant() const;
	friend std::ostream& operator<<(std::ostream& os, const CRSet& r);

private:
	// A simple helper
	// Make sure that data is at leasts (adjusting howmany,but not in_use).
	void ensure_min_size(int s);

	// Add a CharRange to this set, splitting it as required.
	// Adding begins at i.This is used in CRSet: add().
	void add_at(const CharRange a, int i);
	
	// Is r covered by this set?
	int covered(const CharRange& r) const;
	
	// A class constant: must be at least 1.
	enum { expansion_size = 5 };
	
	// Some implementation details:
	int howmany;
	int in_use;
	CharRange *data;
};

// Now for the inline versions of the member functions:

// Create the emptyset:
inline CRSet::CRSet() :
	howmany(0), in_use(0), data(0)
{
	assert(class_invariant());
}

// Also need a destructor and an operator=
inline CRSet::~CRSet()
{
	assert(class_invariant());
	delete[]data;
}

// Add a CharRange to this set, splitting it as required.
// It's not possible to add the empty CharRange to a CRSet!
inline CRSet& CRSet::add(const CharRange a)
{
	assert(class_invariant());
	add_at(a, 0);
	return(*this);
}

// Append a CharRange onto the end of this set, knowing that a is disjoint with
// any others in the set.
inline CRSet& CRSet::append(const CharRange& a)
{
	assert(class_invariant());
	assert(a.class_invariant());
	ensure_min_size(in_use + 1);
	data[in_use++] = a;
	assert(class_invariant());
	return(*this);
}

// How many CharRanges are in *this? 
inline int CRSet::size() const
{
	assert(class_invariant());
	return(in_use);
}

// Fetch the it'th CharRange in *this.
inline const CharRange& CRSet::iterator(const int it) const
{
	assert(class_invariant());
	assert(!iter_end(it));
	return(data[it]);
}

// Is there even in it'th CharRange?
inline int CRSet::iter_end(const int it) const
{
	assert(class_invariant());
	assert(0 <= it);
	return(it >= in_use);
}

//Some special members :
inline int CRSet::class_invariant() const
{
	int result;
	result = 0 <= howmany && in_use <= howmany && (howmany == 0 ? data == 0 : data != 0) && 1 <= expansion_size;

	// Make sure that all of data[] are pairwise disjoint.
	for (int i = 0; i < in_use && result; i++)
	{
		for (int j = i + 1; j < in_use && result; j++)
		{
			result = !data[i].not_disjoint(data[j]);
		}
	}
	return(result);
}