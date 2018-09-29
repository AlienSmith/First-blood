#pragma once
#include <stdio.h>
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER)
#define INFOSIZE 13
#define ACTIVITE true;
// on this machine size_t takes 7 bytes
struct INFOBLCOK { char start[4]; char isusing; size_t size; char end[4]; };
#else
// This is one way we create a do nothing (NO OP) macro that doesn't
// generate a compiler warning or error
#define INFOSIZE 5
#define ACTIVITE false;
struct INFOBLCOK {  char isusing; size_t size };
#endif
class HeapManager {
public:
	// the static to decide wheter a block is being used by client. e suggests end of the heap;
	static const char infoisusing = 'y';
	static const char infoisnotusing = 'n';
	static const char infoend = 'e';
	static constexpr const char const guardarray[4] = { NULL,NULL,NULL,NULL };
	static const int guardsize = 4;
	static const char fillguard = '\0';
	static const char fillfreed = 'f';
	static const char fillinitialfilled = 'i';
	static const char padding = 'p';
	HeapManager(size_t HeapSize, unsigned int numDescriptors, void* _pHeapMemeoy);
private:
	size_t _sizeHeap;
	unsigned int _numDescriptors;
	void* _pHeapMemory;
	void* _current;
	void* _movePointer(void* _pointer, int number);
	bool _isdebugactivited = ACTIVITE;
};