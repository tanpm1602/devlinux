#include "sensors.h"
#include "config.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

static float m_hist[SENSOR_AVG_WINDOW];
static float t_hist[SENSOR_AVG_WINDOW];
static int idx;
static int count;
static float m_cur, t_cur;

static float frand(float a, float b) {
    return a + (float)rand() / (float)RAND_MAX * (b - a);
}

void sensors_init(void) {
    srand((unsigned)time(NULL));
    m_cur = SENSOR_MOISTURE_START;
    t_cur = SENSOR_TEMP_START;
    for (int i=0;i<SENSOR_AVG_WINDOW;i++) {
        m_hist[i]=m_cur; t_hist[i]=t_cur;
    }
    idx=0; count=0;
}

void sensors_read(SensorData *out) {
    // Mô phỏng biến thiên chậm + nhiễu
    m_cur += frand(-0.4f, 0.2f) + frand(-SENSOR_MOISTURE_NOISE, SENSOR_MOISTURE_NOISE)*0.05f;
    if (m_cur < 5.0f) m_cur = 5.0f;
    if (m_cur > 95.0f) m_cur = 95.0f;

    t_cur += frand(-0.05f, 0.05f) + frand(-SENSOR_TEMP_NOISE, SENSOR_TEMP_NOISE)*0.05f;

    m_hist[idx] = m_cur;
    t_hist[idx] = t_cur;
    idx = (idx + 1) % SENSOR_AVG_WINDOW;
    if (count < SENSOR_AVG_WINDOW) count++;

    float m_sum = 0.f, t_sum = 0.f;
    for (int i=0;i<count;i++){ m_sum += m_hist[i]; t_sum += t_hist[i]; }

    out->soil_moisture_percent = m_sum / (float)count;
    out->air_temp_c = t_sum / (float)count;
}

bool sensors_has_error(const SensorData *s) {
    // Quy ước lỗi nếu giá trị phi lý
    if (s->soil_moisture_percent < 0.f || s->soil_moisture_percent > 100.f) return true;
    if (s->air_temp_c < -20.f || s->air_temp_c > 80.f) return true;
    return false;
}
