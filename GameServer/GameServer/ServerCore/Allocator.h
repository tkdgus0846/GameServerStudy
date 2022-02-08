#pragma once

/* --------------------
	  Base Allocator
-----------------------*/

class BaseAllocator
{
public:
	static void* Alloc(int32 size);
	static void Release(void* ptr);
};

/* --------------------
	  Stomp Allocator
-----------------------*/

// StompAllocator의 장점..? 
/*
	기존의 malloc, free 방식의 문제점을 잡을 수 있다. free를 해도 해당 힙영역의 데이터를 조작할 수 있다는 문제점이 있었는데, ViurtalAllocFree를 이용해 조작할 수 없게한다.
	한마디로 데이터 오염 방지에 유리하다고 볼 수 있다.
*/
class StompAllocator
{
enum {PAGE_SIZE = 0x1000};
public:
	static void* Alloc(int32 size);
	static void Release(void* ptr);
};

/* --------------------
	  STL Allocator
-----------------------*/

template<typename T>
class StlAllocator
{
public:
	using value_type = T;
	StlAllocator() {}

	template<typename Other>
	StlAllocator(const StlAllocator<Other>&) {}

	T* allocate(size_t count)
	{
		const int32 size = static_cast<int32>(count * sizeof(T));
		return static_cast<T*>(Xalloc(size));
	}

	void deallocate(T* ptr, size_t count)
	{
		Xrelease(ptr);
	}
};



