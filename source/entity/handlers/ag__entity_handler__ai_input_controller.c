#include "entity/handlers/ag__entity_handler__ai_input_controller.h"
#include "collisions/hitbox_aabb_manager.h"
#include "defines.h"
#include "entity/entity.h"
#include "game.h"
#include "input/input.h"
#include "vectors.h"

void m_entity_handler__ai_input_controller(
        Entity *p_this_entity,
        Game *p_game,
        World *p_world) {
    Input *p_input = 
        get_p_input_from__game(p_game);

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
    p_hitbox_aabb->velocity__3i32F4 =
        VECTOR__3i32F4__0_0_0;
    // up to here.
    if (is_input__forward_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.y__i32F4 = 0b1000;
    }
    if (is_input__backward_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.y__i32F4 = -0b1000;
    }
    if (is_input__right_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.x__i32F4 = 0b1000;
    }
    if (is_input__left_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.x__i32F4 = -0b1000;
    }
    if (is_input__consume_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.z__i32F4 = 0b1000;
        debug_info("z: %d", i32F4_to__i32(
                    p_hitbox_aabb->position__3i32F4.z__i32F4) >> 3);
    }
    if (is_input__examine_held(p_input)) {
        p_hitbox_aabb->velocity__3i32F4.z__i32F4 = -0b1000;
        debug_info("z: %d", i32F4_to__i32(
                    p_hitbox_aabb->position__3i32F4.z__i32F4) >> 3);
    }
}
