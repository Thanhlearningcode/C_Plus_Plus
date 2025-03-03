#include "ENCODER.h"


void ENCODER1_INIT(void) {

    // Enable clock for TIM2 and GPIOA, GPIOB
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;    // Enable clock for TIM2
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;   // Enable clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;   // Enable clock for GPIOB

    // Configure GPIOA (PA15) and GPIOB (PB3) for alternate function (AF1) for TIM2_CH1 and TIM2_CH2
    GPIOA->MODER |= GPIO_MODER_MODER15_1;  // Set PA15 to alternate function mode
    GPIOB->MODER |= GPIO_MODER_MODER3_1;   // Set PB3 to alternate function mode

    // Set output speed for GPIOA and GPIOB (medium speed for both)
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15;
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;

    // Set pull-up/pull-down resistors (pull-down for both)
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR15_0;  // Pull-down for PA15
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR3_0;   // Pull-down for PB3

    // Configure alternate functions for PA15 and PB3 (AF1 for TIM2)
    GPIOA->AFR[1] |= 0x00000001;  // Set PA15 to AF1 (TIM2_CH1)
    GPIOB->AFR[0] |= 0x00000001;  // Set PB3 to AF1 (TIM2_CH2)

    // Configure TIM2
    TIM2->ARR = 0xFFFFFFFF;  // Set auto-reload register to maximum (for 32-bit counting)

    // Configure TIM2 to use encoder interface mode 3 (count both rising and falling edges)
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;  // Set CC1 and CC2 to input mode
    TIM2->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;        // Encoder mode 3

    // Enable TIM2
    TIM2->CR1 |= TIM_CR1_CEN;  // Enable the counter
 }
void ENCODER2_INIT(void){
 // Enable clock for TIM3 and GPIOB, GPIOC
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;    // Enable clock for TIM3
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;   // Enable clock for GPIOB
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;   // Enable clock for GPIOC

    // Configure GPIOB (PB4) and GPIOC (PC7) for alternate function (AF2) for TIM3_CH1 and TIM3_CH2
    GPIOB->MODER |= GPIO_MODER_MODER4_1;  // Set PB4 to alternate function mode
    GPIOC->MODER |= GPIO_MODER_MODER7_1;  // Set PC7 to alternate function mode

    // Set output speed for GPIOB and GPIOC (medium speed for both)
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;

    // Set pull-up/pull-down resistors (pull-down for both)
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR4_0;  // Pull-down for PB4
    GPIOC->PUPDR |= GPIO_PUPDR_PUPDR7_0;  // Pull-down for PC7

    // Configure alternate functions for PB4 and PC7 (AF2 for TIM3)
    GPIOB->AFR[0] |= 0x00020000;  // Set PB4 to AF2 (TIM3_CH1)
    GPIOC->AFR[0] |= 0x02000000;  // Set PC7 to AF2 (TIM3_CH2)

    // Configure TIM3
    TIM3->ARR = 0xFFFFFFFF;  // Set auto-reload register to maximum (for 32-bit counting)

    // Configure TIM3 to use encoder interface mode 3 (count both rising and falling edges)
    TIM3->CCMR1 |= TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0;  // Set CC1 and CC2 to input mode
    TIM3->SMCR |= TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1;        // Encoder mode 3

    // Enable TIM3
    TIM3->CR1 |= TIM_CR1_CEN;  // Enable the counter
}
uint16_t read_encoder_left(void) {
    return TIM2->CNT;
}

// Ð?c giá tr? encoder c?a bánh ph?i (s? d?ng TIM3)
uint16_t read_encoder_right(void) {
    return TIM3->CNT;
}
