#include "world/implemented/ag__chunk_generator_overworld.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "numerics.h"
#include "platform_defaults.h"
#include "types/implemented/tile_cover_kind.h"
#include "types/implemented/tile_kind.h"
#include "vectors.h"
#include "world/global_space.h"
#include "world/chunk_vectors.h"
#include "world/chunk.h"
#include "random.h"
#include "world/world.h"

#define BIOME_SHIFT 3
#define BIOME_MASK  0x3

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
    Biome_Ocean = 0,
    Biome_Plains = 1,
    Biome_Hills = 2,
    Biome_Mountains = 3
} Biome_Type;

// Utilities
i32F4 get_random_height_sample(
        Repeatable_Psuedo_Random *p_repeatable_psuedo_random,
        i32 x, i32 y, Biome_Type biome) {
    i32 base;
    switch (biome) {
        case Biome_Ocean: base = -3; break;
        case Biome_Plains: base = 2; break;
        case Biome_Hills: base = 12; break;
        case Biome_Mountains: base = 28; break;
        default: base = 0; break;
    }

    i32 noise = get_pseudo_random_i32_with__xy__intrusively(
            p_repeatable_psuedo_random, x, y);
    i32F4 variation = (noise & MASK(6)) - BIT(5);

    i32F4 base_fp = i32_to__i32F4(base);
    return base_fp + variation;
}

// Fills chunk entirely with given tile kind
void fill_chunk_with(
        Chunk *p_chunk,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover) {
    for (i32 dx = 0; dx < CHUNK__WIDTH; ++dx) {
        for (i32 dy = 0; dy < CHUNK__HEIGHT; ++dy) {
            for (i32 dz = 0; dz < CHUNK__DEPTH; ++dz) {
                Local_Tile_Vector__3u8 tile_vec = { dx, dy, dz };
                Tile *p_tile = get_p_tile_from__chunk(p_chunk, tile_vec);
                p_tile->the_kind_of__tile = the_kind_of__tile;
                p_tile->the_kind_of__tile_cover = the_kind_of__tile_cover;
            }
        }
    }
}

void f_chunk_generator__overworld(Game *p_game, Global_Space *p_global_space) {
    Repeatable_Psuedo_Random *p_repeatable_psuedo_random =
        get_p_repeatable_psuedo_random_from__world(
                get_p_world_from__game(p_game));
    Chunk *p_chunk = get_p_chunk_from__global_space(p_global_space);
    Chunk_Vector__3i32 chunk_vec = p_global_space->chunk_vector__3i32;
    Tile_Vector__3i32 base_tile_vec = chunk_vector_3i32_to__tile_vector_3i32(chunk_vec);

    i32 chunk_x = chunk_vec.x__i32;
    i32 chunk_y = chunk_vec.y__i32;
    i32 chunk_z = chunk_vec.z__i32;

    i32 base_x = base_tile_vec.x__i32;
    i32 base_y = base_tile_vec.y__i32;
    i32 base_z = base_tile_vec.z__i32;

    // Determine biome
    i32 biome_noise = get_pseudo_random_i32_with__xy__intrusively(p_repeatable_psuedo_random, 
            chunk_x >> BIOME_SHIFT, chunk_y >> BIOME_SHIFT);
    Biome_Type biome = (Biome_Type)(biome_noise & BIOME_MASK);

    // Sample height map at 9 key points
    i32 center_x = base_x + CHUNK__WIDTH / 2;
    i32 center_y = base_y + CHUNK__HEIGHT / 2;

    i32F4 h00 = get_random_height_sample(
            p_repeatable_psuedo_random, base_x, base_y, biome);
    i32F4 h10 = get_random_height_sample(
            p_repeatable_psuedo_random, base_x + CHUNK__WIDTH, base_y, biome);
    i32F4 h01 = get_random_height_sample(
            p_repeatable_psuedo_random, base_x, base_y + CHUNK__HEIGHT, biome);
    i32F4 h11 = get_random_height_sample(
            p_repeatable_psuedo_random, base_x + CHUNK__WIDTH, base_y + CHUNK__HEIGHT, biome);
    i32F4 h_center = get_random_height_sample(
            p_repeatable_psuedo_random, center_x, center_y, biome);

    // Terrain height at center (used for early exit)
    i32F4 h_mid = h_center;
    i32 terrain_height_tile = i32F4_to__i32(h_mid);
    Tile_Vector__3i32 center_tile_vec = { center_x, center_y, terrain_height_tile };
    Chunk_Vector__3i32 terrain_chunk_vec = tile_vector_3i32_to__chunk_vector_3i32(center_tile_vec);

    if (chunk_z < terrain_chunk_vec.z__i32) {
        fill_chunk_with(
                p_chunk,
                Tile_Kind__Stone,
                Tile_Cover_Kind__Wall__Stone);
        return;
    }

    if (chunk_z > terrain_chunk_vec.z__i32) {
        fill_chunk_with(
                p_chunk,
                Tile_Kind__None,
                Tile_Cover_Kind__None);
        return;
    }

    // Within terrain surface zone
    for (i32 dx = 0; dx < CHUNK__WIDTH; ++dx) {
        for (i32 dy = 0; dy < CHUNK__HEIGHT; ++dy) {
            i32 world_x = base_x + dx;
            i32 world_y = base_y + dy;

            // Bilinear interpolation (simplified)
            i32F4 tx = i32_to__i32F4(dx) / CHUNK__WIDTH;
            i32F4 ty = i32_to__i32F4(dy) / CHUNK__HEIGHT;

            i32F4 h0 = h00 + i32F4_to__i32((h10-h00) * tx);
            i32F4 h1 = h01 + i32F4_to__i32((h11 - h01) * tx);
            i32F4 height_fp = h0 + i32F4_to__i32((h1-h0) * ty);
            i32 terrain_z = i32F4_to__i32(height_fp);

            for (i32 dz = 0; dz < CHUNK__DEPTH; ++dz) {
                i32 tile_z = base_z + dz;
                Local_Tile_Vector__3u8 local_tile_vec = { dx, dy, dz };
                Tile *p_tile = get_p_tile_from__chunk(p_chunk, local_tile_vec);
                p_tile->the_kind_of__tile_cover = 
                    Tile_Cover_Kind__None;

                if (tile_z > terrain_z) {
                    if (tile_z <= 0) {
                        p_tile->the_kind_of__tile = Tile_Kind__Water;
                    } else {
                        p_tile->the_kind_of__tile = Tile_Kind__None;
                    }
                } else if (tile_z == terrain_z) {
                    p_tile->the_kind_of__tile = Tile_Kind__Grass;
                }  else if (tile_z >= terrain_z - 2) {
                    if (tile_z <= 0) {
                        p_tile->the_kind_of__tile = Tile_Kind__Sand;
                        p_tile->the_kind_of__tile_cover = Tile_Cover_Kind__Wall__Sand;
                    } else if (tile_z >= terrain_z - 2) {
                        p_tile->the_kind_of__tile = Tile_Kind__Dirt;
                        p_tile->the_kind_of__tile_cover = Tile_Cover_Kind__Wall__Dirt;
                    }
                } else {
                    p_tile->the_kind_of__tile = Tile_Kind__Stone;
                    p_tile->the_kind_of__tile_cover = Tile_Cover_Kind__Wall__Stone;
                }
            }
        }
    }
}










































// typedef struct Region_Generation_Data__Node_Point_t {
//     uint8_t x__node__u3     :3;
//     uint8_t y__node__u3     :3;
//     uint8_t piece_flags__u2 :2;
//     uint8_t z__node__u8     :8;
// } Region_Generation_Data__Node_Point;
// 
// #define REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE 2
// 
// typedef struct Region_Generation_Data__Node_t {
//     Region_Generation_Data__Node_Point region_generation_data__node__points[
//         REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE];
// } Region_Generation_Data__Node;
// 
// static inline
// Region_Generation_Data__Node_Point *get_p_region_generation_data__node_point_by__index(
//         Region_Generation_Data__Node *p_region_generation_data__node,
//         Index__u8 index_of__point_in__node) {
//     return &p_region_generation_data__node
//         ->region_generation_data__node__points[
//         index_of__point_in__node];
// }
// 
// #define REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF 4
// #define REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF 4
// 
// #define REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__GLOB \
//     REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE * 4
// 
// typedef struct Region_Generation_Data__Glob_t {
//     Region_Generation_Data__Node_Point *ptr_array_of__region_generation_data__nodes_points[
//         REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__GLOB];
//     ///
//     /// Small globs will have the last 4 entries as nullptr.
//     ///
// } Region_Generation_Data__Glob;
// 
// static inline
// Region_Generation_Data__Node_Point *get_p_region_generation_data__node_point_by__index_in__glob(
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Index__u8 index_of__point_in__node) {
//     return p_region_generation_data__glob
//         ->ptr_array_of__region_generation_data__nodes_points[
//         index_of__point_in__node];
// }
// 
// typedef struct Region_Generation_Data_t {
//     Region_Generation_Data__Node region_generation_data__nodes[
//         REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF
//             * REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF];
//     Region_Generation_Data__Glob region_generation_data__globs[
//         (REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF+1)
//             * (REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF+1)];
// } Region_Generation_Data;
// 
// bool populate_region_generation_data__glob(
//         Region_Generation_Data *p_region_generation_data,
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Repeatable_Psuedo_Random *p_randomizer,
//         Index__u8 index_x_of__glob__u8,
//         Index__u8 index_y_of__glob__u8);
// 
// bool populate_region_generation_data__glob__mini(
//         Region_Generation_Data *p_region_generation_data,
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Repeatable_Psuedo_Random *p_randomizer,
//         Index__u8 index_x_of__glob__u8,
//         Index__u8 index_y_of__glob__u8);
// 
// static inline
// Region_Generation_Data__Node *get_p_region_generation_data__node_by__indices(
//         Region_Generation_Data *p_region_generation_data,
//         Index__u8 index_x_of__node,
//         Index__u8 index_y_of__node) {
//     return &p_region_generation_data->region_generation_data__nodes[
//         index_x_of__node
//             + index_y_of__node
//             * REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF];
// }
// 
// bool populate_region_generation_data__glob__edge(
//         Region_Generation_Data *p_region_generation_data,
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Repeatable_Psuedo_Random *p_randomizer,
//         Index__u8 index_x_of__glob__u8,
//         Index__u8 index_y_of__glob__u8);
// 
// bool populate_region_generation_data__glob__edge__mini(
//         Region_Generation_Data *p_region_generation_data,
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Repeatable_Psuedo_Random *p_randomizer,
//         Index__u8 index_x_of__glob__u8,
//         Index__u8 index_y_of__glob__u8);
// 
// void populate_region_generation_data(
//         Region_Generation_Data *p_region_generation_data,
//         Repeatable_Psuedo_Random *p_randomizer,
//         Region_Vector__3i32 region_vector__3i32) {
//     Vector__3i32 node_vector__origin__3i32 =
//         get_vector__3i32(
//                 region_vector__3i32.x__i32
//                 * REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF,
//                 region_vector__3i32.y__i32
//                 * REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF,
//                 region_vector__3i32.z__i32
//                 * (REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF
//                     * REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF));
// 
//     Region_Generation_Data__Node *p_region_generation_data__node =
//         p_region_generation_data->region_generation_data__nodes;
// 
//     // randomize nodes
// 
//     for (Index__u8 index_y_of__node = 0;
//             index_y_of__node
//             < REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF;
//             index_y_of__node++) {
//         for (Index__u8 index_x_of__node = 0;
//                 index_x_of__node
//                 < REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF;
//                 index_x_of__node++) {
// 
//             p_region_generation_data__node =
//                 &p_region_generation_data->region_generation_data__nodes[
//                     index_x_of__node
//                         + index_y_of__node
//                         * REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF];
//             
//             Vector__3i32 node_vector__3i32 =
//                 get_vector__3i32(
//                         node_vector__origin__3i32.x__i32
//                         + index_x_of__node,
//                         node_vector__origin__3i32.y__i32
//                         + index_y_of__node,
//                         node_vector__origin__3i32.z__i32);
// 
//             i32 random_value = 
//                 get_pseudo_random_i32_with__xy__intrusively(
//                         p_randomizer, 
//                         node_vector__3i32.x__i32, 
//                         node_vector__3i32.y__i32);
// 
//             Repeatable_Psuedo_Random sub_randomizer;
//             initialize_repeatable_psuedo_random(
//                     &sub_randomizer, 
//                     random_value);
// 
//             for (Index__u8 index_of__point_in__node = 0;
//                     index_of__point_in__node
//                     < REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE;
//                     index_x_of__node++) {
//                 Region_Generation_Data__Node_Point *p_point =
//                     get_p_region_generation_data__node_point_by__index(
//                             p_region_generation_data__node, 
//                             index_of__point_in__node);
//                 p_point->x__node__u3 =
//                     random_value & MASK(3);
//                 p_point->y__node__u3 =
//                     (random_value>>3) & MASK(3);
//                 random_value = get_pseudo_random_i32__intrusively(
//                         &sub_randomizer);
//             }
//         }
//     }
// 
//     // populate globs
// 
//     for (Index__u8 index_y_of__glob = 0;
//             index_y_of__glob
//             < REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF;
//             index_y_of__glob++) {
//         for (Index__u8 index_x_of__glob = 0;
//                 index_x_of__glob
//                 < REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF;
//                 index_x_of__glob++) {
//             Region_Generation_Data__Glob *p_region_generation_data__glob =
//                 &p_region_generation_data->region_generation_data__globs[
//                     index_x_of__glob
//                         + index_y_of__glob
//                         * (REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF+1)]
//                         ;
//             bool is_glob__mini_glob = (index_x_of__glob & 0b1);
//             bool is_glob__edge_glob =
//                 !index_x_of__glob
//                 || !index_y_of__glob
//                 || (index_x_of__glob
//                         == REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF-1)
//                 || (index_y_of__glob
//                         == REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF-1)
//                 ;
// 
//             if (is_glob__mini_glob
//                     && is_glob__edge_glob) {
//                 populate_region_generation_data__glob__edge__mini(
//                         p_region_generation_data, 
//                         p_region_generation_data__glob, 
//                         p_randomizer, 
//                         index_x_of__glob, 
//                         index_y_of__glob);
//                 continue;
//             }
// 
//             if (is_glob__mini_glob) {
//                 populate_region_generation_data__glob__mini(
//                         p_region_generation_data, 
//                         p_region_generation_data__glob, 
//                         p_randomizer, 
//                         index_x_of__glob, 
//                         index_y_of__glob);
//                 continue;
//             }
// 
//             if (is_glob__edge_glob) {
//                 populate_region_generation_data__glob__edge(
//                         p_region_generation_data, 
//                         p_region_generation_data__glob, 
//                         p_randomizer, 
//                         index_x_of__glob, 
//                         index_y_of__glob);
//                 continue;
//             }
// 
//             populate_region_generation_data__glob(
//                     p_region_generation_data, 
//                     p_region_generation_data__glob, 
//                     p_randomizer, 
//                     index_x_of__glob, 
//                     index_y_of__glob);
//         }
//     }
// }
// 
// Region_Generation_Data__Node_Point 
// *get_p_region_generation_data__node_point_closest_to__this_point(
//         Region_Generation_Data__Node *p_region_generation_data__node,
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Index__u8 minimum_index_x__u8,
//         Index__u8 minimum_index_y__u8) {
//     Region_Generation_Data__Node_Point *p_region_generation_data__node_point__closest =
//         0;
// 
//     u32 distance_squared_of__closest = 0;
// 
//     for (Index__u8 index_of__point_in__node = 0;
//             index_of__point_in__node
//             < REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE;
//             index_of__point_in__node++) {
//         Region_Generation_Data__Node_Point *p_region_generation_data__node_point =
//             get_p_region_generation_data__node_point_by__index(
//                     p_region_generation_data__node, 
//                     index_of__point_in__node);
// 
//         if (!p_region_generation_data__node_point__closest) {
//             p_region_generation_data__node_point__closest =
//                 p_region_generation_data__node_point;
//             i8 delta_x__closest =
//                 p_region_generation_data__node_point->x__node__u3
//                 - minimum_index_x__u8
//                 ;
//             i8 delta_y__closest =
//                 p_region_generation_data__node_point->y__node__u3
//                 - minimum_index_y__u8
//                 ;
// 
//             distance_squared_of__closest =
//                 (delta_x__closest*delta_x__closest)
//                 + (delta_y__closest*delta_y__closest);
//             continue;
//         }
// 
//         i8 delta_x = 
//             p_region_generation_data__node_point->x__node__u3
//             - minimum_index_x__u8
//             ;
//         i8 delta_y = 
//             p_region_generation_data__node_point->y__node__u3
//             - minimum_index_y__u8
//             ;
// 
//         u32 distance_squared =
//             (delta_x * delta_x)
//             + (delta_y * delta_y)
//             ;
// 
//         if (distance_squared
//                 >= distance_squared_of__closest) {
//             continue;
//         }
// 
//         if (!p_region_generation_data__glob)
//             goto set_closest;
//         
//         for (Index__u8 index_of__point_in__glob = 0;
//                 index_of__point_in__glob
//                 < REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__GLOB;
//                 index_of__point_in__glob++) {
//             if (p_region_generation_data__node_point
//                     == get_p_region_generation_data__node_point_by__index_in__glob(
//                         p_region_generation_data__glob, 
//                         index_of__point_in__node)) {
//                 continue;
//             }
//         }
// 
// set_closest:
//         distance_squared_of__closest =
//             distance_squared;
//         p_region_generation_data__node_point__closest =
//             p_region_generation_data__node_point;
//     }
//     return p_region_generation_data__node_point__closest;
// }
// 
// Region_Generation_Data__Node_Point *
// populate_region_generation_data__glob__points(
//         Region_Generation_Data__Node *p_region_generation_data__node,
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Index__u8 *p_index_of__point_in__glob,
//         Signed_Index__i8 closest_to__x,
//         Signed_Index__i8 closest_to__y) {
//     Region_Generation_Data__Node_Point *p_region_generation_data__node_point = 0;
//     for (Index__u8 index_of__point_in__node = 0;
//             index_of__point_in__node
//             < REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE;
//             index_of__point_in__node++) {
//         p_region_generation_data__node_point =
//             get_p_region_generation_data__node_point_closest_to__this_point(
//                     p_region_generation_data__node, 
//                     p_region_generation_data__glob,
//                     closest_to__x, 
//                     closest_to__y);
// 
//         if (!p_region_generation_data__node_point)
//             return 0;
// 
//         closest_to__x =
//             p_region_generation_data__node_point
//             ->x__node__u3;
//         closest_to__y =
//             p_region_generation_data__node_point
//             ->y__node__u3;
// 
//         p_region_generation_data__glob
//             ->ptr_array_of__region_generation_data__nodes_points[
//             (*p_index_of__point_in__glob)++] =
//                 p_region_generation_data__node_point;
//     }
//     return p_region_generation_data__node_point;
// }
// 
// bool populate_region_generation_data__glob(
//         Region_Generation_Data *p_region_generation_data,
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Repeatable_Psuedo_Random *p_randomizer,
//         Index__u8 index_x_of__glob__u8,
//         Index__u8 index_y_of__glob__u8) {
//     Region_Generation_Data__Node *p_node__top_left =
//         get_p_region_generation_data__node_by__indices(
//                 p_region_generation_data, 
//                 index_x_of__glob__u8 - 1, 
//                 index_y_of__glob__u8 - 1);
//     Region_Generation_Data__Node *p_node__top_right =
//         get_p_region_generation_data__node_by__indices(
//                 p_region_generation_data, 
//                 index_x_of__glob__u8, 
//                 index_y_of__glob__u8 - 1);
//     Region_Generation_Data__Node *p_node__bottom_left =
//         get_p_region_generation_data__node_by__indices(
//                 p_region_generation_data, 
//                 index_x_of__glob__u8 - 1, 
//                 index_y_of__glob__u8);
//     Region_Generation_Data__Node *p_node__bottom_right =
//         get_p_region_generation_data__node_by__indices(
//                 p_region_generation_data, 
//                 index_x_of__glob__u8, 
//                 index_y_of__glob__u8);
// 
//     Index__u8 index_of__point_in__glob = 0;
//     Region_Generation_Data__Node_Point 
//         *p_region_generation_data__node_point__latest =
//         populate_region_generation_data__glob__points(
//                 p_node__top_left, 
//                 p_region_generation_data__glob, 
//                 &index_of__point_in__glob,
//                 0, 0);
//     if (!p_region_generation_data__node_point__latest) {
//         return false;
//     }
//     p_region_generation_data__node_point__latest =
//         populate_region_generation_data__glob__points(
//                 p_node__top_right, 
//                 p_region_generation_data__glob, 
//                 &index_of__point_in__glob,
//                 p_region_generation_data__node_point__latest
//                 ->x__node__u3 - 8,
//                 p_region_generation_data__node_point__latest
//                 ->y__node__u3);
//     if (!p_region_generation_data__node_point__latest) {
//         return false;
//     }
//     p_region_generation_data__node_point__latest =
//         populate_region_generation_data__glob__points(
//                 p_node__bottom_right, 
//                 p_region_generation_data__glob, 
//                 &index_of__point_in__glob,
//                 p_region_generation_data__node_point__latest
//                 ->x__node__u3,
//                 p_region_generation_data__node_point__latest
//                 ->y__node__u3 - 8);
//     if (!p_region_generation_data__node_point__latest) {
//         return false;
//     }
//     p_region_generation_data__node_point__latest =
//         populate_region_generation_data__glob__points(
//                 p_node__bottom_right, 
//                 p_region_generation_data__glob, 
//                 &index_of__point_in__glob,
//                 p_region_generation_data__node_point__latest
//                 ->x__node__u3 + 8,
//                 p_region_generation_data__node_point__latest
//                 ->y__node__u3);
// 
//     return true;
// }
// 
// bool populate_region_generation_data__glob__mini(
//         Region_Generation_Data *p_region_generation_data,
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Repeatable_Psuedo_Random *p_randomizer,
//         Index__u8 index_x_of__glob__u8,
//         Index__u8 index_y_of__glob__u8) {
//     
//     return true;
// }
// 
// bool populate_region_generation_data__glob__edge(
//         Region_Generation_Data *p_region_generation_data,
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Repeatable_Psuedo_Random *p_randomizer,
//         Index__u8 index_x_of__glob__u8,
//         Index__u8 index_y_of__glob__u8) {
//     
//     return true;
// }
// 
// bool populate_region_generation_data__glob__edge__mini(
//         Region_Generation_Data *p_region_generation_data,
//         Region_Generation_Data__Glob *p_region_generation_data__glob,
//         Repeatable_Psuedo_Random *p_randomizer,
//         Index__u8 index_x_of__glob__u8,
//         Index__u8 index_y_of__glob__u8) {
//     
//     return true;
// }
