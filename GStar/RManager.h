#pragma once
#include "UpdateRObject.h"
#include "RObject.h"
#include "TransformComponent.h"
namespace GStar {
	class RManager {
	public:
		static RManager* Instance();
		static void Terminate();
		RObject& CreateRenderObject(TransformComponent* gameobject);
		void Update();
		//TODO add sorting method
		//TODO add search method and remove method
	private:
		RManager(){}
		static RManager* instance;
		SingleLinkedList<RObject*> RenderObjectList;
	};
}