#include <engine/Include/Application.h>
#include <engine/Include/MemoryAllocator.h>
#include <thread>
#include <stdio.h>
#include <thread>
#include <engine/Include/MemPool.h>

enum class StopCode
{
	CleanStop,
	Restart,
	CrashStop
};

Application::Application()
{
	MemPool<float> a(5);
	
	float* b = a.getBlock();
	*b = 1.0f;

	float* c = a.getBlock();
	*c = 2.0f;

	float* d = a.getBlock();
	*d = 3.0f;

	m_running = true;

	a.freeBlock(b);
	float* e = a.getBlock();
	b = a.getBlock();
	int dadadab = 2;
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