#include "scene/implemented/scene__world_load.h"
#include "defines.h"
#include "rendering/ag__graphics_window.h"
#include "rendering/graphics_window_manager.h"
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
#include "world/implemented/chunk_generator_registrar.h"
#include "world/world.h"
#include "process/process.h"
#include "game_action/implemented/game_action_registrar.h"

Graphics_Window *_p_graphics_window__world_load = 0;

UI_Element *_p_ui_element__loading_text = 0;

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

    register_game_actions__offline(
            get_p_game_action_logic_table_from__game(p_game));

    allocate_client_pool_for__game(
            p_game, 
            0, 
            1);

    _p_graphics_window__world_load =
        make_AG_graphics_window_with__composition_texture(
                p_game, 
                name_of__texture__ui, 
                IDENTIFIER__UNKNOWN__u32, 
                true, 
                false);

    _p_ui_element__loading_text =
        make_ag_text(
                p_game, 
                _p_graphics_window__world_load, 
                get_vector__3i32(128, 128, 0), 
                128, 
                32, 
                "Loading.   ", 
                sizeof("Loading.   "));
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

    Process *p_process__load_client =
        load_client(
                p_game, 
                0);
    if (!p_process__load_client) {
        state_of__loading_text =
            Loading_Text_State__Failed;
    }
    Process *p_process__load_world = 0;

    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        manage_game__pre_render(p_game);

        if (p_process__load_client) {
            if (is_process__complete(p_process__load_client)) {
                p_process__load_world = 
                    load_world(p_game);
                if (!p_process__load_world) {
                    state_of__loading_text =
                        Loading_Text_State__Failed;
                }
                p_process__load_client = 0;
            } else if (is_process__failed(p_process__load_client)) {
                state_of__loading_text =
                    Loading_Text_State__Failed;
                p_process__load_client = 0;
            }
        }
        if (p_process__load_world) {
            if (is_process__complete(p_process__load_world)) {
                set_active_scene_for__scene_manager(
                        get_p_scene_manager_from__game(p_game), 
                        Scene_Kind__World);
            } else if (is_process__failed(p_process__load_world)) {
                state_of__loading_text =
                    Loading_Text_State__Failed;
            }
        }

        if (poll_timer_u8(&_tick_timer__loading_text)) {
            loop_timer_u8(&_tick_timer__loading_text);
            switch (state_of__loading_text) {
                default:
                case Loading_Text_State__LoadingDot:
                    insert_c_str_into__ui_text(
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
                            _p_ui_element__loading_text, 
                            '.');
                    break;
                case Loading_Text_State__Failed:
                    insert_c_str_into__ui_text(
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

        // poll_ui_manager__update(
        //         _p_graphics_window__world_load
        //         ->p_ui_manager, 
        //         p_game, 
        //         _p_graphics_window__world_load);

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
