// Beep.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	printf("This should beep in all cases...\a\r\n\r\n\r\n");
	Sleep(1000);
	printf("This, too...\r\n\r\n");
	Beep(440, 150);

	return 0;
}

