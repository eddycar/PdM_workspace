#ifndef API_INC_MAX31865_LIB_H_
#define API_INC_MAX31865_LIB_H_

#include <main.h>
#include <math.h>
#include <stdio.h>

#define CS_Pin GPIO_PIN_4 // Chip Select

void MAX31865Init(uint8_t num_wires); // Initialize The Max31865 Module
uint8_t MAX31865ConfigurationInfo(void); // Get max31865 configuration info
double MAX31865GetTemperature(void); // Get Temperature
double MAX31865GetTemperatureMath(double PT100_Resistance); // Conversion of resistance to temperature

#endif /* API_INC_MAX31865_LIB_H_ */
