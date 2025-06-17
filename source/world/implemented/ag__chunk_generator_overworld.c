#include "world/implemented/ag__chunk_generator_overworld.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform_defaults.h"
#include "types/implemented/tile_kind.h"
#include "vectors.h"
#include "world/global_space.h"
#include "world/chunk_vectors.h"
#include "random.h"

typedef struct Region_Generation_Data__Node_Point_t {
    uint8_t x__node__u3     :3;
    uint8_t y__node__u3     :3;
    uint8_t piece_flags__u2 :2;
    uint8_t z__node__u8     :8;
} Region_Generation_Data__Node_Point;

#define REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE 2

typedef struct Region_Generation_Data__Node_t {
    Region_Generation_Data__Node_Point region_generation_data__node__points[
        REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE];
} Region_Generation_Data__Node;

static inline
Region_Generation_Data__Node_Point *get_p_region_generation_data__node_point_by__index(
        Region_Generation_Data__Node *p_region_generation_data__node,
        Index__u8 index_of__point_in__node) {
    return &p_region_generation_data__node
        ->region_generation_data__node__points[
        index_of__point_in__node];
}

#define REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF 4
#define REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF 4

#define REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__GLOB \
    REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE * 4

typedef struct Region_Generation_Data__Glob_t {
    Region_Generation_Data__Node_Point *ptr_array_of__region_generation_data__nodes_points[
        REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__GLOB];
    ///
    /// Small globs will have the last 4 entries as nullptr.
    ///
} Region_Generation_Data__Glob;

static inline
Region_Generation_Data__Node_Point *get_p_region_generation_data__node_point_by__index_in__glob(
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Index__u8 index_of__point_in__node) {
    return p_region_generation_data__glob
        ->ptr_array_of__region_generation_data__nodes_points[
        index_of__point_in__node];
}

typedef struct Region_Generation_Data_t {
    Region_Generation_Data__Node region_generation_data__nodes[
        REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF
            * REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF];
    Region_Generation_Data__Glob region_generation_data__globs[
        (REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF+1)
            * (REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF+1)];
} Region_Generation_Data;

bool populate_region_generation_data__glob(
        Region_Generation_Data *p_region_generation_data,
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Repeatable_Psuedo_Random *p_randomizer,
        Index__u8 index_x_of__glob__u8,
        Index__u8 index_y_of__glob__u8);

bool populate_region_generation_data__glob__mini(
        Region_Generation_Data *p_region_generation_data,
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Repeatable_Psuedo_Random *p_randomizer,
        Index__u8 index_x_of__glob__u8,
        Index__u8 index_y_of__glob__u8);

static inline
Region_Generation_Data__Node *get_p_region_generation_data__node_by__indices(
        Region_Generation_Data *p_region_generation_data,
        Index__u8 index_x_of__node,
        Index__u8 index_y_of__node) {
    return &p_region_generation_data->region_generation_data__nodes[
        index_x_of__node
            + index_y_of__node
            * REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF];
}

bool populate_region_generation_data__glob__edge(
        Region_Generation_Data *p_region_generation_data,
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Repeatable_Psuedo_Random *p_randomizer,
        Index__u8 index_x_of__glob__u8,
        Index__u8 index_y_of__glob__u8);

bool populate_region_generation_data__glob__edge__mini(
        Region_Generation_Data *p_region_generation_data,
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Repeatable_Psuedo_Random *p_randomizer,
        Index__u8 index_x_of__glob__u8,
        Index__u8 index_y_of__glob__u8);

void populate_region_generation_data(
        Region_Generation_Data *p_region_generation_data,
        Repeatable_Psuedo_Random *p_randomizer,
        Region_Vector__3i32 region_vector__3i32) {
    Vector__3i32 node_vector__origin__3i32 =
        get_vector__3i32(
                region_vector__3i32.x__i32
                * REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF,
                region_vector__3i32.y__i32
                * REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF,
                region_vector__3i32.z__i32
                * (REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF
                    * REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF));

    Region_Generation_Data__Node *p_region_generation_data__node =
        p_region_generation_data->region_generation_data__nodes;

    // randomize nodes

    for (Index__u8 index_y_of__node = 0;
            index_y_of__node
            < REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF;
            index_y_of__node++) {
        for (Index__u8 index_x_of__node = 0;
                index_x_of__node
                < REGION_GENERATION_DATA__NODE__ROW__MAX_QUANTITY_OF;
                index_x_of__node++) {

            p_region_generation_data__node =
                &p_region_generation_data->region_generation_data__nodes[
                    index_x_of__node
                        + index_y_of__node
                        * REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF];
            
            Vector__3i32 node_vector__3i32 =
                get_vector__3i32(
                        node_vector__origin__3i32.x__i32
                        + index_x_of__node,
                        node_vector__origin__3i32.y__i32
                        + index_y_of__node,
                        node_vector__origin__3i32.z__i32);

            i32 random_value = 
                get_pseudo_random_i32_with__xy__intrusively(
                        p_randomizer, 
                        node_vector__3i32.x__i32, 
                        node_vector__3i32.y__i32);

            Repeatable_Psuedo_Random sub_randomizer;
            initialize_repeatable_psuedo_random(
                    &sub_randomizer, 
                    random_value);

            for (Index__u8 index_of__point_in__node = 0;
                    index_of__point_in__node
                    < REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE;
                    index_x_of__node++) {
                Region_Generation_Data__Node_Point *p_point =
                    get_p_region_generation_data__node_point_by__index(
                            p_region_generation_data__node, 
                            index_of__point_in__node);
                p_point->x__node__u3 =
                    random_value & MASK(3);
                p_point->y__node__u3 =
                    (random_value>>3) & MASK(3);
                random_value = get_pseudo_random_i32__intrusively(
                        &sub_randomizer);
            }
        }
    }

    // populate globs

    for (Index__u8 index_y_of__glob = 0;
            index_y_of__glob
            < REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF;
            index_y_of__glob++) {
        for (Index__u8 index_x_of__glob = 0;
                index_x_of__glob
                < REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF;
                index_x_of__glob++) {
            Region_Generation_Data__Glob *p_region_generation_data__glob =
                &p_region_generation_data->region_generation_data__globs[
                    index_x_of__glob
                        + index_y_of__glob
                        * (REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF+1)]
                        ;
            bool is_glob__mini_glob = (index_x_of__glob & 0b1);
            bool is_glob__edge_glob =
                !index_x_of__glob
                || !index_y_of__glob
                || (index_x_of__glob
                        == REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF-1)
                || (index_y_of__glob
                        == REGION_GENERATION_DATA__NODE__COLUMN__MAX_QUANTITY_OF-1)
                ;

            if (is_glob__mini_glob
                    && is_glob__edge_glob) {
                populate_region_generation_data__glob__edge__mini(
                        p_region_generation_data, 
                        p_region_generation_data__glob, 
                        p_randomizer, 
                        index_x_of__glob, 
                        index_y_of__glob);
                continue;
            }

            if (is_glob__mini_glob) {
                populate_region_generation_data__glob__mini(
                        p_region_generation_data, 
                        p_region_generation_data__glob, 
                        p_randomizer, 
                        index_x_of__glob, 
                        index_y_of__glob);
                continue;
            }

            if (is_glob__edge_glob) {
                populate_region_generation_data__glob__edge(
                        p_region_generation_data, 
                        p_region_generation_data__glob, 
                        p_randomizer, 
                        index_x_of__glob, 
                        index_y_of__glob);
                continue;
            }

            populate_region_generation_data__glob(
                    p_region_generation_data, 
                    p_region_generation_data__glob, 
                    p_randomizer, 
                    index_x_of__glob, 
                    index_y_of__glob);
        }
    }
}

Region_Generation_Data__Node_Point 
*get_p_region_generation_data__node_point_closest_to__this_point(
        Region_Generation_Data__Node *p_region_generation_data__node,
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Index__u8 minimum_index_x__u8,
        Index__u8 minimum_index_y__u8) {
    Region_Generation_Data__Node_Point *p_region_generation_data__node_point__closest =
        0;

    u32 distance_squared_of__closest = 0;

    for (Index__u8 index_of__point_in__node = 0;
            index_of__point_in__node
            < REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE;
            index_of__point_in__node++) {
        Region_Generation_Data__Node_Point *p_region_generation_data__node_point =
            get_p_region_generation_data__node_point_by__index(
                    p_region_generation_data__node, 
                    index_of__point_in__node);

        if (!p_region_generation_data__node_point__closest) {
            p_region_generation_data__node_point__closest =
                p_region_generation_data__node_point;
            i8 delta_x__closest =
                p_region_generation_data__node_point->x__node__u3
                - minimum_index_x__u8
                ;
            i8 delta_y__closest =
                p_region_generation_data__node_point->y__node__u3
                - minimum_index_y__u8
                ;

            distance_squared_of__closest =
                (delta_x__closest*delta_x__closest)
                + (delta_y__closest*delta_y__closest);
            continue;
        }

        i8 delta_x = 
            p_region_generation_data__node_point->x__node__u3
            - minimum_index_x__u8
            ;
        i8 delta_y = 
            p_region_generation_data__node_point->y__node__u3
            - minimum_index_y__u8
            ;

        u32 distance_squared =
            (delta_x * delta_x)
            + (delta_y * delta_y)
            ;

        if (distance_squared
                >= distance_squared_of__closest) {
            continue;
        }

        if (!p_region_generation_data__glob)
            goto set_closest;
        
        for (Index__u8 index_of__point_in__glob = 0;
                index_of__point_in__glob
                < REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__GLOB;
                index_of__point_in__glob++) {
            if (p_region_generation_data__node_point
                    == get_p_region_generation_data__node_point_by__index_in__glob(
                        p_region_generation_data__glob, 
                        index_of__point_in__node)) {
                continue;
            }
        }

set_closest:
        distance_squared_of__closest =
            distance_squared;
        p_region_generation_data__node_point__closest =
            p_region_generation_data__node_point;
    }
    return p_region_generation_data__node_point__closest;
}

Region_Generation_Data__Node_Point *
populate_region_generation_data__glob__points(
        Region_Generation_Data__Node *p_region_generation_data__node,
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Index__u8 *p_index_of__point_in__glob,
        Signed_Index__i8 closest_to__x,
        Signed_Index__i8 closest_to__y) {
    Region_Generation_Data__Node_Point *p_region_generation_data__node_point = 0;
    for (Index__u8 index_of__point_in__node = 0;
            index_of__point_in__node
            < REGION_GENERATION_DATA__NODE__POINT__QUANTITY_OF_PER__NODE;
            index_of__point_in__node++) {
        p_region_generation_data__node_point =
            get_p_region_generation_data__node_point_closest_to__this_point(
                    p_region_generation_data__node, 
                    p_region_generation_data__glob,
                    closest_to__x, 
                    closest_to__y);

        if (!p_region_generation_data__node_point)
            return 0;

        closest_to__x =
            p_region_generation_data__node_point
            ->x__node__u3;
        closest_to__y =
            p_region_generation_data__node_point
            ->y__node__u3;

        p_region_generation_data__glob
            ->ptr_array_of__region_generation_data__nodes_points[
            (*p_index_of__point_in__glob)++] =
                p_region_generation_data__node_point;
    }
    return p_region_generation_data__node_point;
}

bool populate_region_generation_data__glob(
        Region_Generation_Data *p_region_generation_data,
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Repeatable_Psuedo_Random *p_randomizer,
        Index__u8 index_x_of__glob__u8,
        Index__u8 index_y_of__glob__u8) {
    Region_Generation_Data__Node *p_node__top_left =
        get_p_region_generation_data__node_by__indices(
                p_region_generation_data, 
                index_x_of__glob__u8 - 1, 
                index_y_of__glob__u8 - 1);
    Region_Generation_Data__Node *p_node__top_right =
        get_p_region_generation_data__node_by__indices(
                p_region_generation_data, 
                index_x_of__glob__u8, 
                index_y_of__glob__u8 - 1);
    Region_Generation_Data__Node *p_node__bottom_left =
        get_p_region_generation_data__node_by__indices(
                p_region_generation_data, 
                index_x_of__glob__u8 - 1, 
                index_y_of__glob__u8);
    Region_Generation_Data__Node *p_node__bottom_right =
        get_p_region_generation_data__node_by__indices(
                p_region_generation_data, 
                index_x_of__glob__u8, 
                index_y_of__glob__u8);

    Index__u8 index_of__point_in__glob = 0;
    Region_Generation_Data__Node_Point 
        *p_region_generation_data__node_point__latest =
        populate_region_generation_data__glob__points(
                p_node__top_left, 
                p_region_generation_data__glob, 
                &index_of__point_in__glob,
                0, 0);
    if (!p_region_generation_data__node_point__latest) {
        return false;
    }
    p_region_generation_data__node_point__latest =
        populate_region_generation_data__glob__points(
                p_node__top_right, 
                p_region_generation_data__glob, 
                &index_of__point_in__glob,
                p_region_generation_data__node_point__latest
                ->x__node__u3 - 8,
                p_region_generation_data__node_point__latest
                ->y__node__u3);
    if (!p_region_generation_data__node_point__latest) {
        return false;
    }
    p_region_generation_data__node_point__latest =
        populate_region_generation_data__glob__points(
                p_node__bottom_right, 
                p_region_generation_data__glob, 
                &index_of__point_in__glob,
                p_region_generation_data__node_point__latest
                ->x__node__u3,
                p_region_generation_data__node_point__latest
                ->y__node__u3 - 8);
    if (!p_region_generation_data__node_point__latest) {
        return false;
    }
    p_region_generation_data__node_point__latest =
        populate_region_generation_data__glob__points(
                p_node__bottom_right, 
                p_region_generation_data__glob, 
                &index_of__point_in__glob,
                p_region_generation_data__node_point__latest
                ->x__node__u3 + 8,
                p_region_generation_data__node_point__latest
                ->y__node__u3);

    return true;
}

bool populate_region_generation_data__glob__mini(
        Region_Generation_Data *p_region_generation_data,
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Repeatable_Psuedo_Random *p_randomizer,
        Index__u8 index_x_of__glob__u8,
        Index__u8 index_y_of__glob__u8) {
    
    return true;
}

bool populate_region_generation_data__glob__edge(
        Region_Generation_Data *p_region_generation_data,
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Repeatable_Psuedo_Random *p_randomizer,
        Index__u8 index_x_of__glob__u8,
        Index__u8 index_y_of__glob__u8) {
    
    return true;
}

bool populate_region_generation_data__glob__edge__mini(
        Region_Generation_Data *p_region_generation_data,
        Region_Generation_Data__Glob *p_region_generation_data__glob,
        Repeatable_Psuedo_Random *p_randomizer,
        Index__u8 index_x_of__glob__u8,
        Index__u8 index_y_of__glob__u8) {
    
    return true;
}

void f_chunk_generator__overworld(
        Game *p_game,
        Global_Space *p_global_space) {
    if (!p_global_space) {
        debug_error("f_chunk_generator__overworld, p_global_space == 0.");
        return;
    }
    Chunk *p_chunk =
        get_p_chunk_from__global_space(
                p_global_space);
}
