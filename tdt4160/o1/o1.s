.thumb
.syntax unified

.include "gpio_constants.s"     // Register-adresser og konstanter for GPIO

.text
	.global Start

// R0 = GPIO_BASE
// R1 = portsize*LED_PORT + GPIO_PORT_DOUT = output register offset
// R2 = portsize*BUTTON_PORT + GPIO_PORT_DIN = input register offset
Start:
	LDR R0, =GPIO_BASE
	MOV R3, #PORT_SIZE  // 9w=36B

	// setup output
	MOV R1, #LED_PORT
	MUL R1, R1, R3 // portsize*LED_PORT
	LDR R4, =GPIO_PORT_DOUT  // 12B
	ADD R1, R1, R4	// R1 = output register offset

	// setup input
	MOV R2, #BUTTON_PORT
	MUL R2, R2, R3	// portsize*BUTTON_PORT
	LDR R4, =GPIO_PORT_DIN  // 28B
	ADD R2, R2, R4	// R2 = input register offset

	B #Loop

Loop:
	// all calls from here must preserve {R0, R1, R2}
	// check pin
	LDR R3, [R0, R2]
	MOV R4, #1
	LSL R4, R4, #BUTTON_PIN
	AND R3, R3, R4  // R3 = 0000 0001 0000 0000 hvis trykt
					// 	 og 0...0 ellers

	CMP R3, R4
	BEQ #noBlink
	BNE #Blink

	B #Loop // ikke nødvendig

Blink:
	MOV R3, #1
	LSL R3, R3, #LED_PIN
	STR R3, [R0, R1]

	B #Loop

noBlink:
	MOV R3, #0
	STR R3, [R0, R1]

	B #Loop

NOP // Behold denne pÃ¥ bunnen av fila

