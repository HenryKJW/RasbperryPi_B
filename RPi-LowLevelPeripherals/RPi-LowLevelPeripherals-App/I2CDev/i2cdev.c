#include <unistd.h>   
#include <errno.h>   
#include <stdio.h>   
#include <stdlib.h>   
#include <linux/i2c-dev.h>   
#include <sys/ioctl.h>   
#include <fcntl.h>   
  
#define MPU6050_ADDRESS	(0x68)
#define MPU6050_REGISTER	(0x75)
  
int main()   
{   
    char buf[10];   
    const char * devName = "/dev/i2c-1";
  
    // Open up the I2C bus   
    int file = open(devName, O_RDWR);   
    if (file == -1)   
    {   
        perror(devName);   
        exit(1);   
    }   
  
    // Specify the address of the slave device.   
    if (ioctl(file, I2C_SLAVE, MPU6050_ADDRESS) < 0)   
    {   
        perror("Failed to acquire bus access and/or talk to slave");   
        exit(1);   
    }   
  
    // Write a byte to the slave.   
    buf[0] = MPU6050_REGISTER;   
    if (write(file, buf, 1) != 1)   
    {   
        perror("Failed to write to the i2c bus");   
        exit(1);   
    }   
  
    // Read a byte from the slave.   
    if (read(file,buf,1) != 1)
    {   
        perror("Failed to read from the i2c bus");   
        exit(1);   
    }   
  
    printf("result: 0x%02X\n", buf[0]);   
  
    return 0;
} 