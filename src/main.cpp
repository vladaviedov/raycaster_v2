#include <iostream>
#include <exception>
#include <memory>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "util.hpp"
#include "logger.hpp"
#include "map/world.hpp"
#include "entities/player.hpp"
#include "input/handler.hpp"

std::unique_ptr<World> world = nullptr;
std::shared_ptr<Player> player = nullptr;

void init();

int main(int argc, char **argv) {
	glfwSetErrorCallback(&glfw_error);
	glfwInit();
	GLFWwindow *win = glfwCreateWindow(1920, 1080, "rc2", NULL, NULL);
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);
	glfwSetKeyCallback(win, &key_handler);
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1920, 1080, 0);

	init();

	while (!glfwWindowShouldClose(win)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
		player->update();
		player->render_pov();
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}

void init() {
	log_info("Starting Init");
	world = std::make_unique<World>("../maps/test_cross.csv");
	player = world->spawn_player();
	log_info("Finished Init");
}
