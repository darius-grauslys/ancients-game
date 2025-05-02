#ifndef IMPL_UI_TILE_KIND_H
#define IMPL_UI_TILE_KIND_H

#define DEFINE_UI_TILE_KIND

typedef enum UI_Tile_Kind {
    UI_Tile_Kind__None,

    UI_Tile_Kind__Background_Fill = 104,
    UI_Tile_Kind__Background_Corner__Bottom_Left = 129 + 6,
    UI_Tile_Kind__Background_Corner__Bottom_Right = 131 + 6,
    UI_Tile_Kind__Background_Corner__Top_Left = 65 + 6,
    UI_Tile_Kind__Background_Corner__Top_Right = 67 + 6,
    UI_Tile_Kind__Background_Edge__Left = 97 + 6,
    UI_Tile_Kind__Background_Edge__Right = 99 + 6,
    UI_Tile_Kind__Background_Edge__Top = 66 + 6,
    UI_Tile_Kind__Background_Edge__Bottom = 130 + 6,

    UI_Tile_Kind__Button_Fill = 98,
    UI_Tile_Kind__Button_Corner__Bottom_Left = 129,
    UI_Tile_Kind__Button_Corner__Bottom_Right = 131,
    UI_Tile_Kind__Button_Corner__Top_Left = 65,
    UI_Tile_Kind__Button_Corner__Top_Right = 67,
    UI_Tile_Kind__Button_Edge__Left = 97,
    UI_Tile_Kind__Button_Edge__Right = 99,
    UI_Tile_Kind__Button_Edge__Top = 66,
    UI_Tile_Kind__Button_Edge__Bottom = 130,

    UI_Tile_Kind__Button_Toggled_Fill = 98 + 96,
    UI_Tile_Kind__Button_Toggled_Corner__Bottom_Left = 129 + 96,
    UI_Tile_Kind__Button_Toggled_Corner__Bottom_Right = 131 + 96,
    UI_Tile_Kind__Button_Toggled_Corner__Top_Left = 65 + 96,
    UI_Tile_Kind__Button_Toggled_Corner__Top_Right = 67 + 96,
    UI_Tile_Kind__Button_Toggled_Edge__Left = 97 + 96,
    UI_Tile_Kind__Button_Toggled_Edge__Right = 99 + 96,
    UI_Tile_Kind__Button_Toggled_Edge__Top = 66 + 96,
    UI_Tile_Kind__Button_Toggled_Edge__Bottom = 130 + 96,

    UI_Tile_Kind__Slider_Box_Vertical_Fill = 98 + (32*14),
    UI_Tile_Kind__Slider_Box_Vertical_Corner__Bottom_Left = 129,
    UI_Tile_Kind__Slider_Box_Vertical_Corner__Bottom_Right = 131,
    UI_Tile_Kind__Slider_Box_Vertical_Corner__Top_Left = 65,
    UI_Tile_Kind__Slider_Box_Vertical_Corner__Top_Right = 67,
    UI_Tile_Kind__Slider_Box_Vertical_Edge__Left = 97,
    UI_Tile_Kind__Slider_Box_Vertical_Edge__Right = 99,
    UI_Tile_Kind__Slider_Box_Vertical_Edge__Top = 66 + (32*14),
    UI_Tile_Kind__Slider_Box_Vertical_Edge__Bottom = 130 + (32*14),

    UI_Tile_Kind__Text_Box_Fill = 364 + 28 - 96,
    UI_Tile_Kind__Text_Box_Corner__Bottom_Left = 395 + 28 - 96,
    UI_Tile_Kind__Text_Box_Corner__Bottom_Right = 397 + 28 - 96,
    UI_Tile_Kind__Text_Box_Corner__Top_Left = 331 + 28 - 96,
    UI_Tile_Kind__Text_Box_Corner__Top_Right = 333 + 28 - 96,
    UI_Tile_Kind__Text_Box_Edge__Left = 363 + 28 - 96,
    UI_Tile_Kind__Text_Box_Edge__Right = 365 + 28 - 96,
    UI_Tile_Kind__Text_Box_Edge__Top = 332 + 28 - 96,
    UI_Tile_Kind__Text_Box_Edge__Bottom = 396 + 28 - 96,
    UI_Tile_Kind__Unknown
} UI_Tile_Kind;

#endif


