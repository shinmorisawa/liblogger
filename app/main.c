#include <logger.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	LoggerOptions options = {0};
	options.filename = "test.log";
	options.flags = LOGGER_CONSOLE_LOG | LOGGER_FILE_LOG | LOGGER_COLOR_ENABLE | LOGGER_ENABLE_SPLASH;
	Logger logger = logger_init(options);

	logger_log(&logger, LOGGER_LOG_TRACE, "hi");
	logger_log(&logger, LOGGER_LOG_DEBUG, "hi");
	logger_log(&logger, LOGGER_LOG_INFO, "hi");
	logger_log(&logger, LOGGER_LOG_WARN, "hi");
	logger_log(&logger, LOGGER_LOG_ERROR, "hi");
	logger_log(&logger, LOGGER_LOG_FATAL, "hi");
	logger_log(&logger, LOGGER_LOG_CATASTROPHIC, "hi");

	logger_close(&logger);
	return 0;
}
