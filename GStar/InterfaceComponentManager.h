#pragma once
#include "InterfaceComponent.h"
#include "SingleLinkedList.h"
#include "CollisionEvent.h"
#include"EventManager.h"
namespace GStar {
	class InterfaceComponentManager {
	public:
		static InterfaceComponentManager* Instance();
		static void Terminate();
		void RegisterCollisionEventReciver();
		void AddInterface(InterfaceComponent* i_pinterface);
		void Update();
	private:
		InterfaceComponentManager();
		static InterfaceComponentManager* instance;
		SingleLinkedList<InterfaceComponent*> interfacelist;
		void DistributeCollisionEvent(GStar::Event * input);
	};
}