/*
 * project_logic.h
 *
 *  Created on: Jun 9, 2025
 *      Author: vladislav
 */

#ifndef INC_PROJECT_LOGIC_H_
#define INC_PROJECT_LOGIC_H_
#define LCD_COLS 16
#include <stdint.h>
#include "lcd.h"
#include "sensors.h"
#include <stdio.h>
#include <string.h>
#include "main.h"
#include <stdbool.h>
#include "DHT.h"

typedef enum {
    SHOW_LM335 = 0,
    SHOW_DHT_TEMP,
    SHOW_DHT_HUM,
    SHOW_MODES
} DisplayMode;

extern char line[LCD_COLS + 1];
extern DisplayMode display_mode;
void ProjectLogic_Init(void);
void ProjectLogic_Update(void);

#endif /* INC_PROJECT_LOGIC_H_ */
