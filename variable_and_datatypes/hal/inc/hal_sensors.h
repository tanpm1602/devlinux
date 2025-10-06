#ifndef _HAL_SENSORS_H_
#define _HAL_SENSORS_H_

#include <stdbool.h>

void SoilMoistureSensor_Init(float simuValue);

float SoilMoistureSensor_Read(void);

void AirTempertureSensor_Init(float simuValue);

float AirTempertureSensor_Read(void);

#endif