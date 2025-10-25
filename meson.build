project('logger', 'c')

logger_src = files(
)

subdir('src')

logger_include = include_directories('src/include')

warning_level = 3
werror = true

shared_library('logger', logger_src,
  include_directories: logger_include,
  install: true
)

static_library('logger', logger_src,
  include_directories: logger_include,
  install: true
)

install_headers('src/include/logger.h', subdir: 'liblogger')
