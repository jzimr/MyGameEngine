#include "stdafx.h"
//#include "Physics.h"
//#include "Entity.h"
//
//Physics::Physics(Entity* ent)
//	: Component{ ent }
//	, velocity{}
//{
//
//}
//
//void Physics::update(float dt)
//{
//	updateGravity(dt);
//	m_entity->move(dt * velocity);
//}
//
//void Physics::setVelocity(sf::Vector2f vel)
//{
//	velocity = vel;
//}
//
//sf::Vector2f Physics::getVelocity() const
//{
//	return velocity;
//}
//
//void Physics::updateGravity(float dt)
//{
//	//	velocity += acceleration * dt;
//	//	position += velocity * dt;
//
//	velocity += (sf::Vector2f(0, gravity * dt));
//	m_entity->move(sf::Vector2f(0, velocity.y * dt));
//
//	//std::cout << velocity.y << '\n';
//
//		//	time += timestep;
//		//	position += timestep * (velocity + timestep * acceleration / 2);
//		//	velocity += timestep * acceleration;
//}
