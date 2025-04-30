#ifndef AG_FONTS_H
#define AG_FONTS_H

#include "defines.h"

extern Font AG_font__large;

static inline
Font *const get_AG_font__large() {
    return &AG_font__large;
}

#endif
