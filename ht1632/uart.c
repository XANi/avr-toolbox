
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "lib/lcd.h"

#define XTAL   16000000
#define F_CPU 16000000


//set desired baud rate
#define BAUDRATE 9600

//calculate UBRR value
#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)



#define tbi(PORT,BIT)        PORT^=_BV(BIT)  
#define sbi(port, bit)   (port) |= (1 << (bit))
#define cbi(port, bit)   (port) &= ~(1 << (bit))
#define gbi(port, bit)   (port) & (1 << (bit))


char usart_get_char() {
	uint8_t tmp;
		while(!(UCSRA&(1<<RXC))){};
		tmp=UDR;
		return tmp;
}
void usart_send_char(uint8_t tmp) {
		while (!(UCSRA&(1<<UDRE))){};
		UDR=tmp;
}

void main() {
	DDRA = 0xFF;
	DDRD = 0xFF;
	DDRC = 0xFF;

	// UART init
	//Set baud rate

	UBRRL=UBRRVAL; //low byte
	UBRRH=(UBRRVAL>>8); //high byte
	//Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
	UCSRC=(1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|
		(0<<USBS)|(0<<UCSZ2)|(1<<UCSZ1)|(1<<UCSZ0);

//Enable Transmitter and Receiver
	UCSRB=(1<<RXEN)|(1<<TXEN);
	uint8_t serial_tmp;

	sbi(PORTC,PC4);
	lcd_init(LCD_DISP_ON_CURSOR_BLINK);
	lcd_clrscr();
	//	loading();
	lcd_puts("UART:");
	while(1) {
		serial_tmp=usart_get_char();
		if(serial_tmp==17) {
			lcd_gotoxy(0,0);
		} else if (serial_tmp==18) {
			lcd_gotoxy(0,1);
		} else if (serial_tmp==19) {
			lcd_clrscr();
		} else {
			lcd_putc(serial_tmp);
		}
		usart_send_char(serial_tmp); 
	}
}
