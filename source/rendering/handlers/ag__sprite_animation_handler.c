#include "rendering/handlers/ag__sprite_animation_handler.h"
#include "collisions/hitbox_aabb.h"
#include "collisions/hitbox_aabb_manager.h"
#include "defines.h"
#include "game.h"
#include "rendering/graphics_window.h"
#include "rendering/sprite.h"
#include "rendering/sprite_manager.h"
#include "types/implemented/sprite_animation_kind.h"

void m_sprite_animation_handler__ag__humanoid(
        Sprite *p_this_sprite,
        Game *p_game,
        Sprite_Manager *p_sprite_manager) {
    Hitbox_AABB *p_hitbox_aabb =
        get_p_hitbox_aabb_by__uuid_u32_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(
                    p_game), 
                GET_UUID_P(p_this_sprite));

    if (!p_hitbox_aabb) {
        set_sprite_as__disabled(p_this_sprite);
        debug_error("m_sprite_animation_handler__ag__directional, sprite lacks hitbox component.");
        return;
    }

    if (!p_sprite_manager) {
        debug_error("m_sprite_animation_handler__ag__directional, entity is in graphics window without a sprite_manager.");
        return;
    }

    // TODO: check by armor
    // p_sprite->index_of__sprite_animation_sub_group__u8 = 0;
    if (get_movement_direction_of__hitbox(
                p_hitbox_aabb)) {
        set_sprite_animation(
                p_sprite_manager, 
                p_this_sprite, 
                Sprite_Animation_Kind__Humanoid_Walk);
    } else {
        set_sprite_animation(
                p_sprite_manager, 
                p_this_sprite, 
                Sprite_Animation_Kind__Humanoid_Idle);
    }

    m_sprite_animation_handler__default(
            p_this_sprite, 
            p_game, 
            p_sprite_manager);
}
