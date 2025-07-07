#include "world/implemented/ag__chunk_generator_overworld.h"
#include "config/implemented/engine_config.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "numerics.h"
#include "platform_defaults.h"
#include "platform_defines.h"
#include "types/implemented/chunk_generator_kind.h"
#include "types/implemented/tile.h"
#include "types/implemented/tile_cover_kind.h"
#include "types/implemented/tile_kind.h"
#include "util/bitmap/bitmap.h"
#include "vectors.h"
#include "world/global_space.h"
#include "world/chunk_vectors.h"
#include "world/chunk.h"
#include "random.h"
#include "world/world.h"
#include "process/process.h"
#include "world/global_space_manager.h"
#include "world/chunk_pool.h"
#include "collisions/collision_node_pool.h"

#define BIOME__BIT_SHIFT 3
#define BIOME__RANGE BIT(BIOME__BIT_SHIFT)
#define REGION__BIT_SHIFT 5
#define REGION__RANGE BIT(REGION__BIT_SHIFT)

#define REGION__MAX_HEIGHT__BIT_SHIFT (8+8)
#define CHUNK__MAX_HEIGHT__BIT_SHIFT (2+8)

// void f_chunk_generator__overworld(
//         Game *p_game,
//         Global_Space *p_global_space) {
//     if (!p_global_space) {
//         debug_error("f_chunk_generator__overworld, p_global_space == 0.");
//         return;
//     }
//     Chunk *p_chunk =
//         get_p_chunk_from__global_space(
//                 p_global_space);
// }

typedef enum {
    Biome__Ocean = 0,
    Biome__Beach = 1,
    Biome__Desert = 2,
    Biome__Arid = 3,
    Biome__Plains = 4,
    Biome__Forest = 5,
    Biome__Rain_Forest = 6,
    Biome__Tundra = 7,
    Biome__Sparse_Tundra = 8,
    Biome__Snow_Plains = 9,
    Biome__Mountain_Peaks = 10,
    Biome__Desert_Peaks = 11,
    Biome__Snow_Peaks = 12,
    Biome__Unknown
} Biome_Type;

#define HEIGHT__OCEAN i32_to__i32F8(0)
#define HEIGHT__BEACH i32_to__i32F8(2)
#define HEIGHT__LOWLANDS i32_to__i32F8(32)
#define HEIGHT__LOWLANDS_92 (HEIGHT__LOWLANDS+i32_to__i32F8(92))
#define HEIGHT__MIDLANDS i32_to__i32F8(128)
#define HEIGHT__MIDLANDS_24 (HEIGHT__MIDLANDS+i32_to__i32F8(24))
#define HEIGHT__HIGHLANDS i32_to__i32F8(176)
#define HEIGHT__GODLANDS i32_to__i32F8(256)

#define MOISTURE__DRY i32_to__i32F8(32)
#define MOISTURE__ARID i32_to__i32F8(80)
#define MOISTURE__ARID_32 (MOISTURE__ARID+i32_to__i32F8(32))
#define MOISTURE__ARID_48 (MOISTURE__ARID+i32_to__i32F8(48))
#define MOISTURE__NORMAL i32_to__i32F8(144)
#define MOISTURE__HUMID  i32_to__i32F8(176)
#define MOISTURE__WET    i32_to__i32F8(256)

Biome_Type classify_biome(
        i32F8 height,
        i32F8 moisture) {
///
/// height < 0    : ocean
/// height < 2    : beach
/// height < 32   : lowlands
/// height < 92   : lowlands_92
/// height < 128  : midlands
/// height < 152  : midlands_24
/// height < 176  : highlands
/// height >= 176 : godlands
///
/// moisture < 32   : dry
/// moisture < 80   : arid
/// moisture < 144  : normal
/// moisture < 176  : humid
/// moisture >= 176 : wet
///
///      moisture:|    dry    |  arid    | arid+32 | arid+48 |   normal  |  humid  |   wet   |
/// height:       |           |          |         |         |           |         |         |
/// --------------+-----------+----------+---------+---------+-----------+---------+---------+
/// lowlands      |   desert  |  arid    | plains  | plains  |   forest  |r-forest | r-forest|
/// --------------+-----------+----------+---------+---------+-----------+---------+---------+
/// lowlands+92   |   desert  |  desert  |  arid   | forest  |   forest  |r-forest | forest  |
/// --------------+-----------+----------+---------+---------+-----------+---------+---------+
/// midlands      |   desert  |  desert  |  arid   | plains  |   forest  | forest  | tundra  |
/// --------------+-----------+----------+---------+---------+-----------+---------+---------+
/// midlands+24   |   desert  |  desert  |  arid   | s-plains|   tundra  | s-plains| s-plains|
/// --------------+-----------+----------+---------+---------+-----------+---------+---------+
/// highlands     | desert-p  | desert-p | desert-p| m-peaks | snow-peaks|  s-peaks| s-peaks |
/// --------------+-----------+----------+---------+---------+-----------+---------+---------+
/// godlands      | desert-p  | m-peaks  | m-peaks | s-peaks | snow-peaks|  s-peaks| s-peaks |
/// --------------+-----------+----------+---------+---------+-----------+---------+---------+
///

    if (height < HEIGHT__OCEAN) {
        return Biome__Ocean;
    }

    if (height < HEIGHT__BEACH) {
        return Biome__Beach;
    }

    if (height < HEIGHT__LOWLANDS) {
        if (moisture < MOISTURE__DRY) {
            return Biome__Desert;
        }
        if (moisture < MOISTURE__ARID) {
            return Biome__Arid;
        }
        if (moisture < MOISTURE__ARID_48) {
            return Biome__Plains;
        }
        if (moisture < MOISTURE__HUMID) {
            return Biome__Forest;
        }
        return Biome__Rain_Forest;
    }

    if (height < HEIGHT__LOWLANDS_92) {
        if (moisture < MOISTURE__ARID) {
            return Biome__Desert;
        }
        if (moisture < MOISTURE__ARID_32) {
            return Biome__Plains;
        }
        if (moisture < MOISTURE__NORMAL) {
            return Biome__Forest;
        }
        if (moisture < MOISTURE__HUMID) {
            return Biome__Rain_Forest;
        }
        return Biome__Forest;
    }

    if (height < HEIGHT__MIDLANDS) {
        if (moisture < MOISTURE__ARID) {
            return Biome__Desert;
        }
        if (moisture < MOISTURE__ARID_32) {
            return Biome__Arid;
        }
        if (moisture < MOISTURE__ARID_48) {
            return Biome__Plains;
        }
        if (moisture < MOISTURE__HUMID) {
            return Biome__Forest;
        }
        return Biome__Tundra;
    }

    if (height < HEIGHT__HIGHLANDS) {
        if (moisture < MOISTURE__ARID_32) {
            return Biome__Desert_Peaks;
        }
        if (moisture < MOISTURE__ARID_48) {
            return Biome__Mountain_Peaks;
        }
        return Biome__Snow_Peaks;
    }

    if (height < HEIGHT__GODLANDS) {
        if (moisture < MOISTURE__DRY) {
            return Biome__Desert_Peaks;
        }
        if (moisture < MOISTURE__ARID_32) {
            return Biome__Mountain_Peaks;
        }
        return Biome__Snow_Peaks;
    }

    return Biome__Unknown;
}

// Utilities
i32F8 get_random_sample(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random,
        i32 x__i32, i32 y__i32) {
    i32F8 region__h00 = 
        get_pseudo_random_i32_with__xy__intrusively(
                p_repeatable_psuedo_random, 
                (x__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT)
                >> REGION__BIT_SHIFT, 
                (y__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT)
                >> REGION__BIT_SHIFT)
        & MASK(REGION__MAX_HEIGHT__BIT_SHIFT);
    i32F8 region__h10 = 
        get_pseudo_random_i32_with__xy__intrusively(
                p_repeatable_psuedo_random, 
                ((x__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT)
                >> REGION__BIT_SHIFT) + 1, 
                ((y__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT)
                >> REGION__BIT_SHIFT))
        & MASK(REGION__MAX_HEIGHT__BIT_SHIFT);
    i32F8 region__h01 = 
        get_pseudo_random_i32_with__xy__intrusively(
                p_repeatable_psuedo_random, 
                ((x__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT)
                >> REGION__BIT_SHIFT), 
                ((y__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT)
                >> REGION__BIT_SHIFT) + 1)
        & MASK(REGION__MAX_HEIGHT__BIT_SHIFT);
    i32F8 region__h11 = 
        get_pseudo_random_i32_with__xy__intrusively(
                p_repeatable_psuedo_random, 
                ((x__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT)
                >> REGION__BIT_SHIFT) + 1, 
                ((y__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT)
                >> REGION__BIT_SHIFT) + 1)
        & MASK(REGION__MAX_HEIGHT__BIT_SHIFT);

    u32 x__base_region__u32 = mod__i32_into__u32(
            x__i32, 
            BIT(REGION__BIT_SHIFT + CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT));
    u32 y__base_region__u32 = mod__i32_into__u32(
            y__i32, 
            BIT(REGION__BIT_SHIFT + CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT));
    i32F8 region__height=
        lerp__xy__i32F8(
                region__h00, 
                region__h10, 
                region__h01, 
                region__h11, 
                divide_into__i32F8(
                    x__base_region__u32,
                    BIT(REGION__BIT_SHIFT + CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT)), 
                divide_into__i32F8(
                    y__base_region__u32,
                    BIT(REGION__BIT_SHIFT + CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT))
                );

    i32F8 chunk__h00 =
        get_pseudo_random_i32_with__xy__intrusively(
                p_repeatable_psuedo_random, 
                (x__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT), 
                (y__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT))
                & MASK(CHUNK__MAX_HEIGHT__BIT_SHIFT);

    i32F8 chunk__h10 =
        get_pseudo_random_i32_with__xy__intrusively(
                p_repeatable_psuedo_random, 
                (x__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT) + 1, 
                (y__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT))
                & MASK(CHUNK__MAX_HEIGHT__BIT_SHIFT);

    i32F8 chunk__h01 =
        get_pseudo_random_i32_with__xy__intrusively(
                p_repeatable_psuedo_random, 
                (x__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT), 
                (y__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT) + 1)
                & MASK(CHUNK__MAX_HEIGHT__BIT_SHIFT);

    i32F8 chunk__h11 =
        get_pseudo_random_i32_with__xy__intrusively(
                p_repeatable_psuedo_random, 
                (x__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT) + 1, 
                (y__i32 >> CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT) + 1)
                & MASK(CHUNK__MAX_HEIGHT__BIT_SHIFT);

    u32 x__base_chunk__u32 = mod__i32_into__u32(
            x__i32, 
            BIT(CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT));
    u32 y__base_chunk__u32 = mod__i32_into__u32(
            y__i32, 
            BIT(CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT));
    i32F8 chunk__height = lerp__xy__i32F8(
                chunk__h00, 
                chunk__h10, 
                chunk__h01, 
                chunk__h11, 
                divide_into__i32F8(
                    x__base_chunk__u32, 
                    BIT(CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT)), 
                divide_into__i32F8(
                    y__base_chunk__u32, 
                    BIT(CHUNK__WIDTH_AND__HEIGHT__BIT_SHIFT))
                );

    return lerp__i32F8(
            region__height, 
            region__height + chunk__height, 
            0b11100000);
}

i32F8 flatten_height(i32F8 height__i32F8) {
    i32 z__level = i32F8_to__i32(height__i32F8);

    if (z__level < HEIGHT__BEACH) {
        return lerp__i32F8(height__i32F8, HEIGHT__BEACH, 0b11010000);
    }
    if (z__level < HEIGHT__LOWLANDS) {
        return lerp__i32F8(height__i32F8, HEIGHT__LOWLANDS, 0b11010000);
    }
    if (z__level < HEIGHT__MIDLANDS) {
        return lerp__i32F8(height__i32F8, HEIGHT__MIDLANDS, 0b11010000);
    }
    if (z__level < HEIGHT__HIGHLANDS) {
        return lerp__i32F8(height__i32F8, HEIGHT__HIGHLANDS, 0b00110100);
    }
    return height__i32F8;
}

// Fills chunk entirely with given tile kind
void fill_chunk_with(
        Chunk *p_chunk,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover) {
    for (i32 dz = 0; dz < CHUNK__WIDTH; ++dz) {
        for (i32 dy = 0; dy < CHUNK__HEIGHT; ++dy) {
            for (i32 dx = 0; dx < CHUNK__DEPTH; ++dx) {
                Local_Tile_Vector__3u8 tile_vec = { dx, dy, dz };
                Tile *p_tile = get_p_tile_from__chunk(p_chunk, tile_vec);
                p_tile->the_kind_of__tile = the_kind_of__tile;
                p_tile->the_kind_of__tile_cover = the_kind_of__tile_cover;
            }
        }
    }
}

i32 ag__get_natural_world_height_at__xy(
        Repeatable_Psuedo_Random *p_random,
        i32 x,
        i32 y) {
    return i32F8_to__i32(
            get_random_sample(p_random, x, y));
}

typedef u8 Slope_Map_Value__u2;

#define SLOPE_MAP__WALL 0b00
#define SLOPE_MAP__PROSPECT_SLOPE 0b01
#define SLOPE_MAP__CONFIRMED_SLOPE 0b10
#define SLOPE_MAP__EXCLUDED_SLOPE 0b11

typedef struct Slope_Map_Entry_t {
    u8 quantity_of__adjacent_walls : 2;
    Slope_Map_Value__u2 final_slope_map__value : 2;
    union {
        struct {
            bool is_wall_adjacent__west  : 1;
            bool is_wall_adjacent__south : 1;
            bool is_wall_adjacent__east  : 1;
            bool is_wall_adjacent__north : 1;
        };
        u8 wall_adjacency_flags__u4          : 4;
    };
    union {
        struct {
            bool is_stair_adjacent__west  : 1;
            bool is_stair_adjacent__south : 1;
            bool is_stair_adjacent__east  : 1;
            bool is_stair_adjacent__north : 1;
        };
        u8 stair_adjacency_flags__u4          : 4;
    };
} Slope_Map_Entry;

typedef Slope_Map_Entry Slope_Map[CHUNK__WIDTH * CHUNK__HEIGHT];

static inline
Slope_Map_Entry *get_p_slope_map_entry__at(
        Slope_Map slope_map,
        u8 local__x,
        u8 local__y) {
#ifndef NDEBUG
    if (local__x >= CHUNK__WIDTH)
        return 0;
    if (local__y >= CHUNK__HEIGHT)
        return 0;
#endif
    return &slope_map[local__x + ((CHUNK__HEIGHT - local__y - 1) * CHUNK__WIDTH)];
}

void generate_slope_map(
        Global_Space_Manager *p_global_space_manager,
        Global_Space *p_global_space,
        Chunk *ptr_array_of__chunk__neighbors[8],
        Slope_Map slope_map,
        u8 local__z) {
    Chunk *p_chunk = get_p_chunk_from__global_space(p_global_space);

    for (i8 local__y = 0; local__y < CHUNK__HEIGHT; local__y++) {
        for (i8 local__x = 0; local__x < CHUNK__WIDTH; local__x++) {
            Slope_Map_Entry *p_entry = 
                get_p_slope_map_entry__at(slope_map, local__x, local__y);
            memset(p_entry, 0, sizeof(Slope_Map_Entry));
            Tile *p_tile = get_p_tile_from__chunk(
                    p_chunk, (Local_Tile_Vector__3u8) {local__x, local__y, local__z});
            if (is_tile_cover__a_wall(
                        get_tile_cover_kind_from__tile(p_tile))) {
                p_entry->final_slope_map__value =
                    SLOPE_MAP__WALL;
                continue;
            }
            p_entry->final_slope_map__value =
                SLOPE_MAP__PROSPECT_SLOPE;
            p_tile = get_p_tile_from__chunk_neighborhood(
                    p_chunk, 
                    ptr_array_of__chunk__neighbors,
                    local__x+1, local__y, local__z);
            if (p_tile && is_tile_cover__a_wall(
                        get_tile_cover_kind_from__tile(p_tile))) {
                p_entry->is_wall_adjacent__east = true;
                p_entry->quantity_of__adjacent_walls++;
            }
            p_tile = get_p_tile_from__chunk_neighborhood(
                    p_chunk, 
                    ptr_array_of__chunk__neighbors,
                    local__x-1, local__y, local__z);
            if (p_tile && is_tile_cover__a_wall(
                        get_tile_cover_kind_from__tile(p_tile))) {
                p_entry->is_wall_adjacent__west = true;
                p_entry->quantity_of__adjacent_walls++;
            }
            p_tile = get_p_tile_from__chunk_neighborhood(
                    p_chunk, 
                    ptr_array_of__chunk__neighbors,
                    local__x, local__y+1, local__z);
            if (p_tile && is_tile_cover__a_wall(
                        get_tile_cover_kind_from__tile(p_tile))) {
                p_entry->is_wall_adjacent__north = true;
                p_entry->quantity_of__adjacent_walls++;
            }
            p_tile = get_p_tile_from__chunk_neighborhood(
                    p_chunk, 
                    ptr_array_of__chunk__neighbors,
                    local__x, local__y-1, local__z);
            if (p_tile && is_tile_cover__a_wall(
                        get_tile_cover_kind_from__tile(p_tile))) {
                p_entry->is_wall_adjacent__south = true;
                p_entry->quantity_of__adjacent_walls++;
            }
        }
    }
}

static inline
void invalidate_slope_map_entry(
        Slope_Map_Entry *p_slope_map_entry) {
    if (p_slope_map_entry->final_slope_map__value
            == SLOPE_MAP__PROSPECT_SLOPE) {
        p_slope_map_entry->final_slope_map__value =
            SLOPE_MAP__EXCLUDED_SLOPE;
    }
}

static inline
void invalidate_slope_map_entry__at(
        Slope_Map slope_map,
        u8 local__x,
        u8 local__y) {
    if (local__x >= CHUNK__WIDTH)
        return;
    if (local__y >= CHUNK__HEIGHT)
        return;
    Slope_Map_Entry *p_slope_map_entry =
        get_p_slope_map_entry__at(
                slope_map, 
                local__x, 
                local__y);
    if (p_slope_map_entry->final_slope_map__value
            == SLOPE_MAP__PROSPECT_SLOPE) {
        p_slope_map_entry->final_slope_map__value =
            SLOPE_MAP__EXCLUDED_SLOPE;
    }
}

void invalidate_adjacent_slope_map_entries(
        Slope_Map slope_map,
        u8 local__x,
        u8 local__y) {
    invalidate_slope_map_entry__at(slope_map, local__x+1, local__y);
    invalidate_slope_map_entry__at(slope_map, local__x-1, local__y);
    invalidate_slope_map_entry__at(slope_map, local__x, local__y+1);
    invalidate_slope_map_entry__at(slope_map, local__x, local__y-1);
}

void resolve_slope_map__niche_slopes(Slope_Map slope_map) {
    for (u8 local__y = 0; local__y < CHUNK__HEIGHT; local__y++) {
        for (u8 local__x = 0; local__x < CHUNK__WIDTH; local__x++) {
            Slope_Map_Entry *p_entry = 
                get_p_slope_map_entry__at(slope_map, local__x, local__y);
            if (p_entry->final_slope_map__value
                    != SLOPE_MAP__PROSPECT_SLOPE) {
                continue;
            }
            if (p_entry->quantity_of__adjacent_walls == 2) {
                if (p_entry->is_wall_adjacent__east
                        && p_entry->is_wall_adjacent__west) {
                    p_entry->final_slope_map__value =
                        SLOPE_MAP__EXCLUDED_SLOPE;
                    continue;
                }
                if (p_entry->is_wall_adjacent__north
                        && p_entry->is_wall_adjacent__south) {
                    p_entry->final_slope_map__value =
                        SLOPE_MAP__EXCLUDED_SLOPE;
                    continue;
                }
            }
            if (p_entry->quantity_of__adjacent_walls >= 3) {
                invalidate_adjacent_slope_map_entries(
                        slope_map,
                        local__x,
                        local__y);
                continue;
            }
        }
    }
}

void resolve_slope_map__slope_adjacency(Slope_Map slope_map) {
    for (u8 local__y = 0; local__y < CHUNK__HEIGHT; local__y++) {
        for (u8 local__x = 0; local__x < CHUNK__WIDTH; local__x++) {
            Slope_Map_Entry *p_entry = 
                get_p_slope_map_entry__at(slope_map, local__x, local__y);
            if (p_entry->final_slope_map__value
                    != SLOPE_MAP__PROSPECT_SLOPE) {
                continue;
            }

            Slope_Map_Entry *p_entry__other =
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x + 1, 
                        local__y);
            if (p_entry__other
                    && p_entry__other->quantity_of__adjacent_walls
                    && p_entry__other->final_slope_map__value
                    == SLOPE_MAP__PROSPECT_SLOPE) {
                p_entry->is_stair_adjacent__east = true;
            }
            p_entry__other =
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x - 1, 
                        local__y);
            if (p_entry__other
                    && p_entry__other->quantity_of__adjacent_walls
                    && p_entry__other->final_slope_map__value
                    == SLOPE_MAP__PROSPECT_SLOPE) {
                p_entry->is_stair_adjacent__west = true;
            }
            p_entry__other =
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x, 
                        local__y + 1);
            if (p_entry__other
                    && p_entry__other->quantity_of__adjacent_walls
                    && p_entry__other->final_slope_map__value
                    == SLOPE_MAP__PROSPECT_SLOPE) {
                p_entry->is_stair_adjacent__north = true;
            }
            p_entry__other =
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x, 
                        local__y - 1);
            if (p_entry__other
                    && p_entry__other->quantity_of__adjacent_walls
                    && p_entry__other->final_slope_map__value
                    == SLOPE_MAP__PROSPECT_SLOPE) {
                p_entry->is_stair_adjacent__south = true;
            }

            p_entry__other =
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x + 1, 
                        local__y + 1);
            if (p_entry__other 
                    && p_entry__other->final_slope_map__value
                    == SLOPE_MAP__WALL) {
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x + 1, 
                        local__y)->is_stair_adjacent__west = true;
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x, 
                        local__y+1)->is_stair_adjacent__south = true;
                p_entry->is_stair_adjacent__north = true;
                p_entry->is_stair_adjacent__east = true;
            }
            p_entry__other =
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x - 1, 
                        local__y + 1);
            if (p_entry__other 
                    && p_entry__other->final_slope_map__value
                    == SLOPE_MAP__WALL) {
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x - 1, 
                        local__y)->is_stair_adjacent__east = true;
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x, 
                        local__y + 1)->is_stair_adjacent__south = true;
                p_entry->is_stair_adjacent__north = true;
                p_entry->is_stair_adjacent__west = true;
            }
            p_entry__other =
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x + 1, 
                        local__y - 1);
            if (p_entry__other 
                    && p_entry__other->final_slope_map__value
                    == SLOPE_MAP__WALL) {
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x + 1, 
                        local__y)->is_stair_adjacent__west = true;
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x, 
                        local__y - 1)->is_stair_adjacent__north = true;
                p_entry->is_stair_adjacent__south = true;
                p_entry->is_stair_adjacent__east = true;
            }
            p_entry__other =
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x - 1, 
                        local__y - 1);
            if (p_entry__other 
                    && p_entry__other->final_slope_map__value
                    == SLOPE_MAP__WALL) {
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x - 1, 
                        local__y)->is_stair_adjacent__east = true;
                get_p_slope_map_entry__at(
                        slope_map, 
                        local__x, 
                        local__y - 1)->is_stair_adjacent__north = true;
                p_entry->is_stair_adjacent__south = true;
                p_entry->is_stair_adjacent__west = true;
            }
        }
    }
}

void render_slope_map_into__chunk(
        Chunk *p_chunk,
        Slope_Map slope_map,
        u8 local__z) {
    for (u8 local__y = 0; local__y < CHUNK__HEIGHT; local__y++) {
        for (u8 local__x = 0; local__x < CHUNK__WIDTH; local__x++) {
            Slope_Map_Entry *p_entry = 
                get_p_slope_map_entry__at(slope_map, local__x, local__y);
            if (p_entry->final_slope_map__value
                    != SLOPE_MAP__PROSPECT_SLOPE) {
                continue;
            }
            Tile *p_tile =
                get_p_tile_from__chunk(
                        p_chunk, (Local_Tile_Vector__3u8){local__x, local__y, local__z});
            Tile *p_tile__above =
                (local__z != CHUNK__DEPTH-1)
                ? get_p_tile_from__chunk(
                        p_chunk, (Local_Tile_Vector__3u8){local__x, local__y, 
                        (local__z + 1) & MASK(CHUNK__DEPTH__BIT_SHIFT)})
                : p_tile // TODO: need to go back after chunk is generated, and apply seam fixing.
                ;
            if (p_entry->quantity_of__adjacent_walls == 0) {
                // this is possibly a convex stair
                switch (p_entry->stair_adjacency_flags__u4) {
                    case 0b1001: //adj north west
                        p_tile->ag_tile_flags__u4 |=
                            AG_TILE_FLAG__IS_FLIPPED_Y;
                        p_tile__above->ag_tile_flags__u4 |=
                            AG_TILE_FLAG__IS_FLIPPED_Y;
                    case 0b1100: //adj north east
                        p_tile->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__Convex_Corner__North_East;
                        p_tile__above->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__Convex_Corner__North_East;
                        break;
                    case 0b0011: //adj south west
                        p_tile->ag_tile_flags__u4 |=
                            AG_TILE_FLAG__IS_FLIPPED_Y;
                        p_tile__above->ag_tile_flags__u4 |=
                            AG_TILE_FLAG__IS_FLIPPED_Y;
                    case 0b0110: //adj south east
                        p_tile->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__Convex_Corner__South_East;
                        p_tile__above->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__Convex_Corner__South_East;
                        break;
                    default:
                        break;
                }
                continue;
            }
            switch (p_entry->wall_adjacency_flags__u4) {
                case 0b1000: //adj north
                    if (p_entry->is_stair_adjacent__east) {
                        if (p_entry->is_stair_adjacent__west) {
                            p_tile->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__North__East_West;
                            p_tile__above->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__North__East_West;
                        } else {
                            p_tile->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__North__East;
                            p_tile__above->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__North__East;
                        }
                    } else if (p_entry->is_stair_adjacent__west) {
                        p_tile->ag_tile_flags__u4 |=
                            AG_TILE_FLAG__IS_FLIPPED_Y;
                        p_tile__above->ag_tile_flags__u4 |=
                            AG_TILE_FLAG__IS_FLIPPED_Y;
                        p_tile->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__North__East;
                        p_tile__above->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__North__East;
                    } else {
                        p_tile->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__North;
                        p_tile__above->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__North;
                    }
                    break;
                case 0b0100: //adj east
                    p_tile->ag_tile_flags__u4 |=
                        AG_TILE_FLAG__IS_FLIPPED_Y;
                    p_tile__above->ag_tile_flags__u4 |=
                        AG_TILE_FLAG__IS_FLIPPED_Y;
                case 0b0001: //adj west
                    if (p_entry->is_stair_adjacent__north) {
                        if (p_entry->is_stair_adjacent__south) {
                            p_tile->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__West__North_South;
                            p_tile__above->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__West__North_South;
                        } else {
                            p_tile->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__West__North;
                            p_tile__above->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__West__North;
                        }
                    } else if (p_entry->is_stair_adjacent__south) {
                        // TODO: missing from tileset
                        // p_tile->the_kind_of__tile_cover =
                        //     p_tile->the_kind_of__tile
                        //     + Tile_Cover_Kind__Stair__;
                        // p_tile__above->the_kind_of__tile_cover =
                        //     p_tile->the_kind_of__tile
                        //     + Tile_Cover_Kind__Stair__;
                    } else {
                        p_tile->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__West;
                        p_tile__above->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__West;
                    }
                    break;
                case 0b0010: //adj south
                    if (p_entry->is_stair_adjacent__east) {
                        if (p_entry->is_stair_adjacent__west) {
                            p_tile->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__South__East_West;
                            p_tile__above->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__South__East_West;
                        } else {
                            p_tile->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__South__East;
                            p_tile__above->the_kind_of__tile_cover =
                                p_tile->the_kind_of__tile
                                + Tile_Cover_Kind__Stair__South__East;
                        }
                    } else if (p_entry->is_stair_adjacent__west) {
                        p_tile->ag_tile_flags__u4 |=
                            AG_TILE_FLAG__IS_FLIPPED_Y;
                        p_tile__above->ag_tile_flags__u4 |=
                            AG_TILE_FLAG__IS_FLIPPED_Y;
                        p_tile->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__South__East;
                        p_tile__above->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__South__East;
                    } else {
                        p_tile->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__South;
                        p_tile__above->the_kind_of__tile_cover =
                            p_tile->the_kind_of__tile
                            + Tile_Cover_Kind__Stair__South;
                    }
                    break;
                case 0b1100: //adj north east
                    p_tile->ag_tile_flags__u4 |=
                        AG_TILE_FLAG__IS_FLIPPED_Y;
                    p_tile__above->ag_tile_flags__u4 |=
                        AG_TILE_FLAG__IS_FLIPPED_Y;
                case 0b1001: //adj north west
                    p_tile->the_kind_of__tile_cover =
                        p_tile->the_kind_of__tile
                        + Tile_Cover_Kind__Stair__Concave_Corner__North_West;
                    p_tile__above->the_kind_of__tile_cover =
                        p_tile->the_kind_of__tile
                        + Tile_Cover_Kind__Stair__Concave_Corner__North_West;
                    break;
                case 0b0110: //adj south east
                    p_tile->ag_tile_flags__u4 |=
                        AG_TILE_FLAG__IS_FLIPPED_Y;
                    p_tile__above->ag_tile_flags__u4 |=
                        AG_TILE_FLAG__IS_FLIPPED_Y;
                case 0b0011: //adj south west
                    p_tile->the_kind_of__tile_cover =
                        p_tile->the_kind_of__tile
                        + Tile_Cover_Kind__Stair__Concave_Corner__South_West;
                    p_tile__above->the_kind_of__tile_cover =
                        p_tile->the_kind_of__tile
                        + Tile_Cover_Kind__Stair__Concave_Corner__South_West;
                    break;
            }
        }
    }
}

typedef enum Chunk_Generation__State {
    Chunk_Generation__State__Default,
    Chunk_Generation__State__Terrain,
    Chunk_Generation__State__Awaiting_Neighbors,
    Chunk_Generation__State__Unknown,
} Chunk_Generation__State;

#define CHUNK_FLAG__IS_DONE_TERRAIN \
    CHUNK_FLAG__MODDABLE_0

static inline
bool is_global_space__finished_terrain(
        Global_Space *p_global_space) {
    return p_global_space
        && get_p_chunk_from__global_space(p_global_space)
        && (get_p_chunk_from__global_space(p_global_space)
                ->chunk_flags
                & CHUNK_FLAG__IS_DONE_TERRAIN)
        ;
}

static inline
void set_global_space_as__finished_terrain(
        Global_Space *p_global_space) {
    if (!p_global_space) return;
    if (!get_p_chunk_from__global_space(p_global_space))
        return;
    get_p_chunk_from__global_space(p_global_space)
        ->chunk_flags |= CHUNK_FLAG__IS_DONE_TERRAIN;
}

static u8 poll_global_space_neighbors(
        Game *p_game,
        Global_Space *p_global_space) {
    u8 neighbor_flags = 0;
    u8 neighbor_flag__shift = 0;
    Chunk_Vector__3i32 chunk_pos = p_global_space->chunk_vector__3i32;

    Global_Space_Manager *p_global_space_manager =
        get_p_global_space_manager_from__game(p_game);
    Global_Space *p_global_space__neighbor = 0;

    for (i8 y=-1;y<2;y++) {
        for (i8 x=-1;x<2;x++) {
            if (x == 0 && y == 0)
                continue;
            p_global_space__neighbor =
                get_p_global_space_from__global_space_manager(
                        p_global_space_manager, 
                        add_vectors__3i32(
                            chunk_pos,
                            get_vector__3i32(x, y, 0)));
            if (p_global_space__neighbor
                    && is_global_space__finished_terrain(
                        p_global_space__neighbor)) {
                neighbor_flags |= BIT(neighbor_flag__shift++);
            }
        }
    }
    
    return neighbor_flags;
}

static bool hold_global_space_neighbors(
        Game *p_game,
        Global_Space *p_global_space) {
    u8 neighbor_flags = 0;
    u8 neighbor_flag__shift = 0;
    Chunk_Vector__3i32 chunk_pos = p_global_space->chunk_vector__3i32;

    Global_Space_Manager *p_global_space_manager =
        get_p_global_space_manager_from__game(p_game);
    Global_Space *p_global_space__neighbor = 0;

    for (i8 y=-1;y<2;y++) {
        for (i8 x=-1;x<2;x++) {
            if (x == 0 && y == 0)
                continue;
            p_global_space__neighbor =
                get_p_global_space_from__global_space_manager(
                        p_global_space_manager, 
                        add_vectors__3i32(
                            chunk_pos,
                            get_vector__3i32(x, y, 0)));
            if (!p_global_space__neighbor) {
                u8 neighbor_unset_flag__shift = 0;
                for (y=-1;y<2;y++) {
                    for (x=-1;x<2;x++) {
                        p_global_space__neighbor =
                            get_p_global_space_from__global_space_manager(
                                    p_global_space_manager, 
                                    add_vectors__3i32(
                                        chunk_pos,
                                        get_vector__3i32(x, y, 0)));
                        if (p_global_space__neighbor
                                && (neighbor_flags 
                                    & BIT(neighbor_unset_flag__shift++))) {
                            drop_global_space(p_global_space__neighbor);
                        }
                    }
                }
                return false;
            }

            neighbor_flags |= BIT(neighbor_flag__shift++);
            hold_global_space(p_global_space__neighbor);
        }
    }
    
    return true;
}

static void drop_global_space_neighbors(
        Game *p_game,
        Global_Space *p_global_space) {
    Chunk_Vector__3i32 chunk_pos = p_global_space->chunk_vector__3i32;

    Global_Space_Manager *p_global_space_manager =
        get_p_global_space_manager_from__game(p_game);
    Global_Space *p_global_space__neighbor = 0;

    for (i8 y=-1;y<2;y++) {
        for (i8 x=-1;x<2;x++) {
            if (x == 0 && y == 0)
                continue;
            p_global_space__neighbor =
                get_p_global_space_from__global_space_manager(
                        p_global_space_manager, 
                        add_vectors__3i32(
                            chunk_pos,
                            get_vector__3i32(x, y, 0)));
            if (!p_global_space__neighbor) {
                continue;
            }

            drop_global_space(p_global_space__neighbor);
        }
    }
}

void m_process__chunk_generator__slope_resolver(
        Process *p_this_process,
        Game *p_game);

void m_process__chunk_generator__overworld(
        Process *p_this_process,
        Game *p_game) {
    Global_Space *p_global_space = p_this_process->p_process_data;
    Chunk *p_chunk = get_p_chunk_from__global_space(p_global_space);
    Chunk_Vector__3i32 chunk_pos = p_global_space->chunk_vector__3i32;

    switch (p_this_process->process_value_bytes__u8[0]) {
        default:
        case Chunk_Generation__State__Terrain:
            break;
        case Chunk_Generation__State__Awaiting_Neighbors:
            p_this_process->process_value_bytes__u8[1] =
                poll_global_space_neighbors(
                        p_game, 
                        p_global_space);

            if (p_this_process->process_value_bytes__u8[1]
                    != (u8)-1) {
                // never timeout, but check for awaiting deconstruction
                if (is_global_space__awaiting_deconstruction(
                            p_global_space)) {
                    release_global_space(
                            get_p_world_from__game(p_game), 
                            p_global_space);
                    debug_info("dropping %d,%d,%d",
                            chunk_pos.x__i32,
                            chunk_pos.y__i32,
                            chunk_pos.z__i32);
                    complete_process(p_this_process);
                }
                return;
            }

            hold_global_space_neighbors(
                    p_game, 
                    p_global_space);
            debug_info("go to slope%d,%d,%d",
                    chunk_pos.x__i32,
                    chunk_pos.y__i32,
                    chunk_pos.z__i32);
            p_this_process->m_process_run__handler =
                m_process__chunk_generator__slope_resolver;
            return;
    }

    Repeatable_Psuedo_Random *p_random = get_p_repeatable_psuedo_random_from__world(get_p_world_from__game(p_game));

    Tile_Vector__3i32 tile_vector_of__chunk =
        chunk_vector_3i32_to__tile_vector_3i32(chunk_pos);
    i32 tile_origin_x = tile_vector_of__chunk.x__i32;
    i32 tile_origin_y = tile_vector_of__chunk.y__i32;
    i32 tile_origin_z = tile_vector_of__chunk.z__i32;

    for (u32 local__y = 0; local__y < CHUNK__HEIGHT; ++local__y) {
        for (u32 local__x = 0; local__x < CHUNK__WIDTH; ++local__x) {
            i32 world__x = tile_origin_x + local__x;
            i32 world__y = tile_origin_y + local__y;

            i32F8 interp_height   = get_random_sample(p_random, world__x, world__y);
            i32F8 interp_moisture = get_random_sample(p_random, world__y, world__x); // flipped axes for moisture

            interp_height = flatten_height(interp_height);

            Biome_Type type_of__biome =
                classify_biome(
                        interp_height, 
                        interp_moisture);

            i32 z__height = i32F8_to__i32(interp_height);

            i32 z_chunk__height = z__height >> CHUNK__DEPTH__BIT_SHIFT;
            if (chunk_pos.z__i32 + 1 < z_chunk__height) {
                fill_chunk_with(
                        p_chunk, 
                        Tile_Kind__Stone, 
                        Tile_Cover_Kind__Wall__Stone);
                set_global_space_as__finished_terrain(p_global_space);
                complete_process(p_this_process);
                return;
            }
            if (chunk_pos.z__i32 - 1 > z_chunk__height) {
                fill_chunk_with(
                        p_chunk, 
                        Tile_Kind__None, 
                        Tile_Cover_Kind__None);
                set_global_space_as__finished_terrain(p_global_space);
                complete_process(p_this_process);
                return;
            }

            for (u32 local__z = 0; local__z < CHUNK__DEPTH; local__z++) {
                i32 global__z = local__z + tile_origin_z;
                Tile tile;
                memset(&tile, 0 , sizeof(Tile));
                if (global__z > z__height) {
                    if (global__z < 0) {
                        tile.the_kind_of__tile = Tile_Kind__Water;
                    } else {
                        tile.the_kind_of__tile = Tile_Kind__None;
                    }
                    tile.the_kind_of__tile_cover = Tile_Cover_Kind__None;
                }
                if (global__z <= z__height) {
                    switch (type_of__biome) {
                        default:
                            tile.the_kind_of__tile = Tile_Kind__None;
                            break;
                        case Biome__Ocean:
                            tile.the_kind_of__tile = Tile_Kind__Water;
                            break;
                        case Biome__Beach:
                        case Biome__Desert:
                            tile.the_kind_of__tile = Tile_Kind__Sand;
                            break;
                        case Biome__Arid:
                            tile.the_kind_of__tile = Tile_Kind__Dirt;
                            break;
                        case Biome__Plains:
                        case Biome__Forest:
                        case Biome__Rain_Forest:
                            tile.the_kind_of__tile = Tile_Kind__Grass;
                            break;
                        case Biome__Snow_Plains:
                        case Biome__Tundra:
                            tile.the_kind_of__tile = Tile_Kind__Grass;
                            // TODO: tilecover as snow
                            break;
                        case Biome__Desert_Peaks:
                            tile.the_kind_of__tile = Tile_Kind__Sandstone;
                            break;
                        case Biome__Mountain_Peaks:
                            tile.the_kind_of__tile = Tile_Kind__Stone;
                            break;
                        case Biome__Snow_Peaks:
                            tile.the_kind_of__tile = Tile_Kind__Stone;
                            // TODO: tilecover as snow
                            break;
                    }
                }
                if (global__z < z__height) {
                    if (global__z + 6 < z__height) {
                        tile.the_kind_of__tile = Tile_Kind__Stone;
                    } else if (global__z + 4 < z__height) {
                        switch (tile.the_kind_of__tile) {
                            case Tile_Kind__Sand:
                                tile.the_kind_of__tile = Tile_Kind__Sandstone;
                            case Tile_Kind__Sandstone:
                                break;
                            default:
                                tile.the_kind_of__tile = Tile_Kind__Stone;
                                break;
                        }
                    } else if (global__z < z__height) {
                        switch (tile.the_kind_of__tile) {
                            case Tile_Kind__Grass:
                                tile.the_kind_of__tile = Tile_Kind__Dirt;
                            default:
                                break;
                        }
                    }
                    if (global__z < z__height) {
                        switch (tile.the_kind_of__tile) {
                            case Tile_Kind__Water:
                            case Tile_Kind__None:
                                break;
                            default:
                                tile.the_kind_of__tile_cover =
                                    tile.the_kind_of__tile
                                    + Tile_Cover_Kind__Wall
                                    ;
                                break;
                        }
                    }
                }
                set_tile_of__chunk(
                        p_chunk, 
                        (Local_Tile_Vector__3u8){
                            local__x, CHUNK__HEIGHT - local__y - 1, local__z}, 
                            &tile);
            }
        }
    }

    debug_info("awaiting neighbor %d,%d,%d",
            chunk_pos.x__i32,
            chunk_pos.y__i32,
            chunk_pos.z__i32);
    set_global_space_as__finished_terrain(p_global_space);
    p_this_process->process_value_bytes__u8[0] =
        Chunk_Generation__State__Awaiting_Neighbors;
}

void m_process__chunk_generator__slope_resolver(
        Process *p_this_process,
        Game *p_game) {
    Global_Space_Manager *p_global_space_manager = 
        get_p_global_space_manager_from__game(p_game);
    Global_Space *p_global_space = p_this_process->p_process_data;
    Chunk *p_chunk = get_p_chunk_from__global_space(p_global_space);
    Chunk_Vector__3i32 chunk_pos = p_global_space->chunk_vector__3i32;
    Tile_Vector__3i32 tile_vector_of__chunk =
        chunk_vector_3i32_to__tile_vector_3i32(chunk_pos);
    i32 tile_origin_z = tile_vector_of__chunk.z__i32;

    Chunk *ptr_array_of__chunk__neighbors[8];

    for (i8 y=-1,index=0;y<2;y++) {
        for (i8 x=-1;x<2;x++) {
            if (x == 0 && y == 0) continue;
            ptr_array_of__chunk__neighbors[index++] =
                get_p_chunk_from__global_space(
                        get_p_global_space_from__global_space_manager(
                            p_global_space_manager, 
                            add_vectors__3i32(
                                p_global_space->chunk_vector__3i32,
                                get_vector__3i32(x,y,0))));
        }
    }

    Slope_Map slope_map;
    for (u32 local__z = 0; local__z < CHUNK__DEPTH; local__z++) {
        i32 global__z = local__z + tile_origin_z;
        memset(slope_map, 0, sizeof(Slope_Map));
        generate_slope_map(
                get_p_global_space_manager_from__game(p_game),
                p_global_space,
                ptr_array_of__chunk__neighbors,
                slope_map, 
                local__z);
        resolve_slope_map__niche_slopes(slope_map);
        resolve_slope_map__slope_adjacency(
                slope_map);
        render_slope_map_into__chunk(
                p_chunk, 
                slope_map, 
                local__z);
    }

    debug_info("done slope: %d,%d,%d",
            chunk_pos.x__i32,
            chunk_pos.y__i32,
            chunk_pos.z__i32);
    drop_global_space_neighbors(
            p_game, 
            p_global_space);
    complete_process(p_this_process);
}
