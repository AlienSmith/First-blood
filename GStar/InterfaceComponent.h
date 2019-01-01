#pragma once
#include "Component.h"
namespace GStar {
	class InterfaceComponent : public Component {
	public:
		const static char TypeWord() {
			return INTERFACE_WORD;
		}
		virtual void Initialize() = 0;
		//This will work on the updateobject instead of the Object.
		virtual void Update(float deltatime) = 0;
		virtual void Terminate() = 0;
		InterfaceComponent() :Component(INTERFACE_WORD) {}
		virtual ~InterfaceComponent() {}
	};
}