#pragma once
#include "Allocator.h"

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

