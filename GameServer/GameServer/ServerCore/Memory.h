#pragma once
#include "Allocator.h"

class MemoryPool;

/*---------------
	Memory
-----------------*/

class Memory
{
	enum
	{
		// �޸𸮰� Ŭ���� ���� Ȯ���� ����.
		POOL_COUNT = (1024 / 32) + (1024 / 128) + (2048 / 256),
		MAX_ALLOC_SIZE = 4096
	};

public:
	Memory();
	~Memory();

	void*	Allocate(int32 size);
	void	Release(void* ptr);

private:
	vector<MemoryPool*> _pools;

	MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];

};

template<typename Type, typename... Args>
Type* xnew(Args&&... args)
{
	// �޸� �Ҵ��� �س���.
	Type* obj = static_cast<Type*>(Xalloc(sizeof(Type)));

	// ������ ���� �ش� �޸𸮿� �����ڸ� ȣ���Ͽ� �������Է�.
	// placement new
	new(obj) Type(std::forward<Args>(args)...);


	return obj;
}

template<typename Type>
void xdelete(Type* obj)
{
	obj->~Type();
	Xrelease(obj);
}

