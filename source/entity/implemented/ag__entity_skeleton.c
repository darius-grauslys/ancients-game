#include "entity/implemented/ag__entity_skeleton.h"
#include "collisions/hitbox_aabb.h"
#include "collisions/hitbox_aabb_manager.h"
#include "defines.h"
#include "entity/entity_manager.h"
#include "entity/handlers/ag__entity_handler__ai_hostile_controller.h"
#include "entity/handlers/ag__entity_handler__body_humanoid.h"
#include "entity/handlers/ag__entity_handler__update.h"
#include "game.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/graphics_window.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "rendering/sprite_context.h"
#include "rendering/sprite_manager.h"
#include "rendering/handlers/ag__sprite_animation_handler.h"
#include "collisions/collision_node_pool.h"
#include "collisions/collision_node.h"
#include "vectors.h"
#include "world/chunk_vectors.h"
#include "world/global_space.h"
#include "world/local_space.h"
#include "world/global_space_manager.h"
#include "world/world.h"

void m_entity_handler__update_skeleton(
        Entity *p_this_skeleton,
        Game *p_game,
        World *p_world) {

}

void m_entity_handler__update_skeleton__begin(
        Entity *p_this_skeleton,
        Game *p_game,
        World *p_world) {
    Texture texture_of__skeleton;

    get_texture_by__alias(
        get_p_aliased_texture_manager_from__game(
            p_game), 
        name_of__texture__skeleton,
        &texture_of__skeleton);

    Sprite *p_sprite =
        allocate_sprite_from__sprite_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_sprite_manager_from__graphics_window(
                    p_game,
                    get_p_graphics_window_from__world(
                        p_world)), 
                get_p_graphics_window_from__world(
                    p_world), 
                GET_UUID_P(p_this_skeleton), 
                texture_of__skeleton,
                TEXTURE_FLAG__SIZE_16x16);

    if (p_sprite) {
        p_sprite->m_sprite_animation_handler =
            m_sprite_animation_handler__ag__humanoid;
    }

    Hitbox_AABB *p_hitbox_aabb =
        get_p_hitbox_aabb_by__uuid_u32_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(p_game), 
                GET_UUID_P(p_this_skeleton));

    if (!p_hitbox_aabb) {
        p_hitbox_aabb =
            allocate_hitbox_aabb_from__hitbox_aabb_manager(
                    get_p_hitbox_aabb_manager_from__game(p_game), 
                    GET_UUID_P(p_this_skeleton));
        if (!p_hitbox_aabb) {
            debug_error("m_entity_handler__update_skeleton__begin, failed to allocate hitbox.");
            set_entity_as__disabled(p_this_skeleton);
            return;
        }
    }

    set_size_of__hitbox_aabb(
            p_hitbox_aabb, 
            8, 8);

    set_hitbox__position_with__3i32(
            p_hitbox_aabb, 
            get_vector__3i32(
                32, 0, 0));

    Global_Space *p_global_space =
        get_p_global_space_from__global_space_manager(
                get_p_global_space_manager_from__game(p_game), 
                vector_3i32F4_to__chunk_vector_3i32(
                    get_position_3i32F4_of__hitbox_aabb(
                        p_hitbox_aabb)));

    if (p_global_space) {
        Collision_Node *p_collision_node =
            get_p_collision_node_from__global_space(
                    p_global_space);
        if (p_collision_node) {
            add_entry_to__collision_node(
                    get_p_collision_node_pool_from__world(
                        get_p_world_from__game(p_game)), 
                    p_collision_node, 
                    p_hitbox_aabb);
        }
    }

    p_this_skeleton->entity_data
        .hearts.max_quantity_of__resource_symbols = 10;
    memset(&p_this_skeleton->entity_data.hearts.resource_symbols,
            Heart_Kind__Full_Normal,
            10);

    set_m_entity_update_handler_for__entity(
            p_this_skeleton, 
            m_entity_handler__update__ag);
}

void register_entity_skeleton_into__entity_manager(
        Entity_Manager *p_entity_manager) {
    Entity_Functions entity_functions__skeleton;
    memset(&entity_functions__skeleton,
            0,
            sizeof(Entity_Functions));

    entity_functions__skeleton.m_entity_update_handler =
        m_entity_handler__update_skeleton__begin;
    entity_functions__skeleton.m_entity_ai_handler =
        m_entity_handler__ai_hostile__melee_controller;
    entity_functions__skeleton.m_entity_body_handler =
        m_entity_handler__body_humanoid;

    register_entity_into__entity_manager(
            p_entity_manager, 
            Entity_Kind__Skeleton, 
            entity_functions__skeleton);
}
