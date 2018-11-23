#pragma once
#include "SingleLinkedList.h"
namespace GStar {
	template<class T, class M>
	class SingleLinkedDictionary {
	public:
		SingleLinkedDictionary() {
			Keys = SingleLinkedList<T*>();
			values = SingleLinkedList<M*>();
		}
		void Put(T* key, M* value);
		bool ContainKey(T* key);
		bool DeleteKey(T* key);
		bool SetValue(T* key, M* value);
	private:
		SingleLinkedList<T*> Keys;
		SingleLinkedList<M*> values;
	};
	template<class T, class M>
	inline void SingleLinkedDictionary<T, M>::Put(T* key, M* value)
	{
			Keys.Push(key);
			values.Push(value);
	}
	template<class T, class M>
	inline bool SingleLinkedDictionary<T, M>::ContainKey(T* key)
	{
			Keys.Resetcurrent();
			T*& currentkey;
			while (Keys.HasNext()) {
				currentkey = Keys.GetNext();
				if (*currentkey == *key) {
					return true;
				}
				Keys.Move();
			}
			return false;
	}
	template<class T, class M>
	inline bool SingleLinkedDictionary<T, M>::DeleteKey(T* key)
	{
		Keys.Resetcurrent();
		values.Resetcurrent();
		T*& currentkey;
		M*& currentvalue;
		while (Keys.HasNext()) {
			currentkey = Keys.GetNext();
			currentvalue = values.GetNext();
			if (*currentkey == *key) {
				Keys.DeleteNext();
				values.DeleteNext();
				return true;
			}
			Keys.Move();
			values.Move();
		}
		return false;
	}
	template<class T, class M>
	inline bool SingleLinkedDictionary<T, M>::SetValue(T* key, M* value)
	{
		Keys.Resetcurrent();
		values.Resetcurrent();
		T*& currentkey;
		M*& currentvalue;
		while (Keys.HasNext()) {
			currentkey = Keys.GetNext();
			currentvalue = values.GetNext();
			if (*currentkey == *key) {
				currentvalue = &value;
				return true;
			}
			Keys.Move();
			values.Move();
		}
		return false;
	}
}