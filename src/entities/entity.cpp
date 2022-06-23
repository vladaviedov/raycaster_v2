#include "entity.hpp"

#include <cmath>

#include "../map/world.hpp"

Entity::Entity(World &world, double xspawn, double yspawn) : world(world), xpos(xspawn), ypos(yspawn) {

}

void Entity::update() {
	xpos += xvel;
	ypos += yvel;
	xvel += xacc;
	yvel += yacc;
}

void Entity::apply_force(double force, double angle) {
	double acc = force / inertia;
	xacc += acc * cos(angle);
	yacc += acc * sin(angle);
}

void Entity::apply_force_relative(double force, double angle) {
	apply_force(force, view_angle + angle);
}
