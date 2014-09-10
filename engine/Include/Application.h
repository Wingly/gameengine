#pragma once
class MemoryAllocator;
class Application
{
public:
	Application();
	int Run();
	~Application();

private:
	void ThreadFunc(void* p_init);

	bool m_running;

};

