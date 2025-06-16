#include "sensors.h"
#include "adc.h"

uint16_t Read_LM335(void) {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    uint16_t value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    return value;
}

float ADC_to_Voltage(uint16_t adc) {
    return (3.3f * adc) / 4095.0f;
}

float Voltage_to_Temperature(float voltage) {
    return -50.0f * (voltage - 2.02f);
}
