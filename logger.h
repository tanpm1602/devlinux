#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>

/* 8 mức theo syslog (giá trị nhỏ = nghiêm trọng hơn) */
typedef enum {
    LOG_EMERGENCY = 0,
    LOG_ALERT     = 1,
    LOG_CRITICAL  = 2,
    LOG_ERROR     = 3,
    LOG_WARNING   = 4,
    LOG_NOTICE    = 5,
    LOG_INFO      = 6,
    LOG_DEBUG     = 7
} LogLevel;

/* Đích ghi log */
typedef enum {
    LOGGER_SINK_NONE    = 0,
    LOGGER_SINK_CONSOLE = 1,
    LOGGER_SINK_FILE    = 2,
    LOGGER_SINK_BOTH    = 3
} LoggerSink;

/* API khởi tạo/huỷ */
int  logger_init_with_sink(LoggerSink sink, const char *filepath /* có thể NULL */, LogLevel min_level);
static inline int logger_init(const char *filepath, LogLevel min_level) {
    return logger_init_with_sink(LOGGER_SINK_BOTH, filepath, min_level);
}
void logger_close(void);

/* Cấu hình động lúc chạy */
int      logger_set_min_level(LogLevel min_level);
LogLevel logger_get_min_level(void);

int  logger_set_file(const char *filepath);     /* NULL => tắt file logging */
int  logger_set_sink(LoggerSink sink);          /* đổi đích log lúc chạy   */
void logger_flush(void);

/* Hàm nền (dùng qua macro) */
void logger_log_impl(LogLevel level, const char *src_file, int src_line,
                     const char *fmt, ...) __attribute__((format(printf,4,5)));

/* Macro tiện lợi: tự chèn __FILE__ và __LINE__ */
#define log_message(level, fmt, ...) \
    logger_log_impl((level), __FILE__, __LINE__, (fmt), ##__VA_ARGS__)

#endif /* LOGGER_H */
