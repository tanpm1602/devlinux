#include "actuators.h"
#include "config.h"
#include <stdio.h>
#include <inttypes.h>

extern uint64_t monotonic_ms(void);

void turn_pump_on(SystemState *st, const char *reason) {
    if (st->act.pump == PUMP_ON) return;
    st->act.pump = PUMP_ON;
    st->pump_on_since_ms = monotonic_ms();
    printf("[ACT] PUMP ON  (reason: %s)\n", reason ? reason : "-");
}

void turn_pump_off(SystemState *st, const char *reason) {
    if (st->act.pump == PUMP_OFF) return;
    st->act.pump = PUMP_OFF;
    st->last_water_end_ms = monotonic_ms();
    printf("[ACT] PUMP OFF (reason: %s)\n", reason ? reason : "-");
}

void update_led(SystemState *st) {
    LedState want = LED_NORMAL;
    if (st->act.error) {
        want = LED_ERROR;
    } else if (st->act.pump == PUMP_ON) {
        want = LED_WATERING;
    } else if (st->cfg.mode == MODE_AUTO &&
               st->sensor.soil_moisture_percent < st->cfg.moisture_min_percent) {
        want = LED_LOW_MOISTURE_ALERT;
    } else {
        want = LED_NORMAL;
    }
    if (st->act.led != want) {
        st->act.led = want;
        const char *name = (want==LED_NORMAL)?"NORMAL":
                           (want==LED_WATERING)?"WATERING":
                           (want==LED_LOW_MOISTURE_ALERT)?"LOW_MOISTURE":
                           "ERROR";
        printf("[LED] -> %s\n", name);
    }
}

void telemetry_print(const SystemState *st, const char *tag) {
    printf("[TEL]%s M=%.1f%%  T=%.1fC  MODE=%s  PUMP=%s  LED=%d  ERR=%d\n",
        (tag && *tag)? " ":"",
        st->sensor.soil_moisture_percent,
        st->sensor.air_temp_c,
        (st->cfg.mode==MODE_AUTO)?"AUTO":"MANUAL",
        (st->act.pump==PUMP_ON)?"ON":"OFF",
        st->act.led,
        st->act.error?1:0
    );
}

void set_error(SystemState *st, bool err, const char *why) {
    if (st->act.error == err) return;
    st->act.error = err;
    printf("[ERR] %s (%s)\n", err? "SET":"CLEAR", why?why:"-");
}
