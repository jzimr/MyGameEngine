#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <filesystem>
#include <map>
#include <sstream>
#include "TextureHolder.h"
class Entity;
class EntityManager;

class EntityFactory
{
public:
	typedef std::unique_ptr<Entity> EntPtr;

public:
								EntityFactory();



	//	Create function for reading a new file (path) on runtime



	EntPtr		spawnEntity(int uniqueID, std::string ID, sf::Vector2f position = sf::Vector2f(0, 0));

private:
	//	Better to store path as it makes it easier to modify entities at
	//	runtime for testing purposes.
	//	First = Entity name, Second = path to m_entity file
	std::map<std::string, std::string> entities;
	TextureHolder<std::string> textureHolder;
	TextureHolder<std::string> spriteSheetHolder;

private:
	void						loadTextures();		//	Temporary

	//	Load all files from a directory and put it in a map
	template <typename Identifier>
	std::map<Identifier, std::string>	getAllFilesFromFolder(std::string folderPath)
	{
		std::map<Identifier, std::string> tempMap;

		//	For each file in folder
		for (auto & p : std::filesystem::directory_iterator(folderPath))
		{
			if (!p.is_regular_file())		//	Check if not directory, stream, etc.
				continue;

			///	Get the m_entity name
			std::string name = p.path().filename().string();		//	E.g. "Player.txt", "Player.dat"
			std::string path = p.path().string();		//	E.g. "Player.txt"
			auto checkIfFType = name.find_first_of('.');
			name.erase(checkIfFType);							//	now = "Player"
			name.erase(std::remove(name.begin(), name.end(), '"'), name.end());		//	now = Player																										//	Get the path
		

			tempMap.insert(std::make_pair(name, path));
		}

		return tempMap;
	}
};