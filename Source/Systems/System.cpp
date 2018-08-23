#include "stdafx.h"
#include "System.h"

System::System()
{
	
}

void System::configure(EventManager& events)
{
}

void System::begin()
{
}

void System::update(float dt, EventManager& events)
{
}

void System::end()
{
}

void System::onNotify(int entity, std::function<void()> command)
{
	//	Execute task in derived class
}

void System::onNotify(int entity, EventID event)
{
	//	Switch through Events in derived class
}

void System::addObserver(System * observer)
{
	//	Check if the observer is already subscribed to this subject
	for (const auto& listObserver : observers)
		if (listObserver == observer)
			return;

	//	If not, we can add it
	observers.push_back(observer);
}

void System::removeObserver(System * observer)
{
	auto it = std::find(observers.begin(), observers.end(), observer);

	if (it != observers.end())		//	If we have item "observer" in vector
		observers.erase(it);
}

void System::notify(int entity, std::function<void()> command)
{
	for (auto& observer : observers)
		observer->onNotify(entity, command);
}

void System::notify(int entity, EventID event)
{
	//	Notify all observers
	for (auto& observer : observers)
		observer->onNotify(entity, event);
}
