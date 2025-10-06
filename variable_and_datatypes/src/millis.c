#define _POSIX_C_SOURCE 200809L
#include "millis.h"
#include <time.h>

static struct timespec t0;
static int initialized = 0;

static inline unsigned long long timespec_to_ms(const struct timespec *ts) {
    // ms = sec*1000 + nsec/1e6
    return (unsigned long long)ts->tv_sec * 1000ULL + (unsigned long long)(ts->tv_nsec / 1000000ULL);
}

unsigned long long millis(void) {
    struct timespec now;
    if (!initialized) {
        clock_gettime(CLOCK_MONOTONIC, &t0);
        initialized = 1;
    }
    clock_gettime(CLOCK_MONOTONIC, &now);

    // now - t0 -> ms
    unsigned long long now_ms = timespec_to_ms(&now);
    unsigned long long t0_ms  = timespec_to_ms(&t0);
    return now_ms - t0_ms;
}

unsigned long long epoch_millis(void) {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return (unsigned long long)now.tv_sec * 1000ULL + (unsigned long long)(now.tv_nsec / 1000000ULL);
}
