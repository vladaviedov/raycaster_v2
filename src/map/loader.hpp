#ifndef RC2_MAP_LOADER_HPP
#define RC2_MAP_LOADER_HPP

#include <string>
#include <filesystem>

#include "types.hpp"

void load_file(std::filesystem::path file);
bool is_loaded();
void close_file();
void load_meta(map_meta *buf);
void load_player_info(map_player_info *buf);
world_cell_t **load_map();

#endif // RC2_MAP_LOADER_HPP
