#pragma once
#include "Component.h"
namespace GStar {
	class InterfaceComponent : public Component {
	public:
		const static char TypeWord() {
			return INTERFACE_WORD;
		}
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Terminate() = 0;
		InterfaceComponent() :Component(INTERFACE_WORD) {}
		virtual ~InterfaceComponent() {}
	};
}