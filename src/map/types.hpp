#ifndef RC2_MAP_TYPES_HPP
#define RC2_MAP_TYPES_HPP

#include <string>

typedef enum {
	OOB,
	VOID,
	WALL
} world_cell_t;

typedef struct {
	std::string name;
	int xdim;
	int ydim;
} map_meta;

typedef struct {
	double xspawn;
	double yspawn;
} map_player_info;

#endif // RC2_MAP_TYPES_HPP
