#include <engine/Include/Application.h>
#include <engine/Include/TestCases.h>

#include <thread>
#include <complex>
#include <stdio.h>
#include <vector>
#include <Windows.h>

#define WIDTH 2000
#define HEIGHT 2000
#define TOTAL_SIZE (HEIGHT * WIDTH *sizeof(int))

enum class StopCode
{
	CleanStop,
	Restart,
	CrashStop
};

Application::Application()
{
}

Application::~Application()
{
	
}


void PoolTest(threadParam param)
{
	std::vector<Particle*> particle;
	
	int numParticlesPerThread = param.Casey.pool.nrOfBlocks / param.Casey.nrThreads;

	for(int i = 0; i < numParticlesPerThread; i++) 
	{
		Particle* part = param.pool->getBlock();
		if(part != nullptr)
		{
			part->lifeTime = rand() % 2000 + 1;
			particle.push_back(part);
		}
	}

	float emissionTime = 0.0f;
	param.freeBlocks = 0;
	while(--param.runTime) 
	{
		emissionTime++;
		for (int i = 0; i < particle.size(); i++ )
		{
			particle.at(i)->lifeTime--;
			if(particle.at(i)->lifeTime <= 0)
			{
				param.pool->freeBlock(particle.at(i));
				particle.erase(particle.begin() + i);
				param.freeBlocks++;
			}
		}

		if(emissionTime >= param.emissionRate && param.freeBlocks > 0)
		{
			Particle* part = param.pool->getBlock();
			if(part != nullptr)
			{
				part->lifeTime = rand() % 2000 + 1;
				particle.push_back(part);
				param.freeBlocks--;
			}
		}
	}
	if(!param.Casey.sharedMemory)
		delete param.pool;
}

void StackTest(threadParam param)
{
	float workperthread = HEIGHT / (NUM_THREADS); //Aslong as HEIGHT == WIDTH this will work
	float threadStartPos = workperthread * param.id;
	MemStack* stack = nullptr;
	stack = param.al_the_croc->CreateStack(param.Casey.stack.stackSize, 4, false, param.Casey.customAllocation);

	std::vector<float*> testVector;
	while(--param.Casey.runTime)
	{
		while(true)
		{
			float* testVar = stack->Push<float>(1);
			if(testVar != nullptr)
				testVector.push_back(testVar);
			else
				break;

		}

		stack->Wipe();
		if(!param.Casey.customAllocation)
			for(auto x : testVector)
			{
				delete x;
			}
		testVector.clear();
	}
	
	if(!param.Casey.sharedMemory)
		delete stack;
}


int Application::Run(TestCases::TestCase p_testCase)
{
	m_Al_The_Croc = new MemoryAllocator();
	
	if(p_testCase.functionFlag == 1)
	{		
		unsigned int numberOfThreads = p_testCase.nrThreads;

		if(p_testCase.sharedMemory)
		{
			m_pool = m_Al_The_Croc->CreatePool<Particle>(p_testCase.pool.nrOfBlocks, p_testCase.alignment, p_testCase.sharedMemory, p_testCase.customAllocation);
			m_pool->init();
		}

		//srand (time(NULL));
		std::thread* thread = new std::thread[numberOfThreads];

		for(int i = 0; i < numberOfThreads; i++) {
			threadParam params;
			params.emissionRate = rand() % 10000 + 1000;
			params.freeBlocks = 0;
			params.runTime = p_testCase.runTime;
			if(p_testCase.sharedMemory)
				params.pool = m_pool;
			else
			{
				params.pool = m_Al_The_Croc->CreatePool<Particle>(p_testCase.pool.nrOfBlocks / p_testCase.nrThreads, p_testCase.alignment, p_testCase.sharedMemory, p_testCase.customAllocation);
				params.pool->init();
			}
			params.Casey = p_testCase;
			thread[i] = std::thread(PoolTest, params);
		}
		for(int i = 0; i < numberOfThreads; i++) {
			thread[i].join();
		}
		if(p_testCase.customAllocation && p_testCase.sharedMemory)
			delete m_pool;
	}
	else if(p_testCase.functionFlag == 2)
	{
		unsigned int numberOfThreads = p_testCase.nrThreads;

		srand (time(NULL));

		std::thread* thread = new std::thread[numberOfThreads];

		unsigned int* pixmap;
		//if(p_testCase.customAllocation)
		//	pixmap = reinterpret_cast<unsigned int*>(m_stack->Push<unsigned int[WIDTH*HEIGHT]>());
		//else
		//	pixmap = new unsigned int[TOTAL_SIZE];//(unsigned int*)malloc(TOTAL_SIZE);	

		
		for(int i = 0; i < numberOfThreads; i++) 
		{
			threadParam params;
			params.al_the_croc = m_Al_The_Croc;
			params.id = i;
			params.runTime = p_testCase.runTime;
			params.Casey = p_testCase;
			//params.pixmap = pixmap;
			thread[i] = std::thread(StackTest, params);
		}

		for(int i = 0; i < NUM_THREADS; i++) {
			thread[i].join();
		}
		//writeTga(pixmap, WIDTH, HEIGHT, "image.tga");
		delete[] thread;
	}
	delete m_Al_The_Croc;
	return (int)StopCode::CleanStop;
}

void Application::writeTga(unsigned int* p_pixmap, unsigned int p_width, unsigned int p_height, char* p_name)
{
	FILE *f;
	int i,j;
	char buffer[50];
	f = fopen(p_name,"wb");
	fwrite("\x00\x00\x02",sizeof(char),3,f);
	fwrite("\x00\x00\x00\x00\x00",sizeof(char),5,f);
	fwrite("\x00\x00",sizeof(char),2,f);
	fwrite("\x00\x00",sizeof(char),2,f);
	sprintf(buffer,"%c%c",(p_width & 0x00ff)%0xff,(p_width & 0xff00)%0xff);
	fwrite(buffer,sizeof(char),2,f);
	sprintf(buffer,"%c%c",(p_height & 0x00ff)%0xff,(p_height & 0xff00)%0xff);
	fwrite(buffer,sizeof(char),2,f);
	fwrite("\x18\x00",sizeof(char),2,f);
	for (i = p_height; i >= 0; i--) {
		for (j = 0; j < p_width; j++) {
			sprintf(buffer, "%c%c%c",
				(p_pixmap[j+(i)*p_width]>>0)&0x000000ff,
				(p_pixmap[j+i*p_width]>>0)&0x000000ff,
				(p_pixmap[j+i*p_width]>>8)&0x000000ff);
			fwrite(buffer,sizeof(char),3,f);
		}
	}
	fclose(f);
}