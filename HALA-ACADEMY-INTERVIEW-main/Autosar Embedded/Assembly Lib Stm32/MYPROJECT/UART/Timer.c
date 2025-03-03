/* Author: Nguyen Van Thanh */
#include "Timer.h"

void Delay_ms(uint32_t time)
{		
		TIM1->EGR=0;
		while(time>0){
		while( (TIM1->SR&0x1)==1){
		time--;
		TIM1->SR&=~0x1;
}}}
void Tim1_init(void)
{
	RCC->APB2ENR|=(1U<<0);
	TIM1->CNT=0;
	TIM1->PSC=99;
	TIM1->ARR=7999;
	TIM1->EGR=0;
	TIM1->CR1=1;
}