//--------------------------------------------------------------
// File     : stm32_ub_lcd_2x16.c
// Datum    : 15.04.2013
// Version  : 1.0
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.0
// Module   : GPIO
// Funktion : Text-LCD Funktionen (2x16 Zeichen)
//            im 4Bit-Mode
//            Chip : ST7066U/HD44780/SED1278/KS0066U/S6A0069X
// 
// Hinweis  : Das Display benutzt die CPU-Pins :
//			ESTE EJEMPLO DISPONE LOS PINES A UTILIZAR TAL QUE PUEDE COLOCARSE
//			UNA PLACA CON UN CONECTOR EN P2 EN EL EXTREMO gnd Y 5v

//          RS ,GPIOA,GPIO_Pin_0
// 			E  ,GPIOA,GPIO_Pin_4
//  		D4 ,GPIOC,GPIO_Pin_12
// 			D5 ,GPIOC,GPIO_Pin_10
//  		D6 ,GPIOC,GPIO_Pin_11
//  		D7 ,GPIOD,GPIO_Pin_2

//--------------------------------------------------------------



//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_lcd_2x16.h"



//--------------------------------------------------------------
// interne Funktionen
//--------------------------------------------------------------
void P_LCD_2x16_InitIO(void);
void P_LCD_2x16_PinLo(TLCD_NAME_t lcd_pin);
void P_LCD_2x16_PinHi(TLCD_NAME_t lcd_pin);
void P_LCD_2x16_Clk(void);
void P_LCD_2x16_InitSequenz(void);
void P_LCD_2x16_Cmd(uint8_t wert);
void P_LCD_2x16_Data(uint8_t wert);
void P_LCD_2x16_Cursor(uint8_t x, uint8_t y);
void P_LCD_2x16_Delay(volatile uint32_t nCount);
 


//--------------------------------------------------------------
// Definition aller Pins f�r das Display
// Reihenfolge wie bei TLCD_NAME_t
//
// Init : [Bit_SET,Bit_RESET]
//--------------------------------------------------------------
LCD_2X16_t LCD_2X16[] = {
		// Name   ,PORT , PIN       , CLOCK              , Init
		{TLCD_RS ,GPIOA,GPIO_Pin_0 ,RCC_AHB1Periph_GPIOA,Bit_RESET},
		{TLCD_E  ,GPIOA,GPIO_Pin_4 ,RCC_AHB1Periph_GPIOA,Bit_RESET},
		{TLCD_D4 ,GPIOC,GPIO_Pin_12 ,RCC_AHB1Periph_GPIOC,Bit_RESET},
		{TLCD_D5 ,GPIOC,GPIO_Pin_10 ,RCC_AHB1Periph_GPIOC,Bit_RESET},
		{TLCD_D6 ,GPIOC,GPIO_Pin_11 ,RCC_AHB1Periph_GPIOC,Bit_RESET},
		{TLCD_D7 ,GPIOD,GPIO_Pin_2,	RCC_AHB1Periph_GPIOD,Bit_RESET},
};



//--------------------------------------------------------------
// Init vom Text-LCDisplay
//--------------------------------------------------------------
void LCDinit(void)
{
  // init aller IO-Pins
  P_LCD_2x16_InitIO();
  // kleine Pause
  P_LCD_2x16_Delay(TLCD_INIT_PAUSE);
  // Init Sequenz starten
  P_LCD_2x16_InitSequenz();
  // LCD-Settings einstellen
  P_LCD_2x16_Cmd(TLCD_CMD_INIT_DISPLAY);
  P_LCD_2x16_Cmd(TLCD_CMD_ENTRY_MODE);
  // Display einschalten
  P_LCD_2x16_Cmd(TLCD_CMD_DISP_M1);
  // Display l�schen
  P_LCD_2x16_Cmd(TLCD_CMD_CLEAR);
  // kleine Pause
  P_LCD_2x16_Delay(TLCD_PAUSE);
}


//--------------------------------------------------------------
// L�scht das Text-LCDisplay
//--------------------------------------------------------------
void UB_LCD_2x16_Clear(void)
{
  // Display l�schen
  P_LCD_2x16_Cmd(TLCD_CMD_CLEAR);
  // kleine Pause
  P_LCD_2x16_Delay(TLCD_PAUSE);
}


//--------------------------------------------------------------
// Stellt einen Display Mode ein
// mode : [TLCD_OFF, TLCD_ON, TLCD_CURSOR, TLCD_BLINK]
//--------------------------------------------------------------
void UB_LCD_2x16_SetMode(TLCD_MODE_t mode)
{
  if(mode==TLCD_OFF) P_LCD_2x16_Cmd(TLCD_CMD_DISP_M0);
  if(mode==TLCD_ON) P_LCD_2x16_Cmd(TLCD_CMD_DISP_M1);
  if(mode==TLCD_CURSOR) P_LCD_2x16_Cmd(TLCD_CMD_DISP_M2);
  if(mode==TLCD_BLINK) P_LCD_2x16_Cmd(TLCD_CMD_DISP_M3);
}


//--------------------------------------------------------------
// Ausgabe von einem String auf dem Display an x,y Position
// x : 0 bis 15
// y : 0 bis 1
//--------------------------------------------------------------
void UB_LCD_2x16_String(uint8_t x, uint8_t y, char *ptr)
{
  // Cursor setzen
  P_LCD_2x16_Cursor(x,y);
  // kompletten String ausgeben
  while (*ptr != 0) {
    P_LCD_2x16_Data(*ptr);
    ptr++;
  }
}


//--------------------------------------------------------------
// interne Funktion
// init aller IO-Pins
//--------------------------------------------------------------
void P_LCD_2x16_InitIO(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  TLCD_NAME_t lcd_pin;
  
  for(lcd_pin=0;lcd_pin<TLCD_ANZ;lcd_pin++) {
    // Clock Enable
    RCC_AHB1PeriphClockCmd(LCD_2X16[lcd_pin].TLCD_CLK, ENABLE);

    // Config als Digital-Ausgang
    GPIO_InitStructure.GPIO_Pin = LCD_2X16[lcd_pin].TLCD_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_2X16[lcd_pin].TLCD_PORT, &GPIO_InitStructure);

    // Default Wert einstellen
    if(LCD_2X16[lcd_pin].TLCD_INIT==Bit_RESET) {
      P_LCD_2x16_PinLo(lcd_pin);
    }
    else {
      P_LCD_2x16_PinHi(lcd_pin);
    }
  }  
}


//--------------------------------------------------------------
// interne Funktion
// Pin auf Lo setzen
//--------------------------------------------------------------
void P_LCD_2x16_PinLo(TLCD_NAME_t lcd_pin)
{
  LCD_2X16[lcd_pin].TLCD_PORT->BSRRH = LCD_2X16[lcd_pin].TLCD_PIN;
}


//--------------------------------------------------------------
// interne Funktion
// Pin auf Hi setzen
//--------------------------------------------------------------
void P_LCD_2x16_PinHi(TLCD_NAME_t lcd_pin)
{
  LCD_2X16[lcd_pin].TLCD_PORT->BSRRL = LCD_2X16[lcd_pin].TLCD_PIN;
}


//--------------------------------------------------------------
// interne Funktion
// einen Clock Impuls ausgeben
//--------------------------------------------------------------
void P_LCD_2x16_Clk(void)
{
  // Pin-E auf Hi
  P_LCD_2x16_PinHi(TLCD_E);
  // kleine Pause
  P_LCD_2x16_Delay(TLCD_CLK_PAUSE);
  // Pin-E auf Lo
  P_LCD_2x16_PinLo(TLCD_E);
  // kleine Pause
  P_LCD_2x16_Delay(TLCD_CLK_PAUSE);  
}


//--------------------------------------------------------------
// interne Funktion
// init Sequenz f�r das Display
//--------------------------------------------------------------
void P_LCD_2x16_InitSequenz(void)
{
  // Init Sequenz
  P_LCD_2x16_PinHi(TLCD_D4);
  P_LCD_2x16_PinHi(TLCD_D5);
  P_LCD_2x16_PinLo(TLCD_D6);
  P_LCD_2x16_PinLo(TLCD_D7);
  // Erster Init Impuls
  P_LCD_2x16_Clk();
  P_LCD_2x16_Delay(TLCD_PAUSE);
  // Zweiter Init Impuls
  P_LCD_2x16_Clk();
  P_LCD_2x16_Delay(TLCD_PAUSE);
  // Dritter Init Impuls
  P_LCD_2x16_Clk();
  P_LCD_2x16_Delay(TLCD_PAUSE);
  // LCD-Modus einstellen (4Bit-Mode)
  P_LCD_2x16_PinLo(TLCD_D4);
  P_LCD_2x16_PinHi(TLCD_D5);
  P_LCD_2x16_PinLo(TLCD_D6);
  P_LCD_2x16_PinLo(TLCD_D7);
  P_LCD_2x16_Clk();
  P_LCD_2x16_Delay(TLCD_PAUSE);
}


//--------------------------------------------------------------
// interne Funktion
// Kommando an das Display senden
//--------------------------------------------------------------
void P_LCD_2x16_Cmd(uint8_t wert)
{
  // RS=Lo (Command)
  P_LCD_2x16_PinLo(TLCD_RS);
  // Hi-Nibble ausgeben         
  if((wert&0x80)!=0) P_LCD_2x16_PinHi(TLCD_D7); else P_LCD_2x16_PinLo(TLCD_D7);
  if((wert&0x40)!=0) P_LCD_2x16_PinHi(TLCD_D6); else P_LCD_2x16_PinLo(TLCD_D6);
  if((wert&0x20)!=0) P_LCD_2x16_PinHi(TLCD_D5); else P_LCD_2x16_PinLo(TLCD_D5);
  if((wert&0x10)!=0) P_LCD_2x16_PinHi(TLCD_D4); else P_LCD_2x16_PinLo(TLCD_D4);
  P_LCD_2x16_Clk();
  // Lo-Nibble ausgeben         
  if((wert&0x08)!=0) P_LCD_2x16_PinHi(TLCD_D7); else P_LCD_2x16_PinLo(TLCD_D7);
  if((wert&0x04)!=0) P_LCD_2x16_PinHi(TLCD_D6); else P_LCD_2x16_PinLo(TLCD_D6);
  if((wert&0x02)!=0) P_LCD_2x16_PinHi(TLCD_D5); else P_LCD_2x16_PinLo(TLCD_D5);
  if((wert&0x01)!=0) P_LCD_2x16_PinHi(TLCD_D4); else P_LCD_2x16_PinLo(TLCD_D4);
  P_LCD_2x16_Clk();  
}


//--------------------------------------------------------------
// interne Funktion
// Daten an das Display senden
//--------------------------------------------------------------
void P_LCD_2x16_Data(uint8_t wert)
{
  // RS=Hi (Data)
  P_LCD_2x16_PinHi(TLCD_RS);
  // Hi-Nibble ausgeben          
  if((wert&0x80)!=0) P_LCD_2x16_PinHi(TLCD_D7); else P_LCD_2x16_PinLo(TLCD_D7);
  if((wert&0x40)!=0) P_LCD_2x16_PinHi(TLCD_D6); else P_LCD_2x16_PinLo(TLCD_D6);
  if((wert&0x20)!=0) P_LCD_2x16_PinHi(TLCD_D5); else P_LCD_2x16_PinLo(TLCD_D5);
  if((wert&0x10)!=0) P_LCD_2x16_PinHi(TLCD_D4); else P_LCD_2x16_PinLo(TLCD_D4);
  P_LCD_2x16_Clk();
  // Lo-Nibble ausgeben        
  if((wert&0x08)!=0) P_LCD_2x16_PinHi(TLCD_D7); else P_LCD_2x16_PinLo(TLCD_D7);
  if((wert&0x04)!=0) P_LCD_2x16_PinHi(TLCD_D6); else P_LCD_2x16_PinLo(TLCD_D6);
  if((wert&0x02)!=0) P_LCD_2x16_PinHi(TLCD_D5); else P_LCD_2x16_PinLo(TLCD_D5);
  if((wert&0x01)!=0) P_LCD_2x16_PinHi(TLCD_D4); else P_LCD_2x16_PinLo(TLCD_D4);
  P_LCD_2x16_Clk();  
}


//--------------------------------------------------------------
// interne Funktion
// Cursor auf x,y stellen
//--------------------------------------------------------------
void P_LCD_2x16_Cursor(uint8_t x, uint8_t y)
{
  uint8_t wert;

  if(x>=TLCD_MAXX) x=0;
  if(y>=TLCD_MAXY) y=0;

  wert=(y<<6);
  wert|=x;
  wert|=0x80;
  P_LCD_2x16_Cmd(wert);
}


//--------------------------------------------------------------
// kleine Pause (ohne Timer)
//--------------------------------------------------------------
void P_LCD_2x16_Delay(volatile uint32_t nCount)
{
  while(nCount--)
  {
  }
}
