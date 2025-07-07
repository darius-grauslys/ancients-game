#ifndef AG__CHUNK_GENERATOR_OVERWORLD_H
#define AG__CHUNK_GENERATOR_OVERWORLD_H

#include "defines.h"

void fill_chunk_with(
        Chunk *p_chunk,
        Tile_Kind the_kind_of__tile,
        Tile_Cover_Kind the_kind_of__tile_cover);

i32 ag__get_natural_world_height_at__xy(
        Repeatable_Psuedo_Random *p_random,
        i32 x,
        i32 y);

void m_process__chunk_generator__overworld(
        Process *p_this_process,
        Game *p_game);

#endif
