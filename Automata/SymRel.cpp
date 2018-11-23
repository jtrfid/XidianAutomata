/**********************************************************************
	Implementation: SymRel inherits for implementation from StateRel. All of the member functions
simply call through to StateRel.
 **********************************************************************/
#include "stdafx.h"
#include "SymRel.h"

// Make *this into the identity relation.
SymRel& SymRel::identity()
{
	assert(class_invariant());
	// Iterate over the States,setting them to the identify.
	for (State p = 0; p < domain(); p++)
	{
		StateTo<StateSet>::map(p).clear();
		StateTo<StateSet>::map(p).add(p);
	}
	assert(class_invariant());
	return(*this);
}

// Complement *this.
SymRel& SymRel::complement()
{
	assert(class_invariant());
	// Go through all of the StateSets and complement them.
	for (State p = 0; p < domain(); p++)
	{
		StateTo<StateSet>::map(p).complement();
	}
	assert(class_invariant());
	return(*this);
}

// 修改为inline, 否则连接器找不到StateRel
inline std::ostream& operator<<(std::ostream& os, const SymRel& r)
{
	assert(r.class_invariant());
	return(os << (const StateRel&)r);
}

