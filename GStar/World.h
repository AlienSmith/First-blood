#pragma once
#include"SingleLinkedList.h"
#include"RObject.h"
#include"TransformComponent.h"
#include"GLError.h"
namespace GStar {
	class World {
	public:
		static World& Instance() {
			static World instance;
			return instance;
		}
		World():ObjectsList(SingleLinkedList<RObject*>()){}
		RObject* AddObject() {
			ObjectsList.Push(new RObject());
			return ObjectsList.GetEndT();
		}
		void Update() {
			WorldRoot.Resetcurrent();
			while (WorldRoot.HasNext()) {
				WorldRoot.GetNext()->WorldUpdate();
				WorldRoot.Move();
				check_gl_error();
			}
		}
		inline void AddToRoot(GStar::TransformComponent* transform) {
			WorldRoot.Push(transform); 
		}
	private:
		SingleLinkedList<RObject*> ObjectsList;
		SingleLinkedList<GStar::TransformComponent*> WorldRoot;
	};
}