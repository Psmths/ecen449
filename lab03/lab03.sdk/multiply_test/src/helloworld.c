#include <stdio.h>
#include <xparameters.h>
#include <multiply.h>
#include "platform.h"

//Memory Map of multiply IP
//0x43C00000	r0		32b
//0x43C00004	r1		32b
//0x43C00008	r2		32b
//For whatever reason it needs 65k of memory???

void print(char *str);

int main()
{
    unsigned char i; //Iterator for the loop
    unsigned char max_val = 16; //Iterations to run
    unsigned int result; //Result of IP block

	init_platform();

    print("---------- Multiply Test Program ----------\n\r");
    printf("\t+ multiply: I am at offset %x\n\r", XPAR_MULTIPLY_0_S00_AXI_BASEADDR);
    for (i = 0; i <= max_val; i++){

    	MULTIPLY_mWriteReg(XPAR_MULTIPLY_0_S00_AXI_BASEADDR, 0x00, i); //Load first value into reg. 1
    	MULTIPLY_mWriteReg(XPAR_MULTIPLY_0_S00_AXI_BASEADDR, 0x04, max_val - i); //Load second value into reg. 2
    	result = MULTIPLY_mReadReg(XPAR_MULTIPLY_0_S00_AXI_BASEADDR, 0x08); //Read result from reg 3

    	//Print results of operation
    	printf("R0: %d\tR1: %d\tR2: %d\tOPERATION IS R0 * R1\n\r", i, max_val-i,result);

    }

    cleanup_platform();
    return 0;
}
