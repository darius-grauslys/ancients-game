#include "scene/implemented/scene__multiplayer.h"
#include "defines.h"
#include "defines_weak.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/gfx_context.h"
#include "rendering/graphics_window.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "game.h"
#include "types/implemented/scene_kind.h"
#include "ui/ui_ag__text.h"
#include "ui/ui_ag__text_box.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "ui/ag_fonts.h"
#include "ui/ui_ag__button.h"
#include "ui/ui_text.h"
#include "ui/ui_tile_map_manager.h"
#include "vectors.h"

static Graphics_Window *_p_graphics_window__multiplayer = 0;

static void m_ui_button__clicked_handler__back(
        UI_Element *p_this_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    set_active_scene_for__scene_manager(
            get_p_scene_manager_from__game(p_game), 
            Scene_Kind__None);
}

static void m_ui_button__clicked_handler__connect(
        UI_Element *p_this_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    debug_info("m_ui_button__clicked_handler__connect");
}

void m_load_scene_as__multiplayer_handler(
        Scene *p_this_scene,
        Game *p_game) {
    _p_graphics_window__multiplayer =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAG__SIZE_256x256);

    if (!_p_graphics_window__multiplayer) {
        debug_error("m_load_scene_as__singleplayer_handler, failed to allocate _p_graphics_window__singleplayer.");
        return;
    }

    set_graphics_window__ui_tile_map(
            _p_graphics_window__multiplayer, 
            allocate_ui_tile_map_with__ui_tile_map_manager(
                get_p_ui_tile_map_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                UI_Tile_Map_Size__Large));

    set_graphics_window__ui_tile_map__texture(
            _p_graphics_window__multiplayer, 
            get_uuid_of__aliased_texture(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__ui));

    allocate_ui_manager_for__graphics_window(
            get_p_gfx_context_from__game(p_game), 
            _p_graphics_window__multiplayer);

    make_ag_button(
            p_game, 
            _p_graphics_window__multiplayer, 
            get_p_ui_manager_from__graphics_window(
                _p_graphics_window__multiplayer), 
            m_ui_button__clicked_handler__back, 
            get_vector__3i32(24, 256 - 16, 0), 
            48, 
            32, 
            get_AG_font__large(), 
            "BACK");

    make_ag_text(
            p_game, 
            _p_graphics_window__multiplayer, 
            get_vector__3i32(48, 168 - 24, 0),
            96, 48, 
            "IP Address:",
            sizeof("IP Address:"));

    make_ag_text_box(
            p_game, 
            _p_graphics_window__multiplayer, 
            get_p_ui_manager_from__graphics_window(
                _p_graphics_window__multiplayer), 
            get_vector__3i32(96+32, 144, 0), 
            128, 32, 
            get_AG_font__large(), 
            15);

    make_ag_button(
            p_game, 
            _p_graphics_window__multiplayer, 
            get_p_ui_manager_from__graphics_window(
                _p_graphics_window__multiplayer), 
            m_ui_button__clicked_handler__connect, 
            get_vector__3i32(192, 16, 0), 
            128, 
            32, 
            get_AG_font__large(), 
            "CONNECT");
}

void m_enter_scene_as__multiplayer_handler(
        Scene *p_this_scene,
        Game *p_game) {
    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        manage_game__pre_render(p_game);

        poll_ui_manager__update(
                _p_graphics_window__multiplayer
                ->p_ui_manager, 
                p_game, 
                _p_graphics_window__multiplayer);

        compose_graphic_windows_in__graphics_window_manager(p_game);
        render_graphic_windows_in__graphics_window_manager(p_game);

        manage_game__post_render(p_game);
    }
}

void m_unload_scene_as__multiplayer_handler(
        Scene *p_this_scene,
        Game *p_game) {
    release_graphics_window_from__graphics_window_manager(
            p_game, 
            _p_graphics_window__multiplayer);
}

void register_scene__multiplayer(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
            Scene_Kind__Multiplayer, 
            m_load_scene_as__multiplayer_handler, 
            m_enter_scene_as__multiplayer_handler, 
            m_unload_scene_as__multiplayer_handler);
}
