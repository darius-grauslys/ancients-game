#include "world/implemented/ag__chunk_generator_overworld.h"
#include "platform_defaults.h"
#include "types/implemented/tile_kind.h"
#include "world/global_space.h"

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

    for (Index__u32 index_of__tile = 0;
            index_of__tile
            < CHUNK__QUANTITY_OF__TILES;
            index_of__tile++) {
        p_chunk->tiles[index_of__tile] =
        (Tile){
            Tile_Kind__Grass,
            Tile_Cover_Kind__None
        };
    }
}
