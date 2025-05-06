#include "rendering/implemented/ag__sprite_humanoid.h"
#include "defines.h"
#include "rendering/sprite_manager.h"
#include "types/implemented/sprite_animation_group_kind.h"
#include "types/implemented/sprite_animation_kind.h"

Sprite_Animation_Group sprite_animation_group__humanoid = {
    6, // columns in group
    4, // rows in group
    10 // number of sub groups
};

Sprite_Animation sprite_animation__humanoid__idle = {
    0, // init frame on row
    1, // quantity of frames
    8, // ticks per frame
    SPRITE_ANIMATION_FLAG__IS_OFFSET_BY__DIRECTION
};

Sprite_Animation sprite_animation__humanoid__walk = {
    1, // init frame on row
    2, // quantity of frames
    8, // ticks per frame
    SPRITE_ANIMATION_FLAG__IS_OFFSET_BY__DIRECTION
};

Sprite_Animation sprite_animation__humanoid__use = {
    3, // init frame on row
    3, // quantity of frames
    8, // ticks per frame
    SPRITE_ANIMATION_FLAG__IS_OFFSET_BY__DIRECTION
};

Sprite_Animation sprite_animation__humanoid__die = {
    18,// init frame on row
    3, // quantity of frames
    8  // ticks per frame
};

Sprite_Animation sprite_animation__humanoid__sleep = {
    21,// init frame on row
    1, // quantity of frames
    8  // ticks per frame
};

void register_sprite_animation_for__humanoid(
        Sprite_Manager *p_sprite_manager) {
    register_sprite_animation_group_into__sprite_manager(
            p_sprite_manager, 
            Sprite_Animation_Group_Kind__Humanoid, 
            sprite_animation_group__humanoid);
    
    register_sprite_animation_into__sprite_manager(
            p_sprite_manager, 
            Sprite_Animation_Kind__Humanoid_Walk, 
            sprite_animation__humanoid__walk);
    
    register_sprite_animation_into__sprite_manager(
            p_sprite_manager, 
            Sprite_Animation_Kind__Humanoid_Idle, 
            sprite_animation__humanoid__idle);

    register_sprite_animation_into__sprite_manager(
            p_sprite_manager, 
            Sprite_Animation_Kind__Humanoid_Use, 
            sprite_animation__humanoid__use);

    register_sprite_animation_into__sprite_manager(
            p_sprite_manager, 
            Sprite_Animation_Kind__Humanoid_Die, 
            sprite_animation__humanoid__die);

    register_sprite_animation_into__sprite_manager(
            p_sprite_manager, 
            Sprite_Animation_Kind__Humanoid_Sleep, 
            sprite_animation__humanoid__sleep);
}
