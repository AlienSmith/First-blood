#pragma once
#include<stdint.h>
#include"Assert.h"
#include"ConsolePrint.h"
namespace GStar {
	typedef uint64_t ref_count_t;
	template<class T>
	class SharedPointer {
		template<class U>
		friend class SmartPointer;
	public:
		inline public bool MarkForDeath() {
			if (!(*markofdeath)) {
				*markofdeath = true;
				return true;
			}
			return false;
		}
		SharedPointer():m_ptr(nullptr),m_RefCount(new ref_count_t(0)),markofdeath(new bool(false)){}
		SharedPointer(T* i_ptr):m_ptr(i_ptr),m_RefCount(new ref_count_t(1)),markofdeath(new bool(false)){}
		SharedPointer(const SmartPointer<T>& i_other) :
			m_ptr(i_other.m_ptr),
			m_RefCount(i_other.m_RefCount),
			markofdeath(i_other.markofdeath){
			ASSERT(m_ptr != nullptr, "try to copy a nullptr");
			(*m_RefCount)++;
		}
		template<class U>
		SharedPointer(const SmartPointer<U>& i_other) :
			m_ptr(i_other.m_ptr),
			m_RefCount(i_other.m_RefCount),
			markofdeath(i_other.markofdeath){
			ASSERT(m_ptr != nullptr, "try to copy a nullptr");
			(*m_RefCount)++;
		}
		inline SharedPointer& operator = (const SharedPointer<T>& i_other) {
			ASSERT(m_ptr != nullptr, "try to copy a nullptr");
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			(*m_RefCount)++;
			markofdeath = i_other.markofdeath;
			return *this;
		}

		template<class U>
		inline SharedPointer& operator = (const SharedPointer<U>& i_other) {
			ASSERT(m_ptr != nullptr, "try to copy a nullptr");
			if (m_ptr == i_other.m_ptr) {
				DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "SelfAssignment");
				return *this;
			}
			ReleaseReference();
			m_ptr = i_other.m_ptr;
			m_RefCount = i_other.m_RefCount;
			(*m_RefCount)++;
			markofdeath = i_other.markofdeath;
			return *this;
		}

		~SharedPointer() {
			if (m_ptr) {
				ReleaseReference();
			}
		}

		inline T* operator ->() {
			return m_ptr;
		}
		inline T& operator *() {
			return *m_ptr;
		}
		inline bool operator ==(const SharedPointer<T>& i_other) const {
			return m_ptr == i_other.m_ptr;
		}
		template<class U>
		inline bool operator == (const SharedPointer<U>& i_other) const {
			return m_ptr == i_other.m_ptr;
		}
		inline bool operator !=(const SharedPointer<T>& i_other) const {
			return m_ptr != i_other.m_ptr;
		}
		template<class U>
		inline bool operator != (const SharedPointer<U>& i_other) const {
			return m_ptr != i_other.m_ptr;
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
		inline bool operator!() const {
			return !m_ptr;
		}
		inline operator bool() const {
			return m_ptr;
		}
		inline bool isValid() {
			if (m_ptr && !(*markofdeath)) {
				return true;
			}
			else {
				ReleaseReference();
			}
		}
	private:
		T* m_ptr;
		ref_count_t* m_RefCount;
		bool* markofdeath;
		inline void ReleaseReference() {
			ASSERT(m_ptr != nullptr, "try to release a nullptr");
			if (--(*m_RefCount) == 0) {
				(*markofdeath) = true;
				delete m_RefCount;
				delete m_ptr;
				delete markofdeath;
			}
		}
	};
}