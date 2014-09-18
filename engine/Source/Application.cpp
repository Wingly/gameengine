#include <engine/Include/Application.h>

#include <thread>
#include <stdio.h>

static const unsigned int NUM_THREADS = 4;
static const unsigned int NUM_BLOCKS = 1024;
static const unsigned int NUM_PARTICLES_PER_THREAD = NUM_BLOCKS/NUM_THREADS;

static const unsigned int RUN_PARTICLE_TEST = true;


enum class StopCode
{
	CleanStop,
	Restart,
	CrashStop
};



Application::Application()
{
	

	MemoryAllocator* memAl = new MemoryAllocator();
	MemPool<float>* a = memAl->CreatePool<float>(5, 16);
	m_pool = memAl->CreatePool<Particle>(NUM_BLOCKS, 16);
	
	float* b = a->getBlock();
	*b = 1.0f;

	float* c = a->getBlock();
	*c = 2.0f;

	float* d = a->getBlock();
	*d = 3.0f;

	m_running = true;

	a->freeBlock(b);
	float* e = a->getBlock();
	b = a->getBlock();

	MemStack* stack = memAl->CreateStack(200000, 16);

}

Application::~Application()
{
	
}

void Application::ThreadInit()
{
	if(RUN_PARTICLE_TEST)
	{
		Particle* particles[NUM_PARTICLES_PER_THREAD];// = new Particle[];
		for(int i = 0; i < NUM_PARTICLES_PER_THREAD; i++) 
		{
			particles[i] = m_pool->getBlock();
		}
		
	}
	else
	{

	}
}

void Application::ThreadRun()
{

}


int Application::Run()
{
	while(m_running)
	{
		ThreadRun();
	}

	return (int)StopCode::CleanStop;
}


void Application::ThreadFunc(void* p_init)
{

}