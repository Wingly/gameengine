#include <Windows.h>
#include <engine/Include/Application.h>

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

int main()
{
	Application application;
	
	int stopCode = 1;	// 1 == restart
	while(stopCode == 1) 
	{
		stopCode = application.Run();
	}

	system("pause");
	return 0;
}