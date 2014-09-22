#pragma once

#include <engine/Include/MemoryAllocator.h>
#include <random>

static const unsigned int NUM_THREADS = 4;
static const unsigned int NUM_BLOCKS = 1024;
static const unsigned int NUM_PARTICLES_PER_THREAD = NUM_BLOCKS/NUM_THREADS;

static const unsigned int RUN_PARTICLE_TEST = true;

struct float3
{
	float x;
	float y;
	float z;
};

struct Particle {
	float lifeTime;
	float startSpeed;
	float3 start;
	float3 dir;
	float3 colR;
};
struct threadParam
{
	int emissionRate;
	int freeBlocks;
	int runTime;
	MemPool<Particle>* pool;
};
class MemoryAllocator;
class Application
{
public:
	Application();
	~Application();

	//void ThreadRun(threadParam param);
	int Run();

private:
	void ThreadFunc(void* p_init);
	MemPool<Particle>* m_pool;
	void Mandelbrot(float p_width, float p_height, unsigned int* p_pixMap );
	void writeTga(unsigned int* p_pixmap, unsigned int p_width, unsigned int p_height, char* p_name);
	bool m_running;

	Particle* m_particle[NUM_THREADS];

};

