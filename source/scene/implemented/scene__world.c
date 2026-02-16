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
#include "serialization/identifiers.h"
#include "types/implemented/graphics_window_kind.h"
#include "types/implemented/scene_kind.h"
#include "types/implemented/tile_cover_kind.h"
#include "world/chunk_vectors.h"
#include "world/global_space.h"
#include "world/implemented/ag__chunk_generator_overworld.h"
#include "world/implemented/f_tile_render_kernel.h"
#include "world/local_space.h"
#include "world/chunk.h"
#include "input/input.h"
#include "world/camera.h"
#include "world/world.h"
#include "collisions/hitbox_aabb_manager.h"
#include "collisions/hitbox_aabb.h"
#include "world/local_space_manager.h"
#include "world/global_space_manager.h"
#include "entity/entity_manager.h"

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

    Identifier__u32 uuid_of__ground_texture =
        get_uuid_of__aliased_texture(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__ground);

    Identifier__u32 uuid_of__cover_texture =
        get_uuid_of__aliased_texture(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__cover);

    Identifier__u32 uuid_of__cover_over_sprites_texture =
        get_uuid_of__aliased_texture(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture__cover);

    if (is_identifier_u32__invalid(uuid_of__ground_texture)) {
        debug_error("m_load_scene_as__world_handler, failed to load ground texture.");
    }

    if (is_identifier_u32__invalid(uuid_of__cover_texture)) {
        debug_error("m_load_scene_as__world_handler, failed to load cover texture.");
    }

    if (is_identifier_u32__invalid(uuid_of__cover_over_sprites_texture)) {
        debug_error("m_load_scene_as__world_handler, failed to load cover_over_sprites texture.");
    }

    Graphics_Window *p_graphics_window__world =
        get_default_platform_graphics_window(
                get_p_gfx_context_from__game(p_game));
    Graphics_Window *p_graphics_window__ground =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAGS(
                    TEXTURE_FLAG__SIZE_256x256,
                    0,
                    TEXTURE_FLAG__FORMAT__RGBA8888));
    p_this_scene->p_scene_data =
        p_graphics_window__ground;

    Graphics_Window *p_graphics_window__cover =
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
            p_graphics_window__cover,
            128); // TODO: should maybe change
    register_sprite_animations(
            get_p_sprite_context_from__gfx_context(
                get_p_gfx_context_from__game(p_game)));

    get_p_world_from__game(p_game)
        ->p_graphics_window_for__world = p_graphics_window__cover;

    Graphics_Window *p_graphics_window__cover_over_sprites =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAGS(
                    TEXTURE_FLAG__SIZE_256x256,
                    0,
                    TEXTURE_FLAG__FORMAT__RGBA8888));

    set_graphics_window__tile_map__texture(
            p_graphics_window__ground, 
            uuid_of__ground_texture);

    set_graphics_window__tile_map__texture(
            p_graphics_window__cover, 
            uuid_of__cover_texture);

    set_graphics_window__tile_map__texture(
            p_graphics_window__cover_over_sprites, 
            uuid_of__cover_over_sprites_texture);

    set_position_3i32_of__graphics_window(
            p_game, 
            p_graphics_window__ground, 
            get_vector__3i32(0, 0, -1));

    set_position_3i32_of__graphics_window(
            p_game, 
            p_graphics_window__cover, 
            get_vector__3i32(0, 0, 0));

    set_position_3i32_of__graphics_window(
            p_game, 
            p_graphics_window__cover_over_sprites, 
            get_vector__3i32(0, TILE__WIDTH_AND__HEIGHT_IN__PIXELS >> 1, 1));

    Graphics_Window *p_graphics_window__ui =
        allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAGS(
                    TEXTURE_FLAG__SIZE_256x256,
                    0,
                    TEXTURE_FLAG__FORMAT__RGBA8888));

    set_graphics_window_as__parent_to__this_graphics_window(
        get_p_graphics_window_manager_from__gfx_context(
                get_p_gfx_context_from__game(p_game)),
        p_graphics_window__world,
        p_graphics_window__ui);
    set_graphics_window_as__parent_to__this_graphics_window(
        get_p_graphics_window_manager_from__gfx_context(
                get_p_gfx_context_from__game(p_game)),
        p_graphics_window__cover,
        p_graphics_window__cover_over_sprites);
    set_graphics_window_as__parent_to__this_graphics_window(
        get_p_graphics_window_manager_from__gfx_context(
                get_p_gfx_context_from__game(p_game)),
        p_graphics_window__ground,
        p_graphics_window__cover);
    set_graphics_window_as__parent_to__this_graphics_window(
        get_p_graphics_window_manager_from__gfx_context(
                get_p_gfx_context_from__game(p_game)),
        p_graphics_window__world,
        p_graphics_window__ground);

    p_graphics_window__ground->f_PLATFORM_compose_gfx_window =
        PLATFORM_compose_world;
    set_p_camera_of__graphics_window(
            p_graphics_window__ground, 
            &_camera);

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
            i32_to__i32F20(-10), 
            i32_to__i32F20(100));

    set_camera_to__follow(
            &_camera, 
            GET_UUID_P(get_p_local_client_by__from__game(p_game)));

    set_p_camera_of__graphics_window(
            p_graphics_window__ground,
            &_camera);
    set_p_camera_of__graphics_window(
            p_graphics_window__cover,
            &_camera);

    set_f_tile_render_kernel_of__world(
            get_p_world_from__game(p_game), 
            f_tile_render_kernel);

    // allocate_entity_in__entity_manager(
    //         p_game, 
    //         get_p_world_from__game(p_game), 
    //         get_p_entity_manager_from__game(p_game), 
    //         Entity_Kind__Skeleton);
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
    // Chunk *p_chunk =
    //         get_p_chunk_from__global_space(
    //             get_p_global_space_from__global_space_manager(
    //                 get_p_global_space_manager_from__game(p_game), 
    //                 (Chunk_Vector__3i32){0,0,0}));

    // fill_chunk_with(p_chunk, 
    //         Tile_Kind__None, Tile_Cover_Kind__None);

    // for (u8 i = 0; i<8;i++) {
    //     Tile *p_tile = get_p_tile_from__chunk(
    //             p_chunk,
    //             (Local_Tile_Vector__3u8){i,4,0});

    //     p_tile->the_kind_of__tile_cover =
    //         Tile_Kind__Grass +
    //         Tile_Cover_Kind__Stair__Convex_Corner__North_East+i;

    //     p_tile = get_p_tile_from__chunk(
    //             p_chunk,
    //             (Local_Tile_Vector__3u8){i,5,0});

    //     p_tile->the_kind_of__tile_cover =
    //         Tile_Kind__Grass +
    //         Tile_Cover_Kind__Stair__Convex_Corner__South_East+i;

    //     p_tile = get_p_tile_from__chunk(
    //             p_chunk,
    //             (Local_Tile_Vector__3u8){i,6,0});

    //     p_tile->the_kind_of__tile_cover =
    //         Tile_Kind__Grass +
    //         Tile_Cover_Kind__Stair__South__East_West+i;
    //     p_tile = get_p_tile_from__chunk(
    //             p_chunk,
    //             (Local_Tile_Vector__3u8){i,7,0});

    //     p_tile->the_kind_of__tile_cover =
    //         Tile_Kind__Grass +
    //         Tile_Cover_Kind__Stair__North__East_West+i;
    // }

    Graphics_Window *p_graphics_window__ground =
        (Graphics_Window*)p_this_scene->p_scene_data;

    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        poll_multiplayer(p_game);
        manage_game__pre_render(p_game);

        manage_world(p_game);

        set_graphics_window_as__in_need_of__composition(p_graphics_window__ground);
        compose_graphic_windows_in__graphics_window_manager(
                p_game);

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
            get_default_platform_graphics_window(
                get_p_gfx_context_from__game(p_game)));
}

void register_scene__world(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
            Scene_Kind__World, 
            m_load_scene_as__world_handler, 
            m_enter_scene_as__world_handler, 
            m_unload_scene_as__world_handler);
}
