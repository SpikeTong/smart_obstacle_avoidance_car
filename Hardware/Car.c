#include "stm32f10x.h"                  // Device header
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Servo.h"
#include "Ultrasound.h"
#include "esp8266.h"
#include "Timer.h"
#include <string.h>
#include <stdio.h> 

void Buzzer_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//
	
	GPIO_SetBits(GPIOB, GPIO_Pin_11);//设置蜂鸣器默认电平 高电平驱动
}

void buzzer_open()
{
		GPIO_SetBits(GPIOB, GPIO_Pin_11);		//将PB12引脚设置为低电平，蜂鸣器鸣叫
		Delay_ms(100);							//延时100ms
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);		//将PB12引脚设置为高电平，蜂鸣器停止
		Delay_ms(100);							//延时100ms
		GPIO_SetBits(GPIOB, GPIO_Pin_11);		//将PB12引脚设置为低电平，蜂鸣器鸣叫
		Delay_ms(100);							//延时100ms
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);		//将PB12引脚设置为高电平，蜂鸣器停止
		Delay_ms(700);							//延时700ms
}

void buzzer_close()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_11);
}

//避障函数 实现使小车原地转到安全方向
void Car_Detect_Turn(float Distance)	
{
			float Distance_Max;
			enum Direction
			{
					Front, Back, Left, Right
			}flag;
	while(Distance = Test_Distance() <20)//超声波检测前方距离小于安全距离 开始避障 只有当前距离小于安全距离才退出while 继续前进
	{
			//检测车辆前方
			Delay_ms(500);//检测车辆前方
			Distance = Test_Distance();
			Distance_Max = Distance;
			flag = Front;//默认前方为安全方向
			OLED_ShowNum(2, 10, Distance, 3);

			//检测车辆右方
			Servo_SetAngle(0);//检测车辆右方
			//OLED_ShowNum(2, 7, 0 , 3);
			Delay_ms(500);//等待舵机到达位置
			Distance = Test_Distance();
			OLED_ShowNum(2, 10, Distance, 3);
			if(Distance > Distance_Safe || Distance > Distance_Max) //找到前、左、右三个方向中车障最大且安全的方向
			{
				Distance_Max = Distance;
				flag = Right;
			}
			//Delay_ms(500);
			
			//检测车辆左方
			Servo_SetAngle(180);//检测车辆左方
			//OLED_ShowNum(2, 7, 180, 3);
			Delay_ms(500);
			Distance = Test_Distance();
			OLED_ShowNum(2, 10, Distance, 3);
			if(Distance > Distance_Safe || Distance > Distance_Max) 
			{
				Distance_Max = Distance;//寻找最大距离
				flag = Left;
			}
			//Delay_ms(500);
			
			Servo_SetAngle(90);//回正
			Delay_ms(500);
			//OLED_ShowNum(2, 7, 90, 3);
			
			//判断当前最大车障距离是否安全 安全距离设置为20cm
			switch(flag)
			{
				
				case Front://三个方向均不安全，调头，重新开始检测
				OLED_ShowString(1, 11, "Back");
				Turn_back();//调头
				Delay_ms(1000);
				OLED_ShowString(1, 11,"Front");
				//Go_Straight();
				break;
				
				//右侧安全，右转
				case Right:
				OLED_ShowString(1, 11,"Right");
				Turn_Right();
				Delay_ms(1000);
				OLED_ShowString(1, 11,"Front");
				//Go_Straight();
				break;
				
				//左侧安全，左转
				case Left:
				OLED_ShowString(1, 11,"Left");
				Turn_Left();
				Delay_ms(1000);
				OLED_ShowString(1, 11,"Front");
				//Go_Straight();
				break;
				
				default:Brake();
				OLED_ShowString(1, 11, "Brake");
			}
		}
}
