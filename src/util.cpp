#include "util.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

void fatal(int code, const char *format, ...) {
	std::va_list args;
	va_start(args, format);
	std::vfprintf(stderr, format, args);
	fputc('\n', stderr);
	va_end(args);
	
	exit(code);
}

void glfw_error(int error, const char *desc) {
	fatal(1, "GLFW Error %d: %s", error, desc);
}
