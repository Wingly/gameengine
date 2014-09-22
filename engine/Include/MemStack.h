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
	uint32_t* m_start;
	uint32_t m_size;
	uint32_t* m_current;
	//Marker m_currentMarker;
	uint32_t m_alignment;
	//std::atomic_flag m_lock =  ATOMIC_FLAG_INIT;
	std::atomic_flag m_lock;
	
	
public:	
	MemStack(unsigned int p_stacksize, unsigned p_alignment);

	~MemStack();

	void Wipe();

	template <class T>
	T* Push(int id)
	{
		
		while(m_lock.test_and_set(std::memory_order_acquire))
		{
			std::cout << "Im locked :(  id: " << id << std::endl ;
			//Keep on spinning in the free world
		}
		std::cout << "doing work" << id << std::endl ;
		//m_lock.lock();
		uint32_t mask = m_alignment - 1;
		uint32_t misalignment = ((uint32_t)m_current & mask);
		uint32_t adjustment = m_alignment - misalignment;
		
		T* returnblock = (T*)((uint32_t)m_current + adjustment);
		int i = 0;
		while(i < 100000)
		{
			i++;
		}
		uint32_t* metadata = (uint32_t*)(m_current-4);
		*metadata = adjustment;
		//Check end of stack
		m_current += sizeof(T)+adjustment;
		std::cout << "Releasing lock" << id << std::endl ;
		m_lock.clear(std::memory_order_release);
		return returnblock; 
	}

	//bool Free(Marker p_marker);

	//Marker GetMarker();

};
