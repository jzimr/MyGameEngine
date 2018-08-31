#include "stdafx.h"
#include "Entity.h"

Entity::Entity(int id)
	: uniqueID{ id }
	, parent{ NULL }
	, children{}
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

void Entity::attachChild(EntPtr child)
{
	children.push_back(child);
}

Entity::EntPtr Entity::detachChild(EntPtr child)
{
	return nullptr;
}

bool Entity::hasChildren() const
{
	return !children.empty();
}

bool Entity::hasParent() const
{
	return parent != NULL ? true : false;
}

Entity::EntPtr Entity::getParent()
{
	return parent;
}

//	Check the whole hierarchy with recursion
bool Entity::isChildOf(const EntPtr entity) const
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






void Entity::setPosition(float x, float y)
{
	sf::Vector2f distToNewPos = sf::Vector2f(x, y) - getPosition();
	transform.setPosition(x, y);

	for (auto& child : children)
	{
		child->move(distToNewPos);
	}

}

void Entity::setPosition(const sf::Vector2f position)
{
	sf::Vector2f distToNewPos = position - getPosition();
	transform.setPosition(position);

	for (auto& child : children)
	{
		child->move(distToNewPos);
	}
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





