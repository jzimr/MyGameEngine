#include "stdafx.h"
#include "EntityManager.h"

EntityManager::EntityManager()
	: entityFactory{}
{
	std::cout << entities.size() << '\n';
}

EntPtr EntityManager::createEntity(sf::Vector2f position)
{
	EntPtr newEntity(new Entity(uniqueID++));
	entities.push_back(newEntity);

	return entities.back();
}

EntPtr EntityManager::createEntity(std::string ID, sf::Vector2f position)
{
	EntPtr newEntity = entityFactory.spawnEntity(uniqueID++, ID, position);
	entities.push_back(newEntity);
	return entities.back();
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

EntPtr EntityManager::getEntity(unsigned int entID)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getID() == entID)
		{
			return entities[i];
		}
	}
	return NULL;
}



std::vector<EntPtr> EntityManager::getAllEntities()
{
	return entities;
}

//	Initialize static variables

std::vector<EntPtr> EntityManager::entities{};
unsigned int EntityManager::uniqueID{ 0 };