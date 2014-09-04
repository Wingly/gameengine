#pragma onnce

#include <engine/Include/Pool.h>
#include <stdlib.h>

class MemoryObject
{
public:
	MemoryObject(){};
	~MemoryObject(){};
	
	/*
	void* operator new(size_t nbytes)
	{
		if (nbytes == 0)
			nbytes = 1;						// so all alloc's get a distinct address
		void* ans = malloc(nbytes + 4);		// overallocate by 4 bytes
//		*(Pool**)ans = NULL;				// use NULL in the global new
		return (char*)ans + 4;				// don't let users see the Pool*
	}
	*/	

	void* operator new(size_t nbytes, Pool& pool)
	{
		if (nbytes == 0)
			nbytes = 1;							// so all alloc's get a distinct address
		void* ans = pool.alloc(nbytes + 4);		// overallocate by 4 bytes
		*(Pool**)ans = &pool;					// put the Pool* here
		return (char*)ans + 4;					// don't let users see the Pool*
	}

	void operator delete(void* p)
	{
		if (p != NULL) {
			p = (char*)p - 4;				// back off to the Pool*
		Pool* pool = *(Pool**)p;
		if (pool == NULL)
			free(p);						// note: 4 bytes left of the original p
		else
			pool->dealloc(p);				// note: 4 bytes left of the original p
		}
	}
};