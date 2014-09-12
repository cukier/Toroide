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

#define botStart	PIN_B0
#define bufferSize	750

short ctrl;

long vetor[bufferSize];
long cont;
int main(void) {

	SETUP_ADC(ADC_CLOCK_INTERNAL);
	SETUP_ADC_PORTS(AN0);
	set_adc_channel(0);

	while (TRUE) {

		if (!input(botStart)) {
			delay_ms(100);
			if (!input(botStart) && !ctrl) {
				ctrl = TRUE;
				cont = 0;
				while (cont < bufferSize) {
					vetor[cont++] = read_adc();
					while (!adc_done())
						;
				}
				for (cont = 0; cont < bufferSize; ++cont) {
					printf("%lu\n\r", vetor[cont]);
				}
				cont = 0;
			} else if (ctrl)
				ctrl = FALSE;
		}
	}
	return 0;
}
