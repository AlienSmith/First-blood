#include "InterfaceComponentManager.h"
#include "ConsolePrint.h"
#include "PhysicComponent.h"
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
	void InterfaceComponentManager::Initialize()
	{
		RegisterCollisionEventReciver();
		interfacelist.Resetcurrent();
		while (interfacelist.HasNext()) {
			interfacelist.GetNext()->Initialize();
			interfacelist.Move();
		}
	}
	InterfaceComponent * InterfaceComponentManager::FindInterfacewithTransform(TransformComponent * transformcomponent)
	{
		interfacelist.Resetcurrent();
		while (interfacelist.HasNext()) {
			if (interfacelist.GetNext()->GetComponent() == transformcomponent){
				return interfacelist.GetNext();
			}
			interfacelist.Move();
		}
		return nullptr;
	}
	void InterfaceComponentManager::DistributeCollisionEvent(GStar::Event * input)
	{
		GStar::CollisionEvent* temp_event = static_cast<GStar::CollisionEvent*>(input);
		InterfaceComponent* temp = FindInterfacewithTransform(temp_event->ColliderA->getPhysic()->GetTransformComponent());
		if (temp) {
			temp->OnCollision(temp_event->ColliderB, temp_event->Point);
		}
	}
}
