#pragma once
#include "stdafx.h"
#include "Components/Component.h"
#include <bitset>

////////////////////////////////////////////////////////////
/// Hub for all information regarding the entity's state
/// E.g. moving, jumping, attacking, sleeping, etc.
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
/// NOT IN USE YET
/// 
////////////////////////////////////////////////////////////

class State : public Component
{
public:
	enum StateID
	{
		Idle,
		MovingLeft,
		MovingRight,
	};

public:
								State(Entity* ent);

	bool						isActive(StateID id);
	void						toggleID(StateID id);

private:
	std::bitset<16>				state;
};
