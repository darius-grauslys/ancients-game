#include "entity/implemented/ag__entity_humanoid.h"
#include "collisions/hitbox_aabb.h"
#include "collisions/hitbox_aabb_manager.h"
#include "game.h"
#include "rendering/graphics_window.h"
#include "rendering/sprite_manager.h"
#include "types/implemented/sprite_animation_kind.h"

void poll_ag_humanoid_for__animation_update(
        Game *p_game,
        Graphics_Window *p_graphics_window,
        Entity *p_ag_humanoid) {
    Hitbox_AABB *p_hitbox_aabb =
        get_p_hitbox_aabb_by__entity_from__hitbox_aabb_manager(
                get_p_hitbox_aabb_manager_from__game(
                    p_game), 
                p_ag_humanoid);

    if (!p_hitbox_aabb)
        return;

    Sprite *p_sprite =
        get_p_sprite_by__uuid_from__sprite_manager(
                get_p_sprite_manager_from__graphics_window(
                    p_graphics_window), 
                GET_UUID_P(p_ag_humanoid));

    if (!p_sprite)
        return;

    // TODO: check by armor
    p_sprite->index_of__sprite_animation_sub_group__u8 = 0;
    if (get_movement_direction_of__hitbox(
                p_hitbox_aabb)) {
        set_sprite_animation_with__sprite_manager(
                p_game,
                get_p_sprite_manager_from__graphics_window(
                    p_graphics_window), 
                p_sprite, 
                Sprite_Animation_Kind__Humanoid_Walk,
                Sprite_Animation_Group_Kind__Humanoid);
    } else {
        set_sprite_animation_with__sprite_manager(
                p_game,
                get_p_sprite_manager_from__graphics_window(
                    p_graphics_window), 
                p_sprite, 
                Sprite_Animation_Kind__Humanoid_Idle,
                Sprite_Animation_Group_Kind__Humanoid);
    }
}
