/*
    C socket server example
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

//UART
#include "uart.h"
#include "status.h"
#include <termios.h>
#include <sys/select.h> 
#include <sys/time.h> 
//End

#define	PORT		5000
#define   MessageLen	20
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    unsigned char client_message[200];
	
    memset(client_message, 0, sizeof(client_message));//clean message 
//UART
    struct timeval timeout;
    fd_set readfds;
    int fd;

    if ( (fd = initUART("/dev/ttyAMA0")) < 0 ) {
	return -1;
    }
//End
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
    
    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , MessageLen, 0)) > 0 )
    {
	printf("Client Messages:%s \n",client_message);	
        //Send the message back to client
       write(client_sock , client_message , strlen(client_message));
//UART
	printf("WriteByte=%c \n",client_message[0]);
	writeByte(fd,client_message[0]);

//-----------Print and Read Uart----------------
	timeout.tv_sec = 0;
	timeout.tv_usec = 200000;

	FD_ZERO(&readfds);
	FD_SET(fd,&readfds);
	
	printf("readByte=");
	while( select(fd+1, &readfds,NULL, NULL, &timeout)>0 )
	{
		if(FD_ISSET(fd,&readfds)) 
		{
		readByte(fd,&client_message[0]);
		printf("%c",client_message[0]);
		}

		timeout.tv_sec = 0;
		timeout.tv_usec = 200000;

		FD_ZERO(&readfds);
		FD_SET(fd,&readfds);		
	}
	printf("\n");
//End
	memset(client_message, 0, sizeof(client_message));
    }

//UART
    closeComPort(fd);
//End
     
    if(read_size == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
     
    return 0;
}
