#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

uint16_t Read_LM335(void);
float ADC_to_Voltage(uint16_t adc);
float Voltage_to_Temperature(float voltage);

#endif // SENSORS_H
