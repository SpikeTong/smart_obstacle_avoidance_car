#include "stm32f10x.h"                  // Device header

//extern uint16_t Num;//声明变量在其他文件，需系统自行查找后使用

void Timer_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启RCC内部时钟
	//选择时机单元时钟：内部时钟
	TIM_InternalClockConfig(TIM2);//定时器上电后默认使用内部时钟（有时不写）
	
	//配置时机单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	//指定时钟分频：TIM_CKD_DIV1为不分频，TIM_CKD_DIV2为2分频，TIM_CKD_DIV4为4分频
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	//计数器模式选择：向上计数（常用）、向下计数、中央对齐计数
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//选择向上计数
	//定时频率=72M/(PSC+1)/(ARR+1)，定时1秒即为定时频率1Hz,PSC和ARR取值都在0到65535之间。
	//对72M进行7200分频，得到10k的计数频率，该频率下计10000数，得到计时时间为50ms。
	TIM_TimeBaseInitStructure.TIM_Period=500-1;//周期，ARR自动重装器的值
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;//PSC预分频器的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复计数器的值（高级定时器才有，不用给0）
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//手动清除更新中断标志位，避免刚刚初始化完就进入中断
	
	//使能更新中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//选择更新中断到NVIC通路
	
	//配置NVIC
	//配置优先级分组：先占（抢占）优先级和从占（响应）优先级。整个程序只需执行一次
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//选择2,2分组
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;//指定中断通道，选择TIM2通道
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;//指定中断通道是使能还是失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//指定抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;//指定响应优先级
	NVIC_Init(&NVIC_InitStructure);

	//启动定时器
	TIM_Cmd(TIM2,ENABLE);
}


