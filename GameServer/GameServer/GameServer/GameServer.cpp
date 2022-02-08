#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include "RefCounting.h"
#include "Memory.h"

class Player
{
public:
	Player() {}
	~Player() {}
};

class Knight : public Player
{
public:
	Knight() : _hp(0) {}
	Knight(int32 hp) : _hp(hp) {}

	/*static void* operator new(size_t size)
	{
		void* ptr = ::malloc(size);
		return ptr;
	}
	static void operator delete(void* obj)
	{
		::free(obj);
	}*/

	int32 _hp;
};

int main()
{	
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);


}