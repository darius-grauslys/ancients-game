#include "entity/implemented/entity_registrar.h"
#include "entity/implemented/ag__entity_player.h"
#include "entity/implemented/ag__entity_skeleton.h"

void register_entities(Entity_Manager *p_entity_manager) {
    register_entity_player_into__entity_manager(
            p_entity_manager);
    register_entity_skeleton_into__entity_manager(
            p_entity_manager);
}
