#ifndef AG__GFX_WINDOW__INVENTORY_H
#define AG__GFX_WINDOW__INVENTORY_H

#include "defines.h"
#include "defines_weak.h"

void ag__gfx_window__inventory__allocate(
        Game *p_game,
        Graphics_Window *p_gfx_window);
void ag__gfx_window__inventory__release(
        Game *p_game,
        Graphics_Window *p_gfx_window);
void ag__gfx_window__inventory__show(
        Game *p_game,
        Graphics_Window *p_gfx_window);
void ag__gfx_window__inventory__hide(
        Game *p_game,
        Graphics_Window *p_gfx_window);
///
/// Spawns a process to acquire the inventory
/// then populate the UI.
///
void ag__gfx_window__inventory__update_contents(
        Game *p_game,
        Graphics_Window *p_gfx_window,
        Identifier__u32 uuid__inventory__u32);

void ag__gfx_window__inventory_container__allocate(
        Game *p_game,
        Graphics_Window *p_gfx_window);
void ag__gfx_window__inventory_container__release(
        Game *p_game,
        Graphics_Window *p_gfx_window);
void ag__gfx_window__inventory_container__show(
        Game *p_game,
        Graphics_Window *p_gfx_window);
void ag__gfx_window__inventory_container__hide(
        Game *p_game,
        Graphics_Window *p_gfx_window);
///
/// Spawns a process to acquire the inventory_container
/// then populate the UI.
///
void ag__gfx_window__inventory_container__update_contents(
        Game *p_game,
        Graphics_Window *p_gfx_window,
        Identifier__u32 uuid__inventory_container__u32);

#endif
