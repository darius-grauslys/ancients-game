#include "ui/implemented/ui_window_registrar.h"
#include "defines.h"
#include "defines_weak.h"
#include "rendering/gfx_context.h"
#include "types/implemented/graphics_window_kind.h"
#include "ui/implemented/generated/game/ui_window__game__equip.h"
#include "ui/implemented/generated/game/ui_window__game__inventory_column.h"
#include "ui/implemented/generated/game/ui_window__game__equipment.h"
#include "ui/implemented/generated/game/ui_window__game__hud.h"
#include "ui/implemented/generated/game/ui_window__game__labor.h"
#include "ui/implemented/generated/game/ui_window__game__settings.h"
#include "ui/implemented/generated/game/ui_window__game__station.h"
#include "ui/implemented/generated/game/ui_window__game__trade.h"
#include "ui/implemented/generated/game/ui_window__game__typer.h"
#include "ui/ui_context.h"
#include "ui/ui_window.h"

void register_ui_windows(Gfx_Context *p_gfx_context) {
    UI_Context *p_ui_context =
        get_p_ui_context_from__gfx_context(p_gfx_context);
    register_ui_window_into__ui_context(
            p_ui_context, 
            allocate_ui_for__ui_window__game__equip, 
            f_ui_window__close__default, 
            UI_Window_Kind__Game__Equip,
            128, 128); // TODO: magic num sprite quant
    register_ui_window_into__ui_context(
            p_ui_context, 
            allocate_ui_for__ui_window__game__inventory_column, 
            f_ui_window__close__default, 
            UI_Window_Kind__Inventory_Column,
            -1, -1); // TODO: magic num sprite quant (neg is using parent pool)
    register_ui_window_into__ui_context(
            p_ui_context, 
            allocate_ui_for__ui_window__game__equipment, 
            f_ui_window__close__default, 
            UI_Window_Kind__Equipment,
            -1, -1); // TODO: magic num sprite quant (neg is using parent pool)
    register_ui_window_into__ui_context(
            p_ui_context, 
            allocate_ui_for__ui_window__game__hud, 
            f_ui_window__close__default, 
            UI_Window_Kind__Game__Hud,
            0, 16); // TODO: magic num sprite quant
    register_ui_window_into__ui_context(
            p_ui_context, 
            allocate_ui_for__ui_window__game__hud, 
            f_ui_window__close__default, 
            UI_Window_Kind__Game__Idle,
            0, 16); // TODO: magic num sprite quant
    register_ui_window_into__ui_context(
            p_ui_context, 
            allocate_ui_for__ui_window__game__labor, 
            f_ui_window__close__default, 
            UI_Window_Kind__Game__Labor,
            0, 16); // TODO: magic num sprite quant
    register_ui_window_into__ui_context(
            p_ui_context, 
            allocate_ui_for__ui_window__game__settings, 
            f_ui_window__close__default, 
            UI_Window_Kind__Game__Settings,
            0, 16); // TODO: magic num sprite quant
    register_ui_window_into__ui_context(
            p_ui_context, 
            allocate_ui_for__ui_window__game__station, 
            f_ui_window__close__default, 
            UI_Window_Kind__Game__Station,
            128, 128); // TODO: magic num sprite quant
    register_ui_window_into__ui_context(
            p_ui_context, 
            allocate_ui_for__ui_window__game__trade, 
            f_ui_window__close__default, 
            UI_Window_Kind__Game__Trade,
            128, 128); // TODO: magic num sprite quant
    register_ui_window_into__ui_context(
            p_ui_context, 
            allocate_ui_for__ui_window__game__typer, 
            f_ui_window__close__default, 
            UI_Window_Kind__Game__Typer,
            0, 128); // TODO: magic num sprite quant
}
