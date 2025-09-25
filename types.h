#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MODE_AUTO = 0,
    MODE_MANUAL
} SystemMode;

typedef enum {
    PUMP_OFF = 0,
    PUMP_ON
} PumpState;

typedef enum {
    LED_NORMAL = 0,
    LED_WATERING,
    LED_LOW_MOISTURE_ALERT,
    LED_ERROR
} LedState;

typedef struct {
    float soil_moisture_percent; // 0..100
    float air_temp_c;            // °C
} SensorData;

typedef struct {
    int   moisture_min_percent;     // ngưỡng bật bơm
    int   moisture_max_percent;     // ngưỡng tắt bơm
    int   max_water_seconds;        // tưới tối đa
    int   sensor_period_ms;         // chu kỳ đọc cảm biến
    int   status_period_ms;         // chu kỳ in trạng thái
    int   cooldown_seconds;         // nghỉ giữa hai lần tưới
    int   manual_water_seconds;     // tưới tay
    SystemMode mode;                // AUTO/MANUAL
} Settings;

typedef struct {
    PumpState pump;
    LedState  led;
    bool      error;
} ActuatorState;

typedef struct {
    SensorData  sensor;
    Settings    cfg;
    ActuatorState act;
    // thời gian
    uint64_t last_sensor_ms;
    uint64_t last_status_ms;
    uint64_t pump_on_since_ms;
    uint64_t last_water_end_ms;
} SystemState;

#endif // TYPES_H
