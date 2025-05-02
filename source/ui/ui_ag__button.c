#include "ui/ui_ag__button.h"
#include "defines.h"
#include "defines_weak.h"
#include "ui/ui_element.h"
#include "ui/ui_manager.h"
#include "ui/ui_button.h"
#include "ui/ui_text.h"

UI_Element *make_ag_button(
        Game *p_game,
        Graphics_Window *p_graphics_window,
        UI_Manager *p_ui_manager,
        m_UI_Clicked m_ui_clicked_handler__button,
        Vector__3i32 position__3i32,
        Quantity__u32 width,
        Quantity__u32 height,
        Font *p_font,
        const char *p_text__c_str) {

    UI_Element *p_ui_element =
        allocate_ui_element_from__ui_manager(
                p_ui_manager);

    initialize_ui_element_as__button(
            p_ui_element, 
            m_ui_clicked_handler__button, 
            true, 
            false);

    allocate_hitbox_for__ui_element(
            p_game, 
            p_graphics_window,
            p_ui_element, 
            width, height, 
            position__3i32);

    UI_Tile_Span ui_tile_span;
    get_ui_tile_span_for__ag_button(
            &ui_tile_span);

    set_ui_tile_span_of__ui_element(
            p_ui_element, 
            &ui_tile_span);

    if (!p_text__c_str)
        return p_ui_element;

    UI_Element *p_ui_element__text__child =
        allocate_ui_element_from__ui_manager(
                p_ui_manager);

    initialize_ui_element_as__text_with__const_c_str(
            p_ui_element__text__child, 
            p_font, 
            p_text__c_str, 
            strnlen(p_text__c_str, 32));

    set_ui_element__transformed_handler(
            p_ui_element__text__child, 
            m_ui_element__transformed_handler__text__centered);

    allocate_hitbox_for__ui_element(
            p_game, 
            p_graphics_window,
            p_ui_element__text__child, 
            width, height, 
            position__3i32);

    set_ui_element_as__the_parent_of__this_ui_element(
            p_ui_manager, 
            p_ui_element, 
            p_ui_element__text__child);

    return p_ui_element;
}

void get_ui_tile_span_for__ag_button(
        UI_Tile_Span *p_ui_tile_span) {
    memset(p_ui_tile_span, 0, sizeof(UI_Tile_Span));
    p_ui_tile_span->ui_tile__fill = (UI_Tile) {
        UI_Tile_Kind__Button_Fill, 0
    };
    p_ui_tile_span->ui_tile__corner__top_left = (UI_Tile) {
        UI_Tile_Kind__Button_Corner__Top_Left, 0
    };
    p_ui_tile_span->ui_tile__corner__top_right = (UI_Tile) {
        UI_Tile_Kind__Button_Corner__Top_Right, 0
    };
    p_ui_tile_span->ui_tile__corner__bottom_left = (UI_Tile) {
        UI_Tile_Kind__Button_Corner__Bottom_Left, 0
    };
    p_ui_tile_span->ui_tile__corner__bottom_right = (UI_Tile) {
        UI_Tile_Kind__Button_Corner__Bottom_Right, 0
    };
    p_ui_tile_span->ui_tile__edge__left = (UI_Tile) {
        UI_Tile_Kind__Button_Edge__Left, 0
    };
    p_ui_tile_span->ui_tile__edge__right = (UI_Tile) {
        UI_Tile_Kind__Button_Edge__Right, 0
    };
    p_ui_tile_span->ui_tile__edge__top = (UI_Tile) {
        UI_Tile_Kind__Button_Edge__Top, 0
    };
    p_ui_tile_span->ui_tile__edge__bottom = (UI_Tile) {
        UI_Tile_Kind__Button_Edge__Bottom, 0
    };
}

