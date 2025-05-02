#include "scene/implemented/scene_registrar.h"
#include "scene/implemented/scene__main.h"
#include "scene/implemented/scene__settings.h"
#include "scene/implemented/scene__world.h"
#include "scene/implemented/scene__singleplayer.h"
#include "scene/implemented/scene__multiplayer.h"
#include "scene/implemented/scene__world_load.h"
#include "scene/implemented/scene__world_new.h"

void register_scenes(Scene_Manager *p_scene_manager) {
    register_scene__main(p_scene_manager);
    register_scene__world(p_scene_manager);
    register_scene__world_new(p_scene_manager);
    register_scene__world_load(p_scene_manager);
    register_scene__settings(p_scene_manager);
    register_scene__singleplayer(p_scene_manager);
    register_scene__multiplayer(p_scene_manager);
}
