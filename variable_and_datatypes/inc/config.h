#ifndef _CONFIG_H_
#define _CONFIG_H_

#define ON 1
#define OFF 0
#define HIGH ON
#define LOW OFF
#define TIME_500MS 500
#define TIME_1000MS 1000
#define SECOND_TO_MS(X) X*1000

typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} SystemMode_t;

typedef enum {
    PUMP_OFF,
    PUMP_ON
} PumpState_t;

typedef enum {
    LED_NORMAL,                 // Xanh: Bình thường, chờ
    LED_WATERING,               // Vàng: Đang tưới
    LED_LOW_MOISTURE_ALERT,     // Đỏ nhấp nháy: Độ ẩm thấp, cảnh báo
    LED_ERROR,                  // Đỏ sáng liên tục: Lỗi
} LedState_t;

typedef struct {
    float soilMoisturePercent;
    float airTemperatureCelsius;
} SensorData_t;

typedef struct {
    float minMoistureThreshold;
    float maxMoistureThreshold;
    unsigned int maxWateringDuration_s;
    unsigned int sensorReadInterval_s;
    unsigned int manualWateringDuration_s;
} SystemSettings_t;

typedef struct {
    SystemMode_t currentMode;
    PumpState_t pumpState;
    LedState_t ledState;
    unsigned int wateringTimeCounter;
    unsigned int sensorCheckCounter;
} SystemState_t;

#endif /* _CONFIG_H_ */

