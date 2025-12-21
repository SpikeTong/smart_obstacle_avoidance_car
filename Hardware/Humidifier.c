#include <string.h>
#include <stdio.h> 
#include "stm32f10x.h" 
#include "Humidifier.h" 

	void Humidifier_Init()
	{
		/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOB的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//将PA4和PA5引脚初始化为推挽输出	
	}
	
	void Humidifier_Open()
	{
			GPIO_SetBits(GPIOB, GPIO_Pin_11);
	}
	
		void Humidifier_Close()
	{
			GPIO_ResetBits(GPIOB, GPIO_Pin_11);
	}