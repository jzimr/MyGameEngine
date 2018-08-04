#include "stdafx.h"
#include "EntityFactory.h"
#include "World.h"

EntityFactory::EntityFactory(World * world)
	: mWorld{ world }
{
}

void EntityFactory::createPlayer()
{
	std::unique_ptr<Entity> newEntity(new Entity(mWorld->getUniqueID()));
	Transform* transform = newEntity.get()->addComponent<Transform>();
	Sprite2D* sprite2D = newEntity.get()->addComponent<Sprite2D>();
	Physics* physics = newEntity.get()->addComponent<Physics>();
	Collider* collider = newEntity.get()->addComponent<Collider>();
	Movement* movement = newEntity.get()->addComponent<Movement>();
	Controller* controller = newEntity.get()->addComponent<Controller>();

	//	Transform
	transform->transform.setPosition(200, 200);

	//	Sprite2D
	sprite2D->texture = mWorld->getTexture("Raptor");
	sprite2D->sprite = sf::Sprite(sprite2D->texture);
	sprite2D->sprite.setPosition(transform->transform.getPosition());

	//	Collider
	collider->colliderBox = sprite2D->sprite.getGlobalBounds();

	mWorld->addEntity(std::move(newEntity));
}

void EntityFactory::createGround()
{
	std::unique_ptr<Entity> newEntity(new Entity(mWorld->getUniqueID()));
	Transform* transform = newEntity.get()->addComponent<Transform>();
	Sprite2D* sprite2D = newEntity.get()->addComponent<Sprite2D>();
	Collider* collider = newEntity.get()->addComponent<Collider>();

	//	Transform
	transform->transform.setPosition(0, 400);

	//	Sprite2D
	sprite2D->texture = mWorld->getTexture("Ground");
	sprite2D->sprite = sf::Sprite(sprite2D->texture);
	sprite2D->sprite.setPosition(transform->transform.getPosition());

	//	Collider
	collider->colliderBox = sprite2D->sprite.getGlobalBounds();

	mWorld->addEntity(std::move(newEntity));
}
