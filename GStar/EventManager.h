#pragma once
#include "Delegate.h"
#include "SingleLinkedList.h"
namespace GStar {
	class EventManager {
	public:
		static EventManager* Instance() {
			if (!instance) {
				instance = new EventManager();
			}
			return instance;
		}
	private:
		EventManager() {}
		static EventManager* instance;
	};
}