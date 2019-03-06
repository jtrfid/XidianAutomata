/**********************************************************************************************
 Implementation: The implementation is largely replaceable by any standard library providing
	the same functionality.The width is stored as an integer in the object, along with the
	number of words allocated.The vector itself is stored as a pointer to an allocated block
	of unsigned int. The width can only grow(except in the case of a reincarnate member function call; 
	it will then shrink to zero).
 Performance: The low level bit operations could benefit from being written in assembler.The
	copying of the data area that occurs in the copy constructor and assignment operator can
	be avoided by use - counting.The left shift operator and the iteration operators could be
	implemented more efficiently.
************************************************************************************************/

#include "BitVec.h"


// Normal copy constructor.
BitVec::BitVec(const BitVec& r):
	bits_in_use(r.bits_in_use),
	words(r.words),
	data(new unsigned int[r.words])
{
	for (int i = 0; i < words; i++) data[i] = r.data[i];
	// Bug!!! r.words = 0时，data分配了无元素的空数组，会引起class_invariant()异常
	// 如下处理
	if (r.words == 0)
	{
		delete[] data;
		data = 0;
	}

	assert(class_invariant());
}

// Needs a special operator=.
const BitVec& BitVec::operator=(const BitVec& r)
{
	assert(r.class_invariant());
	// Check against assignment to self.
	if (this != &r)
	{
		// The data area may need to be grow.
		if (words < words_required(r.width()))
		{
			words = words_required(r.width());
			// Wipe out previously used memory.
			// Assume delete[]0 is okay.
			delete[]data;
			// Could probably benefit from a specialized operator new.
			data = new unsigned int[words];
		}
		assert(words >= words_required(r.width()));
		bits_in_use = r.bits_in_use;
		int i = 0;
		for (i = 0; i < words_required(r.width()); i++) data[i] = r.data[i];
		// Make sure that nothing extraneous is in the vector.
		for (; i < words; i++) data[i] = 0U;
	}
	assert(class_invariant());
	return(*this);
}

// Tests:
// A special equality operator.
int BitVec::operator==(const BitVec& r) const
{
	assert(class_invariant() && r.class_invariant());
	// Can't be equal if bit counts aren't the same.
	assert(width() == r.width());
	// Compare all of the bits.
	for (int i = 0; i < std::min(words, r.words); i++)
	{
		if (data[i] != r.data[i]) return(0); // Return at the earliest possible moment.
	}
	return(1);
}

// Is there a bit set?
int BitVec::something_set() const
{
	assert(class_invariant());
	// Check if all bits are unset.
	unsigned int result = 0U;
	for (int i = 0; i < words; i++) result |= data[i];
	return(result != 0U);
}

// Howmany bits are set? 
// return (max index of bit is set to 1) + 1; [0,bits_in_use(width)]
int BitVec::bits_set() const
{
	assert(class_invariant());
	int s = 0;
	for (int st = 0; st < width(); st++)
	{
		if (contains(st)) s++;
	}
	return(s);
}

BitVec& BitVec::bitwise_or(const BitVec& r)
{
	assert(class_invariant() && r.class_invariant());
	assert(width() == r.width());
	// General-purpose counter
	for (int i = 0; i < std::min(words, r.words); i++) data[i] |= r.data[i];
	return(*this);
}

BitVec& BitVec::bitwise_and(const BitVec& r)
{
	assert(class_invariant() && r.class_invariant());
	assert(width() == r.width());
	for (int i = 0; i < std::min(words, r.words); i++) data[i] &= r.data[i];
	return(*this);
}

BitVec& BitVec::bitwise_unset(const BitVec& r)
{
	assert(class_invariant() && r.class_invariant());
	assert(width() == r.width());
	for (int i = 0; i < std::min(words, r.words); i++) data[i] &= ~r.data[i];
	return(*this);
}

BitVec& BitVec::bitwise_complement()
{
	assert(class_invariant());
	// Do a bitwise complement of all of data that's in use.
	int w = words_required(bits_in_use);
	for (int i = 0; i < w; i++) data[i] = ~data[i];
	// Now make sure that only bits that the only 1 bits are those that fall within [0,bits_in_use)
	if (bit_index(bits_in_use) != 0) {
		// There are some bit's that are not used in data[w-1].
		// "and" the unused ones away.
		data[w - 1] &= ((1U << bit_index(bits_in_use)) - 1);
	}
	assert(class_invariant());
	return(*this);
}

// Bitwise containment.
int BitVec::contains(const BitVec& r) const
{
	assert(class_invariant()&&r.class_invariant());
	assert(width() == r.width());
	for (int i = 0; i < std::min(words, r.words); i++)
	{
		if (r.data[i] != (r.data[i] & data[i])) return(0);
	}
	return(1);
}

// Does *this have a bit in common with r?
int BitVec::something_common(const BitVec& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(width() == r.width());
	// Check if there's a bit in common.
	unsigned int result = 0U;
	for (int i = 0; i < std::min(words, r.words); i++) result |= (data[i] & r.data[i]);
	return(result != 0U);
}

// Make *this the empty vector.
void BitVec::clear()
{
	// Zero-out all of the words.
	for (int i = 0; i < words; i++) data[i] = 0U;
}

// What is the set bit with the smallest index in *this?
int BitVec::smallest() const
{
	assert(class_invariant());
	// Find the first non-empty word.
	int r;
	int howfar = words_required(width());
	for (r = 0; r < howfar && data[r] == 0; r++);

	//Could be that there isn't one:
	if (r == howfar) return -1;

	// Find the first non-zero bit.
	int bitnum = r * bits_per_word;
	unsigned int d = data[r];
	// Keep eating bits until the least significant bit is 1.
	// We're sure that there will be a bit.
	assert(d != 0U);
	while (d % 2 == 0) {
		bitnum++;
		d = d >> 1;
	}
	return(bitnum);
}

void BitVec::set_width(const int r)
{
	assert(class_invariant());
	// Make sure that things are not shrinking.
	assert(r >= width());
	// The data[] area may need some growing.
	if (r > words*bits_per_word)
	{
		int w = words_required(r);
		unsigned int *d = new unsigned int[w];
		int i = 0;
		for (; i < words; i++) d[i] = data[i];
		// Make sure that now additional bits are set.
		for (; i < w; i++)d[i] = 0U;
		delete[]data;
		data = d;
		words = w;
	}
	bits_in_use = r;
	assert(class_invariant());
}

// Shift *this left, zero filling.
BitVec& BitVec::left_shift(const int r)
{
	// Don't do anything needless:
	if (r == 0) return(*this);
	
	words = words_required(width() + r);
	unsigned int *d = new unsigned int[words];
	for (int i = 0; i < words; i++) d[i] = 0U;
	int wi = word_index(r);
	int bi = bit_index(r);
	// (wi,bi)index where the first bit of data[] must go in d[].
	if (bi == 0) { // Word aligned.
		for (int i = 0; i < words_required(width()); i++) d[i + wi] = data[i];
	}
	else { // Deal with the unaliged case.
		// Mask has the (bi) least-significant bits on.
		unsigned int rmask = (1U << bi) - 1;
		for (int i = 0; i < words_required(width()); i++)
		{
			// move data[i] into d[i+wi] and d[i+wi+1]
			// d[i+wi] = (d[i+wi] & rmask) |((data[i)<<bi) & ~rmask);
			// Assume that zero-filling occurs on the LSB.
			d[i + wi] = (d[i + wi] & rmask) | (data[i] << bi);
			// bug!!!  this statement is not necessary!!!
			//d[i + wi + 1] = (data[i] >> (bits_per_word - bi)) & rmask;
		}
		delete[]data;
		data = d;
		bits_in_use += r;
	}
	return(*this);
}

// Append another bit-vector.
// The following could be made a lot more efficient by not constructing the local BitVec.
BitVec& BitVec::append(const BitVec& r)
{
	assert(class_invariant() && r.class_invariant());
	BitVec t(r);
	// Make room for *this.
	t.left_shift(width());
	assert(t.width() == width() + r.width());
	set_width(width() + r.width());
	assert(t.width() == width());
	bitwise_or(t);
	assert(class_invariant());
	return(*this);
}

// Place the next set bit, after r(in the iteration sequence), in reference r.
int BitVec::iter_next(int& r) const
{
	assert(class_invariant());
	// Find the next bit that is set.
	for (r++; r < width(); r++)
	{
		if (contains(r)) return(r);
	}
	return(r = -1);
}

std::ostream& operator<<(std::ostream& os, const BitVec& r)
{
	assert(r.class_invariant());
	// Output the BitVec as a space-separated sequence of set bits.
	int st;
	os << "{";
	for (r.iter_start(st); !r.iter_end(st); r.iter_next(st))
		os << " " << st << " ";
	return(os << "}");
}

