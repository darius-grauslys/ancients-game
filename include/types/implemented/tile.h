#ifndef IMPL_TILE_H
#define IMPL_TILE_H

#include "defines_weak.h"
#include "types/implemented/tile_cover_kind.h"

#define DEFINE_TILE

typedef struct Tile_t {
    Tile_Kind the_kind_of__tile             :10;
    Tile_Cover_Kind the_kind_of__tile_cover :10;
    Tile_Slope_Flags__u4 slope_flags__u4    :4;
} Tile;

static inline
Tile_Cover_Kind get_tile_cover_kind_from__tile(
        Tile *p_tile) {
    return p_tile->the_kind_of__tile_cover;
}

typedef uint16_t Tile_Wall_Adjacency_Code__u16;
typedef uint16_t Tile_Stair_Adjacency_Code__u6;

#ifndef TILE_RENDER__WALL_ADJAVENCY
#define TILE_RENDER__WALL_ADJAVENCY 
#define TILE_COVER__BIT_IS_WALL BIT(9)
#define TILE_RENDER__WALL_ADJACENCY__BIT_VFLIP BIT(5)

#define TILE_RENDER__WALL_ADJACENCY__EAST  0b00010001
#define TILE_RENDER__WALL_ADJACENCY__WEST  0b00110001
#define TILE_RENDER__WALL_ADJACENCY__NORTH 0b00000100
#define TILE_RENDER__WALL_ADJACENCY__SOUTH 0b00001000

#define TILE_RENDER__WALL_ADJACENCY__COVER_MASK \
    MASK(2) 
#define TILE_RENDER__WALL_ADJACENCY__SPRITE_COVER_MASK \
    MASK(4)
#endif

#ifndef TILE_STAIR_ADJACENCY_CODE
#define TILE_STAIR_ADJACENCY_CODE
#define TILE_RENDER__STAIR_ADJACENCY__NORTH 0b001000
#define TILE_RENDER__STAIR_ADJACENCY__EAST 0b000100
#define TILE_RENDER__STAIR_ADJACENCY__SOUTH 0b000010
#define TILE_RENDER__STAIR_ADJACENCY__WEST 0b000001

#define TILE_RENDER__STAIR_ADJACENCY__CONCAVE 0b010000
#define TILE_RENDER__STAIR_ADJACENCY__CONVEX 0b100000
#endif

static inline 
bool is_tile_cover__a_wall(
        enum Tile_Cover_Kind kind_of_tile_cover) {
    return kind_of_tile_cover & TILE_COVER__BIT_IS_WALL;
}

static inline
bool is_tile_cover__a_stair(
        enum Tile_Cover_Kind kind_of_tile_cover) {
    return (kind_of_tile_cover 
        & BIT(4))
        && !(kind_of_tile_cover
                & BIT(9));
}

static inline 
bool does_tile__have_a_wall(
        Tile *p_tile) {
    return is_tile_cover__a_wall(get_tile_cover_kind_from__tile(p_tile));
}

static inline 
bool does_wall_adjacency_require__vflip(
        Tile_Wall_Adjacency_Code__u16 wall_adjacency) {
    return
        (bool)(wall_adjacency
                & TILE_RENDER__WALL_ADJACENCY__BIT_VFLIP);
}

#endif
