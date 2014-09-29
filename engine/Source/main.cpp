#include <Windows.h>
#include <engine/Include/Application.h>
#include <engine/Include/GameTimer.h>
#include <fstream>

static const unsigned int MAX_TESTS = 100;

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
		//std::cout << newTime << std::endl;
		writeToFile("file.test", i, newTime);
	}
	
	system("pause");
	return 0;
}