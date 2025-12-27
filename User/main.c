#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Servo.h"
#include "Ultrasound.h"
#include "dht11.h"
#include "usart.h"
#include "onenet.h"
#include "esp8266.h"
#include "Timer.h"
#include <string.h>
#include <stdio.h> 
#include <car.h>
#include <mq2.h>
#include <adcx.h>
#include <Humidifier.h>
uint8_t dhtFlag=0;
uint8_t KeyNum;			//定义用于接收键码的变量
float Angle = 90;			//定义角度变量
unsigned char *dataPtr = NULL;	
float Distance;
int main(void)
{

	/*模块初始化*/
	// 核心控制器与外设
	SystemInit();		//内部时钟初始化
	delay_init(72);		//延时函数选择外部时钟
	// 运动控制模块
	Motor_Init();		//直流电机初始化
	Servo_Init();		//舵机初始化
	Ultrasound_Init();	//超声波初始化 TIM4 B89 需獨立用時鐘
	// 传感器模块
	MQ2_Init();			//传感器初始化
	// 通信模块
	Usart1_Init(115200);    // 串口1初始化 (与ESP8266通信)
	ESP8266_Init();         // WiFi模块初始化
	// 执行器模块
	Humidifier_Init();      // 加湿器初始化 (B11)
	Humidifier_Open();
	Motor_Fan_Open();       // 开启风扇
	Servo_SetAngle(90);	//摆正舵机角度
	// 网络连接
	while(OneNet_DevLink())			//接入OneNET
	Delay_ms(500);	
	
		while (1)//同时运行避障、传感、通信模块
	{                
		
		//避障模块
		Distance = Test_Distance();
		if (Distance<Distance_Safe)//车辆前方小于安全距离,开始避障
		{
			Brake();
			Car_Detect_Turn(Distance);//核心避障函数 使小车原地转到安全方向
			Go_Straight();
		}
		Delay_ms(10);
		
		//传感通信模块
		DHT11_Read_Data(&temperature,&humidity);		
		if(temperature>=30)
		{
			Motor_Fan_Open();
		}
		else
			Motor_Fan_Close();
		
		if(humidity<=75)
		{
				Humidifier_Open();
		}
		else
			Humidifier_Close();
		
		OneNet_SendData();//向云平台发送数据
		ESP8266_Clear();
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)	OneNet_RevPro(dataPtr);//检测平台返回数据
		//检测空气质量
		ppm = MQ2_GetData_PPM();
		Delay_ms(20);	
	
	}
}
