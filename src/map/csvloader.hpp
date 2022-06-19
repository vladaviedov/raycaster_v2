#ifndef RC2_MAP_CSVLOADER_HPP
#define RC2_MAP_CSVLOADER_HPP

#include "loader.hpp"
#include <fstream>
#include <memory>

class CsvLoader : public Loader {
	public:
		CsvLoader(std::unique_ptr<std::ifstream> f) : Loader(std::move(f)) {}

		virtual void load_meta(map_meta *buf);
		virtual void load_player_info(map_player_info *buf);
		virtual world_cell_t **load_map();
};

#endif // RC2_MAP_CSVLOADER_HPP
