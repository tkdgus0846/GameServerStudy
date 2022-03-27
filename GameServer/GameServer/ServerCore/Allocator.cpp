#include "pch.h"
#include "Allocator.h"
#include "Memory.h"

void* BaseAllocator::Alloc(int32 size)
{
	return ::malloc(size);
}

void BaseAllocator::Release(void* ptr)
{
	::free(ptr);
}

void* StompAllocator::Alloc(int32 size)
{
	const int64 pageCount = (size + PAGE_SIZE - 1) / PAGE_SIZE;
	const int64 offset = pageCount * PAGE_SIZE - size;
	void* baseAddress = ::VirtualAlloc(nullptr, pageCount * PAGE_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	
	// 여기서 int8* 로 캐스팅 해주는 이유는 포인터의 연산이 1바이트씩 이뤄지게 하기 위함이다.(+연산)
	return static_cast<void*>(static_cast<int8*>(baseAddress) + offset);
}

void StompAllocator::Release(void* ptr)
{
	// reinterpret_cast를 해주는 이유는 포인터형(32bits, 64bits) 에서 자료를 담는 바구니로 바꾸려고 하기때문에 강제 형변화가 필요하기 때문이다.
	const int64 baseAddress = reinterpret_cast<int64>(ptr);
	const int64 address = baseAddress - (baseAddress % PAGE_SIZE);
	::VirtualFree(reinterpret_cast<void*>(address), 0, MEM_RELEASE);
}

/*-------------------
	PoolAllocator
-------------------*/

void* PoolAllocator::Alloc(int32 size)
{
	return GMemory->Allocate(size);
}

void PoolAllocator::Release(void* ptr)
{
	GMemory->Release(ptr);
}
