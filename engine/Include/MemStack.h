#pragma once

#include <stdint.h>
#include <atomic>
/*
struct Marker
{
	uint32_t* mark;
	int id;
};*/

#include <iostream>
namespace
{
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
}
class MemStack
{
private:
	size_t* m_start;
	size_t m_size;
	size_t* m_current;
	//Marker m_currentMarker;
	size_t m_alignment;
	//std::atomic_flag m_lock =  ATOMIC_FLAG_INIT;
	std::atomic_flag m_lock;
	
	
public:	
	MemStack(unsigned int p_stacksize, unsigned p_alignment);

	~MemStack();

	void Wipe();

	template <class T>
	T* Push()
	{

		while(m_lock.test_and_set(std::memory_order_acquire))
		{
			std::cout << "This should not happen in this version";
			//Keep on spinning in the free world
		}
		size_t mask = m_alignment - 1;
		size_t misalignment = ((size_t)m_current & mask);
		size_t adjustment = m_alignment - misalignment;
		
		T* returnblock = (T*)(m_current /*+ adjustment*/);
		
		int i = sizeof(T);
		int j = m_size;
		/*uint32_t* metadata = (uint32_t*)((uint32_t)returnblock - 4);
		*metadata = adjustment;*/
		//Check end of stack
		
		i = i + (size_t)m_current;
		m_current = (size_t*)i;/*+adjustment;*/
		m_lock.clear(std::memory_order_release);
		return returnblock; 
	}

	//bool Free(Marker p_marker);

	//Marker GetMarker();

};
