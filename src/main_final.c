
// PROYECTO FINAL ASISTENTE DE CONENTRACION//

#include "stm32f4xx.h"
#include "tm_stm32f4_mfrc522.h"
#include "stm32f4xx_it.h"
void NVIC_Configuration(void);

int main(void) {


	uint8_t CardID[7];

	int a=0;
	TM_MFRC522_Init();


	while (1)
	{
		if (TM_MFRC522_Check(CardID) == MI_OK) // Tarjeta detectada
		{
			a=2;
			NVIC_Configuration();
		}else {
			a=3;

		}
	}
}


void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	SPI_ITConfig(SPI2, SPI_IT_TXE, ENABLE);
}


void SPI2_IRQHandler(void)
{
int x;
SPI_ITConfig(SPI2, SPI_IT_TXE, DISABLE);
}



