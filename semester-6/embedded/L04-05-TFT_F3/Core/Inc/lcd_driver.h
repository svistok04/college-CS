/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"
#include "spi.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>	
/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup LCD
  * @{
  */

/** @defgroup LCD_Exported_Types
  * @{
  */
   
/**
  * @}
  */ 

/** @defgroup LCD_Exported_Constants
  * @{
  */
      
/** 
  * @brief  LCD Size  
  */
#define LCD_WIDTH				240
#define LCD_HEIGHT			320

/** 
  * @brief  LCD ID  
  */  
#define  ST7789V				0x52
#define  HX8347D				0x47

/**
  * @}
  */
	
#define  MAX_BMP_FILES  25 
	
/** 
  * @brief  LCD ID  
  */  
#define LCD_CMD					0
#define LCD_DATA				1
/**
  * @}
  */

#define FONT_1206				12
#define FONT_1608				16
	
#define WHITE						0xFFFF
#define BLACK						0x0000	  
#define BLUE						0x001F  
#define BRED						0XF81F
#define GRED						0XFFE0
#define GBLUE						0X07FF
#define RED							0xF800
#define MAGENTA					0xF81F
#define GREEN						0x07E0
#define CYAN						0x7FFF
#define YELLOW					0xFFE0
#define BROWN						0XBC40 
#define BRRED						0XFC07 
#define GRAY						0X8430


#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))	
/**
  * @brief  LCD Control Lines management
  */
#define __LCD_CS_CLR()      HAL_GPIO_WritePin(LCD_CS_GPIO_PORT, LCD_CS_PIN, GPIO_PIN_RESET)
#define __LCD_CS_SET()      HAL_GPIO_WritePin(LCD_CS_GPIO_PORT, LCD_CS_PIN, GPIO_PIN_SET)
#define __LCD_DC_CLR()      HAL_GPIO_WritePin(LCD_DC_GPIO_PORT, LCD_DC_PIN, GPIO_PIN_RESET)
#define __LCD_DC_SET()      HAL_GPIO_WritePin(LCD_DC_GPIO_PORT, LCD_DC_PIN, GPIO_PIN_SET)
#define __LCD_BKL_SET()			HAL_GPIO_WritePin(LCD_BL_GPIO_PORT, LCD_BL_PIN, GPIO_PIN_SET)
#define __LCD_BKL_CLR()			HAL_GPIO_WritePin(LCD_BL_GPIO_PORT, LCD_BL_PIN, GPIO_PIN_RESET)
/**
  * @brief  LCD Control Interface pins (shield D10)
  */
#define LCD_CS_PIN                                 LCD_CS_Pin
#define LCD_CS_GPIO_PORT                           LCD_CS_GPIO_Port
#define LCD_CS_GPIO_CLK_ENABLE()                   __HAL_RCC_GPIOB_CLK_ENABLE()
#define LCD_CS_GPIO_CLK_DISABLE()                  __HAL_RCC_GPIOB_CLK_DISABLE()
#define LCD_BL_PIN                                 LCD_BL_Pin
#define LCD_BL_GPIO_PORT                           LCD_BL_GPIO_Port
/**
  * @brief  LCD Data/Command Interface pins
  */
#define LCD_DC_PIN                                 LCD_DC_Pin
#define LCD_DC_GPIO_PORT                           LCD_DC_GPIO_Port
#define LCD_DC_GPIO_CLK_ENABLE()                   __HAL_RCC_GPIOB_CLK_ENABLE()
#define LCD_DC_GPIO_CLK_DISABLE()                  __HAL_RCC_GPIOB_CLK_DISABLE()
/*------------------------------------------------------------------------------------------------------*/

#define XPT2046_CS_PIN          XPT2046_CS_Pin
#define XPT2046_IRQ_PIN         XPT2046_IRQ_Pin

#define XPT2046_CS_GPIO         XPT2046_CS_GPIO_Port
#define XPT2046_IRQ_GPIO        XPT2046_CS_GPIO_Port

#define __XPT2046_CS_SET()      HAL_GPIO_WritePin(XPT2046_CS_GPIO, XPT2046_CS_PIN, GPIO_PIN_SET)
#define __XPT2046_CS_CLR()      HAL_GPIO_WritePin(XPT2046_CS_GPIO, XPT2046_CS_PIN, GPIO_PIN_RESET)

#define __XPT2046_IRQ_READ()    HAL_GPIO_ReadPin(XPT2046_IRQ_GPIO, XPT2046_IRQ_PIN)

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ADAFRUIT_SPI_LCD_Exported_Functions
  * @{
  */ 
void lcd_init(void);
uint8_t lcd_read_id(void);
void lcd_write_byte(uint8_t chByte, uint8_t chCmd);
void lcd_set_cursor( uint16_t hwXpos, uint16_t hwYpos);
void lcd_write_ram_prepare(void);
void lcd_write_ram( uint16_t hwData);
void lcd_set_window( uint16_t hwXpos, uint16_t hwYpos, uint16_t hwWidth, uint16_t hwHeight);
void lcd_draw_point( uint16_t hwXpos, uint16_t hwYpos, uint16_t hwColor);
void lcd_clear_screen( uint16_t hwColor);
void lcd_display_char(	uint16_t hwXpos, //specify x position.
															uint16_t hwYpos, //specify y position.
															uint8_t chChr,   //a char is display.
															uint8_t chSize,  //specify the size of the char
															uint16_t hwColor); //specify the color of the char
void lcd_display_num(	uint16_t hwXpos,  //specify x position.
															uint16_t hwYpos, //specify y position.
															uint32_t chNum,  //a number is display.
															uint8_t chLen,   //length ot the number
															uint8_t chSize,  //specify the size of the number
															uint16_t hwColor); //specify the color of the number
void lcd_display_string( uint16_t hwXpos, //specify x position.
																uint16_t hwYpos,   //specify y position.
																const uint8_t *pchString,  //a pointer to string
																uint8_t chSize,    // the size of the string 
																uint16_t hwColor);  // specify the color of the string 
void lcd_draw_line( 	uint16_t hwXpos0, //specify x0 position.
														uint16_t hwYpos0, //specify y0 position.
														uint16_t hwXpos1, //specify x1 position.
														uint16_t hwYpos1, //specify y1 position.
														uint16_t hwColor); //specify the color of the line
void lcd_draw_circle( 	uint16_t hwXpos,  //specify x position.
															uint16_t hwYpos,  //specify y position.
															uint16_t hwRadius, //specify the radius of the circle.
															uint16_t hwColor);  //specify the color of the circle.
void lcd_fill_rect( uint16_t hwXpos,  //specify x position.
													 uint16_t hwYpos,  //specify y position.
													 uint16_t hwWidth, //specify the width of the rectangle.
													 uint16_t hwHeight, //specify the height of the rectangle.
													 uint16_t hwColor);  //specify the color of rectangle.
void lcd_draw_v_line( 	uint16_t hwXpos, //specify x position.
															uint16_t hwYpos, //specify y position. 
															uint16_t hwHeight, //specify the height of the vertical line.
															uint16_t hwColor);  //specify the color of the vertical line.
void lcd_draw_h_line(	uint16_t hwXpos, //specify x position.
															uint16_t hwYpos,  //specify y position. 
															uint16_t hwWidth, //specify the width of the horizonal line.
															uint16_t hwColor); //specify the color of the horizonal line.
void lcd_draw_rect( 	uint16_t hwXpos,  //specify x position.
														uint16_t hwYpos,  //specify y position.
														uint16_t hwWidth, //specify the width of the rectangle.
														uint16_t hwHeight, //specify the height of the rectangle.
														uint16_t hwColor);  //specify the color of rectangle.

void setRotation( uint8_t rotation);
void lcd_write_word( uint16_t hwData);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */
