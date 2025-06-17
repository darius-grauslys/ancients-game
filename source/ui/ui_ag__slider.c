#include "ui/ui_ag__slider.h"
#include "defines.h"
#include "game.h"
#include "rendering/aliased_texture_manager.h"
#include "rendering/graphics_window.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "rendering/sprite.h"
#include "types/implemented/ui_element_data.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "ui/ui_slider.h"
#include "rendering/sprite_manager.h"

UI_Element *make_ag_slider(
        Game *p_game,
        Graphics_Window *p_graphics_window,
        UI_Manager *p_ui_manager,
        m_UI_Dragged m_ui_dragged_handler,
        Vector__3i32 position__3i32,
        Vector__3i32 span_length__3i32,
        Quantity__u32 width,
        Quantity__u32 height,
        bool is_horizontal_or__vertical) {
    UI_Element *p_ui_slider =
        allocate_ui_element_from__ui_manager(
                p_ui_manager);

    initialize_ui_element_as__slider(
            p_ui_slider, 
            span_length__3i32,
            m_ui_dragged_handler,
            is_horizontal_or__vertical);

    allocate_hitbox_for__ui_element(
            p_game, 
            p_graphics_window,
            p_ui_slider, 
            width, height, 
            position__3i32);

    UI_Tile_Span ui_tile_span;
    get_ui_tile_span_for__ag_slider__vertical(
            &ui_tile_span);

    set_ui_tile_span_of__ui_element(
            p_ui_slider, 
            &ui_tile_span);

    UI_Element *p_ui_slider__sprite =
        allocate_ui_element_from__ui_manager(
                p_ui_manager);

    Texture texture_of__slider;
    get_texture_by__alias(
        get_p_aliased_texture_manager_from__game(
            p_game), 
        name_of__texture__ui_sprites__16x16,
        &texture_of__slider);

    Sprite *p_sprite =
        allocate_sprite_from__sprite_manager(
                get_p_gfx_context_from__game(p_game), 
                get_p_sprite_manager_from__graphics_window(
                    p_graphics_window), 
                p_graphics_window, 
                GET_UUID_P(p_ui_slider__sprite), 
                texture_of__slider,
                TEXTURE_FLAG__SIZE_16x16);

    set_frame_index_of__sprite(
            p_sprite, 
            1);

    set_ui_element_as__using_sprite(p_ui_slider__sprite);

    allocate_hitbox_for__ui_element(
            p_game, 
            p_graphics_window,
            p_ui_slider__sprite, 
            16, 16, 
            position__3i32);

    set_ui_element_as__the_parent_of__this_ui_element(
            p_graphics_window->p_ui_manager, 
            p_ui_slider, 
            p_ui_slider__sprite);

    return p_ui_slider;
}

void get_ui_tile_span_for__ag_slider__vertical(
        UI_Tile_Span *p_ui_tile_span) {
    memset(p_ui_tile_span, 0, sizeof(UI_Tile_Span));
    p_ui_tile_span->ui_tile__fill = (UI_Tile) {
        UI_Tile_Kind__Slider_Box_Vertical_Fill, 0
    };
    p_ui_tile_span->ui_tile__corner__top_left = (UI_Tile) {
        UI_Tile_Kind__Slider_Box_Vertical_Corner__Top_Left, 0
    };
    p_ui_tile_span->ui_tile__corner__top_right = (UI_Tile) {
        UI_Tile_Kind__Slider_Box_Vertical_Corner__Top_Right, 0
    };
    p_ui_tile_span->ui_tile__corner__bottom_left = (UI_Tile) {
        UI_Tile_Kind__Slider_Box_Vertical_Corner__Bottom_Left, 0
    };
    p_ui_tile_span->ui_tile__corner__bottom_right = (UI_Tile) {
        UI_Tile_Kind__Slider_Box_Vertical_Corner__Bottom_Right, 0
    };
    p_ui_tile_span->ui_tile__edge__left = (UI_Tile) {
        UI_Tile_Kind__Slider_Box_Vertical_Edge__Left, 0
    };
    p_ui_tile_span->ui_tile__edge__right = (UI_Tile) {
        UI_Tile_Kind__Slider_Box_Vertical_Edge__Right, 0
    };
    p_ui_tile_span->ui_tile__edge__top = (UI_Tile) {
        UI_Tile_Kind__Slider_Box_Vertical_Edge__Top, 0
    };
    p_ui_tile_span->ui_tile__edge__bottom = (UI_Tile) {
        UI_Tile_Kind__Slider_Box_Vertical_Edge__Bottom, 0
    };
}
