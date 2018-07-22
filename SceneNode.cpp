#include "stdafx.h"
#include "SceneNode.h"
#include <cassert>

SceneNode::SceneNode()
	: mChildren{}
	, mParent{nullptr}
{
}

void SceneNode::attachChild(Ptr child)
{
	//	Check if the child is already attached to this SceneNode
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) { return p == child; });
	assert(found == mChildren.end());

	child->mParent = this;
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	//	Check if the child exists within this SceneNode
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	Ptr result = std::move(*found);		//	Move the node to this local variable
	result->mParent = nullptr;
	mChildren.erase(found);				//	Remove from list	
	return result;
}

void SceneNode::update(float dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(float dt)
{
	//	Do nothing by default
}

void SceneNode::updateChildren(float dt)
{
	for(Ptr& child : mChildren)
		child->update(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Apply transform of current node
	states.transform *= getTransform();

	// Draw node and children with changed transform
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const Ptr& child : mChildren)
		child->draw(target, states);
}

