#ifndef ACTUATORS_H
#define ACTUATORS_H
#include "types.h"

// Điều khiển bơm
void turn_pump_on(SystemState *st, const char *reason);
void turn_pump_off(SystemState *st, const char *reason);

// Điều khiển LED theo trạng thái tổng
void update_led(SystemState *st);

// Gửi “telemetry”/trạng thái (console/UART giả lập)
void telemetry_print(const SystemState *st, const char *tag);

// Cập nhật cờ lỗi (nếu có)
void set_error(SystemState *st, bool err, const char *why);

#endif // ACTUATORS_H
