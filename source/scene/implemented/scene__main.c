#include "scene/implemented/scene__main.h"
#include "collisions/hitbox_aabb_manager.h"
#include "defines.h"
#include "defines_weak.h"
#include "rendering/gfx_context.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/graphics_window.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "rendering/font/font_manager.h"
#include "rendering/aliased_texture_manager.h"
#include "ui/ui_manager.h"
#include "ui/ag_fonts.h"
#include "ui/ui_ag__button.h"
#include "ui/ui_tile_map_manager.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "game.h"
#include "types/implemented/scene_kind.h"

static Graphics_Window *_p_main__graphics_window__ui = 0;

static void m_ui_button__clicked_handler__singleplayer(
        UI_Element *p_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    debug_info("singleplayer");
}

static void m_ui_button__clicked_handler__multiplayer(
        UI_Element *p_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    debug_info("multiplayer");
}

static void m_ui_button__clicked_handler__settings(
        UI_Element *p_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    debug_info("settings");
}

static void m_ui_button__clicked_handler__quit(
        UI_Element *p_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    set_active_scene_for__scene_manager(
            get_p_scene_manager_from__game(p_game), 
            Scene_Kind__Unknown);
}

void m_load_scene_as__main_handler(
        Scene *p_this_scene,
        Game *p_game) {
    register_aliased_textures(
            get_p_aliased_texture_manager_from__game(
                p_game), 
            p_game);

    initialize_hitbox_aabb_manager(
            get_p_hitbox_aabb_manager_from__game(p_game));

    _p_main__graphics_window__ui =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAG__SIZE_256x256);

    if (!_p_main__graphics_window__ui) {
        debug_error("m_load_scene_as__main_handler, _p_main__graphics_window__ui failed to allocate.");
        set_active_scene_for__scene_manager(
                get_p_scene_manager_from__game(p_game), 
                Scene_Kind__Unknown);
        return;
    }

    get_AG_font__large()->p_PLATFORM_texture_of__font =
        get_p_PLATFORM_texture_by__alias(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__font__large);

    set_graphics_window__ui_tile_map(
            _p_main__graphics_window__ui, 
            allocate_ui_tile_map_with__ui_tile_map_manager(
                get_p_ui_tile_map_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                UI_Tile_Map_Size__Large));

    set_graphics_window__ui_tile_map__texture(
            _p_main__graphics_window__ui, 
            get_uuid_of__aliased_texture(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__ui));

    allocate_ui_manager_for__graphics_window(
            get_p_gfx_context_from__game(p_game), 
            _p_main__graphics_window__ui);

    make_ag_button(
            p_game, 
            _p_main__graphics_window__ui, 
            get_p_ui_manager_from__graphics_window(
                _p_main__graphics_window__ui), 
            m_ui_button__clicked_handler__singleplayer, 
            get_vector__3i32(128, 128 + 48, 0), 
            128, 
            32, 
            (Font*)get_AG_font__large(), 
            "SINGLEPLAYER");

    make_ag_button(
            p_game, 
            _p_main__graphics_window__ui, 
            get_p_ui_manager_from__graphics_window(
                _p_main__graphics_window__ui), 
            m_ui_button__clicked_handler__multiplayer, 
            get_vector__3i32(128, 128, 0), 
            128, 
            32, 
            (Font*)get_AG_font__large(), 
            "MULTIPLAYER");

    make_ag_button(
            p_game, 
            _p_main__graphics_window__ui, 
            get_p_ui_manager_from__graphics_window(
                _p_main__graphics_window__ui), 
            m_ui_button__clicked_handler__settings, 
            get_vector__3i32(128, 128 - 48, 0), 
            128, 
            32, 
            (Font*)get_AG_font__large(), 
            "SETTINGS");

    make_ag_button(
            p_game, 
            _p_main__graphics_window__ui, 
            get_p_ui_manager_from__graphics_window(
                _p_main__graphics_window__ui), 
            m_ui_button__clicked_handler__quit, 
            get_vector__3i32(128, 128 - 48*2, 0), 
            128, 
            32, 
            (Font*)get_AG_font__large(), 
            "QUIT");
}

void m_enter_scene_as__main_handler(
        Scene *p_this_scene,
        Game *p_game) {
    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        manage_game__pre_render(p_game);

        poll_ui_manager__update(
                _p_main__graphics_window__ui
                ->p_ui_manager, 
                p_game, 
                _p_main__graphics_window__ui);

        compose_graphic_windows_in__graphics_window_manager(p_game);
        render_graphic_windows_in__graphics_window_manager(p_game);

        manage_game__post_render(p_game);
    }
}

void register_scene__main(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
            Scene_Kind__None, 
            m_load_scene_as__main_handler, 
            m_enter_scene_as__main_handler, 
            0);
}
