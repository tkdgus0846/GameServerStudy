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
	
	// ���⼭ int8* �� ĳ���� ���ִ� ������ �������� ������ 1����Ʈ�� �̷����� �ϱ� �����̴�.(+����)
	return static_cast<void*>(static_cast<int8*>(baseAddress) + offset);
}

void StompAllocator::Release(void* ptr)
{
	// reinterpret_cast�� ���ִ� ������ ��������(32bits, 64bits) ���� �ڷḦ ��� �ٱ��Ϸ� �ٲٷ��� �ϱ⶧���� ���� ����ȭ�� �ʿ��ϱ� �����̴�.
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
