#ifndef __ONENET_H_
#define __ONENET_H_ 

extern u8 temperature;  	    
extern u8 humidity;
extern u8 ppm;

_Bool OneNet_DevLink(void);

void OneNet_SendData(void);

void OneNet_RevPro(unsigned char *cmd);

unsigned char MqttOnenet_Savedata(char *t_payload);

#endif
