// TCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TCPServer.h"
#include <afxsock.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	int nPort = 1500;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// Initialize the sockets things...
		if (!AfxSocketInit())
		{
			AfxMessageBox("failed");
			return 1;
		}

		// Check if a port was entered at the command line
		if (argc > 1) {
			sscanf(argv[1], "%d", &nPort);
		}

		CString s;

		CSocket socket, connect;

		// Create the server socket
		socket.Create(nPort);

		cout << "Listening..." << endl;

		// Bind the server socket to the port
		socket.Bind(nPort);
		int BufferSize = 1 << 16;

		// Listen....
		while (socket.Listen()) {
			// Accept a new connection
			if (socket.Accept(connect)) {
				UINT nPort = 0;
				CString s;
				socket.GetSockName(s, nPort);

				cout << "Connection from " <<  s << " established" << endl;
				LPTSTR buf = s.GetBuffer(BufferSize);

				int nRead = 0;
				int nSent = 0;
				int nOldSent = 0;
				int nRecvPackets = 0;
				int nSendPackets = 0;

				int nb = 65535;
				int nL = sizeof(nb);
				// Set the send- and receive-buffer according to the packet size
				socket.SetSockOpt(SO_RCVBUF, (void *)&nb, nL);
				socket.SetSockOpt(SO_SNDBUF, (void *)&nb, nL);

				connect.SetSockOpt(SO_RCVBUF, (void *)&nb, nL);
				connect.SetSockOpt(SO_SNDBUF, (void *)&nb, nL);

				DWORD dwEnable = 1;
				socket.IOCtl(FIONBIO, &dwEnable);
				connect.IOCtl(FIONBIO, &dwEnable);
				
#ifdef _DEBUG
				printf("Packets recv:           Packets sent:          ");
#endif

				// Read until an error occurs
				while((nRead = connect.Receive(buf, BufferSize)) != SOCKET_ERROR) {
					nRecvPackets++;
					if (atof(buf) == 0) {
						nRecvPackets = 1;
						nSendPackets = 0;
					}
#ifdef _DEBUG
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		
					printf("%09d", nRecvPackets);
#endif
					if (nRead == 0) {
						break;
					}
					try{
						// Just send back what we received
						nSent = connect.Send(buf, nRead);

						// Make sure the thread gets preempted so that the client thread
						// has a chance to be loaded right now
						Sleep(0);

						// Check for errors
						if (nSent == 0) {
							cout << "Connection closed" << endl;
							break;
						}
						else if (nSent == SOCKET_ERROR) {
							cerr << "Error sending: " << nSent << endl;
							DWORD dwError = GetLastError();
							break;
						}
#ifdef _DEBUG
						printf(" Packets sent: %09d", ++nSendPackets);
#endif
					}
					catch (CException * pEx) {
						CString sErr;
						pEx->GetErrorMessage(sErr.GetBuffer(1024), 1024);
						sErr.ReleaseBuffer();
						cerr << sErr << endl;
						pEx->Delete();
					}
				}

				// Check for errors while receiving
				if (nRead == 0) {
					cout << "Connection closed" << endl;
				}
				else if (nRead == SOCKET_ERROR) {
					cerr << "Socket error " << nRead << endl;
					DWORD dwError = GetLastError();
				} 
				s.ReleaseBuffer();
				connect.Close();
			}
			else {
				DWORD dwError = GetLastError();
				cerr << "Socket error " << dwError << endl;
			}
		}

		socket.Close();
	}

	return nRetCode;
}


