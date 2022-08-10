#include "player.hpp"

#include "../map/world.hpp"
#include "../renderer/render.hpp"
#include "../input/handler.hpp"

Player::Player(World &world, double xspawn, double yspawn) :
	Entity(world, xspawn, yspawn),
	player_force(Vector::make_cart(0.0, 0.0)) {}

void Player::update(double dt) {
	double move_angle = get_move_angle();
	if (move_angle != -1) {
		player_force.set_polar(1.0, move_angle + view_angle);
		player_force.apply_to(velocity, dt);
	}
	Entity::update(dt);
}

void Player::render_pov() {
	render_3d(world, position.get_x(), position.get_y(), view_angle, vert_angle, 16, fov, rpd);
}
