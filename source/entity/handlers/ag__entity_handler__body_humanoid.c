#include "entity/handlers/ag__entity_handler__body_humanoid.h"
#include "collisions/hitbox_aabb_manager.h"
#include "entity/implemented/ag__entity_humanoid.h"
#include "game.h"

void m_entity_handler__body_humanoid(
        Entity *p_this_entity,
        Game *p_game,
        World *p_world) {
    poll_ag_humanoid_for__animation_update(
            p_game, 
            p_world->p_graphics_window_for__world, 
            p_this_entity);
}
