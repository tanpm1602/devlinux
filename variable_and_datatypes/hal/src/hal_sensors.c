#include "hal_sensors.h"
#include <stdio.h>

#define SOIL_MOISTURE_MAX_PERCENT_SIM 90
#define SOIL_MOISTURE_MIN_PERCENT_SIM -1
#define SOIL_MOISTURE_STEP_PCT 2
#define AIR_TEMPERATURE_MAX_CELSIUS_SIM 40
#define AIR_TEMPERATURE_MIN_CELSIUS_SIM -1
#define AIR_TEMPERATURE_STEP_C 0.5

static float g_soilMoistureValue;
static float g_airTempertureValue;

void SoilMoistureSensor_Init(float simuValue)
{
    g_soilMoistureValue = simuValue;
}

float SoilMoistureSensor_Read(void)
{
    g_soilMoistureValue += SOIL_MOISTURE_STEP_PCT;
    if (g_soilMoistureValue > SOIL_MOISTURE_MAX_PERCENT_SIM) {
        g_soilMoistureValue = -SOIL_MOISTURE_MIN_PERCENT_SIM;
    }

    return g_soilMoistureValue;
}

void AirTempertureSensor_Init(float simuValue)
{
    g_airTempertureValue = simuValue;
}

float AirTempertureSensor_Read(void)
{
    g_airTempertureValue += AIR_TEMPERATURE_STEP_C;
    if (g_airTempertureValue > AIR_TEMPERATURE_MAX_CELSIUS_SIM) {
        g_airTempertureValue = AIR_TEMPERATURE_MIN_CELSIUS_SIM;
    }

    return g_airTempertureValue;
}