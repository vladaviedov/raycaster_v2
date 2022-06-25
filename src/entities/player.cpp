#include "player.hpp"

#include "../map/world.hpp"
#include "../renderer/render.hpp"
#include "../input/handler.hpp"

Player::Player(World &world, double xspawn, double yspawn) : Entity(world, xspawn, yspawn) {

}

#include "../logger.hpp"
void Player::update(double dt) {
	double move_angle = get_move_angle();
	if (move_angle != -1) {
		Vector player = Vector::make_polar(1.0, move_angle + view_angle);
		forces.push_back(player);
		log_debug("Player Force: %.2f @ %.2f", player.get_r(), player.get_th());
	}

	Entity::update(dt);
}

void Player::render_pov() {
	render_2d(world, position.get_x(), position.get_y(), view_angle);
//	render_3d(world, xpos, ypos, view_angle, vert_angle, 8, fov, rpd);
}
