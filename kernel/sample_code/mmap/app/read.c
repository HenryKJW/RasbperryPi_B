#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	 int fd;
	 char *addr=NULL;
	 
	 fd = open("/dev/DEMO",O_RDWR);
	 if(fd < 0) {
		 perror("open");
		 return 0;
	 }
	 addr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	 if(addr == MAP_FAILED) {
		 perror("DEMO");
		 return 0;
	 }
	 printf("%s\n", addr);
	 memset(addr,'f',100);
	 addr[0]='p';
	 printf("%s\n", addr);
	 munmap(addr,4096);
	 addr=NULL;
	 close(fd);

	 fd = open("/dev/DEMO",O_RDWR);
	 if(fd < 0) {
		 perror("open");
		 return 0;
	 }
	 addr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	 if(addr == MAP_FAILED) {
		 perror("DEMO");
		 return 0;
	 }
	 printf("%s\n", addr);
	 munmap(addr,4096);
	 close(fd);
	 return(0);
}