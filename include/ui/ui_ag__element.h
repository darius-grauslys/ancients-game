#ifndef UI_AG__ELEMENT_H
#define UI_AG__ELEMENT_H

#include "ag__defines.h"
#include "defines_weak.h"

static inline
void set_ui_element__p_data(
        UI_Element *p_ui_element,
        void *p_data) {
    p_ui_element->ui_element_data.p_data_of__ui_element = p_data;
}

#endif
