#include "stdafx.h"
#include "State.h"

State::State(Entity* ent)
	: Component(ent)
	, state{}
{
}

bool State::isActive(StateID id)
{
	return state.test(id);
}

void State::toggleID(StateID id)
{
	state.flip(id);
}

