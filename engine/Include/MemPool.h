#pragma once

#include <stdint.h>

#include <atomic>

static const unsigned int FREE_TO_LAST = 1;
template <class T>
class MemPool
{

private:
	// Startpointer
	size_t* m_start;

	size_t* m_firstFree;
	size_t* m_last;
	std::atomic_flag m_lockFirst;
	std::atomic_flag m_lockFirstLast;
	unsigned int m_numBlocks;
	unsigned int m_alignment;
	unsigned int m_sizeOfBlock;
	bool m_shared;
	bool m_custom;

public:
	MemPool(unsigned p_numBlocks, unsigned p_alignment, bool p_shared, bool p_custom)
	{
		m_numBlocks = p_numBlocks + 1;
		m_alignment = p_alignment;
		m_sizeOfBlock = sizeof(T);
		m_shared = p_shared;
		m_custom = p_custom;
		m_lockFirst.clear(); //Init the spinlock
		m_lockFirstLast.clear();
	}

	void init()
	{
		if(m_custom)
		{
			size_t* raw = (size_t*)malloc(m_numBlocks * m_sizeOfBlock + m_alignment);
			size_t mask = m_alignment - 1;

			size_t misalignment = (reinterpret_cast<size_t>(raw) & mask);
			size_t adjustment = m_alignment - misalignment;

			m_start = reinterpret_cast<size_t*>(reinterpret_cast<size_t>(raw) + adjustment);

			char* metadata = (char*)((size_t)m_start-1);
			*metadata = static_cast<char>(adjustment);
		
		
			m_firstFree = m_start;
		
			size_t* currentBlock = m_firstFree;
			for(unsigned int i = 0; i < m_numBlocks-1; i++)
			{
				size_t adress = (size_t)currentBlock; //get pointer adress as uint
				*currentBlock = (size_t)(adress + m_sizeOfBlock); //Save next block as uint in the currentBlock
				currentBlock = reinterpret_cast<size_t*>(*currentBlock); //Set currentBlock to next block		
			}
			//nyrad
			m_last = currentBlock;
			*currentBlock = NULL;
		}
	}
	~MemPool()
	{
		
			char* test = (char*)((size_t)m_start-1);
			size_t test2 = (size_t)(*test);
			void* deleteptr = (void*)((size_t)m_start - test2);
			free(deleteptr);
		
	}
	
	T* getBlock()
	{
		if(m_custom)
		{
			while(m_shared && m_lockFirst.test_and_set(std::memory_order_acquire) )
			{
				//keep on spinning in the free world!
			}
			if(m_firstFree == nullptr || m_last == m_firstFree)
			{
				m_lockFirst.clear();
				return nullptr;
			}
				
			T* local = (T*)m_firstFree;
			if(*m_firstFree != NULL)
				m_firstFree = (size_t*)*m_firstFree;
			else
				m_firstFree = nullptr; //No more memory now;
			m_lockFirst.clear(std::memory_order_release);
			return local;
		}
		else
			return new T();
	}

	void freeBlock(T* p_block)
	{
		if(m_custom)
		{
			if(FREE_TO_LAST)
			{
				while(m_shared && m_lockFirstLast.test_and_set(std::memory_order_acquire))
				{
					//keep on spinning in the free world!
				}
				size_t* block = (size_t*)p_block;
				*m_last = (size_t)block;
				m_last = block;
				*m_last = NULL;
				m_lockFirstLast.clear(std::memory_order_release);
			}
			else
			{
				while(m_shared && m_lockFirst.test_and_set(std::memory_order_acquire))
				{
					//keep on spinning in the free world!
				}
				size_t* block = (size_t*)p_block;
				*block = (size_t)m_firstFree;
				m_firstFree = block;
				m_lockFirst.clear(std::memory_order_release);
			}
		}
		else
			delete p_block;
	}
};
