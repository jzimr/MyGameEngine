#pragma once
#include "stdafx.h"
#include "Component.h"
#include <bitset>
#include <algorithm>
#include <cassert>
#include "World.h"

//enum class UpdateCommands
//{
//	ADD,
//	REMOVE,
//
//};

class System : sf::NonCopyable
{
public:
								System();

	virtual void				init();				//	At initialization of system
	
	virtual void				begin();			//	Before update()
	virtual void				update(float dt);	//	Each game tick
	virtual void				end();				//	After update()

	virtual void				onEntityUpdate(Entity* ent) = 0;
};
