#include <xparameters.h>
#include <xgpio.h>
#include <xstatus.h>
#include <xil_printf.h>

//Definitions
#define GPIO_DEVICE_ID XPAR_LED_DEVICE_ID //GPIO device for LEDs
#define WAIT_VAL 10000000 //clock division parameter

int delay (void);

int main() {
	int count; //loop counter
	int count_masked; //low nibble of counter
	XGpio leds; //LED GPIO
	int status; //boolean
	
	status = XGpio_Initialize(&leds, GPIO_DEVICE_ID); //status of GPIO bind
	XGpio_SetDataDirection(&leds, 1, 0x00); //pin directions
	if (status != XST_SUCCESS) {
		xil_printf("Initialization failed");
	}
	count = 0;
    //infinite loop
	while(1) {
		count_masked = count & 0xF;
		XGpio_DiscreteWrite(&leds, 1, count_masked); //output to GPIO
		xil_printf("Value of LEDs = 0x%x\n\r", count_masked);
		delay(); 
		count++;
	}
	return(0);
}

int delay(void) {
    //Loop for WAIT_VAL cycles
	volatile int delay_count = 0;
	while(delay_count < WAIT_VAL)
		delay_count++;
	return (0);
}
