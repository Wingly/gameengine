#pragma once

template <class T>
class MemPool
{
private:
	// Startpointer
	void* m_start;

	void* m_firstFree;
	//void* m_lastFree;

	unsigned int m_numBlocks;
	unsigned int m_sizeOfBlock;

public:
	
	MemPool(unsigned p_numBlocks) 
	{
		m_numBlocks = p_numBlocks;
		m_sizeOfBlock = sizeof(T);

		m_start = malloc(p_numBlocks * m_sizeOfBlock);
		m_firstFree = m_start;
		//m_lastFree = nullptr;

		char** local = (char**)m_firstFree;
		for(unsigned int i = 0; i < p_numBlocks-1; i++)
		{
			*local = local + m_sizeOfBlock;
			local = local + m_sizeOfBlock;
		}
		*local = nullptr;
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
		m_firstFree = *m_firstFree;

		return local;
	}
};
