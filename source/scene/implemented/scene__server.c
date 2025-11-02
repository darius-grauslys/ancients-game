#include "scene/implemented/scene__server.h"
#include "ag__client.h"
#include "client.h"
#include "collisions/hitbox_aabb_manager.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity_manager.h"
#include "game_action/implemented/game_action_registrar.h"
#include "multiplayer/tcp_socket_manager.h"
#include "platform.h"
#include "platform_defines.h"
#include "process/process.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "game.h"
#include "types/implemented/scene_kind.h"
#include "world/implemented/chunk_generator_registrar.h"
#include "world/implemented/tile_logic_table_registrar.h"
#include "world/world.h"
#include "process/process_manager.h"
#include "world/world.h"
#include "multiplayer/server__default.h"
#include "entity/f_entity_initializer.h"

void m_load_scene_as__server_handler(
        Scene *p_this_scene,
        Game *p_game) {
    // register_game_actions__server(
    //         get_p_game_action_logic_table_from__game(p_game));

    begin_multiplayer_for__game(
            p_game, 
            m_poll_tcp_socket_manager_as__server__default);

    set_dispatch_handler_process_for__load_client(
            p_game, 
            m_process__deserialize_client__ag);
    set_dispatch_handler_process_for__save_client(
            p_game, 
            m_process__serialize_client__ag);

    allocate_world_for__game(p_game);
    initialize_world(p_game, get_p_world_from__game(p_game));
    set_name_of__world(
            get_p_world_from__game(p_game), 
            "default");
    set_entity_initializer_in__entity_manager(
            get_p_entity_manager_from__game(p_game), 
            f_entity_initializer__ag);
    register_tile_logic_tables(
            p_game, 
            get_p_tile_logic_table_from__world(
                get_p_world_from__game(p_game)));
    register_chunk_generators(
            get_p_chunk_generation_table_from__world(
                get_p_world_from__game(p_game)));

    allocate_client_pool_for__game(
            p_game, 
            0, 
            MAX_QUANTITY_OF__CLIENTS);
    Process *p_process__load_server_client =
        load_client(p_game, 0);
    if (!p_process__load_server_client) {
        debug_error("m_load_scene_as__server_handler, failed to load client.");
        set_active_scene_for__scene_manager(
                get_p_scene_manager_from__game(p_game), 
                Scene_Kind__Unknown); // quit game.
        return;
    }

    set_client_as__inactive(
            get_p_local_client_by__from__game(p_game));

    while(!is_process__complete(
                p_process__load_server_client)) {
        poll_process_manager(
                get_p_process_manager_from__game(p_game),
                p_game);
    }

    Process *p_process__load_world =
        load_world(p_game);

    while(!is_process__complete(
                p_process__load_world)) {
        poll_process_manager(
                get_p_process_manager_from__game(p_game),
                p_game);
    }

    release_hitbox_aabb_from__hitbox_aabb_manager(
            p_game, 
            get_p_hitbox_aabb_manager_from__game(p_game), 
            get_p_hitbox_aabb_by__uuid_u32_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(p_game), 
                GET_UUID_P(get_p_local_client_by__from__game(p_game))));
}

void m_enter_scene_as__server_handler(
        Scene *p_this_scene,
        Game *p_game) {
    TCP_Socket *p_tcp_socker__server =
        open_server_socket_on__tcp_socket_manager__ipv4(
                get_p_tcp_socket_manager_from__game(p_game), 
                0, 
                55566);
    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        poll_multiplayer(p_game);
        manage_world(p_game, 0);
        manage_game__pre_render(p_game);
        manage_game__post_render(p_game);
    }
}

void m_unload_scene_as__server_load_handler(
        Scene *p_this_scene,
        Game *p_game) {
    save_world(
            get_p_PLATFORM_file_system_context_from__game(p_game), 
            get_p_world_from__game(p_game));
    set_active_scene_for__scene_manager(
            get_p_scene_manager_from__game(p_game), 
            Scene_Kind__Unknown); // quit game.
    return;
}

void register_scene__server(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
#ifdef IS_SERVER
            Scene_Kind__None, 
#else
            Scene_Kind__Server,
#endif
            m_load_scene_as__server_handler, 
            m_enter_scene_as__server_handler, 
            m_unload_scene_as__server_load_handler);
}
