#include "logger.hpp"

#include <cstdio>
#include <cstdarg>
#include <sstream>
#include <map>

static const std::map<loglev, const char *> loglev_str = {
	{ ::DEBUG, "DEBUG" },
	{ ::INFO, "INFO " },
	{ ::WARN, "WARN " },
	{ ::ERROR, "ERROR" }
};

void log_write(loglev lvl, const char *format, ...) {
	va_list args;
	va_start(args, format);

	std::stringstream log_str;
	log_str << std::string(loglev_str.find(lvl)->second)
		<< " | "
		<< std::string(format)
		<< std::endl;

	vfprintf(stderr, log_str.str().c_str(), args);
	va_end(args);
}
