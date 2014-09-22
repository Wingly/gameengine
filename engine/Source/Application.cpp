#include <engine/Include/Application.h>

#include <thread>
#include <stdio.h>
#include <vector>




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