/*******************************************************
 Implementation: A CRSet contains a pointer to a dynamically allocated array of CharRanges,
 an integer representing the size of the array, and an integer representing the number of elements
 in the array that are in use. The member add_at is a good candidate for optimization.
 *******************************************************/

#include "CRSet.h"

// The singleton set :
CRSet::CRSet(const CharRange& a):
	howmany(expansion_size),in_use(1),data(new CharRange[expansion_size])
{
	data[0] = a;
	assert(class_invariant());
}
CRSet::CRSet(const CRSet& r):
	howmany(r.in_use+expansion_size),in_use(r.in_use),data(new CharRange[r.in_use+expansion_size])
{
	assert(r.class_invariant());
	for (int i = 0; i < in_use; i++) data[i] = r.data[i];
	assert(class_invariant());
}

const CRSet& CRSet::operator=(const CRSet& r)
{
	assert(r.class_invariant());
	// May need to allocate some more memory
	if (r.in_use > howmany) {
		CharRange *d(new CharRange[howmany = r.in_use + expansion_size]);
		delete[]data;
		data = d;
	}
	assert(r.in_use <= howmany);
	for (int i = 0; i < r.in_use; i++) data[i] = r.data[i];
	in_use = r.in_use;
	assert(class_invariant());
	return(*this);
}

// Combine two CRSet's, splitting CharRange's to maintain their pairwise disjointness.
CRSet& CRSet::combine(const CRSet& r)
{
	assert(r.class_invariant());
	assert(class_invariant());
	for (int i = 0; i < r.in_use; i++) add(r.data[i]);
	assert(class_invariant());
	return(*this);
}

// Does *this and r cover the same set of characters(letters)?
int CRSet::equivalent_cover(const CRSet& r) const
{
	assert(class_invariant());
	int result = 1;
	for (int i = 0; i < in_use && result; i++)
	{
		result = r.covered(data[i]);
	}
	return result;
}

// Is r covered by this set?
int CRSet::covered(const CharRange& r) const
{
	assert(class_invariant());
	assert(r.class_invariant());
	int i;
	for (i = 0; i < in_use && !r.not_disjoint(data[i]); i++);

	if (i < in_use)
	{
		assert(r.not_disjoint(data[i]));
		// They have something in common.
		if (r <= data[i]) {
			// r is completely coverd by data[i]
			return(1);
		}
		else {
			// Now,figure out if the excesses are also covered.
			// This could be made more efficient!
			int ret1 = 1, ret2 = 1;
			if (r.low() != data[i].low()) {
				// There actually is a left excess:
				ret1 = covered(r.left_excess(data[i]));
			}
			if (r.high() != data[i].high()) {
				// There actually is a right excess:
				ret2 = covered(r.right_excess(data[i]));
			}
			return(ret1 && ret2);
		}
	}
	else
	{
		assert(i >= in_use);
		// r is not covered by *this.
		return 0;
	}
}

// A simple helper
// Make sure that data is at leasts (adjusting howmany,but not in_use).
void CRSet::ensure_min_size(int s)
{
	assert(class_invariant());
	// May need to allocate some new memory.
	if (s > howmany)
	{
		CharRange *d(new CharRange[howmany = s + expansion_size]);
		for (int i = 0; i < in_use; i++) d[i] = data[i];
		delete[]data;
		data = d;
	}
	assert(class_invariant());
}

// Add a CharRange to this set, splitting it as required.
// Adding begins at i.This is used in CRSet : add().
void CRSet::add_at(const CharRange a, int i)
{
	assert(class_invariant());
	assert(a.class_invariant());
	// Go through data[] to see if a can be coalesced with data[i].
	for (; i < in_use && !data[i].not_disjoint(a); i++);
	/**
	 Perhaps this is a coalescing candidate.
	 There are serveral possibilities,namely:
	 (1). a and data[i] are disjoint
	 (2). a <= data[i] (a is entirely contained in data[i])
	 (3). data[i] <= a
		a and data[i] are not disjoint(but no containment holds).
		In this case,we have three pieces: the intersection, and a slice each from a, data[i].
	 **/
	if (i < in_use)
	{
		assert(data[i].not_disjoint(a));
		if (data[i] == a); // Nothing to do
		else 
		{
			assert(data[i].not_disjoint(a) && data[i] != a);
			/**
			 a needs some splitting. We know that the excess does not fall into data[0..i],
			 we begin adding the excess at data[i+1].
			 For efficiency(not impplemented here),we could just append any part of data[i] that doesn't fall within a,
			 since data[i] is pairwise disjoint with all other elements in array data[].
			 **/
			CharRange old(data[i]);
			data[i].intersection(a);
			// data[i] now contain old intersection a

			// Now deal with the left and right excesses of old with a.
			// There are a few possibilites:
			if (a.low() != old.low())
			{
				// Then there is left excess
				add_at(a.left_excess(old), i + 1);
			}
			if (a.high() != old.high())
			{
				// Then there is right excess
				add_at(a.right_excess(old), i + 1);
			}
		}
	} 
	else  
	{
		assert(i >= in_use);
		// There may still be something left to put in data[].
		append(a);
	}
	assert(class_invariant());
	return;
}

std::ostream& operator<<(std::ostream& os, const CRSet& r)
{
	os << '{';
	for (int i = 0; i < r.in_use; i++) os << ' ' << r.data[i] << ' ';
	return (os << '}');
}

