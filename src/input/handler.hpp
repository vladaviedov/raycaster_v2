#ifndef RC2_INPUT_HANDLER_HPP
#define RC2_INPUT_HANDLER_HPP

class Player;
#include <memory>
#include <GLFW/glfw3.h>

extern double turn_horz;
extern double turn_vert;

void key_handler(GLFWwindow *win, int key, int scancode, int action, int mod);
void mouse_handler(GLFWwindow *win, double xpos, double ypos);
double get_move_angle();

#endif // RC2_INPUT_HANDLER_HPP
