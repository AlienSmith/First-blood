#pragma once
#include"SingleLinkedList.h"
#include"Object.h"
#include"TransformComponent.h"
namespace GStar {
	class World {
	public:
		static World& Instance() {
			static World instance;
			return instance;
		}
		World():ObjectsList(SingleLinkedList<Object*>()){}
		Object* AddObject() {
			ObjectsList.Push(new Object());
			return ObjectsList.GetEndT();
		}
		void Update(float deltatime) {
			WorldRoot.Resetcurrent();
			while (WorldRoot.HasNext()) {
				WorldRoot.GetNext()->WorldUpdate(deltatime);
				WorldRoot.Move();
			}
		}
		inline void AddToRoot(GStar::TransformComponent* transform) {
			WorldRoot.Push(transform); 
		}
	private:
		SingleLinkedList<Object*> ObjectsList;
		SingleLinkedList<GStar::TransformComponent*> WorldRoot;
	};
}