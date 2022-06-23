#ifndef RC2_ENTITIES_ENTITY_HPP
#define RC2_ENTITIES_ENTITY_HPP

class World;
class Entity {
	protected:
		World &world;
		
		// Physics
		double xvel = 0.0;
		double yvel = 0.0;
		double xacc = 0.0;
		double yacc = 0.0;
		double friction = 1.0;
		double inertia = 1.0;

		Entity(World &world, double xpos, double ypos);
	public:
		double xpos;
		double ypos;
		double view_angle = 0.0;

		virtual void update();
		void apply_force(double force, double angle);
		void apply_force_relative(double force, double angle);
};

#endif // RC2_ENTITIES_ENTITY_HPP
