#include "player.hpp"

#include "../map/world.hpp"
#include "../3d/render.hpp"

Player::Player(World &world, double xspawn, double yspawn) : Entity(world, xspawn, yspawn) {

}

#define _USE_MATH_DEFINES
#include <cmath>
void Player::render_pov() {
	render_3d(world, xpos, ypos, view_angle, vert_angle, 8, fov, rpd);
}
