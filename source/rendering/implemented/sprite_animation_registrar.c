#include "rendering/implemented/sprite_animation_registrar.h"
#include "debug/debug.h"
#include "rendering/implemented/ag__sprite_humanoid.h"

void register_sprite_animations(
        Sprite_Manager *p_sprite_manager) {
    register_sprite_animation_for__humanoid(
            p_sprite_manager);
}
