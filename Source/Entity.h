#pragma once
#include "stdafx.h"
//#include "SceneNode.h"
//class Component;
#include <vector>
#include <bitset>
#include <cassert>
#include "Component.h"

class Entity : public sf::NonCopyable
{
public:
	typedef std::unique_ptr<BaseComponent> CompPtr;
	//typedef std::unique_ptr<Entity> EntPtr;

public:
	Entity(int id);
	int						getID() const;

private:
	int						uniqueID;

	////////////////////////////////////////////////////////////
	/// Component System
	///	TODO: Implement own system that handles this
	////////////////////////////////////////////////////////////
public:
	template<typename T> T*	addComponent()
	{
		CompPtr newComp(new T());
		components.push_back(std::move(newComp));

		return dynamic_cast<T*>(components.back().get());
	}

	template<typename T> T& getComponent() const
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

	template<typename T> bool hasComponent() const
	{
		T* it = NULL;
		for (size_t i = 0; i < components.size(); i++)
		{
			it = dynamic_cast<T*> (components[i].get());
			if (it != NULL)
				return true;
		}
		return false;
	}

	template<typename T> T&	removeComponent();		//	TODO (Also disable possibility of removing transform component)

private:
	std::vector<CompPtr>	components;		//	Components attached to this entity
};
