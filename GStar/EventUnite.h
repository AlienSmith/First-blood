#pragma once
#include "Delegate.h"
#include "SingleLinkedList.h"
#include "MyString.h"
namespace GStar {
	class EventUnite {
	public:
		EventUnite* Create(MyString& name) {
			EventUnite(MyString::hash_str(name.GetString()));
		}
		//Bind a free function
		template<void(*Function)(Event*)>
		void Bind(void) {
			Delegate temp;
			temp.m_stub.first = nullptr;
			temp.m_stub.second = &FunctionStub<Function>;
			my_functionlist.Push(temp);
		}
		//Bind a class method
		template <class C, void(C::*Function)(Event*)>
		void Bind(C* instance) {
			Delegate temp;
			temp.m_stub.first = instance;
			temp.m_stub.second = &ClassMethodStub<C, Function>;
			my_functionlist.Push(temp);
		}
		//Invokes the delegate
		void Invoke(Event* ARG0) {
			my_functionlist.Resetcurrent();
			while (my_functionlist.HasNext()) {
				Delegate temp = my_functionlist.GetNext();
				temp.m_stub.second(temp.m_stub.first, ARG0);
				my_functionlist.Move();
			}
			//use new to for an event, delete it when calling all functions.
			delete ARG0;
			return;
		}
	private:
		//Pointer to function do not need to be deleted?
		EventUnite(size_t id) :my_id(id) {}
		SingleLinkedList<Delegate> my_functionlist;
		size_t my_id;
	};
}