#pragma once
#include "ConsolePrint.h"
#include "Assert.h"
#include <stdint.h>
namespace GStar {
	typedef uint64_t	ref_counter_t;
	template<class T>
	class ObserverPointer;
	template<class T>
	class SmartPointer {
		template<class U>
		friend class ObserverPointer;
		template<class U>
		friend class SmartPointer;
	private:
		T* m_ptr;
		//This canbe unsigned int
		ref_counter_t* m_RefCount;
		ref_counter_t* m_observercount;
		inline void ReleaseReference() {
			ASSERT(m_ptr != nullptr, "try to release a nullptr");
			if (--(*m_RefCount) == 0) {
				delete m_RefCount;
				if (m_ptr) {
					delete m_ptr;
				}
				if ((*m_observercount) == 0) {
					delete m_observercount;
				}
			}
		}
	public: 
		inline T* GetUnderlingReference() {
			return m_ptr;
		}
		SmartPointer() :m_ptr(nullptr), m_RefCount(new ref_counter_t(1)),m_observercount(new ref_counter_t(0)) {}
		SmartPointer(T* Pointer) :m_ptr(Pointer), m_RefCount(new ref_counter_t(1)),m_observercount(new ref_counter_t(0)) {}
		SmartPointer(const SmartPointer& i_other) :
			m_ptr(i_other.m_ptr),
			m_RefCount(i_other.m_RefCount),
			m_observercount(i_other.m_observercount)
		{
			ASSERT(m_ptr != nullptr, "try to copy a nullptr");
			(*m_RefCount)++;
		}
		template<class U>
		SmartPointer(const SmartPointer<U> & i_other) : 
			m_ptr(i_other.m_ptr),
			m_RefCount(i_other.m_RefCount),
			m_observercount(i_other.m_observercount)
		{
			ASSERT(i_other.m_ptr != nullptr, "try to copy a nullptr");
			(*m_RefCount)++;
		}
		inline SmartPointer& operator = (const SmartPointer<T>& i_other) {
			ASSERT(i_other.m_ptr != nullptr, "try to copy a nullptr");
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			m_observercount = i_other.m_observercount;
			(*m_RefCount)++ ;
			return *this;
		}
		template<class U>
		inline SmartPointer& operator = (const SmartPointer<U> & i_other) {
			ASSERT(i_other.m_ptr != nullptr, "try to copy a nullptr");
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			m_observercount = i_other.m_observercount;
			(*m_RefCount)++;
			return *this;
		}
		~SmartPointer() {
			if (m_ptr) {
				ReleaseReference();
			}
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
	template<class T>
	class ObserverPointer {
		template<class U>
		friend class ObserverPointer;
		template<class U>
		friend class SmartPointer;
	private:
		T* m_ptr;
		//This canbe unsigned int
		ref_counter_t* m_RefCount;
		ref_counter_t* m_observercount;
		inline void ReleaseReference() {
			ASSERT(m_observercount != nullptr, "try to release a nullptr");
			if (--(*m_observercount) == 0) {
				if (!m_ptr) {
					delete m_observercount;
				}
			}
		}inline bool isValid() {
			return m_ptr;
		}
	public:
		ObserverPointer():m_ptr(nullptr),m_RefCount(nullptr),m_observercount(new ref_counter_t(1)){}
		ObserverPointer(const ObserverPointer& i_other) :
			m_ptr(i_other.m_ptr),
			m_RefCount(i_other.m_RefCount),
			m_observercount(i_other.m_observercount)
		{
			ASSERT(i_other.m_ptr != nullptr, "try to copy a nullptr");
			(*m_observercount)++;
		}
		template<class U>
		ObserverPointer(const ObserverPointer<U> & i_other) :
			m_ptr(i_other.m_ptr),
			m_RefCount(i_other.m_RefCount),
			m_observercount(i_other.m_observercount)
		{
			ASSERT(i_other.m_ptr != nullptr, "try to copy a nullptr");
			(*m_observercount)++;
		}
		inline ObserverPointer& operator = (const ObserverPointer<T>& i_other) {
			ASSERT(i_other.m_ptr != nullptr, "try to copy a nullptr");
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			m_observercount = i_other.m_observercount;
			(*m_observercount)++;
			return *this;
		}
		template<class U>
		inline ObserverPointer& operator = (const ObserverPointer<U> & i_other) {
			ASSERT(i_other.m_ptr != nullptr, "try to copy a nullptr");
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			m_observercount = i_other.m_observercount;
			(*m_observercount)++;
			return *this;
		}
		inline ObserverPointer& operator = (const SmartPointer<T>& i_other) {
			ASSERT(i_other.m_ptr != nullptr, "try to copy a nullptr");
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			m_observercount = i_other.m_observercount;
			(*m_observercount)++;
			return *this;
		}
		template<class U>
		inline ObserverPointer& operator = (const SmartPointer<U> & i_other) {
			ASSERT(i_other.m_ptr != nullptr, "try to copy a nullptr");
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			m_observercount = i_other.m_observercount;
			(*m_observercount)++;
			return *this;
		}
		inline T* operator ->() {
			if (isValid()) {
				return m_ptr;
			}
		}
		inline T& operator *() {
			if (isValid) {
				ASSERT(m_ptr != nullptr, "SmartPointer is null");
				return *m_ptr;
			}
		}
	};
}