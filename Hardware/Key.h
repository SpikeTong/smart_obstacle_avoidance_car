#ifndef __KEY_H
#define __KEY_H
#include "stdint.h"
extern  uint8_t Mode;		
extern	uint8_t LeftKey;
extern	uint8_t RightKey;

void Key_Init(void);
uint8_t Key_GetMode(void);
uint8_t Key_GetNum(void);

#endif
