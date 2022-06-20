#include "raycast.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#include "../map/types.hpp"
#include "../map/world.hpp"

rc_result cast_horz(World &world, double x0, double y0, double th, int depth);
rc_result cast_vert(World &world, double x0, double y0, double th, int depth);

rc_result cast_ray(World &world, double x0, double y0, double th, int depth) {
	rc_result horz = cast_horz(world, x0, y0, th, depth);
	rc_result vert = cast_vert(world, x0, y0, th, depth);

	return horz.distance > vert.distance
		? vert
		: horz;
}

/* Internal */

rc_result cast_horz(World &world, double x0, double y0, double th, int depth) {
	rc_result res = { ::HORZ, ::OOB, HUGE_VAL };
	if (th == 0 || th == M_PI) {
		return res;
	}

	// Direction is flipped, because OpenGL coordinates are flipped
	const int r_direction = th > M_PI ? -1 : 1;
	int r_depth = 0;
	double r_x;
	double r_y;
	int cell_y;
	bool hit_solid;
	
	// Reach first boundary (does not count towards depth)
	r_y = r_direction == 1 ? ceil(y0) : floor(y0);
	r_x = x0 + (r_y - y0) / tan(th);
	cell_y = r_direction == 1 ? r_y : (r_y - 1);
	hit_solid = world.is_solid_xy(r_x, cell_y);

	// Continue casting ray until solid or max depth
	while (!hit_solid && r_depth < depth) {
		r_y += r_direction;
		r_x += r_direction / tan(th);
		cell_y = r_direction == 1 ? r_y : (r_y - 1);
		hit_solid = world.is_solid_xy(r_x, cell_y);

		r_depth++;
	}

	// If not at max depth, calculate distance and get cell type
	if (r_depth < depth) {
		res.cell = world.get_cell(r_x, cell_y);
		res.distance = sqrt((r_x - x0) * (r_x - x0) + (r_y - y0) * (r_y - y0));
	}

	return res;
}

rc_result cast_vert(World &world, double x0, double y0, double th, int depth) {
	rc_result res = { ::VERT, ::OOB, HUGE_VAL };
	if (th == M_PI / 2 || th == 3 * M_PI / 2) {
		return res;
	}

	// Direction is flipped, because OpenGL coordinates are flipped
	const int r_direction = (th < M_PI / 2 || th > 3 * M_PI / 2) ? -1 : 1;
	int r_depth = 0;
	double r_x;
	double r_y;
	int cell_x;
	bool hit_solid;
	
	// Reach first boundary (does not count towards depth)
	r_x = r_direction == 1 ? ceil(x0) : floor(x0);
	r_y = y0 + (r_x - x0) * tan(th);
	cell_x = r_direction == 1 ? r_x : (r_x - 1);
	hit_solid = world.is_solid_xy(cell_x, r_y);

	// Continue casting ray until solid or max depth
	while (!hit_solid && r_depth < depth) {
		r_x += r_direction;
		r_y += r_direction * tan(th);
		cell_x = r_direction == 1 ? r_x : (r_x - 1);
		hit_solid = world.is_solid_xy(cell_x, r_y);

		r_depth++;
	}

	// If not at max depth, calculate distance and get cell type
	if (r_depth < depth) {
		res.cell = world.get_cell(cell_x, r_y);
		res.distance = sqrt((r_x - x0) * (r_x - x0) + (r_y - y0) * (r_y - y0));
	}
	return res;
}
