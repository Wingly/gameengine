#pragma once

#include <stdint.h>
#include <atomic>
#include <iostream>
namespace
{
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
}
class SingleFrameStack
{
private:
	size_t* m_start;
	size_t m_size;
	size_t* m_current;
	//Marker m_currentMarker;
	unsigned m_nonCustomMemFinder;
	//std::atomic_flag m_lock =  ATOMIC_FLAG_INIT;
	std::atomic_flag m_lock;
	
	bool m_shared;
	bool m_custom;
public:	
	SingleFrameStack(unsigned int p_stacksize, bool p_shared, bool p_custom);

	~SingleFrameStack();

	void Wipe();

	template <class T>
	T* Push(unsigned p_alignment)
	{
		if(m_custom)
		{
			while(m_shared && m_lock.test_and_set(std::memory_order_acquire))
			{
				//Keep on spinning in the free world
			}
			
			size_t mask = p_alignment - 1;
			size_t misalignment = ((size_t)m_current & mask);
			size_t adjustment = p_alignment - misalignment;

			
			if(((size_t)m_current + (size_t)adjustment + sizeof(T)) >= ((size_t)m_start + (size_t)m_size))
			{
				m_lock.clear();
				return nullptr;
			}

			T* returnblock = (T*)((size_t)m_current + adjustment);
		
			int i = sizeof(T);
			int j = m_size;
			char* metadata = (char*)((size_t)returnblock-1);
			*metadata = static_cast<char>(adjustment);
			//Check end of stack
		
			i = i + (size_t)m_current;
			m_current = (size_t*)(i + adjustment);
			m_lock.clear(std::memory_order_release);
			return returnblock; 
		}
		else
		{
			m_nonCustomMemFinder+= sizeof(T);
			if(m_nonCustomMemFinder < m_size)
				return new T();
			else
				return nullptr;
		}
	}
	

	//bool Free(Marker p_marker);

	//Marker GetMarker();

};
