#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdatomic.h>
#include "config.h"
#include "types.h"
#include "sensors.h"
#include "actuators.h"
#include "buttons.h"
#include "watering_logic.h"

static atomic_int g_running = 1;

uint64_t monotonic_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec*1000ULL + (uint64_t)ts.tv_nsec/1000000ULL;
}

static void on_sigint(int sig) {
    (void)sig;
    g_running = 0;
}

static void msleep(unsigned ms) {
    struct timespec ts; ts.tv_sec = ms/1000; ts.tv_nsec = (ms%1000)*1000000UL;
    nanosleep(&ts, NULL);
}

int main(void) {
    signal(SIGINT, on_sigint);

    SystemState st;
    memset(&st, 0, sizeof(st));
    spws_init(&st);
    buttons_init();

    printf("[SYS] Smart Plant Watering System started.\n");

    while (g_running) {
        // 1) Poll phím như nút nhấn
        bool b1=false, b2=false, quit=false, snap=false;
        if (buttons_poll(&b1, &b2, &quit, &snap)) {
            if (quit) { g_running=0; break; }
            if (snap) telemetry_print(&st, "SNAP");
            spws_handle_buttons(&st, b1, b2);
        }

        // 2) Tác vụ định kỳ (đọc cảm biến, báo trạng thái, tự tắt manual)
        spws_periodic_tick(&st);

        // 3) Điều khiển tự động
        spws_auto_control(&st);

        // 4) Nghỉ ngắn
        msleep(MAIN_LOOP_SLEEP_MS);
    }

    buttons_shutdown();
    printf("\n[SYS] Exit.\n");
    return 0;
}
