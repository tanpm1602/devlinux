#ifndef WATERING_LOGIC_H
#define WATERING_LOGIC_H
#include "types.h"

// Khởi tạo cấu hình & trạng thái ban đầu
void spws_init(SystemState *st);

// Xử lý nút nhấn (BTN1/BTN2)
void spws_handle_buttons(SystemState *st, bool btn1_toggle_mode, bool btn2_manual);

// Vòng điều khiển tự động (gọi đều đặn trong main loop)
void spws_auto_control(SystemState *st);

// Tick định kỳ: đọc cảm biến, in trạng thái nếu cần
void spws_periodic_tick(SystemState *st);

#endif // WATERING_LOGIC_H
