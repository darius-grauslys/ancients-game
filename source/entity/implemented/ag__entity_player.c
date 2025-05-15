#include "entity/implemented/ag__entity_player.h"
#include "ag__defines_weak.h"
#include "collisions/hitbox_aabb.h"
#include "collisions/hitbox_aabb_manager.h"
#include "entity/entity.h"
#include "defines.h"
#include "entity/entity_manager.h"
#include "entity/handlers/ag__entity_handler__ai_input_controller.h"
#include "entity/handlers/ag__entity_handler__body_humanoid.h"
#include "entity/handlers/ag__entity_handler__update.h"
#include "game.h"
#include "rendering/sprite_manager.h"
#include "rendering/graphics_window.h"
#include "types/implemented/entity_functions.h"
#include "types/implemented/entity_kind.h"
#include "world/world.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/implemented/aliased_texture_registrar.h"

void m_entity_handler__update_player__begin(
        Entity *p_this_entity,
        Game *p_game,
        World *p_world) {
    allocate_sprite_from__sprite_manager(
            get_p_gfx_context_from__game(p_game), 
            get_p_sprite_manager_from__graphics_window(
                get_p_graphics_window_from__world(
                    p_world)), 
            get_p_graphics_window_from__world(
                p_world), 
            GET_UUID_P(p_this_entity), 
            get_p_PLATFORM_texture_by__alias(
                get_p_aliased_texture_manager_from__game(
                    p_game), 
                name_of__texture__player), 
            TEXTURE_FLAG__SIZE_16x16);

    Hitbox_AABB *p_hitbox_aabb =
        get_p_hitbox_aabb_by__uuid_u32_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(p_game), 
                GET_UUID_P(p_this_entity));

    if (!p_hitbox_aabb) {
        p_hitbox_aabb =
            allocate_hitbox_aabb_from__hitbox_aabb_manager(
                    get_p_hitbox_aabb_manager_from__game(p_game), 
                    GET_UUID_P(p_this_entity));
        if (!p_hitbox_aabb) {
            debug_error("m_entity_handler__update_player__begin, failed to allocate hitbox.");
            set_entity_as__disabled(p_this_entity);
            return;
        }
    }

    set_size_of__hitbox_aabb(
            p_hitbox_aabb, 
            8, 8);

    p_this_entity->entity_data
        .hearts.max_quantity_of__resource_symbols = 10;
    memset(&p_this_entity->entity_data.hearts.resource_symbols,
            Heart_Kind__Full_Normal,
            10);

    set_m_entity_update_handler_for__entity(
            p_this_entity, 
            m_entity_handler__update__ag);
}

void register_entity_player_into__entity_manager(
        Entity_Manager *p_entity_manager) {
    Entity_Functions entity_functions__player;
    memset(&entity_functions__player,
            0,
            sizeof(Entity_Functions));

    entity_functions__player.m_entity_update_handler =
        m_entity_handler__update_player__begin;
    entity_functions__player.m_entity_ai_handler =
        m_entity_handler__ai_input_controller;
    entity_functions__player.m_entity_body_handler =
        m_entity_handler__body_humanoid;

    register_entity_into__entity_manager(
            p_entity_manager, 
            Entity_Kind__Player, 
            entity_functions__player);
}
