#ifndef IMPL_TILE_KIND_H
#define IMPL_TILE_KIND_H

#define DEFINE_TILE_KIND

typedef enum Tile_Kind {
    Tile_Kind__None = 0,
    Tile_Kind__Wood,
    Tile_Kind__Stone_Brick,
    Tile_Kind__Gold,
    Tile_Kind__Iron,
    Tile_Kind__Diamond,
    Tile_Kind__Amethyst,
    Tile_Kind__Sandstone,
    Tile_Kind__Stone,
    Tile_Kind__Dirt,
    Tile_Kind__Sand,
    Tile_Kind__Grass,
    Tile_Kind__Steel,

    Tile_Kind__Water,

    Tile_Kind__Unknown
} Tile_Kind;

#endif
