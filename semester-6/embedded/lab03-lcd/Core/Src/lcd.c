/*
 * lcd.c
 *
 *  Created on: Apr 8, 2021
 *      Author: Krzysiek
 */

/*Pins for LCD: LCD_RS_Pin, LCD_RW_Pin, LCD_E_Pin, LCD_DB4_Pin, LCD_DB5_Pin, LCD_DB6_Pin, LCD_DB7_Pin*/

#include "stm32f4xx_hal.h"
#include "lcd.h"
#include "gpio.h"

GPIO_InitTypeDef GPIO_InitStruct;

/* Function for 4bit writing*/
void LCD_Write4bit(char data)
{
  HAL_GPIO_WritePin(LCD_GPIO, LCD_E_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_GPIO, LCD_DB4_Pin, (GPIO_PinState)(data & 0x01));
  HAL_GPIO_WritePin(LCD_GPIO, LCD_DB5_Pin, (GPIO_PinState)(data & 0x02));
  HAL_GPIO_WritePin(LCD_GPIO, LCD_DB6_Pin, (GPIO_PinState)(data & 0x04));
  HAL_GPIO_WritePin(LCD_GPIO, LCD_DB7_Pin, (GPIO_PinState)(data & 0x08));
  HAL_GPIO_WritePin(LCD_GPIO, LCD_E_Pin, GPIO_PIN_RESET);
}


/*Function for 4bit reading*/
unsigned char LCD_Read4bit(void)
{
  unsigned char tmp = 0;
  HAL_GPIO_WritePin(LCD_GPIO, LCD_E_Pin, GPIO_PIN_SET);
  tmp |= (HAL_GPIO_ReadPin(LCD_GPIO, LCD_DB4_Pin) << 0);
  tmp |= (HAL_GPIO_ReadPin(LCD_GPIO, LCD_DB5_Pin) << 1);
  tmp |= (HAL_GPIO_ReadPin(LCD_GPIO, LCD_DB6_Pin) << 2);
  tmp |= (HAL_GPIO_ReadPin(LCD_GPIO, LCD_DB7_Pin) << 3);
  HAL_GPIO_WritePin(LCD_GPIO, LCD_E_Pin, GPIO_PIN_RESET);
  return tmp;
}


/*Function for busy status reading, with data pin direction change*/
unsigned char LCD_ReadBusy(void)
{
  unsigned char status = 0;

  GPIO_InitStruct.Pin =  LCD_DB4_Pin | LCD_DB5_Pin | LCD_DB6_Pin | LCD_DB7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(LCD_GPIO, &GPIO_InitStruct);

  HAL_GPIO_WritePin(LCD_GPIO, LCD_RW_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LCD_GPIO, LCD_RS_Pin, GPIO_PIN_RESET);

  status |= (LCD_Read4bit() << 4);
  status |= LCD_Read4bit();


  GPIO_InitStruct.Pin = LCD_DB4_Pin|LCD_DB5_Pin|LCD_DB6_Pin|LCD_DB7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(LCD_GPIO, &GPIO_InitStruct);

  return status;
}


/*Function for writing data do LCD - character to show*/
void LCD_WriteData(char data)
{
  HAL_GPIO_WritePin(LCD_GPIO, LCD_RW_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_GPIO, LCD_RS_Pin, GPIO_PIN_SET);

  LCD_Write4bit(data >> 4);
  LCD_Write4bit(data & 0x0F);

  while(LCD_ReadBusy() & 0x80);
}


/*Function for writing command do LCD*/
void LCD_WriteCommand(char command)
{
  HAL_GPIO_WritePin(LCD_GPIO, LCD_RW_Pin | LCD_RS_Pin, GPIO_PIN_RESET);
  LCD_Write4bit(command >> 4);
  LCD_Write4bit(command & 0x0F);

  while(LCD_ReadBusy() & 0x80);
}


/*Function for writing string to LCD*/
void LCD_WriteText(char * text)
{
  while(*text)
    LCD_WriteData(*text++);
}


/*LCD init function*/
void LCD_Init(void)
{
  volatile unsigned char i = 0;
  volatile unsigned int delayCnt = 0;


  __HAL_RCC_GPIOE_CLK_ENABLE();


  GPIO_InitStruct.Pin = LCD_DB4_Pin|LCD_DB5_Pin|LCD_DB6_Pin|LCD_DB7_Pin|LCD_RS_Pin|LCD_RW_Pin|LCD_E_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(LCD_GPIO, &GPIO_InitStruct);

  HAL_GPIO_WritePin(LCD_GPIO, LCD_RS_Pin | LCD_E_Pin | LCD_RW_Pin, GPIO_PIN_RESET);


  for(delayCnt = 0; delayCnt < 300000; delayCnt++);

  for(i = 0; i < 3; i++) {
    LCD_Write4bit(0x03);
    for(delayCnt = 0; delayCnt < 30000; delayCnt++);
  }

  LCD_Write4bit(0x02);

  for(delayCnt = 0; delayCnt < 6000; delayCnt++);

  LCD_WriteCommand(LCD_FUNCTION_SET |
                   LCD_FONT5x7 |
				   LCD_TWO_LINE |
				   LCD_4_BIT);

  LCD_WriteCommand(LCD_DISPLAY_ONOFF |
		  	  	   LCD_DISPLAY_OFF);

  LCD_WriteCommand(LCD_CLEAR);

  LCD_WriteCommand(LCD_ENTRY_MODE |
		  	  	   LCD_EM_SHIFT_CURSOR |
				   LCD_EM_INCREMENT);

  LCD_WriteCommand(LCD_DISPLAY_ONOFF |
		  	  	   LCD_DISPLAY_ON |
				   LCD_CURSOR_OFF |
				   LCD_CURSOR_NOBLINK);
}
