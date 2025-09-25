#ifndef CONFIG_H
#define CONFIG_H

// ======= Cấu hình mặc định =======
#define DEFAULT_MOISTURE_MIN_PERCENT     35   // % - bắt đầu tưới khi thấp hơn
#define DEFAULT_MOISTURE_MAX_PERCENT     55   // % - dừng tưới khi đạt
#define DEFAULT_MAX_WATER_SECONDS        60   // s - tưới tối đa mỗi lần
#define DEFAULT_SENSOR_PERIOD_MS         5000 // ms - chu kỳ đọc cảm biến
#define DEFAULT_STATUS_PERIOD_MS         10000// ms - chu kỳ báo trạng thái
#define DEFAULT_COOLDOWN_SECONDS         120  // s - thời gian nghỉ giữa 2 lần tưới
#define DEFAULT_MANUAL_WATER_SECONDS     10   // s - tưới tay

// ======= Mô phỏng cảm biến =======
#define SENSOR_MOISTURE_START            40.0f // %
#define SENSOR_TEMP_START                28.0f // °C
#define SENSOR_MOISTURE_NOISE            2.0f  // %
#define SENSOR_TEMP_NOISE                0.3f  // °C
#define SENSOR_AVG_WINDOW                4     // trung bình trượt

// ======= Chu kỳ vòng lặp chính =======
#define MAIN_LOOP_SLEEP_MS               50    // ms

#endif // CONFIG_H
