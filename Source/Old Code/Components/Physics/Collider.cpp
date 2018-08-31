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
//	//	Set the m_entity's collision box to its sprite size
//	if (m_entity->hasComponent<Sprite2D>())
//	{
//		m_entity->setPosition(300, 300);		// Remove after done testing
//		sf::Sprite entSprite = m_entity->getComponent<Sprite2D>().getSprite();
//		sf::Vector2f entPos = m_entity->getPosition();
//		sf::Vector2f entOrigin = m_entity->getOrigin();
//
//		collisionBox = entSprite.getGlobalBounds();		//	For size of collision box
//		collisionBox.left = entPos.x - entOrigin.x;		//	For position of collision box
//		collisionBox.top = entPos.y - entOrigin.y;
//
//		///				FOR TESTING
//		//std::cout << m_entity->getOrigin().x << ", " << m_entity->getOrigin().y << " | "
//		//	<< m_entity->getPosition().x << ", " << m_entity->getPosition().y << '\n';
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
//	sf::Vector2f entPos = m_entity->getPosition();
//	sf::Vector2f entOrigin = m_entity->getOrigin();
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
