#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "util.hpp"

int main(int argc, char **argv) {
	glfwSetErrorCallback(&glfw_error);
	glfwInit();
	GLFWwindow *win = glfwCreateWindow(640, 480, "rc2", NULL, NULL);
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(win)) {
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}
