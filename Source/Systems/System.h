#pragma once
#include "stdafx.h"
#include "Component.h"
#include <bitset>
#include <algorithm>
#include <vector>
#include <cassert>
#include <functional>
#include "World.h"

enum class Event
{
	ENTITY_JUMP,			//	Trigger a jump event
	ENTITY_LEFT,			//	Go left
	ENTITY_RIGHT,			//	Go right
	STOP_ENTITY_LEFT,		//	Stop left movement
	STOP_ENTITY_RIGHT,		//	Stop right movement
};

class System : sf::NonCopyable
{
public:
								System();

	virtual void				init();				//	At initialization of system
	
	virtual void				begin();			//	Before update()
	virtual void				update(float dt);	//	Each game tick
	virtual void				end();				//	After update()

	//	Called when an entity has changed its components
	virtual void				onEntityUpdate(const Entity* ent) = 0;

	////////////////////////////////////////////////////////////
	/// Handle events between systems
	///	THINK: Maybe move all into a seperate class and rather 
	///		   have instances of its class instead?
	////////////////////////////////////////////////////////////
	virtual void				onNotify(int entity, std::function<void()> command);
	virtual void				onNotify(int entity, Event event);//	Get notified from subscriptions
	void						addObserver(System* observer);	//	Subscribe observers to this
	void						removeObserver(System* observer);	//	Remove them

protected:
	void						notify(int entity, std::function<void()> command);
	void						notify(int entity, Event event);		//	Notify subscribers

protected:
	std::vector<System*> observers;			//	List of subscribers
};
