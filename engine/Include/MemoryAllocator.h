#pragma once

#include "MemPool.h"
#include "MemStack.h"

class MemoryAllocator
{
public:
	MemoryAllocator();
	~MemoryAllocator();

	template <class T>
	MemPool<T>* CreatePool(unsigned int p_numBlocks, unsigned int p_alignment) 
	{
		MemPool<T>* pool = new MemPool<T>(p_numBlocks, p_alignment);
		return pool;
	}
	MemStack* CreateStack(unsigned int p_stacksize, unsigned int p_alignment);

};