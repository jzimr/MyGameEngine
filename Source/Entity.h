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
	template<typename T> T&	addComponent()
	{
		CompPtr newComp(new T()/*(this)*/);
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

	template<typename T> bool hasComponent() const
	{
		T* it = NULL;
		for (int i = 0; i < components.size(); i++)
		{
			it = dynamic_cast<T*> (components[i].get());
			if (it != NULL)
				return true;
		}
		return false;
	}

	template<typename T> T&	removeComponent();		//	TODO

private:
	std::vector<CompPtr>	components;		//	Components attached to this entity
};
