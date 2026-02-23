#include "entity/handlers/ag__entity_handler__ai_input_controller.h"
#include "ag__defines.h"
#include "client.h"
#include "collisions/hitbox_aabb.h"
#include "collisions/hitbox_aabb_manager.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "game.h"
#include "input/input.h"
#include "numerics.h"
#include "rendering/graphics_window.h"
#include "scene/scene_manager.h"
#include "serialization/serialization_header.h"
#include "types/implemented/graphics_window_kind.h"
#include "types/implemented/tile_cover_kind.h"
#include "ui/ui_context.h"
#include "vectors.h"
#include "world/chunk_vectors.h"
#include "world/tile_vectors.h"
#include "world/chunk.h"
#include "world/global_space_manager.h"
#include "world/global_space.h"
#include "world/world.h"

void m_entity_handler__ai_input_controller(
        Entity *p_this_entity,
        Game *p_game,
        World *p_world) {
    Client *p_client__controller =
        get_p_client_by__uuid_from__game(
                p_game, 
                BRAND_UUID(GET_UUID_P(p_this_entity), 
                    GET_UUID_BRANDING(Lavender_Type__Player, 0)));
    if (!p_client__controller) {
        debug_error("m_entity_handler__ai_input_controller, p_client__controller == 0.");
        set_entity_as__disabled(p_this_entity);
        return;
    }
    if (!is_client__active(p_client__controller)) {
        // Wait for client to be active...
        return;
    }
    Input *p_input = 
        get_p_input_of__client(p_client__controller);

    Hitbox_AABB *p_hitbox_aabb = 
        get_p_hitbox_aabb_by__entity_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(p_game), 
                p_this_entity);

    if (!p_hitbox_aabb) {
        debug_error("m_entity_handler__ai_input_controller, missing hitbox component.");
        set_entity_as__disabled(p_this_entity);
        return;
    }

    // TODO: remove the direct velocity mod
    p_hitbox_aabb->velocity__3i32F4.x__i32F4 = 0;
    p_hitbox_aabb->velocity__3i32F4.y__i32F4 = 0;
    // up to here.
    if (is_input__game_settings_released(p_input)) {
        Scene_Manager *p_scene_manager =
            get_p_scene_manager_from__game(p_game);
        Scene *p_current_scene =
            get_p_active_scene_from__scene_manager(p_scene_manager);
        World_Scene_Data *p_world_scene_data =
            p_current_scene->p_scene_data;

        Graphics_Window *p_graphics_window__ui =
            p_world_scene_data->p_graphics_window__ui;
        UI_Manager *p_ui_manager =
            get_p_ui_manager_from__graphics_window(
                    p_game, 
                    p_graphics_window__ui);
        reset_graphics_window(
                p_game, 
                p_graphics_window__ui, 
                true /*is_releasing_unprovided_children*/);

        if (!p_ui_manager) {
            // If the ui_manager was not previously allocated
            // open the ui
            populate_window_with__ui(
                    p_game, 
                    p_graphics_window__ui,
                    UI_Window_Kind__Game__Equip, 
                    0);
        }
    }
    if (is_input__turn_left_released(p_input)) {
        debug_info(
                "pos: %d,%d,%d",
                ARITHMETRIC_R_SHIFT(p_hitbox_aabb->position__3i32F4.x__i32F4, 7),
                ARITHMETRIC_R_SHIFT(p_hitbox_aabb->position__3i32F4.y__i32F4, 7),
                ARITHMETRIC_R_SHIFT(p_hitbox_aabb->position__3i32F4.z__i32F4, 7)
                );
        Tile_Vector__3i32 tile_vector__3i32 =
                get_vector__3i32(ARITHMETRIC_R_SHIFT(p_hitbox_aabb->position__3i32F4.x__i32F4, 7),
                    ARITHMETRIC_R_SHIFT(p_hitbox_aabb->position__3i32F4.y__i32F4, 7),
                    ARITHMETRIC_R_SHIFT(p_hitbox_aabb->position__3i32F4.z__i32F4, 7));
        Chunk_Vector__3i32 gsv__3i32 =
            tile_vector_3i32_to__chunk_vector_3i32(tile_vector__3i32);
        Local_Tile_Vector__3u8 ltv__3i32 =
            tile_vector_3i32_to__local_tile_vector_3u8(tile_vector__3i32);
        debug_info(
                "ltile pos: %d,%d,%d",
                ltv__3i32.x__u8,
                ltv__3i32.y__u8,
                ltv__3i32.z__u8
                );
        debug_info(
                "chunk pos: %d,%d,%d",
                gsv__3i32.x__i32,
                gsv__3i32.y__i32,
                gsv__3i32.z__i32
                );

        get_p_tile_from__global_space_manager(
                get_p_global_space_manager_from__game(p_game), 
                get_vector__3i32(
                    ARITHMETRIC_R_SHIFT(p_hitbox_aabb->position__3i32F4.x__i32F4, 7), 
                    ARITHMETRIC_R_SHIFT(p_hitbox_aabb->position__3i32F4.y__i32F4, 7), 
                    ARITHMETRIC_R_SHIFT(p_hitbox_aabb->position__3i32F4.z__i32F4, 7)))
            ->the_kind_of__tile_cover = Tile_Cover_Kind__Wall__Amethyst;
        Global_Space *p_global_space =
            get_p_global_space_from__global_space_manager(
                    get_p_global_space_manager_from__game(p_game), 
                    vector_3i32F4_to__chunk_vector_3i32(
                        get_position_3i32F4_of__hitbox_aabb(
                            p_hitbox_aabb)));
        set_global_space_as__dirty(p_global_space);
        set_chunk_as__visually_updated(get_p_chunk_from__global_space(p_global_space));
    }
    if (is_input__forward_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.y__i32F4 = 0b1000;
        set_hitbox_aabb_as__dirty(p_hitbox_aabb);
    }
    if (is_input__backward_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.y__i32F4 = -0b1000;
        set_hitbox_aabb_as__dirty(p_hitbox_aabb);
    }
    if (is_input__right_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.x__i32F4 = 0b1000;
        set_hitbox_aabb_as__dirty(p_hitbox_aabb);
    }
    if (is_input__left_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.x__i32F4 = -0b1000;
        set_hitbox_aabb_as__dirty(p_hitbox_aabb);
    }
    if (is_input__consume_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.z__i32F4 = 0b1000;
        debug_info("z: %d", i32F4_to__i32(
                    p_hitbox_aabb->position__3i32F4.z__i32F4) >> 3);
        set_hitbox_aabb_as__dirty(p_hitbox_aabb);
    }
    if (is_input__examine_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.z__i32F4 = -0b1000;
        debug_info("z: %d", i32F4_to__i32(
                    p_hitbox_aabb->position__3i32F4.z__i32F4) >> 3);
        set_hitbox_aabb_as__dirty(p_hitbox_aabb);
    }
}
