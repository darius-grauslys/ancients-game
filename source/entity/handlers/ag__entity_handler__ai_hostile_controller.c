#include "entity/handlers/ag__entity_handler__ai_hostile_controller.h"
#include "collisions/hitbox_aabb.h"
#include "collisions/hitbox_aabb_manager.h"
#include "defines.h"
#include "defines_weak.h"
#include "entity/entity.h"
#include "entity/entity_manager.h"
#include "game.h"
#include "serialization/identifiers.h"
#include "types/implemented/entity_kind.h"
#include "world/chunk_vectors.h"
#include "world/local_space.h"
#include "world/local_space_manager.h"
#include "degree.h"
#include "game_action/core/hitbox/game_action__hitbox.h"

static Identifier__u32 get_target(
        Entity *p_this_entity,
        Game *p_game,
        Hitbox_AABB *p_hitbox_aabb,
        Entity **p_ptr_OUT_player) {

    Local_Space_Manager *p_local_space_manager =
        get_p_local_space_manager_thats__closest_to__this_position(
                p_game, 
                get_position_3i32_of__hitbox_aabb(p_hitbox_aabb));

    if (!p_local_space_manager) {
        debug_error("m_entity_handler__ai_hostile__melee_controller, failed to get local_space_manager.");
        set_entity_as__disabled(p_this_entity);
        return IDENTIFIER__UNKNOWN__u32;
    }

    Local_Space *p_local_space =
        get_p_local_space_from__local_space_manager(
                p_local_space_manager, 
                vector_3i32F4_to__chunk_vector_3i32(
                    get_position_3i32F4_of__hitbox_aabb(p_hitbox_aabb)));

    if (!p_local_space) {
        set_entity_as__disabled(p_this_entity);
        return IDENTIFIER__UNKNOWN__u32;
    }

    // TODO: add helpers for scanning local_space_managers

    Collision_Node_Entry *p_collision_node_entry =
        get_p_collision_node_from__local_space(
                p_local_space)
        ->p_linked_list__collision_node_entries__tail;

    Entity *p_player = 0;
    while (p_collision_node_entry) {
        Entity *p_entity =
            get_p_entity_by__uuid_from__entity_manager(
                    get_p_entity_manager_from__game(p_game), 
                    p_collision_node_entry->uuid_of__hitbox__u32);
        if (p_entity
                && p_entity->entity_data.the_kind_of__entity
                == Entity_Kind__Player) {
            p_player = p_entity;
        }
        p_collision_node_entry = 
            p_collision_node_entry->p_previous_entry;
    }

    if (!p_player)
        return IDENTIFIER__UNKNOWN__u32;
    return GET_UUID_P(p_player);
}

static void engage_player(
        Entity *p_this_entity,
        Hitbox_AABB *p_hitbox_aabb_of__this_entity,
        Game *p_game,
        Entity *p_player) {
    Hitbox_AABB *p_hitbox_aabb_of__target =
        get_p_hitbox_aabb_by__uuid_u32_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(p_game), 
                GET_UUID_P(p_player));

    if (!p_hitbox_aabb_of__this_entity) {
        p_this_entity->entity_data.uuid_of__target = 
            IDENTIFIER__UNKNOWN__u32;
        return;
    }

    i32 distance_squared_from__target =
        get_distance_squared_of__vector_3i32F4(
                subtract_vectors__3i32F4(
                    p_hitbox_aabb_of__this_entity->position__3i32F4, 
                    p_hitbox_aabb_of__target->position__3i32F4));

    if (distance_squared_from__target
            >= i32_to__i32F4(64 << 6)) {
        p_this_entity->entity_data.uuid_of__target =
            IDENTIFIER__UNKNOWN__u32;
        return;
    } else if (
            distance_squared_from__target
            < i32_to__i32F4(96)) {
        // humanoid__use(
        //         p_game,
        //         p_this_entity);
        return;
    }

    Degree__u9 angle_to__target =
        get_angle_between__vectors_3i32(
                vector_3i32F4_to__vector_3i32(
                    p_hitbox_aabb_of__this_entity->position__3i32F4), 
                vector_3i32F4_to__vector_3i32(
                    p_hitbox_aabb_of__target->position__3i32F4));
    Vector__3i32F4 movement__3i32F4 =
        get_2i32F4_offset_from__angle(angle_to__target);
    movement__3i32F4.x__i32F4 >>= 1;
    movement__3i32F4.y__i32F4 >>= 1;

    dispatch_game_action__hitbox(
            p_game,
            GET_UUID_P(p_this_entity),
            get_position_3i32F4_of__hitbox_aabb(
                p_hitbox_aabb_of__this_entity),
            get_velocity_3i32F4_of__hitbox_aabb(
                p_hitbox_aabb_of__this_entity),
            vector_3i32F4_to__vector_3i16F8(movement__3i32F4));
}

void m_entity_handler__ai_hostile__melee_controller(
        Entity *p_this_entity,
        Game *p_game,
        World *p_world) {

    Hitbox_AABB *p_hitbox_aabb =
        get_p_hitbox_aabb_by__uuid_u32_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(p_game), 
                GET_UUID_P(p_this_entity));

    if (!p_hitbox_aabb) {
        debug_error("m_entity_handler__ai_hostile__melee_controller, missing hitbox component.");
        set_entity_as__disabled(p_this_entity);
        return;
    }

    Entity *p_player = 0;
    if (is_identifier_u32__invalid(
                p_this_entity->entity_data.uuid_of__target)) {
        p_this_entity->entity_data.uuid_of__target =
            get_target(
                    p_this_entity, 
                    p_game, 
                    p_hitbox_aabb, 
                    &p_player);
    } else {
        p_player = get_p_entity_by__uuid_from__entity_manager(
                get_p_entity_manager_from__game(p_game), 
                p_this_entity->entity_data.uuid_of__target);

        // TODO: if p_player != 0, play alert sound.
    }

    if (p_player) {
        engage_player(
                p_this_entity, 
                p_hitbox_aabb,
                p_game, 
                p_player);
        return;
    }

    // i32 distance_squared_from__player =
    //     get_distance_squared_of__vector_3i32F4(
    //             subtract_vectors__3i32F4(
    //                 p_this_entity->hitbox.position__3i32F4, 
    //                 p_player->hitbox.position__3i32F4));

    // if (distance_squared_from__player
    //         < i32_to__i32F4(64 << 6)) {
    //     point_serialized_field_to__this_serialized_struct(
    //             &p_this_entity->goal__s_entity_ptr, 
    //             p_player);
    //     if (p_this_entity->the_kind_of__audio_effect_for__alert
    //             != Audio_Effect_Kind__None) {
    //         play_audio_effect_and__forget(
    //                 get_p_PLATFORM_audio_context_from__game(p_game), 
    //                 p_this_entity->the_kind_of__audio_effect_for__alert, 
    //                 AUDIO_FLAGS__NONE, 
    //                 get_timer__u32(8));
    //     }
    //     return;
    // }

    if (is_vectors_3i32F4__out_of_bounds(
                p_this_entity->entity_data.goal__3i32F4)) {
        return;
    }

    if (8 << 6 > get_distance_squared_of__vector_3i32F4(
                subtract_vectors__3i32F4(
                    p_hitbox_aabb->position__3i32F4, 
                    p_this_entity->entity_data.goal__3i32F4))) {
        return;
    }

    Degree__u9 angle_to__goal =
        get_angle_between__vectors_3i32(
                vector_3i32F4_to__vector_3i32(
                    p_hitbox_aabb->position__3i32F4),
                vector_3i32F4_to__vector_3i32(
                    p_this_entity->entity_data.goal__3i32F4));

    Vector__3i32F4 movement__3i32F4 =
        get_2i32F4_offset_from__angle(angle_to__goal);
    movement__3i32F4.x__i32F4 >>= 1;
    movement__3i32F4.y__i32F4 >>= 1;

    dispatch_game_action__hitbox(
            p_game,
            GET_UUID_P(p_this_entity),
            get_position_3i32F4_of__hitbox_aabb(
                p_hitbox_aabb),
            get_velocity_3i32F4_of__hitbox_aabb(
                p_hitbox_aabb),
            vector_3i32F4_to__vector_3i16F8(movement__3i32F4));
}
