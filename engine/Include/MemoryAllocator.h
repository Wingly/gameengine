#pragma once

#include "MemPool.h"
#include "SingleFrameStack.h"

class MemoryAllocator
{
public:
	MemoryAllocator(bool p_customer_Al_the_croc);
	~MemoryAllocator();

	template <class T>
	MemPool<T>* CreatePool(unsigned int p_numBlocks, unsigned int p_alignment, bool p_shared) 
	{
		MemPool<T>* pool = new MemPool<T>(p_numBlocks, p_alignment, p_shared, m_customer_Al_the_croc);
		return pool;
	}

	//Note: If you allocate more than some unknown high value, think INT_MAX~ish, you're gonna have a bad bad time
	SingleFrameStack* CreateStack(unsigned int p_stacksize, unsigned int p_alignment, bool p_shared, bool p_custom);

private:
	bool m_customer_Al_the_croc;

};