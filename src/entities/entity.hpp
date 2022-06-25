#ifndef RC2_ENTITIES_ENTITY_HPP
#define RC2_ENTITIES_ENTITY_HPP

#include <vector>

#include "../physics/vector.hpp"

class World;
class Entity {
	protected:
		World &world;
		
		// Physics
		Vector position;
		Vector velocity;
		std::vector<Vector> forces;
		double inertia = 1.0;

		Entity(World &world, double xpos, double ypos);
	public:
		double view_angle = 0.0;

		virtual void update(double dt);
};

#endif // RC2_ENTITIES_ENTITY_HPP
