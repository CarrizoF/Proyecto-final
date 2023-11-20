/*******************************
 * teclado.c
 *******************************/

#include "teclado.h"


uint16_t PIN_TECLADO_COL[4] = {GPIO_Pin_7, GPIO_Pin_6, GPIO_Pin_5, GPIO_Pin_4};
uint32_t PORT_TECLADO_COL[4] = {GPIOD_BASE, GPIOD_BASE, GPIOD_BASE, GPIOD_BASE};

uint16_t PIN_TECLADO_FIL[4] = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_0, GPIO_Pin_1};
uint32_t PORT_TECLADO_FIL[4] = {GPIOD_BASE, GPIOD_BASE, GPIOF_BASE, GPIOF_BASE};

char teclado (void)						// barrido del teclado
{
	int f;
	int c;
	char StatusTecla;
	char TeclaPresionada[4][4]={
			{'1','2','3','A'},
			{'4','5','6','B'},
			{'7','8','9','C'},
			{'*','0','#','D'},
	};


	for( f=0; f<4 ; f++)
	{
		GPIO_SetBits( PORT_TECLADO_FIL[f], PIN_TECLADO_FIL[f]);

		for( c=0; c<4 ; c++)
		{
			if (GPIO_ReadInputDataBit(PORT_TECLADO_COL[c], PIN_TECLADO_COL[c]))
			{
				delay_ms(20);
				if (GPIO_ReadInputDataBit(PORT_TECLADO_COL[c], PIN_TECLADO_COL[c]))
				{
					if(StatusTecla != TeclaPresionada[f][c])
					{
						StatusTecla=TeclaPresionada[f][c];
						GPIO_ResetBits( PORT_TECLADO_FIL[f], PIN_TECLADO_FIL[f]);
						return TeclaPresionada[f][c];
					}
				}
			}
		}
		GPIO_ResetBits( PORT_TECLADO_FIL[f], PIN_TECLADO_FIL[f]);
	}
return 'X';
}


void Tecladoinit()
{
	int i;

	GPIO_InitTypeDef GPIO_InitStructure;

	//for ( i=0; i<4 ; i++)						// filas teclado
		//GPIO_InitStructure.GPIO_Pin = PIN_TECLADO_FIL[i];

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); // entradas
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	//  salidas
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

}




