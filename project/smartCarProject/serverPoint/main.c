/*
Raspberry Pi 系統會預設從UART送出Kernel和端終機送出資訊,請先關閉
*/
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h> 
#include <sys/time.h> 

#include "uart.h"
#include "status.h"

int main() 
{
	int fd;
	unsigned char byte[1];
	struct timeval timeout;
	fd_set readfds;
	
	
	if ( (fd = initUART("/dev/ttyAMA0")) < 0 ) {
		return -1;
	}
	
	while(1)
	{
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		FD_ZERO(&readfds);
		FD_SET(fd,&readfds);

		if ( select(fd+1, &readfds,NULL, NULL, &timeout) < 0 )
			return -1;

		if(FD_ISSET(fd,&readfds)) {
			readByte(fd,&byte[0]);
			printf("readByte=%c \n",byte[0]);
			writeByte(fd,byte[0]);
		}
	}
	closeComPort(fd);
	return SUCCESS;
}