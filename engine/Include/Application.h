#pragma once

#include <engine/Include/MemoryAllocator.h>
struct Particle {
	float lifeTime;
	float startSpeed;
	float startX;
	float startY;
	float startZ;
	float dirX;
	float dirY;
	float dirZ;
	float colR;
	float colG;
	float colB;
};
class MemoryAllocator;
class Application
{
public:
	Application();
	~Application();

	void ThreadInit();
	void ThreadRun();
	int Run();

private:
	void ThreadFunc(void* p_init);
	MemPool<Particle>* m_pool;
	bool m_running;

};

