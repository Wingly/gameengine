#include <Windows.h>
#include <engine/Include/Application.h>
#include <engine/Include/GameTimer.h>
#include <fstream>
#include <string>

static const unsigned int MAX_TESTS = 1000;

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
	for(unsigned int i = 0; i < MAX_TESTS; ++i)
	//	while(stopCode == 1) 
	{
		double oldTime, newTime;
		GameTimer gameTimer = GameTimer();

		gameTimer.Start();
		gameTimer.Tick();
		oldTime = gameTimer.GetGameTime();

		stopCode = application.Run(TestCases::GetTestCase(i));

		gameTimer.Tick();
		gameTimer.Stop();
		newTime = gameTimer.GetGameTime();
	
		newTime = newTime - oldTime;

		if(newTime < min)
			min = newTime;
		if(newTime > max)
			max = newTime;

		sum += newTime;
		//std::cout << newTime << std::endl;

		writeToFile("Test_stack_4_threads.txt", i, newTime);
	}
	sum -= (min+max);
	avg = sum/(MAX_TESTS-2);
	writeToFile("Test_pool_4_threads.txt", -1, avg);
	system("pause");
	return 0;
}