#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Motor.h"
#include "Delay.h"
/**
  * 函    数：直流电机初始化
  * 参    数：无
  * 返 回 值：无
  */
void Motor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);						//将PA4和PA5引脚初始化为推挽输出	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);		//开启GPIOC的时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);						//推挽输出	
	//GPIO_ResetBits(GPIOA, GPIO_Pin_0);//设置蜂鸣器默认电平
	
	PWM_Init();													//初始化直流电机的底层PWM
}

/**
  * 函    数：直流电机设置速度
  * 参    数：Speed 要设置的速度，范围：-100~100
  * 返 回 值：无
  */
void Brake()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
}

void Turn_Left()
{
	int Speed=Speed_Left;
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	PWM_SetCompare2(Speed);
	PWM_SetCompare3(Speed);
	Delay_ms(Time_TurnLeft);
	Brake();
}

void Turn_Right()
{
	int Speed=Speed_Right;
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
	PWM_SetCompare2(Speed);
	PWM_SetCompare3(Speed);
	Delay_ms(Time_TurnRight);
	Brake();
}

void Go_Straight()
{
	int Speed=Speed_Straight;
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
	PWM_SetCompare2(Speed);
	PWM_SetCompare3(Speed);
}

void Go_back()
{
	int Speed=Speed_back;
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	GPIO_SetBits(GPIOA, GPIO_Pin_6);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	PWM_SetCompare2(Speed);
	PWM_SetCompare3(Speed);
	Delay_ms(Time_GoBack);
	Brake();
}

void Turn_back()
{
	int Speed=Speed_back;
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	GPIO_SetBits(GPIOA, GPIO_Pin_5);
	GPIO_ResetBits(GPIOA, GPIO_Pin_6);
	PWM_SetCompare2(Speed);
	PWM_SetCompare3(Speed);
	Delay_ms(Time_TurnBack);
	Brake();
}

void Motor_SetLeftSpeed(int8_t Speed_L)
{
	if (Speed_L >= 0)							//如果设置正转的速度值
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_0);	
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);	//PA4置高电平
		PWM_SetCompare2(Speed_L);				//PWM设置为速度值
	}
	else									//否则，即设置反转的速度值
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);	//PA4置低电平
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		PWM_SetCompare2(-Speed_L);			//PWM设置为负的速度值，因为此时速度值为负数，而PWM只能给正数
	}
}

void Motor_SetRightSpeed(int8_t Speed_R)
{
	if (Speed_R >= 0)							//如果设置正转的速度值
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);	
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);	//PA4置高电平
		PWM_SetCompare3(Speed_R);				//PWM设置为速度值
	}
	else									//否则，即设置反转的速度值
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);	//PA4置低电平
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		PWM_SetCompare3(-Speed_R);			//PWM设置为负的速度值，因为此时速度值为负数，而PWM只能给正数
	}
}

void Motor_Fan_Open()
{
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	
		GPIO_SetBits(GPIOC, GPIO_Pin_14);
		PWM_SetCompare4(Speed_Fan);
}

void Motor_Fan_Close()
{
		GPIO_ResetBits(GPIOC, GPIO_Pin_15);	
		GPIO_ResetBits(GPIOC, GPIO_Pin_14);
}
