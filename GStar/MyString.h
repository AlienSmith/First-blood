#pragma once
#ifndef GSTAR_MyString_H
#define GSTAR_MyString_H
#define PrimeA 54059 /* a prime */
#define PrimeB 76963 /* another prime */
#define PrimeC 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */
//How write a rvalue referece of char array
namespace GStar {
	class MyString {
	public:
		const static size_t StringHeapSize;
		static void* StringHeap;
		static void Initialize();
		static void swap(MyString& string,MyString& other);
		static void swap(MyString& string, char*& other, size_t size);
		static size_t stringlength(const char* other);
		static unsigned int hash_str(const char* s)
		{
			unsigned int h = FIRSTH;
			while (*s) {
				h = (h * PrimeA) ^ (s[0] * PrimeB);
				s++;
			}
			return h % PrimeC;
		}
		MyString();
		//Value Constructor
		MyString(const char other[]);
		MyString(size_t size);
		//Copy Constructor
		MyString(const MyString& other);
		//Move Constructor
		MyString(MyString&& other);
		//Copy Assignment operator
		MyString& operator= (const MyString& other);
		//MyString& operator= (MyString other); and MyString& operator= (MyString && other); will lead to a error
		//Move Assignment operator
		MyString& operator= (MyString && other);
		MyString& operator= (const char other[]);
		MyString& operator= (const char(&&other)[]);
		//Geters
		size_t GetSize() const;
		const char* const GetString() const;
		//Destructor
		~MyString();
		/*void* operator new(size_t i_size);
		void operator delete(void* i_ptr);*/
	private:
		char* my_string = nullptr;// always always intialize those that need to be delete check the prvious version for compiler constructor empty object without using default constructor.
		size_t my_size = 0;
	};
	GStar::MyString operator+ (const GStar::MyString& A, const GStar::MyString& B);
}
#endif
