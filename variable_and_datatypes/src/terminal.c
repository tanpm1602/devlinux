#define _POSIX_C_SOURCE 200809L
#include "terminal.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

static struct termios s_oldt;
static int s_inited = 0;

static void Terminal__Restore(void) {
    if (!s_inited) return;
    tcsetattr(STDIN_FILENO, TCSANOW, &s_oldt);
    int fl = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (fl != -1) fcntl(STDIN_FILENO, F_SETFL, fl & ~O_NONBLOCK);
    s_inited = 0;
}

static void Terminal__OnSignal(int sig) {
    (void)sig;
    Terminal__Restore();
    _exit(0);
}

void Terminal_Init(void) {
    if (s_inited) return;

    // Lưu cấu hình hiện tại
    tcgetattr(STDIN_FILENO, &s_oldt);
    struct termios t = s_oldt;

    // Raw-ish: không canonical, không echo
    t.c_lflag &= ~(ICANON | ECHO);
    t.c_cc[VMIN]  = 0;  // không yêu cầu tối thiểu byte nào
    t.c_cc[VTIME] = 0;  // không timeout nội bộ
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // Non-blocking read
    int fl = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, fl | O_NONBLOCK);

    // Tự khôi phục khi thoát / Ctrl+C
    atexit(Terminal_Shutdown);
    signal(SIGINT,  Terminal__OnSignal);
    signal(SIGTERM, Terminal__OnSignal);

    s_inited = 1;
}

void Terminal_Shutdown(void) {
    Terminal__Restore();
}

int Terminal_Read(char *buf, size_t maxlen) {
    if (!s_inited || !buf || maxlen == 0) return 0;

    // Đọc hết những gì đang có (tối đa maxlen)
    size_t total = 0;
    while (total < maxlen) {
        ssize_t n = read(STDIN_FILENO, buf + total, maxlen - total);
        if (n > 0) {
            total += (size_t)n;
            // tiếp tục vòng while để gom thêm ký tự nếu người dùng gõ nhanh
            continue;
        }
        // n == -1 (EAGAIN) hoặc n == 0: không còn byte nào để đọc ngay
        break;
    }
    return (int)total;
}
