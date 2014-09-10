#pragma once

template <class T>
class MemPool
{
private:
	// Startpointer
	uint64_t* m_start;

	uint64_t* m_firstFree;

	unsigned int m_numBlocks;
	unsigned int m_sizeOfBlock;

public:
	
	MemPool(unsigned p_numBlocks) 
	{
		m_numBlocks = p_numBlocks;
		m_sizeOfBlock = sizeof(T);

		m_start = (uint64_t*)malloc(p_numBlocks * m_sizeOfBlock);
		m_firstFree = m_start;
		
		uint64_t* currentBlock = m_firstFree;
		for(unsigned int i = 0; i < p_numBlocks-1; i++)
		{
			uint64_t adress = (uint64_t)currentBlock; //get pointer adress as uint
			*currentBlock = (uint64_t)(adress + m_sizeOfBlock); //Save next block as uint in the currentBlock
			currentBlock = reinterpret_cast<uint64_t*>(*currentBlock); //Set currentBlock to next block		
		}
		currentBlock = nullptr;
	}

	~MemPool()
	{
	}
	
	T* getFreeBlock()
	{
		if(m_firstFree == nullptr)
		{
			//Inget ledigt minne!
		}
		T* local = (T*)m_firstFree;

		m_firstFree = reinterpret_cast<uint64_t*>(*m_firstFree);
		return local;
	}
};
