#ifndef SENSORS_H
#define SENSORS_H
#include "types.h"

// Khởi tạo mô phỏng cảm biến
void sensors_init(void);

// Đọc cảm biến (mô phỏng), có làm mịn trung bình trượt
void sensors_read(SensorData *out);

// Phát hiện lỗi cảm biến (ví dụ trả -1, hoặc bất thường)
bool sensors_has_error(const SensorData *s);

#endif // SENSORS_H
