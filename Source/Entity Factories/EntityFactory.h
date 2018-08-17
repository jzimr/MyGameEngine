#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>
#include <sstream>
#include "TextureHolder.h"
//class World;
class Entity;
class EntityManager;

class EntityFactory
{
public:
	typedef std::shared_ptr<Entity> EntPtr;

private:
	enum LineType
	{
		COMPONENT,
	};

public:
	EntityFactory();




	//	Create function for reading a new file (path) on runtime



	std::shared_ptr<Entity>		spawnEntity(int uniqueID, std::string ID, sf::Vector2f position = sf::Vector2f(0, 0));

private:
	void						getEntitiesPath();
	void						loadTextures();		//	Temporary

private:
	//World * mWorld;
	//	Better to store path as it makes it easier to modify entities at
	//	runtime for testing purposes.
	//	First = Entity name, Second = path to entity file
	std::map<std::string, std::string> entities;
	TextureHolder<std::string> textureHolder;

};