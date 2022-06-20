#include <iostream>
#include <exception>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "util.hpp"
#include "logger.hpp"
#include "map/world.hpp"

void init();

int main(int argc, char **argv) {
	glfwSetErrorCallback(&glfw_error);
	glfwInit();
	GLFWwindow *win = glfwCreateWindow(640, 480, "rc2", NULL, NULL);
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);

	init();

	while (!glfwWindowShouldClose(win)) {
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}

void init() {
	log_info("Starting Init");
	try {
		World world("../maps/test_cross.csv");
	} catch(const std::exception &e) {
		fatal(1, e.what());
	}
	log_info("Finished Init");
}
