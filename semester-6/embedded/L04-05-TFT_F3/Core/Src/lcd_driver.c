/**
  ******************************************************************************
  * @file    xxx.c 
  * @author  Waveshare Team
  * @version 
  * @date    xx-xx-2014
  * @brief   xxxxx.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WAVESHARE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "Fonts.h"
#include "lcd_driver.h"
#include "usart.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

uint8_t lcd_id;
uint8_t _rotation = 0;

void lcd_write_byte(uint8_t chByte, uint8_t chCmd)
{
    if (chCmd) {
        __LCD_DC_SET();
    } else {
        __LCD_DC_CLR();
    }
    __LCD_CS_CLR();
		HAL_SPI_Transmit(&hspi1,&chByte,1,0xff);
    __LCD_CS_SET();
}

void lcd_write_word(uint16_t hwData)
{
		uint8_t hval = hwData >> 8;
		uint8_t lval = hwData & 0xFF;
    __LCD_DC_SET();
    __LCD_CS_CLR();
		HAL_SPI_Transmit(&hspi1,&hval,1,0xff);
		HAL_SPI_Transmit(&hspi1,&lval,1,0xff);
    __LCD_CS_SET();
}

static void lcd_write_register(uint8_t chRegister, uint8_t chValue)
{
	lcd_write_byte(chRegister, LCD_CMD);
	lcd_write_byte(chValue, LCD_DATA);
}

//set the specified position of cursor on lcd.
//hwXpos specify x position
//hwYpos specify y position
void lcd_set_cursor(uint16_t hwXpos, uint16_t hwYpos)
{
	if(ST7789V == lcd_id){
		if(1==_rotation||3==_rotation){
			lcd_write_byte(0x2A,LCD_CMD);
			lcd_write_byte(((hwXpos)>>8)&0xff,LCD_DATA);
			lcd_write_byte((hwXpos)&0xff,LCD_DATA);
			lcd_write_byte(0x2B,LCD_CMD);
			lcd_write_byte(0x00,LCD_DATA);
			lcd_write_byte((hwYpos)&0xff,LCD_DATA);
		}else{
			lcd_write_byte(0x2A,LCD_CMD);
			lcd_write_byte(0x00,LCD_DATA);
			lcd_write_byte(hwXpos&0xff,LCD_DATA);
			lcd_write_byte(0x2B,LCD_CMD);
			lcd_write_byte((hwYpos>>8)&0xff,LCD_DATA);
			lcd_write_byte(hwYpos&0xff,LCD_DATA);
		}
		lcd_write_byte(0x2C, LCD_CMD);
	}else{
			lcd_write_register(0x02, hwXpos >> 8);
			lcd_write_register(0x03, hwXpos & 0xFF); //Column Start
			lcd_write_register(0x06, hwYpos >> 8);
			lcd_write_register(0x07, hwYpos & 0xFF); //Row Start
			lcd_write_register(0x02, hwXpos >> 8);
			lcd_write_register(0x03, hwXpos & 0xFF); //Column Start
			lcd_write_register(0x06, hwYpos >> 8);
			lcd_write_register(0x07, hwYpos & 0xFF); //Row Start
			lcd_write_byte(0x22, LCD_CMD);
	}
}

//clear the lcd with the specified color.
void lcd_clear_screen(uint16_t hwColor)  
{
	uint32_t i, wCount = LCD_WIDTH;
	uint8_t hval = hwColor >> 8;
	uint8_t lval = hwColor & 0xFF;
	wCount *= LCD_HEIGHT;
	
	if(ST7789V == lcd_id){
		setRotation(_rotation);
		__LCD_DC_SET();
		__LCD_CS_CLR();
		for (i = 0; i < wCount; i ++) {
			HAL_SPI_Transmit(&hspi1,&hval,1,0xff);
			HAL_SPI_Transmit(&hspi1,&lval,1,0xff);
		}
		__LCD_CS_SET();
	}else{
		lcd_set_cursor(0, 0);
		lcd_write_byte(0x22, LCD_CMD);
			
		__LCD_DC_SET();
		__LCD_CS_CLR();
		for (i = 0; i < wCount; i ++) {
			HAL_SPI_Transmit(&hspi1,&hval,1,0xff);
			HAL_SPI_Transmit(&hspi1,&lval,1,0xff);
		}
		__LCD_CS_SET();
	}
}

void lcd_write_ram_prepare(void)
{
	if(ST7789V == lcd_id){
		lcd_write_byte(0x2C, LCD_CMD);
	}else{
    lcd_write_byte(0x22, LCD_CMD);
	}
}

void lcd_write_ram(uint16_t hwData)
{
    lcd_write_word(hwData);
}    

void lcd_set_window(uint16_t hwXpos, uint16_t hwYpos, uint16_t hwWidth, uint16_t hwHeight)
{
	if(ST7789V == lcd_id){
		switch(_rotation){
			case 0:
			 /* Memory access control: MY = 0, MX = 0, MV = 0, ML = 0 */
			 /*  */
				if( 240 > hwXpos + hwWidth - 1 && 320 > hwYpos + hwHeight - 1 ){
					lcd_write_register(0X36, 0x00);
					lcd_write_byte(0x2A,LCD_CMD);
					lcd_write_byte(0x00,LCD_DATA);
					lcd_write_byte(hwXpos-1 & 0xff,LCD_DATA);
					lcd_write_byte(0x00,LCD_DATA);
					lcd_write_byte(hwXpos+hwWidth-1&0xff,LCD_DATA);
					lcd_write_byte(0x2B,LCD_CMD);
					lcd_write_byte((hwYpos-1)>>8&0xFF,LCD_DATA);
					lcd_write_byte(hwYpos-1&0xFF,LCD_DATA);
					lcd_write_byte((hwYpos+hwHeight-1)>>8&0xFF,LCD_DATA);
					lcd_write_byte((hwHeight+hwYpos-1)&0xff,LCD_DATA);
					lcd_set_cursor(hwXpos,hwYpos);
				}
				break;
			
			case 1:
			 /* Memory access control: MY = 0, MX = 1, MV = 1, ML = 0 */
				if( 320 > hwXpos + hwWidth - 1 && 240 > hwYpos + hwHeight - 1 ){
					lcd_write_register(0X36, 0x60);
					lcd_write_byte(0x2A,LCD_CMD);
					lcd_write_byte(((hwXpos-1)>>8)&0xff,LCD_DATA);
					lcd_write_byte((hwXpos-1)&0xff,LCD_DATA);
					lcd_write_byte(((hwWidth+hwXpos-1)>>8)&0xff,LCD_DATA);
					lcd_write_byte((hwWidth+hwXpos-1)&0xff,LCD_DATA);
					lcd_write_byte(0x2B,LCD_CMD);
					lcd_write_byte(0x00,LCD_DATA);
					lcd_write_byte(hwYpos-1,LCD_DATA);
					lcd_write_byte(0x00,LCD_DATA);
					lcd_write_byte((hwHeight+hwYpos-1)&0xff,LCD_DATA);
					lcd_set_cursor(hwXpos,hwYpos);
				}
				break;
				
			case 2:
			 /* Memory access control: MY = 1, MX = 1, MV = 0, ML = 0 */
				if( 240 > hwXpos + hwWidth - 1 && 320 > hwYpos + hwHeight - 1 ){
					lcd_write_register(0X36, 0xC0);
					lcd_write_byte(0x2A,LCD_CMD);
					lcd_write_byte(0x00,LCD_DATA);
					lcd_write_byte(hwXpos-1 & 0xff,LCD_DATA);
					lcd_write_byte(0x00,LCD_DATA);
					lcd_write_byte(hwXpos+hwWidth-1&0xff,LCD_DATA);
					lcd_write_byte(0x2B,LCD_CMD);
					lcd_write_byte((hwYpos-1)>>8&0xFF,LCD_DATA);
					lcd_write_byte(hwYpos-1&0xFF,LCD_DATA);
					lcd_write_byte((hwYpos+hwHeight-1)>>8&0xFF,LCD_DATA);
					lcd_write_byte((hwHeight+hwYpos-1)&0xff,LCD_DATA);
					lcd_set_cursor(hwXpos,hwYpos);
				}
				break;
				
			case 3:
			 /* Memory access control: MY = 1, MX = 0, MV = 1, ML = 0 */
			
				if( 320 > hwXpos + hwWidth - 1 && 240 > hwYpos + hwHeight - 1 ){
					lcd_write_register(0X36, 0xA0);
					lcd_write_byte(0x2A,LCD_CMD);
					lcd_write_byte(((hwXpos-1)>>8)&0xff,LCD_DATA);
					lcd_write_byte((hwXpos-1)&0xff,LCD_DATA);
					lcd_write_byte(((hwWidth+hwXpos-1)>>8)&0xff,LCD_DATA);
					lcd_write_byte((hwWidth+hwXpos-1)&0xff,LCD_DATA);
					lcd_write_byte(0x2B,LCD_CMD);
					lcd_write_byte(0x00,LCD_DATA);
					lcd_write_byte(hwYpos-1,LCD_DATA);
					lcd_write_byte(0x00,LCD_DATA);
					lcd_write_byte((hwHeight+hwYpos-1)&0xff,LCD_DATA);
					lcd_set_cursor(hwXpos,hwYpos);
				}
				break;
	 }
	}else{
		lcd_write_register(0x04, (hwXpos + hwWidth - 1) >> 8);
		lcd_write_register(0x05, (hwXpos + hwWidth - 1) & 0xFF); //Column End
		lcd_write_register(0x08, (hwYpos + hwHeight - 1) >> 8);
		lcd_write_register(0x09, (hwYpos + hwHeight - 1) & 0xFF); //Row End
	}
}


//draw a point on the lcd with the specified color.
//hwXpos specify x position.
//hwYpos specify y position.
//hwColor color of the point.
void lcd_draw_point(uint16_t hwXpos, uint16_t hwYpos, uint16_t hwColor) 
{
	if(ST7789V == lcd_id){
		lcd_set_cursor(hwXpos, hwYpos);
		lcd_write_byte(0x2C, LCD_CMD);
		lcd_write_word(hwColor);
	}else{
		lcd_set_cursor(hwXpos, hwYpos);
		lcd_write_byte(0x22, LCD_CMD);
		lcd_write_word(hwColor);
	}
}

//display a char at the specified position on lcd.
void lcd_display_char(		uint16_t hwXpos, //specify x position.
													uint16_t hwYpos, //specify y position.
													uint8_t chChr,   //a char is display.
													uint8_t chSize,  //specify the size of the char
													uint16_t hwColor) //specify the color of the char
{      	
	uint8_t i, j, chTemp;
	uint16_t hwYpos0 = hwYpos, hwColorVal = 0;
	
    for (i = 0; i < chSize; i ++) {   
			if (FONT_1206 == chSize) {
				chTemp = c_chFont1206[chChr - 0x20][i];  
				}else if (FONT_1608 == chSize) { 
				chTemp = c_chFont1608[chChr - 0x20][i];
			}
			for (j = 0; j < 8; j ++) {
					if (chTemp & 0x80) {
						hwColorVal = hwColor;
						lcd_draw_point(hwXpos, hwYpos, hwColorVal);
					}			
					chTemp <<= 1;
					hwYpos ++;
					if ((hwYpos - hwYpos0) == chSize) {
						hwYpos = hwYpos0;
						hwXpos ++;
						break;
				}
			}  	 
    } 
}

//_pow
static uint32_t _pow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;
	
	while(n --) result *= m;    
	return result;
}

//display a number at the specified position on lcd.
void lcd_display_num(			uint16_t hwXpos,  //specify x position.
                          uint16_t hwYpos, //specify y position.
                          uint32_t chNum,  //a number is display.
                          uint8_t chLen,   //length ot the number
                          uint8_t chSize,  //specify the size of the number
                          uint16_t hwColor) //specify the color of the number
{         	
	uint8_t i;
	uint8_t chTemp, chShow = 0;
	
	for(i = 0; i < chLen; i ++) {
		chTemp = (chNum / _pow(10, chLen - i - 1)) % 10;
		if(chShow == 0 && i < (chLen - 1)) {
			if(chTemp == 0) {
				lcd_display_char(hwXpos + (chSize / 2) * i, hwYpos, ' ', chSize, hwColor);
				continue;
			} else {
				chShow = 1;
			}	 
		}
	 	lcd_display_char(hwXpos + (chSize / 2) * i, hwYpos, chTemp + '0', chSize, hwColor); 
	}
} 

//display a string at the specified position on lcd.
void lcd_display_string(	uint16_t hwXpos, //specify x position.
													uint16_t hwYpos,   //specify y position.
													const uint8_t *pchString,  //a pointer to string
													uint8_t chSize,    // the size of the string 
													uint16_t hwColor)  // specify the color of the string 
{
    while (*pchString != '\0') {       
        if (hwXpos > (LCD_WIDTH - chSize / 2)) {
			hwXpos = 0;
			hwYpos += chSize;
			if (hwYpos > (LCD_HEIGHT - chSize)) {
				hwYpos = hwXpos = 0;
				lcd_clear_screen(0x00);
			}
		}
        lcd_display_char(hwXpos, hwYpos, (uint8_t)*pchString, chSize, hwColor);
        hwXpos += chSize / 2;
        pchString ++;
    } 
}

//draw a line at the specified position on lcd.
void lcd_draw_line(		uint16_t hwXpos0, //specify x0 position.
                      uint16_t hwYpos0, //specify y0 position.
                      uint16_t hwXpos1, //specify x1 position.
                      uint16_t hwYpos1, //specify y1 position.
                      uint16_t hwColor) //specify the color of the line
{
		int x = hwXpos1 - hwXpos0;
    int y = hwYpos1 - hwYpos0;
    int dx = abs(x), sx = hwXpos0 < hwXpos1 ? 1 : -1;
    int dy = -abs(y), sy = hwYpos0 < hwYpos1 ? 1 : -1;
    int err = dx + dy, e2;
    
    for (;;){
        lcd_draw_point(hwXpos0, hwYpos0 , hwColor);
        e2 = 2 * err;
        if (e2 >= dy) {     
            if (hwXpos0 == hwXpos1) break;
            err += dy; hwXpos0 += sx;
        }
        if (e2 <= dx) {
            if (hwYpos0 == hwYpos1) break;
            err += dx; hwYpos0 += sy;
        }
    }
}

//draw a circle at the specified position on lcd.
void lcd_draw_circle(		uint16_t hwXpos,  //specify x position.
                        uint16_t hwYpos,  //specify y position.
                        uint16_t hwRadius, //specify the radius of the circle.
                        uint16_t hwColor)  //specify the color of the circle.
{
		int x = -hwRadius, y = 0, err = 2 - 2 * hwRadius, e2;
	
    do {
        lcd_draw_point(hwXpos - x, hwYpos + y, hwColor);
        lcd_draw_point(hwXpos + x, hwYpos + y, hwColor);
        lcd_draw_point(hwXpos + x, hwYpos - y, hwColor);
        lcd_draw_point(hwXpos - x, hwYpos - y, hwColor);
        e2 = err;
        if (e2 <= y) {
            err += ++ y * 2 + 1;
            if(-x == y && e2 <= x) e2 = 0;
        }
        if(e2 > x) err += ++ x * 2 + 1;
    } while(x <= 0);
}

//fill a rectangle out at the specified position on lcd.
void lcd_fill_rect(uint16_t hwXpos,  //specify x position.
                   uint16_t hwYpos,  //specify y position.
                   uint16_t hwWidth, //specify the width of the rectangle.
                   uint16_t hwHeight, //specify the height of the rectangle.
                   uint16_t hwColor)  //specify the color of rectangle.
{
	uint16_t i, j;
	
	for(i = 0; i < hwHeight; i ++){
		for(j = 0; j < hwWidth; j ++){
			lcd_draw_point(hwXpos + j, hwYpos + i, hwColor);
		}
	}
}

//draw a vertical line at the specified position on lcd.
void lcd_draw_v_line(		uint16_t hwXpos, //specify x position.
                        uint16_t hwYpos, //specify y position. 
                        uint16_t hwHeight, //specify the height of the vertical line.
                        uint16_t hwColor)  //specify the color of the vertical line.
{	
		uint16_t i, y1 = MIN(hwYpos + hwHeight, LCD_HEIGHT - 1);
	
    for (i = hwYpos; i < y1; i ++) {
        lcd_draw_point(hwXpos, i, hwColor);
    }
}

//draw a horizonal line at the specified position on lcd.
void lcd_draw_h_line(		uint16_t hwXpos, 	//specify x position.
                        uint16_t hwYpos,  //specify y position. 
                        uint16_t hwWidth, //specify the width of the horizonal line.
                        uint16_t hwColor) //specify the color of the horizonal line.
{	
		uint16_t i, x1 = MIN(hwXpos + hwWidth, LCD_WIDTH - 1);
	
    for (i = hwXpos; i < x1; i ++) {
        lcd_draw_point(i, hwYpos, hwColor);
    }
}

void lcd_draw_rect(		uint16_t hwXpos,  //specify x position.
                      uint16_t hwYpos,  //specify y position.
                      uint16_t hwWidth, //specify the width of the rectangle.
                      uint16_t hwHeight, //specify the height of the rectangle.
                      uint16_t hwColor)  //specify the color of rectangle.
{
	lcd_draw_h_line(hwXpos, hwYpos, hwWidth, hwColor);
	lcd_draw_h_line(hwXpos, hwYpos + hwHeight, hwWidth, hwColor);
	lcd_draw_v_line(hwXpos, hwYpos, hwHeight, hwColor);
	lcd_draw_v_line(hwXpos + hwWidth, hwYpos, hwHeight + 1, hwColor);
}


void setRotation(uint8_t rotation)
{
	_rotation = rotation;
	if(ST7789V == lcd_id){
		//switch(_rotation){
		switch(_rotation){

			case 0:
			 /* Memory access control: MY = 0, MX = 0, MV = 0, ML = 0 */
			 /*  */
				lcd_write_register(0X36, 0x00);
				lcd_write_byte(0x2A,LCD_CMD);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte((LCD_WIDTH-1)&0xff,LCD_DATA);
				lcd_write_byte(0x2B,LCD_CMD);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(((LCD_HEIGHT-1)>>8)&0xff,LCD_DATA);
				lcd_write_byte((LCD_HEIGHT-1)&0xff,LCD_DATA);
				lcd_write_byte(0x2C,LCD_CMD);
				break;

			case 1:
			 /* Memory access control: MY = 0, MX = 1, MV = 1, ML = 0 */
			 lcd_write_register(0X36, 0x60);
				lcd_write_byte(0x2A,LCD_CMD);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(((LCD_HEIGHT-1)>>8)&0xff,LCD_DATA);
				lcd_write_byte((LCD_HEIGHT-1)&0xff,LCD_DATA);
				lcd_write_byte(0x2B,LCD_CMD);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte((LCD_WIDTH-1)&0xff,LCD_DATA);	
				lcd_write_byte(0x2C,LCD_CMD);
				break;

			case 2:
			 /* Memory access control: MY = 1, MX = 1, MV = 0, ML = 0 */
			 lcd_write_register(0X36, 0xC0);
				lcd_write_byte(0x2A,LCD_CMD);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte((LCD_WIDTH-1)&0xff,LCD_DATA);
				lcd_write_byte(0x2B,LCD_CMD);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(((LCD_HEIGHT-1)>>8)&0xff,LCD_DATA);
				lcd_write_byte((LCD_HEIGHT-1)&0xff,LCD_DATA);
				lcd_write_byte(0x2C,LCD_CMD);
				break;

			case 3:
			 /* Memory access control: MY = 1, MX = 0, MV = 1, ML = 0 */
			 lcd_write_register(0X36, 0xA0);
			
				lcd_write_byte(0x2A,LCD_CMD);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(((LCD_HEIGHT-1)>>8)&0xff,LCD_DATA);
				lcd_write_byte((LCD_HEIGHT-1)&0xff,LCD_DATA);

				lcd_write_byte(0x2B,LCD_CMD);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte(0x00,LCD_DATA);
				lcd_write_byte((LCD_WIDTH-1)&0xff,LCD_DATA);
				lcd_write_byte(0x2C,LCD_CMD);
				break;
				
				default:
				break;
		 }
	}else{
		//HX8347 ROTATION SET
	} 
}


//initialize the lcd.
void lcd_init(void)
{
		__LCD_CS_SET();		// Comm ML
		__LCD_BKL_SET();	// Comm ML
		
		lcd_id = lcd_read_id();
		//HAL_UART_Transmit(&huart2, &lcd_id, 1, 1000);
		lcd_id = lcd_read_id();
		//HAL_UART_Transmit(&huart2, &lcd_id, 1, 1000);

		if(ST7789V == lcd_id){
			lcd_write_byte(0x11,LCD_CMD);
			HAL_Delay(100);
			lcd_write_register(0x36,0x00);
			lcd_write_register(0x3a,0x55);
			lcd_write_byte(0xb2,LCD_CMD);
			lcd_write_byte(0x0c,LCD_DATA);
			lcd_write_byte(0x0c,LCD_DATA);
			lcd_write_byte(0x00,LCD_DATA);
			lcd_write_byte(0x33,LCD_DATA);
			lcd_write_byte(0x33,LCD_DATA);
			lcd_write_register(0xb7,0x35);
			lcd_write_register(0xbb,0x28);
			lcd_write_register(0xc0,0x3c);
			lcd_write_register(0xc2,0x01);
			lcd_write_register(0xc3,0x0b);
			lcd_write_register(0xc4,0x20);
			lcd_write_register(0xc6,0x0f);
			lcd_write_byte(0xD0,LCD_CMD);
			lcd_write_byte(0xa4,LCD_DATA);
			lcd_write_byte(0xa1,LCD_DATA);
			lcd_write_byte(0xe0,LCD_CMD);
			lcd_write_byte(0xd0,LCD_DATA);
			lcd_write_byte(0x01,LCD_DATA);
			lcd_write_byte(0x08,LCD_DATA);
			lcd_write_byte(0x0f,LCD_DATA);
			lcd_write_byte(0x11,LCD_DATA);
			lcd_write_byte(0x2a,LCD_DATA);
			lcd_write_byte(0x36,LCD_DATA);
			lcd_write_byte(0x55,LCD_DATA);
			lcd_write_byte(0x44,LCD_DATA);
			lcd_write_byte(0x3a,LCD_DATA);
			lcd_write_byte(0x0b,LCD_DATA);
			lcd_write_byte(0x06,LCD_DATA);
			lcd_write_byte(0x11,LCD_DATA);
			lcd_write_byte(0x20,LCD_DATA);
			lcd_write_byte(0xe1,LCD_CMD);
			lcd_write_byte(0xd0,LCD_DATA);
			lcd_write_byte(0x02,LCD_DATA);
			lcd_write_byte(0x07,LCD_DATA);
			lcd_write_byte(0x0a,LCD_DATA);
			lcd_write_byte(0x0b,LCD_DATA);
			lcd_write_byte(0x18,LCD_DATA);
			lcd_write_byte(0x34,LCD_DATA);
			lcd_write_byte(0x43,LCD_DATA);
			lcd_write_byte(0x4a,LCD_DATA);
			lcd_write_byte(0x2b,LCD_DATA);
			lcd_write_byte(0x1b,LCD_DATA);
			lcd_write_byte(0x1c,LCD_DATA);
			lcd_write_byte(0x22,LCD_DATA);
			lcd_write_byte(0x1f,LCD_DATA);
			lcd_write_register(0x55,0xB0);
			lcd_write_byte(0x29,LCD_CMD);
		}else{
			lcd_write_register(0xEA,0x00);
			lcd_write_register(0xEB,0x20);
			lcd_write_register(0xEC,0x0C);
			lcd_write_register(0xED,0xC4);
			lcd_write_register(0xE8,0x38);
			lcd_write_register(0xE9,0x10);
			lcd_write_register(0xF1,0x01);
			lcd_write_register(0xF2,0x10);
			lcd_write_register(0x40,0x01); 
			lcd_write_register(0x41,0x00); 
			lcd_write_register(0x42,0x00); 
			lcd_write_register(0x43,0x10); 
			lcd_write_register(0x44,0x0E); 
			lcd_write_register(0x45,0x24); 
			lcd_write_register(0x46,0x04); 
			lcd_write_register(0x47,0x50); 
			lcd_write_register(0x48,0x02); 
			lcd_write_register(0x49,0x13); 
			lcd_write_register(0x4A,0x19); 
			lcd_write_register(0x4B,0x19); 
			lcd_write_register(0x4C,0x16); 
			lcd_write_register(0x50,0x1B); 
			lcd_write_register(0x51,0x31); 
			lcd_write_register(0x52,0x2F); 
			lcd_write_register(0x53,0x3F); 
			lcd_write_register(0x54,0x3F); 
			lcd_write_register(0x55,0x3E); 
			lcd_write_register(0x56,0x2F); 
			lcd_write_register(0x57,0x7B); 
			lcd_write_register(0x58,0x09); 
			lcd_write_register(0x59,0x06); 
			lcd_write_register(0x5A,0x06); 
			lcd_write_register(0x5B,0x0C); 
			lcd_write_register(0x5C,0x1D); 
			lcd_write_register(0x5D,0xCC); 
			lcd_write_register(0x1B,0x1B);
			lcd_write_register(0x1A,0x01);
			lcd_write_register(0x24,0x2F);
			lcd_write_register(0x25,0x57);
			lcd_write_register(0x23,0x88);
			lcd_write_register(0x18,0x34);
			lcd_write_register(0x19,0x01);
			lcd_write_register(0x01,0x00);
			lcd_write_register(0x1F,0x88);
			lcd_write_register(0x1F,0x80);
			lcd_write_register(0x1F,0x90);
			lcd_write_register(0x1F,0xD0);
			lcd_write_register(0x17,0x05); 
			lcd_write_register(0x36,0x02); 
			lcd_write_register(0x28,0x38);
			lcd_write_register(0x28,0x3F);
			lcd_write_register(0x16,0x18); 
			lcd_write_register(0x02,0x00);
			lcd_write_register(0x03,0x00);
			lcd_write_register(0x04,0x00);
			lcd_write_register(0x05,0xEF);
			lcd_write_register(0x06,0x00);
			lcd_write_register(0x07,0x00);
			lcd_write_register(0x08,0x01);
			lcd_write_register(0x09,0x3F);
		}
    lcd_clear_screen(WHITE);
    __LCD_BKL_SET();
}

uint8_t lcd_read_id(void)
{
	uint8_t reg = 0xDC;
	uint8_t tx_val = 0x00;
	uint8_t rx_val;

	__LCD_CS_CLR();
	__LCD_DC_CLR();
	HAL_SPI_Transmit(&hspi1,&reg,1,0xff);
	HAL_SPI_TransmitReceive(&hspi1,&tx_val,&rx_val,1,0xff);
	__LCD_CS_SET();

	//rx_val = 0x52;

	return rx_val;
}

/*-------------------------------END OF FILE-------------------------------*/

