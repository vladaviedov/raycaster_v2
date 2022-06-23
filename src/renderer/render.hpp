#ifndef RC2_RENDERER_RENDER_HPP
#define RC2_RENDERER_RENDER_HPP

#include "../map/world.hpp"

void render_2d(World &world, double x, double y, double th);
void render_3d(World &world, double x, double y, double th, double al, double depth, double fov, int rpd);

#endif // RC2_RENDERER_RENDER_HPP
