#include "game_action/override/tcp/game_action__tcp_connect__accept__ag.h"
#include "collisions/hitbox_aabb.h"
#include "collisions/hitbox_aabb_manager.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "entity/entity_manager.h"
#include "game.h"
#include "game_action/game_action.h"
#include "game_action/game_action_logic_entry.h"
#include "game_action/game_action_logic_table.h"
#include "process/process.h"
#include "types/implemented/entity_kind.h"
#include "types/implemented/game_action_kind.h"
#include "game_action/core/entity/game_action__entity__spawn.h"
#include "vectors.h"

void m_process__game_action__tcp_connect__accept__ag__outbound_server(
        Process *p_this_process,
        Game *p_game) {
    Game_Action *p_game_action =
        (Game_Action*)p_this_process->p_process_data;
    Identifier__u32 uuid__u32 =
        get_client_uuid_from__game_action(p_game_action);

    Entity *p_entity =
        get_p_entity_by__uuid_from__entity_manager(
                get_p_entity_manager_from__game(p_game), 
                uuid__u32);

    if (!p_entity) {
        debug_error("m_process__game_action__tcp_connect__accept__ag, p_entity == 0.");
        fail_process(p_this_process);
        return;
    }

    Hitbox_AABB *p_hitbox_aabb =
        get_p_hitbox_aabb_by__entity_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(p_game), 
                p_entity);

    if (!p_hitbox_aabb) {
        debug_error("m_process__game_action__tcp_connect__accept__ag, p_hitbox_aabb == 0.");
        fail_process(p_this_process);
        return;
    }

    set_entity_as__enabled(p_entity);
    set_hitbox_aabb_as__active(p_hitbox_aabb);

    broadcast_game_action__entity__spawn(
            p_game,
            GET_UUID_P(p_entity),
            Entity_Kind__Player,
            VECTOR__3i32F4__OUT_OF_BOUNDS);

    complete_process(p_this_process);
    return;
}

void register_game_action__tcp_connect__accept_for__server__ag(
        Game_Action_Logic_Table *p_game_action_logic_table) {
    initialize_game_action_logic_entry_as__message(
            get_p_game_action_logic_entry_by__game_action_kind(
                p_game_action_logic_table, 
                Game_Action_Kind__TCP_Connect__Accept));
    initialize_game_action_logic_entry(
            get_p_game_action_logic_entry_by__game_action_kind(
                p_game_action_logic_table, 
                Game_Action_Kind__TCP_Connect__Accept), //override core 
            GAME_ACTION_FLAGS__OUTBOUND_SANITIZE
            | GAME_ACTION_FLAGS__BIT_IS_WITH_PROCESS
            | GAME_ACTION_FLAGS__BIT_IS_PROCESSED_ON_INVOCATION_OR_RESPONSE,
            GAME_ACTION_FLAG_MASK__OUTBOUND_SANITIZE,
            GAME_ACTION_FLAGS__INBOUND_SANITIZE,
            GAME_ACTION_FLAG_MASK__INBOUND_SANITIZE,
            PROCESS_PRIORITY__0_MAXIMUM,
            m_process__game_action__tcp_connect__accept__ag__outbound_server, 
            PROCESS_FLAGS__NONE,
            0,
            0);
}
