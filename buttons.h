#ifndef BUTTONS_H
#define BUTTONS_H
#include <stdbool.h>

// Mô phỏng 2 nút bằng bàn phím, non-blocking
//  a: toggle AUTO/MANUAL (BTN1)
//  m: manual water (BTN2) nếu ở MODE_MANUAL
//  s: in trạng thái
//  q: quit
void buttons_init(void);
void buttons_shutdown(void);

// Poll phím; trả về true nếu có sự kiện
bool buttons_poll(bool *btn1_toggle_mode, bool *btn2_manual_water, bool *quit, bool *snap_status);

#endif // BUTTONS_H
