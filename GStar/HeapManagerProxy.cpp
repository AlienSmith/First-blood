#include "HeapManagerProxy.h"
#include "HeapManager.h"
HeapManager * GStar::CreateHeapManager(void * i_pMemory, size_t i_sizeMemory, unsigned int i_numDescriptors)
{
	return new HeapManager(i_sizeMemory, i_numDescriptors, i_pMemory);
}
