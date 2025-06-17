#ifndef AG__WORLD_H
#define AG__WORLD_H

#include "ag__defines.h"
#include "defines_weak.h"

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
        Direction__u8 direction_of__placement__u8);

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
        Tile tile);

#endif
