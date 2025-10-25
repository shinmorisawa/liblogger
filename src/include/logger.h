#pragma once
#include <stdint.h>
#include <stdio.h>

#define LOGGER_VERSION "0.0.3"

/* magic numbers ooh 
*  also um color_enable only works with
*  console_log so yeah no file_log :(
*/
#define LOGGER_CONSOLE_LOG   1 << 0
#define LOGGER_FILE_LOG      1 << 1
#define LOGGER_COLOR_ENABLE  1 << 2
#define LOGGER_ENABLE_SPLASH 1 << 3
#define LOGGER_MIN_LOG       1 << 4

#define LOGGER_LOG_TRACE        1 << 0
#define LOGGER_LOG_DEBUG        1 << 1
#define LOGGER_LOG_INFO         1 << 2
#define LOGGER_LOG_WARN         1 << 3
#define LOGGER_LOG_ERROR        1 << 4
#define LOGGER_LOG_FATAL        1 << 5
#define LOGGER_LOG_CATASTROPHIC 1 << 6

#define LOGGER_COLOR_TRACE        "\033[36m"
#define LOGGER_COLOR_DEBUG        "\033[34m"
#define LOGGER_COLOR_INFO         "\033[32m"
#define LOGGER_COLOR_WARN         "\033[33m"
#define LOGGER_COLOR_ERROR        "\033[31m"
#define LOGGER_COLOR_FATAL        "\033[35m"
#define LOGGER_COLOR_CATASTROPHIC "\033[31m"
#define LOGGER_COLOR_RESET        "\033[0m"

/* types */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define true 1
#define false 0

typedef enum LoggerResult {
    OK = 0,
    ERR = 1,
    FOPEN_ERR = 2,
    FILENAME_ERR = 3,
} LoggerResult;

typedef struct LoggerOptions {
    u8 flags;
    u8 previous_log_type;
    u8 loggable;
    char* filename;
    char* splash;
} LoggerOptions;

typedef struct Logger {
    LoggerOptions options;
    LoggerResult result;
    FILE* file;
} Logger;
/* end of types */

#ifdef __cplusplus
extern "C" {
#endif

Logger logger_init(LoggerOptions options);
void logger_log(Logger* l, u8 level, const char* text);
LoggerResult logger_close(Logger* l);

#ifdef __cplusplus
}
#endif
