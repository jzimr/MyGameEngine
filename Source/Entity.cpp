#include "stdafx.h"
#include "Entity.h"

Entity::Entity(int id)
	: uniqueID{ id }
{
}

int Entity::getID() const
{
	return uniqueID;
}