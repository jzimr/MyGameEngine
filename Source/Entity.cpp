#include "stdafx.h"
#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(int id)
	: uniqueID{ id }
	, parent{ NULL }
	, children{}
	, localPosition{0, 0}
{
}

int Entity::getID() const
{
	return uniqueID;
}

////////////////////////////////////////////////////////////
/// Parent-child relationship
///
////////////////////////////////////////////////////////////

//	Necessary with "parent", as this will send the shared_ptr over here.
//	TODO: CHANGE!
void Entity::attachChild(Entity* child, sf::Vector2f offset)
{
	children.push_back(child);
	child->parent = this;

	if (offset == sf::Vector2f(0, 0))
		child->localPosition = child->getPosition() - transform.getPosition();
	else
		child->localPosition = offset;
	child->setPosition(getPosition());
}

Entity* Entity::detachChild(Entity* child)
{
	Entity* found;
	auto it = std::find_if(children.begin(), children.end(), [&](Entity* &p) { if (p == child) { found = p; return true; } });

	assert(it != children.end());
	children.erase(it);

	child->parent = NULL;

	return found;
}

bool Entity::hasChildren() const
{
	return !children.empty();
}

std::vector<Entity*> Entity::getChildren() const
{
	return children;
}

bool Entity::hasParent() const
{
	return parent != NULL ? true : false;
}

Entity* Entity::getParent() const
{
	return parent;
}

//	Check the upper hierachy with recursion
bool Entity::isChildOf(const Entity* entity) const
{
	if (parent)
	{
		if (parent == entity)
			return true;

		if (parent->isChildOf(entity))
			return true;
	}

	return false;
}

bool Entity::isParentOf(const Entity* entity) const
{
	for (const auto& child : children)
	{
		//	Some more recursion :D
		if (child == entity)
			return true;

		if (child->isParentOf(entity))
			return true;
	}
	return false;		
}

bool Entity::isRelatedWith(const Entity* entity) const
{
	if (/*std::shared_ptr<Entity>(this) == entity ||*/
		isChildOf(entity) || isParentOf(entity))
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////////
/// Transform manipulation
///
////////////////////////////////////////////////////////////

void Entity::setPosition(float x, float y)
{
	//std::cout << localPosition.x << " " << localPosition.y << '\n';

	///	NEW
	transform.setPosition(sf::Vector2f(x + localPosition.x, y + localPosition.y));
	for (auto& child : children)
		child->setPosition(transform.getPosition().x, transform.getPosition().y);
}

void Entity::setPosition(const sf::Vector2f position)
{

	///	NEW
	transform.setPosition(position + localPosition);
	for (auto& child : children)
		child->setPosition(transform.getPosition());
}

const sf::Vector2f Entity::getPosition() const
{
	return transform.getPosition();
}

void Entity::move(float offsetX, float offsetY)
{
	transform.move(offsetX, offsetY);

	for (auto& child : children)
	{
		child->move(offsetX, offsetY);
	}
}

void Entity::move(const sf::Vector2f & offset)
{
	transform.move(offset);

	for (auto& child : children)
	{
		child->move(offset);
	}
}

void Entity::setLocalPosition(float x, float y)
{
	localPosition = sf::Vector2f(x, y);
	setPosition(parent->getPosition());
}

void Entity::setLocalPosition(const sf::Vector2f position)
{
	localPosition = position;
	setPosition(parent->getPosition());
}

sf::Vector2f Entity::getLocalPosition() const
{
	return localPosition;
}





