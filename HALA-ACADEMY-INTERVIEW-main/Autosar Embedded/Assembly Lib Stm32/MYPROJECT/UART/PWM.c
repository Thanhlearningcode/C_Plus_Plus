#include "PWM.h"

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

// H�m quay ph?i
void Turn_Right(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

// H�m d?ng robot
void Stop(uint16_t a,uint16_t b) {
    PWM1(a);
    PWM2(b);
}

void Avoid_Obstacle(void) {
    float distance = HCSR04_Read();  
	 Delay3(10);
    if (distance < 0);
    else if (distance < 20.0) { 
        Stop(0,0); 
        Delay3(1000);  

        Turn_Left(700,300);  
        Delay3(500);  

        Move_Forward(300,700);  
        Delay3(1000); 
    } else {
        Move_Forward(300,300);  
    }
}