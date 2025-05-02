#include "world/implemented/chunk_generator_registrar.h"
#include "types/implemented/chunk_generator_kind.h"
#include "world/chunk_generator_table.h"
#include "world/implemented/ag__chunk_generator_overworld.h"

void register_chunk_generators(
        Chunk_Generator_Table *p_chunk_generator_table) {
    register_chunk_generator_into__chunk_generator_table(
            p_chunk_generator_table, 
            Chunk_Generator_Kind__Overworld, 
            f_chunk_generator__overworld);
}
