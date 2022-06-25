#include "entity.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#include "../map/world.hpp"
#include "../physics/vector.hpp"

Entity::Entity(World &world, double xspawn, double yspawn) :
	world(world),
	position(Vector::make_cart(xspawn, yspawn)),
	velocity(Vector::make_cart(0.0, 0.0)) {}

#include "../logger.hpp"
void Entity::update(double dt) {
//	log_debug("Velocity Vector: %.2f @ %.2f", velocity.get_r(), velocity.get_th());
	Vector friction = Vector::make_polar(velocity.get_r(), velocity.get_th() + M_PI);
//	log_debug("Friction Force: %.2f @ %.2f", friction.get_r(), friction.get_th());
	forces.push_back(friction);

	for (auto &f : forces) {
		f.apply_to(velocity, dt / inertia);
	}
	forces.clear();

	velocity.apply_to(position, dt);
}
