#pragma once
#include <stdio.h>
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER)
#define ACTIVITE true;
// on this machine size_t takes 7 bytes
struct INFOBLCOK { char start[4]; char isusing; size_t size; char end[4]; };
#else
// This is one way we create a do nothing (NO OP) macro that doesn't
// generate a compiler warning or error
#define INFOSIZE 8
#define ACTIVITE false;
struct INFOBLCOK {  char isusing; size_t size };
#endif
class HeapManager {
public:
	static HeapManager TheManager;
	static void Initialize();
	int jump = 0;

	static void* _movePointerForward(const void* const _pointer, int number) ;
	static void* _movePointerBackward(const void* const _pointer, int number);
	static size_t difference(void* one, void* two);
	// the static to decide wheter a block is being used by client. e suggests end of the heap;
	static const char infoisusing = 'y';
	static const char infoisnotusing = 'n';
	static const char infoend = 'e';
	static const int guardsize = 4;
	static const char fillguard = '\0';
	static const char fillfreed = 'f';
	static const char fillinitialfilled = 'i';
	static const char fillpadding = 'p';
	HeapManager(size_t HeapSize, unsigned int numDescriptors, void* _pHeapMemeoy);
	//TODO implement a copy constructor and a assignement operator.
	~HeapManager();
	void* FindFirstFit(rsize_t size);
	void* FindFirstFit(rsize_t size,unsigned int i_alignment);
	bool free(void* i_ptr);
	//This function will jump three blocks backward to see if they are descriptor
	bool contains(void* ipr) const;
	bool IsAllocated(void* ipr) const;
	void Collect();
	void ShowFreeBlocks() const;
	void ShowOutstandingAllocations() const;
private:
	bool _tryFastBackCollect();// Require the _current pointer set to the descriptor return blocksize + INFOSIZE -1 for false
	void _deletHead();// Require the _current pointer set to the descriptor return blocksize + INFOSIZE
	size_t _sizeHeap;
	unsigned int _numDescriptors;
	void* _pHeapMemory;
	void* _current;
	bool _Match(rsize_t size,unsigned int alignment);
	bool _isdebugactivited = ACTIVITE;
	bool _TryCut(rsize_t size, unsigned int alignment);
	void _addinfoblock(size_t size);
	INFOBLCOK* _TravelToNextDescriptor(const INFOBLCOK* const i_ptr) const;// take the input pointer return the pointer to the next descriptor this will also check if write on the padding value under debug
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER)
	void _FreeCheck(void* ipr); // Do notic this function will not report if the user write on the padding area check if write overrange and on to the filled guard writing on 
								//TODO add a descriptro as block + using + size for pervious + this padding size + size for next + block for debug and use using + size for pervious +size for next for release
#endif
};