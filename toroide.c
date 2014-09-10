/*
 * toroide.c
 *
 *  Created on: 09/09/2014
 *      Author: cuki
 */

#include<18F452.h>
#DEVICE ADC=10

#FUSES HS

#USE delay(clock=16MHz)
#USE rs232(xmit=PIN_C6, BAUD=9600)

long reed;
long reedAux;

long freq;
long freqAux;

int latencia = 2;

float aux;

int main(void) {

	SETUP_ADC(ADC_CLOCK_INTERNAL);
	SETUP_ADC_PORTS(AN0_AN1_AN3);

	while (TRUE) {

		set_adc_channel(0);
		delay_ms(latencia);
		freq = read_adc();

		if (freq != freqAux) {
			freqAux = freq;
			printf("AN0: %f\n\r", (float) freq / 10.24);
		}

		set_adc_channel(3);
		delay_ms(latencia);
		reed = read_adc();

		if (reed != reedAux) {
			reedAux = reed;
			printf("AN3: %f\n\r", (float) reed / 10.24);
		}
	}
	return 0;
}
