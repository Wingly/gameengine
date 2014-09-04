#include <engine/Include/Application.h>
#include <engine/Include/MemoryAllocator.h>
#include <thread>
#include <stdio.h>
#include <thread>
#include <engine/Include/MemPool.h>
#include <engine/Include/Pool.h>
#include <engine/Include/TestObject.h>

enum class StopCode
{
	CleanStop,
	Restart,
	CrashStop
};

void recursiveTest(int p_init)
{
		if(p_init < 7)
			recursiveTest(++p_init);
		else
			printf("im DONE MATE %d", p_init);
}

void thread_func(void* init_value)
{
	recursiveTest((int) init_value);
}

Application::Application()
{
	Pool* pool = new Pool();

	TestObject* B = new(*pool) TestObject();
}

Application::~Application()
{
	
}


int Application::Run()
{
	return (int)StopCode::CleanStop;
}


void Application::ThreadFunc(void* p_init)
{

}