#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager()
	: entityFactory{}
{
	std::cout << entities.size() << '\n';
}

Entity* EntityManager::createEntity(sf::Vector2f position)
{
	EntPtr newEntity(new Entity(uniqueID++));
	entities.push_back(std::move(newEntity));

	return entities.back().get();
}

Entity* EntityManager::createEntity(std::string ID, sf::Vector2f position)
{
	EntPtr newEntity = entityFactory.spawnEntity(uniqueID++, ID, position);
	entities.push_back(std::move(newEntity));
	return entities.back().get();
}

bool EntityManager::removeEntity(unsigned int entID)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getID() == entID)
		{
			entities.erase(entities.begin() + i);
			return true;
		}
	}
	return false;				//	If not found
}

Entity* EntityManager::getEntity(unsigned int entID)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getID() == entID)
		{
			return entities[i].get();
		}
	}
	return NULL;
}



std::vector<Entity*> EntityManager::getAllEntities()
{
	std::vector<Entity*> entsToReturn;
	
	for (int i = 0; i < entities.size(); i++)
		entsToReturn.push_back(entities[i].get());

	return entsToReturn;
}

//	Initialize static variables

std::vector<EntPtr> EntityManager::entities{};
unsigned int EntityManager::uniqueID{ 10 };		//	0-9 are reserverd:
//	------ Reservations of IDs ------
//	| 0 = ?
//	| 1 = CollisionsSystem: Creation of temporary entities to send collision event