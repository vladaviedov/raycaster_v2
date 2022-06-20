#ifndef RC2_ENTITIES_PLAYER_HPP
#define RC2_ENTITIES_PLAYER_HPP

#include "entity.hpp"

class Player : public Entity {
	private:
		double vert_angle;
	public:
		double fov = 60.0;
		int rpd = 3;

		Player(double xspawn, double yspawn) : Entity(xspawn, yspawn) {}
		~Player() {};

		void render_pov();
};

#endif // RC2_ENTITIES_PLAYER_HPP
