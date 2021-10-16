#include "MemAllocator.h"


MemAllocator::MemAllocator()
{
	this->backstore = (uint8*)VirtualAlloc(nullptr, this->backstore_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	DWORD error = GetLastError();

	this->backstore[0] = 1;
}

MemAllocator::~MemAllocator()
{

}