#include "entity.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#include "../map/world.hpp"
#include "../physics/vector.hpp"
#include "../util.hpp"

Entity::Entity(World &world, double xspawn, double yspawn) :
	world(world),
	position(Vector::make_cart(xspawn, yspawn)),
	velocity(Vector::make_cart(0.0, 0.0)),
	friction_force(Vector::make_cart(0.0, 0.0)) {}

void Entity::update(double dt) {
	friction_force.set_polar(velocity.get_r(), wrap_angle(velocity.get_th() + M_PI));
	friction_force.apply_to(velocity, dt / inertia);
	velocity.apply_to(position, dt);
}
