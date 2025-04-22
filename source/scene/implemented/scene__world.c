#include "scene/implemented/scene__world.h"
#include "defines.h"
#include "defines_weak.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "game.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/gfx_context.h"

Graphics_Window *ptr_array_of__p_graphics_windows[] = {
    0, // world, ground
    0, // world, cover
    0, // world, ui
};

Graphics_Window **p_ptr_graphics_window__ground = 
        &ptr_array_of__p_graphics_windows[0];
Graphics_Window **p_ptr_graphics_window__cover = 
        &ptr_array_of__p_graphics_windows[1];
Graphics_Window **p_ptr_graphics_window__ui = 
        &ptr_array_of__p_graphics_windows[2];

void m_load_scene_as__world_handler(
        Scene *p_this_scene,
        Game *p_game) {
    register_aliased_textures_for__world(
            get_p_aliased_texture_manager_from__game(p_game), 
            p_game);
    register_aliased_textures_for__entities(
            get_p_aliased_texture_manager_from__game(p_game), 
            p_game);

    *p_ptr_graphics_window__ground =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAG__SIZE_256x256);

    *p_ptr_graphics_window__cover =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAG__SIZE_256x256);

    *p_ptr_graphics_window__ui =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAG__SIZE_256x256);
}

void m_enter_scene_as__world_handler(
        Scene *p_this_scene,
        Game *p_game) {
    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        manage_game__pre_render(p_game);
        manage_game__post_render(p_game);
    }
}

void register_scene__world(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
            Scene_Kind__None, 
            m_load_scene_as__world_handler, 
            m_enter_scene_as__world_handler, 
            0);
}
