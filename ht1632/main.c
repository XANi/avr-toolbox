
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>

#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "ht1632c.h"
//#define XTAL   16000000
//#define F_CPU 16000000


//set desired baud rate
//#define BAUDRATE 9600

//calculate UBRR value
//#define UBRRVAL ((F_CPU/(BAUDRATE*16UL))-1)

#define byte uint8_t
#define word uint16_t

#define tbi(PORT,BIT)        PORT^=_BV(BIT)
#define sbi(port, bit)   (port) |= (1 << (bit))
#define cbi(port, bit)   (port) &= ~(1 << (bit))
#define gbi(port, bit)   (port) & (1 << (bit))


int main() {
  HTpinsetup();
  HTsetup();
  //  HTcommand(HTsetbright + (2<<1) );
  HTleds[0]=2;
  HTleds[1]=6;
  for (byte i=0;i<32;i++) HTleds[i]=0b11010101<<(i%2);  HTsendscreen();
  while(1) {
    //    _delay_ms(10);
    for (byte i=0;i<32;i++) HTleds[i]=rand();  HTsendscreen();
  }

}
