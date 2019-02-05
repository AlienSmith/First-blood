#pragma once
#include "UpdateRObject.h"
#include "RObject.h"
#include "TransformComponent.h"
namespace GStar {
	class RManager {
	public:
		static RManager* Instance();
		static void Terminate();
		inline RObject& CreateRenderObject(TransformComponent* gameobject);
		inline void Update();
		//TODO add sorting method
		//TODO add search method and remove method
	private:
		RManager(){}
		static RManager* instance;
		SingleLinkedList<RObject*> RenderObjectList;
	};
}