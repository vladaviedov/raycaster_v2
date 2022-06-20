#include "render.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <exception>
#include <GL/gl.h>

#define DEG (M_PI / 180)
#define TAU (M_PI * 2)

#include "../map/types.hpp"
#include "../map/world.hpp"
#include "raycast.hpp"

// Temporary
#define WIDTH 1920
#define HEIGHT 1080

void set_color(rc_result &ray);
void draw_line(double width, double height, double startx);

void render_3d(World &world, double x, double y, double th, double al, double depth, double fov, int rpd) {
	if (fov * rpd != round(fov * rpd)) {
		throw std::logic_error("Ray count (fov * rpd) must be an integer");
	}

	double start_th = th - (fov / 2.0) * DEG;
	const double line_width = WIDTH / (fov * rpd);
	for (int i = 0; i < fov * rpd; i++) {
		double r_th = start_th + i * (1.0 / rpd) * DEG;
		if (r_th < 0) r_th += TAU;
		if (r_th > TAU) r_th -= TAU;
		double d_th = th - r_th;

		rc_result ray = cast_ray(world, x, y, r_th, depth);
		if (ray.distance == HUGE_VAL) continue;
		double real_distance = ray.distance * cos(d_th);

		double height = HEIGHT / real_distance;
		if (height > HEIGHT) height = HEIGHT;

		set_color(ray);
		glLineWidth(line_width);
		draw_line(line_width, height, line_width * i);
	}
}

void set_color(rc_result &ray) {
	switch (ray.cell) {
		case ::WALL:
			if (ray.type == ::HORZ) {
				glColor3d(0.7, 0, 0);
			} else {
				glColor3d(0.5, 0, 0);
			}
			break;
		default:
			glColor3d(0.3, 0.3, 0.3);
			break;
	}
}

void draw_line(double width, double height, double startx) {
	glBegin(GL_QUADS);
	glVertex2d(startx, HEIGHT / 2.0 - height / 2.0);
	glVertex2d(startx + width, HEIGHT / 2.0 - height / 2.0);
	glVertex2d(startx + width, HEIGHT / 2.0 + height / 2.0);
	glVertex2d(startx, HEIGHT / 2.0 + height / 2.0);
	glEnd();
}
