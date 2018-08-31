#pragma once
#include "stdafx.h"
#include <memory>
#include <algorithm>
#include "Entity.h"
#include "Entity Factories/EntityFactory.h"

typedef std::shared_ptr<Entity> EntPtr;

//////////////////////	
//
//	TODO: Add a "pendingUpdate()" which checks if a new m_entity has been created
//		  or that an m_entity has gotten a new component. This is to reduce calls
//		  to the "getEntWithComps()" for each update();

class EntityManager
{
public:
	EntityManager();

	// Create a custom m_entity and add to list
	EntPtr& createEntity(sf::Vector2f position = sf::Vector2f(0,0));
	//	Create a premade m_entity (preferred)
	EntPtr& createEntity(std::string ID, sf::Vector2f position = sf::Vector2f(0, 0));
	//EntPtr& addEntity(Entity* ent);			//	Add the m_entity from parameter to list
	bool removeEntity(unsigned int entID);		//	Delete the m_entity from the list
	//EntPtr* getEntity(unsigned int entID);		//	Get m_entity by ID

	template<class T> std::vector<EntPtr>	getEntWithComp();
	template<class T, class... params> std::vector<EntPtr> getEntWithComps();
	std::vector<EntPtr>						getAllEntities();

private:
	static std::vector<EntPtr> entities;
	EntityFactory entityFactory;
	static unsigned int uniqueID;
};

template<class T> std::vector<EntPtr> EntityManager::getEntWithComp()
{
	std::vector<EntPtr> ents;

	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->hasComponent<T>())
		{
			ents.push_back(entities[i]);
		}
	}
	return ents;
}
template<class T, class... params> std::vector<EntPtr> EntityManager::getEntWithComps()
{
	std::vector<EntPtr> ents;

	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->hasComponents<T, params...>())
			ents.push_back(entities[i]);
	}
	return ents;
}

//	TODO:::


//	Disable entities (Useful for chunk loading!!)
//		You can then move the disabled enetities into the unloaded chunk class and load 
//		them fast when the chunk is loaded again