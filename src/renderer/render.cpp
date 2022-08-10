#include "render.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <exception>
#include <GL/gl.h>

#define DEG (M_PI / 180)

#include "../util.hpp"
#include "../map/types.hpp"
#include "../map/world.hpp"
#include "raycast.hpp"

// Temporary
#define WIDTH 2560
#define HEIGHT 1440

void set_color(rc_result &ray);
void draw_line(double width, double height, double startx);
void draw_ray(double p_x, double p_y, double r_x, double r_y);

void render_2d(World &world, double x, double y, double th) {
	int xdim, ydim;
	world.get_size(&xdim, &ydim);

	// Draw map
	for (int x = 0; x < xdim; x++) {
		int xs = x * 32;
		for (int y = 0; y < ydim; y++) {
			int ys = y * 32;
			world_cell_t cell = world.get_cell(x, y);
			
			if (cell == WALL) {
				glColor3d(0.3, 0.5, 0.3);
			} else {
				glColor3d(0.0, 0.0, 0.0);
			}

			glBegin(GL_QUADS);
			glVertex2i(xs + 1, ys + 1);
			glVertex2i(xs + 1, ys + 32 - 1);
			glVertex2i(xs + 32 - 1, ys + 32 - 1);
			glVertex2i(xs + 32 - 1, ys + 1);
			glEnd();
		}
	}

	// Draw player
	glColor3d(1.0, 1.0, 0);
	glPointSize(16);
	glBegin(GL_POINTS);
	glVertex2d(x * 32, y * 32);
	glEnd();
}

void render_2d_rays(World &world, double x, double y, double th, double depth, double fov, int rpd) {
	render_2d(world, x, y, th);
	if (fov * rpd != round(fov * rpd)) {
		throw std::logic_error("Ray count (fov * rpd) must be an integer");
	}

	double start_th = th - (fov / 2.0) * DEG;
	glColor3d(1.0, 0.0, 0.0);
	glLineWidth(2);
	for (int i = 0; i < fov * rpd; i++) {
		double r_th = start_th + i * (1.0 / rpd) * DEG;
		r_th = wrap_angle(r_th);
		double d_th = th - r_th;

		rc_result ray = cast_ray(world, x, y, r_th, depth);
		if (ray.distance == HUGE_VAL) continue;

		draw_ray(x, y, x + ray.distance * cos(r_th), y + ray.distance * sin(r_th));
	}

}

void render_3d(World &world, double x, double y, double th, double al, double depth, double fov, int rpd) {
	if (fov * rpd != round(fov * rpd)) {
		throw std::logic_error("Ray count (fov * rpd) must be an integer");
	}

	double start_th = th - (fov / 2.0) * DEG;
	const double line_width = WIDTH / (fov * rpd);
	for (int i = 0; i < fov * rpd; i++) {
		double r_th = start_th + i * (1.0 / rpd) * DEG;
		r_th = wrap_angle(r_th);
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

void draw_ray(double p_x, double p_y, double r_x, double r_y) {
	glBegin(GL_LINES);
	glVertex2d(32 * p_x, 32 * p_y);
	glVertex2d(32 * r_x, 32 * r_y);
	glEnd();
}
