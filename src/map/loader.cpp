#include "loader.hpp"

#include <filesystem>
#include <exception>
#include <fstream>
#include <memory>

#include "csvloader.hpp"
#include "types.hpp"

#define EXT_CSV ".csv"

Loader *load_file(std::filesystem::path file) {
	if (!std::filesystem::exists(file)) {
		throw std::runtime_error("File does not exist");
	}

	std::unique_ptr<std::ifstream> stream = std::make_unique<std::ifstream>(file);
	if (file.extension() == EXT_CSV) {
		return new CsvLoader(std::move(stream));
	}
	
	// Does not match any known formats
	throw std::runtime_error("Bad file format");
}

