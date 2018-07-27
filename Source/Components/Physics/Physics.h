#pragma once
#include "stdafx.h"
#include "Components/Component.h"


////////////////////////////////////////////////////////////
/// Class that represents all Physics.
/// 
////////////////////////////////////////////////////////////
class Physics : public Component
{
public:
								Physics(Entity* ent);

	void						update(float dt);

	void						setVelocity(sf::Vector2f vel);
	sf::Vector2f				getVelocity() const;

private:
	sf::Vector2f				velocity;

};