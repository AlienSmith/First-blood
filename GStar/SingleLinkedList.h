#pragma once
#include <iostream>
#include <type_traits>
#include <crtdbg.h>
#include "Debug.h"
namespace GStar {
	/*template <class T>
	static void deleteIfPointer(const T& t)
	{

		std::cout << "not pointer" << std::endl;

	}

	template <class T>
	static void deleteIfPointer(T* t){
		if (t != nullptr) {
			delete t;
		}
	}*/
	template<class T>
	class SingleLinkedList;
	template<class T>
	class SingleLinkedListNode
	{
	public:
		SingleLinkedListNode(T data);
		SingleLinkedListNode();
		~SingleLinkedListNode();
		//This function will try to delete the data each nodes holds
		void Delete(SingleLinkedListNode<T>* previous, SingleLinkedList<T>* end);
		SingleLinkedListNode<T>* GetNext();
		void SetNext(SingleLinkedListNode<T>* next);
		T GetData();
	private:
		SingleLinkedListNode<T>* m_Next;
		T m_data;
	};
	/**Objects stored as Pointer will be deleted automatically when the list are deleted 
	 *the list end will nullptr*/
	template<class T>
	class SingleLinkedList
	{
	public:
		inline void DeleteContent();
		SingleLinkedListNode<T> * GetHead();
		void Reset();
		void Push(T data);
		
		inline T GetEndT() {
			return this->m_end->GetData();
		}
		SingleLinkedList();
		~SingleLinkedList();
		inline void Resetcurrent() {
			m_current = m_pHead;
		}
		inline T GetNext() {
			if (m_current->GetNext()) {
				return m_current->GetNext()->GetData();
			}
			return m_pHead->GetNext()->GetData();
		}
		inline SingleLinkedListNode<T>* GetNextNode() {
			return m_current->GetNext();
		}
		inline bool HasNext() {
			if (m_current->GetNext() != nullptr) {
				return true;
			}
			return false;
		}
		inline void Move() {
			if (m_current->GetNext()) {
				m_current = m_current->GetNext();
			}
		}
		//This function will only remove the node from the list, if the data stored in it is pointer, the pointer will not get deleted.
		inline void DeleteNext() {
			m_current->GetNext()->Delete(m_current, this);
		}
	private:
		SingleLinkedListNode<T>* m_pHead;
		SingleLinkedListNode<T>* m_end;
		SingleLinkedListNode<T>* m_current;
	};
	//This function will delete the pointer stored in the list, make sure the stored data is pointers
	template<class T>
	inline void SingleLinkedList<T>::DeleteContent()
	{
		SingleLinkedListNode<T>* temp = m_pHead;
		SingleLinkedListNode<T>* temp1;
		while (temp != nullptr)
		{
			temp1 = temp->GetNext();
			T data = temp->GetData();
			delete data;
			temp = temp1;
		}
	}

	// this function will return a nullptr if nothing has been added to the list
	template<class T>
	inline SingleLinkedListNode<T>* SingleLinkedList<T>::GetHead()
	{
		return m_pHead;
	}

	template<class T>
	inline void SingleLinkedList<T>::Reset()
	{
		this->m_end = this->m_pHead;
	}

	template<class T>
	inline void SingleLinkedList<T>::Push(T data)
	{
		SingleLinkedListNode<T>* temp = new SingleLinkedListNode<T>(data);
		m_end->SetNext(temp);
		temp->SetNext(nullptr);
		m_end = temp;
	}

	template<class T>
	inline SingleLinkedList<T>::SingleLinkedList()
	{
		this->m_pHead = new SingleLinkedListNode<T>();
		m_pHead->SetNext(nullptr);
		this->m_end = this->m_pHead;
	}

	template<class T>
	inline SingleLinkedList<T>::~SingleLinkedList()
	{
		/*SingleLinkedListNode<T>* temp = m_pHead;
		SingleLinkedListNode<T>* temp1;
		while (temp != nullptr)
		{
			temp1 = temp->GetNext();
			delete temp;
			temp = temp1;
		}*/
	}

	template<class T>
	inline T  SingleLinkedListNode<T>::GetData()
	{
		return this->m_data;
	}
	template<class T>
	inline SingleLinkedListNode<T> * SingleLinkedListNode<T>::GetNext()
	{
		return this->m_Next;
	}
	template<class T>
	inline void SingleLinkedListNode<T>::SetNext(SingleLinkedListNode<T>* next)
	{
		this->m_Next = next;
	}
	template<class T>
	inline SingleLinkedListNode<T>::SingleLinkedListNode(T data)
	{
		m_data = data;
	}
	template<class T>
	inline SingleLinkedListNode<T>::SingleLinkedListNode()
	{
	}
	template<class T>
	inline SingleLinkedListNode<T>::~SingleLinkedListNode()
	{
		//deleteIfPointer(this->GetData());
	}
	//This function will only delete the node not the info stored 
	template<class T>
	inline void SingleLinkedListNode<T>::Delete(SingleLinkedListNode<T>* previous, SingleLinkedList<T>* List)
	{
		SingleLinkedListNode<T>* temp = previous->m_Next;
		if (temp->GetNext() == nullptr) {
			List->Reset();
		}
		previous->m_Next = this->m_Next;
		delete temp;
		temp = nullptr;
	}	
}

