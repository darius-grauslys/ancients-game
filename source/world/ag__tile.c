#include "world/ag__tile.h"

bool is_tile_with__stairs(Tile *p_tile) {
    switch (p_tile->the_kind_of__tile_cover) {
        default:
            return false;
        case Tile_Cover_Kind__Stair__Grass:
        case Tile_Cover_Kind__Stair__Stone_Brick:
        case Tile_Cover_Kind__Stair__Gold:
        case Tile_Cover_Kind__Stair__Iron:
        case Tile_Cover_Kind__Stair__Sandstone:
        case Tile_Cover_Kind__Stair__Stone:
        case Tile_Cover_Kind__Stair__Amethyst:
        case Tile_Cover_Kind__Stair__Diamond:
        case Tile_Cover_Kind__Stair__Dirt:
        case Tile_Cover_Kind__Stair__Sand:
        case Tile_Cover_Kind__Stair__Steel:
        case Tile_Cover_Kind__Stair__Leaves:
        case Tile_Cover_Kind__Stair__Snow:
            return true;
    }
}
