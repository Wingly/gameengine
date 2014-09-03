#pragma once

class Block
{
public:
	Block() {};
	~Block() {};
	void* m_prev;
	void* m_next;
};

template <class T>
class MemPool
{
private:
	// Startpointer
	void* m_start;

	void* m_firstFree;
	void* m_lastFilled;

	unsigned int m_numBlocks;
	unsigned int m_sizeOfBlock;

public:
	
	MemPool(unsigned p_numBlocks, unsigned p_sizeOfBlock) 
	{
		m_numBlocks = p_numBlocks;
		m_sizeOfBlock = p_sizeOfBlock;

		m_start = malloc(p_numBlocks * p_sizeOfBlock);
		m_firstFree = m_block;
		m_lastFilled = nullptr;

		Block* local = (Block*)m_firstFree;
		for(unsigned int i = 0; i < p_numBlocks-1; i++)
		{
			local->m_next = local + p_sizeOfBlock;

		}
		local->m_next = m_firstFree;
	}

	~MemPool()
	{
	}
	
	T* getFreeBlock()
	{
		T* local = (T*)m_firstFree;

		Block* newFirstFree	= dymamic_cast<Block*>(m_firstFree->m_next);		// Get next block that is supposed to be first.
		Block* prev			= dymamic_cast<Block*>(local->m_prev);

		// Update prev	
		newFirstFree->m_prev = prev;

		// Update previous block's next pointer
		prev->m_next = first;

		//
		(Block*)m_lastFilled->m_next->m_prev			= (Block*)local; // 
		(Block*)m_lastFilled->m_next					= (Block*)local;

		//
		(Block*)local->m_prev = (Block*)m_lastFilled;
		(Block*)local->m_next = (Block*)m_start;

		return local;
	}
};
