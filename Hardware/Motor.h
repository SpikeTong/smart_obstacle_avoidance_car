#ifndef __MOTOR_H
#define __MOTOR_H
#define Speed_Straight 70
#define Speed_Left 70
#define Speed_Right 70
#define Speed_back 70
#define Speed_Fan 50
#define Distance_Safe 20
#define Time_TurnLeft 800
#define Time_TurnRight 800
#define Time_TurnBack 1600
#define Time_GoBack 2000
#define tic 1000000 //1 10000000tick=1s
#include "stdint.h"

void Motor_Init(void);
void Motor_SetSpeed(int8_t Speed);
void Turn_Right();
void Turn_Left();
void Brake();
void Go_Straight();
void Go_back();
void Turn_back();
void Motor_Fan_Open();
void Motor_Fan_Close();


#endif
