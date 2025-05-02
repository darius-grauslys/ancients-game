#include "scene/implemented/scene__world.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "game.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/gfx_context.h"
#include "client.h"
#include "rendering/aliased_texture_manager.h"
#include "world/local_space.h"
#include "world/chunk.h"

Graphics_Window *ptr_array_of__p_graphics_windows[] = {
    0, // world, ground
    0, // world, cover
    0, // world, ui
};

PLATFORM_Texture *ptr_array_of__p_PLATFORM_textures_for__world[] = {
    0, // ground
    0, // cover
    0, // ui
};

Graphics_Window **p_ptr_graphics_window__ground = 
        &ptr_array_of__p_graphics_windows[0];
Graphics_Window **p_ptr_graphics_window__cover = 
        &ptr_array_of__p_graphics_windows[1];
Graphics_Window **p_ptr_graphics_window__ui = 
        &ptr_array_of__p_graphics_windows[2];

PLATFORM_Texture **p_ptr_PLATFORM_texture__ground_tileset =
        &ptr_array_of__p_PLATFORM_textures_for__world[0];
PLATFORM_Texture **p_ptr_PLATFORM_texture__cover_tileset =
        &ptr_array_of__p_PLATFORM_textures_for__world[1];
PLATFORM_Texture **p_ptr_PLATFORM_texture__ui_tileset =
        &ptr_array_of__p_PLATFORM_textures_for__world[2];

void m_load_scene_as__world_handler(
        Scene *p_this_scene,
        Game *p_game) {
    register_aliased_textures_for__world(
            get_p_aliased_texture_manager_from__game(p_game), 
            p_game);
    register_aliased_textures_for__entities(
            get_p_aliased_texture_manager_from__game(p_game), 
            p_game);

    *p_ptr_PLATFORM_texture__ground_tileset =
        get_p_PLATFORM_texture_by__alias(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__ground);

    *p_ptr_PLATFORM_texture__cover_tileset =
        get_p_PLATFORM_texture_by__alias(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__cover);

    *p_ptr_PLATFORM_texture__ui_tileset =
        get_p_PLATFORM_texture_by__alias(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__ui);

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

void f_tile_render_kernel__TO_REMOVE_LATER(
        Local_Space *p_local_space,
        Tile_Render_Kernel_Result *p_tile_kernel_render_results,
        Quantity__u32 quantity_of__tile_kernel_render_results,
        u8 x__local,
        u8 y__local,
        u8 z__local) {
    Tile *p_tile = 
        get_p_tile_from__chunk_using__u8(
                get_p_chunk_from__local_space(p_local_space), 
                x__local, 
                y__local, 
                z__local);

    p_tile_kernel_render_results[0].index_of__texture =
        p_tile->the_kind_of__tile;
    p_tile_kernel_render_results[1].index_of__texture =
        p_tile->the_kind_of__tile_cover;
}


void m_enter_scene_as__world_handler(
        Scene *p_this_scene,
        Game *p_game) {
    Client *p_client = get_p_local_client_by__from__game(p_game);

    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        manage_game__pre_render(p_game);

        PLATFORM_compose_world(
                get_p_gfx_context_from__game(p_game), 
                ptr_array_of__p_graphics_windows, 
                get_p_local_space_manager_from__client(p_client), 
                ptr_array_of__p_PLATFORM_textures_for__world, 
                3, 
                f_tile_render_kernel__TO_REMOVE_LATER);

        render_graphic_windows_in__graphics_window_manager(
                p_game);
        manage_game__post_render(p_game);
    }
}

void register_scene__world(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
            Scene_Kind__World, 
            m_load_scene_as__world_handler, 
            m_enter_scene_as__world_handler, 
            0);
}
