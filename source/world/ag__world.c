#include "world/ag__world.h"
#include "client.h"
#include "game.h"
#include "platform_defines.h"
#include "world/global_space.h"
#include "world/local_space.h"
#include "world/local_space_manager.h"

bool is_ag_world__loaded(
        Game *p_game) {
    Client *p_local_client =
        get_p_local_client_by__from__game(p_game);
    if (!p_local_client) {
        return false;
    }
    Quantity__u32 quantity_of__loaded_spaces = 0;
    for (Index__u32 index_of__local_space = 0;
            index_of__local_space
            < VOLUME_OF__LOCAL_SPACE_MANAGER;
            index_of__local_space++) {
        Local_Space *p_local_space =
            &get_p_local_space_manager_from__client(p_local_client)
            ->local_spaces[index_of__local_space];
        Global_Space *p_global_space =
            get_p_global_space_from__local_space(p_local_space);
        if (!p_global_space)
            continue;
        if (is_global_space__awaiting_construction(p_global_space)
                || is_global_space__constructing(p_global_space)) {
            return false;
        }
        if (is_global_space__active(p_global_space))
            quantity_of__loaded_spaces++;
    }
    return quantity_of__loaded_spaces > 0;
}
