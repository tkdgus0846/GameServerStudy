#pragma once
#include "Allocator.h"

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

