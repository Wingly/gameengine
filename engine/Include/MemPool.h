#pragma once

#include <stdint.h>

#include <atomic>

static const unsigned int FREE_TO_LAST = 1;
template <class T>
class MemPool
{

private:
	// Startpointer
	uint32_t* m_start;

	uint32_t* m_firstFree;
	uint32_t* m_last;
	std::atomic_flag m_lock;
	std::atomic_flag m_lock2;
	unsigned int m_numBlocks;
	unsigned int m_alignment;
	unsigned int m_sizeOfBlock;
	bool m_shared;

public:
	MemPool(unsigned p_numBlocks, unsigned p_alignment, bool p_shared)
	{
		m_numBlocks = p_numBlocks + 1;
		m_alignment = p_alignment;
		m_sizeOfBlock = sizeof(T);
		m_shared = p_shared;
		m_lock.clear(); //Init the spinlock
		m_lock2.clear();
	}

	void init()
	{
		uint32_t* raw = (uint32_t*)malloc(m_numBlocks * m_sizeOfBlock + m_alignment);
		uint32_t mask = m_alignment - 1;

		uint32_t misalignment = (reinterpret_cast<uint32_t>(raw) & mask);
		uint32_t adjustment = m_alignment - misalignment;

		m_start = reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(raw) + adjustment);

		uint32_t* metadata = (uint32_t*)(m_start-4);
		*metadata = adjustment;
		
		
		m_firstFree = m_start;
		
		uint32_t* currentBlock = m_firstFree;
		for(unsigned int i = 0; i < m_numBlocks-1; i++)
		{
			uint32_t adress = (uint32_t)currentBlock; //get pointer adress as uint
			*currentBlock = (uint32_t)(adress + m_sizeOfBlock); //Save next block as uint in the currentBlock
			currentBlock = reinterpret_cast<uint32_t*>(*currentBlock); //Set currentBlock to next block		
		}
		//nyrad
		m_last = currentBlock;
		*currentBlock = NULL;
	}
	~MemPool()
	{
	}
	
	T* getBlock()
	{
		while(m_lock.test_and_set(std::memory_order_acquire) && m_shared)
		{
			//keep on spinning in the free world!
		}
		if(m_firstFree == nullptr || m_last == m_firstFree)
		{
			std::cout << "POOL OUT OF MEMORY!!!!" << std::endl << " I have no clue how to tell you which pool it is, but i'm sure you'll be able to figure it out" 
					<< std::endl << "Also, you should really make some better sort of errorhandling for this";
			system("pause");
			//Inget ledigt minne!
		}
				
		T* local = (T*)m_firstFree;
		if(*m_firstFree != NULL)
			m_firstFree = (uint32_t*)*m_firstFree;
		else
			m_firstFree = nullptr; //No more memory now;
		m_lock.clear(std::memory_order_release);
		return local;
	}

	void freeBlock(T* p_block)
	{
		if(FREE_TO_LAST)
		{
			while(m_lock2.test_and_set(std::memory_order_acquire) && m_shared)
			{
				//keep on spinning in the free world!
			}
			uint32_t* block = (uint32_t*)p_block;
			*m_last = (uint32_t)block;
			m_last = block;
			m_lock2.clear(std::memory_order_release);
		}
		else
		{
			while(m_lock.test_and_set(std::memory_order_acquire) && m_shared)
			{
				//keep on spinning in the free world!
			}
			uint32_t* block = (uint32_t*)p_block;
			*block = (uint32_t)m_firstFree;
			m_firstFree = block;
			m_lock.clear(std::memory_order_release);
		}
	}
};
