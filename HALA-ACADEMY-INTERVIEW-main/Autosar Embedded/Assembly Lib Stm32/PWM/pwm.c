/* Author: NGUYEN VAN THANH */
/* PWM GPIOD PIN12, PIN13 */
#include "stm32f411xe.h"
void Delay11(uint16_t time){
	TIM1->EGR=0;
while(time>0){
while( (TIM1->SR&0x1)==1){
time--;
	TIM1->SR&=~0x1;
}}}
void Delay3(__IO uint32_t nCount)
{
    while(nCount--)
    {
    }
}
void TiM1_init1(void){
//__ASM volatile (
//    "LDR R0, =0x40021000 \n"  
//    "LDR R1, [R0, #0x18] \n"  
//    "ORR R1, R1, #1 \n"      
//    "STR R1, [R0, #0x18] \n"  
//)
RCC->APB2ENR|=(1U<<0);
	TIM1->CNT=0;
	TIM1->PSC=15;
	TIM1->ARR=999;
	TIM1->CR1|=(1U<<7);
	TIM1->CR1&=~(1U<<4);
	TIM1->CR1&=~(1U<<2);
		TIM1->CR1&=~(1U<<1);
	TIM1->EGR|=(1U<<0);
	TIM1->CR1|=(1U<<0);
}
void EXTI0_Init(void)
{
    /* Enable clock for SYSCFG and GPIOA */
    RCC->APB2ENR |= (1U << 14);
    RCC->AHB1ENR |= (1U << 0);

    /* Configure GPIOA Pin 0 as input */
    GPIOA->MODER &= ~(3U << 0);

    /* Connect EXTI0 line to GPIOA Pin 0 */
    SYSCFG->EXTICR[0] &= ~(0xFU << 0);

    /* Configure EXTI line for falling edge trigger */
    EXTI->FTSR |= (1U << 0);  // Falling edge
    EXTI->RTSR &= ~(1U << 0); // Disable rising edge

    /* Enable interrupt for EXTI0 */
    EXTI->IMR |= (1U << 0);  // Unmask EXTI0 interrupt
    EXTI->PR |= (1U << 0);   // Clear pending flag

    /* Enable EXTI0 in NVIC */
    NVIC_EnableIRQ(EXTI0_IRQn);
}

extern void TIM4_Init(void);
extern void PWM_1(unsigned short duty1);
extern void PWM_2(unsigned short duty1);
void EXTI0_IRQHandler(void){
	Delays3(20000);
PWM_1(0);
}
int main() {
    TIM4_Init(); 
//TiM1_init1();
	EXTI0_Init();
    while (1) {
  PWM_1(889);
			
		//	Delay11(2000);
		

    }
    return 0; 
}
