#include "loader.hpp"

#include <filesystem>
#include <exception>
#include <fstream>

#include "types.hpp"

#define EXT_CSV ".csv"

typedef enum {
	CSV
} loader_t;

static std::ifstream *file_stream = nullptr;
static loader_t loader;

void load_file(std::filesystem::path file) {
	if (!std::filesystem::exists(file)) {
		throw std::runtime_error("File does not exist");
	}

	file_stream = new std::ifstream(file);
	if (file.extension() == EXT_CSV) {
		loader = ::CSV;
		return;
	}
	
	throw std::runtime_error("Bad file format");
}

bool is_loaded() {
	return file_stream != nullptr;
}

void close_file() {
	file_stream->close();
	delete file_stream;
}

void load_meta(map_meta *buf) {
	// todo: implement
}

void load_player_info(map_player_info *buf) {
	// todo: implement
}

world_cell_t **load_map() {
	return nullptr;
}
