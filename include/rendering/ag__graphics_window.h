#ifndef AG__GRAPHICS_WINDOW_H
#define AG__GRAPHICS_WINDOW_H

#include "defines.h"

Graphics_Window *make_AG_graphics_window_with__composition_texture(
        Game *p_game,
        Texture_Name__c_str name_of__texture_for__window_to__sample,
        Identifier__u32 uuid__u32,
        bool is_made_with__ui_manager_or__not,
        bool is_made_with__sprite_manager_or__not);

#endif
