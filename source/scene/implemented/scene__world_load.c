#include "scene/implemented/scene__world_load.h"
#include "client.h"
#include "collisions/collision_node.h"
#include "collisions/hitbox_aabb.h"
#include "defines.h"
#include "entity/entity.h"
#include "numerics.h"
#include "rendering/ag__graphics_window.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/graphics_window.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "game.h"
#include "timer.h"
#include "types/implemented/scene_kind.h"
#include "ui/ui_ag__text.h"
#include "ui/ui_manager.h"
#include "ui/ui_text.h"
#include "vectors.h"
#include "world/chunk_vectors.h"
#include "world/global_space.h"
#include "world/global_space_manager.h"
#include "world/implemented/ag__chunk_generator_overworld.h"
#include "world/implemented/chunk_generator_registrar.h"
#include "world/implemented/tile_logic_table_registrar.h"
#include "world/local_space_manager.h"
#include "world/world.h"
#include "process/process.h"
#include "game_action/implemented/game_action_registrar.h"
#include "game_action/core/world/game_action__world__load_world.h"
#include "game_action/core/world/game_action__world__load_client.h"
#include "entity/entity_manager.h"
#include "entity/f_entity_initializer.h"

static Graphics_Window *_p_graphics_window__world_load = 0;

static UI_Manager *_p_ui_manager = 0;

static UI_Element *_p_ui_element__loading_text = 0;

typedef enum Loading_Text_State {
    Loading_Text_State__LoadingDot,
    Loading_Text_State__LoadingDotDot,
    Loading_Text_State__LoadingDotDotDot,
    Loading_Text_State__LoadingDotDotDotDot,
    Loading_Text_State__Failed,
} Loading_Text_State;
static Loading_Text_State state_of__loading_text =
    Loading_Text_State__LoadingDot;

void m_load_scene_as__world_load_handler(
        Scene *p_this_scene,
        Game *p_game) {

    register_tile_logic_tables(
            p_game, 
            get_p_tile_logic_table_from__world(
                get_p_world_from__game(p_game)));
    
    set_entity_initializer_in__entity_manager(
            get_p_entity_manager_from__game(p_game), 
            f_entity_initializer__ag);

    _p_graphics_window__world_load =
        make_AG_graphics_window_with__composition_texture(
                p_game, 
                name_of__texture__ui, 
                IDENTIFIER__UNKNOWN__u32, 
                true, 
                false);

    // TODO: null check
    _p_ui_manager = get_p_ui_manager_from__graphics_window(
            p_game, 
            _p_graphics_window__world_load);

    _p_ui_element__loading_text =
        make_ag_text(
                p_game, 
                _p_graphics_window__world_load, 
                get_vector__3i32(128, 128, 0), 
                128, 
                32, 
                "Loading.   ", 
                sizeof("Loading.   "));

    if (!is_world_allocated_for__game(p_game)) {
        state_of__loading_text =
            Loading_Text_State__Failed;
    }
}

static Timer__u8 _tick_timer__loading_text;
static Timer__u8 _tick_timer__failed_text;

void m_enter_scene_as__world_load_handler(
        Scene *p_this_scene,
        Game *p_game) {
    initialize_timer_u8(
            &_tick_timer__loading_text,
            32);
    initialize_timer_u8(
            &_tick_timer__failed_text,
            24);
    register_chunk_generators(
            get_p_chunk_generation_table_from__world(
                get_p_world_from__game(p_game)));

    Client *p_client =
        get_p_local_client_by__from__game(p_game);

    dispatch_game_action__world__load_world(
            p_game, 
            GET_UUID_P(get_p_local_client_by__from__game(p_game)));
    dispatch_game_action__world__load_client(
            p_game, 
            GET_UUID_P(get_p_local_client_by__from__game(p_game)));

    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        poll_multiplayer(p_game);
        manage_game__pre_render(p_game);

        if (is_client__active(p_client)) {
            set_active_scene_for__scene_manager(
                    get_p_scene_manager_from__game(p_game), 
                    Scene_Kind__World);
        }

        if (poll_timer_u8(&_tick_timer__loading_text)) {
            loop_timer_u8(&_tick_timer__loading_text);
            switch (state_of__loading_text) {
                default:
                case Loading_Text_State__LoadingDot:
                    insert_c_str_into__ui_text(
                            _p_ui_manager,
                            _p_ui_element__loading_text, 
                            "Loading.   ", 
                            sizeof("Loading.   "), 
                            0);
                    set_cursor_of__ui_text(
                            _p_ui_element__loading_text, 
                            sizeof("Loading") - 1);
                    break;
                case Loading_Text_State__LoadingDotDot:
                case Loading_Text_State__LoadingDotDotDot:
                case Loading_Text_State__LoadingDotDotDotDot:
                    append_symbol_into__ui_text(
                            _p_ui_manager,
                            _p_ui_element__loading_text, 
                            '.');
                    break;
                case Loading_Text_State__Failed:
                    insert_c_str_into__ui_text(
                            _p_ui_manager,
                            _p_ui_element__loading_text, 
                            "Failed.    ", 
                            sizeof("Failed.    "), 
                            0);
                    if (poll_timer_u8(&_tick_timer__failed_text)) {
                        set_active_scene_for__scene_manager(
                                get_p_scene_manager_from__game(p_game), 
                                Scene_Kind__None);
                    }
                    break;
            }
            if (state_of__loading_text != Loading_Text_State__Failed) {
                state_of__loading_text =
                    (state_of__loading_text + 1)
                    & MASK(2)
                    ;
            }
        }

        compose_graphic_windows_in__graphics_window_manager(p_game);
        render_graphic_windows_in__graphics_window_manager(p_game);

        manage_game__post_render(p_game);
    }
}

void m_unload_scene_as__world_load_handler(
        Scene *p_this_scene,
        Game *p_game) {
    release_graphics_window_from__graphics_window_manager(
            p_game, 
            _p_graphics_window__world_load);
}

void register_scene__world_load(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
            Scene_Kind__World_Load, 
            m_load_scene_as__world_load_handler, 
            m_enter_scene_as__world_load_handler, 
            m_unload_scene_as__world_load_handler);
}
