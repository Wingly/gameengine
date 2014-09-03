#pragma once
class MemoryAllocator;
class Application
{
public:
	Application(void);
	int Run();
	~Application(void);

private:
	void ThreadFunc(void* p_init);

};

