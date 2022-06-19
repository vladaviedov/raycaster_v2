#include "world.hpp"

#include <cstdlib>
#include <filesystem>
#include <memory>

#include "types.hpp"
#include "loader.hpp"

#include <iostream>
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

	std::cerr << "Map name: " << meta.name << std::endl;
	std::cerr << "Map size: " << xdim << "x" << ydim << std::endl;
	std::cerr << "Player spawn: " << xspawn << "," << yspawn << std::endl;
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
