#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO

#define UART_TX			GPIO_Pin_9
#define UART_RX			GPIO_Pin_10
#define UART_GPIO		GPIOA
typedef enum{
	Parity_Mode_NONE,
	Parity_Mode_ODD,
	Parity_Mode_EVENT
}Parity_Mode;

void delay_us(unsigned int us) {
    while (us--) {
      
        for (volatile int i = 0; i < 1000; i++);
    }
}
void RCC_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}
void GPIO_Config()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin = UART_TX | UART_RX;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(UART_GPIO, &GPIO_InitStruct);
	
}

void UART_Config(){
	USART_InitTypeDef UART_InitStruct;
	
	UART_InitStruct.USART_BaudRate = 9600;
	
	UART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	UART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	UART_InitStruct.USART_Parity = USART_Parity_No;
	
	UART_InitStruct.USART_StopBits = USART_StopBits_1;
	
	UART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1, &UART_InitStruct);
	USART_Cmd(USART1,ENABLE);
}

char USART_RecieveChar(USART_TypeDef *USARTx){
	USARTx->DR = 0x00;
	uint8_t tmp_data;
	tmp_data = USART_ReceiveData(USARTx);
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE)!=1);
	
	return tmp_data;
}

void USART_SendChar(USART_TypeDef *USARTx, uint8_t data){
	USARTx->DR = 0x00;
	USART_SendData(USARTx,data);
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) != 1);
}
void USART_StringSend(USART_TypeDef *USARTx, uint8_t *data){
	while(*data){
		USART_SendData(USARTx, *data);
		data++;
	}
}
void UART_Transmit(uint8_t DataValue) {
    
    GPIO_WriteBit(UART_GPIO, UART_TX, Bit_RESET);
    delay_us(104);

   
    for (unsigned char i = 0; i < 8; i++) {
        if ((DataValue & 0x01) == 0x01) {
            GPIO_WriteBit(UART_GPIO, UART_TX, Bit_SET); 
        } else {
            GPIO_WriteBit(UART_GPIO, UART_TX, Bit_RESET); // BIT 0
        }
        delay_us(104); 
        DataValue = DataValue >> 1;
    }


    GPIO_WriteBit(UART_GPIO, UART_TX, Bit_SET);
    delay_us(104);
}	
unsigned char UART_Receive(void){
	unsigned char DataValue = 0;
	while(GPIO_ReadInputDataBit(UART_GPIO, RX_Pin) == 1);
	delay_us(BRateTime);
	delay_us(BRateTime/2);
	for ( unsigned char i = 0; i < 8; i++ ){
		if ( GPIO_ReadInputDataBit(UART_GPIO, RX_Pin) == 1 ){
			DataValue |= (1<<i);}
		delay_us(BRateTime);
	}
	if ( GPIO_ReadInputDataBit(UART_GPIO, RX_Pin) == 1 ){
		delay_us(BRateTime/2);
		return DataValue;
	}
	//Xu li loi
}




uint8_t Parity_Generate(uint8_t data, Parity_Mode Mode){
	uint8_t count =0;
	uint8_t data1 = data;
	for(int i=0; i< 8; i++){
		if(data1 & 0x01){
			count++;
		}
		data1>>=1;
	}
	switch(Mode){
		case Parity_Mode_NONE:
			return data; 
			break;
		case Parity_Mode_ODD:
			if(count%2){
				return ((data<<1)|1);
			} else {
				return (data<<1);
			}
			break;
		case Parity_Mode_EVENT:
			if(!(count%2)){
				return ((data<<1)|1);
			} else {
				return (data<<1);
			}
			break;
		default:
			return data;
			break;
	}
}

uint8_t Parity_Check(uint8_t data, Parity_Mode Mode){
	uint8_t count =0;
	for(int i=0; i< 8; i++){
		if(data & 0x01){
			count++;
		}
		data>>=1;
	}
	switch(Mode){
		case Parity_Mode_NONE:
			return 1; 
			break;
		case Parity_Mode_ODD:
			return (count%2); 
			break;
		case Parity_Mode_EVENT:
			return (!(count%2)); 
			break;
		default:
			return 0;
			break;
	}
}



int main(){
	RCC_Config();
	GPIO_Config();
	UART_Config();
	
	while(1){
		
	}
}
