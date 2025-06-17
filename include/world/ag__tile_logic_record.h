#ifndef AG__TILE_LOGIC_RECORD_H
#define AG__TILE_LOGIC_RECORD_H

#include "ag__defines.h"
#include "types/implemented/tile_logic_record_data.h"

static inline
bool is_tile_logic_record__ground_place_overriden(
        Tile_Logic_Record tile_logic_record) {
    return tile_logic_record.tile_logic_flags__u8
        & TILE_LOGIC_FLAG__AG__IS_GROUND__PLACE_OVERIDDEN;
}

static inline
bool is_tile_logic_record__cover_place_overriden(
        Tile_Logic_Record tile_logic_record) {
    return tile_logic_record.tile_logic_flags__u8
        & TILE_LOGIC_FLAG__AG__IS_COVER__PLACE_OVERIDDEN;
}
#endif
