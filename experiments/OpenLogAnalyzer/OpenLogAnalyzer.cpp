// OpenLogAnalyzer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>

int main(int argc, char* argv[])
{
	FILE* fp = NULL;

	int nCounter = 0;

	char line [1024];
	char * pLine;

	char IP[16];
	char * pIP;

	char referer[512];
	char * pReferer;

	char ua[512];
	char * pUA;

	char user[32];
	char * pUser;

	char delimiter[2];
	char * pDelimiter;

	char date[64];
	char * pDate;

	char get[512];
	char * pGet;

	clock_t start, finish;
	double duration;

	int size;
	int response;

	fp = fopen("E:\\Eigene Dateien\\access_log\\access_log", "r");
	if (!fp) {
		printf("Error opening file!");
		return 1;
	}

	start = clock();

	while(!feof(fp)) {
		if( fgets( line, 1024, fp ) == NULL) {
			if (ferror(fp)) {
				printf( "fgets error\n" );
				fclose(fp);
				return 1;
			}
		}

		pLine = line;
		pIP = IP;
		
		while((*pIP++ = *pLine++) != ' ');
		*(--pIP) = '\0';


		pUser = user;
		while((*pUser++ = *pLine++) != ' ');
		*(--pUser) = '\0';

		pDelimiter = delimiter;
		while((*pDelimiter++ = *pLine++) != ' ');
		*(--pDelimiter) = '\0';

		pLine++;
		pDate = date;
		while((*pDate++ = *pLine++) != ']');
		*(--pDate) = '\0';

		pLine+=2;
		pGet = get;
		while((*pGet++ = *pLine++) != '\"');
		*(--pGet) = '\0';

		sscanf(pLine, "%d %d", &response, &size);

		while(*pLine++ != '\"');

		pReferer = referer;
		while((*pReferer++ = *pLine++) != '\"');
		*(--pReferer) = '\0';		

		while(*pLine++ != '\"');		

		pUA = ua;
		while((*pUA++ = *pLine++) != '\"');
		*(--pUA) = '\0';

		nCounter++;
	}
	
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;

	printf("%d %f\r\n", nCounter, duration);
	fclose(fp);

	return 0;
}

