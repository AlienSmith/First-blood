#include "HeapManagerProxy.h"
#include <Windows.h>

#include <assert.h>
#include <algorithm>
#include <vector>

#define SUPPORTS_ALIGNMENT
#define SUPPORTS_SHOWFREEBLOCKS
#define SUPPORTS_SHOWOUTSTANDINGALLOCATIONS

bool HeapManager_UnitTest()
{
	using namespace GStar;

	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;

	// Allocate memory for my test heap.
	void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	//assert(pHeapMemory);

	// Create a heap manager for my test heap.
	HeapManager * pHeapManager = CreateHeapManager(pHeapMemory, sizeHeap, numDescriptors);
	//assert(pHeapManager);

	if (pHeapManager == nullptr)
		return false;
	alloc(pHeapManager, 20);
	alloc(pHeapManager, 20);
	return true;
}