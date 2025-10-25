#include <stdio.h>
#include "logger.h"

Logger logger_init(LoggerOptions options) {
    Logger logger = {0};
    logger.options = options;
    logger.file = NULL;
    logger.result = OK;

    if (options.flags & LOGGER_FILE_LOG) {
        if (options.filename) {
            logger.file = fopen(options.filename, "a");
            if (!logger.file) {
                logger.result = FOPEN_ERR;
                return logger;
            }
        } else {
            logger.result = FILENAME_ERR;
            return logger;
        }
    }

    const char* splash = options.splash ? options.splash : "liblogger";

    if ((options.flags & LOGGER_ENABLE_SPLASH) && (options.flags & LOGGER_CONSOLE_LOG)) 
        fprintf(stdout, "┌─%s\n└─", splash);
    if ((options.flags & LOGGER_ENABLE_SPLASH) && (options.flags & LOGGER_FILE_LOG)) 
        fprintf(logger.file, "┌─%s\n└─", splash);
    if ((options.flags & LOGGER_CONSOLE_LOG) && !(options.flags & LOGGER_ENABLE_SPLASH))
        fprintf(stdout, "┌─\n└─");
    if ((options.flags & LOGGER_FILE_LOG) && !(options.flags & LOGGER_ENABLE_SPLASH))
        fprintf(logger.file, "┌─\n└─");

    fflush(stdout);

    if (logger.file)
        fflush(logger.file);

    return logger;
}

void logger_log(Logger* l, u8 level, const char* text) {
    /* file log */
    if (l->options.flags & LOGGER_FILE_LOG) {
        switch (level) {
            case LOGGER_LOG_TRACE:
                fprintf(l->file, "\r├─TRACE %s\n└─", text);
                break;
            case LOGGER_LOG_DEBUG:
                fprintf(l->file, "\r├─DEBUG %s\n└─", text);
                break;
            case LOGGER_LOG_INFO:
                fprintf(l->file, "\r├─INFO  %s\n└─", text);
                break;
            case LOGGER_LOG_WARN:
                fprintf(l->file, "\r├─WARN  %s\n└─", text);
                break;
            case LOGGER_LOG_ERROR:
                fprintf(l->file, "\r├─ERROR %s\n└─", text);
                break;
            case LOGGER_LOG_FATAL:
                fprintf(l->file, "\r├─FATAL %s\n└─", text);
                break;
            case LOGGER_LOG_CATASTROPHIC:
                fprintf(l->file, "\r├─CATASTROPHIC %s\n└─", text);
                break;
        }
    }

    /* console log */
    if (l->options.flags & LOGGER_CONSOLE_LOG) {
        char* color = LOGGER_COLOR_RESET;
        if (l->options.flags & LOGGER_COLOR_ENABLE) {
            switch (level) {
                case LOGGER_LOG_TRACE:
                    color = LOGGER_COLOR_TRACE;
                    break;
                case LOGGER_LOG_DEBUG:
                    color = LOGGER_COLOR_DEBUG;
                    break;
                case LOGGER_LOG_INFO:
                    color = LOGGER_COLOR_INFO;
                    break;
                case LOGGER_LOG_WARN:
                    color = LOGGER_COLOR_WARN;
                    break; case LOGGER_LOG_ERROR:
                    color = LOGGER_COLOR_ERROR;
                    break;
                case LOGGER_LOG_FATAL:
                    color = LOGGER_COLOR_FATAL;
                    break;
                case LOGGER_LOG_CATASTROPHIC:
                    color = LOGGER_COLOR_CATASTROPHIC;
                    break;
                default:
                    color = LOGGER_COLOR_RESET;
                    break;
            }
        }
        fprintf(stdout, "%s", color);
        switch (level) {
            case LOGGER_LOG_TRACE:
                fprintf(stdout, "\r├─TRACE %s\n└─", text);
                break;
            case LOGGER_LOG_DEBUG:
                fprintf(stdout, "\r├─DEBUG %s\n└─", text);
                break;
            case LOGGER_LOG_INFO:
                fprintf(stdout, "\r├─INFO  %s\n└─", text);
                break;
            case LOGGER_LOG_WARN:
                fprintf(stdout, "\r├─WARN  %s\n└─", text);
                break;
            case LOGGER_LOG_ERROR:
                fprintf(stdout, "\r├─ERROR %s\n└─", text);
                break;
            case LOGGER_LOG_FATAL:
                fprintf(stdout, "\r├─FATAL %s\n└─", text);
                break;
            case LOGGER_LOG_CATASTROPHIC:
                fprintf(stdout, "\r├─CATASTROPHIC %s\n└─", text);
                break;
            default:
                fprintf(stdout, "\r├─LOG   %s\n└─", text);
                break;
        }
        fprintf(stdout, "%s", LOGGER_COLOR_RESET);
    }

    fflush(stdout);
    if (l->file)
        fflush(l->file);

    l->options.previous_log_type = level;
    l->result = OK;
}

LoggerResult logger_close(Logger* l) {
    LoggerResult r = OK;

    if (l->options.flags & LOGGER_FILE_LOG)
        fprintf(l->file, "\r└─\n");
    if (l->options.flags & LOGGER_CONSOLE_LOG)
        fprintf(stdout, "\r└─\n%s", LOGGER_COLOR_RESET);

    if (l->file)
        fclose(l->file);

    return r;
}
