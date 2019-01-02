#pragma once
#include"Event.h"
namespace GStar {
	class MouseInputEvent :public Event {
	public:
		double xpos;
		double ypos;
		MouseInputEvent(double x, double y) :xpos(x), ypos(y) {}
	};
}