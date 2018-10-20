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

HeapManager::~HeapManager()
{
	delete _pHeapMemory;
}

void * HeapManager::FindFirstFit(rsize_t size)
{
	return FindFirstFit(size,4);
}

void * HeapManager::FindFirstFit(rsize_t size, unsigned int i_alignment)
{
	_current = _pHeapMemory;
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _current);
	INFOBLCOK* current = reinterpret_cast<INFOBLCOK*>(_current);
	while (!(this->_Match(size,i_alignment))) {
		_Travel();
		if (current->isusing == HeapManager::infoend) {
			return nullptr;
		}
	}
	DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Log, "%p", _current);
	return _current;
}

#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER)
void HeapManager::_FreeCheck(void* ipr)
{
	INFOBLCOK* temp = (INFOBLCOK*)_movePointerBackward(ipr, INFOSIZE);
	INFOBLCOK* tempnext = (INFOBLCOK*)_TravelToNextDescriptor(temp);
	for (int i = 0; i < 4; i++) {
		if (temp->start[i] != HeapManager::fillguard || temp->end[i] != HeapManager::fillguard|| tempnext->start[i] != HeapManager::fillguard || tempnext->end[i] != HeapManager::fillguard) {
			DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Error, "Write on the Fill Guard %p", ipr);
		}
	}
}
#endif
INFOBLCOK * HeapManager::_TravelToNextDescriptor(INFOBLCOK * i_ptr)
{
	char* start = (char*)_movePointerForward(i_ptr, i_ptr->size+ INFOSIZE);// lead to place after the users data
	while (*start == HeapManager::fillpadding) {
		start = start++;
	}
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER)
	if (*start != HeapManager::fillguard) {
		DEBUG_PRINT(GStar::LOGPlatform::Output, GStar::LOGType::Error, "Write on the Guard %p", i_ptr);
	}
#endif

	return (INFOBLCOK*)start;
}

void HeapManager::Collect()
{
	INFOBLCOK*  d_ptr= (INFOBLCOK*)_pHeapMemory;
	//the start of user info
	void*  i_ptr= _movePointerForward(d_ptr, INFOSIZE);
	while (contains(i_ptr)) {
		if (d_ptr->isusing == HeapManager::infoisnotusing) {
			_current = _TravelToNextDescriptor(d_ptr);
			void* next = _TravelToNextDescriptor((INFOBLCOK*)_current);
			if (_tryFastBackCollect()) {
				d_ptr->size = difference(i_ptr, next);
			}
			else {
				d_ptr = (INFOBLCOK*)next;
				i_ptr = _movePointerForward(d_ptr, INFOSIZE);
			}
		}
		else {
			d_ptr = _TravelToNextDescriptor(d_ptr);
			i_ptr = _movePointerForward(d_ptr, INFOSIZE);
		}
		
	}
}
bool HeapManager::free(void * i_ptr)
{
	if (IsAllocated(i_ptr)) {
		_current = _movePointerBackward(i_ptr, INFOSIZE);
		INFOBLCOK* temp = (INFOBLCOK*)_current;
		temp->isusing = HeapManager::infoisnotusing;
#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_HEAPMANAGER)
		_FreeCheck(i_ptr);
#endif
		_current = _TravelToNextDescriptor(temp);// move to the next dicriptor
		void* next = _TravelToNextDescriptor((INFOBLCOK*)_current);
		if (_tryFastBackCollect()) {
			temp->size = difference(i_ptr,next);
		}

	}

	return false;
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
	memset(_current, HeapManager::fillinitialfilled, INFOSIZE);
}
bool HeapManager::contains(void * ipr) const
{
	bool result = true;
	void* _current = _movePointerBackward(ipr, INFOSIZE);
	INFOBLCOK* temp = (INFOBLCOK*)_current;
	int count = 0;
	if (temp->isusing != HeapManager::infoisusing &&temp->isusing != HeapManager::infoisnotusing) {
		return false;
	}
	while(count < 2){
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
		void* _current = _movePointerBackward(ipr, INFOSIZE);
		INFOBLCOK* temp = (INFOBLCOK*)_current;
		if (temp->isusing == HeapManager::infoisusing) {
			return true;
		}
	}
	return false;
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
size_t HeapManager::difference(void * one, void * two)
{
	unsigned long address1 = reinterpret_cast<unsigned long>(one);
	unsigned long address2 = reinterpret_cast<unsigned long>(two);
	if (address1 > address2) {
		return address1 - address2;
	}
	else
	{
		return address2 - address1;
	}
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

