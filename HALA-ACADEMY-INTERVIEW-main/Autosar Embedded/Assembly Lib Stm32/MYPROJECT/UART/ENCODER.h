/* Author: Nguyen Van Thanh */
#ifndef _ENCODER_H_
#define _ENCODER_H_
#include "stm32f411xe.h"
uint16_t read_encoder_right(void);
uint16_t read_encoder_left(void);
void ENCODER1_INIT(void);
void ENCODER2_INIT(void);
#endif