#include <Windows.h>
#include <engine/Include/Application.h>
#include <engine/Include/GameTimer.h>
#include <fstream>
#include <string>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

static const unsigned int MAX_TESTS = 9000;

void writeToFile(char* p_fileName, int p_id, float p_time)
{
	std::ofstream outfile;
	outfile.open(p_fileName, std::ios_base::app);
	outfile << "id: " << p_id << " time: " << p_time << "\n";
}

int main()
{
	Application application;
	int stopCode = 1;	
	double sum = 0;
	double avg = 0;
	double min = 1000;
	double max = 0;
	//Each test is a set of 1000, to only run certain tests change i to a higher value
	//or lower the MAX_TESTS variable
	for(unsigned int i = 0; i < MAX_TESTS; ++i) 
	//	while(stopCode == 1) 
	{
		double oldTime, newTime;
		GameTimer gameTimer = GameTimer();

		TestCases::TestCase CaseyAleine = TestCases::GetTestCase(i);
		gameTimer.Start();
		gameTimer.Tick();
		oldTime = gameTimer.GetGameTime();

		stopCode = application.Run(CaseyAleine);

		gameTimer.Tick();
		gameTimer.Stop();

		newTime = gameTimer.GetGameTime();
	
		newTime = newTime - oldTime;

		if(newTime < min)
			min = newTime;
		if(newTime > max)
			max = newTime;

		sum += newTime;

		//_CrtDumpMemoryLeaks();

		if(i % 100 == 0)
		{
			std::cout << "Iteration i= " << i << std::endl;
		}

		writeToFile(CaseyAleine.m_fileName, i, newTime);
		if((i + 1) % TestCases::nrOfRunsPerTest == 0 && i != 0)
	//	if(i % 10 == 0 && i != 0)
		{
				sum -= (min+max);
				avg = sum/(TestCases::nrOfRunsPerTest-2);
			//	avg = sum/(MAX_TESTS-2);
				writeToFile(CaseyAleine.m_fileName, -1, sum);
				writeToFile(CaseyAleine.m_fileName, -2, avg);
				sum = 0;
				min = 1000;
				max = 0;
		}
	}

	system("pause");
	return 0;
}