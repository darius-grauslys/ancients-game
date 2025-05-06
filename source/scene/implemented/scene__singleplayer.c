#include "scene/implemented/scene__singleplayer.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "rendering/ag__graphics_window.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/gfx_context.h"
#include "rendering/graphics_window.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "game.h"
#include "types/implemented/scene_kind.h"
#include "types/implemented/ui_tile_kind.h"
#include "ui/ui_ag__slider.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "ui/ui_tile_map.h"
#include "ui/ag_fonts.h"
#include "ui/ui_ag__button.h"
#include "ui/ui_slider.h"
#include "ui/ui_tile_map_manager.h"
#include "vectors.h"
#include "serialization/game_directory.h"
#include "world/world.h"

static Graphics_Window *_p_graphics_window__singleplayer = 0;
static Graphics_Window *p_graphics_window__slider = 0;

static void m_ui_button__clicked_handler__back(
        UI_Element *p_this_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    set_active_scene_for__scene_manager(
            get_p_scene_manager_from__game(p_game), 
            Scene_Kind__None);
}

static void m_ui_button__clicked_handler__world(
        UI_Element *p_this_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    initialize_world(
            p_game, 
            get_p_world_from__game(p_game));
    set_name_of__world(
            get_p_world_from__game(p_game), 
            get_child_of__ui_element(p_this_ui_element)
                ->pM_char_buffer);
    set_active_scene_for__scene_manager(
            get_p_scene_manager_from__game(
                p_game), 
            Scene_Kind__World_Load);
}

static void m_ui_button__clicked_handler__new_world(
        UI_Element *p_this_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    set_active_scene_for__scene_manager(
            get_p_scene_manager_from__game(
                p_game), 
            Scene_Kind__World_New);
}

void m_load_scene_as__singleplayer_handler(
        Scene *p_this_scene,
        Game *p_game) {
    _p_graphics_window__singleplayer =
        make_AG_graphics_window_with__composition_texture(
                p_game, 
                name_of__texture__ui, 
                IDENTIFIER__UNKNOWN__u32,
                true,
                true);

    if (!_p_graphics_window__singleplayer) {
        debug_error("m_load_scene_as__singleplayer_handler, failed to allocate _p_graphics_window__singleplayer.");
        return;
    }

    make_ag_button(
            p_game, 
            _p_graphics_window__singleplayer, 
            get_p_ui_manager_from__graphics_window(
                _p_graphics_window__singleplayer), 
            m_ui_button__clicked_handler__back, 
            get_vector__3i32(-128 + 24, 128 - 16, 0), 
            48, 
            32, 
            get_AG_font__large(), 
            "BACK");

    // TODO: elements in graphics_window under slider
    // need the input offset - do this in Lavender
    UI_Element *p_ui_slider =
        make_ag_slider(
            p_game, 
            _p_graphics_window__singleplayer, 
            get_p_ui_manager_from__graphics_window(
                _p_graphics_window__singleplayer), 
            m_ui_slider__dragged_handler__gfx_window__default, 
            get_vector__3i32(220 - 128 + 12, (192 - 128 - 16)/2 + 8, 0), 
            get_vector__3i32(0, -512, 0),
            24, 
            192 - 16,
            false);

    p_graphics_window__slider =
        make_AG_graphics_window_with__composition_texture(
                p_game, 
                name_of__texture__ui, 
                GET_UUID_P(p_ui_slider), 
                true, 
                false);

    set_position_3i32_of__graphics_window(
            p_game, 
            p_graphics_window__slider, 
            get_vector__3i32(0,0,-7));

    fill_ui_tile_map(
            get_ui_tile_map_from__graphics_window(
                _p_graphics_window__singleplayer), 
            (UI_Tile){UI_Tile_Kind__Background_Fill});
    fill_ui_tile_map_in__this_region(
            get_ui_tile_map_from__graphics_window(
                _p_graphics_window__singleplayer), 
            (UI_Tile){0}, 
            6, 
            0, 
            20, 32);
    fill_ui_tile_map(
            get_ui_tile_map_from__graphics_window(
                p_graphics_window__slider), 
            (UI_Tile){UI_Tile_Kind__Button_Toggled_Fill});

    char directory_names[1024];
    memset(directory_names, 0, sizeof(directory_names));
    Quantity__u32 max_length_of__directory_name = 32;

    IO_path path_to__saves;
    PLATFORM_get_base_directory(path_to__saves);
    append_path(
            path_to__saves, 
            "save");

    Quantity__u32 quantity_of__directories =
        PLATFORM_get_directories(
                get_p_PLATFORM_file_system_context_from__game(p_game), 
                path_to__saves, 
                directory_names, 
                sizeof(directory_names), 
                max_length_of__directory_name);

    for (Index__u32 index_of__directory = 0;
            index_of__directory
            < quantity_of__directories;
            index_of__directory++) {
        make_ag_button(
                p_game, 
                p_graphics_window__slider, 
                get_p_ui_manager_from__graphics_window(
                    p_graphics_window__slider), 
                m_ui_button__clicked_handler__world, 
                get_vector__3i32(
                    0,
                    128 - 16 - (index_of__directory * 48), 
                    0),
                96, 
                32, 
                get_AG_font__large(), 
                &directory_names[index_of__directory * 32]);
    }

    make_ag_button(
            p_game, 
            p_graphics_window__slider, 
            get_p_ui_manager_from__graphics_window(
                p_graphics_window__slider), 
            m_ui_button__clicked_handler__new_world, 
            get_vector__3i32(
                0,
                128 - 16 - (quantity_of__directories * 48), 
                0),
            96, 
            32, 
            get_AG_font__large(), 
            "NEW WORLD");
}

void m_enter_scene_as__singleplayer_handler(
        Scene *p_this_scene,
        Game *p_game) {
    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        manage_game__pre_render(p_game);

        poll_ui_manager__update(
                _p_graphics_window__singleplayer
                ->p_ui_manager, 
                p_game, 
                _p_graphics_window__singleplayer);
        poll_ui_manager__update(
                p_graphics_window__slider
                ->p_ui_manager, 
                p_game, 
                p_graphics_window__slider);

        compose_graphic_windows_in__graphics_window_manager(p_game);
        render_graphic_windows_in__graphics_window_manager(p_game);

        manage_game__post_render(p_game);
    }
}

void m_unload_scene_as__singleplayer_handler(
        Scene *p_this_scene,
        Game *p_game) {
    release_graphics_window_from__graphics_window_manager(
            p_game, 
            _p_graphics_window__singleplayer);
}

void register_scene__singleplayer(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
            Scene_Kind__Singleplayer, 
            m_load_scene_as__singleplayer_handler, 
            m_enter_scene_as__singleplayer_handler, 
            m_unload_scene_as__singleplayer_handler);
}
