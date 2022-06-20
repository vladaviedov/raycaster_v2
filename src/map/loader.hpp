#ifndef RC2_MAP_LOADER_HPP
#define RC2_MAP_LOADER_HPP

#include <filesystem>
#include <fstream>
#include <memory>

#include "types.hpp"

class Loader {
	protected:
		std::unique_ptr<std::ifstream> file;
		int xdim = 0;
		int ydim = 0;

		Loader(std::unique_ptr<std::ifstream> f) : file(std::move(f)) {};
	public:
		virtual void load_meta(map_meta *buf) = 0;
		virtual void load_player_info(map_player_info *buf) = 0;
		virtual world_cell_t **load_map() = 0;
};

Loader *load_file(std::filesystem::path file);

#endif // RC2_MAP_LOADER_HPP
