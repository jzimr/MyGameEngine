#include "stdafx.h"
#include "EntityFactory.h"
#include <fstream>
#include "Components/Controller.h"
#include "Components/Health.h"
#include "Components/Sprite2D.h"
#include "Components/State.h"
#include "Components/Test.h"
#include "Components/Physics/Physics.h"

EntityFactory::EntityFactory()
	: entities{}
{
	getAllFromDirectory();		//	Only for testing
}

void EntityFactory::getAllFromDirectory()
{
	std::string path = "\Entities";

	//	For each file in folder
	for (auto & p : std::filesystem::directory_iterator(path))
	{
		if (p.is_regular_file())		//	Check if not directory, stream, etc.
		{
			//	Get the entity name
			std::string entityName = p.path().filename().string();		//	E.g. "Player"
			auto checkIfFType = entityName.find_first_of('.');
			assert(checkIfFType == -1);	//	If the file has a specific filetype (Tip: It shouldn't have!)	
			entityName.erase(std::remove(entityName.begin(), entityName.end(), '"'), entityName.end());		//	now = Player

			//	Get the path
			std::string path = p.path().filename().string();		//	E.g. "Player"

			//	Store into map
			entities.insert(std::pair(entityName, path));
		}
	}
}

EntityFactory::EntPtr EntityFactory::createEntity(std::string entityName)
{
	EntityFactory::EntPtr entity(new Entity());

	auto it = entities.find(entityName);
	assert(it != entities.end());			//	If name not found in map
	
	std::string entityPath = it->second;	//	Get file path
	std::ofstream file(entityPath);
	
	if (file)			//	If file exists
	{
		
	}
	
}