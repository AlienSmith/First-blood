#include "MemorySystem.h"
#include "FixiedSizeAllocator.h"
//This is windows specific
#include <Windows.h>
void* generalHeap = nullptr;
bool InitializeMemorySystem()
{ 
	generalHeap = HeapAlloc(GetProcessHeap(), 0, GENERALHEAPSIZE);
	FixedSizeAllocator::Initialize(generalHeap, GENERALHEAPSIZE, GENERALHEAPSIZE);
	return true;
}

void Collect()
{
	HeapManager::Instance().Collect();
}

void DestroyMemorySystem()
{
	FixedSizeAllocator::Terminate();
	HeapFree(GetProcessHeap(), 0, generalHeap);
}

