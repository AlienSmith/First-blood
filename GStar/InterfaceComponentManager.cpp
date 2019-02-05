#include "InterfaceComponentManager.h"
namespace GStar {
	InterfaceComponentManager* InterfaceComponentManager::instance = nullptr;
	InterfaceComponentManager * GStar::InterfaceComponentManager::Instance()
	{
		if (!instance) {
			instance = new InterfaceComponentManager();
		}
		return instance;
	}
	void InterfaceComponentManager::Terminate()
	{
		if (instance) {
			delete instance;
		}
	}
	inline void InterfaceComponentManager::AddInterface(InterfaceComponent * i_pinterface)
	{
		interfacelist.Push(i_pinterface);
	}
	inline void InterfaceComponentManager::Update()
	{
		interfacelist.Resetcurrent();
		while (interfacelist.HasNext()) {
			interfacelist.GetNext()->Update();
			interfacelist.Move();
		}
	}
}
