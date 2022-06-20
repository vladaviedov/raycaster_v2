#include "csvloader.hpp"
#include "types.hpp"

#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>
#include <exception>

#define SEPARATOR ','

int CsvLoader::find_section(const char *name) {
	std::string buf;

	file->seekg(SEEK_SET);
	while (std::getline(*file, buf)) {
		if (buf == name) {
			return 0;
		}
	}

	return -1;
}

#define SECT_META "[meta]"
#define META_NAME "name"
#define META_SIZE "size"

void CsvLoader::load_meta(map_meta *buf) {
	if (find_section(SECT_META) < 0) {
		throw std::runtime_error("csvmap meta section not found");
	}

	// Clear struct
	*buf = {};

	std::string line;
	while (std::getline(*file, line)) {
		std::istringstream iss(line);
		std::getline(iss, line, SEPARATOR);
		if (line == META_NAME) {
			std::getline(iss, line, SEPARATOR);
			buf->name = line;
		} else if (line == META_SIZE) {
			std::getline(iss, line, SEPARATOR);
			buf->xdim = stoi(line);
			std::getline(iss, line, SEPARATOR);
			buf->ydim = stoi(line);
		} else {
			// End of section
			break;
		}
	}

	xdim = buf->xdim;
	ydim = buf->ydim;
}

#define SECT_PLAYER "[player]"
#define PLAYER_SPAWN "spawn"

void CsvLoader::load_player_info(map_player_info *buf) {
	if (find_section(SECT_PLAYER) < 0) {
		throw std::runtime_error("csvmap player section not found");
	}

	// Clear struct
	*buf = {};

	std::string line;
	while (std::getline(*file, line)) {
		std::istringstream iss(line);
		std::getline(iss, line, SEPARATOR);
		if (line == PLAYER_SPAWN) {
			std::getline(iss, line, SEPARATOR);
			buf->xspawn = stof(line);
			std::getline(iss, line, SEPARATOR);
			buf->yspawn = stof(line);
		} else {
			// End of section
			break;
		}
	}
}

#define SECT_WALLS "[walls]"
#define WALLS_HWALL "hwall"
#define WALLS_VWALL "vwall"

world_cell_t **CsvLoader::load_map() {
	if (xdim == 0 || ydim == 0) {
		throw std::logic_error("csvmap cannot create map without meta");
	}

	// Allocate map
	world_cell_t **map = (world_cell_t **)std::calloc(xdim, sizeof(world_cell_t *));
	if (map == nullptr) {
		throw std::runtime_error("failed to allocate map");
	}
	for (int i = 0; i < xdim; i++) {
		map[i] = (world_cell_t *)std::calloc(ydim, sizeof(world_cell_t));
		if (map[i] == nullptr) {
			throw std::runtime_error("failed to allocate map");
		}
	}

	if (find_section(SECT_WALLS) < 0) {
		return map;
	}
	
	std::string line;
	while (std::getline(*file, line)) {
		std::istringstream iss(line);
		std::getline(iss, line, SEPARATOR);
		if (line == WALLS_HWALL) {
			std::getline(iss, line, SEPARATOR);
			int y = stoi(line);
			std::getline(iss, line, SEPARATOR);
			int startx = stoi(line);
			std::getline(iss, line, SEPARATOR);
			int endx = stoi(line);
			
			for (int i = startx; i < endx; i++) {
				map[i][y] = ::WALL;
			}
		} else if (line == WALLS_VWALL) {
			std::getline(iss, line, SEPARATOR);
			int x = stoi(line);
			std::getline(iss, line, SEPARATOR);
			int starty = stoi(line);
			std::getline(iss, line, SEPARATOR);
			int endy = stoi(line);
			
			for (int i = starty; i < endy; i++) {
				map[x][i] = ::WALL;
			}
		} else {
			// End of section
			break;
		}
	}

	return map;
}
