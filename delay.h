#ifndef DELAY_H_
#define DELAY_H_

#include <delays.h>

#define delay1MicroSecond()	   {Delay10TCYx(1); Delay1TCY(); Delay1TCY();}
#define delay5MicroSecond()		Delay10TCYx(6) 
#define delay10MicroSecond()	Delay10TCYx(12)
#define delay50MicroSecond()	Delay10TCYx(60)
#define delay100MicroSecond()	Delay100TCYx(12)
#define delay200MicroSecond()	Delay100TCYx(24)
#define delay1MiliSecond()		Delay1KTCYx(12)
#define delay2MiliSecond()		Delay1KTCYx(24)
#define delay5MiliSecond()		Delay1KTCYx(60)
#define delay10MiliSecond()		Delay10KTCYx(12)
#define delay50MiliSecond()		Delay10KTCYx(60)
#define delay100MiliSecond()	Delay10KTCYx(120)	
#define delay200MiliSecond()	Delay10KTCYx(240)
#define delay1Second()		   {Delay10KTCYx(240); Delay10KTCYx(240); Delay10KTCYx(240);\
								Delay10KTCYx(240); Delay10KTCYx(240);}
#define delay2Second()		   {delay1Second(); delay1Second();}
#define delay5Second()		   {delay2Second(); delay2Second(); delay1Second();}
#define delay10Second()		   {delay5Second(); delay5Second();}

#endif