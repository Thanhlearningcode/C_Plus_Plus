; Author: NGUYEN VAN THANH
RCC_BASE           EQU 0x40023800
GPIOD_BASE         EQU 0x40020C00

ONESECOND          EQU 1000     

    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
	EXTERN HCSR04_Read
    EXPORT TM_HCSR04_Init


TM_HCSR04_Init
    LDR     R0, =RCC_BASE + 0x30        ; AHB1ENR
    LDR     R1, [R0]
    ORR     R1, R1, #1<<3               ; GPIOD EN
    STR     R1, [R0]

    ; Configure GPIOD Pin 0 is Output for TRIG
    LDR     R0, =GPIOD_BASE + 0x00      ; MODER
    LDR     R1, [R0]
    BIC     R1, R1, #3<<0              
    ORR     R1, R1, #1<<0             
    STR     R1, [R0]

    ; Configure GPIOD is PUSH-PULL
    LDR     R0, =GPIOD_BASE + 0x04      ; OTYPER
    LDR     R1, [R0]
    BIC     R1, R1, #1<<0                          
    STR     R1, [R0]

    ; Configure GPIOD SPEED IS MEDIUM
    LDR     R0, =GPIOD_BASE + 0x08      ; OSPEEDR
    LDR     R1, [R0]
    BIC     R1, R1, #3<<0   
    ORR     R1, R1, #1<<0 
    STR     R1, [R0]

    ; Configure GPIOD Pin 2 is Input for Echo
    LDR     R0, =GPIOD_BASE + 0x00      ; MODER
    LDR     R1, [R0]
    BIC     R1, R1, #3<<4              
    STR     R1, [R0]

    LDR     R0, =GPIOD_BASE + 0x08      ; OSPEEDR
    LDR     R1, [R0]
    BIC     R1, R1, #3<<4   
    ORR     R1, R1, #1<<4 
    STR     R1, [R0]

    LDR     R0, =GPIOD_BASE + 0x0C      ; PUPDR
    LDR     R1, [R0]
    BIC     R1, R1, #3<<4   
    ORR     R1, R1, #2<<4 
    STR     R1, [R0]

    ; GPIOD->ODR &= ~(1U << 0);    
    LDR     R0, =0x40020C00+0x14       
    LDR     R1, [R0]               
    BIC     R1, R1, #1 << 0  
    STR     R1, [R0]               
    BL      HCSR04_Read
    
    CMP     R0, #0
    BGE     return_1               

    MOVS    R0, #0
    BX      LR

return_1
    MOVS    R0, #1
    BX      LR

    ALIGN
    END
