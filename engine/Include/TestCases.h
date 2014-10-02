#pragma once

namespace TestCases
{
	static const unsigned int nrOfRunsPerTest = 1000;

	// functionFlag 1
struct Pool
{
	unsigned int blockSize;		// in bytes
	unsigned int nrOfBlocks;	

	Pool() 
	{
		blockSize = 0;
		nrOfBlocks = 0;
	}

	Pool(unsigned int p_blockSize, unsigned int p_nrOfBlocks, unsigned int p_runTime) : blockSize(p_blockSize), nrOfBlocks(p_nrOfBlocks)
	{
	}
};

// functionFlag 2
struct Stack
{
	unsigned int stackSize; // In bytes
};

struct TestCase
{
	unsigned int functionFlag;
	unsigned int nrThreads;		// If using stack, make sure this count can divide 2000 
	unsigned int alignment;
	unsigned int runTime;	
	bool customAllocation;
	bool sharedMemory;
	Stack stack;
	Pool pool;
	char* m_fileName;
};

	inline TestCase GetTestCase(unsigned int index)
	{
		TestCase testCase;
		if(index >= nrOfRunsPerTest*0 && index < nrOfRunsPerTest*1)
		{
			testCase.functionFlag = 2;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.stack = Stack();
			testCase.stack.stackSize = 12000;
			testCase.runTime = 1400;
			testCase.customAllocation = false;
			testCase.sharedMemory = false;
			testCase.m_fileName = "Stack_noncustom_nonshared.txt";
		}
		else if(index >= nrOfRunsPerTest*1 && index < nrOfRunsPerTest*2)
		{
			testCase.functionFlag = 2;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.stack = Stack();
			testCase.stack.stackSize = 12000;
			testCase.runTime = 1400;
			testCase.customAllocation = true;
			testCase.sharedMemory = false;
			testCase.m_fileName = "Stack_custom_nonshared.txt";
		}
		else if(index >= nrOfRunsPerTest*2 && index < nrOfRunsPerTest*3)
		{
			testCase.functionFlag = 2;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.stack = Stack();
			testCase.stack.stackSize = 1024;
			testCase.runTime = 1400;
			testCase.customAllocation = true;
			testCase.sharedMemory = false;
			testCase.m_fileName = "Stack_custom_nonshared_1024.txt";
		}
		else if(index >= nrOfRunsPerTest*3 && index < nrOfRunsPerTest*4)
		{
			testCase.functionFlag = 2;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.stack = Stack();
			testCase.stack.stackSize = 56;
			testCase.runTime = 1400;
			testCase.customAllocation = true;
			testCase.sharedMemory = false;
			testCase.m_fileName = "Stack_custom_nonshared_56.txt";
		}
		else if(index >= nrOfRunsPerTest*4 && index < nrOfRunsPerTest*5) // 0, 1
		{
			testCase.functionFlag = 1;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.pool = Pool();
			testCase.pool.blockSize = 44;
			testCase.pool.nrOfBlocks = 1024;
			testCase.runTime = 1400;
			testCase.customAllocation = false;
			testCase.sharedMemory = true;
			testCase.m_fileName = "Pool_noncustom_shared.txt";
		}
		else if(index >= nrOfRunsPerTest*5 && index < nrOfRunsPerTest*6)
		{
			testCase.functionFlag = 1;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.pool = Pool();
			testCase.pool.blockSize = 44;
			testCase.pool.nrOfBlocks = 1024;
			testCase.runTime = 1400;
			testCase.customAllocation = true;
			testCase.sharedMemory = true;
			testCase.m_fileName = "Pool_custom_shared.txt";

		}
		else if(index >= nrOfRunsPerTest*6 && index < nrOfRunsPerTest*7)
		{
			testCase.functionFlag = 1;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.pool = Pool();
			testCase.pool.blockSize = 440;
			testCase.pool.nrOfBlocks = 1024;
			testCase.runTime = 1400;
			testCase.customAllocation = true;
			testCase.sharedMemory = false;
			testCase.m_fileName = "Pool_custom_nonshared.txt";
		}
		else if(index >= nrOfRunsPerTest*7 && index < nrOfRunsPerTest*8)
		{
			testCase.functionFlag = 1;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.pool = Pool();
			testCase.pool.blockSize = 44;
			testCase.pool.nrOfBlocks = 5000;
			testCase.runTime = 1400;
			testCase.customAllocation = true;
			testCase.sharedMemory = true;
			testCase.m_fileName = "Pool_custom_shared_5000.txt";

		}
		else if(index >= nrOfRunsPerTest*8 && index < nrOfRunsPerTest*9)
		{
			testCase.functionFlag = 1;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.pool = Pool();
			testCase.pool.blockSize = 44;
			testCase.pool.nrOfBlocks = 100;
			testCase.runTime = 1400;
			testCase.customAllocation = true;
			testCase.sharedMemory = true;
			testCase.m_fileName = "Pool_custom_shared_100.txt";

		}
		
		return testCase;		
	}
}