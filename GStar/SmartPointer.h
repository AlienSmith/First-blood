#pragma once
#include "ConsolePrint.h"
#include "Assert.h"
namespace GStar {
	template<class T>
	class SmartPointer {
	private:
		mutable T* m_ptr;
		//This canbe unsigned int
		mutable unsigned int* m_RefCount;
		mutable unsigned int* m_ConstRefCount;
		inline void ReleaseReference() {
			ASSERT(m_ptr != nullptr, "try to release a nullptr");
			if (--(*m_RefCount) == 0) {
				delete m_RefCount;
				delete m_ptr;
			}
		}
		inline void ReleaseReference() const {
			if (--(*m_ConstRefCount) == 0) {
				if (!m_ptr) {
					delete m_WRefCount;
				}
			}
		}
	public:
		const SmartPointer<T> ObtainConstPointer() const{
			m_ConstRefCount++;
			return *this;
		}
		SmartPointer<T> ObtainPointer() const{
			m_RefCount++;
			return const_cast<SmartPointer<T>>* this;
		}
		SmartPointer() :m_ptr(nullptr), m_RefCount(new unsigned int(0)) {}
		SmartPointer(T* Pointer) :m_ptr(Pointer), m_RefCount(new unsigned int(1)) {}
		template<class U>
		SmartPointer(const SmartPointer<U> & i_other) :
			m_ptr(i_other.m_ptr),
			m_RefCount(i_other.m_RefCount)
		{
			m_ptr != nullptr ? (*m_RefCount)++ : (*m_RefCount) = 0;
		}
		inline const SmartPointer& operator = (const SmartPointer<T>& i_other) const {
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			if (m_ptr) {
				m_ptr = i_other.m_ptr;
				m_RefCount = i_other.m_RefCount;
				m_ConstRefCount = i_other.m_ConstRefCount;
				(*m_ConstRefCount)++;
				return *this;
			}
		}
		inline SmartPointer& operator = (const SmartPointer<T>& i_other) {
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			m_ptr != nullptr ? (*m_RefCount)++ : (*m_RefCount) = 0;
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
			m_ptr != nullptr ? (*m_RefCount)++ : (*m_RefCount) = 0;
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
		inline bool operator == (const SmartPointer<T> & i_other) const {
			return m_ptr == i_other.m_ptr;
		}
		template<class U>
		inline bool operator == (const SmartPointer<U> & i_other) const {
			return m_ptr == i_other.m_ptr;
		}
		inline bool operator ==(T* i_other_ptr) const {
			return m_ptr == i_other_ptr;
		}
		template<class U>
		inline bool operator ==(U* i_other_ptr) const {
			return m_ptr == i_other_ptr;
		}
		inline bool operator ==(std::nullptr_t nullp) const {
			return m_ptr == nullp;
		}

		inline bool operator != (const SmartPointer<T> & i_other) const {
			return m_ptr == i_other.m_ptr;
		}
		template<class U>
		inline bool operator != (const SmartPointer<U> & i_other) const {
			return m_ptr == i_other.m_ptr;
		}
		inline bool operator !=(T* i_other_ptr) const {
			return m_ptr == i_other_ptr;
		}
		template<class U>
		inline bool operator !=(U* i_other_ptr) const {
			return m_ptr == i_other_ptr;
		}
		inline bool operator !=(std::nullptr_t nullp) const {
			return m_ptr == nullp;
		}
		inline bool operator!() const{
			return !m_ptr;
		}
		inline operator bool() const {
			return m_ptr;
		}
	};
}