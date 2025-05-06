#include "ag__client.h"
#include "collisions/hitbox_aabb_manager.h"
#include "collisions/hitbox_aabb.h"
#include "defines_weak.h"
#include "game.h"
#include "process/process.h"
#include "client.h"
#include "entity/entity.h"
#include "entity/entity_manager.h"
#include "types/implemented/entity_kind.h"
#include "vectors.h"

void m_process__deserialize_client__ag(
        Process *p_this_process,
        Game *p_game) {
    Serialization_Request *p_serialization_request =
        (Serialization_Request*)p_this_process->p_process_data;
    Client *p_client =
        (Client*)p_serialization_request->p_data;

    Entity *p_entity =
        allocate_entity_with__this_uuid_in__entity_manager(
                p_game, 
                get_p_world_from__game(p_game), 
                get_p_entity_manager_from__game(
                    p_game), 
                Entity_Kind__Player,
                GET_UUID_P(p_client));

    if (!p_entity) {
        debug_error("m_process__deserialize_client__ag, failed to allocate p_entity for client.");
        fail_process(p_this_process);
        return;
    }

    PLATFORM_Read_File_Error error = 
        deserialize_entity(
                p_game, 
                p_serialization_request, 
                p_entity);

    if (error) {
        debug_error("m_process__deserialize_client__default, read file error: %d",
                error);
        fail_process(p_this_process);
        return;
    }

    set_client_as__active(p_client);
    complete_process(p_this_process);
}

void m_process__serialize_client__ag(
        Process *p_this_process,
        Game *p_game) {
    Serialization_Request *p_serialization_request =
        (Serialization_Request*)p_this_process->p_process_data;
    Client *p_client =
        (Client*)p_serialization_request->p_data;

    Entity *p_entity =
        get_p_entity_by__uuid_from__entity_manager(
                get_p_entity_manager_from__game(p_game), 
                GET_UUID_P(p_client));

    if (!p_entity) {
        debug_error("m_process__serialize_client__ag, client lacks entity.");
        fail_process(p_this_process);
        return;
    }

    PLATFORM_Write_File_Error error =
        serialize_entity(
                p_game, 
                p_serialization_request, 
                p_entity);

    if (error) {
        debug_error("m_process__serialize_client__ag, write error: %d",
                error);
        release_client_from__game(
                p_game,
                p_client);
        fail_process(p_this_process);
        return;
    }

    release_client_from__game(
            p_game,
            p_client);
    complete_process(p_this_process);
    return;
}
