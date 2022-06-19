#include "csvloader.hpp"

#include <iostream>

void CsvLoader::load_meta(map_meta *buf) {
	std::cout << "csv load meta" << std::endl;
}

void CsvLoader::load_player_info(map_player_info *buf) {
	std::cout << "csv load player" << std::endl;
}

world_cell_t **CsvLoader::load_map() {
	std::cout << "csv load map" << std::endl;
	return nullptr;
}
