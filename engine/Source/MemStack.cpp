#include "engine\Include\MemStack.h"
#include <stdlib.h>


MemStack::MemStack(unsigned p_stacksize, unsigned p_alignment, bool p_shared)
{
	m_size = p_stacksize;
	m_start = (uint32_t*)malloc(p_stacksize);
	m_current = m_start;
	m_alignment = p_alignment;
	m_lock.clear();
	m_shared = p_shared;
	//m_currentMarker.mark = m_current;
	//m_currentMarker.id = 0;
}


MemStack::~MemStack()
{
	//delete all

	//free(m_start);
}

void MemStack::Wipe()
{
	m_current = m_start;
}
/*
bool MemStack::Free( Marker p_marker )
{
	if(m_currentMarker.id == p_marker.id)
	{
		//pls align
		m_currentMarker.id--;
		m_current = m_currentMarker.mark;
		return true;
	}
	else
		return false;
}

Marker MemStack::GetMarker()
{
	m_currentMarker.mark = m_current;
	m_currentMarker.id++;
	return m_currentMarker;
}

*/