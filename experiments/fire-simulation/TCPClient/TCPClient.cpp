// A simple client that connects to a server and sends some random data
//
//
// J.P. Bergamin, 2003

#include "stdafx.h"
#include "TCPClient.h"
#include <afxsock.h>
#include <sys/timeb.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

void print_stat(int nExp, double s, __int64 ulBytesSent, UINT unPacketsSent)
{
	ULONG ulBufferSize = 1 << nExp;
	cout << endl;
	cout << "Statistics for packetsize of 2^";
	cout << nExp;
	cout << " ";
	cout << ulBufferSize;
	cout << endl;
	cout << "-------------------------------------------" << endl;

	double MBs = (double)ulBytesSent / s / 1024 / 1024;
	double Ps = (double)unPacketsSent / s;
	cout << (ULONG)ulBytesSent << " Bytes in " << s << " sec. - " << MBs << " MB/s - " << Ps << " Packets/s" << endl << endl;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	int nPort = 1500;
	CString sServer = "localhost";

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		//cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		if (!AfxSocketInit())
		{
			AfxMessageBox("KAKA");
			return 1;
		}

		// Check if a server and a port was entered at the command line
		if (argc > 2) {
			sscanf(argv[2], "%d", &nPort);
			sServer = argv[1];
		}


		CString strBuffer;

		__int64 ulBufferSize = 1 << 16;

		__int64 ulMBtoSend = 20;
		__int64 ulBytesSent = 0;
		UINT unPacketsSent = 0;
		UINT unPacketsRead = 0;
		char rbuffer[1 << 16];
		char seqBuffer[10] = "";

		LPTSTR buffer = strBuffer.GetBuffer(ulBufferSize);
		
		printf("Preparing...\r\n");
		memset(buffer, 0, ulBufferSize);

		// Fill the buffer with some dummy data
		for(int i = 0; i < ulBufferSize; i++) {
			buffer[i] = (char)(int)(i % 26 + 65);
		}

		CSocket socket, connect;

		clock_t c_start, c_finish;

		// Try to create the socket
		if (!socket.Create()) {
			cerr << "Could not create socket" << endl;
			return 1;
		}

		int nSent = 0;
		int nRead = 0;
		USHORT nOldPercent = 0;

		DWORD dwEnable = 1;
		// Enable non blocking operation
		if (!socket.IOCtl(FIONBIO, &dwEnable)) {
			DWORD dwError = GetLastError();
		}

		// Connect to the server
		if (socket.Connect(sServer, nPort)) {
			printf("Starting...\r\n");

			// Packets with the sizes 2^x (with x from this array)
			// are sent
			int sizes[12] = {2, 4, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16};
			
			for(i = 0; i < sizeof(sizes) / sizeof(int); i++) {
			    // Calculate the buffer size 2^x
				ulBufferSize = (1 << sizes[i]);

				// Calculate the amount of data that will be sent,
				// according to the packet size
				ulMBtoSend = ulBufferSize / 32 + 1;
				
#ifdef _DEBUG
				printf("\r\n");
				printf("Packetsize: %d - Packets sent:           Packets read:          ", ulBufferSize);
#endif				

				int nb = 65535;
				int nL = sizeof(nb);
				// Set the receive and sendbuffer size according to the packet size
				socket.SetSockOpt(SO_RCVBUF, (void *)&nb, nL);
				socket.SetSockOpt(SO_SNDBUF, (void *)&nb, nL);

				c_start = 0;
				printf("Percent: 00%%");

				// Send as many packets until ulMBtoSend MBytes have been sent
				while(ulMBtoSend * 1024 * 1024 - 1 > ulBytesSent) {
					sprintf(seqBuffer, "%09d", unPacketsSent);
					memcpy(buffer, seqBuffer, 9);
#ifdef _DEBUG
					if (unPacketsSent % 1 == 0) {
						printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
					}

					USHORT nPercent = 1 + (ulBytesSent / 1024) / (ulMBtoSend * 10.24);
					if (nPercent != nOldPercent) {
						printf("\b\b\b");
						printf("%02d%%", nPercent);
						nOldPercent = nPercent;
					}

#else
					int nPercent = 1 + ulBytesSent / 1024  / 10.24 / ulMBtoSend;
					if (nPercent != nOldPercent) {
						printf("\b\b\b");
						printf("%02d%%", nPercent);
						nOldPercent = nPercent;
					}
#endif
					// Actually send some data
					nSent = socket.Send(buffer, ulBufferSize);
					
					if (nSent == -1) {
						DWORD dwE = GetLastError();
						//cerr << "Send failed with error " << dwE << endl;
						break;
					}
					
					ulBytesSent += nSent;

					unPacketsSent++;
#ifdef _DEBUG
					if (unPacketsSent % 1 == 0) {
						printf("%09d", unPacketsSent);
					}
#endif
					// Make sure the thread gets preempted so that the server thread
					// has a chance to be loaded right now
					Sleep(0);

					// Receive the answer from the server
					nRead = socket.Receive(rbuffer, ulBufferSize);
					
					if (c_start == 0) {
						c_start = clock();
					}

					unPacketsRead++;
#ifdef _DEBUG
					if (unPacketsSent % 1 == 0) {
						printf(" Packets read: %09d", unPacketsRead);
					}
#endif


					if (nRead == 0) {
						//cout << "Connection was closed" << endl;
						break;
					}
					else if (nRead == SOCKET_ERROR) {
						//cerr << "Error while receiving: " << nRead << endl;
						break;
					}
				}
				
				c_finish = clock();

				// Calculate some statistics and print it to the console
				double s = (double)(c_finish - c_start) / CLOCKS_PER_SEC;
				print_stat(sizes[i], s, ulBytesSent, unPacketsSent);
				
				ulBytesSent = 0;
				unPacketsSent = 0;
				unPacketsRead = 0;
			}

			//cout << endl << endl << "===========================================" << endl << "Finished" << endl;
		}

		strBuffer.ReleaseBuffer();
		socket.Close();

	}
	
	return nRetCode;
}





