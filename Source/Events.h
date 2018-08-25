#pragma once
#include <string>
#include "stdafx.h"
class Entity;


struct Event
{
	//	Need a virtual function in base class to be able to use dynamic_cast
	virtual ~Event() {};

	const EventID eventID = BASE_EVENT;
};

struct Collision : public Event
{
	enum CollisionDirection
	{
		COLLISION_TOP,
		COLLISION_BOTTOM,
		COLLISION_RIGHT,
		COLLISION_LEFT,
		COLLISION_FAULT
	};

	Collision() {}
	Collision(CollisionDirection dir, sf::Vector2f newPos, std::shared_ptr<Entity> ent)
		: direction{ dir }, newEntPos{ newPos }, entity{ ent }
	{

	}

	CollisionDirection direction;			//	Direction of collision
	sf::Vector2f newEntPos;
	std::shared_ptr<Entity> entity;			//	Entity that collided

	const EventID eventID = COLLISION;
};

struct Action : public Event				//	An action that the entity performed
{
	const enum EntAction
	{
		NOTHING,
		ENTITY_JUMP,			//	Trigger a jump event
		ENTITY_LEFT,			//	Go left
		ENTITY_RIGHT,			//	Go right
		STOP_ENTITY_LEFT,		//	Stop left movement
		STOP_ENTITY_RIGHT,		//	Stop right movement
	};

	Action() {}
	Action(std::shared_ptr<Entity> entity/*, EntAction action = NOTHING*/)
		: m_entity{ entity }/*, m_action{ action }*/
	{
		 //
	}

	EntAction m_action = NOTHING;						//	Action the entity performed
	std::shared_ptr<Entity> m_entity;			

	const EventID eventID = ACTION;
};

struct Message : public Event			//	Messages that don't require an Entity
{
	enum M 
	{
		CHUNK_UPDATE,			//	List with loaded chunks has been updated
	};

	Message() {}
	Message(M m) : message{ m } {}

	M message;
	M operator()() const { return message; }
	bool operator==(M m) const { return m == message; }
	const EventID eventID = MESSAGE;
};

struct Explosion : public Event
{
	int damage;
	const EventID eventID = EXPLOSION;
};
