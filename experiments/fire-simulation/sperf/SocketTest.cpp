// SocketTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/*
int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	return 0;
}*/

//#include <sys/types.h>
//#include <sys/socket.h>
//#include <sys/time.h>
#include <winsock2.h>
#include <conio.h>
#include <stdlib.h>
#include <io.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//#include <netinet/in.h> 
//#include <unistd.h>



#define SIZE(x) sizeof(x)/sizeof(x[0])
#define OSNAMESZ 100

void print_help() {
	printf("USAGE:\n\nsperf ip port br buf [-d]\n\n");
	exit(0);
}

int main(int argc, char *argv[])
{
        int ssfd, csfd;
        int slen, clen;
        int result;
        int debug_on = 1;
        int counter = 0;
        int show = 0;
        int delay = 0;
        int buffer_size, socket_buffer_size;
        char * recv_buf;
        struct sockaddr_in saddr;
        struct sockaddr_in caddr;
        int readb;

		WORD wVersionRequested;
		WSADATA wsaData;
 
		wVersionRequested = MAKEWORD( 2, 2 );
 
		int err = WSAStartup( wVersionRequested, &wsaData );
		if ( err != 0 ) {
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			return false;
		}
 
		/* Confirm that the WinSock DLL supports 2.2.*/
		/* Note that if the DLL supports versions greater    */
		/* than 2.2 in addition to 2.2, it will still return */
		/* 2.2 in wVersion since that is the version we      */
		/* requested.                                        */
 
		if ( LOBYTE( wsaData.wVersion ) != 2 ||
				HIBYTE( wsaData.wVersion ) != 2 ) {
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			WSACleanup( );
			return false;
		}
		
		if (argv[3]) {
			buffer_size = atoi(argv[3]);
		}
		if (argv[4]) {
			socket_buffer_size = atoi(argv[4]);
		}
		
		recv_buf = (char *)malloc((int)(buffer_size * sizeof(char)));
		
		if (argc < 5) {
			print_help();
		}
		
        ssfd = socket(AF_INET, SOCK_STREAM, 0);
 
 		if (argv[5] && strcmp(argv[5], "-d") == 0) {
 			printf("RUNNING IN DEBUG MODE\n");
 			setsockopt(ssfd, SOL_SOCKET, SO_DEBUG, (char *)&debug_on, sizeof(debug_on));
 		}
 
 		if (socket_buffer_size > 65535) {
 			perror(">> Buffersize larger than 65535\n>> Setting the buffer to 65535 Bytes\n");
 			socket_buffer_size = 65535;
 		}
		setsockopt(ssfd, SOL_SOCKET, SO_RCVBUF, (char *)&socket_buffer_size, sizeof(socket_buffer_size));
 
        if(!ssfd)
        {
                perror("server1 failed while trying to create a socket");
                exit(1);
        }
 
        memset(&saddr, 0, sizeof(saddr)); 

		
        saddr.sin_family = AF_INET; 
        saddr.sin_port = atoi(argv[2]); 
        saddr.sin_addr.s_addr = inet_addr(argv[1]); 
        
        printf("Listening on %s:%d\n\n", argv[1], saddr.sin_port);
        
        slen = sizeof(saddr);
        result = bind(ssfd, (struct sockaddr *)&saddr, slen);
 
        if(result < 0)
        {
                perror("server1 failed while binding to socket");
                exit(1);
        }
 
        result = listen(ssfd, 5);

        if(result < 0)
        {
                perror("server1 failed while trying to listen");
                exit(1);
        }

        printf("server1 listening...\n");

        clen = sizeof(caddr);

        csfd = accept(ssfd, (struct sockaddr *)&caddr, &clen);

        if(!csfd)
        {
                perror("server1 failed in attempt to accet a connection");
                exit(1);
        }
        
        printf("-");
        while(++counter) {
	        memset(recv_buf, '\0', 256);
	        
	        readb = read(csfd, recv_buf, 256);
	        
	        if (readb == -1) {
	        	perror("ERROR read()");
	        }
	
			//printf("READ FROM CLIENT (%d): %s\n", readb, recv_buf);
			if (readb == 0) {
				break;
			}
			
			/* Hoppla. Die Ausgabe verlangsamt das ganze etwa um den Faktor 5!!!!! */
			/*switch (counter % 4) {
				case 0:
					printf("\b-");
					break;
				case 1:
					printf("\b\\");
					break;	
				case 2:
					printf("\b|");
					break;	
				case 3:
					printf("\b/");
					break;			
			}
			
			fflush(stdout);*/


	        if (strstr(recv_buf, "---end---") != 0) {
	        	printf("\n\nEND FOUND\n\n");
	        	break;
	        }
	    }

		free(recv_buf);

        close(csfd);

		return 0;
}
