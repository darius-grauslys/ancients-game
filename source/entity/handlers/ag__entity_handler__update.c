#include "entity/handlers/ag__entity_handler__update.h"
#include "entity/ag__entity.h"
#include "entity/entity_manager.h"
#include "entity/reserves.h"
#include "game.h"
#include "serialization/serialization_header.h"

void m_entity_handler__update__ag(
        Entity *p_this_entity,
        Game *p_game,
        World *p_world) {
    if (!get_quantity_u16_of__health_of__entity(
                p_this_entity, 
                false)) {
        if (!handle_entity__death(
                p_this_entity, 
                p_game, 
                p_world)) {
            release_entity_from__entity_manager(
                    p_game, 
                    p_world, 
                    get_p_entity_manager_from__game(
                        p_game), 
                    p_this_entity);
            return;
        }
    }

    if (p_this_entity->entity_functions.m_entity_ai_handler) {
        p_this_entity->entity_functions.m_entity_ai_handler(
                p_this_entity,
                p_game,
                p_world);
    }
    if (p_this_entity->entity_functions.m_entity_body_handler) {
        p_this_entity->entity_functions.m_entity_body_handler(
                p_this_entity,
                p_game,
                p_world);
    }
}
