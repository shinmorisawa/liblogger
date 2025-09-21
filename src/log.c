#include <stdio.h>
#include "logger.h"

Logger logger_init(LoggerOptions options) {
    Logger logger;
    logger.options = options;
    logger.file = NULL;
    logger.result = OK;

    if (options.flags & LOGGER_FILE_LOG) {
        if (options.filename) {
            logger.file = fopen(options.filename, "a");
            if (!logger.file) {
                logger.result = FOPEN_ERR;
            }
            fprintf(logger.file, "┌─liblogger 0.0.1\n│\n");
        } else {
            logger.result = FILENAME_ERR;
        }
    }

    if (options.flags & LOGGER_CONSOLE_LOG) {
        fprintf(stdout, "┌─liblogger 0.0.1\n│\n");
    }

    return logger;
}

void logger_log(Logger* l, u8 level, const char* text) {
    if ((l->options.previous_log_type & level) == 0) {
        if (l->options.flags & LOGGER_CONSOLE_LOG) {
            if (l->options.flags & LOGGER_COLOR_ENABLE) {
                const char* color = "";
                if (level & LOGGER_LOG_TRACE)       color = "\033[36m";
                else if (level & LOGGER_LOG_DEBUG)  color = "\033[34m";
                else if (level & LOGGER_LOG_INFO)   color = "\033[32m";
                else if (level & LOGGER_LOG_WARN)   color = "\033[33m";
                else if (level & LOGGER_LOG_ERROR)  color = "\033[31m";
                else if (level & LOGGER_LOG_FATAL)  color = "\033[35m";
                else if (level & LOGGER_LOG_CATASTROPHIC) color = "\033[41m";

                fprintf(stdout, "%s├─", color);

                if (level & LOGGER_LOG_TRACE)       fprintf(stdout, "TRACE ");
                else if (level & LOGGER_LOG_DEBUG)  fprintf(stdout, "DEBUG ");
                else if (level & LOGGER_LOG_INFO)   fprintf(stdout, "INFO  ");
                else if (level & LOGGER_LOG_WARN)   fprintf(stdout, "WARN  ");
                else if (level & LOGGER_LOG_ERROR)  fprintf(stdout, "ERROR ");
                else if (level & LOGGER_LOG_FATAL)  fprintf(stdout, "FATAL ");
                else if (level & LOGGER_LOG_CATASTROPHIC) fprintf(stdout, "CATASTROPHIC ");

                fprintf(stdout, "%s\033[0m\n", text);
            } else {
                if (level & LOGGER_LOG_TRACE)       fprintf(stdout, "├─TRACE ");
                else if (level & LOGGER_LOG_DEBUG)  fprintf(stdout, "├─DEBUG ");
                else if (level & LOGGER_LOG_INFO)   fprintf(stdout, "├─INFO  ");
                else if (level & LOGGER_LOG_WARN)   fprintf(stdout, "├─WARN  ");
                else if (level & LOGGER_LOG_ERROR)  fprintf(stdout, "├─ERROR ");
                else if (level & LOGGER_LOG_FATAL)  fprintf(stdout, "├─FATAL ");
                else if (level & LOGGER_LOG_CATASTROPHIC) fprintf(stdout, "├─CATASTROPHIC ");

                fprintf(stdout, "%s\n", text);
            }
        }

        if (l->options.flags & LOGGER_FILE_LOG) {
            if (level & LOGGER_LOG_TRACE) {
                fprintf(l->file, "├─TRACE %s\n", text);
            }

            if (level & LOGGER_LOG_DEBUG) {
                fprintf(l->file, "├─DEBUG %s\n", text);
            }

            if (level & LOGGER_LOG_INFO) {
                fprintf(l->file, "├─INFO %s\n", text);
            }

            if (level & LOGGER_LOG_WARN) {
                fprintf(l->file, "├─WARN %s\n", text);
            }

            if (level & LOGGER_LOG_ERROR) {
                fprintf(l->file, "├─ERROR %s\n", text);
            }

            if (level & LOGGER_LOG_FATAL) {
                fprintf(l->file, "├─FATAL %s\n", text);
            }

            if (level & LOGGER_LOG_CATASTROPHIC) {
                fprintf(l->file, "├─CATASTROPHIC %s\n", text);
            }
        }
    }

    if (l->options.previous_log_type & level) {
        char* color = "";
        if (level & 0b0110011) {
            if (l->options.flags & LOGGER_FILE_LOG) {
                fprintf(l->file, "├───►   %s\n", text);
            }

            if (l->options.flags & LOGGER_CONSOLE_LOG) {
                if (l->options.flags & LOGGER_COLOR_ENABLE) {
                    if (level & LOGGER_LOG_TRACE)       color = "\033[36m";
                    else if (level & LOGGER_LOG_DEBUG)  color = "\033[34m";
                    else if (level & LOGGER_LOG_ERROR)  color = "\033[31m";
                    else if (level & LOGGER_LOG_FATAL)  color = "\033[35m";

                    fprintf(stdout, "%s├───►   %s\n", color, text);
                } else {
                    fprintf(stdout, "├───►   %s\n", text);
                }
            }
        }

        if (level & 0b0001100) {
            if (l->options.flags & LOGGER_FILE_LOG) {
                fprintf(l->file, "├───►   %s\n", text);
            }

            if (l->options.flags & LOGGER_CONSOLE_LOG) {
                if (l->options.flags & LOGGER_COLOR_ENABLE) {
                    if (level & LOGGER_LOG_INFO)   color = "\033[32m";
                    else if (level & LOGGER_LOG_WARN)   color = "\033[33m";

                    fprintf(stdout, "%s├───►   %s\n", color, text);
                } else {
                    fprintf(stdout, "├───►  %s\n", text);
                }
            }
        }

        if (level & 0b1000000) {
            if (l->options.flags & LOGGER_FILE_LOG) {
                fprintf(l->file, "├───►          %s\n", text);
            }

            if (l->options.flags & LOGGER_CONSOLE_LOG) {
                if (l->options.flags & LOGGER_COLOR_ENABLE) {
                    if (level & LOGGER_LOG_CATASTROPHIC) color = "\033[41m";

                    fprintf(stdout, "%s├───►          %s\n", color, text);
                } else {
                    fprintf(stdout, "├───►          %s\n", text);
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
        fprintf(l->file, "└───\n");
    if (l->options.flags & LOGGER_CONSOLE_LOG)
        fprintf(stdout, "└───\n");

    if (l->file)
        fclose(l->file);

    return r;
}