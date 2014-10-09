#pragma once

#include <engine/Include/MemoryAllocator.h>
#include <engine/Include/TestCases.h>
#include <random>

static const unsigned int NUM_THREADS = 4;
static const unsigned int NUM_BLOCKS = 1024;
static const unsigned int NUM_PARTICLES_PER_THREAD = NUM_BLOCKS/NUM_THREADS;
static const bool CUSTOM_ALLOCATION = true;
static const bool RUN_PARTICLE_TEST = false;

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

	//Added to simulate bigger blocks in the pool
	/*float data;
	float data2;
	float data3;

	int extradata;
	int moredata;*/
};
struct threadParam
{
	int emissionRate;
	int freeBlocks;
	int runTime;
	int id;
	unsigned int* pixmap;
	MemPool<Particle>* pool;
	MemStack* stack;
	MemoryAllocator* al_the_croc;
	TestCases::TestCase Casey;
};

// Forward declaratiuon
class MemoryAllocator;
/*namespace TestCases
{
	struct TestCase;
}
*/

class Application
{
public:
	Application();
	~Application();

	int Run(TestCases::TestCase p_testCase);

private:
	//void ThreadFunc(void* p_init);

	MemPool<Particle>* m_pool;
	MemStack* m_stack;
	MemoryAllocator* m_Al_The_Croc;
	void writeTga(unsigned int* p_pixmap, unsigned int p_width, unsigned int p_height, char* p_name);
	bool m_running;

	Particle* m_particle[NUM_THREADS];

};

