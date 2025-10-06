#include "spws_controller.h"
#include "hal_actuators.h"
#include "hal_buttons.h"
#include "hal_leds.h"
#include "hal_sensors.h"
#include "millis.h"
#include <stdio.h>
#include "terminal.h"

#define SIMU_AUTO_MODE_BUTTON 'a'
#define SIMU_MANUAL_MODE_BUTTON 'm'
#define SIMU_TURN_PUMP_ON '1'
#define SIMU_TURN_PUMP_OFF '0'

extern SystemSettings_t g_systemSettings;
extern SystemState_t g_systemState;
extern SensorData_t g_sensorData;

void SPWS_RunAutoMode()
{
    g_systemState.currentMode = MODE_AUTO;

    if (g_sensorData.soilMoisturePercent < 0)
    {
        g_systemState.pumpState = PUMP_OFF;
        return;
    }

    if (g_sensorData.soilMoisturePercent <= g_systemSettings.minMoistureThreshold && g_systemState.pumpState == PUMP_OFF)
    {
        g_systemState.pumpState = PUMP_ON;
        Pump_TurnOn();
        g_systemState.wateringTimeCounter = millis();
    }
    else if (g_sensorData.soilMoisturePercent >= g_systemSettings.maxMoistureThreshold ||
             ((millis() - g_systemState.wateringTimeCounter > SECOND_TO_MS(g_systemSettings.maxWateringDuration_s))))
    {
        g_systemState.pumpState = PUMP_OFF;
        Pump_TurnOff();
    }
}

void SPWS_RunManualMode()
{
    if (g_systemState.currentMode == MODE_AUTO)
    {
        g_systemState.pumpState = PUMP_OFF;
        g_systemState.currentMode = MODE_MANUAL;
        return;
    }
    else if (PumpButton_Read() == HIGH && g_systemState.pumpState == PUMP_OFF)
    {
        g_systemState.pumpState = PUMP_ON;
        Pump_TurnOn();
        g_systemState.wateringTimeCounter = millis();
    }
    else if (g_systemState.pumpState == PUMP_ON &&
             ((millis() - g_systemState.wateringTimeCounter > SECOND_TO_MS(g_systemSettings.manualWateringDuration_s))))
    {
        Pump_TurnOff();
        g_systemState.pumpState = PUMP_OFF;
    }
}

void SPWS_Alert()
{
    static LedState_t preLedState;
    static unsigned long long preTime;
    static bool toggleRedLed;

    if (g_systemState.pumpState == PUMP_ON)
    {
        g_systemState.ledState = LED_WATERING;
    }
    else if (g_sensorData.soilMoisturePercent < 0)
    {
        g_systemState.ledState = LED_ERROR;
    }
    else if (g_sensorData.soilMoisturePercent < g_systemSettings.minMoistureThreshold)
    {
        g_systemState.ledState = LED_LOW_MOISTURE_ALERT;
    }
    else
    {
        g_systemState.ledState = LED_NORMAL;
    }

    switch (g_systemState.ledState)
    {
    case LED_NORMAL:
        LedRGB_SetBlueColor();
        break;
    case LED_WATERING:
        LedRGB_SetYellowColor();
        break;
    case LED_LOW_MOISTURE_ALERT:
        if (preLedState != LED_LOW_MOISTURE_ALERT)
        {
            LedRGB_SetRedColor();
            toggleRedLed = true;
            preTime = millis();
        }
        if (millis() - preTime >= TIME_500MS)
        {
            if (toggleRedLed)
            {
                LedRGB_TurnOff();
            }
            else
            {
                LedRGB_SetRedColor();
            }
            toggleRedLed = !toggleRedLed;
            preTime = millis();
        }
        break;
    case LED_ERROR:
        LedRGB_SetRedColor();
        break;
    default:
        break;
    }
    preLedState = g_systemState.ledState;
}

void SPWS_ReadSensors()
{
    static unsigned long long preTime = 0;
    if (millis() - preTime >= SECOND_TO_MS(g_systemSettings.sensorReadInterval_s) || preTime == 0)
    {
        printf("Read sensors !\n");
        g_sensorData.soilMoisturePercent = SoilMoistureSensor_Read();
        g_sensorData.airTemperatureCelsius = AirTempertureSensor_Read();
        preTime = millis();
    }
}

void SPWS_ReadButtons()
{
    char buf[64];

    printf("Nhap cac phim [a]Auto, [m]Manual, [1][0]PumpButton\n");

    int n = Terminal_Read(buf, sizeof(buf));
    for (int i = 0; i < n; ++i)
    {
        unsigned char c = (unsigned char)buf[i];
        if (c == 'q')
        {
            puts("Bye!");
            Terminal_Shutdown();
            return;
        }

        switch (c)
        {
        case SIMU_AUTO_MODE_BUTTON:
            ModeButton_Init(HIGH);
            break;
        case SIMU_MANUAL_MODE_BUTTON:
            ModeButton_Init(LOW);
            break;
        case SIMU_TURN_PUMP_ON:
            PumpButton_Init(HIGH);
            break;
        case SIMU_TURN_PUMP_OFF:
            PumpButton_Init(LOW);
            break;
        default:
            break;
        }
    }
    fflush(stdout);
}
