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
	memset(&(infoblock->start),HeapManager::fillguard,4);
	memset(&(infoblock->end), HeapManager::fillguard, 4);
	infoblock->isusing = HeapManager::infoisnotusing;
	infoblock->size = HeapSize - sizeof(INFOBLCOK) - guardsize - 1; // start with infroblock end with guards
	_current = _movePointerForward(_current, sizeof(INFOBLCOK));
	memset(_current, HeapManager::fillinitialfilled, infoblock->size);
	_current = _movePointerForward(_current, infoblock->size);
	_current = _movePointerForward(_pHeapMemeoy, HeapSize);
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
	_current = _movePointerForward(_current, 1);
	size_t* size = reinterpret_cast<size_t*>(_current);
	*size = HeapSize - INFOSIZE;
	_current = _movePointerForward(_current, 4);



	/*DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%i", sizeof(bool));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%i", sizeof(size_t));
	unsigned long address = reinterpret_cast<unsigned long>(_pHeapMemeoy);
	address += 1;
	void* temp = reinterpret_cast<void*>(address);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", temp);*/
}

void * HeapManager::FindFirstFit(rsize_t size)
{
	_current = _pHeapMemory;
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _current);
	INFOBLCOK* current = reinterpret_cast<INFOBLCOK*>(_current);
	while (!(this->_Match(size,4))) {
		_Travel();
		if (current->isusing == HeapManager::infoend) {
			return nullptr;
		}
	}
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _current);
	return _current;
}

void* HeapManager::_movePointerForward(void * _pointer, int number)
{
	unsigned long address = reinterpret_cast<unsigned long>(_pointer);
	address += number;
	return reinterpret_cast<void*>(address);
}
void* HeapManager::_movePointerBackward(void * _pointer, int number)
{
	unsigned long address = reinterpret_cast<unsigned long>(_pointer);
	address -= number;
	return reinterpret_cast<void*>(address);
}
void HeapManager::_Travel()
{
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _current);
	INFOBLCOK* current = reinterpret_cast<INFOBLCOK*>(_current);
	_current = _movePointerForward(_current, sizeof(INFOBLCOK) + current->size);
}

bool HeapManager::_Match(rsize_t size, unsigned int alignment)
{
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _current);
	INFOBLCOK* current = reinterpret_cast<INFOBLCOK*>(_current);
	if ((current->size > size + sizeof(INFOBLCOK))&&current->isusing == HeapManager::infoisnotusing) {
		return _TryCut(size,alignment);
	}
	else {
		return false;
	}
	
}


bool HeapManager::_TryCut(rsize_t size, unsigned int alignment)
{
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _current);
	INFOBLCOK* current = reinterpret_cast<INFOBLCOK*>(_current);
	size_t end = reinterpret_cast<size_t>(_movePointerForward(_current, current->size + sizeof(INFOBLCOK)));
	end -= size;
	size_t temp = end % alignment;
	if (current->size < temp) {
		return false;
	}
	else
	{
		end -= temp;
		_current = reinterpret_cast<void*>(end);
		void* temppointer = _movePointerForward(_current,size);
		memset(temppointer, HeapManager::fillpadding, temp);
		//Fill the padding 
		//if the block is too small just give it all to the user
		if (current->size < temp + sizeof(INFOBLCOK) * 2) {
			memset(_current,HeapManager::fillinitialfilled,size);
			current->isusing = HeapManager::infoisusing;
		}
		//if the block is big enough cut parts to the user
		else {
			_current = _movePointerBackward(_current,sizeof(INFOBLCOK));
			_addinfoblock(size);
			//size + padding + info block
			current->size -= size + temp + sizeof(INFOBLCOK);
		}
	}
	return true;
}

void HeapManager::_addinfoblock(size_t size)
{
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "The new block start at%p", _current);
	INFOBLCOK* infoblock = reinterpret_cast<INFOBLCOK*>(_current);
	memset(&(infoblock->start), HeapManager::fillguard, 4);
	memset(&(infoblock->end), HeapManager::fillguard, 4);
	infoblock->isusing = HeapManager::infoisusing;
	infoblock->size = size; // start with infroblock end with guards
	_current = _movePointerForward(_current, sizeof(INFOBLCOK));
	memset(_current, HeapManager::fillinitialfilled, infoblock->size);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "userinfomation start at%p", _current);
}
