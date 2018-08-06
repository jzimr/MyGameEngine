#include "stdafx.h"
#include "EntityFactory.h"
#include "World.h"

EntityFactory::EntityFactory(World * world)
	: mWorld{ world }
{
	getEntitiesPath();		//	Automatically load all entities from folder
}

void EntityFactory::getEntitiesPath()
{
	std::string path = "\Entities";

	//	For each file in folder
	for (auto & p : std::filesystem::directory_iterator(path))
	{
		if (!p.is_regular_file())		//	Check if directory, stream, etc.
			continue;

		///	Get the entity name
		std::string entityName = p.path().filename().string();		//	E.g. "Player.txt", "Player.dat"
		std::string path = p.path().string();		//	E.g. "Player.txt"
		auto checkIfFType = entityName.find_first_of('.');
		entityName.erase(checkIfFType);							//	now = "Player"
		entityName.erase(std::remove(entityName.begin(), entityName.end(), '"'), entityName.end());		//	now = Player																										//	Get the path

		///	Store in map
		entities.insert(std::pair(entityName, path));
	}
}

std::unique_ptr<Entity> EntityFactory::spawnEntity(std::string ID, int uniqueID, sf::Vector2f position)
{
	///	Find path from list
	assert(!entities.empty());			//	If there are no entities to spawn at all
	auto it = entities.find(ID);
	assert(it != entities.end());		//	If the entity was not found in the list
	std::string& path = it->second;

	///	Read contents from file
	std::ifstream file(path);
	std::unique_ptr<Entity> entity;

	if (file)
	{
		std::string line;
		entity = std::unique_ptr<Entity>(new Entity(uniqueID));

		//	Mandatory component
		entity->addComponent<Transform>();	
		entity->getComponent<Transform>().transform.setPosition(position);

		while (std::getline(file, line, '\n'))
		{
			std::istringstream iss(line);
			std::vector<std::string> words{
				std::istream_iterator<std::string>(iss),{}
			};
			if (words.empty())		//	Blank line detected, skip
				continue;

			///	Spaghetti code. Improve it. Please.
			if (words[0] == "Component")
			{
				if (words[1] == "Physics")
					entity->addComponent<Physics>();
				else if (words[1] == "Collider")
					entity->addComponent<Collider>();
				else if (words[1] == "Controller")
					entity->addComponent<Controller>();
				else if (words[1] == "Movement")
					entity->addComponent<Movement>();
				else if (words[1] == "Sprite2D")
					entity->addComponent<Sprite2D>();
			}
			else if (words[0] == "Texture")
			{
				Sprite2D* spriteComp = &entity->getComponent<Sprite2D>();
				Transform* transform = &entity->getComponent<Transform>();
				spriteComp->texture = mWorld->getTexture(words[1]);	//	Get texture from world
				spriteComp->sprite = sf::Sprite(spriteComp->texture);
				spriteComp->sprite.setPosition(transform->transform.getPosition());
			}
			else if (words[0] == "ColliderBox")
			{
				if (words[1] == "default")
				{
					Collider* collider = &entity->getComponent<Collider>();
					Sprite2D* sprite2D = &entity->getComponent<Sprite2D>();

					collider->colliderBox = sprite2D->sprite.getGlobalBounds();
					collider->colliderBox.left -= 1; collider->colliderBox.top -= 1;
					collider->colliderBox.width += 1; collider->colliderBox.height += 1;
				}
			}
		}
	}
	return std::move(entity);
}

//void EntityFactory::linkLineTypes()
//{
//	lineTypes.insert(std::make_pair("Component", COMPONENT));
//}
