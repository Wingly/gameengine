#include <engine/Include/Application.h>

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
/*
void ThreadFunc(void* p_init, int id)
{
	//int id = -1;
	MemStack* temp = reinterpret_cast<MemStack*>(p_init);
	int brake = 0;
	while(brake < 10)
	{
		brake++;
		int* hej = temp->Push<int>(id);
		*hej = 5;
		//Marker markymark = stack->GetMarker();
		float* dej = temp->Push<float>(id);
		*dej = 10.0f;
		int dadadab = 2;
	//	stack->Free(markymark);
		float* mej = temp->Push<float>(id);
		*mej = 13131.0f;
	}
}
*/
Application::Application()
{
	m_Al_The_Croc = new MemoryAllocator();
	m_pool = m_Al_The_Croc->CreatePool<Particle>(NUM_BLOCKS, 16);
	m_stack = m_Al_The_Croc->CreateStack(TOTAL_SIZE + 200000, 4); 
	m_pool->init();
	//Run();

	// STACK TEST //
	/*
	MemStack* stack = memAl->CreateStack(200000 + TOTAL_SIZE, 16);
	std::thread ett = std::thread(ThreadFunc,stack,1);
	std::thread tva = std::thread(ThreadFunc,stack,2);
	std::thread tre = std::thread(ThreadFunc,stack,3);
	ett.join();
	tva.join();
	tre.join();
	*/
//	//int* hej = stack->Push<int>();
//	*hej = 5;
//	//Marker markymark = stack->GetMarker();
////	float* dej = stack->Push<float>();
//	*dej = 10.0f;
//	int dadadab = 2;
////	stack->Free(markymark);
//	float* mej = stack->Push<float>();
//	*mej = 13131.0f;
//	int hejsan = 3;

	/*unsigned int* test = reinterpret_cast<unsigned int*>(stack->Push<unsigned int[TOTAL_SIZE]>());
	Mandelbrot(WIDTH, HEIGHT, test);
	writeTga(test, WIDTH, HEIGHT, "Hej.tga");*/
	

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
		std::cout << "Thread id: " << param.id << "entering work zone" << std::endl;
		float workperthread = HEIGHT / (NUM_THREADS); //Aslong as HEIGHT == WIDTH this will work
		float threadStartPos = workperthread * param.id;
		MemStack* stack = param.al_the_croc->CreateStack(56, 4);
		Mandelbrot(stack, threadStartPos, workperthread, WIDTH, HEIGHT, param.pixmap);
		std::cout << "Thread id: " << param.id << "LEAVING work zone" << std::endl;

	}
}


int Application::Run()
{
	srand (time(NULL));
	std::thread thread[NUM_THREADS];
	unsigned int* pixmap;
	if(!RUN_PARTICLE_TEST)
		 pixmap = reinterpret_cast<unsigned int*>(m_stack->Push<unsigned int[WIDTH*HEIGHT]>());
	for(int i = 0; i < NUM_THREADS; i++) {
		threadParam params;
		params.emissionRate = rand() % 10000 + 1000;
		params.freeBlocks = 0;
		params.runTime = 10000;
		params.pool = m_pool;
		params.al_the_croc = m_Al_The_Croc;
		if(!RUN_PARTICLE_TEST) 
		{
			params.stack = m_stack;
			params.id = i;
			params.pixmap = pixmap;
		}
		thread[i] = std::thread(ThreadRun, params);
	}
	for(int i = 0; i < NUM_THREADS; i++) {
		thread[i].join();
	}
	if(!RUN_PARTICLE_TEST)
		writeTga(pixmap, WIDTH, HEIGHT, "image.tga");
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