#pragma once

#include "MemPool.h"
#include "MemStack.h"

class MemoryAllocator
{
public:
	MemoryAllocator();
	~MemoryAllocator();

	template <class T>
	MemPool<T>* CreatePool(unsigned int p_numBlocks) 
	{
		MemPool<T>* pool = new MemPool<T>(p_numBlocks);
		return pool;
	}
	//Note: If you allocate more than some unknown high value, think INT_MAX~ish, you're gonna have a bad bad time
	MemStack* CreateStack(unsigned int p_stacksize); 

};