#ifndef UI_AG__BUTTON_H
#define UI_AG__BUTTON_H

#include "defines.h"

///
/// p_font can be null
/// p_text__c_str must be null if p_font is null, it must otherwise
/// point to a \0 terminated string (capped 32 characters)
///
UI_Element *make_ag_button(
        Game *p_game,
        Graphics_Window *p_graphics_window,
        UI_Manager *p_ui_manager,
        m_UI_Clicked m_ui_clicked_handler__button,
        Vector__3i32 position__3i32,
        Quantity__u32 width,
        Quantity__u32 height,
        Font *p_font,
        const char *p_text__c_str);

void get_ui_tile_span_for__ag_button(
        UI_Tile_Span *p_ui_tile_span);

#endif
