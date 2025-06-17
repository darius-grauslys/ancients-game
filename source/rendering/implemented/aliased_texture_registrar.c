#include "rendering/implemented/aliased_texture_registrar.h"
#include "game.h"
#include "rendering/aliased_texture_manager.h"

Texture_Name__c_str name_of__texture__ground = "ground";
Texture_Name__c_str name_of__texture__cover = "cover";
Texture_Name__c_str name_of__texture__ui = "ui";
Texture_Name__c_str name_of__texture__font__large = "font__large";
Texture_Name__c_str name_of__texture__ui_sprites__16x16 = "ui_s16x16";
Texture_Name__c_str name_of__texture__player = "player";
Texture_Name__c_str name_of__texture__skeleton = "skeleton";

IO_path path_to__texture__ground = "assets/world/ground.png";
IO_path path_to__texture__cover = "assets/world/cover.png";
IO_path path_to__texture__ui = "assets/ui/default/ui.png";
IO_path path_to__texture__font__large = "assets/ui/font/font__large.png";
IO_path path_to__texture__ui_sprites__16x16 = "assets/ui/sprites/ui_sprites__16x16/ui_sprites__16x16.png";
IO_path path_to__texture__player = "assets/entities/entities__16x16/player.png";
IO_path path_to__texture__skeleton = "assets/entities/entities__16x16/skeleton.png";

void register_aliased_textures(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    load_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__ui, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__ui,
            0);

    load_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__font__large, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__font__large,
            0);

    load_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__ui_sprites__16x16, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__ui_sprites__16x16,
            0);
}

void register_aliased_textures_for__world(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    load_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__ground, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__ground,
            0);

    load_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__cover, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__cover,
            0);
}

void register_aliased_textures_for__entities(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    load_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__player, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__player,
            0);
    load_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__skeleton, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__skeleton,
            0);
}
