#include "HeapManagerProxy.h"
#include "HeapManager.h"
HeapManager * GStar::CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	return new HeapManager(i_sizeMemory, i_numDescriptors, i_pMemory);
}

void GStar::Destroy(HeapManager * i_pManager)
{
	delete i_pManager;
}

void * GStar::alloc(HeapManager * i_pManager, size_t i_size)
{
	return i_pManager->FindFirstFit(i_size);
}

void * GStar::alloc(HeapManager * i_pManager, size_t i_size, unsigned int i_alignment)
{
	return i_pManager->FindFirstFit(i_size,i_alignment);
}

bool GStar::free(HeapManager * i_pManager, void * i_ptr)
{
	return i_pManager->free(i_ptr);
}

void GStar::Collect(HeapManager * i_pManager)
{
	i_pManager->Collect();
}

bool GStar::Contains(const HeapManager * i_pManager, void * i_ptr)
{
	return i_pManager->contains(i_ptr);
}

bool GStar::IsAllocated(const HeapManager * i_pManager, void * i_ptr)
{
	return i_pManager->IsAllocated(i_ptr);
}
