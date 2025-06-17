#include "world/ag__world.h"
#include "defines.h"
#include "types/implemented/tile_cover_kind.h"
#include "world/ag__tile.h"
#include "world/ag__tile_logic_record.h"
#include "world/tile_logic_table_manager.h"
#include "game.h"
#include "world/world.h"
#include "world/global_space_manager.h"
#include "world/tile_slope_flags.h"

///
/// Attempts to set the qualities of the
/// tile argument to the tile of tile_vector__3i32.
///
/// AG uses custom tile logic flags to determine
/// the success or failure of such placement.
///
/// Returns true on complete successful placement.
/// Returns false on partial, or total placement failure.
///
/// NOTE: p_tile is modified based on placement success.
/// Qualities that are successfully placed will be
/// set to their respective None values, and failure
/// will leave the quality unchanged.
///
bool place_tile(
        World *p_world,
        Tile_Vector__3i32 tile_vector__3i32,
        Tile *p_tile,
        Direction__u8 direction_of__placement__u8) {
    Tile *p_tile_at__location =
        get_p_tile_from__global_space_manager(
                get_p_global_space_manager_from__world(
                    p_world),
                tile_vector__3i32);

    if (!p_tile_at__location) {
        debug_error("place_tile, tile_vector__3i32 is invalid at this time.");
        return false;
    }

    Tile_Logic_Record tile_logic_record;
    get_tile_logic_record_for__this_tile(
            get_p_tile_logic_table_manager_from__world(p_world), 
            &tile_logic_record, 
            p_tile_at__location);

    if (p_tile->the_kind_of__tile
            != Tile_Kind__None
            && (is_tile_logic_record__ground_place_overriden(
                tile_logic_record)
            || p_tile_at__location->the_kind_of__tile
            == Tile_Kind__None)) {
        p_tile_at__location->the_kind_of__tile =
            p_tile->the_kind_of__tile;
        p_tile->the_kind_of__tile = Tile_Kind__None;
    }
    if (p_tile->the_kind_of__tile_cover
            != Tile_Cover_Kind__None
            && (is_tile_logic_record__ground_place_overriden(
                tile_logic_record)
            || p_tile_at__location->the_kind_of__tile_cover
            == Tile_Cover_Kind__None)) {

        if (is_tile_with__stairs(p_tile)) {
            p_tile_at__location->slope_flags__u4 =
                get_tile_slope_flags(
                        p_world,
                        tile_vector__3i32,
                        direction_of__placement__u8);
        }

        p_tile_at__location->the_kind_of__tile_cover =
            p_tile->the_kind_of__tile_cover;
        p_tile->the_kind_of__tile_cover = Tile_Cover_Kind__None;
    }
    return 
        !p_tile->the_kind_of__tile
        && !p_tile->the_kind_of__tile_cover;
}

///
/// To remove a tile, the respective tile_kind
/// and tile_cover_kind must match the contents
/// of the tile located at tile_vector__3i32.
///
/// For example, if the tile at tile_vector__3i32
/// has Tile_Kind__Grass, and the tile argument
/// has Tile_Kind__None, then the specified tile
/// will be unchanged in this regard.
///
/// If you sample the designated tile, and pass
/// it as the tile argument, all qualities of
/// the designated tile will be removed from the world.
///
/// Returns false if the tile removal failed for
/// any reason.
///
bool remove_tile(
        World *p_world,
        Tile_Vector__3i32 tile_vector__3i32,
        Tile tile) {
    Tile *p_tile_at__location =
        get_p_tile_from__global_space_manager(
                get_p_global_space_manager_from__world(
                    p_world),
                tile_vector__3i32);

    if (!p_tile_at__location) {
        debug_error("remove_tile, tile_vector__3i32 is invalid at this time.");
        return false;
    }

    bool result = true;
    if (p_tile_at__location->the_kind_of__tile
            == tile.the_kind_of__tile) {
        p_tile_at__location->the_kind_of__tile =
            Tile_Kind__None;
    } else if (tile.the_kind_of__tile != Tile_Kind__None) {
        result = false;
    }

    if (p_tile_at__location->the_kind_of__tile_cover
            == tile.the_kind_of__tile_cover) {
        if (is_tile_with__stairs(
                    p_tile_at__location)) {
            p_tile_at__location->slope_flags__u4 = 0;
        }
        p_tile_at__location->the_kind_of__tile =
            Tile_Kind__None;
    } else if (tile.the_kind_of__tile_cover != Tile_Cover_Kind__None) {
        result = false;
    }

    return result;
}
