#include "entity/f_entity_initializer.h"
#include "entity/entity_manager.h"
#include "entity/handlers/ag__entity_handler__update.h"

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
}
