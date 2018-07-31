#pragma once
#include "stdafx.h"
#include "Entity.h"
#include <filesystem>
#include <map>
#include <algorithm>
#include <cassert>
#include <memory>
#include "World.h"

class EntityFactory
{
public:
	typedef std::unique_ptr<Entity> EntPtr;

public:
								EntityFactory();
	void						getAllFromDirectory();
	EntPtr						createEntity(std::string entityName);


private:

private:
	std::map<std::string, std::string> entities;	// Entity name, path
	
};
