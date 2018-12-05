#pragma once
#include"SingleLinkedList.h"
#include"Object.h"
namespace GStar {
	class World {
	public:
		static World& Instance() {
			static World instance;
			return instance;
		}
		World():ObjectsList(SingleLinkedList<Object>()){}
		Object& AddObject() {
			ObjectsList.Push(Object());
			return *(ObjectsList.GetEnd());
		}
		void Update() {
			ObjectsList.Resetcurrent();
			while (ObjectsList.HasNext()) {
				ObjectsList.GetNext().Update();
				ObjectsList.Move();
			}
		}
	private:
		SingleLinkedList<Object> ObjectsList;
	};
}