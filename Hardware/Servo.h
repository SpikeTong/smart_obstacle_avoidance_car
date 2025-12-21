#ifndef __SERVO_H
#define __SERVO_H
#include "stdint.h"

void Servo_Init(void);
void Servo_SetAngle(float Angle);
void Servo_SetCompare2(uint16_t Compare);


#endif
