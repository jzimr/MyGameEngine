#pragma once
#include "stdafx.h"
#include "Component.h"
#include <bitset>
#include <algorithm>
#include <vector>
#include <cassert>
#include "World.h"

enum class Event
{
	IS_IN_AIR,			//	An entity is in the air
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
	virtual void				onNotify(int entity, Event event) const;//	Get notified from subscriptions
	void						addObserver(const System* observer);	//	Subscribe observers to this
	void						removeObserver(const System* observer);	//	Remove them

protected:
	//	TODO: Replace with callbacks
	void						notify(int entity, Event event);		//	Notify subscribers

protected:
	std::vector<const System*> observers;			//	List of subscribers
};
