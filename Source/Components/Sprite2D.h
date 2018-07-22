#pragma once
#include "stdafx.h"
#include "Component.h"

class Sprite2D : public Component
{
public:
						Sprite2D(Entity* ent);

	void				draw(sf::RenderTarget& target, sf::RenderStates states);
	void				addTexture(sf::Texture& tex);
	//	hasTexture
	//	getTexture
	//	getSprite

private:
	sf::Texture			texture;
	sf::Sprite			sprite;
};
