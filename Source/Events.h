#pragma once
#include <string>
#include "stdafx.h"
class Entity;
class Collider;


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
		COLLISION_FAULT,
	};

	Collision() {}
	Collision(CollisionDirection direction, sf::Vector2f newPos, Entity* entity, Entity* otherEntity = NULL)
		: m_direction{ direction }, m_newEntPos{ newPos }, m_entity{ entity }, m_other_entity {otherEntity}
	{
	}

	CollisionDirection m_direction;			//	Direction of collision
	sf::Vector2f m_newEntPos;
	Entity* m_entity;			//	Entity that collided
	Entity* m_other_entity = NULL;

	const EventID eventID = COLLISION;
};

struct Action : public Event				//	An action that the m_entity performed
{
	const enum EntAction
	{
		NOTHING,
		/*ENTITY_JUMP,*/			//	Trigger a jump event
		ENTITY_UP,				//	Go up
		ENTITY_DOWN,			//	-- down 
		ENTITY_LEFT,			//	-- left
		ENTITY_RIGHT,			//	-- right
		STOP_ENTITY_UP,			//	Stop up movement
		STOP_ENTITY_DOWN,		//	---- down 
		STOP_ENTITY_LEFT,		//	---- left 
		STOP_ENTITY_RIGHT,		//	---- right

		ENTITY_GRAB,			//	Entity is grabbing an object
		ENTITY_BUILD,			//	Entity wants to build something

		ENTITY_CLICK_LEFT		//	User clicked left mouse button
	};

	Action() {}
	bool operator==(EntAction action) const { return m_action == action; }
	Action(Entity* m_entity, EntAction action = NOTHING)
		: m_entity{ m_entity }, m_action{ action }
	{
		 
	}

	EntAction m_action = NOTHING;						//	Action the m_entity performed
	Entity* m_entity;

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

struct MousePosition : public Event		//	Currently used as an example on how to create Events
{
	sf::Vector2f mousePos;				//	In world coordinates
	const EventID eventID = MOUSE_POS;
};
