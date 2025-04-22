#include "rendering/implemented/aliased_texture_registrar.h"
#include "defines.h"
#include "game.h"
#include "rendering/aliased_texture_manager.h"

Texture_Name__c_str name_of__texture__ground = "ground";
Texture_Name__c_str name_of__texture__cover = "cover";

IO_path path_to__texture__ground = "assets/world/ground";
IO_path path_to__texture__cover = "assets/world/cover";

Texture_Name__c_str name_of__texture__player = "player.png";
Texture_Name__c_str name_of__texture__skeleton = "skeleton.png";

IO_path path_to__texture__player = "assets/entities/entities__16x16/player.png";
IO_path path_to__texture__skeleton = "assets/entities/entities__16x16/skeleton.png";

void register_aliased_textures_for__world(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__ground, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__ground);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__cover, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__cover);
}

void register_aliased_textures_for__entities(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Game *p_game) {
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__player, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__player);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__skeleton, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__skeleton);
}

void register_aliased_textures(
        Aliased_Texture_Manager *p_aliased_texture_manager,
        Game *p_game) {
    /*
    PLATFORM_Gfx_Context *p_PLATFORM_gfx_context =
        get_p_PLATFORM_gfx_context_from__game(p_game);

    ///
    /// TILESHEETS
    ///

    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__tilesheet_ground__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__tilesheet_ground__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__tilesheet_cover__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__tilesheet_cover__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__tilesheet_ui__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__tilesheet_ui__c_str);

    ///
    /// ENTITIES
    ///
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__player__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__player__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__skeleton__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__skeleton__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__items__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__items__c_str);

    ///
    /// UI sprites
    ///
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__ui_8x8__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__ui_8x8__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__ui_16x16__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__ui_16x16__c_str);
    load_p_PLATFORM_texture_from__path_with__alias(
            p_PLATFORM_gfx_context, 
            0, 
            p_aliased_texture_manager, 
            name_of__texture__ui_32x32__c_str, 
            TEXTURE_FLAGS(
                TEXTURE_FLAG__SIZE_256x256,
                TEXTURE_FLAG__RENDER_METHOD__0,
                TEXTURE_FLAG__FORMAT__RGBA8888),
            path_to__texture__ui_32x32__c_str);
    */
}
