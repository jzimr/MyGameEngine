#pragma once
#include "stdafx.h"
#include "Component.h"

class Health : public Component
{
public:
								Health(Entity* ent);
	int							getHealth() const;

	//	Can use Sprite.cpp component to draw or sf::Sprite (Your choice)

	//void				update(float dt);
	//void				draw(sf::RenderTarget& target, sf::RenderStates states);

private:
	int health;
};
