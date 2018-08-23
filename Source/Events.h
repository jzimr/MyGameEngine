#pragma once
#include <string>

enum EventID
{
	BASE_EVENT,
	ENTITY_JUMP,			//	Trigger a jump event
	ENTITY_LEFT,			//	Go left
	ENTITY_RIGHT,			//	Go right
	STOP_ENTITY_LEFT,		//	Stop left movement
	STOP_ENTITY_RIGHT,		//	Stop right movement

	COLLISION_RIGHT,		//	Collision to the right of object
	COLLISION_LEFT,			//	Collision to the left   -- || --
	COLLISION_BOTTOM,		//	Collision on the bottom -- || --
	COLLISION_TOP,			//	Collision on the top	-- || --
	COLLISION_FAULT,		//	Collision was miscalculated

	EXPLOSION,
	MESSAGE,
	//ENTITY_MOVING,			//	The entity is moving (velocity != 0)
	//ENTITY_STOPPED_MOVING,	//	An entity has stopped moving (velocity == 0)
};


struct Event
{
	//	Need a virtual function in base class to be able to use dynamic_cast
	virtual ~Event() {};

	const EventID eventID = BASE_EVENT;
};

struct Message : public Event
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
