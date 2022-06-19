#ifndef RC2_LOGGER_HPP
#define RC2_LOGGER_HPP

typedef enum {
	DEBUG,
	INFO,
	WARN,
	ERROR
} logl;

void log_write(logl lvl, const char *format, ...);
#define log_debug(...) log_write(::DEBUG, __VA_ARGS__)
#define log_info(...) log_write(::INFO, __VA_ARGS__)
#define log_warn(...) log_write(::WARN, __VA_ARGS__)
#define log_error(...) log_write(::ERROR, __VA_ARGS__)

#endif // RC2_LOGGER_HPP
