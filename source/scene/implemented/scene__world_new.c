#include "scene/implemented/scene__world_new.h"
#include "defines.h"
#include "defines_weak.h"
#include "random.h"
#include "rendering/ag__graphics_window.h"
#include "rendering/graphics_window.h"
#include "rendering/graphics_window_manager.h"
#include "rendering/implemented/aliased_texture_registrar.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "game.h"
#include "types/implemented/scene_kind.h"
#include "ui/ag_fonts.h"
#include "ui/ui_ag__button.h"
#include "ui/ui_ag__text.h"
#include "ui/ui_ag__text_box.h"
#include "ui/ui_element.h"
#include "ui/ui_text_box.h"
#include "ui/ui_manager.h"
#include "vectors.h"
#include "world/implemented/ag__chunk_generator_overworld.h"
#include "world/world.h"

static Graphics_Window *_p_graphics_window__world_new = 0;
static UI_Element *_p_ui_element__world_name__text_box = 0;
static UI_Element *_p_ui_element__world_seed__text_box = 0;

static void m_ui_button__clicked_handler__back(
        UI_Element *p_this_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    set_active_scene_for__scene_manager(
            get_p_scene_manager_from__game(p_game), 
            Scene_Kind__None);
}

static void m_ui_button__clicked_handler__create(
        UI_Element *p_this_ui_element,
        Game *p_game,
        Graphics_Window *p_graphics_window) {
    allocate_world_for__game(p_game);
    if (is_world_allocated_for__game(p_game)) {
        initialize_world(
                p_game, 
                get_p_world_from__game(p_game));
        set_name_of__world(
                get_p_world_from__game(p_game), 
                _p_ui_element__world_name__text_box
                ->pM_char_buffer);
        u32 seed = 0;
        for (Index__u32 index_of__seed_string = 0;
                index_of__seed_string < 32
                && _p_ui_element__world_seed__text_box->pM_char_buffer[index_of__seed_string];
                index_of__seed_string++) {
            char c = _p_ui_element__world_seed__text_box->pM_char_buffer[index_of__seed_string];
            seed |= MASK(4) & (seed & (MASK(4) << (index_of__seed_string & MASK(3))))
                        + ((c & MASK(4)) << (index_of__seed_string & MASK(3)));
        }
        if (seed) {
            initialize_repeatable_psuedo_random(
                    get_p_repeatable_psuedo_random_from__world(
                        get_p_world_from__game(p_game)), 
                    seed);
        }

        i32 z__i32 = 
            ag__get_natural_world_height_at__xy(
                    get_p_repeatable_psuedo_random_from__world(get_p_world_from__game(p_game)), 
                    0, 0);
        set_spawn_point_of__world(
                get_p_world_from__game(p_game),
                get_vector__3i32F4_using__i32(0, 0, z__i32 << TILE__WIDTH_AND__HEIGHT__BIT_SHIFT));
    }
    set_active_scene_for__scene_manager(
            get_p_scene_manager_from__game(p_game), 
            Scene_Kind__World_Load);
}

void m_load_scene_as__world_new_handler(
        Scene *p_this_scene,
        Game *p_game) {
    _p_graphics_window__world_new =
        make_AG_graphics_window_with__composition_texture(
                p_game, 
                name_of__texture__ui, 
                IDENTIFIER__UNKNOWN__u32,
                true,
                true);

    if (!_p_graphics_window__world_new) {
        debug_error("m_load_scene_as__world_new_handler, failed to allocate _p_graphics_window__world_new.");
        return;
    }

    make_ag_button(
            p_game, 
            _p_graphics_window__world_new, 
            get_p_ui_manager_from__graphics_window(
                p_game,
                _p_graphics_window__world_new), 
            m_ui_button__clicked_handler__back, 
            get_vector__3i32(-128 + 24, -128 + 256 - 16, 0), 
            48, 
            32, 
            get_AG_font__large(), 
            "BACK");

    make_ag_text(
            p_game, 
            _p_graphics_window__world_new, 
            get_vector__3i32(-128 + 48, -128 + 168 - 24, 0),
            96, 48, 
            "World Name:",
            sizeof("World Name:"));

    _p_ui_element__world_name__text_box =
        make_ag_text_box(
                p_game, 
                _p_graphics_window__world_new, 
                get_p_ui_manager_from__graphics_window(
                    p_game,
                    _p_graphics_window__world_new), 
                get_vector__3i32(-128 + 96+32, -128 + 144, 0), 
                196, 32, 
                get_AG_font__large(), 
                32);

    make_ag_text(
            p_game, 
            _p_graphics_window__world_new, 
            get_vector__3i32(-128 + 48, -128 + 168 - 48 - 24, 0),
            96, 48, 
            "World Seed:",
            sizeof("World Seed:"));

    _p_ui_element__world_seed__text_box =
        make_ag_text_box(
                p_game, 
                _p_graphics_window__world_new, 
                get_p_ui_manager_from__graphics_window(
                    p_game,
                    _p_graphics_window__world_new), 
                get_vector__3i32(-128 + 96+32, -128 + 144 - 48, 0), 
                196, 32, 
                get_AG_font__large(), 
                32);

    set_ui_element__typed_handler(
            _p_ui_element__world_name__text_box, 
            m_ui_element__typed_handler__text_box__alphanumeric);

    make_ag_button(
            p_game, 
            _p_graphics_window__world_new, 
            get_p_ui_manager_from__graphics_window(
                p_game,
                _p_graphics_window__world_new), 
            m_ui_button__clicked_handler__create, 
            get_vector__3i32(-128 + 192, -128 + 16, 0), 
            128, 
            32, 
            get_AG_font__large(), 
            "CREATE");
}

void m_enter_scene_as__world_new_handler(
        Scene *p_this_scene,
        Game *p_game) {
    while (poll_is__scene_active(
                p_game, 
                p_this_scene)) {
        while(!poll__game_tick_timer(p_game));
        manage_game__pre_render(p_game);

        poll_ui_manager__update(
                get_p_ui_manager_from__graphics_window(
                    p_game,
                    _p_graphics_window__world_new),
                p_game, 
                _p_graphics_window__world_new);

        compose_graphic_windows_in__graphics_window_manager(p_game);
        render_graphic_windows_in__graphics_window_manager(p_game);

        manage_game__post_render(p_game);
    }
}

void m_unload_scene_as__world_new_handler(
        Scene *p_this_game,
        Game *p_game) {
    release_graphics_window_from__graphics_window_manager(
            p_game, 
            _p_graphics_window__world_new);
}

void register_scene__world_new(Scene_Manager *p_scene_manager) {
    register_scene_into__scene_manager(
            p_scene_manager, 
            Scene_Kind__World_New, 
            m_load_scene_as__world_new_handler, 
            m_enter_scene_as__world_new_handler, 
            m_unload_scene_as__world_new_handler);
}
