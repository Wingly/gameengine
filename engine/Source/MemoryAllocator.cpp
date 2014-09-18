#include <engine/Include/MemoryAllocator.h>

MemoryAllocator::MemoryAllocator()
{

}

MemoryAllocator::~MemoryAllocator()
{

}

MemStack* MemoryAllocator::CreateStack(unsigned int p_stacksize, unsigned int p_alignment)
{
	return new MemStack(p_stacksize, p_alignment);
}