#include "stdafx.h"
//#include "EntityFactory.h"
//#include "World.h"
//
//std::unique_ptr<Entity> EntFactory::Player::create(sf::Texture texture)
//{
//	std::unique_ptr<Entity> player(new Entity());
//
//	player.get()->addComponent<Sprite2D>();
//	player.get()->getComponent<Sprite2D>().addTexture(texture);
//
//	//	Set origin to the middle of the sprite
//	sf::FloatRect bounds = player.get()->getComponent<Sprite2D>().getSprite().getLocalBounds();
//	player.get()->setOrigin(bounds.width / 2, bounds.height / 2);
//
//	////////////////////////////////////////////////////////////
//	/// TODO: ADD CORRECT ORDER OF PHYSICS EXECUTIONS OF UPDATE()
//	///
//	////////////////////////////////////////////////////////////
//
//	player.get()->addComponent<Physics>();
//	player.get()->addComponent<Controller>();
//	player.get()->addComponent<Collider>();
//
//	return std::move(player);
//}