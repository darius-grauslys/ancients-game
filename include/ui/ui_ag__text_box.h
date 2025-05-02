#ifndef UI_AG__TEXT_BOX_H
#define UI_AG__TEXT_BOX_H

#include "defines.h"

UI_Element *make_ag_text_box(
        Game *p_game,
        Graphics_Window *p_graphics_window,
        UI_Manager *p_ui_manager,
        Vector__3i32 position__3i32,
        Quantity__u32 width,
        Quantity__u32 height,
        Font *p_font,
        Quantity__u32 buffer_size);

void get_ui_tile_span_for__ag_text_box(
        UI_Tile_Span *p_ui_tile_span);

#endif
