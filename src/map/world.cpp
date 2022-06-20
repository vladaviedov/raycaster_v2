#include "world.hpp"

#include <cstdlib>
#include <filesystem>
#include <memory>

#include "../logger.hpp"
#include "types.hpp"
#include "loader.hpp"

World::World(std::filesystem::path file) {
	map_meta meta;
	map_player_info player_info;

	try {
		std::unique_ptr<Loader> loader(load_file(file));
		loader->load_meta(&meta);
		loader->load_player_info(&player_info);
		data = loader->load_map();
	} catch (const std::exception &e) {
		throw;
	}

	xdim = meta.xdim;
	ydim = meta.ydim;
	xspawn = player_info.xspawn;
	yspawn = player_info.yspawn;

	log_info("Map '%s' loaded (size: %dx%d)", meta.name.c_str(), meta.xdim, meta.ydim);
	log_info("Player spawn point: (%.1f,%.1f)", xspawn, yspawn);
	for (int i = 0; i < xdim; i++) {
#include <sstream>
		std::stringstream ss;
		for (int j = 0; j < ydim; j++) {
			ss << data[i][j] << " ";
		}
		log_debug(ss.str().c_str());
	}
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
