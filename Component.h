#pragma once
#include "stdafx.h"
class Entity;
#include <cassert>

//	This is an abstract class
class Component
{
public:
								Component(Entity* ent);

	//virtual void				init();

	virtual void				update(float dt);
	virtual void				draw(sf::RenderTarget& target, sf::RenderStates states);
	Entity* entity;		//	A component can have one and only one entity

//protected:
};