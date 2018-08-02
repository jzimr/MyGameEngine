#include "stdafx.h"
//#include "Collider.h"
//#include "Entity.h"
//
//Collider::Collider(Entity* ent)
//	: Component(ent)
//	, collisionBox{}
//{
//	init();
//}
//
//void Collider::init()
//{
//	//	Set the entity's collision box to its sprite size
//	if (entity->hasComponent<Sprite2D>())
//	{
//		entity->setPosition(300, 300);		// Remove after done testing
//		sf::Sprite entSprite = entity->getComponent<Sprite2D>().getSprite();
//		sf::Vector2f entPos = entity->getPosition();
//		sf::Vector2f entOrigin = entity->getOrigin();
//
//		collisionBox = entSprite.getGlobalBounds();		//	For size of collision box
//		collisionBox.left = entPos.x - entOrigin.x;		//	For position of collision box
//		collisionBox.top = entPos.y - entOrigin.y;
//
//		///				FOR TESTING
//		//std::cout << entity->getOrigin().x << ", " << entity->getOrigin().y << " | "
//		//	<< entity->getPosition().x << ", " << entity->getPosition().y << '\n';
//		//std::cout << collisionBox.width << ", " << collisionBox.height << " | "
//		//	<< collisionBox.left << ", " << collisionBox.top << '\n';
//	}
//	else
//		collisionBox = sf::FloatRect(0, 0, 10, 10);		//	Default box 
//}
//
//void Collider::update(float dt)
//{
//	//	Update the position of the box
//	sf::Vector2f entPos = entity->getPosition();
//	sf::Vector2f entOrigin = entity->getOrigin();
//
//	collisionBox.left = entPos.x - entOrigin.x;		//	For position of collision box
//	collisionBox.top = entPos.y - entOrigin.y;
//}
//
//bool Collider::hasHitSomething()
//{
//	float left = collisionBox.left;
//	float right = collisionBox.left + collisionBox.width;
//	float top = collisionBox.top;
//	float bottom = collisionBox.top + collisionBox.height;
//
//}
