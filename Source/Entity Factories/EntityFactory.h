#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>
#include <sstream>
class World;
class Entity;

class EntityFactory
{
private:
	enum LineType
	{
		COMPONENT,
	};

public:
	EntityFactory(World* world);
	//void						createPlayer();
	//void						createGround();
	//void						createBlock();



	//	Create function for reading a new file (path) on runtime



	std::unique_ptr<Entity>		spawnEntity(std::string ID, int uniqueID, sf::Vector2f position = sf::Vector2f(0, 0));

private:
	void						getEntitiesPath();
	//void						linkLineTypes();

private:
	World * mWorld;
	//	Better to store path as it makes it easier to modify entities at
	//	runtime for testing purposes.
	//	First = Entity name, Second = path to entity file
	std::map<std::string, std::string> entities;	


	//std::map<std::string, LineType> lineTypes;
};