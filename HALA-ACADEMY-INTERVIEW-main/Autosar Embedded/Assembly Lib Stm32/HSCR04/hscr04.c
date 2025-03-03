#include "stm32f411xe.h"

float dist;
extern float HCSR04_Read();
void Delay3(__IO uint32_t nCount);
float HCSR04_Read(void){
uint32_t time, timeout;
	GPIOD->ODR&=~(1U<<0); // trig low
	Delay3(2);
		GPIOD->ODR|=(1U<<0); // trig high
	Delay3(10);
	GPIOD->ODR&=~(1U<<0); 
	timeout = 1000000;
	while( !(GPIOD->IDR>>2&0x1)){
	if (timeout-- == 0x00) {
			return -1;
		}
}time = 0;
	while( (GPIOD->IDR>>2&0x1)){
	time++;
		Delay3(1);
	}
	dist =  (float)time * ((float)0.0171821);
	return dist;

}
void Configure_PMW( void){
		/// PIND12 chanel 1
RCC->AHB1ENR|=(1U<<3);
RCC->APB1ENR|=(1U<<2);
	GPIOD->MODER&=~(3U<<24);
	GPIOD->MODER|=(2U<<24);
GPIOD->AFR[1]|=(2<<16);
		TIM4 ->ARR =999; // 1ms 
	TIM4 -> PSC = 15;
TIM4->CCR1 = 30;

	TIM4->CCMR1 &=~(0x3<<0);
	TIM4->CCMR1|=(6U<<4);
	TIM4->CCER |= 1;
	TIM4->CR1 |=  (1<<0);
}
int main(){
	Configure_PMW();
//	TIM4_Init();
 

  
  TM_HCSR04_Init();
TIM4->CCR1 = 700;
    while(1){
        // Ð?c kho?ng cách t? HC-SR04
      float  distance = HCSR04_Read();
Delay3(20);
			if( distance<0){
			} else if( distance<20){
		TIM4->CCR1 = 200;
			}
			else{
		
				TIM4->CCR1 =0;
			}
        Delay3(10); 
    }
}

void Delay3(__IO uint32_t nCount)
{
    while(nCount--)
    {
    }
}
