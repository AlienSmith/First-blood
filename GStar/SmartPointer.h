#pragma once
#include "ConsolePrint.h"
#include "Assert.h"
namespace GStar {
	template<class T>
	class SmartPointer {
	private:
		T* m_ptr;
		//This canbe unsigned int
		unsigned int* m_RefCount;
		inline void ReleaseReference() {
			ASSERT(m_ptr != nullptr, "try to dereference a nullptr");
			if (--(*m_RefCount) == 0) {
				delete m_RefCount;
				delete m_ptr;
			}
		}
	public:
		SmartPointer() :m_ptr(nullptr), m_RefCount(new unsigned int(0)) {}
		SmartPointer(T* Pointer) :m_ptr(Pointer), m_RefCount(new unsigned int(1)) {}
		template<class U>
		SmartPointer(const SmartPointer<U> & i_other) :
			m_ptr(i_other.m_ptr),
			m_RefCount(i_other.m_RefCount)
		{
			m_ptr != nullptr ? (*m_RefCount)++:(*m_RefCount) = 0;
		}

		inline SmartPointer& operator = (const SmartPointer<T>& i_other) {
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			m_ptr != nullptr ? (*m_RefCount)++:(*m_RefCount) = 0;
			return *this;
		}
		template<class U>
		inline SmartPointer& operator = (const SmartPointer<U> & i_other) {
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			m_ptr != nullptr ? (*m_RefCount)++:(*m_RefCount) = 0;
			return *this;
		}

		inline T* GetUnderlingReference() {
			return m_ptr;
		}
		~SmartPointer() {
			ReleaseReference();
		}
		inline T* operator ->() {
			return m_ptr;
		}
		inline T& operator *() {
			ASSERT(m_ptr != nullptr, "SmartPointer is null");
			return *m_ptr;
		}
	};
}