#include "handler.hpp"

#include <GLFW/glfw3.h>
#include <memory>
#define _USE_MATH_DEFINES
#include <cmath>

#include "../entities/player.hpp"

bool key_w = false;
bool key_s = false;
bool key_a = false;
bool key_d = false;

void set_key_state(int key, bool state);

#include "../logger.hpp"
void key_handler(GLFWwindow *win, int key, int scancode, int action, int mod) {
	if (action == GLFW_PRESS) {
		set_key_state(key, true);
	}
	if (action == GLFW_RELEASE) {
		set_key_state(key, false);
	}
}

void mouse_handler(GLFWwindow *win, double xpos, double ypos) {
}

double get_move_angle() {
	if (key_w && !key_s && !key_d && !key_a) {
		return 0;
	}
	if (key_s && !key_w && !key_d && !key_a) {
		return M_PI;
	}
	if (key_d && !key_w && !key_s && !key_a) {
		return M_PI / 2;
	}
	if (key_a && !key_w && !key_s && !key_d) {
		return 3 * M_PI / 2;
	}
	
	return -1;
}

void set_key_state(int key, bool state) {
	switch (key) {
		case GLFW_KEY_W:
			key_w = state;
			break;
		case GLFW_KEY_S:
			key_s = state;
			break;
		case GLFW_KEY_A:
			key_a = state;
			break;
		case GLFW_KEY_D:
			key_d = state;
			break;
	}
}
