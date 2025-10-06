#include "spws_controller.h"
#include "hal_actuators.h"
#include "hal_buttons.h"
#include "hal_leds.h"
#include "hal_sensors.h"
#include <stdio.h>
#include <unistd.h>
#include "terminal.h"

SystemSettings_t g_systemSettings;
SystemState_t g_systemState;
SensorData_t g_sensorData;

void System_Init();

int main()
{
    System_Init();

    while (1)
    {
        SPWS_ReadButtons();
        SPWS_ReadSensors();

        if (ModeButton_Read() == HIGH)
        {
            SPWS_RunAutoMode();
        }
        else
        {
            SPWS_RunManualMode();
        }

        SPWS_PumpUpdate();
        SPWS_Alert();

        printf("\tMode: %s, Soil moisture: %.2f, Temperature: %.2f\n", g_systemState.currentMode == MODE_AUTO ? "Auto" : "Manual",
               g_sensorData.soilMoisturePercent, g_sensorData.airTemperatureCelsius);

        sleep(2);
    }
    Terminal_Shutdown();
}

void System_Init()
{
    g_systemSettings.manualWateringDuration_s = 10;
    g_systemSettings.maxMoistureThreshold = 70;
    g_systemSettings.minMoistureThreshold = 20;
    g_systemSettings.maxWateringDuration_s = 30;
    g_systemSettings.sensorReadInterval_s = 2;

    LedRGB_TurnOff();
    ModeButton_Init(HIGH); // HIGH <=> AUTO
    PumpButton_Init(LOW);
    AirTempertureSensor_Init(37.0);
    SoilMoistureSensor_Init(5.0);
    Terminal_Init();
}
