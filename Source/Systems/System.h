#pragma once
#include "stdafx.h"
#include "Component.h"
#include <bitset>
#include <algorithm>
#include <vector>
#include <cassert>
#include <functional>
#include "EntityManager.h"
//#include "Events.h"
#include "EventManager.h"

class System : sf::NonCopyable
{
public:
	typedef std::shared_ptr<Entity> EntPtr;

public:
								System();

	virtual void				configure(EventManager& events);		//	At initialization of system
	
	virtual void				begin();			//	Before update()
	virtual void				update(float dt, EventManager& events);	//	Each game tick
	virtual void				end();				//	After update()

	//	Called when an entity has changed its components
	//virtual void				onEntityUpdate(const Entity* ent) = 0;

	////////////////////////////////////////////////////////////
	/// Handle events between systems
	///	THINK: Maybe move all into a seperate class and rather 
	///		   have instances of it instead?
	////////////////////////////////////////////////////////////
	virtual void				onNotify(int entity, std::function<void()> command);
	virtual void				onNotify(int entity, EventID event);//	Get notified from subscriptions
	void						addObserver(System* observer);	//	Subscribe observers to this
	void						removeObserver(System* observer);	//	Remove them

protected:
	void						notify(int entity, std::function<void()> command);
	void						notify(int entity, EventID event);		//	Notify subscribers

protected:
	std::vector<System*> observers;			//	List of subscribers
	std::vector<EntPtr> entities;			//	List of entities for the system
};
