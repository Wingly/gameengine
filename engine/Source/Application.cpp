#include <engine/Include/Application.h>
#include <engine/Include/MemoryAllocator.h>
#include <thread>
#include <complex>
#include <stdio.h>
#define WIDTH 800
#define HEIGHT 800
#define TOTAL_SIZE (HEIGHT * WIDTH *sizeof(int))

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
	MemStack* stack = memAl->CreateStack(200000 + TOTAL_SIZE);

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

	unsigned int* test = reinterpret_cast<unsigned int*>(stack->Push<unsigned int[TOTAL_SIZE]>());
	Mandelbrot(WIDTH, HEIGHT, test);
	writeTga(test, WIDTH, HEIGHT, "Hej.tga");
	
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

void Application::Mandelbrot(float p_width, float p_height, unsigned int* p_pixMap)
{
	int i, j;
	float xmin = -1.6f;
	float xmax = 1.6f;
	float ymin = -1.6f;
	float ymax = 1.6f;
	for (i = 0; i < p_height; i++) {
		for (j = 0; j < p_width; j++) {
			float b = xmin + j * (xmax - xmin) / p_width;
			float a = ymin + i * (ymax - ymin) / p_height;
			float sx = 0.0f;
			float sy = 0.0f;
			int ii = 0;
			while (sx + sy <= 64.0f) {
				float xn = sx * sx - sy * sy + b;
				float yn = 2 * sx * sy + a;
				sx = xn;
				sy = yn;
				ii++;
				if (ii == 1500)	{
					break;
				}
			}
			if (ii == 1500)	{
				p_pixMap[j+i*(int)p_width] = 0;
			}
			else {
				int c = (int)((ii / 32.0f) * 256.0f);
				p_pixMap[j + i *(int)p_width] = c%256;
			}
		}
	}
}


void Application::writeTga(unsigned int* p_pixmap, unsigned int p_width, unsigned int p_height, char* p_name)
{
	FILE *f;
	int i,j;
	char buffer[50];
	f = fopen(p_name,"wb");
	fwrite("\x00\x00\x02",sizeof(char),3,f);
	fwrite("\x00\x00\x00\x00\x00",sizeof(char),5,f);
	fwrite("\x00\x00",sizeof(char),2,f);
	fwrite("\x00\x00",sizeof(char),2,f);
	sprintf(buffer,"%c%c",(p_width & 0x00ff)%0xff,(p_width & 0xff00)%0xff);
	fwrite(buffer,sizeof(char),2,f);
	sprintf(buffer,"%c%c",(p_height & 0x00ff)%0xff,(p_height & 0xff00)%0xff);
	fwrite(buffer,sizeof(char),2,f);
	fwrite("\x18\x00",sizeof(char),2,f);
	for (i = p_height; i >= 0; i--) {
		for (j = 0; j < p_width; j++) {
			sprintf(buffer, "%c%c%c",
				(p_pixmap[j+(i)*p_width]>>0)&0x000000ff,
				(p_pixmap[j+i*p_width]>>0)&0x000000ff,
				(p_pixmap[j+i*p_width]>>0)&0x000000ff);
			fwrite(buffer,sizeof(char),3,f);
		}
	}
	fclose(f);
}