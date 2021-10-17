#pragma once

#define UNICODE
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

typedef unsigned char uint8;
typedef signed char int8;

typedef unsigned short uint16;
typedef signed short int16;

typedef unsigned int uint32;
typedef signed int int32;

typedef unsigned long long int uint64;
typedef signed long long int int64;

#define align_page(x) (x + x%0x1000llu) // 0x1000 = 4K Windows pagesizes are 4K in size
#define KB 1024llu
#define MB KB*1024llu
#define GB MB*1024llu

enum MemoryBlogFlags
{
	MEMORY_FREE = 0x0,
	MEMORY_ALLOCATED = 0x1
};

struct MemoryBlock;

struct MemoryBlockHeader
{
	MemoryBlock* prev;
	MemoryBlock* next;
	MemoryBlogFlags flags;
};

struct MemoryBlock
{
	MemoryBlockHeader header;
	uint8* memory;
};

//note(tiago): to access the header we just need to walk back from the pointer by the header size so the start of the header is ptr - sizeof(MemoryBlockHeader)

class MemAllocator
{
public:
	uint64 backstore_size = align_page(1*GB);
	uint8* backstore = nullptr;
	MemoryBlock* first_block;

	MemAllocator();
	~MemAllocator();

	void PrintBlocks() const;
};

