#pragma once

class MemStack
{
private:
	void* m_start;
	void* m_current;

public:	
	MemStack(unsigned int stacksize);

	~MemStack();

	void PopAll();

	template <class T>
	T* PushObject()
	{
		T* returnblock = m_nextBlock;
		m_nextBlock += sizeof(T);
		return returnblock; 
	}
};

