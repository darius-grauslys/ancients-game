#ifndef IMPL_TILE_H
#define IMPL_TILE_H

#include "defines_weak.h"
#include "types/implemented/tile_cover_kind.h"

#define DEFINE_TILE

typedef struct Tile_t {
    Tile_Kind the_kind_of__tile             :10;
    Tile_Cover_Kind the_kind_of__tile_cover :10;
} Tile;

#endif
