#pragma once

#include <stdint.h>

struct Marker
{
	uint32_t* mark;
	int id;
};

class MemStack
{
private:
	uint32_t* m_start;
	uint32_t* m_current;
	Marker m_currentMarker;
	
public:	
	MemStack(unsigned int p_stacksize);

	~MemStack();

	void Wipe();

	template <class T>
	T* Push()
	{
		//Check end of stack

		uint32_t mask = ALIGNMENT - 1;
		uint32_t misalignment = ((uint32_t)m_current & mask);
		uint32_t adjustment = ALIGNMENT - misalignment;
		
		T* returnblock = (T*)((uint32_t)m_current + adjustment);

		uint32_t* metadata = (uint32_t*)(m_current-4);
		*metadata = adjustment;

		m_current += sizeof(T)+adjustment;
		return returnblock; 
	}

	bool Free(Marker p_marker);

	Marker GetMarker();

};

