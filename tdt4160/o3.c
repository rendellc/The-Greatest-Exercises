#include "o3.h"
#include "gpio.h"
#include "systick.h"

#define PORT_SIZE 		36
#define NUMBER_OF_PORTS	6

#define GPIO_PORT_CTRL 		0
#define GPIO_PORT_MODEL 	4
#define GPIO_PORT_MODEH 	8
#define GPIO_PORT_DOUTSET	16
#define GPIO_PORT_DOUTCLR 	20

#define GPIO_EXTIPSELL 	256
#define GPIO_EXTIPSELH 	260
#define GPIO_EXTIFALL	268
#define GPIO_IEN 		272
#define GPIO_IFC 		284


#define SYSTICK_CTRL  0
#define SYSTICK_LOAD  4
#define SYSTICK_VAL   8
#define SYSTICK_CALIB 12

#define LED0_PIN  	2
#define LED0_PORT	GPIO_PORT_E
#define PB0_PIN  	9
#define PB0_PORT 	GPIO_PORT_B
#define PB1_PIN  	10
#define PB1_PORT 	GPIO_PORT_B


/**************************************************************************//**
 * @brief Konverterer nummer til string 
 * Konverterer et nummer mellom 0 og 99 til string
 *****************************************************************************/
void int_to_string(char *timestamp, unsigned int offset, int i) {
    if (i > 99) {
        timestamp[offset]   = '9';
        timestamp[offset+1] = '9';
        return;
    }

    while (i > 0) {
	    if (i >= 10) {
		    i -= 10;
		    timestamp[offset]++;
		
	    } else {
		    timestamp[offset+1] = '0' + i;
		    i=0;
	    }
    }
}

/**************************************************************************//**
 * @brief Konverterer 3 tall til en timestamp-string
 * timestamp-argumentet må være et array med plass til (minst) 7 elementer.
 * Det kan deklareres i funksjonen som kaller som "char timestamp[7];"
 * Kallet blir dermed:
 * char timestamp[7];
 * time_to_string(timestamp, h, m, s);
 *****************************************************************************/
void time_to_string(char *timestamp, int h, int m, int s) {
    timestamp[0] = '0';
    timestamp[1] = '0';
    timestamp[2] = '0';
    timestamp[3] = '0';
    timestamp[4] = '0';
    timestamp[5] = '0';
    timestamp[6] = '\0';

    int_to_string(timestamp, 0, h);
    int_to_string(timestamp, 2, m);
    int_to_string(timestamp, 4, s);
}

void setupGPIO();
void GPIO_setupButton(const int button_port, const int button_pin);
void setupSYSTICK();


//typedef enum {SEC_ADJ, MIN_ADJ, HOUR_ADJ, COUNT_DOWN, ALARM} states_t;
//states_t currentState = SEC_ADJ;



void GPIO_setupLed(){

}

void GPIO_setupButton(const int button_port, const int button_pin){
	int bitShift = 0;

	// --- EXTIPSEL ---
	volatile uint32_t* portAddress = (uint32_t*) GPIO_BASE;

	if (button_pin <= 7){
		portAddress = (uint32_t*)((byte*)portAddress + GPIO_EXTIPSELL);
		bitShift = button_pin*4;
	}
	else{
		portAddress = (uint32_t*)((byte*)portAddress + GPIO_EXTIPSELH);
		bitShift = (button_pin - 8)*4;
	}
	word mask = ~(0b1111 << bitShift);
	*portAddress = (word)(*portAddress & mask); // apply negative mask
	mask = (button_port << bitShift);
	*portAddress = (word)(*portAddress | mask);

	// --- EXTIFALL ---
	portAddress = (uint32_t*) GPIO_BASE;
	portAddress = (uint32_t*)((byte*)portAddress + GPIO_EXTIFALL);
	*portAddress = (word)(*portAddress | (0b1 << button_pin));

	// --- IF initialize ---
	portAddress = (uint32_t*) GPIO_BASE;
	portAddress = (uint32_t*)((byte*)portAddress + GPIO_IFC);
	*portAddress = (word)*portAddress | (0b1 << button_pin); // set all interrupt flags to zero

	// --- set mode, DIN ---
	portAddress = (uint32_t*)((byte*)GPIO_BASE + PORT_SIZE*button_port);
	if (button_pin <= 7){

	}

	// --- IEN ---
	portAddress = (uint32_t*) GPIO_BASE;
	portAddress = (uint32_t*)((byte*)portAddress + GPIO_IEN);
	*portAddress = (word)*portAddress | (0b1 << button_pin);
}


int main(void){
    init();

    GPIO_setupButton(PB0_PORT, PB0_PIN);
    GPIO_setupButton(PB1_PORT, PB1_PIN);

    while(1){

    }


    return 0;
}

