#pragma once

#include <stdint.h>
#include <mutex>
/*
struct Marker
{
	uint32_t* mark;
	int id;
};*/

class MemStack
{
private:
	uint32_t* m_start;
	uint32_t m_size;
	uint32_t* m_current;
	//Marker m_currentMarker;
	uint32_t m_alignment;
	std::mutex m_lock;
	
public:	
	MemStack(unsigned int p_stacksize, unsigned p_alignment);

	~MemStack();

	void Wipe();

	template <class T>
	T* Push()
	{
		
		m_lock.lock();
		uint32_t mask = m_alignment - 1;
		uint32_t misalignment = ((uint32_t)m_current & mask);
		uint32_t adjustment = m_alignment - misalignment;
		
		T* returnblock = (T*)((uint32_t)m_current + adjustment);

		uint32_t* metadata = (uint32_t*)(m_current-4);
		*metadata = adjustment;
		//Check end of stack
		m_current += sizeof(T)+adjustment;
		m_lock.unlock();
		return returnblock; 
	}

	//bool Free(Marker p_marker);

	//Marker GetMarker();

};

