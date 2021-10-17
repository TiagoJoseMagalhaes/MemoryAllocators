#include "MemAllocator.h"

#include <iostream>

MemAllocator::MemAllocator()
{
	this->backstore = (uint8*)VirtualAlloc(nullptr, this->backstore_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	DWORD error = GetLastError();

	MemoryBlock* first_block = (MemoryBlock*)this->backstore;
	first_block->memory = this->backstore+sizeof(MemoryBlockHeader);
	first_block->header.next = nullptr;
	first_block->header.prev = nullptr;
	first_block->header.flags = MEMORY_FREE;

	this->first_block = first_block;
}

MemAllocator::~MemAllocator()
{
	VirtualFree(this->backstore, this->backstore_size, MEM_RELEASE);
}

void MemAllocator::PrintBlocks() const
{
	MemoryBlock* block = this->first_block;
	do
	{
		printf("------ Block Start ----------------------\n");
		printf("Block Start Address:\t\t0x%X\n", block);
		printf("Previous Block Start Address:\t0x%X\n", block->header.prev);
		printf("Next Block Start Address:\t0x%X\n", block->header.next);
		printf("Block Flags:\t\t\t0x%X\n", block->header.flags);
		printf("User Memory Region Address:\t0x%X\n", block->memory);
		printf("------ Block End ------------------------\n\n");

		block = block->header.next;
	} 
	while (block != nullptr);
}
