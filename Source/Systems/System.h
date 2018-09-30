#pragma once
#include "stdafx.h"
#include "Component.h"
#include <bitset>
#include <algorithm>
#include <vector>
#include <cassert>
#include <functional>
#include "EntityManager.h"
#include "EventManager.h"

class System : sf::NonCopyable
{
public:
								System();

	virtual void				configure(EventManager& events);		//	At initialization of system
	
	virtual void				begin();			//	Before update()
	virtual void				update(float dt, EventManager& events);	//	Each game tick
	virtual void				end();				//	After update()

protected:
	std::vector<Entity*> entities;			//	List of entities for the system
};
