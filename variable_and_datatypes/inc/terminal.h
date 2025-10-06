#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>

/**
 * @brief Đưa terminal (stdin) vào chế độ raw + non-blocking.
 *
 * - Tắt canonical mode và echo để nhận ký tự ngay khi gõ (không cần Enter).
 * - Đặt stdin thành non-blocking để đọc không chặn.
 * - Tự động đăng ký khôi phục trạng thái khi thoát (atexit, tín hiệu).
 *
 * @note Gọi một lần trước khi dùng Terminal_Read().
 */
void Terminal_Init(void);

/**
 * @brief Khôi phục terminal về trạng thái bình thường.
 *
 * - Khôi phục cấu hình termios và cờ non-blocking của stdin.
 * - An toàn khi gọi nhiều lần; chỉ khôi phục nếu đã được init trước đó.
 */
void Terminal_Shutdown(void);

/**
 * @brief Đọc không chặn các ký tự hiện có trong stdin.
 *
 * @param[out] buf     Bộ đệm nơi ghi dữ liệu đọc được (không thêm '\0').
 * @param[in]  maxlen  Số byte tối đa cần đọc vào buf.
 *
 * @return Số byte đã đọc (>= 0). Trả về 0 nếu không có dữ liệu sẵn.
 *
 * @note Hàm không chặn. Có thể trả về nhiều ký tự nếu người dùng gõ nhanh.
 *       Tự xử lý '\0' nếu muốn coi là chuỗi. Cần gọi sau Terminal_Init().
 */
int Terminal_Read(char *buf, size_t maxlen);

#endif // TERMINAL_H
