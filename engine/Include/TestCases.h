#pragma once

namespace TestCases
{
	static const unsigned int nrOfRunsPerTest = 1000;


struct TestCase
{
	unsigned int functionFlag;
	unsigned int nrThreads;
	unsigned int alignment;
	Stack stack;
	Pool pool;
};

// functionFlag 1
struct Pool
{
	unsigned int blockSize;
	unsigned int nrOfBlocks;
	unsigned int runTime;
};

// functionFlag 2
struct Stack
{
	unsigned int stackSize; // In bytes
};

	TestCase GetTestCase(unsigned int index)
	{
		TestCase testCase;
		if(index >= nrOfRunsPerTest*0 && index < nrOfRunsPerTest*1)
		{
			testCase.functionFlag = 1;
		}
		else if(index >= nrOfRunsPerTest*1 && index < nrOfRunsPerTest*2)
		{

		}
		else if(index >= nrOfRunsPerTest*3 && index < nrOfRunsPerTest*4)
		{

		}
		return testCase;		
	}




}