#pragma once
#include "InterfaceComponent.h"
namespace GStar {
	class InterfaceComponentManager {
	public:
		static InterfaceComponentManager* Instance();
		static void Terminate();
		inline void AddInterface(InterfaceComponent* i_pinterface);
		inline void Update();
	private:
		InterfaceComponentManager() {}
		static InterfaceComponentManager* instance;
		SingleLinkedList<InterfaceComponent*> interfacelist;
	};
}