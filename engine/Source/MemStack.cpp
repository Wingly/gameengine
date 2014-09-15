#include "engine\Include\MemStack.h"
#include <stdlib.h>
MemStack::MemStack(unsigned stacksize)
{
	m_start = (uint32_t*)malloc(stacksize);
	m_current = m_start;
}


MemStack::~MemStack()
{
	//delete all

}

void MemStack::Wipe()
{
	m_current = m_start;
}

