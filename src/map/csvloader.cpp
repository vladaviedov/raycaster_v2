#include "csvloader.hpp"
#include "types.hpp"

#include <cstring>
#include <fstream>
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

world_cell_t **CsvLoader::load_map() {
	return nullptr;
}
