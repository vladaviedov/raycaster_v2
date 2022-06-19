#include "logger.hpp"

#include <cstdio>
#include <cstdarg>
#include <sstream>
#include <map>

static const std::map<logl, const char *> logl_str = {
	{ ::DEBUG, "DEBUG" },
	{ ::INFO, "INFO " },
	{ ::WARN, "WARN " },
	{ ::ERROR, "ERROR" }
};

void log_write(logl lvl, const char *format, ...) {
	va_list args;
	va_start(args, format);

	std::stringstream log_str;
	log_str << std::string(logl_str.find(lvl)->second)
		<< " | "
		<< std::string(format)
		<< std::endl;

	vfprintf(stderr, log_str.str().c_str(), args);
	va_end(args);
}
