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

int reed;
int freq;
int freqAux;
int latencia = 100;

float aux;

int main(void) {

	SETUP_ADC(ADC_CLOCK_INTERNAL);
	SETUP_ADC_PORTS(AN0_AN1_AN3);

	while (TRUE) {

		set_adc_channel(0);
		freq = read_adc();

		if (freq != freqAux) {
			freqAux = freq;
			aux = (59 * freq + 255) / 255;
			latencia = (int) 1000 / aux;
		}
		while (!adc_done())
			;
		set_adc_channel(1);
		reed = read_adc();

		printf("%u\n\r", reed);
		printf("%f\n\r", (float) reed / 255 * 5);

		delay_ms(latencia);
	}
	return 0;
}
