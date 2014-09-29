#include <Windows.h>
#include <engine/Include/Application.h>
#include <fstream>

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
void writeToFile(char* p_fileName, int p_id, float p_time)
{
	std::ofstream outfile;
	outfile.open(p_fileName, std::ios_base::app);
	outfile << "id: " << p_id << " time: " << p_time << "\n";
}
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

