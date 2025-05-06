#ifndef IMPL_SPRITE_ANIMATION_KIND_H
#define IMPL_SPRITE_ANIMATION_KIND_H

#define DEFINE_SPRITE_ANIMATION_KIND

typedef enum Sprite_Animation_Kind {
    Sprite_Animation_Kind__None,
    Sprite_Animation_Kind__Humanoid_Idle,
    Sprite_Animation_Kind__Humanoid_Walk,
    Sprite_Animation_Kind__Humanoid_Use,
    Sprite_Animation_Kind__Humanoid_Die,
    Sprite_Animation_Kind__Humanoid_Sleep,
    Sprite_Animation_Kind__Unknown
} Sprite_Animation_Kind;

#endif

