#include "player.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#include "../map/world.hpp"
#include "../renderer/render.hpp"
#include "../input/handler.hpp"
#include "../util.hpp"

Player::Player(World &world, double xspawn, double yspawn) :
	Entity(world, xspawn, yspawn),
	player_force(Vector::make_cart(0.0, 0.0)) {}

void Player::update(double dt) {
	double move_angle = get_move_angle();

	if (turn_horz) {
		view_angle = wrap_angle(view_angle + turn_horz);
		turn_horz = 0.0;
	}
	if (turn_vert) {
		vert_angle = wrap_angle(vert_angle + turn_vert);
		turn_vert = 0.0;
	}

	if (move_angle != -1) {
		player_force.set_polar(1.0, move_angle + view_angle);
		player_force.apply_to(velocity, dt);
	}

	Entity::update(dt);
}

void Player::render_pov() {
	render_3d(world, position.get_x(), position.get_y(), view_angle, vert_angle, 16, fov, rpd);
}
