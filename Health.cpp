#include "stdafx.h"
#include "Health.h"

Health::Health(Entity* ent)
	: Component{ ent }
	, health{ 100 }
{

}

int Health::getHealth() const
{
	return health;
}