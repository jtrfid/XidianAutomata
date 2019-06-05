/*************************************************************************
	As an example of an abstract state, consider class DSDFARev.
Implementation class: DSDFARev

Files: DSDFARev.h, SDDFARev.cpp

Uses: CharRange, CRSet, DTransRel, StateSet

Description: Class DSDFARev is used in the reversal of a DFA. It is an abstract state representing
a set of states, in the reversal of the deterministic automaton (the reversal of a
deterministic finite automaton is not necessarily deterministic). A DSDFARev is constructed
in the DFA member function reverse. Member functions support all of the required interface
of an abstract state.
 *************************************************************************/
//#pragma once

#ifndef AUTOMATA_DSDFAREV_H
#define AUTOMATA_DSDFAREV_H

#include <iostream>
// 去下行注释则禁用 assert()
// #define NDEBUG
#include <cassert>  // 必须包含
#include "CharRange.h"
#include "CRSet.h"
#include "DTransRel.h"

// This class is used to represent abstract States in a DFA that is still under construction. 
// It is used in the reversal of a DFA.
// Objects of the class represent States in the subset construction of the reverse of a DFA.
// 成员变量which代表abstract states. 
// out-labels()和out-transition(CharRange a)返回：进入当前对象which的“in”字符集和状态集，成为返回对象which的“out”字符集和状态集。就是“reverse”语义
class DSDFARev
{
public:
	// Must always have an argument-less constructor.
	inline DSDFARev();

	inline DSDFARev(const DSDFARev& r);

	// A special constructor:
	inline DSDFARev(const StateSet& rq, const DTransRel *rT, const StateSet *rS);

	inline const DSDFARev& operator = (const DSDFARev& r);

	// The required member functions :

	// which与*S是否有交集，有交集(二者有公共部分)，返回1，否则返回0
	// S与F互换，实现"reverse",表示which是final state.
	inline int final() const;

	// return  CRSet of (in-transitions of which)。进入“in”当前对象which的transitions的字符集将成为返回对象的“out”字符集，就是reverse语义。
	CRSet out_labels() const;

	// return which = {p | T(p,a)属于which },即进入(in)当前对象which的状态集,成为返回对象的out状态集，就是reverse语义。
	DSDFARev out_transition(const CharRange a) const;
	inline int operator == (const DSDFARev& r) const;
	inline int operator != (const DSDFARev& r) const;

	friend std::ostream& operator<<(std::ostream& os, const DSDFARev& r);

	inline int class_invariant() const;

private:
	// abstract State
	StateSet which;
	const DTransRel *T;
	const StateSet *S;
};

// Must always have an argument-less constructor.
inline DSDFARev::DSDFARev() :which(), T(0), S(0)
{

}

inline DSDFARev::DSDFARev(const DSDFARev& r) : which(r.which), T(r.T), S(r.S)
{
	assert(class_invariant());
}

// A special constructor:
inline DSDFARev::DSDFARev(const StateSet& rq, const DTransRel *rT, const StateSet *rS)
	:which(rq), T(rT), S(rS)
{
	assert(class_invariant());
}

inline const DSDFARev& DSDFARev::operator = (const DSDFARev& r)
{
	assert(r.class_invariant());
	which = r.which;
	T = r.T;
	S = r.S;
	assert(class_invariant());
	return(*this);
}

// The required member functions :

// which与*S是否有交集，有交集(二者有公共部分)，返回1，否则返回0
// S与F互换，实现"reverse",表示which是final state.
inline int DSDFARev::final() const
{
	assert(class_invariant());
	return(which.not_disjoint(*S));
}

inline int DSDFARev::operator == (const DSDFARev& r) const
{
	assert(class_invariant() && r.class_invariant());
	assert(T == r.T && S == r.S);
	return(which == r.which);
}

inline int DSDFARev::operator != (const DSDFARev& r) const
{
	return(!operator==(r));
}

inline int DSDFARev::class_invariant() const
{
	return(T != 0 && S != 0 && which.domain() == T->domain()
		&& which.domain() == S->domain());
}



#endif // !AUTOMATA_DSDFAREV_H


