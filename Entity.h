#pragma once
#include "stdafx.h"
//#include "SceneNode.h"
class Component;
#include <vector>
#include <bitset>
#include <cassert>
#include "Component.h"
#include "Health.h"

//	Abstract class
class Entity : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
public:
	typedef std::unique_ptr<Component> CompPtr;
	typedef std::unique_ptr<Entity> EntPtr;

public:
							Entity();	

	void					attachChild(EntPtr child);
	EntPtr					detachChild(const Entity& node);		//	Returns the child after detaching it

	void					update(float dt);

private:
	virtual void			updateCurrent(float dt);
	virtual void			updateChildren(float dt);

	void					draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<EntPtr>		mChildren;
	Entity*					mParent;



	////////////////////////////////////////////////////////////
	/// Component System
	///
	////////////////////////////////////////////////////////////
public:
	//	TODO: Add check if the entity already has this component
	template<typename T> T	addComponent()
	{
		CompPtr newComp(new T(this));
		components.push_back(std::move(newComp));
		return *((T*) components.back().get());
	}

	template<typename T> T& getComponent() const
	{
		T* it = NULL;
		for (int i = 0; i < components.size(); i++)
		{
			it = dynamic_cast<T*> (components[i].get());
			if (it != NULL)
				break;
		}

		assert(it != NULL);

		return *it;
	}
	template<typename T> T&	removeComponent();

private:
	std::vector<CompPtr>	components;		//	Components attached to this entity
};
