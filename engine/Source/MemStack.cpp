#include "engine\Include\MemStack.h"
#include <stdlib.h>
MemStack::MemStack(unsigned stacksize)
{
	m_start = (uint32_t*)malloc(stacksize);
	m_current = m_start;
	m_currentMarker.mark = m_current;
	m_currentMarker.id = 0;
}


MemStack::~MemStack()
{
	//delete all

}

void MemStack::Wipe()
{
	m_current = m_start;
}

bool MemStack::Free( Marker p_marker )
{
	if(m_currentMarker.id - p_marker.id > 1)
	{
		m_currentMarker = p_marker;
		m_current = m_currentMarker.mark;
		return true;
	}
	else
		return false;
}

Marker MemStack::GetMarker()
{
	return m_currentMarker;
}

