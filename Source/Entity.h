#pragma once
#include "stdafx.h"
#include <vector>
#include <bitset>
#include <cassert>
#include "Component.h"

using namespace Settings;

class Entity : public sf::NonCopyable
{
public:
	typedef std::unique_ptr<BaseComponent> CompPtr;

public:
	Entity(int id);
	int						getID() const;

	////////////////////////////////////////////////////////////
	/// Parent-child relationship
	///
	///	TODO: Move into own component
	////////////////////////////////////////////////////////////
	void						attachChild(Entity* child, sf::Vector2f offset = sf::Vector2f(0, 0));
	Entity*						detachChild(Entity* child);
	bool						hasParent() const;
	Entity*						getParent() const;
	bool						hasChildren() const;
	std::vector<Entity*>		getChildren() const;
	bool						isChildOf(const Entity* entity) const;		//	This entity is child of param
	bool						isParentOf(const Entity* entity) const;		//	This entity is parent of param
	bool						isRelatedWith(const Entity* entity) const;


	//	Functions of sf::Transformable
	void						setPosition(float x, float y);
	void						setPosition(const sf::Vector2f position);
	const sf::Vector2f			getPosition() const;
	void						move(float offsetX, float offsetY);
	void						move(const sf::Vector2f &offset);

	//	Custom functions for transform manipulation
	void						setLocalPosition(float x, float y);
	void						setLocalPosition(const sf::Vector2f position);
	sf::Vector2f				getLocalPosition() const;



private:
	std::vector<CompPtr>		components;	//	Components attached to this m_entity
	std::bitset<MAX_COMPS>		compFlags;	//	So we can quickly lookup an m_entity's components instead of looping through the whole list

	sf::Transformable			transform;

	int							uniqueID;

	Entity*						parent;
	std::vector<Entity*>		children;
	sf::Vector2f				localPosition;			//	Position relative to parent		



	////////////////////////////////////////////////////////////
	/// Component System
	///
	////////////////////////////////////////////////////////////
public:

	template<class T> T&		addComponent()
	{
		T comp;
		compFlags.set(comp.type);


		CompPtr newComp(new T());
		components.push_back(std::move(newComp));

		return *dynamic_cast<T*>(components.back().get());
	}

	template<class T> T&		getComponent() const
	{
		T* it = NULL;

		for (size_t i = 0; i < components.size(); i++)
		{
			it = dynamic_cast<T*> (components[i].get());
			if (it != NULL)
				break;
		}

		assert(it != NULL);

		return *it;
	}

	template<class T> bool		hasComponent() const
	{
		T comp;

		return compFlags.test(comp.type) ? true : false;
	}

	//	For recusion of hasComponents() if in total only 1 argument left
	template<class T> bool		hasComponents() const
	{
		return hasComponent<T>();
	}

	template<class T, class S, class... Params> bool hasComponents() const
	{
		if (hasComponent<T>())
		{
			return (true && this->hasComponents<S, Params...>());
		}

		return false;
	}

	template<class T> void		removeComponent()
	{
		T comp;
		T* it = NULL;

		for (size_t i = 0; i < components.size(); i++)
		{
			it = dynamic_cast<T*> (components[i].get());
			if (it != NULL)
			{
				components.erase(components.begin() + i);
				compFlags.reset(comp.type);
			}
		}
	}
};
