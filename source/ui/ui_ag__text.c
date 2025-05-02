#include "ui/ui_ag__text.h"
#include "rendering/graphics_window.h"
#include "ui/ag_fonts.h"
#include "ui/ui_manager.h"
#include "ui/ui_text.h"

UI_Element *make_ag_text(
        Game *p_game,
        Graphics_Window *p_graphics_window,
        Vector__3i32 position__3i32,
        Quantity__u32 width,
        Quantity__u32 height,
        const char *p_text__c_str,
        Quantity__u32 length_of__text__c_str) {
    UI_Element *p_ui_element__text =
        allocate_ui_element_from__ui_manager(
                get_p_ui_manager_from__graphics_window(
                    p_graphics_window));

    initialize_ui_element_as__text_with__const_c_str(
            p_ui_element__text, 
            get_AG_font__large(), 
            p_text__c_str, 
            length_of__text__c_str);

    set_ui_element__transformed_handler(
            p_ui_element__text, 
            m_ui_element__transformed_handler__text__centered);

    allocate_hitbox_for__ui_element(
            p_game, 
            p_graphics_window, 
            p_ui_element__text, 
            width, height,
            position__3i32);
    
    return p_ui_element__text;
}
