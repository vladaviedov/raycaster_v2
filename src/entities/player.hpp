#ifndef RC2_ENTITIES_PLAYER_HPP
#define RC2_ENTITIES_PLAYER_HPP

#include "entity.hpp"

class World;
class Player : public Entity {
	private:
		double vert_angle = 0.0;
	public:
		double fov = 60.0;
		int rpd = 1;

		Player(World &world, double xspawn, double yspawn);
		~Player() {};

		virtual void update();
		void render_pov();
};

#endif // RC2_ENTITIES_PLAYER_HPP
