#include "o3.h"
#include "gpio.h"
#include "systick.h"

#define PORT_SIZE 		36
#define NUMBER_OF_PORTS	6


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

typedef enum {SEC_ADJ, MIN_ADJ, HOUR_ADJ, COUNT_DOWN, ALARM} states_t;
states_t currentState = SEC_ADJ;
int seconds = 0;
int minutes = 0;
int hours = 0;



typedef struct{
	volatile word CTRL;
	volatile word MODEL;
	volatile word MODEH;
	volatile word DOUT;
	volatile word DOUTSET;
	volatile word DOUTCLR;
	volatile word DOUTTGL;
	volatile word DIN;
	volatile word PINKLOCKN;
} GPIO_port_t;

typedef struct {
	volatile word EXTIPSELL;
	volatile word EXTIPSELH;
	volatile word EXTIRISE;
	volatile word EXTIFALL;
	volatile word IEN;
	volatile word IF;
	volatile word IFS;
	volatile word IFC;
	volatile word ROUTE;
	volatile word INSENSE;
	volatile word LOCK;
	volatile word CTRL;
	volatile word CMD;
	volatile word EM4WUEN;
	volatile word EM4WUPOL;
	volatile word EM4WUCAUSE;
} GPIO_config_t;

typedef struct {
	volatile GPIO_port_t PORT[NUMBER_OF_PORTS];
	volatile word padding[10];
	volatile GPIO_config_t CONFIG;
} GPIO_map_t;

typedef struct {
	volatile word CTRL;
	volatile word LOAD;
	volatile word VAL;
	volatile word CALIB;
} SYSTICK_map_t;

void GPIO_buttonSetup(GPIO_map_t* GPIO, const int buttonPort, const int buttonPin){
	volatile word* address = 0;
	int bitshift = 0;
	word mask = 0;

	// --- input mode ---
	if(buttonPin <= 7){
		address = &(GPIO->PORT[buttonPort].MODEL);
		bitshift = buttonPin*4;
	} else{
		address = &(GPIO->PORT[buttonPort].MODEH);
		bitshift = (buttonPin - 8)*4;
	}
	mask = ~(0b1111 << bitshift);
	*address &= mask;
	mask = GPIO_MODE_INPUT << bitshift;
	*address |= mask;

	// --- EXTIPSEL ---
	if(buttonPin <= 7){
		address = &(GPIO->CONFIG.EXTIPSELL);
		bitshift = buttonPin*4;
	} else{
		address = &(GPIO->CONFIG.EXTIPSELH);
		bitshift = (buttonPin - 8)*4;
	}
	mask = ~(0b1111 << bitshift);
	*address &= mask;
	mask = buttonPort << bitshift;
	*address |= mask;

	// --- EXTIFALL ---
	mask = 0b1 << buttonPin;
	GPIO->CONFIG.EXTIFALL |= mask;

	// --- IF ---
	GPIO->CONFIG.IF = 0; // clears any previously unhandled interupts

	// --- IEN ---
	GPIO->CONFIG.IEN |= 0b1 << buttonPin;
}

void GPIO_ledSetup(GPIO_map_t* GPIO, const int ledPort, const int ledPin){
	volatile word* address = 0;
	int bitshift = 0;
	word mask = 0;

	// --- DOUT ---
	address = &(GPIO->PORT[ledPort].DOUT);
	mask = ~(0b1 << ledPin);
	*address = *address & mask; // set bit to zero

	// --- MODE ---
	if (LED0_PIN <= 7){
		address = &(GPIO->PORT[ledPort].MODEL);
		bitshift = ledPin*4;
	} else{
		address = &(GPIO->PORT[ledPort].MODEH);
		bitshift = (ledPin - 8)*4;
	}
	mask = ~(0b1111 << bitshift);
	*address = *address & mask;
	mask = GPIO_MODE_OUTPUT << bitshift;
	*address = *address | mask;
}

void GPIO_setup(GPIO_map_t* GPIO){
	GPIO_buttonSetup(GPIO, PB0_PORT, PB0_PIN);
	GPIO_buttonSetup(GPIO, PB1_PORT, PB1_PIN);
	GPIO_ledSetup(GPIO, LED0_PORT, LED0_PIN);
}

void SYSTICK_toggleEnable(SYSTICK_map_t* SYSTICK);

void LED_enable(GPIO_map_t* GPIO, const int ledPort, const int ledPin){
	GPIO->PORT[ledPort].DOUTSET |= 0b1 << ledPin;
}

void LED_disable(GPIO_map_t* GPIO, const int ledPort, const int ledPin){
	GPIO->PORT[ledPort].DOUTCLR |= 0b1 << ledPin;
}

void GPIO_EVEN_IRQHandler(void){
	// PB1 pressed
	switch (currentState){
		case SEC_ADJ:
			currentState = MIN_ADJ;
			break;
		case MIN_ADJ:
			currentState = HOUR_ADJ;
			break;
		case HOUR_ADJ:
			currentState = COUNT_DOWN;
			SYSTICK_toggleEnable((SYSTICK_map_t*)SYSTICK_BASE);
			break;
		case ALARM:
			currentState = SEC_ADJ;
			break;
		default:
			break;
		}

	((GPIO_map_t*)GPIO_BASE)->CONFIG.IFC |= 0b1 << PB1_PIN;
}

void GPIO_ODD_IRQHandler(void){
	// PB0 pressed
	switch (currentState){
	case SEC_ADJ:
		seconds = (seconds + 1)%60;
		break;
	case MIN_ADJ:
		minutes = (minutes + 1)%60;
		break;
	case HOUR_ADJ:
		hours = (hours + 1)%100;
		break;
	default:
		break;
	}

	((GPIO_map_t*)GPIO_BASE)->CONFIG.IFC |= 0b1 << PB0_PIN;
}

void SYSTICK_setup(SYSTICK_map_t* SYSTICK){
	SYSTICK->LOAD = FREQUENCY;
	SYSTICK->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
	SYSTICK->VAL = SYSTICK->LOAD;
}

void SYSTICK_toggleEnable(SYSTICK_map_t* SYSTICK){
	SYSTICK->CTRL ^= SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void){
	if (seconds > 0){
		seconds--;
	}else{

		if (minutes > 0){
			minutes--;
		}else{
			if (hours > 0){
				hours--;
			}else{
				currentState = ALARM;
				SYSTICK_toggleEnable((SYSTICK_map_t*)SYSTICK_BASE);
				return;
			}
			minutes = 59;
		}
		seconds = 59;
	}
}





int main(void){
    init();
    GPIO_setup((GPIO_map_t*)GPIO_BASE);
    SYSTICK_setup((SYSTICK_map_t*)SYSTICK_BASE);

    char time[7];

    while(1){
    	time_to_string(time, hours, minutes, seconds);
    	lcd_write(time);
    	switch(currentState){
    	case ALARM:
    		LED_enable((GPIO_map_t*)GPIO_BASE, LED0_PORT, LED0_PIN);
    		break;
    	default:
    		LED_disable((GPIO_map_t*)GPIO_BASE, LED0_PORT, LED0_PIN);
    		break;
    	}
    }


    return 0;

}

