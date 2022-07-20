#include "TestSpace.h"
#include <stdio.h>
#include <conio.h>

SoliRom::App TestSpace;

int main(int argc, char* args[])
{
	printf("gaylords unite\n");
	printf("press enter in console to close\n");

	bool skip = false;

	while (!skip)
	{
		//if (kbhit())
		//	if (getch() == '\r')
		//		skip = true;
		std::string a;
		std::getline(std::cin, a);

		printf("\n");

		SR_TRACE(a.c_str());
		SR_CORE_TRACE(a.c_str());
		SR_INFO(a.c_str());
		SR_CORE_INFO(a.c_str());
		SR_WARN(a.c_str());
		SR_CORE_WARN(a.c_str());
		SR_ERROR(a.c_str());
		SR_CORE_ERROR(a.c_str());
		SR_FATAL(a.c_str());
		SR_CORE_FATAL(a.c_str());

		printf("\n");
	}

	return 0;
}