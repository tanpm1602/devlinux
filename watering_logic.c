#include "watering_logic.h"
#include "config.h"
#include "sensors.h"
#include "actuators.h"
#include <stdio.h>

extern uint64_t monotonic_ms(void);

static bool cooldown_over(const SystemState *st) {
    uint64_t now = monotonic_ms();
    return (now - st->last_water_end_ms) >= (uint64_t)DEFAULT_COOLDOWN_SECONDS*1000ULL;
}

void spws_init(SystemState *st) {
    st->cfg.moisture_min_percent  = DEFAULT_MOISTURE_MIN_PERCENT;
    st->cfg.moisture_max_percent  = DEFAULT_MOISTURE_MAX_PERCENT;
    st->cfg.max_water_seconds     = DEFAULT_MAX_WATER_SECONDS;
    st->cfg.sensor_period_ms      = DEFAULT_SENSOR_PERIOD_MS;
    st->cfg.status_period_ms      = DEFAULT_STATUS_PERIOD_MS;
    st->cfg.cooldown_seconds      = DEFAULT_COOLDOWN_SECONDS;
    st->cfg.manual_water_seconds  = DEFAULT_MANUAL_WATER_SECONDS;
    st->cfg.mode                  = MODE_AUTO;

    st->act.pump = PUMP_OFF;
    st->act.led  = LED_NORMAL;
    st->act.error= false;

    st->last_sensor_ms = st->last_status_ms = st->pump_on_since_ms = st->last_water_end_ms = 0;

    sensors_init();
    sensors_read(&st->sensor);
    update_led(st);
    telemetry_print(st, "INIT");
}

void spws_handle_buttons(SystemState *st, bool btn1_toggle_mode, bool btn2_manual) {
    if (btn1_toggle_mode) {
        st->cfg.mode = (st->cfg.mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
        if (st->cfg.mode == MODE_MANUAL) {
            // đảm bảo tắt bơm
            turn_pump_off(st, "switch->MANUAL");
        }
        printf("[BTN] MODE -> %s\n", (st->cfg.mode==MODE_AUTO)?"AUTO":"MANUAL");
    }

    if (btn2_manual) {
        if (st->cfg.mode == MODE_MANUAL) {
            // Bật bơm trong khoảng cố định
            turn_pump_on(st, "manual");
        } else {
            printf("[BTN] Manual ignored (not in MANUAL)\n");
        }
    }
}

void spws_auto_control(SystemState *st) {
    if (st->cfg.mode != MODE_AUTO) return;

    if (st->act.error) {
        turn_pump_off(st, "error");
        return;
    }

    // Nếu đang tắt bơm, xét điều kiện bật
    if (st->act.pump == PUMP_OFF) {
        if (st->sensor.soil_moisture_percent < st->cfg.moisture_min_percent) {
            if (cooldown_over(st)) {
                turn_pump_on(st, "auto_low_moisture");
            } else {
                // cool-down chưa xong -> cảnh báo thôi
            }
        }
    } else {
        // Đang tưới: dừng khi đạt ngưỡng hoặc hết thời gian
        uint64_t now = monotonic_ms();
        bool hit_target = (st->sensor.soil_moisture_percent >= st->cfg.moisture_max_percent);
        bool hit_timeout = (now - st->pump_on_since_ms) >= (uint64_t)st->cfg.max_water_seconds*1000ULL;
        if (hit_target)  turn_pump_off(st, "auto_reach_target");
        else if (hit_timeout) turn_pump_off(st, "auto_timeout");
    }
}

void spws_periodic_tick(SystemState *st) {
    uint64_t now = monotonic_ms();

    if (now - st->last_sensor_ms >= (uint64_t)st->cfg.sensor_period_ms) {
        st->last_sensor_ms = now;
        sensors_read(&st->sensor);
        bool err = sensors_has_error(&st->sensor);
        set_error(st, err, err?"sensor_invalid":"sensor_ok");

        // Nếu đang tưới ở MANUAL: tự tắt sau N giây
        if (st->cfg.mode == MODE_MANUAL && st->act.pump == PUMP_ON) {
            if (now - st->pump_on_since_ms >= (uint64_t)st->cfg.manual_water_seconds*1000ULL) {
                turn_pump_off(st, "manual_done");
            }
        }
    }

    if (now - st->last_status_ms >= (uint64_t)st->cfg.status_period_ms) {
        st->last_status_ms = now;
        telemetry_print(st, "PERIODIC");
    }

    update_led(st);
}
