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



void print_help() {
	printf("USAGE:\n\ncperf ip port MB bs buf [-d]\n\n");
	exit(0);
}

int main(int argc, char *argv[])
{
        /* some local variables */
        int sfd;
        int len;
        int result;
        int debug_on = 1;
        int sent;
        int go = 1;
        unsigned long sent_total = 0;
        int to_send = 0;
        char msg[256] = "Hallo Server\n";
        struct sockaddr_in addr; 
        SYSTEMTIME start_tv;
        SYSTEMTIME end_tv;
		unsigned long millisecs = 0;
		unsigned long packet_counter = 0;

        int buffer_size, socket_buffer_size;
        char * send_buf;

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
		
		if (argv[4]) {
			buffer_size = atoi(argv[4]);
		}
		if (argv[5]) {
			socket_buffer_size = atoi(argv[5]);
		}
		if (argv[3]) {
			to_send = atoi(argv[3]);
		}
		
		send_buf = (char *)malloc((int)(buffer_size * sizeof(char)));
		memset(send_buf, '\0', buffer_size * sizeof(char));
		
		if (argc < 5) {
			print_help();
		}
   
 
        /* create a socket */
        sfd = socket(AF_INET, SOCK_STREAM, 0);

 		if (argv[6] && strcmp(argv[6], "-d") == 0) {
 			printf("RUNNING IN DEBUG MODE\n");
 			setsockopt(sfd, SOL_SOCKET, SO_DEBUG, (char *)&debug_on, sizeof(debug_on));
 		}
 
 		if (socket_buffer_size > 65535) {
 			perror(">> Buffersize larger than 65535\n>> Setting the buffer to 65535 Bytes\n");
 			socket_buffer_size = 65535;
 		}
		setsockopt(sfd, SOL_SOCKET, SO_RCVBUF, (char *)&socket_buffer_size, sizeof(socket_buffer_size));
 
        /* check for errors before continuing */
        if(!sfd)
        {
                /* we got an error... tell the user and exit */
                perror("client1 failed while creating a socket");
                exit(1);
        }
        /* truncate the addr to 0 size */ 
        memset(&addr, 0, sizeof(addr)); 
        /* now, set up the address */

        addr.sin_family = AF_INET; 
        addr.sin_port = atoi(argv[2]); 
        addr.sin_addr.s_addr = inet_addr(argv[1]); 
        len = sizeof(addr);
 
        /* try to connect */
        result = connect(sfd, (struct sockaddr *)&addr, len);
 
        /* examine the value passed to 'result' */
        if(result == -1)
        {
                /* error! */
                perror("client1 failed while trying to connect");
                exit(1);
        }
        
        GetSystemTime(&start_tv);
        
        while(go) {
		
	        /* if we made it this far, we're connected... write to socket */
	        sent = write(sfd, send_buf, buffer_size);
			sent_total += sent;
			//printf("SENT(%d): %s\n", sent, msg);
	 
	        /* see if we sent the entire string */
	        if(sent != buffer_size)
	        {
	                perror("client1 failed while attemting to write to a socket");
	                exit(1);
	        }
	        
	        go = (sent_total < (to_send * 1024 * 1024));
	        packet_counter++;
	    }

		GetSystemTime(&end_tv);

		strcpy(msg, "---end---");
		sent = write(sfd, msg, strlen(msg));
        if(sent != strlen(msg))
        {
                perror("Error sending end...\n");
                exit(1);
        }

		millisecs = 1000 * (end_tv.wSecond - start_tv.wSecond);
		millisecs += ((end_tv.wMilliseconds - start_tv.wMilliseconds) / 1000);

        printf("%d Bytes sent in %d s %d ms\n", sent_total, (int)(millisecs / 1000), millisecs % 1000);
        printf("%d Bytes per Second\n", 1000 * sent_total / millisecs);
        printf("%d Packets per Second\nTotal packets %d\n", 1000 * packet_counter / millisecs, packet_counter);
 
		free(send_buf);
        close(sfd);

		return 0;
}
