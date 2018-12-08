#include "MyString.h"
#include <algorithm>
#include "ConsolePrint.h"
#include <stdio.h>
#include "HeapManager.h"
const size_t GStar::MyString::StringHeapSize = 2014 * 1024;
void* GStar::MyString::StringHeap = nullptr;
void GStar::MyString::Initialize()
{
	StringHeap = malloc(StringHeapSize);
	HeapManager::Instance().InitializeWith(StringHeapSize, StringHeapSize, StringHeap);
}
// this is a swap using shallow opearation
void GStar::MyString::swap(MyString & string, MyString & other)
{
	std::swap(string.my_string, other.my_string);
	std::swap(string.my_size, other.my_size);
}

void GStar::MyString::swap(MyString & string, char *& other, size_t size)
{
	std::swap(string.my_string, other);
	string.my_size = size;
}

size_t GStar::MyString::stringlength(const char * other)
{
	int len = 1;
	const char * p = other;
	while (*p != '\0') {
		len++;
		p++;
	}
	return len;
}

GStar::MyString::MyString():my_size(0), my_string(nullptr)
{
}

GStar::MyString::MyString(const char other[])
	:my_size(MyString::stringlength(other)),
	my_string(new char[MyString::stringlength(other)])
{
	strcpy_s(my_string, my_size, other);
}

GStar::MyString::MyString( size_t size):my_size(size)
{
	my_string = new char[size];
}
// Copy Constructor A deep copy of the string
GStar::MyString::MyString(const MyString & other)
	: my_size(other.my_size),
	my_string(other.my_size ? new char[other.my_size] : nullptr)
{
	//std::copy(other.my_string, other.my_string + my_size, my_string); This is a shallow copy .. wired
	strcpy_s(my_string, my_size, other.my_string);
	
}
GStar::MyString::MyString(MyString && other)
{
	swap(*this, other);
}
//Here input is a Value(Object) instead of a reference type(const reference)
//let the compile handle copy could be beneficial other will be generated using copy constrctor
// Notice copy is not a temporary Temporary exist when function returns
GStar::MyString& GStar::MyString::operator=(const MyString& other)
{
	MyString temp = MyString(other);
	swap(*this, temp);
	return *this;
}

GStar::MyString & GStar::MyString::operator=(MyString && other)
{
	swap(*this,other);
	return *this;
}

GStar::MyString & GStar::MyString::operator=(const char other[])
{
	GStar::MyString temp = GStar::MyString(other);
	*this = temp;
	return *this;
}

GStar::MyString & GStar::MyString::operator=(const char(&& other)[])
{
	this->my_size = GStar::MyString::stringlength(other);
	delete[] this->my_string;
	this->my_string = const_cast<char*>(&other[0]);
	return *this;
}

size_t GStar::MyString::GetSize() const
{
	return this->my_size;
}

const char * const GStar::MyString::GetString() const
{
	return this->my_string;
}

GStar::MyString::~MyString()
{
	if (my_string) {
		delete[] my_string;
	}
}

/*void * GStar::MyString::operator new(size_t i_size)
{
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "string allocator called");
	if (!MyString::StringHeap) {
		MyString::Initialize();
	}
	HeapManager::Instance().SetPointerTo(MyString::StringHeap);
	return HeapManager::Instance().FindFirstFit(i_size);
}

void GStar::MyString::operator delete(void * i_ptr)
{
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "string free called");
	//Do not need to set pointer if not collect
	HeapManager::Instance().SetPointerTo(MyString::StringHeap);
	HeapManager::Instance().free(i_ptr);
	HeapManager::Instance().Collect();
}*/

GStar::MyString GStar::operator+(const GStar::MyString & A, const GStar::MyString & B)
{
	rsize_t temp_size = A.GetSize() + B.GetSize() -1;
	char* temp = new char[temp_size];
	//strcat will look for the null - terminator, interpret that as the end of the string, and append the new text there, overwriting the null - terminator in the process, and writing a new null - terminator at the end of the concatenation.
	strcpy_s(temp, temp_size, A.GetString());
	strcat_s(temp, temp_size, B.GetString());
	// Here I used the copy constructor and deep copyed the value
	// I use the move constrctor insted. since here temp will not be used any more.
	// String tempString = String(temp)
	//Saved one copy time
	MyString tempString = MyString();
	GStar::MyString::swap(tempString, temp, temp_size);
	delete[] temp;
	return tempString;
}
