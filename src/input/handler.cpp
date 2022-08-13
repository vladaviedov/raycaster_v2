#include "handler.hpp"

#include <GLFW/glfw3.h>
#include <memory>
#define _USE_MATH_DEFINES
#include <cmath>

#include "../entities/player.hpp"

#define SENSITIVITY 0.0005

bool key_w = false;
bool key_s = false;
bool key_a = false;
bool key_d = false;

void set_key_state(int key, bool state);

double turn_horz = 0.0;
double turn_vert = 0.0;

bool first_mouse = true;
double last_mouse_x = 0.0;
double last_mouse_y = 0.0;

void key_handler(GLFWwindow *win, int key, int scancode, int action, int mod) {
	if (action == GLFW_PRESS) {
		set_key_state(key, true);
	}
	if (action == GLFW_RELEASE) {
		set_key_state(key, false);
	}
}

#include "../logger.hpp"
void mouse_handler(GLFWwindow *win, double xpos, double ypos) {
	if (first_mouse) {
		first_mouse = false;
		return;
	}

	double offset_x = xpos - last_mouse_x;
	double offset_y = ypos - last_mouse_y;

	last_mouse_x = xpos;
	last_mouse_y = ypos;

	turn_horz += offset_x * SENSITIVITY;
	turn_vert += offset_y * SENSITIVITY;
}

double get_move_angle() {
	if (key_w && !key_a && !key_s && !key_d) {
		return 0;
	}
	if (key_w && !key_a && !key_s && key_d) {
		return M_PI / 4;
	}
	if (!key_w && !key_a && !key_s && key_d) {
		return M_PI / 2;
	}
	if (!key_w && !key_a && key_s && key_d) {
		return 3 * M_PI / 4;
	}
	if (!key_w && !key_a && key_s && !key_d) {
		return M_PI;
	}
	if (!key_w && key_a && key_s && !key_d) {
		return 5 * M_PI / 4;
	}
	if (!key_w && key_a && !key_s && !key_d) {
		return 3 * M_PI / 2;
	}
	if (key_w && key_a && !key_s && !key_d) {
		return 7 * M_PI / 4;
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
