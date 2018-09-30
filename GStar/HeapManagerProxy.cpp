#include "HeapManagerProxy.h"
#include "HeapManager.h"
HeapManager * GStar::CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	return new HeapManager(i_sizeMemory, i_numDescriptors, i_pMemory);
}

void * GStar::alloc(HeapManager * i_pManager, size_t i_size)
{
	return i_pManager->FindFirstFit(i_size);
}

void * GStar::alloc(HeapManager * i_pManager, size_t i_size, unsigned int i_alignment)
{
	return i_pManager->FindFirstFit(i_size,i_alignment);
}
