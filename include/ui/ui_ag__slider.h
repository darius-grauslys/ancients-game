#ifndef UI_AG__SLIDER_H
#define UI_AG__SLIDER_H

#include "defines.h"

UI_Element *make_ag_slider(
        Game *p_game,
        Graphics_Window *p_graphics_window,
        UI_Manager *p_ui_manager,
        m_UI_Dragged m_ui_dragged_handler,
        Vector__3i32 position__3i32,
        Vector__3i32 span_length__3i32,
        Quantity__u32 width,
        Quantity__u32 height,
        bool is_horizontal_or__vertical);

void get_ui_tile_span_for__ag_slider__vertical(
        UI_Tile_Span *p_ui_tile_span);

#endif
