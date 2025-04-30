#ifndef IMPL_UI_TILE_KIND_H
#define IMPL_UI_TILE_KIND_H

#define DEFINE_UI_TILE_KIND

typedef enum UI_Tile_Kind {
    UI_Tile_Kind__None,
    UI_Tile_Kind__Button_Fill = 98,
    UI_Tile_Kind__Button_Corner__Bottom_Left = 129,
    UI_Tile_Kind__Button_Corner__Bottom_Right = 131,
    UI_Tile_Kind__Button_Corner__Top_Left = 65,
    UI_Tile_Kind__Button_Corner__Top_Right = 67,
    UI_Tile_Kind__Button_Edge__Left = 97,
    UI_Tile_Kind__Button_Edge__Right = 99,
    UI_Tile_Kind__Button_Edge__Top = 66,
    UI_Tile_Kind__Button_Edge__Bottom = 130,
    UI_Tile_Kind__Unknown
} UI_Tile_Kind;

#endif


