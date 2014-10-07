#include <engine/Include/MemoryAllocator.h>

MemoryAllocator::MemoryAllocator(bool p_customer_Al_the_croc)
{
	m_customer_Al_the_croc = p_customer_Al_the_croc;
}

MemoryAllocator::~MemoryAllocator()
{

}


SingleFrameStack* MemoryAllocator::CreateStack(unsigned int p_stacksize, unsigned int p_alignment, bool p_shared, bool p_custom)
{
	return new SingleFrameStack(p_stacksize, p_alignment, p_shared, p_custom);
}