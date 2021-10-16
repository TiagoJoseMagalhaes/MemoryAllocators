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

struct MemoryBlock
{
	uint64 size;
	uint8* address;
	bool free = true;
};

class MemAllocator
{
public:
	uint64 backstore_size = align_page(16*GB);
	uint8* backstore = nullptr;

	MemAllocator();
	~MemAllocator();

};

