.thumb
.syntax unified

.include "gpio_constants.s"     // Register-adresser og konstanter for GPIO
.include "sys-tick_constants.s" // Register-adresser og konstanter for SysTick

.text
	.global Start

Start:
	// --- systick ---
	LDR R0, =SYSTICK_BASE
	// set frequency
	MOV R1, #SYSTICK_LOAD
	LDR R2, =FREQUENCY/10
	STR R2, [R0, R1]
	// enable systick
	MOV R1, #SYSTICK_CTRL
	MOV R2, #SysTick_CTRL_CLKSOURCE_Msk
	MOV R3, #SysTick_CTRL_TICKINT_Msk
	ORR R2, R2, R3
	STR R2, [R0, R1]
	//ADD R9, R0, R1 // address of systick enable


	// --- GPIO ---
	LDR R0, =GPIO_BASE

	// enable input mode
	MOV R3, #GPIO_PORT_MODEH
	LDR R4, [R0, R3]
	MOV R5, #0b1111
	LSL R5, #4
	MVN R5, R5
	AND R4, R4, R5
	MOV R5, #0b0001
	LSL R5, #4
	ORR R4, R4, R5
	STR R4, [R0, R3]

	// EXTIPSEL
	MOV R3, #GPIO_EXTIPSELH
	LDR R4, [R0, R3]
	MOV R5, #0b1111
	LSL R5, #4
	MVN R5, R5
	AND R4, R4, R5
	MOV R5, #0b0001
	LSL R5, #4
	ORR R4, R4, R5
	STR R4, [R0, R3]

	// EXTIFALL
	MOV R3, #GPIO_EXTIFALL
	LDR R4, [R0, R3]
	MOV R5, #0b1
	LSL R5, #BUTTON_PIN
	ORR R4, R4, R5
	STR R4, [R0, R3]

	// Init interupt flag (clear)
	MOV R3, #GPIO_IF
	LDR R4, [R0, R3]
	MOV R5, #0b0
	AND R4, R4, R5
	STR R4, [R0, R3]

	// Enable interupt
	MOV R3, #GPIO_IEN
	LDR R4, [R0, R3]
	MOV R5, #1
	LSL R5, #BUTTON_PIN
	ORR R4, R4, R5
	STR R4, [R0, R3]

	// setup led0
	MOV R2, #PORT_SIZE
	MOV R3, #LED_PORT
	MUL R2, R2, R3
	MOV R4, #GPIO_PORT_DOUT
	ADD R3, R2, R4 // offset from GPIO_BASE
	ADD R2, R0, R3 // Pin port addres

	// setup button
	MOV R3, #PORT_SIZE
	MOV R4, #BUTTON_PORT
	MUL R3, R3, R4
	MOV R4, #GPIO_PORT_DIN
	ADD R3, R3, R4
	ADD R3, R0, R3 // button port address

	// --- variables ---
	LDR R0, =SYSTICK_BASE
	LDR R9, =GPIO_BASE
	LDR R10, =tenths
	LDR R11, =seconds
	LDR R12, =minutes


    B Loop

/*
 Register layout
 	R0: SYSTICK_BASE
 	R1: button port address
	R2: led port address

	R9: status
		0b0 = pause
		0b1 = increment variables
	R10: tenths  (address)
	R11: seconds (address)
	R12: minutes (address)
*/


.global GPIO_ODD_IRQHandler
.thumb_func
GPIO_ODD_IRQHandler:
	//PUSH {LR}
	// change systick mode
	LDR R0, =SYSTICK_BASE
	MOV R4, #SYSTICK_CTRL
	LDR R5, [R0, R4]
	MOV R6, #SysTick_CTRL_ENABLE_Msk
	EOR R6, R5, R6
	STR R6, [R0, R4]


	// reset interupt flag
	LDR R9, =GPIO_BASE
	MOV R3, #GPIO_IFC
	LDR R4, [R9, R3]
	MOV R5, #0b1
	LSL R5, #BUTTON_PIN
	ORR R4, R4, R5
	STR R4, [R9, R3]

	//POP {LR}
	BX LR


.global SysTick_Handler
.thumb_func
SysTick_Handler:
	//PUSH {LR} // bevar LR
	updateTenths:
		LDR R5, [R10]
		CMP R5, #9
		BEQ resetTenths
			// increment
			MOV R4, #1
			ADD R5, R4, R5
			STR R5, [R10]

			B end_of_SysTick_Handler
		resetTenths:

			MOV R4, #0
			STR R4, [R10]
	updateSeconds:
		// toggle led
		LDR R4, [R2]
		MOV R5, #1
		LSL R5, #LED_PIN
		EOR R4, R4, R5
		STR R4, [R2]

		// update second
		LDR R5, [R11]
		CMP R5, #59
		BEQ resetSeconds
			// increment
			MOV R4, #1
			ADD R5, R4, R5
			STR R5, [R11]

			B end_of_SysTick_Handler
		resetSeconds:
			MOV R4, #0
			STR R4, [R11]
	updateMinutes:
		LDR R5, [R12]
		MOV R4, #1
		ADD R5, R4, R5
		STR R5, [R12]
	end_of_SysTick_Handler:
	//POP {LR}
	BX LR




Loop:
	B Loop

NOP // Behold denne på bunnen av fila

