//#pragma once

#ifndef AUTOMATA_CHARTANGE_H
#define AUTOMATA_CHARTANGE_H


#include <iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include <algorithm> // min(),max()

/*******************************************************************************
 Represent a set of characters (in the alphabet) in a subrange of char.
 The ranges are specified by their upper and lower (inclusive) bounds.
 Used by most classes as the basis of regular expressions and automata.
 User class: CharRange
 Files: charrang.h, charrang.cpp
 Uses:
 Description: Sets of characters (denoted by a CharRange) can be used as automata transition
 labels and as regular expression atoms (unlike most other systems, which use single characters).
 The sets of characters are limited to a range of characters in the execution character
 set (no particular character set is assumed, and ASCII or EBCDIC can both be used). The
 ranges are specified by their upper and lower (inclusive) bounds. The denoted range may not
 be empty (allowing them to be empty greatly complicates the algorithms). Many member
 functions are provided, including functions determining if two CharRanges have a character
 in common, if one is entirely contained in another, or if they denote sets that are adjacent
 to one another (in the execution character set).
 *************************************************************************************/
class CharRange
{
public:
	// Some constructors :
	// The default is the empty range of characters.
	// and this does not satisfy the class invariant,i.e. one that is invalid.
	inline CharRange();

	// Copy constructor is standard.
	inline CharRange(const CharRange& r);

	// the upper and lower(inclusive) bounds of a character range, and yields the CharRange denoting the range 
	// (since the empty range is not permitted, the upper bound must not be less than the lower bound)
	inline CharRange(const char l, const char h);

	// takes a char and yields the singleton character range 
	// (a character range whose upper and lower bounds are equal) containing the char.
	inline CharRange(const char a);

	// Default operator=, destructor are okay

	// Some normal member functions:
	// Is char a in the range'?
	inline int contains(const char a) const;

	// Access to the representation:
	inline char low()const;
	inline char high()const;

	// Standard comparison operators.
	inline int operator==(const CharRange& r) const;
	inline int operator!=(const CharRange& r) const;

	// Containment operators.
	inline int operator<=(const CharRange& r) const;
	inline int operator>=(const CharRange& r) const;

	// Is there something in common between *this and r'?
	inline int not_disjoint(const CharRange& r) const;

	// Do *this and r overlap, or are they adjacent?
	inline int overlap_or_adjacent(const CharRange& r) const;

	// Some operators on CharRanges.
	// Merge two CharRanges if they're adjacent:
	inline CharRange& merge(const CharRange& r);

	// Make *this the intersection of *this and r.
	inline CharRange& intersection(const CharRange& r);

	// Return the left and right excess of *this with r(respectively):
	inline CharRange left_excess(const CharRange& r) const;
	inline CharRange right_excess(const CharRange& r) const;

	// Define an ordering on CharRange's, used mainly in RE::ordering().
	// this == r: return 0; this > r: return > 0; else return < 0  
	int ordering(const CharRange& r) const;

	// The class structural invariant.
	inline int class_invariant() const;

	// Some extra stuff.
	friend std::ostream& operator<<(std::ostream& os, const CharRange r);

private:
	// used to represent such ranges of characters, 
	// which are specified by their upper and lower(inclusive) bounds. [lo,hi]
	// since the empty range is not permitted, 
	// the upper bound must not be less than the lower bound)
	char lo, hi;

public:
	~CharRange();
};

// Now for the inline versions of the member functions:

// The default is the empty range of characters.
// and this does not satisfy the class invariant,i.e. one that is invalid.
inline CharRange::CharRange::CharRange() :lo(1), hi(0)
{
}

// Copy constructor is standard.
inline CharRange::CharRange(const CharRange& r) :
	lo(r.lo), hi(r.hi)
{
	assert(class_invariant());
}

// the upper and lower(inclusive) bounds of a character range, and yields the CharRange denoting the range 
// (since the empty range is not permitted, the upper bound must not be less than the lower bound)
inline CharRange::CharRange(const char l, const char h) :
	lo(l), hi(h)
{
	assert(class_invariant());
}

inline CharRange::CharRange(const char a) :
	lo(a), hi(a)
{
	assert(class_invariant());
}

// Is char a in the range'?
inline int CharRange::contains(const char a) const
{
	assert(class_invariant());
	return((lo <= a) && (a <= hi));
}

// Access to the representation:
inline char CharRange::low()const
{
	assert(class_invariant());
	return(lo);
}

inline char CharRange::high()const
{
	assert(class_invariant());
	return(hi);
}

// Standard comparison operators.
inline int CharRange::operator==(const CharRange& r) const
{
	assert(class_invariant());
	assert(r.class_invariant());
	return((lo == r.lo) && (hi == r.hi));
}

inline int CharRange::operator!=(const CharRange& r) const
{
	assert(class_invariant());
	assert(r.class_invariant());
	return(!operator==(r));
}

// Containment operators.
inline int CharRange::operator<=(const CharRange& r) const
{
	assert(class_invariant());
	assert(r.class_invariant());
	return((lo <= r.lo) && (hi <= r.hi));
}
inline int CharRange::operator>=(const CharRange& r) const
{
	assert(class_invariant());
	assert(r.class_invariant());
	return((lo >= r.lo) && (hi >= r.hi));
}

// Is there something in common between *this and r'?
// case one: r.lo -- lo -- r.hi -- hi; lo -- r.lo -- r.hi -- hi  ==> lo <= r.hi
// case two: lo -- r.lo -- hi -- r.hi; r.lo -- lo -- hi -- r.hi  ==> hi >= r.lo
// case one && case two <==> not(lo > r.hi || r.lo > hi) <==> (lo <= r.hi && hi >= r.lo) 
inline int CharRange::not_disjoint(const CharRange& r) const
{
	assert(class_invariant());
	assert(r.class_invariant());
	return((lo <= r.hi) && (hi >= r.lo));
}

// Do *this and r overlap, or are they adjacent?
//   this     r  ;      r    this
// ------- ------;   ------ ------- 
inline int CharRange::overlap_or_adjacent(const CharRange& r) const
{
	assert(class_invariant());
	assert(r.class_invariant());
	return(not_disjoint(r) || (r.lo == hi + 1) || (r.hi == lo - 1));
}

// Merge two CharRanges if they're adjacent:
inline CharRange& CharRange::merge(const CharRange& r)
{
	assert(class_invariant());
	lo = std::min(lo, r.lo);
	hi = std::max(hi, r.hi);
	return(*this);
}

// Make *this the intersection of *this and r.
inline CharRange& CharRange::intersection(const CharRange& r)
{
	assert(class_invariant());
	lo = std::max(lo, r.lo);
	hi = std::min(hi, r.hi);
	return(*this);
}

// Return the left and right excess of *this with r(respectively):
inline CharRange CharRange::left_excess(const CharRange& r) const
{
	CharRange ret(std::min(lo, r.lo), std::max(lo, r.lo) - 1);
	return(ret);
}
inline CharRange CharRange::right_excess(const CharRange& r) const
{
	CharRange ret(std::min(hi, r.hi) + 1, std::max(hi, r.hi));
	return(ret);
}

// The class structural invariant.
inline int CharRange::class_invariant() const
{
	// This could possibly be wrong if something goes weird with char being
	// signed or unsigned.
	// since the empty range is not permitted, the upper bound must not be less than the lower bound)
	return(lo <= hi);
}




#endif // !AUTOMATA_CHARTANGE_H

