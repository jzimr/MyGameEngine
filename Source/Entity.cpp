#include "stdafx.h"
#include "Entity.h"
#include "EntityManager.h"

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

//	Necessary with "parent", as this will send the shared_ptr over here.
//	TODO: CHANGE!
void Entity::attachChild(EntPtr child, EntPtr parent)		
{
	children.push_back(child);
	child->parent = parent;
}

/*Entity::EntPtr*/void Entity::detachChild(EntPtr child)
{
	std::shared_ptr<Entity> found;
	auto it = std::find_if(children.begin(), children.end(), [&](std::shared_ptr<Entity> &p) { if (p == child) { found = p; return true; } });

	std::cout << found->parent.use_count();

	assert(it != children.end());
	children.erase(it);

	child->parent = NULL;
	
	//return found;
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

//	Check the upper hierachy with recursion
bool Entity::isChildOf(const EntPtr entity)
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

bool Entity::isParentOf(const EntPtr entity)
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

bool Entity::isRelatedWith(const EntPtr entity)
{
	if (/*std::shared_ptr<Entity>(this) == entity ||*/
		isChildOf(entity) || isParentOf(entity))
		return true;
	else
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





