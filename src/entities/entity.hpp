#ifndef RC2_ENTITIES_ENTITY_HPP
#define RC2_ENTITIES_ENTITY_HPP

class World;
class Entity {
	protected:
		World &world;
		double xvel = 0.0;
		double yvel = 0.0;
		double vel_cap = 5.0;
		double inertia = 1.0;

		Entity(World &world, double xpos, double ypos);
	public:
		double xpos;
		double ypos;
		double view_angle = 0.0;
};

#endif // RC2_ENTITIES_ENTITY_HPP
