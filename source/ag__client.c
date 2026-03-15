#include "ag__client.h"
#include "collisions/hitbox_context.h"
#include "collisions/core/aabb/hitbox_aabb_manager.h"
#include "collisions/core/aabb/hitbox_aabb.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "game_action/core/hitbox/game_action__hitbox.h"
#include "game_action/core/entity/game_action__entity__spawn.h"
#include "numerics.h"
#include "process/process.h"
#include "client.h"
#include "entity/entity.h"
#include "entity/entity_manager.h"
#include "types/implemented/entity_kind.h"
#include "vectors.h"
#include "world/implemented/ag__chunk_generator_overworld.h"
#include "world/world.h"

void m_process__create_client__ag(
        Process *p_this_process,
        Game *p_game) {
    Client *p_client =
        (Client*)p_this_process->p_process_data;

    Entity *p_entity =
        allocate_entity_with__this_uuid_in__entity_manager(
                p_game, 
                get_p_world_from__game(p_game), 
                get_p_entity_manager_from__game(p_game), 
                Entity_Kind__Player,
                GET_UUID_P(p_client));

    if (!p_entity) {
        debug_error("m_process__create_client__ag, failed to allocate entity for player.");
        fail_process(p_this_process);
        return;
    }

    Vector__3i32F4 position__3i32F4 = VECTOR__3i32F4__0_0_0;

    bool success_of_ptr_acquision = 
        opaque_access_to__hitbox(
                get_p_hitbox_context_from__game(p_game),
                GET_UUID_P(get_p_world_from__game(p_game)),
                GET_UUID_P(p_client),
                0,                  // void *pV_OPTIONAL_dimensions,
                &position__3i32F4,  // void *pV_OPTIONAL_position,
                0,                  // void *pV_OPTIONAL_velocity,
                0,                  // void *pV_OPTIONAL_acceleration,
                0,                  // Hitbox_Flags__u8 *p_OPTIONAL_hitbox_flags__u8,
                OPAQUE_HITBOX_ACCESS__GET);

    if (!success_of_ptr_acquision) {
        debug_error("m_process__create_client__ag, failed to get hitbox position pointer for client.");
        fail_process(p_this_process);
        return;
    }

    dispatch_game_action__hitbox(
            p_game,
            GET_UUID_P(p_client),
            get_spawn_point_of__world(get_p_world_from__game(p_game)),
            VECTOR__3i32F4__0_0_0,
            VECTOR__3i16F8__0_0_0,
            Hitbox_Kind__Opaque);

    set_client_as__loaded(p_client);
    complete_process(p_this_process);
}

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

    set_entity_as__disabled(p_entity);

    switch (error) {
        case PLATFORM_Read_File_Error__None:
            break;
        case PLATFORM_Read_File_Error__End_Of_File:
            /// assume this client is new.
            ;
            i32 z__level =
                ag__get_natural_world_height_at__xy(
                        get_p_repeatable_psuedo_random_from__world(
                            get_p_world_from__game(p_game)), 
                        0, 0);

            Vector__3i32F4 position__3i32F4;
            position__3i32F4.z__i32F4 = z__level;

            bool success_of_ptr_acquision = 
                opaque_access_to__hitbox(
                        get_p_hitbox_context_from__game(p_game),
                        GET_UUID_P(get_p_world_from__game(p_game)),
                        GET_UUID_P(p_client),
                        0,                  // void *pV_OPTIONAL_dimensions,
                        &position__3i32F4,  // void *pV_OPTIONAL_position,
                        0,                  // void *pV_OPTIONAL_velocity,
                        0,                  // void *pV_OPTIONAL_acceleration,
                        0,                  // Hitbox_Flags__u8 *p_OPTIONAL_hitbox_flags__u8,
                        OPAQUE_HITBOX_ACCESS__SET);
            if (!success_of_ptr_acquision) {
                debug_error("m_process__deserialize_client__ag, player lacks hitbox.");
                break;
            }
            break;
        default:
            debug_error("m_process__deserialize_client__ag, read file error: %d",
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
