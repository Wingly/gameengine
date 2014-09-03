#pragma once

template <class T>
class MemPool
{
public:
	
	MemPool(unsigned p_numBlocks, unsigned p_sizeOfBlock) 
	{
		m_block = (T*)malloc(p_numBlocks*p_sizeOfBlock);
		m_nextBlock = m_block;
	}

	T* getFreeBlock()
	{
		T* returnblock = m_nextBlock;
		m_nextBlock += sizeof(T);
		return returnblock; 
	}

	~MemPool()
	{
	}

	T* m_block;
	T* m_nextBlock;
};

