#include "buttons.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static struct termios oldt;

void buttons_init(void) {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);    // raw-ish
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    // non-blocking
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    printf("[KEY] a=toggle mode, m=manual, s=status, q=quit\n");
}

void buttons_shutdown(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

bool buttons_poll(bool *btn1_toggle_mode, bool *btn2_manual_water, bool *quit, bool *snap_status) {
    *btn1_toggle_mode = *btn2_manual_water = *quit = *snap_status = false;
    int c = getchar();
    if (c == EOF) return false;
    char ch = (char)c;
    if (ch=='a' || ch=='A') { *btn1_toggle_mode = true; return true; }
    if (ch=='m' || ch=='M') { *btn2_manual_water = true; return true; }
    if (ch=='q' || ch=='Q') { *quit = true; return true; }
    if (ch=='s' || ch=='S') { *snap_status = true; return true; }
    return false;
}
