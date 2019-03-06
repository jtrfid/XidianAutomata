//#pragma once
#ifndef AUTOMATA_BITVEC_H
#define AUTOMATA_BITVEC_H


#include <iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include <algorithm> // min(),max()

/**********************************************************
 Implement a bit-vector. This class can be replaced with any standard library class that
 provides the same functionality. Many of the normal bit-wise operators are available on
 Bit Vec's.
 Bit Vec's clients are StateSet and the item set's (ISImpl).
 Files: bitVec.h, bitVec.cpp
 Uses:
 Description: Bit vectors wider than a single word are used in implementing sets without a
 compiled-in size bound. In addition to many of the standard bit level operators, iterators
 are also provided. The vectors have a width(domain) that is adjustable through a member function.
 Binary operators on vectors must have operands操作数 of the same width, and such width management
 is left to the client. When a vector is widened, the newly allocated bits are assumed to be zero.
 ============================================
 // uesd max number bits in data, denote width(domain),[0,bits_in_use) == > [0,width)
 // width = domain = bits_in_use
 int bits_in_use;
 // number of words = 1,2,...
 int words;
 // save bytes of words,[0,1,2,...words)
 unsigned int *data;

 bits_per_word = (sizeof(unsigned int) * 8) = 4B*8b = 32 bits 每个字可以表示32个状态,1个word是1个unsigend int(4Bytes,32bits)
 2^n = 1,表示第n个状态，n = 0,1,2，...
 int st;
 words = st / bits_per_word + ((st % bits_per_word) != 0 ? 1 : 0));  // int words_required(const int st) const
 word_index = r / bits_per_word;   // int word_index(const int r) const
 bit_index = r % bits_per_word;    // int bit_index(const int r) const
 BitVec::set_width(const int r) --> 调用words_required(r)，计算字数(words); 设置bits_in_use=r; data = new unsigned int[words]
 BitVec& set_bit(const int r) --> data[word_index(r)] |= (1U << bit_index(r));
 int width();  --> bits_in_use
 **********************************************************/
class BitVec
{
public:
	// Constructors,destructors,operator=:

	// Default operator creates the emptyset,with little effort.
	// This assumes that delete[]0 is okay(when it is deleted later).
	inline BitVec();

	// Normal copy constructor.
	BitVec(const BitVec& r);

	// Normal non-virtual destructor.
	inline ~BitVec();

	// Needs a special operator=.
	const BitVec& operator=(const BitVec& r);

	// Tests:
	// A special equality operator.
	int operator==(const BitVec& r) const;

	// Inequality operator.
	inline int operator!=(const BitVec& r) const;

	// Is there a bit set ?
	int something_set() const;

	// Howmany bits are set ?
	// return (max index of bit is set to 1) + 1; [0,bits_in_use(width)]
	int bits_set() const;

	// Bit vector operators :

	// set a bit
	inline BitVec& set_bit(const int r);

	// unset a bit
	inline BitVec& unset_bit(const int r);

	BitVec& bitwise_or(const BitVec& r);

	BitVec& bitwise_and(const BitVec& r);

	BitVec& bitwise_unset(const BitVec& r);

	BitVec& bitwise_complement();

	// Bitwise containment.
	int contains(const BitVec& r) const;

	// Is a bit set?
	// return true(1), if r index of bit is set to 1; else return false(0)  
	inline int contains(const int r) const;

	// Does *this have a bit in common with r ?
	int something_common(const BitVec& r) const;

	// Make *this the empty vector.
	void clear();

	// What is the set bit with the smallest index in *this?
	int smallest() const;

	// Some width related members:

	// return domain(bit_in_use),[0,domain)
	// domain = width = bit_in_use
	inline int width() const;

	// domain = with = bit_in_use, [0,domain)
	void set_width(const int r);

	// Recycle this BitVec.
	inline void reincarnate();

	// Shift *this left, zero filling.
	BitVec& left_shift(const int r);

	// Append another bit-vector.
	BitVec& append(const BitVec& r);

	// iterators:

	// Place the index of the first set bit in the iteration in reference r.
	// r == -1 if there is no first one.
	inline int iter_start(int& r) const;

	// Is r the last set bit in an iteration sequence.
	// if (r== -1) retrun 1; else return 0
	inline int iter_end(int r) const;

	// Place the next set bit, after r(in the iteration sequence), in reference r.
	int iter_next(int& r) const;

	// Other special members:

	friend std::ostream& operator<<(std::ostream& os, const BitVec& r);

	// Structural invariant on the BitVec.
	inline int class_invariant() const;

private:
	// Some trivial helpers:

	// Compute the number of words required to hold st bits.
	inline int words_required(const int st) const;

	// Compute the word index of a particular bit r.
	inline int word_index(const int r) const;

	// Compute the hit index(from the LSB) of a hit r.
	inline int bit_index(const int r) const;

	// Actual representation:

	// uesd max number bits in data, denote width(domain),[0,bits_in_use) == > [0,width)
	int bits_in_use;
	// number of words，1,2,3,...
	int words;
	// save bytes of words,[0,1,2,...width(domain)]
	unsigned int *data;

	// A class constant, used for bit-vector width.
	enum { bits_per_word = (sizeof(unsigned int) * 8) };
};

// Now for the inline versions of the member functions:

// Default operator creates the emptyset,with little effort.
// This assumes that delete[]0 is okay(when it is deleted later).
inline BitVec::BitVec() :bits_in_use(0), words(0), data(0)
{
	assert(class_invariant());
}

// Normal non-virtual destructor.
inline BitVec::~BitVec()
{
	assert(class_invariant());
	delete[]data;
	// 安全起见，其后添加
	data = 0;
}

// Inequality operator.
inline int BitVec::operator!=(const BitVec& r) const
{
	return(!operator==(r));
}

// set a bit
inline BitVec& BitVec::set_bit(const int r)
{
	assert(0 <= r && r < width());
	assert(class_invariant());
	data[word_index(r)] |= (1U << bit_index(r));
	return(*this);
}

// unset a bit
inline BitVec& BitVec::unset_bit(const int r)
{
	// Unset the r'th bit.
	assert(0 <= r && r < width());
	assert(class_invariant());
	data[word_index(r)] &= ~(1U << bit_index(r));
	return(*this);
}

// Is a bit set?
// r: [0,bits_in_use(width))
// return true(1), if r index of bit is set to 1; else return false(0)  
inline int BitVec::contains(const int r) const
{
	// Check if the r'th bit is set
	assert(r < width());
	assert(class_invariant());
	return((data[word_index(r)] & (1U << bit_index(r))) != 0U);
}

inline int BitVec::width() const
{
	return(bits_in_use);
}

// Recycle this BitVec.
inline void BitVec::reincarnate()
{
	assert(class_invariant());
	clear();
	bits_in_use = 0;
	assert(class_invariant());
}

// Place the index of the first set bit in the iteration in reference r.
// r == -1 if there is no first one.
inline int BitVec::iter_start(int& r) const
{
	assert(class_invariant());
	return(r = smallest());
}

// Is r the last set bit in an iteration sequence.
// if (r== -1) retrun 1; else return 0
inline int BitVec::iter_end(int r) const
{
	return(r == -1);
}

// Structural invariant on the BitVec.
inline int BitVec::class_invariant() const
{
	return((width() <= words * bits_per_word)
		&& (width() >= 0)
		&& (words >= 0)
		&& (words == 0 ? data == 0 : data != 0));
}

// Compute the number of words required to hold st bits.
inline int BitVec::words_required(const int st) const
{
	// This may be a little more complicated than it has to be.
	return(st / bits_per_word + ((st % bits_per_word) != 0 ? 1 : 0));
}

// Compute the word index of a particular bit r.
inline int BitVec::word_index(const int r) const
{
	return(r / bits_per_word);
}

// Compute the hit index(from the LSB) of a hit r.
inline int BitVec::bit_index(const int r) const
{
	return(r % bits_per_word);
}


#endif // !AUTOMATA_BITVEC_H
