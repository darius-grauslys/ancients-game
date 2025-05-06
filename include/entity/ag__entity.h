#ifndef AG__ENTITY_H
#define AG__ENTITY_H

#include "ag__defines.h"

static inline
bool is_entity__undead(
        Entity *p_entity) {
    return p_entity->entity_data.entity_flags
        & ENTITY_FLAG__IS_UNDEAD;
}

///
/// Returns true if handler was invoked.
///
static inline
bool handle_entity__death(
        Entity *p_entity,
        Game *p_game,
        World *p_world) {
    if (!p_entity->entity_functions.m_entity_death_handler)
        return false;
    p_entity->entity_functions.m_entity_death_handler(
            p_entity,
            p_game,
            p_world);
    return true;
}

#endif
