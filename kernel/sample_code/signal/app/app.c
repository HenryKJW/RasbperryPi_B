/*
測試流程
[root]#./app.exe
I am Chinese					<--用戶輸入
input available:I am Chinese		<--signal_test程序印出
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//#define debug

#define	MAX_LEN 100

static void signalio_handler(int signum)
{
	printf("receive a signal from globalfifo, signalnum:%d \n",signum);
}

void input_handle(int num)
{
	char data[MAX_LEN];
	int	len;

	len = read(STDIN_FILENO,&data,MAX_LEN);
	data[len];
	printf("input available:%s \n",data);
}

void main(void)
{
  int fd, oflags;
  
#ifdef debug 
	signal(SIGIO, input_handle);
	fcntl(STDIN_FILENO, F_SETOWN, getpid());	
	oflags = fcntl(fd, F_GETFL);
	fcntl(STDIN_FILENO, F_SETFL, oflags|FASYNC);
	while(1);
#else
  fd = open("/dev/globalfifo", O_RDWR, S_IRUSR|S_IWUSR);
  if(fd != -1){
	signal(SIGIO, signalio_handler);
	fcntl(fd, F_SETOWN, getpid());
	oflags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, oflags|FASYNC);
	while(1);
  } else {
	printf("device open failure \n");
  }
  #endif
}
