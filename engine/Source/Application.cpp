#include <engine/Include/Application.h>
#include <engine/Include/MemoryAllocator.h>
#include <thread>
#include <stdio.h>

enum class StopCode
{
	CleanStop,
	Restart,
	CrashStop
};

struct Particle {
	float lifeTime;
	float startSpeed;
	float startX;
	float startY;
	float startZ;
	float dirX;
	float dirY;
	float dirZ;
	float colR;
	float colG;
	float colB;
};

Application::Application()
{
	MemoryAllocator* memAl = new MemoryAllocator();
	MemPool<float>* a = memAl->CreatePool<float>(5, 16);
	
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


int Application::Run()
{
	while(m_running)
	{
		// do stuff
	}

	return (int)StopCode::CleanStop;
}


void Application::ThreadFunc(void* p_init)
{

}