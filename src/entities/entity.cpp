#include "entity.hpp"

#include "../map/world.hpp"

Entity::Entity(World &world, double xspawn, double yspawn) : world(world), xpos(xspawn), ypos(yspawn) {

}
