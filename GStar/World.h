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
		World(){}
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
		SingleLinkedList<GStar::TransformComponent*> WorldRoot;
	};
}