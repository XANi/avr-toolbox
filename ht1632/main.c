
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
  for (byte i=0;i<15;i++) HTleds[i]=0b11010101<<(i%2);  HTsendscreen();
  for (byte i=16;i<32;i++) HTleds[i]=0b10010111<<(i%2);  HTsendscreen();
  _delay_ms(1000);
  byte c=0;
  while(1) {
    //    _delay_ms(10);
    char r;
    if (c == 0 ) {
      c = 1;
      r = 1;
    }
    else {
      c = 0;
      r = 0;
    }
    for (byte i=0;i<32;i++)
    {
      HTleds[i]=r;
      r++;
    }
    HTsendscreen();
  }

}
