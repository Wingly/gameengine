#include <engine/Include/Application.h>
#include <engine/Include/TestCases.h>

#include <thread>
#include <complex>
#include <stdio.h>
#include <vector>

#define WIDTH 2000
#define HEIGHT 2000
#define TOTAL_SIZE (HEIGHT * WIDTH *sizeof(int))

enum class StopCode
{
	CleanStop,
	Restart,
	CrashStop
};

Application::Application()
{
	/*
	m_Al_The_Croc = new MemoryAllocator(CUSTOM_ALLOCATION);
	m_pool = m_Al_The_Croc->CreatePool<Particle>(NUM_BLOCKS, 16, NUM_THREADS == 1 ? false : true);
	m_stack = m_Al_The_Croc->CreateStack(TOTAL_SIZE + 200000, 4, NUM_THREADS == 1 ? false : true); 
	m_pool->init();
	*/
}

Application::~Application()
{
	
}

void Mandelbrot(MemStack* p_stack, float p_startPos, float p_threadHeight, float p_width, float p_height, unsigned int* p_pixMap)
{
	
	int* i = p_stack->Push<int>();
	int* j = p_stack->Push<int>();
	float* xmin = p_stack->Push<float>();
	float* xmax = p_stack->Push<float>();
	float* ymin = p_stack->Push<float>();
	float* ymax = p_stack->Push<float>();
	float* b = p_stack->Push<float>();
	float* a = p_stack->Push<float>();
	float* xn = p_stack->Push<float>();
	float* yn = p_stack->Push<float>();
	int* ii = p_stack->Push<int>();
	float* sx = p_stack->Push<float>();
	float* sy = p_stack->Push<float>();
	int* c = p_stack->Push<int>();
	*xmin = -1.6f;
	*xmax = 1.6f;
	*ymin = -1.6f;
	*ymax = 1.6f;
	for (*i = (int)p_startPos; *i < ((int)p_startPos+p_threadHeight); *i += 1) {
		for (*j = 0; *j < p_width; *j += 1) {
			*b = *xmin + *j * (*xmax - *xmin) / p_width;
			*a = *ymin + *i * (*ymax - *ymin) / p_height;
			*sx = 0.0f;
			*sy = 0.0f;
			*ii = 0;
			while (*sx + *sy <= 64.0f) {
				*xn = (*sx) * (*sx) - (*sy) * (*sy) + (*b);
				*yn = 2 * (*sx) * (*sy) + (*a);
				*sx = (*xn);
				*sy = (*yn);
				*ii+=1; //Apparently ++ has precedence over a de-reference, The more you know™
				if (*ii == 1500)	{
					break;
				}
			}
			if (*ii == 1500)	{
				p_pixMap[*j+*i*(int)p_width] = 0;
			}
			else {
				*c = (int)((*ii / 32.0f) * 256.0f);
				p_pixMap[*j + *i *(int)p_width] = *c%256;
			}
		}
	}
}

void MandelbrotNormalStack(MemStack* p_stack, float p_startPos, float p_threadHeight, float p_width, float p_height, unsigned int* p_pixMap)
{
	
	int i;
	int j;
	float xmin; 
	float xmax; 
	float ymin; 
	float ymax; 
	float b;
	float a;
	float xn;
	float yn;
	int ii;
	float sx;
	float sy;
	int c;
	xmin = -1.6f;
	xmax = 1.6f;
	ymin = -1.6f;
	ymax = 1.6f;
	for (i = (int)p_startPos; i < ((int)p_startPos+p_threadHeight); i ++) {
		for (j = 0; j < p_width; j ++) {
			b = xmin + j * (xmax - xmin) / p_width;
			a = ymin + i * (ymax - ymin) / p_height;
			sx = 0.0f;
			sy = 0.0f;
			ii = 0;
			while (sx + sy <= 64.0f) {
				xn = (sx) * (sx) - (sy) * (sy) + (b);
				yn = 2 * (sx) * (sy) + (a);
				sx = (xn);
				sy = (yn);
				ii++; //Apparently ++ has precedence over a de-reference, The more you know™
				if (ii == 1500)	{
					break;
				}
			}
			if (ii == 1500)	{
				p_pixMap[j+ i*(int)p_width] = 0;
			}
			else {
				c = (int)((ii / 32.0f) * 256.0f);
				p_pixMap[j + i *(int)p_width] = c%256;
			}
		}
	}
}

void PoolTest(threadParam param)
{
	std::vector<Particle*> particle;
		
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

void StackTest(threadParam param)
{
	float workperthread = HEIGHT / (NUM_THREADS); //Aslong as HEIGHT == WIDTH this will work
	float threadStartPos = workperthread * param.id;
	MemStack* stack = param.al_the_croc->CreateStack(56, 4, false);
	if(param.customAllocation)
		Mandelbrot(param.stack, threadStartPos, workperthread, WIDTH, HEIGHT, param.pixmap);
	else
		MandelbrotNormalStack(param.stack, threadStartPos, workperthread, WIDTH, HEIGHT, param.pixmap);
}


int Application::Run(TestCases::TestCase p_testCase)
{
	m_Al_The_Croc = new MemoryAllocator(p_testCase.customAllocation);
	
	if(p_testCase.functionFlag == 1)
	{		
		unsigned int numberOfThreads = p_testCase.nrThreads;

		m_pool = m_Al_The_Croc->CreatePool<Particle>(p_testCase.pool.nrOfBlocks, p_testCase.alignment, numberOfThreads == 1 ? false : true);
		m_pool->init();

		//srand (time(NULL));
		std::thread* thread = new std::thread[numberOfThreads];

		for(int i = 0; i < numberOfThreads; i++) {
			threadParam params;
			params.emissionRate = rand() % 10000 + 1000;
			params.freeBlocks = 0;
			params.runTime = p_testCase.pool.runTime;
			params.pool = m_pool;
			thread[i] = std::thread(PoolTest, params);
		}
		for(int i = 0; i < numberOfThreads; i++) {
			thread[i].join();
		}
		if(p_testCase.customAllocation)
			delete m_pool;
	}
	else if(p_testCase.functionFlag == 2)
	{
		unsigned int numberOfThreads = p_testCase.nrThreads;

		m_stack = m_Al_The_Croc->CreateStack(TOTAL_SIZE, 4, numberOfThreads == 1 ? false : true); 
		srand (time(NULL));

		std::thread* thread = new std::thread[numberOfThreads];

		unsigned int* pixmap;
		if(p_testCase.customAllocation)
			pixmap = reinterpret_cast<unsigned int*>(m_stack->Push<unsigned int[WIDTH*HEIGHT]>());
		else
			pixmap = (unsigned int*)malloc(TOTAL_SIZE);	

		for(int i = 0; i < numberOfThreads; i++) 
		{
			threadParam params;
			params.al_the_croc = m_Al_The_Croc;
			params.stack = m_stack;
			params.customAllocation = p_testCase.customAllocation;
			params.id = i;
			params.pixmap = pixmap;
			thread[i] = std::thread(StackTest, params);
		}

		for(int i = 0; i < NUM_THREADS; i++) {
			thread[i].join();
		}
		//writeTga(pixmap, WIDTH, HEIGHT, "image.tga");
	}
	delete m_Al_The_Croc;
	return (int)StopCode::CleanStop;
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
				(p_pixmap[j+i*p_width]>>8)&0x000000ff);
			fwrite(buffer,sizeof(char),3,f);
		}
	}
	fclose(f);
}