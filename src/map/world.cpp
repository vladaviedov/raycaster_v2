#include "world.hpp"

#include <cstdlib>
#include <filesystem>
#include <memory>

#include "../logger.hpp"
#include "types.hpp"
#include "loader.hpp"
#include "../entities/entity.hpp"
#include "../entities/player.hpp"

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
}

World::~World() {
	std::free(data);
}

/* Public */

void World::get_size(int *xdim, int *ydim) {
	*xdim = this->xdim;
	*ydim = this->ydim;
}

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

std::shared_ptr<Player> World::spawn_player() {
	std::shared_ptr<Player> player = std::make_shared<Player>(*this, xspawn, yspawn);
	entities.push_back(player);
	return player;
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
