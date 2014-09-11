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
#define tmr0reg		0
#define bufferSize	600

short ctrl;

long vetor[bufferSize];
long cont;

#INT_TIMER0
void isr_timer0() {
	clear_interrupt(INT_TIMER0);
	set_timer0(tmr0reg);
	vetor[cont++] = read_adc();
	if (cont >= bufferSize)
		disable_interrupts(INT_TIMER0);
}

int main(void) {

	SETUP_ADC(ADC_CLOCK_INTERNAL);
	SETUP_ADC_PORTS(AN0);
	set_adc_channel(0);

	set_timer0(tmr0reg);
	setup_timer_0(T0_INTERNAL | T0_8_BIT);

	clear_interrupt(INT_TIMER0);
//	enable_interrupts(INT_TIMER0);
//	enable_interrupts(GLOBAL);

	while (TRUE) {

		if (!input(botStart)) {
			delay_ms(100);
			if (!input(botStart) && !ctrl) {
				ctrl = TRUE;
				enable_interrupts(INT_TIMER0);
				enable_interrupts(GLOBAL);
			}
		}

		if (cont >= bufferSize) {
//			delay_ms(1000);
			for (cont = 0; cont < bufferSize; ++cont) {
				printf("%lu\n\r", vetor[cont]);
			}
			return 0;
		}

	}
	return 0;
}
