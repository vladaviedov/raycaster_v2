#include "player.hpp"

#include <cmath>

#include "../map/world.hpp"
#include "../renderer/render.hpp"
#include "../input/handler.hpp"

Player::Player(World &world, double xspawn, double yspawn) : Entity(world, xspawn, yspawn) {

}

void Player::update() {
	double move_angle = get_move_angle();
	if (move_angle != -1) {
		apply_force_relative(0.01, move_angle);
	}
	if (sqrt(xvel * xvel + yvel * yvel) > 0.02) {
		apply_force_relative(-0.01, atan(yvel / xvel));
	}
	Entity::update();
}

void Player::render_pov() {
	render_2d(world, xpos, ypos, view_angle);
//	render_3d(world, xpos, ypos, view_angle, vert_angle, 8, fov, rpd);
}
