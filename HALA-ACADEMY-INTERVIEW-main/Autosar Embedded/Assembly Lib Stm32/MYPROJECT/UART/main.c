#include "stm32f411xe.h"
#include "HSCR04.h"
#include "stdio.h"
#include "UART_DMA.h"
#include "ENCODER.h"
#include "Car_Engine.h"
#include "HSCR04.h"
#include "Timer.h"
// GPIOD12 CHANNEL 1
// GPIOC6  CHANNEL 1	
void Avoid_Obstacle(void) {
    float distance = HCSR04_Read();  
	 Delay3(10);
    if (distance < 0);
    else if (distance < 20.0) { 
        Car(Stop,0,0);
        Delay3(500);  
       Car(Turn_Left,700,300); 
        Delay3(500);  
     Car(Move_Forward,300,700); 
        Delay3(1000); 
    } else {
    Car(Move_Forward,300,700); 
    }
}
/* Author: Nguyen Van Thanh */
void ADC_init() {
    // Enable the clock for ADC1
    RCC->AHB2ENR|=(1U<<8);

    // Configure the injected sequence register for channel 16 (temperature sensor)
    uint32_t* JSQR = (uint32_t*)0x40012038;  // Injected Sequence Register
    *JSQR |= (16 << 15);  // Set channel 16 for JSQ4

    // Setup Control Registers
    uint32_t* CR1 = (uint32_t*)0x40012004;  // Control Register 1
    uint32_t* CR2 = (uint32_t*)0x40012008;  // Control Register 2
    *CR2 |= (0b01 << 20) | (1 << 0);  // Enable continuous conversion

    // Setup the Common Control Register
    uint32_t* CCR = (uint32_t*)0x40012304;  // Common Control Register
    *CCR |= (1 << 23);  // Configure common functionalities
}

// Function to read the ADC value
uint16_t Read_ADC() {
    // Start the ADC conversion
    uint32_t* CR2 = (uint32_t*)0x40012008;  // Control Register 2
    *CR2 |= (1 << 22);  // Start conversion

    // Wait for conversion to complete
    uint32_t* SR = (uint32_t*)0x40012000;  // Status Register
    while (((*SR >> 2) & 1) == 0);  // Wait until the conversion is complete

    // Read the ADC value from the injected data register
    uint32_t* JDR4 = (uint32_t*)0x40012020;  // Injected Data Register 4
    return *JDR4;  // Return the ADC value
}

int main() {
	uint16_t vin,temp;
ADC_init();
    while (1) { 
   uint16_t  cnt = Read_ADC();  // Read the ADC value
    vin = (cnt * 3) / 4095.0;  // Convert ADC value to voltage
    temp = ((vin - 0.76) / 2.5) + 25;  // Convert voltage to temperature



//		     Car(Turn_Left,0,0); 
			
//        Avoid_Obstacle();  

//        uint16_t encoder_left = read_encoder_left();
//        uint16_t encoder_right = read_encoder_right();
//        char buffer[100];
//        sprintf(buffer, "Encoder Left: %d, Encoder Right: %d\n", encoder_left, encoder_right);
//        
//        Uart_DMAStream5_Init_Transmit((uint32_t)buffer, strlen(buffer));


//        } else if (Uart_Data_Buffer[0] == 'B') {
//            Move_Backward();
//        } else if (Uart_Data_Buffer[0] == 'L') {
//            Turn_Left();
		//	Car(Turn_Left,300,300);
//        } else if (Uart_Data_Buffer[0] == 'R') {
//            Turn_Right();
//        } else if (Uart_Data_Buffer[0] == 'S') {
//            Stop();
//        }
    }
}

