#include "stm32f4xx.h"
#include "tm_stm32f4_mfrc522.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_usart.h"
#include "stm32_ub_lcd_2x16.h"
#include "CE_SD_card_control.h"
#include "MENU.h"
#include "teclado.h"
#include <string.h>
#include <stdlib.h>


void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART2_Configuration(int BaudRate);
void NVIC_Configuration(void);

char Data_read;
char Tecla;
int BaudRate=9600;
char Text_opciones[]="ANDA";



int main(void)
{

	RCC_Configuration();
	GPIO_Configuration();
	Tecladoinit();
	LCDinit();

	USART2_Configuration(BaudRate);
	NVIC_Configuration();
	TM_MFRC522_Init();
	Menuinit();
	SysTick_Config( SystemCoreClock / 1000 );



	while (1)
	{
		Menu ( Tecla );
		Tecla = teclado ();
	}

}


/////////////////////// FUNCIONES /////////////////////////////////

void USART2_IRQHandler(void)
{
	int x;
	Data_read = USART_ReceiveData(USART2);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // espero reg libre para enviar

	for (x=0; x < (strlen(Text_opciones)); x++)
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_SendData(USART2, Text_opciones[x]);
	}
	return;
}


void RCC_Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	//  salidas
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	//  salidas
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//  salidas
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


}

void USART2_Configuration(int BaudRate)
{
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);
  }

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}
