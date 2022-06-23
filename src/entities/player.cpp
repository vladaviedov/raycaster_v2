#include "player.hpp"

#include "../map/world.hpp"
#include "../3d/render.hpp"
#include "../input/handler.hpp"

Player::Player(World &world, double xspawn, double yspawn) : Entity(world, xspawn, yspawn) {

}

void Player::update() {
	double move_angle = get_move_angle();
	if (move_angle != -1) {
		apply_force_relative(0.5, move_angle);
	}
	Entity::update();
}

void Player::render_pov() {
	render_3d(world, xpos, ypos, view_angle, vert_angle, 8, fov, rpd);
}
