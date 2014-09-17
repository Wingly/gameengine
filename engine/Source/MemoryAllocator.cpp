#include <engine/Include/MemoryAllocator.h>

MemoryAllocator::MemoryAllocator()
{

}

MemoryAllocator::~MemoryAllocator()
{

}

MemStack* MemoryAllocator::CreateStack(unsigned int p_stacksize)
{
	return new MemStack(p_stacksize);
}