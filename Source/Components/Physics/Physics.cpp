#include "stdafx.h"
#include "Physics.h"
#include "Entity.h"

Physics::Physics(Entity* ent)
	: Component{ ent }
	, velocity{}
{

}

void Physics::update(float dt)
{
	std::cout << velocity.x << '\n';
	entity->move(dt * velocity);
}

void Physics::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

sf::Vector2f Physics::getVelocity() const
{
	return velocity;
}
