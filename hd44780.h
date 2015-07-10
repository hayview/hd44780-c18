#ifndef HD44780_H
#define HD44780_H

#include <p18cxxx.h>
#include "delay.h"

#define HD44780_REGISTER_COMMAND	0x10
#define HD44780_REGISTER_DATA		0x01

#define HD44780_initPinIO()		   {TRISBbits.RB4=0; TRISBbits.RB5=0; TRISD=0x00;}
#define HD44780_EN_PIN				LATBbits.LATB5
#define HD44780_RS_PIN				LATBbits.LATB4
#define HD44780_DATA_PORT			LATD

void HD44780_Init(void); 
void HD44780_WriteString(const rom char *s);
void HD44780_GoToPoint(char row, char col);

#endif

