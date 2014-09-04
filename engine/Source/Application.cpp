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
	m_running = true;
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