/* Author: NGUYEN VAN THANH */
/* PWM GPIOD PIN12, PIN13 */
#include "stm32f411xe.h"

extern void TIM4_Init(void);
extern void PWM_1(unsigned short duty1);
extern void PWM_2(unsigned short duty1);
int main() {
    TIM4_Init(); 

    while (1) {
  PWM_1(999);
	TIM4->CCR2=0000;
    }
    return 0; 
}
