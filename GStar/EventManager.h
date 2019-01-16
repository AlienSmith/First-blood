#pragma once
#include "EventUnite.h"
namespace GStar {
	class EventManager {
		//All the EventUnites die with the manager;
	public:
		static EventManager* Instance() {
			if (!instance) {
				instance = new EventManager();
			}
			return instance;
		}
		EventUnite& RegisterEvent(const MyString& string) {
			EventUnite& temp = *EventUnite::Create(string);
			my_eventlist.Push(&temp);
			return temp;
		}
		EventUnite& GetEventUnite(const MyString& string) {
			size_t tempid = MyString::hash_str(string.GetString());
			my_eventlist.Resetcurrent();
			while (my_eventlist.HasNext()) {
				if (my_eventlist.GetNext()->Getid() == tempid) {
					return *my_eventlist.GetNext();
				}
				my_eventlist.Move();
			}
			DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Error, "Try to access eventunit %s has not been registered",string.GetString());
		}
		~EventManager() {
			my_eventlist.DeleteContent();
		}
		static void Terminate() {
			if (instance) {
				delete instance;
			}
		}
	private:
		EventManager() {}
		EventManager(const EventManager& other) = delete;
		EventManager& operator = (const EventManager& other) = delete;
		static EventManager* instance;
		SingleLinkedList<EventUnite*> my_eventlist;
	};
}