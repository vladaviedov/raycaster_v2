#include "world.hpp"

#include <cstdlib>
#include <filesystem>

#include "types.hpp"
#include "loader.hpp"

World::World(std::filesystem::path filename) {
	map_meta meta;
	map_player_info player_info;

	try {
		load_file(filename);
		load_meta(&meta);
		load_player_info(&player_info);
		data = load_map();
	} catch (const std::exception &e) {
		if (is_loaded()) {
			close_file();
		}
		throw;
	}

	close_file();

	xdim = meta.xdim;
	ydim = meta.ydim;
	xspawn = player_info.xspawn;
	yspawn = player_info.yspawn;
}

World::~World() {
	std::free(data);
}

/* Public */

world_cell_t World::get_cell(int x, int y) {
	// Check for out of bounds
	if (x < 0 || y < 0) {
		return OOB;
	}
	if (x >= xdim || y >= ydim) {
		return OOB;
	}

	return data[x][y];
}

bool World::is_solid_xy(int x, int y) {
	return is_solid(get_cell(x, y));
}

/* Static */

bool World::is_solid(world_cell_t cell) {
	switch (cell) {
		case WALL:
			return true;
		default:
			return false;
	}
}
