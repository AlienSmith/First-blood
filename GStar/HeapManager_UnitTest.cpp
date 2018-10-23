#include"Assert.h"
#include "HeapManagerProxy.h"
#include <Windows.h>

#include <algorithm>
#include <vector>

#define SUPPORTS_ALIGNMENT
//#define SUPPORTS_SHOWFREEBLOCKS
//#define SUPPORTS_SHOWOUTSTANDINGALLOCATIONS

bool HeapManager_UnitTest()
{

	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;

	// Allocate memory for my test heap.
	void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	//assert(pHeapMemory);

	// Create a heap manager for my test heap.
	HeapManager * pHeapManager = GStar::CreateHeapManager(pHeapMemory, sizeHeap, numDescriptors);
	//assert(pHeapManager);

	if (pHeapManager == nullptr)
		return false;
	void* nada = GStar::alloc(pHeapManager, 20, 7);
	void* nada1 = GStar::alloc(pHeapManager, 20);
	bool success1 = GStar::Contains(pHeapManager, nada);
	bool success2 =  GStar::IsAllocated(pHeapManager, nada);
	bool success4 = GStar::free(pHeapManager, nada1);
	bool success3 = GStar::free(pHeapManager, nada);
	GStar::Collect(pHeapManager);

#ifdef TEST_SINGLE_LARGE_ALLOCATION
	// This is a test I wrote to check to see if using the whole block if it was almost consumed by 
	// an allocation worked. Also helped test my ShowFreeBlocks() and ShowOutstandingAllocations().
	{
#ifdef SUPPORTS_SHOWFREEBLOCKS
		ShowFreeBlocks(pHeapManager);
#endif // SUPPORTS_SHOWFREEBLOCKS

		size_t largestBeforeAlloc = GetLargestFreeBlock(pHeapManager);
		void * pPtr = alloc(pHeapManager, largestBeforeAlloc - HeapManager::s_MinumumToLeave);

		if (pPtr)
		{
#if defined(SUPPORTS_SHOWFREEBLOCKS) || defined(SUPPORTS_SHOWOUTSTANDINGALLOCATIONS)
			printf("After large allocation:\n");
#ifdef SUPPORTS_SHOWFREEBLOCKS
			ShowFreeBlocks(pHeapManager);
#endif // SUPPORTS_SHOWFREEBLOCKS
#ifdef SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
			ShowOutstandingAllocations(pHeapManager);
#endif // SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
			printf("\n");
#endif

			size_t largestAfterAlloc = GetLargestFreeBlock(pHeapManager);
			bool success = Contains(pHeapManager, pPtr) && IsAllocated(pHeapManager, pPtr);
			ASSERT(success,"1111111");

			success = free(pHeapManager, pPtr);
			ASSERT(success, "2222222");

			Collect(pHeapManager);

#if defined(SUPPORTS_SHOWFREEBLOCKS) || defined(SUPPORTS_SHOWOUTSTANDINGALLOCATIONS)
			printf("After freeing allocation and garbage collection:\n");
#ifdef SUPPORTS_SHOWFREEBLOCKS
			ShowFreeBlocks(pHeapManager);
#endif // SUPPORTS_SHOWFREEBLOCKS
#ifdef SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
			ShowOutstandingAllocations(pHeapManager);
#endif // SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
			printf("\n");
#endif

			size_t largestAfterCollect = GetLargestFreeBlock(pHeapManager);
		}
	}
#endif

	std::vector<void *> AllocatedAddresses;

	long	numAllocs = 0;
	long	numFrees = 0;
	long	numCollects = 0;

	// allocate memory of random sizes up to 1024 bytes from the heap manager
	// until it runs out of memory
	do
	{
		const size_t		maxTestAllocationSize = 1024;

		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));

#ifdef SUPPORTS_ALIGNMENT
		// pick an alignment
		const unsigned int	alignments[] = { 4, 8, 16, 32, 64 };

		const unsigned int	index = rand() % (sizeof(alignments) / sizeof(alignments[0]));

		const unsigned int	alignment = alignments[index];

		void * pPtr = GStar::alloc(pHeapManager, sizeAlloc, alignment);

		// check that the returned address has the requested alignment
		ASSERT((reinterpret_cast<uintptr_t>(pPtr) & (alignment - 1)) == 0,"Return address aligment wrong");
#else
		void * pPtr = alloc(pHeapManager, sizeAlloc);
#endif // SUPPORT_ALIGNMENT

		// if allocation failed see if garbage collecting will create a large enough block
		if (pPtr == nullptr)
		{
			GStar::Collect(pHeapManager);

#ifdef SUPPORTS_ALIGNMENT
			pPtr = GStar::alloc(pHeapManager, sizeAlloc, alignment);
#else
			pPtr = alloc(pHeapManager, sizeAlloc);
#endif // SUPPORT_ALIGNMENT

			// if not we're done. go on to cleanup phase of test
			if (pPtr == nullptr)
				break;
		}

		AllocatedAddresses.push_back(pPtr);
		numAllocs++;

		// randomly free and/or garbage collect during allocation phase
		const unsigned int freeAboutEvery = 10;
		const unsigned int garbageCollectAboutEvery = 40;

		if (!AllocatedAddresses.empty() && ((rand() % freeAboutEvery) == 0))
		{
			void * pPtr = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			bool success = GStar::Contains(pHeapManager, pPtr) && GStar::IsAllocated(pHeapManager, pPtr);
			ASSERT(success, "Contain function wrong");

			success = GStar::free(pHeapManager, pPtr);
			ASSERT(success, "Free Function wrong");

			numFrees++;
		}

		if ((rand() % garbageCollectAboutEvery) == 0)
		{
			GStar::Collect(pHeapManager);

			numCollects++;
		}

	} while (1);

#if defined(SUPPORTS_SHOWFREEBLOCKS) || defined(SUPPORTS_SHOWOUTSTANDINGALLOCATIONS)
	printf("After exhausting allocations:\n");
#ifdef SUPPORTS_SHOWFREEBLOCKS
	GStar::ShowFreeBlocks(pHeapManager);
#endif // SUPPORTS_SHOWFREEBLOCKS
#ifdef SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
	GStar::ShowOutstandingAllocations(pHeapManager);
#endif // SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
	printf("\n");
#endif

	// now free those blocks in a random order
	if (!AllocatedAddresses.empty())
	{
		// randomize the addresses
		std::random_shuffle(AllocatedAddresses.begin(), AllocatedAddresses.end());

		// return them back to the heap manager
		while (!AllocatedAddresses.empty())
		{
			void * pPtr = AllocatedAddresses.back();
			AllocatedAddresses.pop_back();

			bool success = GStar::Contains(pHeapManager, pPtr) && GStar::IsAllocated(pHeapManager, pPtr);
			ASSERT(success, "Contain function wrong");

			success = GStar::free(pHeapManager, pPtr);
			ASSERT(success, "Free Function wrong");
		}

#if defined(SUPPORTS_SHOWFREEBLOCKS) || defined(SUPPORTS_SHOWOUTSTANDINGALLOCATIONS)
		printf("After freeing allocations:\n");
#ifdef SUPPORTS_SHOWFREEBLOCKS
		GStar::ShowFreeBlocks(pHeapManager);
#endif // SUPPORTS_SHOWFREEBLOCKS

#ifdef SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
		GStar::ShowOutstandingAllocations(pHeapManager);
#endif // SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
		printf("\n");
#endif

		// do garbage collection
		GStar::Collect(pHeapManager);
		// our heap should be one single block, all the memory it started with

#if defined(SUPPORTS_SHOWFREEBLOCKS) || defined(SUPPORTS_SHOWOUTSTANDINGALLOCATIONS)
		printf("After garbage collection:\n");
#ifdef SUPPORTS_SHOWFREEBLOCKS
		GStar::ShowFreeBlocks(pHeapManager);
#endif // SUPPORTS_SHOWFREEBLOCKS

#ifdef SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
		GStar::ShowOutstandingAllocations(pHeapManager);
#endif // SUPPORTS_SHOWOUTSTANDINGALLOCATIONS
		printf("\n");
#endif

		// do a large test allocation to see if garbage collection worked
		void * pPtr = GStar::alloc(pHeapManager, sizeHeap / 2);
		ASSERT(pPtr, "Allocation Wrong");

		if (pPtr)
		{
			bool success = GStar::Contains(pHeapManager, pPtr) && GStar::IsAllocated(pHeapManager, pPtr);
			ASSERT(success,"Contain Worng");

			success = GStar::free(pHeapManager, pPtr);
			ASSERT(success,"Free Wrong");

		}
	}

	GStar::Destroy(pHeapManager);
	pHeapManager = nullptr;

	HeapFree(GetProcessHeap(), 0, pHeapMemory);

	// we succeeded
	return true;
}
