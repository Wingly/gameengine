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
	void Mandelbrot(float p_width, float p_height, unsigned int* p_pixMap );
	void writeTga(unsigned int* p_pixmap, unsigned int p_width, unsigned int p_height, char* p_name);
	bool m_running;

};

