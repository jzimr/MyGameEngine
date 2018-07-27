#pragma once
#include "stdafx.h"
#include "Component.h"
#include "State.h"

////////////////////////////////////////////////////////////
/// \requires Physics(Component), State(Component)
/// Drives the player movement. One instance at a time
////////////////////////////////////////////////////////////
class Controller : public Component
{
public:
	typedef State::StateID StateID;

public:
	Controller(Entity* ent);

	void				update(float dt) override;
};
