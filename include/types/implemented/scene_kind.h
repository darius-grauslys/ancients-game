#ifndef IMPL_SCENE_KIND_H
#define IMPL_SCENE_KIND_H

#define DEFINE_SCENE_KIND

typedef enum Scene_Kind {
    Scene_Kind__None = 0,
    Scene_Kind__Singleplayer,
    Scene_Kind__Multiplayer,
    Scene_Kind__Settings,
    Scene_Kind__World,
    Scene_Kind__World_Load,
    Scene_Kind__World_Save,
    Scene_Kind__World_New,
    Scene_Kind__Unknown
} Scene_Kind;

#endif
