/**
 *  Defines for your entire project at one place
 * 
<<<<<<< HEAD
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
=======
 *	@author 	Tilen MAJERLE
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.net
>>>>>>> e5ce884e878d93d805d1f734fd25e2075f59e355
 *	@version 	v1.0
 *	@ide		Keil uVision 5
 *	@license	GNU GPL v3
 *	
 * |----------------------------------------------------------------------
<<<<<<< HEAD
 * | Copyright (C) Tilen Majerle, 2014
=======
 * | Copyright (C) Tilen MAJERLE, 2014
>>>>>>> e5ce884e878d93d805d1f734fd25e2075f59e355
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H

/* Put your global defines for all libraries here used in your project */

<<<<<<< HEAD
#endif

#define FATFS_USE_SDIO   0
#define FATFS_SPI               SPI4
#define FATFS_SPI_PINSPACK      TM_SPI_PinsPack_2

//Set your CS pin for SPI
#define FATFS_CS_PORT           GPIOE
#define FATFS_CS_PIN            GPIO_PIN_11

// Change Timer used to be able to use Systick for other purposes
#define TM_DELAY_TIM				TIM2
#define TM_DELAY_TIM_IRQ			TIM2_IRQn
#define TM_DELAY_TIM_IRQ_HANDLER	TIM2_IRQHandler
=======
/* Increase SPI5 SCK speed for ILI9341 on STM32F429 discovery board */
#define TM_SPI5_PRESCALER	SPI_BaudRatePrescaler_2

#endif

>>>>>>> e5ce884e878d93d805d1f734fd25e2075f59e355
