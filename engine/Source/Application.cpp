#include <engine/Include/Application.h>
#include <engine/Include/MemoryAllocator.h>
#include <thread>
#include <stdio.h>
#include <thread>

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

}


Application::~Application()
{
	
}


int Run()
{
	

	std::thread first(thread_func,(void*)0);
	std::thread second(thread_func,(void*)1);

	first.join();
	second.join();
	system("pause");

}


void ThreadFunc(void* p_init)
{

}