#pragma once
#include "InterfaceComponent.h"
#include "SingleLinkedList.h"
namespace GStar {
	class InterfaceComponentManager {
	public:
		static InterfaceComponentManager* Instance();
		static void Terminate();
		void AddInterface(InterfaceComponent* i_pinterface);
		void Update();
	private:
		InterfaceComponentManager() {}
		static InterfaceComponentManager* instance;
		SingleLinkedList<InterfaceComponent*> interfacelist;
	};
}