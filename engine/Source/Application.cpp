#include <engine/Include/Application.h>

#include <thread>
#include <complex>
#include <stdio.h>
#include <vector>

#define WIDTH 800
#define HEIGHT 800
#define TOTAL_SIZE (HEIGHT * WIDTH *sizeof(int))

enum class StopCode
{
	CleanStop,
	Restart,
	CrashStop
};


Application::Application()
{
	MemoryAllocator* memAl = new MemoryAllocator();
	m_pool = memAl->CreatePool<Particle>(NUM_BLOCKS, 16);

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

	MemStack* stack = memAl->CreateStack(200000 + TOTAL_SIZE, 16);

	int* hej = stack->Push<int>();
	*hej = 5;
	//Marker markymark = stack->GetMarker();
	float* dej = stack->Push<float>();
	*dej = 10.0f;
	int dadadab = 2;
//	stack->Free(markymark);
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


void ThreadRun(threadParam param)
{
	if(RUN_PARTICLE_TEST)
	{
		std::vector<Particle*> particle;// = new std::vector<Particle*>();
		
		for(int i = 0; i < NUM_PARTICLES_PER_THREAD; i++) 
		{
			particle.push_back(param.pool->getBlock());
			particle.at(i)->lifeTime = rand() % 2000 + 1;
		}

		float emissionTime = 0.0f;
		param.freeBlocks = 0;
		while(--param.runTime) 
		{
			emissionTime++;
			for (int i = 0; i < particle.size(); i++ )
			{
				particle.at(i)->lifeTime--;
				if(particle.at(i)->lifeTime <= 0)
				{
					param.pool->freeBlock(particle.at(i));
					particle.erase(particle.begin() + i);
					param.freeBlocks++;
				}
			}

			if(emissionTime >= param.emissionRate && param.freeBlocks > 0)
			{
				particle.push_back(param.pool->getBlock());
				param.freeBlocks--;
			}
		}
	}
	else
	{

	}
}


int Application::Run()
{
	srand (time(NULL));
	std::thread thread[NUM_THREADS];
	threadParam params;
	for(int i = 0; i < NUM_THREADS; i++) {
		params.emissionRate = rand() % 10000 + 1000;
		params.freeBlocks = 0;
		params.runTime = 10000;
		params.pool = m_pool;
		thread[i] = std::thread(ThreadRun, params);

		thread[i].join();
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