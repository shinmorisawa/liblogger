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
        fprintf(stdout, "┌─%s\n└", splash);
    if ((options.flags & LOGGER_ENABLE_SPLASH) && (options.flags & LOGGER_FILE_LOG)) 
        fprintf(logger.file, "┌─%s\n└", splash);
    if ((options.flags & LOGGER_CONSOLE_LOG) && !(options.flags & LOGGER_ENABLE_SPLASH))
        fprintf(stdout, "┌─\n└");
    if ((options.flags & LOGGER_FILE_LOG) && !(options.flags & LOGGER_ENABLE_SPLASH))
        fprintf(logger.file, "┌─\n└");

    fflush(stdout);

    if (logger.file)
        fflush(logger.file);

    return logger;
}

void logger_log(Logger* l, u8 level, const char* text) {
    if ((l->options.previous_log_type & level) == 0) {
        if (l->options.flags & LOGGER_CONSOLE_LOG) {
            if (l->options.flags & LOGGER_COLOR_ENABLE) {
                const char* color = "";
                if (level & LOGGER_LOG_TRACE)        color = "\033[36m";
                if (level & LOGGER_LOG_DEBUG)        color = "\033[34m";
                if (level & LOGGER_LOG_INFO)         color = "\033[32m";
                if (level & LOGGER_LOG_WARN)         color = "\033[33m";
                if (level & LOGGER_LOG_ERROR)        color = "\033[31m";
                if (level & LOGGER_LOG_FATAL)        color = "\033[35m";
                if (level & LOGGER_LOG_CATASTROPHIC) color = "\033[41m";

                fprintf(stdout, "\r%s├─", color);

                if (level & LOGGER_LOG_TRACE)        fprintf(stdout, "TRACE ");
                if (level & LOGGER_LOG_DEBUG)        fprintf(stdout, "DEBUG ");
                if (level & LOGGER_LOG_INFO)         fprintf(stdout, "INFO  ");
                if (level & LOGGER_LOG_WARN)         fprintf(stdout, "WARN  ");
                if (level & LOGGER_LOG_ERROR)        fprintf(stdout, "ERROR ");
                if (level & LOGGER_LOG_FATAL)        fprintf(stdout, "FATAL ");
                if (level & LOGGER_LOG_CATASTROPHIC) fprintf(stdout, "CATASTROPHIC ");

                fprintf(stdout, "%s\033[0m\n", text);
            } else {
                if (level & LOGGER_LOG_TRACE)        fprintf(stdout, "\r├─TRACE ");
                if (level & LOGGER_LOG_DEBUG)        fprintf(stdout, "\r├─DEBUG ");
                if (level & LOGGER_LOG_INFO)         fprintf(stdout, "\r├─INFO  ");
                if (level & LOGGER_LOG_WARN)         fprintf(stdout, "\r├─WARN  ");
                if (level & LOGGER_LOG_ERROR)        fprintf(stdout, "\r├─ERROR ");
                if (level & LOGGER_LOG_FATAL)        fprintf(stdout, "\r├─FATAL ");
                if (level & LOGGER_LOG_CATASTROPHIC) fprintf(stdout, "\r├─CATASTROPHIC ");

                fprintf(stdout, "%s\n└", text);
            }
        }

        if (l->options.flags & LOGGER_FILE_LOG) {
            if (level & LOGGER_LOG_TRACE) {
                fprintf(l->file, "\r├─TRACE %s\n└", text);
            }

            if (level & LOGGER_LOG_DEBUG) {
                fprintf(l->file, "\r├─DEBUG %s\n└", text);
            }

            if (level & LOGGER_LOG_INFO) {
                fprintf(l->file, "\r├─INFO  %s\n└", text);
            }

            if (level & LOGGER_LOG_WARN) {
                fprintf(l->file, "\r├─WARN  %s\n└", text);
            }

            if (level & LOGGER_LOG_ERROR) {
                fprintf(l->file, "\r├─ERROR %s\n└", text);
            }

            if (level & LOGGER_LOG_FATAL) {
                fprintf(l->file, "\r├─FATAL %s\n└", text);
            }

            if (level & LOGGER_LOG_CATASTROPHIC) {
                fprintf(l->file, "\r├─CATASTROPHIC %s\n└", text);
            }
        }
    }

    if (l->options.previous_log_type & level) {
        char* color = "";
        if (level & 0b0110011) {
            if (l->options.flags & LOGGER_FILE_LOG) {
                fprintf(l->file, "\r├───►   %s\n└", text);
            }

            if (l->options.flags & LOGGER_CONSOLE_LOG) {
                if (l->options.flags & LOGGER_COLOR_ENABLE) {
                    if (level & LOGGER_LOG_TRACE)       color = "\033[36m";
                    else if (level & LOGGER_LOG_DEBUG)  color = "\033[34m";
                    else if (level & LOGGER_LOG_ERROR)  color = "\033[31m";
                    else if (level & LOGGER_LOG_FATAL)  color = "\033[35m";

                    fprintf(stdout, "\r%s├───►   %s\n└", color, text);
                } else {
                    fprintf(stdout, "\r├───►   %s\n└", text);
                }
            }
        }

        if (level & 0b0001100) {
            if (l->options.flags & LOGGER_FILE_LOG) {
                fprintf(l->file, "\r├───►   %s\n└", text);
            }

            if (l->options.flags & LOGGER_CONSOLE_LOG) {
                if (l->options.flags & LOGGER_COLOR_ENABLE) {
                    if (level & LOGGER_LOG_INFO)   color = "\033[32m";
                    else if (level & LOGGER_LOG_WARN)   color = "\033[33m";

                    fprintf(stdout, "\r%s├───►   %s\n└", color, text);
                } else {
                    fprintf(stdout, "\r├───►  %s\n└", text);
                }
            }
        }

        if (level & 0b1000000) {
            if (l->options.flags & LOGGER_FILE_LOG) {
                fprintf(l->file, "\r├───►          %s\n└", text);
            }

            if (l->options.flags & LOGGER_CONSOLE_LOG) {
                if (l->options.flags & LOGGER_COLOR_ENABLE) {
                    if (level & LOGGER_LOG_CATASTROPHIC) color = "\033[41m";

                    fprintf(stdout, "\r%s├───►          %s\n└", color, text);
                } else {
                    fprintf(stdout, "\r├───►          %s\n└", text);
                }
            }
        }
    }

    fflush(stdout);
    fflush(l->file);

    l->options.previous_log_type = level;
    l->result = OK;
}

LoggerResult logger_close(Logger* l) {
    LoggerResult r = OK;

    if (l->options.flags & LOGGER_FILE_LOG)
        fprintf(l->file, "\r└───\n");
    if (l->options.flags & LOGGER_CONSOLE_LOG)
        fprintf(stdout, "\r└───\n");

    if (l->file)
        fclose(l->file);

    return r;
}