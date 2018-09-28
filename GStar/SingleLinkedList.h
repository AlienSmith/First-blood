#pragma once
#include <type_traits>
namespace GStar {
	template <class T>
	static void deleteIfPointer(const T& t)
	{
		std::cout << "not pointer" << std::endl;
	}

	template <class T>
	static void deleteIfPointer(T* t)
		//                           ^
	{
		std::cout << "is pointer" << std::endl;
		delete t;
	}
	template<class T>
	class SingleLinkedList;
	template<class T>
	class SingleLinkedListNode
	{
	public:
		SingleLinkedListNode(T data);
		SingleLinkedListNode();
		~SingleLinkedListNode();
		void Delete(SingleLinkedListNode<T>* previous, SingleLinkedList<T>* end);
		SingleLinkedListNode<T>* GetNext();
		void SetNext(SingleLinkedListNode<T>* next);
		T GetData();
	private:
		SingleLinkedListNode<T>* m_Next;
		T m_data;
	};
	//the list end will nullptr
	template<class T>
	class SingleLinkedList
	{
	public:
		SingleLinkedListNode<T> * GetHead();
		void Reset();
		void Push(T data);
		SingleLinkedList();
		~SingleLinkedList();
	private:
		SingleLinkedListNode<T>* m_pHead;
		SingleLinkedListNode<T>* m_end;
	};

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
		SingleLinkedListNode<T>* temp = m_pHead;
		SingleLinkedListNode<T>* temp1 = m_pHead;
		while (temp != nullptr)
		{
			temp1 = temp->GetNext();
			delete temp;
			temp = temp1;
		}
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
		deleteIfPointer(this->GetData());
	}

	template<class T>
	inline void SingleLinkedListNode<T>::Delete(SingleLinkedListNode<T>* previous, SingleLinkedList<T>* List)
	{
		SingleLinkedListNode<T>* temp = previous->m_Next;
		if (temp->GetNext() == nullptr) {
			List->Reset();
		}
		previous->m_Next = this->m_Next;
		delete temp;
	}
	
}

