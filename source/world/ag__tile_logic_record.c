#include "world/ag__tile_logic_record.h"
#include "defines_weak.h"
#include <string.h>
#include <numerics.h>

void m_tile_logic_table__get_tile_logic_record__ag(
        Tile_Logic_Table *p_tile_logic_manager,
        Tile_Logic_Record *p_tile_logic_record,
        Tile *p_tile) {
    memset(p_tile_logic_record, 0, sizeof(Tile_Logic_Record));
    if (!p_tile)
        return;

    Tile_Logic_Record *p_tile_logic_record__tile =
        &p_tile_logic_manager->tile_logic_table_data
        .tile_logic_record__tile_kind[p_tile->the_kind_of__tile];
    Tile_Logic_Record *p_tile_logic_record__cover =
        &p_tile_logic_manager->tile_logic_table_data
        .tile_logic_record__tile_cover_kind[p_tile->the_kind_of__tile_cover];

    p_tile_logic_record->tile_logic_flags__u8 =
        (p_tile_logic_record__tile->tile_logic_flags__u8
        | p_tile_logic_record__cover->tile_logic_flags__u8)
        & ~TILE_LOGIC_FLAG__IS_WITHOUT_GROUND
        ;

    p_tile_logic_record->tile_logic_flags__u8 |=
        (p_tile_logic_record__tile->tile_logic_flags__u8
         & TILE_LOGIC_FLAG__IS_WITHOUT_GROUND)
        & (p_tile_logic_record__cover->tile_logic_flags__u8
                & TILE_LOGIC_FLAG__IS_WITHOUT_GROUND)
        ;
    p_tile_logic_record->tile_height__i32F4 =
        max__i32(
                p_tile_logic_record__tile->tile_height__i32F4, 
                p_tile_logic_record__cover->tile_height__i32F4);
}
