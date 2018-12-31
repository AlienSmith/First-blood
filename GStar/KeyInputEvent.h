#pragma once
#include"Event.h"
namespace GStar {
	class KeyInputEvent : public Event {
	public:
		int SingleKey;
		int action;
		KeyInputEvent(int key, int inputaction) :SingleKey(key), action(inputaction) {}
	};
}