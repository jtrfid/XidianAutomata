#pragma once
#ifndef STATETOSTATE
#define STATETOSTATE

#include <iostream>
#include <cassert>
#include "StateTo.h"
#include "State.h"

using namespace std;

class StateToState : protected StateTo<State>
{
public:

	StateToState();

	~StateToState();

	inline StateToState& add(State p, State q);

	inline StateToState& remove(const State p, const State q);

	void set_domain(const int r);

	inline int domain() const;

	State image(const State& r) const;

	inline friend std::ostream& operator<<(std::ostream& os, const StateToState& r);

	inline int class_invariant() const;

};

StateToState::StateToState()
{
	assert(class_invariant());
}

StateToState::~StateToState()
{
	//StateTo::~StateTo();
}

inline StateToState& StateToState::add(State p, State q)
{
	assert(class_invariant());
	assert(0 <= p && p < domain());
	assert((0 <= q) && (q < domain()));
	map(p) = q;
	assert(class_invariant());
	return(*this);
}

inline StateToState& StateToState::remove(const State p, const State q)
{
	assert(class_invariant());
	assert(0 <= p && p < domain());
	assert(0 <= q && q < domain());
	map(p) = -1;
	assert(class_invariant());
	return(*this);
}

void StateToState::set_domain(const int r)
{
	assert(class_invariant());
	assert(r >= domain());
	StateTo<State>::set_domain(r);
	for (int i = 0; i < r; i++) map(i) = -1;
	assert(class_invariant());
}

inline int StateToState::domain() const
{
	return(StateTo<State>::domain());
}

State StateToState::image(const State& r) const
{
	assert(class_invariant());
	assert(0 <= r && r < domain());
	return(lookup(r));
}

inline std::ostream& operator<<(std::ostream& os, const StateToState& r)
{
	assert(r.class_invariant());
	return(os << (const StateTo<State>&)r);
}

inline int StateToState::class_invariant() const
{
	return(StateTo::class_invariant());
}

#endif // !STATETOSTATE
