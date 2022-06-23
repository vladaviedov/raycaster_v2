#ifndef RC2_RENDERER_RAYCAST_HPP
#define RC2_RENDERER_RAYCAST_HPP

#include "../map/world.hpp"
#include "../map/types.hpp"

typedef enum {
	HORZ,
	VERT
} hit_type;

typedef struct {
	hit_type type;
	world_cell_t cell;
	double distance;
} rc_result;

rc_result cast_ray(World &world, double x0, double y0, double th, int depth);

#endif // RC2_RENDERER_RAYCAST_HPP
