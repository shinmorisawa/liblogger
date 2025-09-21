project('logger', 'c')

logger_src = files(
  'src/log.c'
)

logger_include = include_directories('src/include')

shared_library('logger', logger_src,
  include_directories: logger_include,
  install: true
)

static_library('logger', logger_src,
  include_directories: logger_include,
  install: true
)

install_headers('src/include/logger.h', subdir: 'liblogger')
