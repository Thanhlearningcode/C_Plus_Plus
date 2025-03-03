RCC_BASE     EQU 0x40023800
GPIOD_BASE   EQU 0x40020C00
TIM4_BASE    EQU 0x40000800 

       AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        EXPORT TIM4_Init
        EXPORT PWM_1
		EXPORT PWM_2
TIM4_Init
	LDR R0,=RCC_BASE + 0x40 ; APB1ENR
	LDR R1,[R0]
	ORR R1,R1,#1<<2 ; TIM4 EN
	STR R1,[R0] 
	
	LDR R0,=RCC_BASE + 0x30 ; AHB1ENR
	LDR R1,[R0]
	ORR R1,R1,#1<<3 ; RCC GPIOD EN
	STR R1,[R0]
	
	; GPIOD12 CHANNEL 1 (PWM)
	LDR R0,=GPIOD_BASE + 0x00 ; MODER
	LDR R1,[R0]
	BIC R1,R1,#3<<24
	ORR R1,R1,#2<<24 ; AF MODE
	STR R1,[R0]
	
		; GPIOD13 CHANNEL 2 (PWM)
	LDR R0,=GPIOD_BASE + 0x00 ; MODER
	LDR R2,[R0]
	BIC R2,R2,#3<<26
	ORR R2,R2,#2<<26 ; AF MODE
	STR R2,[R0]
		
    LDR R0,=GPIOD_BASE + 0x24 ; AFH
	LDR R1,[R0]
	ORR R1,R1,#2<<16 ; AF02 MAPPING
	STR R1,[R0]
	
	LDR R0,=GPIOD_BASE + 0x24 ; AFH
	LDR R2,[R0]
	ORR R2,R2,#2<<20 ; AF02 MAPPING
	STR R2,[R0]

    LDR R0, =TIM4_BASE + 0x2C
    MOVW R1, #999 ; Set auto-reload register to 999
    STR R1, [R0]
		
    LDR R0, =TIM4_BASE + 0x28
    MOVW R1, #15 ; prescaler to 15
    STR R1, [R0]

    ; Configure CCR1 to 0
    LDR R0, =TIM4_BASE + 0x34
    MOV R1, #0
    STR R1, [R0]

    ; Configure CCR2 to 0
    LDR R0, =TIM4_BASE + 0x38
    MOV R1, #0
    STR R1, [R0]

    LDR R0, =TIM4_BASE + 0x18
    LDR R1, [R0]
    BIC R1, R1, #2 << 0 ; Configure CC1 as output
    STR R1, [R0]


    LDR R0, =TIM4_BASE + 0x18
    LDR R1, [R0]
    ORR R1, R1, #6 << 4 ; PWM mode 1
    STR R1, [R0]
	
	LDR R0, =TIM4_BASE + 0x18
    LDR R2, [R0]
    BIC R2, R2, #2 << 8 ; Configure CC2 as output
    STR R2, [R0]

    LDR R0, =TIM4_BASE + 0x18
    LDR R2, [R0]
    ORR R2, R2, #6 << 12 ; PWM mode 2
    STR R1, [R0]

	LDR R0, =TIM4_BASE + 0x20 ; CCER
    ORR R1,R1,#1<<0 ; Enable capture1
    STR R1, [R0]
	
	LDR R0, =TIM4_BASE + 0x20 ; CCER
    ORR R1,R1,#1<<4 ; Enable capture 2
    STR R1, [R0]
	

    ; Configure TIM4 CR1
    LDR R0, =TIM4_BASE + 0x00
    LDR R1, [R0]
    ORR R1, R1, #1<<0  ; Enable counter
    STR R1, [R0]
    BX LR

PWM_1
    PUSH {R4, LR}         
    LDR R4, =TIM4_BASE + 0x34 ; Load Address from CCR1
    STR R0, [R4]          
    POP {R4, LR}           
    BX LR
PWM_2
    PUSH {R5, LR}         
    LDR R5, =TIM4_BASE + 0x38 ; Load Address from CCR2
    STR R0, [R5]          
    POP {R5, LR}           	
    BX LR

    ALIGN
        END
