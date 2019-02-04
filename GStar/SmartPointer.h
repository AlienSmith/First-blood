#pragma once
#include "ConsolePrint.h"
#include "Assert.h"
namespace GStar {
	template<class T>
	class SmartPointer {
	public:
		SmartPointer() :m_ptr(nullptr), m_RefCount(0) {}
		SmartPointer(T* Pointer) :m_ptr(Pointer), m_RefCount(1) {}
		template<class U>
		SmartPointer(const SmartPointer<U> & i_other):
			m_ptr(i_other.m_ptr),
			m_RefCount(i_other.m_RefCount) {
			m_ptr != nullptr? ((*m_RefCount)++:(*m_RefCount) = 0);
		}
		template<class U>
		inline SmartPointer& operator = (const SmartPointer<U> & i_other) {
			ASSERT(m_ptr != i_other.m_ptr, "Self Assignment");
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			m_ptr != nullptr ? ((*m_RefCount)++:(*m_RefCount) = 0);
			return *this;
		}
		~SmartPointer{
			ReleaseReference();
		}
		inline T* operator ->() {
			return m_ptr;
		}
		inline T& operator *() {
			ASSERT(m_ptr != nullptr, "SmartPointer is null");
			return *m_ptr;
		}
		inline bool operator !() {
			return !m_ptr;
		}
		inline bool operator == (const SmartPointer & i_other) {
			return m_ptr == i_other.m_ptr;
		}
		inline bool operator ==(const T* const i_other_ptr) {
			return m_ptr == i_other_ptr;
		}
		inline bool operator != (const SmartPointer & i_other) {
			return m_ptr != i_other.m_ptr;
		}
		inline bool operator !=(const T* const i_other_ptr) {
			return m_ptr != i_other_ptr;
		}
	private:
		inline void ReleaseReference() {
			ASSERT(m_ptr != nullptr, "try to dereference a nullptr");
			if (--(*m_RefCount) == 0) {
				delete m_RefCount;
				delete m_ptr;
			}
		}
		T* m_ptr;
		//This canbe unsigned int
		long* m_RefCount;
	};
}