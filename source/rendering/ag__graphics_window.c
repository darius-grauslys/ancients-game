#include "rendering/ag__graphics_window.h"
#include "defines.h"
#include "defines_weak.h"
#include "game.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/gfx_context.h"
#include "rendering/graphics_window.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "serialization/identifiers.h"
#include "ui/ui_tile_map_manager.h"

Graphics_Window *make_AG_graphics_window_with__composition_texture(
        Game *p_game,
        Texture_Name__c_str name_of__texture_for__window_to__sample,
        Identifier__u32 uuid__u32,
        bool is_made_with__ui_manager_or__not,
        bool is_made_with__sprite_manager_or__not) {
    Graphics_Window *p_graphics_window = 0;
    if (!is_identifier_u32__invalid(uuid__u32)) {
        // TODO: this handling of an optional uuid should be done in core.
        p_graphics_window =
            allocate_graphics_window_with__uuid_from__graphics_window_manager(
                    get_p_gfx_context_from__game(p_game), 
                    get_p_graphics_window_manager_from__gfx_context(
                        get_p_gfx_context_from__game(p_game)), 
                    uuid__u32, 
                    TEXTURE_FLAG__SIZE_256x256);
    } else {
        p_graphics_window = 
            allocate_graphics_window_from__graphics_window_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_graphics_window_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                TEXTURE_FLAG__SIZE_256x256);
    }

    if (!p_graphics_window) {
        debug_error("AG::make_AG_graphics_window_with__composition_texture, failed to allocate p_graphics_window.");
        return 0;
    }
    
    set_graphics_window__ui_tile_map(
            p_graphics_window, 
            allocate_ui_tile_map_with__ui_tile_map_manager(
                get_p_ui_tile_map_manager_from__gfx_context(
                    get_p_gfx_context_from__game(p_game)), 
                UI_Tile_Map_Size__Large));

    set_graphics_window__ui_tile_map__texture(
            p_graphics_window, 
            get_uuid_of__aliased_texture(
                get_p_aliased_texture_manager_from__game(p_game), 
                name_of__texture_for__window_to__sample));

    if (is_made_with__ui_manager_or__not) {
        allocate_ui_manager_for__graphics_window(
                get_p_gfx_context_from__game(p_game), 
                p_graphics_window,
                128); // TODO: perhaps should change
    }

    if (is_made_with__sprite_manager_or__not) {
        allocate_sprite_manager_for__graphics_window(
                get_p_gfx_context_from__game(p_game), 
                p_graphics_window,
                128); // TODO: perhaps should change
    }

    return p_graphics_window;
}
