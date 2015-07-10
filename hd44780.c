#include "hd44780.h"
#include "delay.h"

void HD44780_Clock(void);
void HD44780_WriteByte(char reg, char dat);
void HD44780_WriteData(char dat);
void HD44780_WriteCommand(char dat);

void HD44780_Clock(void)
{
	HD44780_EN_PIN=1;			// starts data read
	delay50MicroSecond();
	HD44780_EN_PIN=0;			// starts data write
}
	
void HD44780_WriteByte(char reg, char dat)
{
	if(reg == HD44780_REGISTER_DATA)
	{
		HD44780_RS_PIN=1;
	}
	
	if(reg == HD44780_REGISTER_COMMAND)
	{
		HD44780_RS_PIN=0;
	}
	
	HD44780_EN_PIN=0;
	
	HD44780_DATA_PORT = dat;
	HD44780_Clock();
}

void HD44780_WriteData(char dat)
{
	HD44780_WriteByte(HD44780_REGISTER_DATA, dat);
	delay50MicroSecond();
}

void HD44780_WriteCommand(char dat)
{
	HD44780_WriteByte(HD44780_REGISTER_COMMAND, dat);
	delay2MiliSecond();
}

void HD44780_Init(void)
{
	//Using initialize by instruction
	//After power on Wait for LCD to Initialize
	delay100MiliSecond();
	HD44780_initPinIO();
	
	HD44780_EN_PIN	 = 0;
    HD44780_RS_PIN	 = 0;
	HD44780_DATA_PORT = 0x30;
	HD44780_Clock();
	delay5MiliSecond();
	
	HD44780_DATA_PORT = 0x30;
	HD44780_Clock();
	delay200MicroSecond();
	
    HD44780_DATA_PORT = 0x30;
	HD44780_Clock();
	delay200MicroSecond();
		
	// FUNCTION SET				| 0  0  1  1  N  F  *  * |
	// BIN_OR_BIT_MASK:			{ 0  0  1  1  1  0  0  0 }
	HD44780_WriteCommand(0x38);	// N = 1; 2 lines, F = 0; 5x8 dots
	delay5MiliSecond();
	// DISPLAY OFF
	HD44780_WriteCommand(0x0C);
	delay5MiliSecond();
	// DISPLAY CLEAR
	HD44780_WriteCommand(0x01);
	delay5MiliSecond();
	// ENTRY MODE SET			| 0  0  0  0  0  1  I/D  S |
	// BIN_OR_BIT_MASK:			{ 0  0  0  0  0  1   1   0 }
	HD44780_WriteCommand(0x06);	// I/D = 1; Increment by 1, S = 0; No shift
	delay5MiliSecond();
	// HOME POSITION
	HD44780_WriteCommand(0x80);
}

void HD44780_WriteString(const rom char *s)
{
	while(*s)
	{
		HD44780_WriteData(*s);
		s++;
	}
}
	
void HD44780_GoToPoint(char row, char col)
{
	char DDRAM_address;
	
	if(row<1) row=1;				// first position user-defined as (1,1)
	if(col<=1)col=0;				// but HD44780 defines as (0,0)
	else col=col-1;

	if(row==1) DDRAM_address = 0x80+col;		// 0x80 for set DDRAM address command
	if(row==2) DDRAM_address = 0x80+0x40+col;	// 0x40 for second line DDRAM address

	HD44780_WriteCommand(DDRAM_address);
}
