#include <logger.h>
#include <stdio.h>

int main() {
	LoggerOptions options;
	options.filename = "test.log";
	options.flags = LOGGER_CONSOLE_LOG | LOGGER_FILE_LOG | LOGGER_COLOR_ENABLE;
	Logger logger = logger_init(options);

	logger_log(&logger, LOGGER_LOG_INFO, "Hello there!");
	logger_log(&logger, LOGGER_LOG_INFO, "ok then");
	logger_log(&logger, LOGGER_LOG_FATAL, "fatal lol");
	logger_log(&logger, LOGGER_LOG_FATAL, "ok what is this");

	logger_close(&logger);
	return 0;
}
