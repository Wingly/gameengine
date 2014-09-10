#include "engine\Include\MemStack.h"
#include <stdlib.h>
MemStack::MemStack(unsigned stacksize)
{
	m_start = malloc(stacksize);
	m_current = m_start;
}


MemStack::~MemStack()
{
	//delete all
}

void MemStack::PopAll()
{
	//pointer gonna be annoying

}

