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
		// 메모리가 클수록 나올 확률이 적다.
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
	// 메모리 할당을 해놓음.
	Type* obj = static_cast<Type*>(Xalloc(sizeof(Type)));

	// 위에서 만든 해당 메모리에 생성자를 호출하여 데이터입력.
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

