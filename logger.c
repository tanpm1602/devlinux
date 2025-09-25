#include "logger.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

#ifndef LOGGER_MESSAGE_BUFSZ
#define LOGGER_MESSAGE_BUFSZ 1024
#endif

#ifndef LOGGER_LINE_BUFSZ
#define LOGGER_LINE_BUFSZ 1400
#endif

/* Trạng thái module */
static struct {
    FILE      *file_fp;         /* NULL nếu không ghi file */
    LogLevel   min_level;       /* chỉ log nếu level <= min_level */
    LoggerSink sink;            /* NONE / CONSOLE / FILE / BOTH */
} g_logger = { NULL, LOG_DEBUG, LOGGER_SINK_CONSOLE };

/* Bảng tên level */
static const char* level_to_string(LogLevel lv) {
    switch (lv) {
        case LOG_EMERGENCY: return "EMERGENCY";
        case LOG_ALERT:     return "ALERT";
        case LOG_CRITICAL:  return "CRITICAL";
        case LOG_ERROR:     return "ERROR";
        case LOG_WARNING:   return "WARNING";
        case LOG_NOTICE:    return "NOTICE";
        case LOG_INFO:      return "INFO";
        case LOG_DEBUG:     return "DEBUG";
        default:            return "UNKNOWN";
    }
}

/* Lấy thời gian local thread-safe (Linux: localtime_r) */
static int fmt_timestamp(char *buf, size_t bufsz) {
    time_t now = time(NULL);
    struct tm tmv;
#if defined(__unix__) || defined(__APPLE__)
    if (localtime_r(&now, &tmv) == NULL) return -1;
#else
    struct tm *ptm = localtime(&now);
    if (!ptm) return -1;
    tmv = *ptm;
#endif
    if (strftime(buf, bufsz, "%Y-%m-%d %H:%M:%S", &tmv) == 0) return -1;
    return 0;
}

/* Quy tắc xuất ra console:
   - Các mức nghiêm trọng (<= LOG_ERROR) -> stderr
   - Còn lại -> stdout
*/
static FILE* pick_console_stream(LogLevel lv) {
    return (lv <= LOG_ERROR) ? stderr : stdout;
}

/* Mở file ở chế độ append nếu có đường dẫn */
static int open_log_file(const char *path) {
    if (!path) return 0;
    FILE *fp = fopen(path, "a");
    if (!fp) return -1;
    g_logger.file_fp = fp;
    return 0;
}

int logger_init_with_sink(LoggerSink sink, const char *filepath, LogLevel min_level) {
    g_logger.min_level = min_level;
    g_logger.sink      = sink;

    /* Đóng file cũ nếu có */
    if (g_logger.file_fp) {
        fflush(g_logger.file_fp);
        fclose(g_logger.file_fp);
        g_logger.file_fp = NULL;
    }

    if ((sink == LOGGER_SINK_FILE || sink == LOGGER_SINK_BOTH) && filepath) {
        if (open_log_file(filepath) != 0) return -1;
    }
    return 0;
}

void logger_close(void) {
    if (g_logger.file_fp) {
        fflush(g_logger.file_fp);
        fclose(g_logger.file_fp);
        g_logger.file_fp = NULL;
    }
}

int logger_set_min_level(LogLevel min_level) {
    g_logger.min_level = min_level;
    return 0;
}

LogLevel logger_get_min_level(void) {
    return g_logger.min_level;
}

int logger_set_file(const char *filepath) {
    /* Đóng file cũ nếu có */
    if (g_logger.file_fp) {
        fflush(g_logger.file_fp);
        fclose(g_logger.file_fp);
        g_logger.file_fp = NULL;
    }
    if (!filepath) {
        return 0; /* tắt file logging */
    }
    return open_log_file(filepath);
}

int logger_set_sink(LoggerSink sink) {
    g_logger.sink = sink;
    return 0;
}

void logger_flush(void) {
    fflush(stdout);
    fflush(stderr);
    if (g_logger.file_fp) fflush(g_logger.file_fp);
}

void logger_log_impl(LogLevel level, const char *src_file, int src_line,
                     const char *fmt, ...) {
    /* Tắt hẳn logger nếu sink = NONE */
    if (g_logger.sink == LOGGER_SINK_NONE) return;

    /* Lọc mức độ: chỉ log nếu level <= min_level */
    if (level > g_logger.min_level) return;

    /* Format message người dùng */
    char msgbuf[LOGGER_MESSAGE_BUFSZ];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msgbuf, sizeof(msgbuf), fmt, ap);
    va_end(ap);

    /* Lấy timestamp */
    char ts[32];
    if (fmt_timestamp(ts, sizeof(ts)) != 0) {
        strncpy(ts, "0000-00-00 00:00:00", sizeof(ts));
        ts[sizeof(ts)-1] = '\0';
    }

    /* Cắt chỉ tên file (không kèm path) */
    const char *fname = src_file;
    for (const char *p = src_file; *p; ++p) {
        if (*p == '/' || *p == '\\') fname = p + 1;
    }

    /* Dòng log chuẩn */
    char linebuf[LOGGER_LINE_BUFSZ];
    snprintf(linebuf, sizeof(linebuf),
             "[%s] [%s] [%s:%d] - %s\n",
             ts, level_to_string(level), fname, src_line, msgbuf);

    /* Console */
    if (g_logger.sink == LOGGER_SINK_CONSOLE || g_logger.sink == LOGGER_SINK_BOTH) {
        FILE *cstream = pick_console_stream(level);
        fputs(linebuf, cstream);
    }

    /* File */
    if ((g_logger.sink == LOGGER_SINK_FILE || g_logger.sink == LOGGER_SINK_BOTH) && g_logger.file_fp) {
        fputs(linebuf, g_logger.file_fp);
    }
}
