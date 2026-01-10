#ifndef IMPL_GRAPHICS_WINDOW_KIND_H
#define IMPL_GRAPHICS_WINDOW_KIND_H

#define DEFINE_GRAPHICS_WINDOW_KIND

typedef enum Graphics_Window_Kind {
    Graphics_Window_Kind__None = 0,

    // The following UI is only to be opened while a world is loaded.
    UI_Window_Kind__Game__Equip,
    UI_Window_Kind__Game__Hud,
    UI_Window_Kind__Game__Idle,
    UI_Window_Kind__Game__Labor,
    UI_Window_Kind__Game__Settings,
    UI_Window_Kind__Game__Station,
    UI_Window_Kind__Game__Trade,
    UI_Window_Kind__Game__Typer,

    // The following UI is only to be opened from the Menu.
    // (Before a world is loaded, or after/while a world is unloaded.)
    UI_Window_Kind__Menu__Main,
    UI_Window_Kind__Menu__Multiplayer,
    UI_Window_Kind__Menu__Settings,
    UI_Window_Kind__Menu__Singleplayer,

    // The following UI is not to be opened willy-nilly:
    UI_Window_Kind__Inventory_Column,
    UI_Window_Kind__Inventory_Column__Small,
    UI_Window_Kind__Station_Items,
    UI_Window_Kind__Equipment,
    Graphics_Window_Kind__Unknown
} Graphics_Window_Kind;

#endif
