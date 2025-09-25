#define _GNU_SOURCE
#include "logger.c"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

static LogLevel parse_level(const char *s) {
    /* chấp nhận số (0..7) hoặc tên (EMERGENCY..DEBUG), không phân biệt hoa/thường */
    if (!s || !*s) return LOG_INFO;
    if (isdigit((unsigned char)s[0])) {
        int v = atoi(s);
        if (v < 0) v = 0;
        if (v > 7) v = 7;
        return (LogLevel)v;
    }
    char buf[16];
    size_t n = strlen(s);
    if (n >= sizeof(buf)) n = sizeof(buf) - 1;
    for (size_t i = 0; i < n; ++i) buf[i] = (char)toupper((unsigned char)s[i]);
    buf[n] = '\0';

    if      (!strcmp(buf,"EMERGENCY")) return LOG_EMERGENCY;
    else if (!strcmp(buf,"ALERT"))     return LOG_ALERT;
    else if (!strcmp(buf,"CRITICAL"))  return LOG_CRITICAL;
    else if (!strcmp(buf,"ERROR"))     return LOG_ERROR;
    else if (!strcmp(buf,"WARNING"))   return LOG_WARNING;
    else if (!strcmp(buf,"NOTICE"))    return LOG_NOTICE;
    else if (!strcmp(buf,"INFO"))      return LOG_INFO;
    else if (!strcmp(buf,"DEBUG"))     return LOG_DEBUG;
    return LOG_INFO;
}

static LoggerSink parse_sink(const char *s) {
    if (!s) return LOGGER_SINK_BOTH;
    char buf[16];
    size_t n = strlen(s);
    if (n >= sizeof(buf)) n = sizeof(buf) - 1;
    for (size_t i = 0; i < n; ++i) buf[i] = (char)tolower((unsigned char)s[i]);
    buf[n] = '\0';

    if      (!strcmp(buf,"none"))    return LOGGER_SINK_NONE;
    else if (!strcmp(buf,"console")) return LOGGER_SINK_CONSOLE;
    else if (!strcmp(buf,"file"))    return LOGGER_SINK_FILE;
    else if (!strcmp(buf,"both"))    return LOGGER_SINK_BOTH;
    return LOGGER_SINK_BOTH;
}

static void print_usage(const char *prog) {
    fprintf(stderr,
        "Usage: %s [-l LEVEL] [-o OUTPUT] [-f FILE]\n"
        "  -l, --level   LEVEL   Log level min (0..7 or name). Default: INFO (6)\n"
        "                        0=EMERGENCY 1=ALERT 2=CRITICAL 3=ERROR 4=WARNING 5=NOTICE 6=INFO 7=DEBUG\n"
        "  -o, --output  OUT     Log destination: none | console | file | both (default: both)\n"
        "  -f, --file    PATH    Log file path (required if output=file or both)\n"
        "Examples:\n"
        "  %s -l INFO -o console\n"
        "  %s -l DEBUG -o both -f app.log\n"
        "  %s --level=ERROR --output=file --file=/var/log/myapp.log\n",
        prog, prog, prog, prog
    );
}

int main(int argc, char **argv) {
    LogLevel   level = LOG_INFO;
    LoggerSink sink  = LOGGER_SINK_BOTH;
    const char *filepath = "app.log";

    static struct option long_opts[] = {
        {"level",  required_argument, 0, 'l'},
        {"output", required_argument, 0, 'o'},
        {"file",   required_argument, 0, 'f'},
        {"help",   no_argument,       0, 'h'},
        {0,0,0,0}
    };

    int opt, optidx;
    while ((opt = getopt_long(argc, argv, "l:o:f:h", long_opts, &optidx)) != -1) {
        switch (opt) {
            case 'l': level = parse_level(optarg); break;
            case 'o': sink  = parse_sink(optarg);  break;
            case 'f': filepath = optarg;           break;
            case 'h': print_usage(argv[0]); return 0;
            default:  print_usage(argv[0]); return 1;
        }
    }

    /* Kiểm tra tham số hợp lệ theo đích log */
    if ((sink == LOGGER_SINK_FILE || sink == LOGGER_SINK_BOTH) && (filepath == NULL || *filepath == '\0')) {
        fprintf(stderr, "Error: output requires --file PATH when output=file or both.\n");
        print_usage(argv[0]);
        return 1;
    }

    /* Khởi tạo logger */
    if (logger_init_with_sink(sink, (sink == LOGGER_SINK_FILE || sink == LOGGER_SINK_BOTH) ? filepath : NULL, level) != 0) {
        fprintf(stderr, "Cannot open log file '%s' (if requested). Fallback to console.\n", filepath ? filepath : "(none)");
        logger_init_with_sink(LOGGER_SINK_CONSOLE, NULL, level);
    }

    /* Demo log các mức */
    log_message(LOG_DEBUG,     "This is DEBUG (min=%d)", logger_get_min_level());
    log_message(LOG_INFO,      "This is INFO");
    log_message(LOG_NOTICE,    "This is NOTICE");
    log_message(LOG_WARNING,   "This is WARNING");
    log_message(LOG_ERROR,     "This is ERROR");
    log_message(LOG_CRITICAL,  "This is CRITICAL");
    log_message(LOG_ALERT,     "This is ALERT");
    log_message(LOG_EMERGENCY, "This is EMERGENCY");

    logger_flush();
    logger_close();
    return 0;
}
