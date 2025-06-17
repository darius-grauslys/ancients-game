#include "world/implemented/f_tile_render_kernel.h"
#include "defines.h"
#include "platform_defines.h"
#include "types/implemented/tile.h"
#include "types/implemented/tile_cover_kind.h"
#include "types/implemented/tile_kind.h"
#include "world/chunk.h"
#include "world/global_space.h"
#include "world/local_space.h"
#include "world/tile.h"

#define TILE_SHEET_TILE_WIDTH 32

Index__u16 get_tile_sheet_index_offset_for__cover_from__wall_adjacency(
        Tile_Wall_Adjacency_Code__u16 wall_adjacency) {
    return 
        TILE_SHEET_TILE_WIDTH
        * (4
        * (1 + (wall_adjacency & TILE_RENDER__WALL_ADJACENCY__COVER_MASK))
        - 1)
        ;
}

static inline Index__u16 
get_tile_sheet_index_offset_for__sprite_cover_from__wall_adjacency(
        Tile_Wall_Adjacency_Code__u16 wall_adjacency) {
    return 
        TILE_SHEET_TILE_WIDTH
        * (wall_adjacency & TILE_RENDER__WALL_ADJACENCY__SPRITE_COVER_MASK);
}

static inline 
void get_tile_cover_texture_sheet_index(
        Tile *p_tile,
        Tile_Render_Result *p_render_result) {
    p_render_result->tile_index__cover = 0;
    switch(p_tile->the_kind_of__tile_cover) {
        default:
            p_render_result->tile_index__cover = 
                p_tile->the_kind_of__tile_cover;
			break;
        case Tile_Cover_Kind__Door__Vertical__Open__Dirt:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Dirt:
            p_render_result->tile_index__cover +=
                Tile_Kind__Dirt;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Sand:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Sand:
            p_render_result->tile_index__cover +=
                Tile_Kind__Sand;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Wood:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Wood:
            p_render_result->tile_index__cover +=
                Tile_Kind__Wood;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Stone:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Stone:
            p_render_result->tile_index__cover +=
                Tile_Kind__Stone;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Stone_Brick:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Stone_Brick:
            p_render_result->tile_index__cover +=
                Tile_Kind__Stone_Brick;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Iron:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Iron:
            p_render_result->tile_index__cover +=
                Tile_Kind__Iron;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Gold:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Gold:
            p_render_result->tile_index__cover +=
                Tile_Kind__Gold;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Diamond:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Diamond:
            p_render_result->tile_index__cover +=
                Tile_Kind__Diamond;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Amethyst:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Amethyst:
            p_render_result->tile_index__cover +=
                Tile_Kind__Amethyst;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Sandstone:
            p_render_result->tile_index__cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Sandstone:
            p_render_result->tile_index__cover +=
                Tile_Kind__Sandstone;
vertical__door:
            p_render_result->tile_index__cover +=
               Tile_Cover_Kind__Door__Vertical
                + 128;
            break;
        case Tile_Cover_Kind__Door__Horizontal__Open__Dirt:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Dirt:
            p_render_result->tile_index__cover +=
                Tile_Kind__Dirt;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Sand:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Sand:
            p_render_result->tile_index__cover +=
                Tile_Kind__Sand;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Wood:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Wood:
            p_render_result->tile_index__cover +=
                Tile_Kind__Wood;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Stone:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Stone:
            p_render_result->tile_index__cover +=
                Tile_Kind__Stone;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Stone_Brick:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Stone_Brick:
            p_render_result->tile_index__cover +=
                Tile_Kind__Stone_Brick;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Iron:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Iron:
            p_render_result->tile_index__cover +=
                Tile_Kind__Iron;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Gold:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Gold:
            p_render_result->tile_index__cover +=
                Tile_Kind__Gold;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Diamond:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Diamond:
            p_render_result->tile_index__cover +=
                Tile_Kind__Diamond;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Amethyst:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Amethyst:
            p_render_result->tile_index__cover +=
                Tile_Kind__Amethyst;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Sandstone:
            p_render_result->tile_index__cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Sandstone:
            p_render_result->tile_index__cover +=
                Tile_Kind__Sandstone;
horizontal__door:
            p_render_result->tile_index__cover +=
                Tile_Cover_Kind__Door__Horizontal
                + 32;
            break;
        case Tile_Cover_Kind__Wall__Dirt:
            p_render_result->tile_index__cover =
                Tile_Kind__Dirt;
            goto wall;
        case Tile_Cover_Kind__Wall__Sand:
            p_render_result->tile_index__cover =
                Tile_Kind__Sand;
            goto wall;
        case Tile_Cover_Kind__Wall__Wood:
            p_render_result->tile_index__cover =
                Tile_Kind__Wood;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone:
            p_render_result->tile_index__cover =
                Tile_Kind__Stone;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone_Brick:
            p_render_result->tile_index__cover =
                Tile_Kind__Stone_Brick;
            goto wall;
        case Tile_Cover_Kind__Wall__Iron:
            p_render_result->tile_index__cover =
                Tile_Kind__Iron;
            goto wall;
        case Tile_Cover_Kind__Wall__Gold:
            p_render_result->tile_index__cover =
                Tile_Kind__Gold;
            goto wall;
        case Tile_Cover_Kind__Wall__Diamond:
            p_render_result->tile_index__cover =
                Tile_Kind__Diamond;
            goto wall;
        case Tile_Cover_Kind__Wall__Amethyst:
            p_render_result->tile_index__cover =
                Tile_Kind__Amethyst;
            goto wall;
        case Tile_Cover_Kind__Wall__Sandstone:
            p_render_result->tile_index__cover =
                Tile_Kind__Sandstone;
wall:
            p_render_result->tile_index__cover +=
                Tile_Cover_Kind__Wall
                + get_tile_sheet_index_offset_for__cover_from__wall_adjacency(
                        p_render_result->wall_adjacency);
            break;
        case Tile_Cover_Kind__Crop_Corn_A:
        case Tile_Cover_Kind__Crop_Onion_A:
        case Tile_Cover_Kind__Crop_Tomato_A:
        case Tile_Cover_Kind__Crop_Pumpkin_A:
        case Tile_Cover_Kind__Crop_Watermelon_A:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__A;
            break;
        case Tile_Cover_Kind__Crop_Corn_B:
        case Tile_Cover_Kind__Crop_Onion_B:
        case Tile_Cover_Kind__Crop_Tomato_B:
        case Tile_Cover_Kind__Crop_Pumpkin_B:
        case Tile_Cover_Kind__Crop_Watermelon_B:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__B;
            break;
        case Tile_Cover_Kind__Crop_Corn_C:
        case Tile_Cover_Kind__Crop_Onion_C:
        case Tile_Cover_Kind__Crop_Tomato_C:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__C;
            break;
        case Tile_Cover_Kind__Crop_Pumpkin_C:
        case Tile_Cover_Kind__Crop_Watermelon_C:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__D;
            break;
        case Tile_Cover_Kind__Crop_Wheat_A:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__E;
            break;
        case Tile_Cover_Kind__Crop_Wheat_B:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__F;
            break;
        case Tile_Cover_Kind__Crop_Wheat_C:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Crop__G;
            break;
        case Tile_Cover_Kind__Tree__Oak:
        case Tile_Cover_Kind__Tree__Pine:
            p_render_result->tile_index__cover =
                Tile_Cover_Kind__Tree__Trunk;
            break;
    }
}

static void inline get_tile_sprite_cover_texture_sheet_index(
        Tile *p_tile,
        Tile_Render_Result *p_render_result) {
    p_render_result->tile_index__sprite_cover = 0;
    switch(p_tile->the_kind_of__tile_cover) {
        default:
            break;
        case Tile_Cover_Kind__Table__Bottom__Left:
        case Tile_Cover_Kind__Table__Bottom__Middle:
        case Tile_Cover_Kind__Table__Bottom__Right:
            p_render_result->tile_index__sprite_cover =
                get_tile_cover_kind_from__tile(p_tile)
                -32;
            break;
        case Tile_Cover_Kind__Door__Vertical__Open__Dirt:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Dirt:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Dirt;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Sand:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Sand:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Sand;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Wood:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Wood:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Wood;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Stone:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Stone:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Stone;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Stone_Brick:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Stone_Brick:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Stone_Brick;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Iron:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Iron:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Iron;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Gold:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Gold:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Gold;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Diamond:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Diamond:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Diamond;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Amethyst:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Amethyst:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Amethyst;
            goto vertical__door;
        case Tile_Cover_Kind__Door__Vertical__Open__Sandstone:
            p_render_result->tile_index__sprite_cover += 32;
        case Tile_Cover_Kind__Door__Vertical__Sandstone:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Sandstone;
vertical__door:
            p_render_result->tile_index__sprite_cover +=
                Tile_Cover_Kind__Door__Vertical
                + 128;
            break;
        case Tile_Cover_Kind__Door__Horizontal__Open__Dirt:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Dirt:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Dirt;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Sand:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Sand:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Sand;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Wood:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Wood:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Wood;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Stone:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Stone:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Stone;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Stone_Brick:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Stone_Brick:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Stone_Brick;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Iron:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Iron:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Iron;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Gold:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Gold:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Gold;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Diamond:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Diamond:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Diamond;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Amethyst:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Amethyst:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Amethyst;
            goto horizontal__door;
        case Tile_Cover_Kind__Door__Horizontal__Open__Sandstone:
            p_render_result->tile_index__sprite_cover += 64;
        case Tile_Cover_Kind__Door__Horizontal__Sandstone:
            p_render_result->tile_index__sprite_cover +=
                Tile_Kind__Sandstone;
horizontal__door:
            p_render_result->tile_index__sprite_cover +=
                Tile_Cover_Kind__Door__Horizontal;
            break;
        case Tile_Cover_Kind__Wall__Dirt:
            p_render_result->tile_index__sprite_cover =
                Tile_Kind__Dirt;
            goto wall;
        case Tile_Cover_Kind__Wall__Sand:
            p_render_result->tile_index__sprite_cover =
                Tile_Kind__Sand;
            goto wall;
        case Tile_Cover_Kind__Wall__Wood:
            p_render_result->tile_index__sprite_cover =
                Tile_Kind__Wood;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone:
            p_render_result->tile_index__sprite_cover =
                Tile_Kind__Stone;
            goto wall;
        case Tile_Cover_Kind__Wall__Stone_Brick:
            p_render_result->tile_index__sprite_cover =
                Tile_Kind__Stone_Brick;
            goto wall;
        case Tile_Cover_Kind__Wall__Iron:
            p_render_result->tile_index__sprite_cover =
                Tile_Kind__Iron;
            goto wall;
        case Tile_Cover_Kind__Wall__Gold:
            p_render_result->tile_index__sprite_cover =
                Tile_Kind__Gold;
            goto wall;
        case Tile_Cover_Kind__Wall__Diamond:
            p_render_result->tile_index__sprite_cover =
                Tile_Kind__Diamond;
            goto wall;
        case Tile_Cover_Kind__Wall__Amethyst:
            p_render_result->tile_index__sprite_cover =
                Tile_Kind__Amethyst;
            goto wall;
        case Tile_Cover_Kind__Wall__Sandstone:
            p_render_result->tile_index__sprite_cover =
                Tile_Kind__Sandstone;
wall:
            p_render_result->tile_index__sprite_cover +=
                Tile_Cover_Kind__Wall
                + get_tile_sheet_index_offset_for__sprite_cover_from__wall_adjacency(
                    p_render_result->wall_adjacency);
            break;
            // TODO: magic numbers below here.
        case Tile_Cover_Kind__Cactus__Tall__Top:
        case Tile_Cover_Kind__Ore__Large__Stone_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Gold_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Iron_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Diamond_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Amethyst_1__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Stone_2__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Gold_2__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Iron_2__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Diamond_2__Top_Right:
        case Tile_Cover_Kind__Ore__Large__Amethyst_2__Top_Right:
            p_render_result->tile_index__sprite_cover =
                p_tile->the_kind_of__tile_cover
                - 32;
            break;
        case Tile_Cover_Kind__Tree__Oak:
            p_render_result->tile_index__sprite_cover =
                Tile_Cover_Kind__Stump
                + 1
                - 32
                ;
            p_render_result->tile_index__sprite_cover__extra =
                Tile_Cover_Kind__Stump
                + 1
                - 64
                ;
            break;
        case Tile_Cover_Kind__Tree__Pine:
            p_render_result->tile_index__sprite_cover =
                Tile_Cover_Kind__Stump
                + 2
                - 32
                ;
            p_render_result->tile_index__sprite_cover__extra =
                Tile_Cover_Kind__Stump
                + 2
                - 64
                ;
            break;
    }
}

static inline 
void get_tile_texture_sheet_index(
        Tile *p_tile,
        Tile_Render_Result *p_render_result) {
    switch (get_tile_kind_from__tile(p_tile)) {
        default:
            p_render_result->tile_index__ground =
                (uint32_t)get_tile_kind_from__tile(p_tile);
            return;
        case Tile_Kind__Wood:
        case Tile_Kind__Stone_Brick:
        case Tile_Kind__Gold:
        case Tile_Kind__Iron:
        case Tile_Kind__Diamond:
        case Tile_Kind__Amethyst:
        case Tile_Kind__Sandstone:
        case Tile_Kind__Stone:
        case Tile_Kind__Dirt:
        case Tile_Kind__Sand:
        case Tile_Kind__Grass:
            goto tile_structure;
        //TODO: leaves and snow
        // case Tile_Kind__Snow:
        //     return TILE_SHEET_INDEX__DIRT;
    }
tile_structure:
    ;
    uint32_t index = get_tile_kind_from__tile(p_tile);
    //TODO: look into why we have to add 1.
    index += 1;
    p_render_result->tile_index__ground = index;
}

static inline 
Tile *get_p_tile__from_chunk_and__wall_adjacency_of__that_tile(
        Local_Space *p_local_space,
        Local_Tile_Vector__3u8 local_tile_vector__3u8,
        Tile_Wall_Adjacency_Code__u16 *p_OUT_wall_adjacency) {
    Index__u8 x__local = local_tile_vector__3u8.x__u8;
    Index__u8 y__local = local_tile_vector__3u8.y__u8;
    Index__u8 z__local = local_tile_vector__3u8.z__u8;
    Tile *p_tile =
        get_p_tile_from__chunk(
                get_p_chunk_from__local_space(
                    p_local_space),
                local_tile_vector__3u8);

    Tile *p_north = 0, *p_east = 0, *p_south = 0, *p_west = 0;

    p_north =
        (y__local == CHUNK__HEIGHT - 1)
        ? (is_local_space__active(
                    p_local_space
                    ->p_local_space__north)
                ? get_p_tile_from__chunk_using__u8(
                    get_p_chunk_from__local_space(
                        p_local_space->p_local_space__north),
                    x__local, 
                    0,
                    z__local)
                : 0)
        : get_p_tile_from__chunk_using__u8(
                get_p_chunk_from__local_space(
                    p_local_space),
                x__local, 
                y__local + 1,
                z__local)
        ;
    p_south =
        (y__local == 0)
        ? (is_local_space__active(
                    p_local_space
                    ->p_local_space__south)
            ? get_p_tile_from__chunk_using__u8(
                    get_p_chunk_from__local_space(
                        p_local_space->p_local_space__south),
                    x__local, 
                    CHUNK__HEIGHT - 1,
                    z__local)
            : 0)
        : get_p_tile_from__chunk_using__u8(
                get_p_chunk_from__local_space(
                    p_local_space),
                x__local, 
                y__local - 1,
                z__local)
        ;
    p_west =
        (x__local == 0)
        ? (is_local_space__active(
                    p_local_space
                    ->p_local_space__west)
            ? get_p_tile_from__chunk_using__u8(
                    get_p_chunk_from__local_space(
                        p_local_space
                        ->p_local_space__west),
                    CHUNK__WIDTH - 1, 
                    y__local,
                    z__local)
            : 0)
        : get_p_tile_from__chunk_using__u8(
                get_p_chunk_from__local_space(
                    p_local_space),
                x__local - 1, 
                y__local,
                z__local)
        ;
    p_east =
        (x__local == CHUNK__WIDTH - 1)
        ? (is_local_space__active(
                    p_local_space
                    ->p_local_space__west)
            ? get_p_tile_from__chunk_using__u8(
                    get_p_chunk_from__local_space(
                        p_local_space
                        ->p_local_space__west),
                    0, 
                    y__local,
                    z__local)
            : 0)
        : get_p_tile_from__chunk_using__u8(
                get_p_chunk_from__local_space(
                    p_local_space),
                x__local + 1, 
                y__local,
                z__local)
        ;

    Tile_Wall_Adjacency_Code__u16 wall_adjacency = 0;
    if (p_north && is_tile_cover__a_wall(get_tile_cover_kind_from__tile(p_north))) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__NORTH;
    }
    if (p_east && is_tile_cover__a_wall(get_tile_cover_kind_from__tile(p_east))) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__EAST;
    }
    if (p_south && is_tile_cover__a_wall(get_tile_cover_kind_from__tile(p_south))) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__SOUTH;
    }
    if (p_west && is_tile_cover__a_wall(get_tile_cover_kind_from__tile(p_west))) {
        wall_adjacency +=
            TILE_RENDER__WALL_ADJACENCY__WEST;
    }

    *p_OUT_wall_adjacency = wall_adjacency;

    return p_tile;
}

// TODO: prim wrap
// TODO: move this to nds
void get_tile_render_result(
        Local_Space *p_local_space,
        Local_Tile_Vector__3u8 local_tile_vector__3u8,
        Tile_Render_Result *p_OUT_tile_render_result) {
    memset(p_OUT_tile_render_result,
            0,
            sizeof(Tile_Render_Result));

    Global_Space *p_global_space =
        get_p_global_space_from__local_space(p_local_space);
    if (!p_global_space
            || !is_global_space__active(p_global_space))
        return;
    Chunk *p_chunk =
        get_p_chunk_from__global_space(p_global_space);
    if (!p_chunk)
        return;

    Tile *p_tile = 
        get_p_tile__from_chunk_and__wall_adjacency_of__that_tile(
                p_local_space, 
                local_tile_vector__3u8, 
                &p_OUT_tile_render_result
                ->wall_adjacency);

    get_tile_texture_sheet_index(
            p_tile, 
            p_OUT_tile_render_result);

    get_tile_cover_texture_sheet_index(
            p_tile, 
            p_OUT_tile_render_result);

    p_OUT_tile_render_result
        ->tile_index__sprite_cover__extra = 
        Tile_Cover_Kind__None;
    get_tile_sprite_cover_texture_sheet_index(
            p_tile, 
            p_OUT_tile_render_result);

    p_OUT_tile_render_result
        ->tile_index__cover &= ((1 << 10)-1);
    p_OUT_tile_render_result
        ->tile_index__ground &= ((1 << 10)-1);
    p_OUT_tile_render_result
        ->tile_index__sprite_cover &= ((1 << 10)-1);

    if (does_tile__have_a_wall(p_tile)) {
        p_OUT_tile_render_result->tile_index__cover |= 
            does_wall_adjacency_require__vflip(
                    p_OUT_tile_render_result
                    ->wall_adjacency)
            << 10;
        p_OUT_tile_render_result
            ->tile_index__sprite_cover |= 
            does_wall_adjacency_require__vflip(
                    p_OUT_tile_render_result
                    ->wall_adjacency)
            << 10;
    }
}

void f_tile_render_kernel(
        Local_Space *p_local_space,
        Tile_Render_Kernel_Result *p_tile_kernel_render_results,
        Quantity__u32 quantity_of__tile_kernel_render_results,
        u8 x__local,
        u8 y__local,
        u8 z__local) {
    if (!is_global_space__active(
                get_p_global_space_from__local_space(p_local_space))) {
        return;
    }

    // TODO: remove Tile_Render_Result entirely
    Tile_Render_Result trr;
    get_tile_render_result(
            p_local_space, 
            get_vector__3u8(
                x__local,
                y__local,
                z__local), 
            &trr);

    if (trr.tile_index__ground) {
        p_tile_kernel_render_results[0].index_of__texture =
            (trr.tile_index__ground  & MASK(10)) - 1;
        p_tile_kernel_render_results[0].is_flipped__y =
            BIT(10) & trr.tile_index__ground;
    } else {
        p_tile_kernel_render_results[0].index_of__texture = 0;
    }
    if (trr.tile_index__cover) {
        p_tile_kernel_render_results[1].index_of__texture =
            (trr.tile_index__cover & MASK(10)) - 1;
        p_tile_kernel_render_results[1].is_flipped__y =
            BIT(10) & trr.tile_index__cover;
    } else {
        p_tile_kernel_render_results[1].index_of__texture = 0;
    }
    if (trr.tile_index__sprite_cover) {
        p_tile_kernel_render_results[2].index_of__texture =
            (trr.tile_index__sprite_cover & MASK(10)) - 1;
        p_tile_kernel_render_results[2].is_flipped__y =
            BIT(10) & trr.tile_index__sprite_cover;
    } else {
        p_tile_kernel_render_results[2].index_of__texture = 0;
    }
    p_tile_kernel_render_results[0].is_flipped__x = 0;
    p_tile_kernel_render_results[1].is_flipped__x = 0;
    p_tile_kernel_render_results[2].is_flipped__x = 0;
}
