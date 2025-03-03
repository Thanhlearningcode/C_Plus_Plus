#include "Car_Engine.h"

void Car(void (*ptr)(uint16_t,uint16_t),uint16_t a, uint16_t b){
ptr(a,b);
}
// Hàm di chuy?n robot v? phía tru?c
void Move_Forward(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

// Hàm lùi
void Move_Backward(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

// Hàm quay trái
void Turn_Left(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

// Hàm quay phai
void Turn_Right(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

// Hàm stop car
void Stop(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

