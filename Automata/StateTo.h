/*************************************************************************
	Implementation class: State To
	Files: StateTo.h
	Uses: State
	
	Description: StateTo is a template class implementing mappings from States to some class T(the
	template type parameter). It is used extensively in transition relations and binary relations
	on states. Two methods of mapping a State are provided:
		• Member function map takes a State and returns a non-const reference to the associated T. 
		  This is most often used to set up the map, by changing the associated T .
		• Member function lookup takes a State and returns a const reference to the associated T. 
		  This is intended for use in clients that only lookup information, without changing the map.

		StateTo includes a reincarnate member function, which does not reincarnate the T's. As
	with StateSets, the domain of the StateTo must be explicitly maintained by the client. A
	special member function disjointing_union is available which performs a normal union after
	the domain of the incoming StateTo has been renamed to avoid clashing with the domain of *this.
	
	Implementation: Each StateTo contains a pointer to a dynamically allocated array of T, an
	integer indicating the size of the array, and an integer indicating how many of the array
	elements are in use. Whenever the array of T is enlarged, a bit extra is allocated to avoid
	repeated calls to new. Class T must have a default constructor, an assignment operator and
	an insertion(output) operator.
	
	Performance: StateTo would benefit from use-counting in the class T. Use-counting in StateTo
	itself would likely add too much overhead if it were already done in T.
 *************************************************************************/
//#pragma once


#ifndef AUTOMATA_STATETO_H
#define AUTOMATA_STATETO_H


#include<iostream>
 // 去下行注释则禁用 assert()
 // #define NDEBUG
#include <cassert>  // 必须包含
#include "State.h"

/*************************************************************************************
// Map State's to class T. Used to implement transitions(TransRel and DTransRel)
// and State relations(StateRel and StateEqRel).

   StateTo<T> 描述state to T(eg. StateSet)的映射(map)关系。
   T *data; 内部使用data[state]表示这种映射关系。
   set_domain(const int r)设置动态数组data的大小，表示存储这种关系的容量,对*data分配了存储空间。
   int howmany; 表示动态数组data大小，包含扩充部分(expansion_extra常量)
   int in_use; 表示实际使用的data大小。

   以下两个函数都是返回state r to T的映射(map),前者返回Not const T&，用于设置；后者返回const T&，用于查询。
   二者均没有给data[r]赋值。留给继承类完成。
   T& map(const State r); retun data[r];  Not const，用于设置；
   const T& lookup(const State r) return data[r]，用于查询。在派生类中给data[r]赋值后才能使用。

   StateTo<T>& StateTo<T>::disjointing_union(const StateTo<T>& r)
  合并this和r ==> this，保证不重叠, this.domain += r.domain;
**************************************************************************************/
template<class T>
class StateTo
{
	// Cannot be protected because the function in DFAseed.h(construct_components) needs access.
public:
	// Constructors, destructors, operator=:

	// Default is to not map anything.
	StateTo();

	// Copying can be costly. Use-counts could make this cheaper.
	StateTo(const StateTo<T>& r);

	// Assume delete[]0 is okay.
	virtual ~StateTo();

	// Use counts could make this cheaper.
	const StateTo<T>& operator=(const StateTo<T>& r);

	// First, a const lookup operator.
	inline const T& lookup(const State r) const;

	// Used to associate a State and a T in the mapping. Note: not const.
	inline T& map(const State r);

	// Some domain members:

	// How many States can *this map ?
	inline int domain() const;

	// Set a new domain.
	void set_domain(const int r);

	// Note the reincarnate() doesn't reincarnate the T's.
	inline void reincarnate();

	// Allow two mappings to be combined; the domain of *this remains the same, while the
	// domain of r is renamed to not clash with the domain of *this.
	StateTo<T>& disjointing_union(const StateTo<T>& r);

	//Some extras:

	// 必须类内定义，使其派生类可以使用inline，在.h文件的类外定义std::ostream& operator<<()
	friend std::ostream& operator<<(std::ostream& os, const StateTo<T>& r)
	{
		assert(r.class_invariant());
		for (int i = 0; i < r.in_use; i++)
			os << i << "->" << r.data[i] << std::endl;
		return(os);
	}

	// Assert that everything's okay.
	inline int class_invariant() const;

private:
	// Represent the map as a dynamically allocated array of T's (include expansion_extra).
	// indicating the size of the array
	int howmany;

	// indicating how many of the dynamically allocated array of T's elements are in use.
	// [0,domain) -> index of T *data;
	int in_use;
	// dynamically allocated array of T's (include expansion_extra).
	T *data;

	// When the array is grown by a certain amount, it also grows by an extra
	// buffer amount for efficiency.
	enum { expansion_extra = 5 };
};

// Default is to not map anything.
template<class T>
StateTo<T>::StateTo() :
	howmany(0),
	in_use(0),
	data(0)
{
	assert(class_invariant());
}

// Copying can be costly. Use-counts could make this cheaper.
template<class T>
StateTo<T>::StateTo(const StateTo<T>& r) :
	howmany(r.in_use + expansion_extra),
	in_use(r.in_use),
	data(new T[r.in_use + expansion_extra])
{
	assert(r.class_invariant());
	for (int i = 0; i < r.in_use; i++) data[i] = r.data[i];
	assert(class_invariant());
}

// Assume there is nothing wrong with delete []O. 
template<class T>
StateTo<T>::~StateTo()
{
	delete[]data;
}

// Use counts could make this cheaper.
template<class T>
const StateTo<T>& StateTo<T>::operator=(const StateTo<T>& r)
{
	assert(r.class_invariant());
	// Prevent assignment to self.
	if (this == &r) return *this;
	if (howmany < r.in_use)
	{
		delete[]data;
		data = new T[howmany = r.in_use + expansion_extra];
	}
	in_use = r.in_use;
	assert(in_use <= howmany);
	for (int i = 0; i < in_use; i++) data[i] = r.data[i];
	assert(class_invariant());
	return(*this);
}

// The actual mapping function
// First, a const lookup operator.
template<class T>
inline const T& StateTo<T>::lookup(const State r) const
{
	assert(class_invariant());
	// First check that it's in bounds
	assert(0 <= r && r < domain());
	return(data[r]);
}

// Used to associate a State and a T in the mapping. Note: not const.
template<class T>
inline T& StateTo<T>::map(const State r)
{
	assert(class_invariant());
	// First check that it's in bounds
	assert(0 <= r && r < domain());
	return(data[r]);
}

// How many States can *this map?
template<class T>
inline int StateTo<T>::domain() const
{
	return(in_use);
}

// Set a new domain.
template<class T>
void StateTo<T>::set_domain(const int r)
{
	assert(class_invariant());
	// Make sure that things aren't shrinking.
	assert(r >= in_use);
	if (r > howmany)
	{
		T *d(new T[howmany = r + expansion_extra]);
		for (int i = 0; i < in_use; i++) d[i] = data[i];
		delete[]data;
		data = d;
		// Note: the newly created T's are only default constructed.
	}
	in_use = r;
	assert(class_invariant());
}

// Note the reincarnate() doesn't reincarnate the T's.
template<class T>
inline void StateTo<T>::reincarnate()
{
	in_use = 0;
}

// Allow two mappings to be combined; the domain of *this remains the same, while the
// domain of r is renamed to not clash with the domain of *this.
template<class T>
StateTo<T>& StateTo<T>::disjointing_union(const StateTo<T>& r)
{
	assert(class_invariant() && r.class_invariant());
	// Don't do anything that's needless
	if (r.domain() != 0)
	{
		int olddom = domain();
		set_domain(olddom + r.domain());
		assert(domain() == olddom + r.domain());
		// Copy r into the new location.
		for (int i = 0; i < r.domain(); i++) data[i + olddom] = r.data[i];
	}
	assert(class_invariant());
	return(*this);
}

//Some extras:

// T is assumed to have an operator<<
/*******************************************************************
// 修改为inline,否则连接器找不到StateTo<Trans>,但是std::cout<<出现同样的错误，移入类内定义
template<class T>
inline std::ostream& operator<<(std::ostream& os, const StateTo<T>& r)
{
	assert(r.class_invariant());
	for (int i = 0; i < r.in_use; i++)
		os << i << "->" << r.data[i] << endl;
	return(os);
}
*********************************************************************/

// Assert that everything's okay.
template<class T>
inline int StateTo<T>::class_invariant() const
{
	return(0 <= in_use
		&& in_use <= howmany
		// So 0 <= howmany by transitivity.
		&& (howmany != 0 ? data != 0 : data == 0));
}

#endif // !AUTOMATA_STATETO_H
