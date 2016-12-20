/*
    C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<stdlib.h>

//Time
#include <sys/time.h>
#include <unistd.h>

//Socket
#define IP_Address	"192.168.20.1"
#define PORT			8888

/*
struct timeval{
	long tv_sec;         //秒
	long tv_usec;       //微秒
};

struct timezone{
    int tz_minuteswest;  //和Greenwich 時間差了多少分鐘
    int tz_dsttime;         //日光節約時間的狀態
};
*/
int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[20] ;
// char server_reply[100];
    //Time

    //Create socket
    sock = socket(AF_INET , SOCK_DGRAM , 0);//TCP - SOCK_STREAM, UDP - SOCK_DGRAM
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr((char *)IP_Address);
    server.sin_family = AF_INET;
    server.sin_port = htons((unsigned short int) PORT );
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
    
    puts("---Connected---\n");

    //keep communicating with server
    while(1)
    {

	 printf("Control Key: (l,L)-Leaser, (S,s)-Sound, u-RedColor, i-GreenColor, o-BreenColor:, p-LedOff, \n");
        printf("Control Key: F-Front, B - Back, S - Stop, L - Left, R - Right:, + speedup , - speeddwon \n");
	 scanf("%s",message);

	 switch(message[0])
	 {
	 	case '8':
	 	              strcpy(message,"forward");
				break;
	 	case '2':
	 	              strcpy(message,"back");
				break;
	 	case '5':
	 	              strcpy(message,"stop");
				break;
	 	case '4':
	 	              strcpy(message,"left");
				break;
	 	case '6':
		              strcpy(message,"right");
				break;
		case '7':
		case '+': strcpy(message,"speedup");
				break;
		case '1':
		case '-': strcpy(message,"speeddown");
				break;
              case 'L':
		case 'l': strcpy(message,"Leaser");
				break;
      		case 'S':
		case 's': strcpy(message,"Sound");
				break;
              case 'o':
              case 'O': strcpy(message,"LED Color");
				break;
              case 'p':
              case 'P': strcpy(message,"LED Time");
				break;
              case '[': strcpy(message,"LedOn+");
				break;
              case ']': strcpy(message,"LedOn-");
				break;
              case 'i':
              case 'I': strcpy(message,"LedOff");
				break;
              case 'q':
                            exit(0);
                            break;
	 }
         
        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
/*
        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
            break;
        }
        printf("Server reply:%s \n",server_reply);	
*/
	 memset(message, 0, sizeof(message));
//	 memset(server_reply, 0, sizeof(server_reply));
    }

    close(sock);
    printf("Exit: \n");
    exit(1);
    return 0;	
}
