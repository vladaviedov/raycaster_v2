#ifndef RC2_UTIL_HPP
#define RC2_UTIL_HPP

#define wrap_angle(th) (th - 2 * M_PI * floor(th / 2 * M_PI)) 

void fatal(int code, const char *format, ...);
void glfw_error(int error, const char *desc);

#endif // RC2_UTIL_HPP
