#include "entity/f_entity_initializer.h"
#include "collisions/hitbox_aabb_manager.h"
#include "defines.h"
#include "entity/entity_manager.h"
#include "entity/handlers/ag__entity_handler__update.h"
#include "game.h"

void f_entity_initializer__ag(
        Game *p_game,
        World *p_world,
        Entity *p_entity) {
    f_entity_initializer__default(
            p_game,
            p_world,
            p_entity);

    p_entity->entity_functions.m_entity_update_handler =
        m_entity_handler__update__ag;

    // TODO: f_entity_initializer__ag should be
    //       f_entity_resource_allocator__ag

    Hitbox_AABB *p_hitbox_aabb =
        get_p_hitbox_aabb_by__entity_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(p_game), 
                p_entity);

    if (!p_hitbox_aabb) {
        allocate_hitbox_aabb_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(p_game), 
                GET_UUID_P(p_entity));
    }
}
