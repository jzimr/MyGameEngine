#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
	: components{}
	, mChildren{}
	, mParent{ nullptr }
{
}

void Entity::attachChild(EntPtr child)
{
	//	Check if the child is already attached to this SceneNode
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](EntPtr& p) { return p == child; });
	assert(found == mChildren.end());

	child->mParent = this;
	mChildren.push_back(std::move(child));


}

Entity::EntPtr Entity::detachChild(const Entity& node)
{
	//	Check if the child exists within this SceneNode
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](EntPtr& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	EntPtr result = std::move(*found);		//	Move the node to this local variable
	result->mParent = nullptr;
	mChildren.erase(found);				//	Remove from list	
	return result;
}

void Entity::update(float dt)
{
	for (auto& c : components)				//	Update components
		c.get()->update(dt);
	updateCurrent(dt);

	updateChildren(dt);
}

void Entity::updateCurrent(float dt)
{
	//	Do nothing by default
	//	Think of this function as "Update()" in Unity
}

void Entity::updateChildren(float dt)
{
	for (EntPtr& child : mChildren)			//	Update children
		child->update(dt);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	//	Send calls to components
	//	DO NOT DRAW ANYTHING INSIDE THE ENTITY OR
	//	CLASSES DERIVED FROM ENTITY!
	for (auto& c : components)
		c.get()->draw(target, states);
}

void Entity::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const EntPtr& child : mChildren)
		child->draw(target, states);
}