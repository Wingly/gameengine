#pragma once

#include <stdint.h>

struct Marker
{
	uint32_t* mark;
	int id;
};

static const unsigned int ALIGNMENT = 16;
class MemStack
{
private:
	uint32_t* m_start;
	uint32_t* m_current;
	Marker m_currentMarker;
	
public:	
	MemStack(unsigned int stacksize);

	~MemStack();

	void Wipe();

	template <class T>
	T* Push()
	{
		//Check end of stack
		uint32_t mask = ALIGNMENT - 1;
		uint32_t misalignment = (*m_current & mask);
		uint32_t adjustment = ALIGNMENT - misalignment;
		
		T* returnblock = *m_current + adjustment;

		uint32_t* metadata = (uint32_t*)(m_current-4);
		*metadata = adjustment;

		m_current += sizeof(T+adjustment);
		return returnblock; 
	}

	bool Free(Marker p_marker);

	Marker GetMarker();

};

