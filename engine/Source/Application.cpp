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

struct testStruct {
	float hej;
	int hureleget;
	char testet;
};

Application::Application()
{
	MemoryAllocator* memAl = new MemoryAllocator();
	MemPool<float>* a = memAl->CreatePool<float>(5);
	
	float* b = a->getBlock();
	*b = 1.0f;

	float* c = a->getBlock();
	*c = 2.0f;

	float* d = a->getBlock();
	*d = 3.0f;

	MemPool<testStruct>* struktur = memAl->CreatePool<testStruct>(5);
	testStruct* sak = struktur->getBlock();
	sak->hej = 1.0f;
	sak->hureleget = 500;
	sak->testet = 'c';

	m_running = true;

	a->freeBlock(b);
	float* e = a->getBlock();
	b = a->getBlock();

	MemStack* stack = memAl->CreateStack(200000);

	int* hej = stack->Push<int>();
	*hej = 5;
	Marker markymark = stack->GetMarker();
	float* dej = stack->Push<float>();
	*dej = 10.0f;
	int dadadab = 2;
	stack->Free(markymark);
	float* mej = stack->Push<float>();
	*mej = 13131.0f;
	int hejsan = 3;
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