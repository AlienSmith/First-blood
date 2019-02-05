#include "RManager.h"
namespace GStar {
	RManager* RManager::instance = nullptr;
	RManager * GStar::RManager::Instance()
	{
		if (!instance) {
			instance = new RManager();
		}
		return instance;
	}
	void RManager::Terminate()
	{
		if (instance) {
			delete instance;
		}
	}
	inline RObject& RManager::CreateRenderObject(TransformComponent * gameobject)
	{
		RObject* temp_Robject = new RObject(gameobject);
		RenderObjectList.Push(temp_Robject);
		return *temp_Robject;
	}
	inline void RManager::Update()
	{
		RenderObjectList.Resetcurrent();
		while (RenderObjectList.HasNext()) {
			RenderObjectList.GetNext()->Update();
			RenderObjectList.Move();
		}
	}
}