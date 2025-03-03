#include "Car_Engine.h"

void Car(void (*ptr)(uint16_t,uint16_t),uint16_t a, uint16_t b){
ptr(a,b);
}
// H�m di chuy?n robot v? ph�a tru?c
void Move_Forward(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

// H�m l�i
void Move_Backward(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

// H�m quay tr�i
void Turn_Left(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

// H�m quay phai
void Turn_Right(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

// H�m stop car
void Stop(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

