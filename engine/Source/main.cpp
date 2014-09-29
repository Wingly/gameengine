#include <Windows.h>
#include <engine/Include/Application.h>
#include <engine/Include/GameTimer.h>

/*
vilken funktion

pool specific
	block size
	number of blocks
	runTime

alignment

stack specific
	stack size
*/

static const unsigned int MAX_TESTS = 1;

int main()
{
	Application application;
	
	int stopCode = 1;	// 1 == restart

	for(unsigned int i = 0; i < MAX_TESTS; ++i)
	//	while(stopCode == 1) 
	{
		float oldTime, newTime;
		GameTimer gameTimer = GameTimer();

		gameTimer.Start();
		gameTimer.Tick();	
		oldTime = gameTimer.GetGameTime();

		stopCode = application.Run(TestCases::GetTestCase(i));

		gameTimer.Tick();
		gameTimer.Stop();
		newTime = gameTimer.GetGameTime();

		newTime = newTime - oldTime;
		std::cout << newTime << std::endl;
		// print to file
	}

	system("pause");
	return 0;
}