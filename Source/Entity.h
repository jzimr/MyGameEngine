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
	//typedef std::unique_ptr<Entity> EntPtr;

public:
	Entity(int id);
	int						getID() const;
	//void					attachChild(Entity* child);
	//void					detachChild(Entity* child);

private:
	std::vector<CompPtr>	components;		//	Components attached to this entity
	std::bitset<MAX_COMPS>	compFlags;	//	So we can quickly lookup an entity's components instead of looping through the whole list

	int						uniqueID;
	//Entity*					parent;
	//Entity*					child;

	////////////////////////////////////////////////////////////
	/// Component System
	///	TODO: Implement own system that handles this
	////////////////////////////////////////////////////////////
public:

	template<class T> T&	addComponent()
	{
		T comp;
		compFlags.set(comp.type);


		CompPtr newComp(new T());
		components.push_back(std::move(newComp));

		return *dynamic_cast<T*>(components.back().get());
	}

	template<class T> T& getComponent() const
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

	template<class T> bool hasComponent() const
	{
		T comp;

		return compFlags.test(comp.type) ? true : false;
	}

	//	For recusion of hasComponents if in total only 1 argument left
	template<class T> bool hasComponents() const
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

	template<class T> void removeComponent()
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
