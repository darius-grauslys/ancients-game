#ifndef F_TILE_RENDER_KERNEL_H
#define F_TILE_RENDER_KERNEL_H

#include "defines.h"

void f_tile_render_kernel(
        Local_Space *p_local_space,
        Tile_Render_Kernel_Result *p_tile_kernel_render_results,
        Quantity__u32 quantity_of__tile_kernel_render_results,
        u8 x__local,
        u8 y__local,
        u8 z__local);

#endif
