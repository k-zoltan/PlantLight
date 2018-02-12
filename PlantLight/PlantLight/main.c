/*
 * PlantLight.c
 *
 * Created: 2018. 02. 06. 19:16:01
 * Author : zoltan
 */ 

#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "twiSlave.h"

#define SLAVE_ADRS	0x40

#define LED_DDR		DDRD			// Port direction bit. 0:Input 1:output
#define LED_PORT	PORTD			// Port being used.
#define LED_P		PD0				// Port bit being used.

#define ANALOG_PORT PINC
#define ANALOG_DDR DDRC
#define LIGHT PINC0

#define COMM_CHECK 0x10
#define READ_LIGHT 0xA0

#define OK 0x00
#define NOK 0xFF

void setupADC(void) {
	ADMUX |= (1 << REFS0) | (1 << ADLAR);
	ADCSRA |= (1 << ADPS1) | (1 << ADPS2) | (1 << ADEN);
}

unsigned char readLight(void) {
	ADMUX = (ADMUX & 0b11110000) | LIGHT;
	ADCSRA |= (1<<ADSC);    // ADC konverzio elinditasa
	while (ADCSRA & (1<<ADSC));    // varas az atalakitasra
	ADCSRA |= (1<<ADSC);         // konverzió elindítás
	while (ADCSRA & (1<<ADSC));    // varas az atalakitasra
	return (ADCH);
}

void shortBlink() {
	LED_PORT |= (1<<LED_P);			// Turn LED ON.
	_delay_ms(100);
	LED_PORT &= ~(1<<LED_P);		// Turn LED OFF.
	_delay_ms(100);
}
void longBlink() {
	LED_PORT |= (1<<LED_P);			// Turn LED ON.
	_delay_ms(500);
	LED_PORT &= ~(1<<LED_P);		// Turn LED OFF.
	_delay_ms(500);
}


int main(void)
{
	setupADC();
	uint8_t data;
	LED_DDR |= (1<<LED_P);			// Set LED pin as an output.
	twiSlaveInit( SLAVE_ADRS );		// Initialize TWI hardware for Slave operation.
	sei();							// Enable interrupts.
	twiSlaveEnable();				// Enable the TWI interface to receive data.
	static char light;
	twiClearOutput();
    while (1) 
    {
		if( twiDataInReceiveBuffer() ) {
			_delay_ms(10);
			data = twiReceiveByte();
			if( data == COMM_CHECK) {
				shortBlink();
				shortBlink();
				twiClearOutput();
				twiTransmitByte(OK);
			} 
			else if (data == READ_LIGHT) {
				light = readLight();
				twiTransmitByte(light);
			}
			else {
				longBlink();
				longBlink();
				twiTransmitByte(NOK);
			}
		}
    }
}

