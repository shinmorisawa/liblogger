#pragma once
#include <stdint.h>
#include <stdio.h>

/* magic numbers ooh 
*  also um color_enable only works with
*  console_log so yeah no file_log :(
*/
#define LOGGER_CONSOLE_LOG  0b1
#define LOGGER_FILE_LOG     0b10
#define LOGGER_COLOR_ENABLE 0b100

#define LOGGER_LOG_TRACE        0b1
#define LOGGER_LOG_DEBUG        0b10
#define LOGGER_LOG_INFO         0b100
#define LOGGER_LOG_WARN         0b1000
#define LOGGER_LOG_ERROR        0b10000
#define LOGGER_LOG_FATAL        0b100000
#define LOGGER_LOG_CATASTROPHIC 0b1000000

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

typedef enum {
    OK = 0,
    ERR = 1,
    FOPEN_ERR = 2,
    FILENAME_ERR = 3,
} LoggerResult;

typedef struct {
    u8 flags;
    u8 previous_log_type;
    u8 loggable;
    char* filename;
} LoggerOptions;

typedef struct {
    LoggerOptions options;
    FILE* file;
    LoggerResult result;
} Logger;
/* end of types */

Logger logger_init(LoggerOptions options);
void logger_log(Logger* l, u8 level, const char* text);
LoggerResult logger_close(Logger* l);