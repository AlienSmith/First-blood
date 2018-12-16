#include "MemorySystem.h"
#include "FixiedSizeAllocator.h"
//This is windows specific
#include <Windows.h>
bool InitializeMemorySystem()
{
	HeapManager::GeneralHeap = HeapAlloc(GetProcessHeap(), 0,GENERALHEAPSIZE);
	FixedSizeAllocator::Initialize(HeapManager::GeneralHeap, GENERALHEAPSIZE, GENERALHEAPSIZE);
	return true;
}

void Collect()
{
	HeapManager::Instance().Collect();
}

void DestroyMemorySystem()
{
	FixedSizeAllocator::Terminate();
	HeapFree(GetProcessHeap(), 0, HeapManager::GeneralHeap);
}

