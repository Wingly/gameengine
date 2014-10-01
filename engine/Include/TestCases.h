#pragma once

namespace TestCases
{
	static const unsigned int nrOfRunsPerTest = 1000;

	// functionFlag 1
struct Pool
{
	unsigned int blockSize;		// in bytes
	unsigned int nrOfBlocks;
	unsigned int runTime;		

	Pool() 
	{
		blockSize = 0;
		nrOfBlocks = 0;
		runTime = 0;
	}

	Pool(unsigned int p_blockSize, unsigned int p_nrOfBlocks, unsigned int p_runTime) : blockSize(p_blockSize), nrOfBlocks(p_nrOfBlocks), runTime(p_runTime) 
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
	bool customAllocation;
	Stack stack;
	Pool pool;
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
			testCase.stack.stackSize = 123456789;
			testCase.customAllocation = false;
		}
		else if(index >= nrOfRunsPerTest*10 && index < nrOfRunsPerTest*11) // 0, 1
		{
			testCase.functionFlag = 1;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.pool = Pool();
			testCase.pool.blockSize = 44;
			testCase.pool.nrOfBlocks = 1024;
			testCase.pool.runTime = 14000;
			testCase.customAllocation = true;
		}
		else if(index >= nrOfRunsPerTest*1 && index < nrOfRunsPerTest*2)
		{
			testCase.functionFlag = 1;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.pool = Pool();
			testCase.pool.blockSize = 44;
			testCase.pool.nrOfBlocks = 1024;
			testCase.pool.runTime = 14000;
			testCase.customAllocation = false;

		}
		else if(index >= nrOfRunsPerTest*2 && index < nrOfRunsPerTest*3)
		{
			testCase.functionFlag = 1;
			testCase.nrThreads = 4;
			testCase.alignment = 4;
			testCase.pool = Pool();
			testCase.pool.blockSize = 440;
			testCase.pool.nrOfBlocks = 102;
			testCase.pool.runTime = 14000;
			testCase.customAllocation = false;
		}
		
		return testCase;		
	}
}