#ifndef  Demo_DMP_H
#define Demo_DMP_H

void setupMPU6050DMP(void);
//quaternion[4]:={w,x,y,z}
//euler[3]:={Yaw, Pitch, Roll} :degree
//pYawPitchRoll[3]:={Yaw, Pitch, Roll} :degree
void GetMPU6050Data(float* pYawPitchRoll,float* pEuler,float* pQuaternion);
#endif
