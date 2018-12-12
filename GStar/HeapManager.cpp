#include "HeapManager.h"

#include <cstring>
#include "ConsolePrint.h"
#include <stdio.h>
#include <stdlib.h>
//TODO make a effecient version for realease
void* HeapManager::GeneralHeap = nullptr;
#if _DEBUGACTIVITE
HeapManager::HeapManager(size_t HeapSize, unsigned int numDescriptors, void * _pHeapMemeoy)
{
	this->_sizeHeap = HeapSize;
	this->_numDescriptors = numDescriptors;
	this->_pHeapMemory = _pHeapMemeoy;
	//memset(_pHeapMemeoy, '\0', HeapSize);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "The memory block Start at%p", _pHeapMemeoy);
	_current = _pHeapMemeoy;
	INFOBLCOK* infoblock = reinterpret_cast<INFOBLCOK*>(_current);
	memset(&(infoblock->start), HeapManager::fillguard, 4);
	memset(&(infoblock->end), HeapManager::fillguard, 4);
	infoblock->isusing = HeapManager::infoisnotusing;
	infoblock->size = HeapSize - sizeof(INFOBLCOK) - guardsize - 1; // start with info end with guards

	_current = _movePointerForward(_current, sizeof(INFOBLCOK));
	memset(_current, HeapManager::fillinitialfilled, infoblock->size);
	_current = _movePointerForward(_current, infoblock->size);
	memset(_current, HeapManager::fillguard, guardsize);
	_current = _movePointerForward(_current, guardsize);
	char* end = reinterpret_cast<char*>(_current);
	*end = HeapManager::infoend;
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _current);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "my info block have size %i", sizeof(INFOBLCOK));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "size_t have size %i", sizeof(size_t));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "char have size %i", sizeof(char));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "start is %s", infoblock->start);
}
#else
HeapManager::HeapManager(size_t HeapSize, unsigned int numDescriptors, void * _pHeapMemeoy)
{
	this->_sizeHeap = HeapSize;
	this->_numDescriptors = numDescriptors;
	this->_pHeapMemory = _pHeapMemeoy;
	//memset(_pHeapMemeoy, '\0', HeapSize);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "The memory block Start at%p", _pHeapMemeoy);
	_current = _pHeapMemeoy;
	INFOBLCOK* infoblock = reinterpret_cast<INFOBLCOK*>(_current);
	infoblock->isusing = HeapManager::infoisnotusing;
	infoblock->size = HeapSize - sizeof(INFOBLCOK) - 1; //no guard 1 byte for end

	_current = _movePointerForward(_current, sizeof(INFOBLCOK));
	memset(_current, HeapManager::fillinitialfilled, infoblock->size);
	_current = _movePointerForward(_current, infoblock->size);
	memset(_current, HeapManager::fillguard, guardsize);
	_current = _movePointerForward(_current, guardsize);
	char* end = reinterpret_cast<char*>(_current); // it could be uint_8 since only one byte for this info
	*end = HeapManager::infoend;
}
#endif
#if _DEBUGACTIVITE
void HeapManager::InitializeWith(size_t HeapSize, unsigned int numDescriptors, void * _pHeapMemeoy)
{
	this->_sizeHeap = HeapSize;
	this->_numDescriptors = numDescriptors;
	this->_pHeapMemory = _pHeapMemeoy;
	//memset(_pHeapMemeoy, '\0', HeapSize);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "The memory block Start at%p", _pHeapMemeoy);
	_current = _pHeapMemeoy;
	INFOBLCOK* infoblock = reinterpret_cast<INFOBLCOK*>(_current);
	memset(&(infoblock->start), HeapManager::fillguard, 4);
	memset(&(infoblock->end), HeapManager::fillguard, 4);
	infoblock->isusing = HeapManager::infoisnotusing;
	infoblock->size = HeapSize - sizeof(INFOBLCOK) - guardsize - 1; // start with infroblock end with guards

	_current = _movePointerForward(_current, sizeof(INFOBLCOK));
	memset(_current, HeapManager::fillinitialfilled, infoblock->size);
	_current = _movePointerForward(_current, infoblock->size);
	memset(_current, HeapManager::fillguard, guardsize);
	_current = _movePointerForward(_current, guardsize);
	char* end = reinterpret_cast<char*>(_current);
	*end = HeapManager::infoend;
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _current);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "my info block have size %i", sizeof(INFOBLCOK));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "size_t have size %i", sizeof(size_t));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "char have size %i", sizeof(char));
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "start is %s", infoblock->start);
}
#else
void HeapManager::InitializeWith(size_t HeapSize, unsigned int numDescriptors, void * _pHeapMemeoy)
{
	this->_sizeHeap = HeapSize;
	this->_numDescriptors = numDescriptors;
	this->_pHeapMemory = _pHeapMemeoy;
	//memset(_pHeapMemeoy, '\0', HeapSize);
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "The memory block Start at%p", _pHeapMemeoy);
	_current = _pHeapMemeoy;
	INFOBLCOK* infoblock = reinterpret_cast<INFOBLCOK*>(_current);
	infoblock->isusing = HeapManager::infoisnotusing;
	infoblock->size = HeapSize - sizeof(INFOBLCOK) - 1; //no guard 1 byte for end

	_current = _movePointerForward(_current, sizeof(INFOBLCOK));
	memset(_current, HeapManager::fillinitialfilled, infoblock->size);
	_current = _movePointerForward(_current, infoblock->size);
	memset(_current, HeapManager::fillguard, guardsize);
	_current = _movePointerForward(_current, guardsize);
	char* end = reinterpret_cast<char*>(_current); // it could be uint_8 since only one byte for this info
	*end = HeapManager::infoend;
}
#endif
HeapManager::~HeapManager()
{
	if (_pHeapMemory) {
		delete _pHeapMemory;
	}
}

void * HeapManager::FindFirstFit(size_t size)
{
	return FindFirstFit(size, 4);
}

void * HeapManager::FindFirstFit(size_t size, unsigned int i_alignment)
{
	jump = 0;
	_current = _pHeapMemory;
	INFOBLCOK* current = reinterpret_cast<INFOBLCOK*>(_current);
	while (!(this->_Match(size, i_alignment))) {
		if (current->isusing != HeapManager::infoend && current->isusing != HeapManager::infoisusing && current->isusing != HeapManager::infoisnotusing) {
			DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Waring, "Gonna Go Wrong  %p \n", _current);
		}
		if (current->isusing == HeapManager::infoend) {
			return nullptr;
		}
		else
		{
			_current = _TravelToNextDescriptor(current);
			jump++;
			current = reinterpret_cast<INFOBLCOK*>(_current);
		}
	}
	DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Log, "Allocated Block  %p \n", _current);
	return _current;
}

INFOBLCOK * HeapManager::_TravelToNextDescriptor(const INFOBLCOK* const i_ptr) const
{
	char* start = (char*)_movePointerForward(i_ptr, i_ptr->size + sizeof(INFOBLCOK));// lead to place after the users data
	int a = 0;
	while (*start == HeapManager::fillpadding) {
		start = (char*)_movePointerForward(start, 1);
	}
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER)
	if (*start != HeapManager::fillguard) {
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Waring, "Write on the Guard %p %p", i_ptr, start);
	}
#endif

	return (INFOBLCOK*)start;
}

void HeapManager::Collect()
{
	INFOBLCOK*  d_ptr = (INFOBLCOK*)_pHeapMemory;
	//the start of user info
	void*  i_ptr = _movePointerForward(d_ptr, sizeof(INFOBLCOK));
	while (contains(i_ptr)) {
		if (d_ptr->isusing == HeapManager::infoisnotusing) {
			_current = _TravelToNextDescriptor(d_ptr);
			if (((INFOBLCOK*)_current)->isusing == HeapManager::infoend) {
				return;
			}
			void* next = _TravelToNextDescriptor((INFOBLCOK*)_current);
			if (_tryFastBackCollect()) {
				d_ptr->size = difference(i_ptr, next);
			}
			else {
				d_ptr = (INFOBLCOK*)next;
				i_ptr = _movePointerForward(d_ptr, sizeof(INFOBLCOK));
			}

		}
		else {
			d_ptr = _TravelToNextDescriptor(d_ptr);
			i_ptr = _movePointerForward(d_ptr, sizeof(INFOBLCOK));
		}

	}
}
void HeapManager::ShowFreeBlocks() const
{
	INFOBLCOK* current = (INFOBLCOK*)_pHeapMemory;
	int count = 0;
	while (current->isusing != HeapManager::infoend) {
		if (current->isusing == HeapManager::infoisnotusing) {
			DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Log, "Free Block %i has size %u \n", count, current->size);
			count++;
		}
		current = _TravelToNextDescriptor(current);
	}
	return;
}
void HeapManager::ShowOutstandingAllocations() const
{
	INFOBLCOK* current = (INFOBLCOK*)_pHeapMemory;
	int count = 0;
	while (current->isusing != HeapManager::infoend) {
		if (current->isusing == HeapManager::infoisusing) {
			DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Log, "OUtStanding Block %i has size %u \n", count, current->size);
			count++;
		}
		current = _TravelToNextDescriptor(current);
	}
	return;
}
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER)
void HeapManager::_FreeCheck(void* ipr)
{
	INFOBLCOK* temp = (INFOBLCOK*)_movePointerBackward(ipr, sizeof(INFOBLCOK));
	INFOBLCOK* tempnext = (INFOBLCOK*)_TravelToNextDescriptor(temp);
	for (int i = 0; i < 4; i++) {
		if (temp->start[i] != HeapManager::fillguard || temp->end[i] != HeapManager::fillguard || tempnext->start[i] != HeapManager::fillguard) {
			DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Waring, "Write on the Fill Guard %p", ipr);
		}
	}
}
#endif
bool HeapManager::free(void * i_ptr)
{
	bool result = false;
	if (IsAllocated(i_ptr)) {
		_current = _movePointerBackward(i_ptr, sizeof(INFOBLCOK));
		INFOBLCOK* temp = (INFOBLCOK*)_current;
		temp->isusing = HeapManager::infoisnotusing;
		result = true;
		DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Log, "Free Block %p \n", _current);
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER)
		_FreeCheck(i_ptr);
#endif
		_current = _TravelToNextDescriptor(temp);// move to the next dicriptor
		if (((INFOBLCOK*)_current)->isusing != HeapManager::infoend) {
			void* next = _TravelToNextDescriptor((INFOBLCOK*)_current);
			if (_tryFastBackCollect()) {
				temp->size = difference(i_ptr, next);;
			}
		}

	}

	return result;
}
bool HeapManager::_tryFastBackCollect()
{
	INFOBLCOK* temp = (INFOBLCOK*)_current;
	if (temp->isusing == HeapManager::infoisnotusing) {
		_deletHead();
		return true;
	}
	return false;
}

void HeapManager::_deletHead()
{
	INFOBLCOK* temp = (INFOBLCOK*)_current;
	memset(_current, HeapManager::fillinitialfilled, sizeof(INFOBLCOK));
}
bool HeapManager::contains(void * ipr) const
{
	bool result = true;
	void* _current = _movePointerBackward(ipr, sizeof(INFOBLCOK));
	INFOBLCOK* temp = (INFOBLCOK*)_current;
	int count = 0;
	if (temp->isusing != HeapManager::infoisusing &&temp->isusing != HeapManager::infoisnotusing) {
		return false;
	}
	while (count < 2) {
		count++;
		if (temp->isusing == HeapManager::infoend) {
			break;
		}
		else if (temp->isusing != HeapManager::infoisusing && temp->isusing != HeapManager::infoisnotusing) {
			result = false;
			break;
		}
	}
	return result;
}

bool HeapManager::IsAllocated(void * ipr) const
{
	if (contains(ipr)) {
		void* _current = _movePointerBackward(ipr, sizeof(INFOBLCOK));
		INFOBLCOK* temp = (INFOBLCOK*)_current;
		if (temp->isusing == HeapManager::infoisusing) {
			return true;
		}
	}
	return false;
}




void HeapManager::SetPointerTo(void * _pHeapMemeoy)
{
	this->_pHeapMemory = _pHeapMemeoy;
}

void* HeapManager::_movePointerForward(const void const * _pointer, int number)
{
	size_t address = reinterpret_cast<size_t>(_pointer);
	address += number;
	return reinterpret_cast<void*>(address);
}
void* HeapManager::_movePointerBackward(const void const * _pointer, int number)
{
	size_t address = reinterpret_cast<size_t>(_pointer);
	address -= number;
	return reinterpret_cast<void*>(address);
}
size_t HeapManager::difference(void * one, void * two)
{
	size_t address1 = reinterpret_cast<size_t>(one);
	size_t address2 = reinterpret_cast<size_t>(two);
	if (address1 > address2) {
		return address1 - address2;
	}
	else
	{
		return address2 - address1;
	}
}

bool HeapManager::_Match(size_t size, unsigned int alignment)
{
	INFOBLCOK* current = reinterpret_cast<INFOBLCOK*>(_current);
	if ((current->size > size + sizeof(INFOBLCOK)) && current->isusing == HeapManager::infoisnotusing) {
		return _TryCut(size, alignment);
	}
	else {
		return false;
	}

}


bool HeapManager::_TryCut(size_t size, unsigned int alignment)
{
	INFOBLCOK* current = reinterpret_cast<INFOBLCOK*>(_current);
	INFOBLCOK* endinfo = _TravelToNextDescriptor(current);
	size_t realsize = difference(current, endinfo);
	realsize -= sizeof(INFOBLCOK);
	size_t end = reinterpret_cast<size_t>(endinfo);
	end -= size;
	size_t padding = end % alignment;
	//If the real size of the block can not put the size + alignment + padding
	if (realsize < size + padding + sizeof(INFOBLCOK) * 2) {
		return false;
	}
	else
	{
		end -= padding;
		_current = reinterpret_cast<void*>(end);
		void* temppointer = _movePointerForward(_current, size);
		memset(temppointer, HeapManager::fillpadding, padding);
		memset(_current, HeapManager::fillinitialfilled, size);
		_current = _movePointerBackward(_current, sizeof(INFOBLCOK));
		_addinfoblock(size);
		size_t output = current->size;
		current->size = realsize - (size + padding + sizeof(INFOBLCOK));
		if (current->size > output) {
			DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Waring, "Wrong Size At %p is used to have length %u", current, output);
		}
		/*
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
			size_t output = current->size;
			current->size -= size + temp + sizeof(INFOBLCOK);
			if (current->size > output ) {
				DEBUG_PRINT(GStar::LOGPlatform::Console, GStar::LOGType::Waring, "Wrong Size At %p is used to have length %u", current,output);
			}
		}*/
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
}

void * operator new(size_t i_size)
{
	if (!HeapManager::GeneralHeap) {
		HeapManager::GeneralHeap = malloc(GENERALHEAPSIZE);
		HeapManager::Instance().InitializeWith(GENERALHEAPSIZE, GENERALHEAPSIZE, HeapManager::GeneralHeap);
	}
	HeapManager::Instance().SetPointerTo(HeapManager::GeneralHeap);
	return HeapManager::Instance().FindFirstFit(i_size);
}

void operator delete(void * i_ptr)
{
	if ((rand() % 1000) == 0) {
		HeapManager::Instance().SetPointerTo(HeapManager::GeneralHeap);
		HeapManager::Instance().free(i_ptr);
		HeapManager::Instance().Collect();
	}
	else {
		HeapManager::Instance().free(i_ptr);
	}
}