# usage
## init a logger
```c
LoggerOptions options = {0};
options.flags = LOGGER_CONSOLE_LOG | LOGGER_FILE_LOG | LOGGER_COLOR_ENABLE;
options.filename = "test.log";

Logger logger = logger_init(options);
```
## log messages
```c
logger_log(&logger, LOGGER_LOG_INFO, "hello");
logger_log(&logger, LOGGER_LOG_INFO, "so um yeah");

logger_log(&logger, LOGGER_LOG_CATASTROPHIC, "oh no something catastrophic happened :(");
```
## closing the logger
```c
logger_close(&logger);
```

# log levels
|level|description|
|-----|-----------|
|TRACE|ultra-mega-detail-logs|
|DEBUG|stuff you might want to debug|
|INFO|just generic information|
|WARN|warnings|
|ERROR|errors, but not as bad|
|FATAL|very bad, but not the worst|
|CATASTROPHIC|oh god, this is terrible!|

# flags
only 4 rn but others soon  
`LOGGER_CONSOLE_LOG` -> console logging  
`LOGGER_FILE_LOG` -> outputs to file, requires Logger.options.filename  
`LOGGER_COLOR_ENABLE` -> color (only console rn sorry)  
`LOGGER_ENABLE_SPLASH` -> splash (defaults to "liblogger", set with options.splash)  

# example
```c
LoggerOptions opts = {0};
opts.flags = LOGGER_CONSOLE_LOG | LOGGER_COLOR_ENABLE;
Logger logger = logger_init(opts);

logger_log(&logger, LOGGER_LOG_INFO, "started app");
logger_log(&logger, LOGGER_LOG_WARN, "low memory uwu");

logger_close(&logger);
```