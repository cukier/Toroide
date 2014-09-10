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

#define padrao 100

long reed;
long reedAux;

float freq;

int latencia = padrao;

float aux;

int main(void) {

	SETUP_ADC(ADC_CLOCK_INTERNAL);
	SETUP_ADC_PORTS(AN0_AN1_AN3);

	if (!latencia)
		latencia = padrao;

	while (TRUE) {

		set_adc_channel(0);
		delay_ms(latencia);
		reed = read_adc();

		if (reedAux != reed) {
			reedAux = reed;
			freq = (float) (59 * reed / 1024) + 1;
			latencia = (int) 1 / freq * 500;
			printf("Lat: %ums Freq: %fHz\n\r", latencia, freq);
		}

		set_adc_channel(3);
		delay_ms(latencia);
		reed = read_adc();
		reedAux = reed;
		printf("Tensao: %f\n\r", (float) 5 * reed / 1024);
	}
	return 0;
}
