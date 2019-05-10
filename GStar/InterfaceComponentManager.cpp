#include "InterfaceComponentManager.h"
#include "ConsolePrint.h"
namespace GStar {
	InterfaceComponentManager* InterfaceComponentManager::instance = nullptr;
	InterfaceComponentManager * GStar::InterfaceComponentManager::Instance()
	{
		if (!instance) {
			instance = new InterfaceComponentManager();
		}
		return instance;
	}
	InterfaceComponentManager::InterfaceComponentManager() {
	}
	void InterfaceComponentManager::Terminate()
	{
		if (instance) {
			delete instance;
		}
	}
	void InterfaceComponentManager::RegisterCollisionEventReciver(){
	
		GStar::EventManager::Instance()->GetEventUnite("CollisionInput").Bind<InterfaceComponentManager, &InterfaceComponentManager::DistributeCollisionEvent>(this);
	}
	void InterfaceComponentManager::AddInterface(InterfaceComponent * i_pinterface)
	{
		interfacelist.Push(i_pinterface);
	}
	void InterfaceComponentManager::Update()
	{
		interfacelist.Resetcurrent();
		while (interfacelist.HasNext()) {
			interfacelist.GetNext()->Update();
			interfacelist.Move();
		}
	}
	void InterfaceComponentManager::DistributeCollisionEvent(GStar::Event * input)
	{
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Waring, "Info Sent to InterfaceManager");
	}
}
