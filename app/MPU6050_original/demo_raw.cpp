#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include <math.h>

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
    // initialize device
    printf("Initializing I2C devices...\n");
    accelgyro.initialize();

    // verify connection
    printf("Testing device connections...\n");
    printf(accelgyro.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
}

void loop() {
    double fax_g, fay_g, faz_g, faxyz_g, fgx_deg, fgy_deg, fgz_deg;
    double Axr, Ayr, Azr;
		
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    fax_g =(double) ax/Accelerometer_AFS_SEL_2g;
    fay_g =(double) ay/Accelerometer_AFS_SEL_2g;
    faz_g =(double) az/Accelerometer_AFS_SEL_2g;
    fgx_deg = (double) gx/Gyroscope_AFS_SEL_250_deg;
    fgy_deg = (double) gy/Gyroscope_AFS_SEL_250_deg;
    fgz_deg = (double) gz/Gyroscope_AFS_SEL_250_deg;
    faxyz_g = sqrt(fax_g*fax_g+fay_g*fay_g+faz_g*faz_g);

    // 1~PI
    Axr = acos(fax_g/faxyz_g);
    Ayr = acos(fay_g/faxyz_g);
    Azr = acos(faz_g/faxyz_g);

    //deg
    Axr = (Axr/PI)*360;
    Ayr = (Ayr/PI)*360;
    Azr = (Azr/PI)*360;
    
//Test
//printf("angles: faxyz_g-->%2.6f, Axr-->%2.6f, Ayr-->%2.6f, Azr-->%2.6f \n", faxyz_g, Axr, Ayr, Azr);		

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    // display accel/gyro x/y/z values
    printf("accel: %6hd %6hd %6hd ---> %2.6f (g)     %2.6f (g)    %2.6f (g) \n", ax, ay, az, fax_g, fay_g, faz_g);
    printf("gyro: %6hd %6hd %6hd  ---> %2.6f (deg/s) %2.6f (deg/s) %2.6f (deg/s) \n", gx, gy, gz, fgx_deg, fgy_deg, fgz_deg);	
    printf("angles: Axr--> %3.6f (deg), Ayr--> %3.6f (deg), Azr--> %3.6f (deg) \n", Axr, Ayr, Azr);		
    usleep(500);
}

int main()
{
    setup();
    for (;;)
        loop();
}

