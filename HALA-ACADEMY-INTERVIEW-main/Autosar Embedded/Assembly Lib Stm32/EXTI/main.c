#include "stm32f411xe.h"
extern void EXIT_Init1(void);

void EXTI0_IRQHandler(void){

// DO Something ....
	GPIOD->ODR&=~(1<<12);
	EXTI->PR |=1;

}
int main(){
	EXIT_Init1();
	RCC->AHB1ENR|=(1<<3);
	GPIOD->MODER &=~(3U<<24);
	GPIOD->MODER |=(1U<<24);
	GPIOD->OTYPER&=~(1<<12);
while(1){
	GPIOD->ODR|=(1<<12);
}
}