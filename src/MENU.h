/*******************************
 * MENU.h
 *******************************/

#ifndef MENU_H_
#define MENU_H_

#include "stm32f4xx.h"
#include "stm32_ub_lcd_2x16.h"
#include "stm32f4xx_it.h"
#include "teclado.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "GLOBAL.h"
#include "tm_stm32f4_mfrc522.h"
#include "CE_SD_card_control.h"
#include <string.h>
#include <ctype.h>

void Menu (Tecla);
void Menuinit(void);


#endif /* MENU_H_ */
