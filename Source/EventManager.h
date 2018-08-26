#pragma once
#include <map>
#include <cassert>
#include <functional>
#include "Constants.h"
#include "Events.h"

class EventManager
{
public:
	typedef std::function<void(Event *)> EventFuncPtr;

public:
	EventManager();

	//	Event to subscribe to and Receiver (function) that will be used for receiving events
	template<typename Ev, typename Receiver, typename FuncPtr>
	void subscribe(Receiver *receiver, FuncPtr handler)
	{
		Ev event;		//	Create dummy object
		void(Receiver::*r)(Event*) = (void (Receiver::*)(Event*)) (handler);

		auto subscription = std::make_pair(event.eventID, std::bind(r, receiver, std::placeholders::_1));

		m_receivers.insert(subscription);
	}

	template<class E>				//	Maybe remove and replace parameter with simple "Event&"?
	void emit(E &event)
	{
		///	Find the event in our multimap
		EventID found = BASE_EVENT;
		std::multimap<EventID, EventFuncPtr>::iterator it;

		for (it = m_receivers.begin(); it != m_receivers.end(); it++)
		{
			if (event.eventID == it->first)
			{
				found = event.eventID;
				break;
			}
		}

		//	VVVVVVVVV	Means you probably have not applied the EventID to the derived Event struct
		assert(found != BASE_EVENT);				//	Throw error if not found

		///	Find all systems that are subscribed to that event
		auto receiversElems = m_receivers.equal_range(found);

		for (auto it2 = receiversElems.first; it2 != receiversElems.second; it2++)
		{
			EventFuncPtr receiver = (it2->second);

			receiver(&event);								//	Call the function of subscribed system with the wished element
		}
	}

private:
	std::multimap<EventID, EventFuncPtr> m_receivers;		//	Or "obsers" (Systems subscribed to events)

};
