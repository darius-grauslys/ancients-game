#include "scene/implemented/scene__world.h"
#include "defines.h"
#include "defines_weak.h"
#include "platform.h"
#include "platform_defines.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "rendering/implemented/sprite_animation_registrar.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "game.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/gfx_context.h"
#include "client.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/graphics_window.h"
#include "types/implemented/scene_kind.h"
#include "types/implemented/tile_cover_kind.h"
#include "world/chunk_vectors.h"
#include "world/global_space.h"
#include "world/implemented/f_tile_render_kernel.h"
#include "world/local_space.h"
#include "world/chunk.h"
#include "input/input.h"
#include "world/camera.h"
#include "world/world.h"
#include "collisions/hitbox_aabb_manager.h"
#include "collisions/hitbox_aabb.h"
#include "world/local_space_manager.h"
#include "entity/entity_manager.h"

Graphics_Window *ptr_array_of__p_graphics_windows[] = {
    0, // world, ground
    0, // world, cover
    0, // world, cover_over_sprites
};

Texture array_of__textures_for__world[] = {
    (Texture){0}, // ground
    (Texture){0}, // cover
    (Texture){0}, // cover
};

Graphics_Window *p_graphics_window__ui;

Graphics_Window **p_ptr_graphics_window__ground = 
        &ptr_array_of__p_graphics_windows[0];
Graphics_Window **p_ptr_graphics_window__cover = 
        &ptr_array_of__p_graphics_windows[1];
Graphics_Window **p_ptr_graphics_window__cover_over_sprites = 
        &ptr_array_of__p_graphics_windows[2];

Texture *p_texture__ground_tileset =
        &array_of__textures_for__world[0];
Texture *p_texture__cover_tileset =
        &array_of__textures_for__world[1];
Texture *p_texture__cover_over_sprites_tileset =
        &array_of__textures_for__world[2];

static Camera _camera;

void m_load_scene_as__world_handler(
        Scene *p_this_scene,
        Game *p_game) {
    register_aliased_textures_for__world(
            get_p_aliased_texture_manager_from__game(p_game), 
            p_game);
    register_aliased_textures_for__entities(
            get_p_aliased_texture_manager_from__game(p_game), 
            p_game);

    if (get_texture_by__alias(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__ground,
                p_texture__ground_tileset)) {
        debug_error("m_load_scene_as__world_handler, failed to load ground texture.");
    }

    if (get_texture_by__alias(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__cover,
                p_texture__cover_tileset)) {
        debug_error("m_load_scene_as__world_handler, failed to load cover texture.");
    }

    if (get_texture_by__alias(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__cover,
                p_texture__cover_over_sprites_tileset)) {
        debug_error("m_load_scene_as__world_handler, failed to load cover_over_sprites texture.");
    }

    *p_ptr_graphics_window__ground =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAGS(
                    TEXTURE_FLAG__SIZE_256x256,
                    0,
                    TEXTURE_FLAG__FORMAT__RGBA8888));
    allocate_sprite_manager_for__graphics_window(
            get_p_gfx_context_from__game(p_game), 
            *p_ptr_graphics_window__ground);
    register_sprite_animations(
            get_p_sprite_manager_from__graphics_window(
                *p_ptr_graphics_window__ground));

    get_p_world_from__game(p_game)
        ->p_graphics_window_for__world = *p_ptr_graphics_window__ground;

    *p_ptr_graphics_window__cover =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAGS(
                    TEXTURE_FLAG__SIZE_256x256,
                    0,
                    TEXTURE_FLAG__FORMAT__RGBA8888));

    *p_ptr_graphics_window__cover_over_sprites =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAGS(
                    TEXTURE_FLAG__SIZE_256x256,
                    0,
                    TEXTURE_FLAG__FORMAT__RGBA8888));

    set_position_3i32_of__graphics_window(
            p_game, 
            *p_ptr_graphics_window__cover, 
            get_vector__3i32(0, 0, 1));

    set_position_3i32_of__graphics_window(
            p_game, 
            *p_ptr_graphics_window__cover_over_sprites, 
            get_vector__3i32(0, TILE__WIDTH_AND__HEIGHT_IN__PIXELS -2, 1));

    p_graphics_window__ui =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAGS(
                    TEXTURE_FLAG__SIZE_256x256,
                    0,
                    TEXTURE_FLAG__FORMAT__RGBA8888));

    set_graphics_window__ui_tile_map__texture(
            p_graphics_window__ui, 
            get_uuid_of__aliased_texture(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__ui));

    Hitbox_AABB *p_hitbox_aabb =
        get_p_hitbox_aabb_by__uuid_u32_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(p_game),
                GET_UUID_P(get_p_local_client_by__from__game(p_game)));

    initialize_camera(
            &_camera, 
            get_position_3i32F4_of__hitbox_aabb(p_hitbox_aabb), 
            m_camera_handler__follow__default, 
            CAMERA_FULCRUM__WIDTH,
            CAMERA_FULCRUM__WIDTH,
            i32_to__i32F20(-1), 
            i32_to__i32F20(100));

    set_p_camera_of__graphics_window(
            *p_ptr_graphics_window__ground,
            &_camera);

    allocate_entity_in__entity_manager(
            p_game, 
            get_p_world_from__game(p_game), 
            get_p_entity_manager_from__game(p_game), 
            Entity_Kind__Skeleton);
}

void m_enter_scene_as__world_handler(
        Scene *p_this_scene,
        Game *p_game) {
    Client *p_client = get_p_local_client_by__from__game(p_game);
    Hitbox_AABB *p_hitbox_aabb =
        get_p_hitbox_aabb_by__uuid_u32_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(
                    p_game), 
                GET_UUID_P(p_client));

    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        manage_game__pre_render(p_game);

        manage_world(
                p_game,
                *p_ptr_graphics_window__ground);

        PLATFORM_compose_world(
                get_p_gfx_context_from__game(p_game), 
                ptr_array_of__p_graphics_windows, 
                get_p_local_space_manager_from__client(p_client), 
                array_of__textures_for__world, 
                sizeof(ptr_array_of__p_graphics_windows)
                / sizeof(Graphics_Window*), 
                f_tile_render_kernel);

        render_graphic_windows_in__graphics_window_manager(
                p_game);
        manage_game__post_render(p_game);
    }
}

void m_unload_scene_as__world_handler(
        Scene *p_this_scene,
        Game *p_game) {
    release_graphics_window_from__graphics_window_manager(
            p_game, 
            *p_ptr_graphics_window__ground);
    release_graphics_window_from__graphics_window_manager(
            p_game, 
            *p_ptr_graphics_window__cover);
    release_graphics_window_from__graphics_window_manager(
            p_game, 
            p_graphics_window__ui);
}

void register_scene__world(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
            Scene_Kind__World, 
            m_load_scene_as__world_handler, 
            m_enter_scene_as__world_handler, 
            m_unload_scene_as__world_handler);
}
