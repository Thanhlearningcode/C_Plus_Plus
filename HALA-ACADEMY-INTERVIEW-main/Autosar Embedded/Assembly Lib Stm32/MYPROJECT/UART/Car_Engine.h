#ifndef _CAR_ENGINE_H_
#define _CAR_ENGINE_H_
#include "stdint.h"
void Move_Forward(uint16_t a,uint16_t b);
void Move_Backward(uint16_t a,uint16_t b);
void Turn_Left(uint16_t a,uint16_t b);
void Turn_Right(uint16_t a,uint16_t b);
void Stop(uint16_t a,uint16_t b);
void Car(void (*ptr)(uint16_t,uint16_t),uint16_t a, uint16_t b);
#endif