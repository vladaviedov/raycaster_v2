#ifndef RC2_MAP_WORLD_HPP
#define RC2_MAP_WORLD_HPP

#include <string>
#include <filesystem>

#include "types.hpp"

class World {
	private:
		int xdim;
		int ydim;

		double xspawn;
		double yspawn;

		world_cell_t **data;
	public:
		World(std::filesystem::path filename);
		~World();

		world_cell_t get_cell(int x, int y);
		bool is_solid_xy(int x, int y);

		static bool is_solid(world_cell_t cell);
};

#endif // RC2_MAP_WORLD_HPP
