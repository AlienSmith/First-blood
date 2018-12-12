#pragma once
#include <stdio.h>
#define GENERALHEAPSIZE 268435456// 64 mb
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER) && _WIN32
#define _DEBUGACTIVITE true;
struct INFOBLCOK { char start[4]; size_t isusing :2; size_t size:30; char end[4]; };
#elif defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER) && _WIN64
#define _DEBUGACTIVITE true;
struct INFOBLCOK { char start[4]; size_t isusing : 2; size_t size : 62; char end[4]; };
#elif _WIN32
#define _DEBUGACTIVITE false;
struct INFOBLCOK { size_t isusing : 2; size_t size : 30; };
#elif _WIN64
#define _DEBUGACTIVITE false;
struct INFOBLCOK { size_t isusing : 2; size_t size : 30; };
#endif
class HeapManager {
public:
	static void* GeneralHeap;
	static HeapManager& Instance() {
		static HeapManager instance;
		return instance;
	}
	int jump = 0;
	HeapManager() :_pHeapMemory(nullptr) {}
	void InitializeWith(size_t HeapSize, unsigned int numDescriptors, void * _pHeapMemeoy);
	void SetPointerTo(void * _pHeapMemeoy);
	static void* _movePointerForward(const void* const _pointer, int number);
	static void* _movePointerBackward(const void* const _pointer, int number);
	static size_t difference(void* one, void* two);
	// the static to decide wheter a block is being used by client. e suggests end of the heap;
	static const size_t infoisusing = 0;
	static const size_t infoisnotusing = 1;
	static const size_t infoend = 2;
	static const int guardsize = 4;
	static const char fillguard = '\0';
	static const char fillfreed = 'f';
	static const char fillinitialfilled = 'i';
	static const char fillpadding = 'p';
	HeapManager(size_t HeapSize, unsigned int numDescriptors, void* _pHeapMemeoy);
	//TODO implement a copy constructor and a assignement operator.
	~HeapManager();
	void* FindFirstFit(size_t size);
	void* FindFirstFit(size_t size, unsigned int i_alignment);
	bool free(void* i_ptr);
	//This function will jump three blocks backward to see if they are descriptor
	bool contains(void* ipr) const;
	bool IsAllocated(void* ipr) const;
	void Collect();
	void ShowFreeBlocks() const;
	void ShowOutstandingAllocations() const;
	//Temp Function
private:
	bool _tryFastBackCollect();// Require the _current pointer set to the descriptor return blocksize + INFOSIZE -1 for false
	void _deletHead();// Require the _current pointer set to the descriptor return blocksize + INFOSIZE
	size_t _sizeHeap;
	unsigned int _numDescriptors;
	void* _pHeapMemory;
	void* _current;
	bool _Match(size_t size, unsigned int alignment);
	bool _TryCut(size_t size, unsigned int alignment);
	void _addinfoblock(size_t size);
	INFOBLCOK* _TravelToNextDescriptor(const INFOBLCOK* const i_ptr) const;// take the input pointer return the pointer to the next descriptor this will also check if write on the padding value under debug
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER)
	void _FreeCheck(void* ipr); // Do notic this function will not report if the user write on the padding area check if write overrange and on to the filled guard writing on 
								//TODO add a descriptro as block + using + size for pervious + this padding size + size for next + block for debug and use using + size for pervious +size for next for release
#endif
};
void* operator new(size_t i_size);
void operator delete(void* i_ptr);