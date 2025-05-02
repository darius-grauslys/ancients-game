#ifndef UI_AG__TEXT_H
#define UI_AG__TEXT_H

#include "defines.h"
#include "defines_weak.h"

UI_Element *make_ag_text(
        Game *p_game,
        Graphics_Window *p_graphics_window,
        Vector__3i32 position__3i32,
        Quantity__u32 width,
        Quantity__u32 height,
        const char *p_text__c_str,
        Quantity__u32 length_of__text__c_str);

#endif
