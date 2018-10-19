/*************************************************************************
Implementation: CharRanges are represented as a pair of characters : the upper and lower (inclusive) bounds.
    There is a potential for problems caused by the fact that the language
	standard does not specify whether char is signed or unsigned.
Performance: In most functions that take a CharRange, the parameter passing is by value(since
	a pair of characters fit into the parameter passing registers on most processors).On some
	machines, performance can be improved by passing a const reference.
**************************************************************************/
#include "stdafx.h"
#include "CharRange.h"


//Define an ordering on CharRange's, used mainly in RE::ordering().
// this == r: return 0; this > r: return > 0; else return < 0 
int CharRange::ordering(const CharRange& r) const
{
	if (*this == r) return(0);
	else if (lo == r.lo) return(hi - r.hi);
	else return(lo - r.lo);
}

// Some extra stuff.
std::ostream& operator<<(std::ostream& os, const CharRange r)
{
	if (r.hi == r.lo) return(os << '\'' << r.lo << '\'');
	else return(os << "[" <<'\'' << r.lo << '\'' << ','
		           << '\'' << r.hi << '\'' << "]");
}

CharRange::~CharRange()
{
}
