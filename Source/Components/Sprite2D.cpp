#include "stdafx.h"
#include "Sprite2D.h"
#include "Entity.h"

Sprite2D::Sprite2D(Entity* ent)
	: Component(ent)
	, texture{}
	, sprite{}
{

}

void Sprite2D::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(sprite, states);
}

void Sprite2D::addTexture(sf::Texture& tex)
{
	texture = tex;
	sprite.setTexture(texture);
}