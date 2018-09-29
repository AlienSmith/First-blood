#include "HeapManager.h"
#include <stdio.h>
#include <cstring>
#include "ConsolePrint.h"
HeapManager::HeapManager(size_t HeapSize, unsigned int numDescriptors, void * _pHeapMemeoy)
{
	this->_sizeHeap = HeapSize;
	this->_numDescriptors = numDescriptors;
	this->_pHeapMemory = _pHeapMemeoy;
	//memset(_pHeapMemeoy, '\0', HeapSize);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%s", _pHeapMemeoy);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _pHeapMemeoy);
	_current = _pHeapMemeoy;
	INFOBLCOK* infoblock = reinterpret_cast<INFOBLCOK*>(_current);
	strncpy_s(infoblock->start, HeapManager::guardarray,3);
	strncpy_s(infoblock->end, HeapManager::guardarray,3);
	infoblock->isusing = HeapManager::infoisusing;
	infoblock->size = HeapSize - sizeof(INFOBLCOK) - guardsize - 1; // start with infroblock end with guards
	_current = _movePointer(_current, sizeof(INFOBLCOK));
	memset(_current, HeapManager::fillinitialfilled, infoblock->size);
	_current = _movePointer(_current, infoblock->size);
	_current = _movePointer(_pHeapMemeoy, HeapSize);
	char* end = reinterpret_cast<char*>(_current);
	*end = HeapManager::infoend;
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _current);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "my info block have size %i", sizeof(INFOBLCOK));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "size_t have size %i", sizeof(size_t));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "char have size %i", sizeof(char));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "start is %s", infoblock->start);
	/*this->_current = this->_pHeapMemory;
	bool* used = reinterpret_cast<bool*>(_current);
	*used = true;
	_current = _movePointer(_current, 1);
	size_t* size = reinterpret_cast<size_t*>(_current);
	*size = HeapSize - INFOSIZE;
	_current = _movePointer(_current, 4);



	/*DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%i", sizeof(bool));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%i", sizeof(size_t));
	unsigned long address = reinterpret_cast<unsigned long>(_pHeapMemeoy);
	address += 1;
	void* temp = reinterpret_cast<void*>(address);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", temp);*/
}

void* HeapManager::_movePointer(void * _pointer, int number)
{
	unsigned long address = reinterpret_cast<unsigned long>(_pointer);
	address += number;
	return reinterpret_cast<void*>(address);
}
