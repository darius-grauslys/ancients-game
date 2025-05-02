#include "scene/implemented/scene__world_save.h"
#include "client.h"
#include "defines.h"
#include "defines_weak.h"
#include "rendering/ag__graphics_window.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "game.h"
#include "types/implemented/scene_kind.h"
#include "rendering/graphics_window_manager.h"
#include "ui/ui_ag__text.h"
#include "ui/ui_text.h"
#include "vectors.h"
#include "world/local_space_manager.h"

Graphics_Window *_p_graphics_window__world_save = 0;

UI_Element *_p_ui_element__saving_text = 0;

typedef enum Saving_Text_State {
    Saving_Text_State__SavingDot,
    Saving_Text_State__SavingDotDot,
    Saving_Text_State__SavingDotDotDot,
    Saving_Text_State__SavingDotDotDotDot,
    Saving_Text_State__Failed,
} Saving_Text_State;
static Saving_Text_State state_of__saving_text =
    Saving_Text_State__SavingDot;

void m_load_scene_as__world_save_handler(
        Scene *p_this_scene,
        Game *p_game) {
    _p_graphics_window__world_save =
        make_AG_graphics_window_with__composition_texture(
                p_game, 
                name_of__texture__ui, 
                IDENTIFIER__UNKNOWN__u32, 
                true, 
                false);

    _p_ui_element__saving_text =
        make_ag_text(
                p_game, 
                _p_graphics_window__world_save, 
                get_vector__3i32(128, 128, 0), 
                128, 
                32, 
                "Saving.   ", 
                sizeof("Saving.   "));
}

static Timer__u8 _tick_timer__saving_text;
static Timer__u8 _tick_timer__failed_text;

void m_enter_scene_as__world_save_handler(
        Scene *p_this_scene,
        Game *p_game) {
    initialize_timer_u8(
            &_tick_timer__saving_text,
            32);
    initialize_timer_u8(
            &_tick_timer__failed_text,
            255);
    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        manage_game__pre_render(p_game);

        Quantity__u32 quantity_of__clients_connected =
            get_quantity_of__clients_connect_to__game(p_game);
        if (!quantity_of__clients_connected) {
            set_active_scene_for__scene_manager(
                    get_p_scene_manager_from__game(p_game), 
                    Scene_Kind__None);
        }

        Client *p_client =
            get_p_client_by__index_from__game(
                    p_game, 
                    (quantity_of__clients_connected > 1)
                    ? 1
                    : 0);

        if (is_local_space_manager__loaded(
                    p_game, 
                    get_p_local_space_manager_from__client(p_client))) {
            if (!is_client__saving(p_client)) {
                save_client(
                        p_game, 
                        p_client);
            }
        }

        if (poll_timer_u8(&_tick_timer__saving_text)) {
            loop_timer_u8(&_tick_timer__saving_text);
            switch (state_of__saving_text) {
                default:
                case Saving_Text_State__SavingDot:
                    insert_c_str_into__ui_text(
                            _p_ui_element__saving_text, 
                            "Saving.   ", 
                            sizeof("Saving.   "), 
                            0);
                    set_cursor_of__ui_text(
                            _p_ui_element__saving_text, 
                            sizeof("Saving") - 1);
                    break;
                case Saving_Text_State__SavingDotDot:
                case Saving_Text_State__SavingDotDotDot:
                case Saving_Text_State__SavingDotDotDotDot:
                    append_symbol_into__ui_text(
                            _p_ui_element__saving_text, 
                            '.');
                    break;
                case Saving_Text_State__Failed:
                    insert_c_str_into__ui_text(
                            _p_ui_element__saving_text, 
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
            if (state_of__saving_text != Saving_Text_State__Failed) {
                state_of__saving_text =
                    (state_of__saving_text + 1)
                    & MASK(2)
                    ;
            }
        }

        compose_graphic_windows_in__graphics_window_manager(p_game);
        render_graphic_windows_in__graphics_window_manager(p_game);

        manage_game__post_render(p_game);
    }
}

void m_unload_scene_as__world_save_handler(
        Scene *p_scene,
        Game *p_game) {
    release_graphics_window_from__graphics_window_manager(
            p_game, 
            _p_graphics_window__world_save);
}

void register_scene__world_save(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
            Scene_Kind__World_Save, 
            m_load_scene_as__world_save_handler, 
            m_enter_scene_as__world_save_handler, 
            m_unload_scene_as__world_save_handler);
}
