#ifndef RC2_MAP_WORLD_HPP
#define RC2_MAP_WORLD_HPP

#include <memory>
#include <string>
#include <filesystem>
#include <vector>

#include "types.hpp"

class Entity;
class Player;
class World {
	private:
		int xdim;
		int ydim;

		double xspawn;
		double yspawn;

		world_cell_t **data;
		std::vector<std::shared_ptr<Entity>> entities;
	public:
		World(std::filesystem::path file);
		~World();

		world_cell_t get_cell(int x, int y);
		bool is_solid_xy(int x, int y);
		std::shared_ptr<Player> spawn_player();

		static bool is_solid(world_cell_t cell);
};

#endif // RC2_MAP_WORLD_HPP
