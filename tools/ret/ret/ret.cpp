// ret.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>

unsigned long _tmain(int argc, _TCHAR* argv[])
{
	if (argc > 1) {
		unsigned long ret;
		std::wistringstream iss(argv[1]);
		iss >> ret;
		return ret;
	}
	else {
		return -1;
	}
}

