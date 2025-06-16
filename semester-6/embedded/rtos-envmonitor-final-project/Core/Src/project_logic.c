// In project_logic.c
#include "project_logic.h"
#include "sensors.h"
#include "main.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>

DisplayMode display_mode = SHOW_LM335;
char line[LCD_COLS + 1] = {0};
int prev_sw[5] = {0, 0, 0, 0, 0};

char mode_display_tapes[SHOW_MODES][LCD_COLS + 1];
int current_tape_scroll_offsets[SHOW_MODES] = {0};

#ifndef LCD_COLS
#define LCD_COLS 16
#endif

const int initial_leading_spaces[SHOW_MODES] = {
    4,
    2,
    2
};

void create_mode_tape(DisplayMode mode_to_update, float current_lm_temp) {
    char raw_sensor_text[LCD_COLS + 1];

    switch (mode_to_update) {
        case SHOW_LM335:
			snprintf(raw_sensor_text, sizeof(raw_sensor_text), "LM:%.1fC", current_lm_temp);
            break;
        case SHOW_DHT_TEMP:
            snprintf(raw_sensor_text, sizeof(raw_sensor_text), "DHT T:23.4C");
            break;
        case SHOW_DHT_HUM:
            snprintf(raw_sensor_text, sizeof(raw_sensor_text), "DHT H:55.5%%");
            break;
        default:
            strncpy(raw_sensor_text, "Error", sizeof(raw_sensor_text) -1);
            raw_sensor_text[sizeof(raw_sensor_text)-1] = '\0';
            break;
    }

    memset(mode_display_tapes[mode_to_update], ' ', LCD_COLS);
    mode_display_tapes[mode_to_update][LCD_COLS] = '\0';

    int text_len = strlen(raw_sensor_text);
    int start_pos_for_text;

    if (text_len >= LCD_COLS) {
        start_pos_for_text = 0;
    } else {
        start_pos_for_text = (LCD_COLS - text_len) / 2;
        if (start_pos_for_text + text_len > LCD_COLS) {
            start_pos_for_text = 0;
        }
    }

    strncpy(&mode_display_tapes[mode_to_update][start_pos_for_text], raw_sensor_text, text_len);
    mode_display_tapes[mode_to_update][LCD_COLS] = '\0';
}

void ProjectLogic_Init(void) {
    float initial_lm_temp = 25.0f;
    for (int i = 0; i < SHOW_MODES; i++) {
        create_mode_tape((DisplayMode)i, initial_lm_temp);
        current_tape_scroll_offsets[i] = 0;
    }
    display_mode = SHOW_LM335;
}

void ProjectLogic_Update(void) {
    uint16_t adc_val = Read_LM335();
    float voltage = ADC_to_Voltage(adc_val);
    float lm335_temp = Voltage_to_Temperature(voltage);
    //DHT_DataTypedef dht_data;
    //DHT_Read(&dht_data);

    int sw0_right_pressed = !HAL_GPIO_ReadPin(SW0_GPIO_Port, SW0_Pin);
    int sw1_reset_pressed = !HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin);
    int sw2_left_pressed  = !HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin);
    int sw3_up_pressed    = !HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin);
    int sw4_down_pressed  = !HAL_GPIO_ReadPin(SW4_GPIO_Port, SW4_Pin);

    DisplayMode previous_display_mode = display_mode;
    bool needs_lcd_clear = false;

    if (sw3_up_pressed && !prev_sw[3]) {
        display_mode = (DisplayMode)(((int)display_mode + 1) % SHOW_MODES);
    }
    if (sw4_down_pressed && !prev_sw[4]) {
        if (display_mode == SHOW_LM335) {
            display_mode = (DisplayMode)(SHOW_MODES - 1);
        } else {
            display_mode = (DisplayMode)((int)display_mode - 1);
        }
    }

    bool tape_content_needs_update = false;

    if (sw1_reset_pressed && !prev_sw[1]) {
        current_tape_scroll_offsets[display_mode] = 0;
        tape_content_needs_update = true;
        needs_lcd_clear = true;
    }

    if (previous_display_mode != display_mode) {
        tape_content_needs_update = true;
        needs_lcd_clear = true;
    }

    if (display_mode == SHOW_LM335) {
        tape_content_needs_update = true;
    }


    if (tape_content_needs_update) {
        create_mode_tape(display_mode, lm335_temp);
    }

    if (needs_lcd_clear) {
        LCD_WriteCommand(LCD_CLEAR);
        HAL_Delay(5);
    }

    if (sw2_left_pressed && !prev_sw[2]) {
        current_tape_scroll_offsets[display_mode] = (current_tape_scroll_offsets[display_mode] + 1) % LCD_COLS;
    }
    if (sw0_right_pressed && !prev_sw[0]) {
        current_tape_scroll_offsets[display_mode] = (current_tape_scroll_offsets[display_mode] - 1 + LCD_COLS) % LCD_COLS;
    }

    prev_sw[0] = sw0_right_pressed;
    prev_sw[1] = sw1_reset_pressed;
    prev_sw[2] = sw2_left_pressed;
    prev_sw[3] = sw3_up_pressed;
    prev_sw[4] = sw4_down_pressed;

    for (int i = 0; i < LCD_COLS; i++) {
        int tape_char_idx = (current_tape_scroll_offsets[display_mode] + i) % LCD_COLS;
        line[i] = mode_display_tapes[display_mode][tape_char_idx];
    }
    line[LCD_COLS] = '\0';

}
