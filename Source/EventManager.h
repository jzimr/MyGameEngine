#pragma once
#include <map>
#include <cassert>
#include <functional>
#include "Events.h"

class EventManager
{
public:
	typedef std::function<void(Event *)> EventFuncPtr;

public:
	EventManager();

	//template<class Derived>
	//struct Receiver
	//{
	//	~Receiver() {}
	//};

	///
	///	
	//	IF ALL FAILS, JUST DYNAMIC CAST THE OBJECT AS EVENT* TO THE MAP AND DYNAMIC CAST IT BACK
	//	ON EMIT, WITH THE ID OF THE EVENT GIVEN

	//	Event to subscribe to and Receiver (function) that will be used for receiving events
	template<typename Ev, typename Receiver, typename FuncPtr>		
	void subscribe(Receiver *receiver, FuncPtr handler)
	{
		Ev event;		//	Create dummy object
		void(Receiver::*r)(Event*) = (void (Receiver::*)(Event*)) (handler);	
		//EventFuncPtr recFunc = &Receiver::receive;
		//receive(Message);
		//std::vector<EventFuncPtr> vec;

		//vec.push_back(std::bind(r, receiver, std::placeholders::_1));
		EventFuncPtr ptr = std::bind(r, receiver, std::placeholders::_1);

		auto aiaiai = std::make_pair(event.eventID, ptr);

		m_receivers.insert(aiaiai);
	}

	template<class E>				//	Maybe remove and replace parameter with simple "Event&"?
	void emit(E &event)
	{
		///	Find the event in our multimap
		EventID found = BASE_EVENT;		
		std::multimap<EventID, EventFuncPtr>::iterator it;

		for (it = m_receivers.begin(); it != m_receivers.end(); it++)
		{
			std::cout << event.eventID << " " << it->first << "\n";
			if (event.eventID == it->first)
			{
				found = event.eventID;
				break;
			}
		}

		//for (size_t i = 0; i < m_receivers.size(); i++)
		//{
		//	found = *dynamic_cast<Event*>(m_receivers[i]);

		//	if (found != NULL)		//	We have found our event
		//		break;
		//}

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
