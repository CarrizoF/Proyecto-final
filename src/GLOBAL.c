/*******************************
 * GLOBAL.c
 *******************************/

#include "GLOBAL.h"


void delay_ms( uint32_t ms)
{
	ms += Systick;
	while( ms > Systick );
}


