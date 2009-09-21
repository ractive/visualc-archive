// sleep.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
	int sleep_ms = 1000;
	if (argc > 1) {
		sleep_ms = _tstoi(argv[1]);
	}

	Sleep(sleep_ms);
	return 0;
}

