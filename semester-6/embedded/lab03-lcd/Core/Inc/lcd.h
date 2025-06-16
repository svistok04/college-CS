/*
 * lcd.h
 *
 *  Created on: Apr 8, 2021
 *      Author: Krzysiek
 */

#define LCD_GPIO GPIOE

#define LCD_CLEAR					 	0x01

#define LCD_HOME						0x02

#define LCD_ENTRY_MODE				  	0x04
	#define LCD_EM_SHIFT_CURSOR		 	0
	#define LCD_EM_SHIFT_DISPLAY	 	1
	#define LCD_EM_DECREMENT		   	0
	#define LCD_EM_INCREMENT		   	2

#define LCD_DISPLAY_ONOFF			   	0x08
	#define LCD_DISPLAY_OFF		     	0
	#define LCD_DISPLAY_ON			   	4
	#define LCD_CURSOR_OFF			   	0
	#define LCD_CURSOR_ON			    2
	#define LCD_CURSOR_NOBLINK	   		0
	#define LCD_CURSOR_BLINK		   	1

#define LCD_DISPLAY_CURSOR_SHIFT 		0x10
	#define LCD_SHIFT_CURSOR		   	0
	#define LCD_SHIFT_DISPLAY		   	8
	#define LCD_SHIFT_LEFT			   	0
	#define LCD_SHIFT_RIGHT		     	4

#define LCD_FUNCTION_SET			   	0x20
	#define LCD_FONT5x7				    0
	#define LCD_FONT5x10			    4
	#define LCD_ONE_LINE			    0
	#define LCD_TWO_LINE			    8
	#define LCD_4_BIT				    0
	#define LCD_8_BIT				    16

#define LCD_CGRAM_SET				    0x40

#define LCD_DDRAM_SET				    0x80

void LCD_Init(void);
void LCD_WriteData(char dataToWrite);
void LCD_WriteCommand(char commandToWrite);
void LCD_WriteText(char * text);
