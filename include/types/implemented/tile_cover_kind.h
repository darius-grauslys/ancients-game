#ifndef IMPL_TILE_COVER_KIND_H
#define IMPL_TILE_COVER_KIND_H

#include "types/implemented/tile_kind.h"

typedef enum Tile_Cover_Kind {
    Tile_Cover_Kind__None = 0                               ,

    Tile_Cover_Kind__Stair = 16                             ,

    Tile_Cover_Kind__Stair__Wood,
    Tile_Cover_Kind__Stair__Stone_Brick,
    Tile_Cover_Kind__Stair__Gold,
    Tile_Cover_Kind__Stair__Iron,
    Tile_Cover_Kind__Stair__Diamond,
    Tile_Cover_Kind__Stair__Amethyst,
    Tile_Cover_Kind__Stair__Sandstone,
    Tile_Cover_Kind__Stair__Stone,
    Tile_Cover_Kind__Stair__Dirt,
    Tile_Cover_Kind__Stair__Sand,
    Tile_Cover_Kind__Stair__Grass,
    Tile_Cover_Kind__Stair__Steel,
    Tile_Cover_Kind__Stair__Leaves,
    Tile_Cover_Kind__Stair__Snow,

#define TILE_COVER_KIND__STAIR__OFFSET__NORTH (32*6)
#define TILE_COVER_KIND__STAIR__OFFSET__EAST_WEST (32*3)
#define TILE_COVER_KIND__STAIR__OFFSET__SOUTH (32*10)

#define TILE_COVER_KIND__STAIR__OFFSET__CONCAVE__NORTH__EAST_WEST (0)
#define TILE_COVER_KIND__STAIR__OFFSET__CONCAVE__SOUTH__EAST_WEST (32*7)

#define TILE_COVER_KIND__STAIR__OFFSET__CONVEX__NORTH__EAST_WEST (32*11)
#define TILE_COVER_KIND__STAIR__OFFSET__CONVEX__SOUTH__EAST_WEST (32*12)

    Tile_Cover_Kind__Stair__Wood__Concave_Corner__North_West            =
        Tile_Cover_Kind__Stair__Wood,
    Tile_Cover_Kind__Stair__Stone_Brick__Concave_Corner__North_West     =
        Tile_Cover_Kind__Stair__Stone_Brick,
    Tile_Cover_Kind__Stair__Gold__Concave_Corner__North_West            =
        Tile_Cover_Kind__Stair__Gold,
    Tile_Cover_Kind__Stair__Iron__Concave_Corner__North_West            =
        Tile_Cover_Kind__Stair__Iron,
    Tile_Cover_Kind__Stair__Diamond__Concave_Corner__North_West         =
        Tile_Cover_Kind__Stair__Diamond,
    Tile_Cover_Kind__Stair__Amethyst__Concave_Corner__North_West        =
        Tile_Cover_Kind__Stair__Amethyst,
    Tile_Cover_Kind__Stair__Sandstone__Concave_Corner__North_West       =
        Tile_Cover_Kind__Stair__Sandstone,
    Tile_Cover_Kind__Stair__Stone__Concave_Corner__North_West           =
        Tile_Cover_Kind__Stair__Stone,
    Tile_Cover_Kind__Stair__Dirt__Concave_Corner__North_West            =
        Tile_Cover_Kind__Stair__Dirt,
    Tile_Cover_Kind__Stair__Sand__Concave_Corner__North_West            =
        Tile_Cover_Kind__Stair__Sand,
    Tile_Cover_Kind__Stair__Grass__Concave_Corner__North_West           =
        Tile_Cover_Kind__Stair__Grass,
    Tile_Cover_Kind__Stair__Steel__Concave_Corner__North_West           =
        Tile_Cover_Kind__Stair__Steel,
    Tile_Cover_Kind__Stair__Leaves__Concave_Corner__North_West          =
        Tile_Cover_Kind__Stair__Leaves,
    Tile_Cover_Kind__Stair__Snow__Concave_Corner__North_West            =
        Tile_Cover_Kind__Stair__Snow,

    Tile_Cover_Kind__Stair__Wood__North_South_West            =
        Tile_Cover_Kind__Stair__Wood
        + (32*1),
    Tile_Cover_Kind__Stair__Stone_Brick__North_South_West     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*1),
    Tile_Cover_Kind__Stair__Gold__North_South_West            =
        Tile_Cover_Kind__Stair__Gold
        + (32*1),
    Tile_Cover_Kind__Stair__Iron__North_South_West            =
        Tile_Cover_Kind__Stair__Iron
        + (32*1),
    Tile_Cover_Kind__Stair__Diamond__North_South_West         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*1),
    Tile_Cover_Kind__Stair__Amethyst__North_South_West        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*1),
    Tile_Cover_Kind__Stair__Sandstone__North_South_West       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*1),
    Tile_Cover_Kind__Stair__Stone__North_South_West           =
        Tile_Cover_Kind__Stair__Stone
        + (32*1),
    Tile_Cover_Kind__Stair__Dirt__North_South_West            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*1),
    Tile_Cover_Kind__Stair__Sand__North_South_West            =
        Tile_Cover_Kind__Stair__Sand
        + (32*1),
    Tile_Cover_Kind__Stair__Grass__North_South_West           =
        Tile_Cover_Kind__Stair__Grass
        + (32*1),
    Tile_Cover_Kind__Stair__Steel__North_South_West           =
        Tile_Cover_Kind__Stair__Steel
        + (32*1),
    Tile_Cover_Kind__Stair__Leaves__North_South_West          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*1),
    Tile_Cover_Kind__Stair__Snow__North_South_West            =
        Tile_Cover_Kind__Stair__Snow
        + (32*1),

    Tile_Cover_Kind__Stair__Wood__North_West            =
        Tile_Cover_Kind__Stair__Wood
        + (32*2),
    Tile_Cover_Kind__Stair__Stone_Brick__North_West     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*2),
    Tile_Cover_Kind__Stair__Gold__North_West            =
        Tile_Cover_Kind__Stair__Gold
        + (32*2),
    Tile_Cover_Kind__Stair__Iron__North_West            =
        Tile_Cover_Kind__Stair__Iron
        + (32*2),
    Tile_Cover_Kind__Stair__Diamond__North_West         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*2),
    Tile_Cover_Kind__Stair__Amethyst__North_West        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*2),
    Tile_Cover_Kind__Stair__Sandstone__North_West       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*2),
    Tile_Cover_Kind__Stair__Stone__North_West           =
        Tile_Cover_Kind__Stair__Stone
        + (32*2),
    Tile_Cover_Kind__Stair__Dirt__North_West            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*2),
    Tile_Cover_Kind__Stair__Sand__North_West            =
        Tile_Cover_Kind__Stair__Sand
        + (32*2),
    Tile_Cover_Kind__Stair__Grass__North_West           =
        Tile_Cover_Kind__Stair__Grass
        + (32*2),
    Tile_Cover_Kind__Stair__Steel__North_West           =
        Tile_Cover_Kind__Stair__Steel
        + (32*2),
    Tile_Cover_Kind__Stair__Leaves__North_West          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*2),
    Tile_Cover_Kind__Stair__Snow__North_West            =
        Tile_Cover_Kind__Stair__Snow
        + (32*2),

    Tile_Cover_Kind__Stair__Wood__West            =
        Tile_Cover_Kind__Stair__Wood
        + (32*3),
    Tile_Cover_Kind__Stair__Stone_Brick__West     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*3),
    Tile_Cover_Kind__Stair__Gold__West            =
        Tile_Cover_Kind__Stair__Gold
        + (32*3),
    Tile_Cover_Kind__Stair__Iron__West            =
        Tile_Cover_Kind__Stair__Iron
        + (32*3),
    Tile_Cover_Kind__Stair__Diamond__West         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*3),
    Tile_Cover_Kind__Stair__Amethyst__West        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*3),
    Tile_Cover_Kind__Stair__Sandstone__West       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*3),
    Tile_Cover_Kind__Stair__Stone__West           =
        Tile_Cover_Kind__Stair__Stone
        + (32*3),
    Tile_Cover_Kind__Stair__Dirt__West            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*3),
    Tile_Cover_Kind__Stair__Sand__West            =
        Tile_Cover_Kind__Stair__Sand
        + (32*3),
    Tile_Cover_Kind__Stair__Grass__West           =
        Tile_Cover_Kind__Stair__Grass
        + (32*3),
    Tile_Cover_Kind__Stair__Steel__West           =
        Tile_Cover_Kind__Stair__Steel
        + (32*3),
    Tile_Cover_Kind__Stair__Leaves__West          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*3),
    Tile_Cover_Kind__Stair__Snow__West            =
        Tile_Cover_Kind__Stair__Snow
        + (32*3),

    Tile_Cover_Kind__Stair__Wood__North_East_West            =
        Tile_Cover_Kind__Stair__Wood
        + (32*4),
    Tile_Cover_Kind__Stair__Stone_Brick__North_East_West     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*4),
    Tile_Cover_Kind__Stair__Gold__North_East_West            =
        Tile_Cover_Kind__Stair__Gold
        + (32*4),
    Tile_Cover_Kind__Stair__Iron__North_East_West            =
        Tile_Cover_Kind__Stair__Iron
        + (32*4),
    Tile_Cover_Kind__Stair__Diamond__North_East_West         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*4),
    Tile_Cover_Kind__Stair__Amethyst__North_East_West        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*4),
    Tile_Cover_Kind__Stair__Sandstone__North_East_West       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*4),
    Tile_Cover_Kind__Stair__Stone__North_East_West           =
        Tile_Cover_Kind__Stair__Stone
        + (32*4),
    Tile_Cover_Kind__Stair__Dirt__North_East_West            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*4),
    Tile_Cover_Kind__Stair__Sand__North_East_West            =
        Tile_Cover_Kind__Stair__Sand
        + (32*4),
    Tile_Cover_Kind__Stair__Grass__North_East_West           =
        Tile_Cover_Kind__Stair__Grass
        + (32*4),
    Tile_Cover_Kind__Stair__Steel__North_East_West           =
        Tile_Cover_Kind__Stair__Steel
        + (32*4),
    Tile_Cover_Kind__Stair__Leaves__North_East_West          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*4),
    Tile_Cover_Kind__Stair__Snow__North_East_West            =
        Tile_Cover_Kind__Stair__Snow
        + (32*4),

    Tile_Cover_Kind__Stair__Wood__North_East            =
        Tile_Cover_Kind__Stair__Wood
        + (32*5),
    Tile_Cover_Kind__Stair__Stone_Brick__North_East     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*5),
    Tile_Cover_Kind__Stair__Gold__North_East            =
        Tile_Cover_Kind__Stair__Gold
        + (32*5),
    Tile_Cover_Kind__Stair__Iron__North_East            =
        Tile_Cover_Kind__Stair__Iron
        + (32*5),
    Tile_Cover_Kind__Stair__Diamond__North_East         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*5),
    Tile_Cover_Kind__Stair__Amethyst__North_East        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*5),
    Tile_Cover_Kind__Stair__Sandstone__North_East       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*5),
    Tile_Cover_Kind__Stair__Stone__North_East           =
        Tile_Cover_Kind__Stair__Stone
        + (32*5),
    Tile_Cover_Kind__Stair__Dirt__North_East            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*5),
    Tile_Cover_Kind__Stair__Sand__North_East            =
        Tile_Cover_Kind__Stair__Sand
        + (32*5),
    Tile_Cover_Kind__Stair__Grass__North_East           =
        Tile_Cover_Kind__Stair__Grass
        + (32*5),
    Tile_Cover_Kind__Stair__Steel__North_East           =
        Tile_Cover_Kind__Stair__Steel
        + (32*5),
    Tile_Cover_Kind__Stair__Leaves__North_East          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*5),
    Tile_Cover_Kind__Stair__Snow__North_East            =
        Tile_Cover_Kind__Stair__Snow
        + (32*5),

    Tile_Cover_Kind__Stair__Wood__North            =
        Tile_Cover_Kind__Stair__Wood
        + (32*6),
    Tile_Cover_Kind__Stair__Stone_Brick__North     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*6),
    Tile_Cover_Kind__Stair__Gold__North            =
        Tile_Cover_Kind__Stair__Gold
        + (32*6),
    Tile_Cover_Kind__Stair__Iron__North            =
        Tile_Cover_Kind__Stair__Iron
        + (32*6),
    Tile_Cover_Kind__Stair__Diamond__North         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*6),
    Tile_Cover_Kind__Stair__Amethyst__North        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*6),
    Tile_Cover_Kind__Stair__Sandstone__North       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*6),
    Tile_Cover_Kind__Stair__Stone__North           =
        Tile_Cover_Kind__Stair__Stone
        + (32*6),
    Tile_Cover_Kind__Stair__Dirt__North            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*6),
    Tile_Cover_Kind__Stair__Sand__North            =
        Tile_Cover_Kind__Stair__Sand
        + (32*6),
    Tile_Cover_Kind__Stair__Grass__North           =
        Tile_Cover_Kind__Stair__Grass
        + (32*6),
    Tile_Cover_Kind__Stair__Steel__North           =
        Tile_Cover_Kind__Stair__Steel
        + (32*6),
    Tile_Cover_Kind__Stair__Leaves__North          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*6),
    Tile_Cover_Kind__Stair__Snow__North            =
        Tile_Cover_Kind__Stair__Snow
        + (32*6),

    Tile_Cover_Kind__Stair__Wood__Concave_Corner__South_West            =
        Tile_Cover_Kind__Stair__Wood
        + (32*7),
    Tile_Cover_Kind__Stair__Stone_Brick__Concave_Corner__South_West     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*7),
    Tile_Cover_Kind__Stair__Gold__Concave_Corner__South_West            =
        Tile_Cover_Kind__Stair__Gold
        + (32*7),
    Tile_Cover_Kind__Stair__Iron__Concave_Corner__South_West            =
        Tile_Cover_Kind__Stair__Iron
        + (32*7),
    Tile_Cover_Kind__Stair__Diamond__Concave_Corner__South_West         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*7),
    Tile_Cover_Kind__Stair__Amethyst__Concave_Corner__South_West        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*7),
    Tile_Cover_Kind__Stair__Sandstone__Concave_Corner__South_West       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*7),
    Tile_Cover_Kind__Stair__Stone__Concave_Corner__South_West           =
        Tile_Cover_Kind__Stair__Stone
        + (32*7),
    Tile_Cover_Kind__Stair__Dirt__Concave_Corner__South_West            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*7),
    Tile_Cover_Kind__Stair__Sand__Concave_Corner__South_West            =
        Tile_Cover_Kind__Stair__Sand
        + (32*7),
    Tile_Cover_Kind__Stair__Grass__Concave_Corner__South_West           =
        Tile_Cover_Kind__Stair__Grass
        + (32*7),
    Tile_Cover_Kind__Stair__Steel__Concave_Corner__South_West           =
        Tile_Cover_Kind__Stair__Steel
        + (32*7),
    Tile_Cover_Kind__Stair__Leaves__Concave_Corner__South_West          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*7),
    Tile_Cover_Kind__Stair__Snow__Concave_Corner__South_West            =
        Tile_Cover_Kind__Stair__Snow
        + (32*7),

    Tile_Cover_Kind__Stair__Wood__South_East_West            =
        Tile_Cover_Kind__Stair__Wood
        + (32*8),
    Tile_Cover_Kind__Stair__Stone_Brick__South_East_West     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*8),
    Tile_Cover_Kind__Stair__Gold__South_East_West            =
        Tile_Cover_Kind__Stair__Gold
        + (32*8),
    Tile_Cover_Kind__Stair__Iron__South_East_West            =
        Tile_Cover_Kind__Stair__Iron
        + (32*8),
    Tile_Cover_Kind__Stair__Diamond__South_East_West         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*8),
    Tile_Cover_Kind__Stair__Amethyst__South_East_West        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*8),
    Tile_Cover_Kind__Stair__Sandstone__South_East_West       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*8),
    Tile_Cover_Kind__Stair__Stone__South_East_West           =
        Tile_Cover_Kind__Stair__Stone
        + (32*8),
    Tile_Cover_Kind__Stair__Dirt__South_East_West            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*8),
    Tile_Cover_Kind__Stair__Sand__South_East_West            =
        Tile_Cover_Kind__Stair__Sand
        + (32*8),
    Tile_Cover_Kind__Stair__Grass__South_East_West           =
        Tile_Cover_Kind__Stair__Grass
        + (32*8),
    Tile_Cover_Kind__Stair__Steel__South_East_West           =
        Tile_Cover_Kind__Stair__Steel
        + (32*8),
    Tile_Cover_Kind__Stair__Leaves__South_East_West          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*8),
    Tile_Cover_Kind__Stair__Snow__South_East_West            =
        Tile_Cover_Kind__Stair__Snow
        + (32*8),

    Tile_Cover_Kind__Stair__Wood__South_East            =
        Tile_Cover_Kind__Stair__Wood
        + (32*9),
    Tile_Cover_Kind__Stair__Stone_Brick__South_East     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*9),
    Tile_Cover_Kind__Stair__Gold__South_East            =
        Tile_Cover_Kind__Stair__Gold
        + (32*9),
    Tile_Cover_Kind__Stair__Iron__South_East            =
        Tile_Cover_Kind__Stair__Iron
        + (32*9),
    Tile_Cover_Kind__Stair__Diamond__South_East         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*9),
    Tile_Cover_Kind__Stair__Amethyst__South_East        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*9),
    Tile_Cover_Kind__Stair__Sandstone__South_East       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*9),
    Tile_Cover_Kind__Stair__Stone__South_East           =
        Tile_Cover_Kind__Stair__Stone
        + (32*9),
    Tile_Cover_Kind__Stair__Dirt__South_East            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*9),
    Tile_Cover_Kind__Stair__Sand__South_East            =
        Tile_Cover_Kind__Stair__Sand
        + (32*9),
    Tile_Cover_Kind__Stair__Grass__South_East           =
        Tile_Cover_Kind__Stair__Grass
        + (32*9),
    Tile_Cover_Kind__Stair__Steel__South_East           =
        Tile_Cover_Kind__Stair__Steel
        + (32*9),
    Tile_Cover_Kind__Stair__Leaves__South_East          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*9),
    Tile_Cover_Kind__Stair__Snow__South_East            =
        Tile_Cover_Kind__Stair__Snow
        + (32*9),

    Tile_Cover_Kind__Stair__Wood__South            =
        Tile_Cover_Kind__Stair__Wood
        + (32*10),
    Tile_Cover_Kind__Stair__Stone_Brick__South     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*10),
    Tile_Cover_Kind__Stair__Gold__South            =
        Tile_Cover_Kind__Stair__Gold
        + (32*10),
    Tile_Cover_Kind__Stair__Iron__South            =
        Tile_Cover_Kind__Stair__Iron
        + (32*10),
    Tile_Cover_Kind__Stair__Diamond__South         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*10),
    Tile_Cover_Kind__Stair__Amethyst__South        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*10),
    Tile_Cover_Kind__Stair__Sandstone__South       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*10),
    Tile_Cover_Kind__Stair__Stone__South           =
        Tile_Cover_Kind__Stair__Stone
        + (32*10),
    Tile_Cover_Kind__Stair__Dirt__South            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*10),
    Tile_Cover_Kind__Stair__Sand__South            =
        Tile_Cover_Kind__Stair__Sand
        + (32*10),
    Tile_Cover_Kind__Stair__Grass__South           =
        Tile_Cover_Kind__Stair__Grass
        + (32*10),
    Tile_Cover_Kind__Stair__Steel__South           =
        Tile_Cover_Kind__Stair__Steel
        + (32*10),
    Tile_Cover_Kind__Stair__Leaves__South          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*10),
    Tile_Cover_Kind__Stair__Snow__South            =
        Tile_Cover_Kind__Stair__Snow
        + (32*10),

    Tile_Cover_Kind__Stair__Wood__Convex_Corner__North_East            =
        Tile_Cover_Kind__Stair__Wood
        + (32*11),
    Tile_Cover_Kind__Stair__Stone_Brick__Convex_Corner__North_East     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*11),
    Tile_Cover_Kind__Stair__Gold__Convex_Corner__North_East            =
        Tile_Cover_Kind__Stair__Gold
        + (32*11),
    Tile_Cover_Kind__Stair__Iron__Convex_Corner__North_East            =
        Tile_Cover_Kind__Stair__Iron
        + (32*11),
    Tile_Cover_Kind__Stair__Diamond__Convex_Corner__North_East         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*11),
    Tile_Cover_Kind__Stair__Amethyst__Convex_Corner__North_East        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*11),
    Tile_Cover_Kind__Stair__Sandstone__Convex_Corner__North_East       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*11),
    Tile_Cover_Kind__Stair__Stone__Convex_Corner__North_East           =
        Tile_Cover_Kind__Stair__Stone
        + (32*11),
    Tile_Cover_Kind__Stair__Dirt__Convex_Corner__North_East            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*11),
    Tile_Cover_Kind__Stair__Sand__Convex_Corner__North_East            =
        Tile_Cover_Kind__Stair__Sand
        + (32*11),
    Tile_Cover_Kind__Stair__Grass__Convex_Corner__North_East           =
        Tile_Cover_Kind__Stair__Grass
        + (32*11),
    Tile_Cover_Kind__Stair__Steel__Convex_Corner__North_East           =
        Tile_Cover_Kind__Stair__Steel
        + (32*11),
    Tile_Cover_Kind__Stair__Leaves__Convex_Corner__North_East          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*11),
    Tile_Cover_Kind__Stair__Snow__Convex_Corner__North_East            =
        Tile_Cover_Kind__Stair__Snow
        + (32*11),

    Tile_Cover_Kind__Stair__Wood__Convex_Corner__South_East            =
        Tile_Cover_Kind__Stair__Wood
        + (32*12),
    Tile_Cover_Kind__Stair__Stone_Brick__Convex_Corner__South_East     =
        Tile_Cover_Kind__Stair__Stone_Brick
        + (32*12),
    Tile_Cover_Kind__Stair__Gold__Convex_Corner__South_East            =
        Tile_Cover_Kind__Stair__Gold
        + (32*12),
    Tile_Cover_Kind__Stair__Iron__Convex_Corner__South_East            =
        Tile_Cover_Kind__Stair__Iron
        + (32*12),
    Tile_Cover_Kind__Stair__Diamond__Convex_Corner__South_East         =
        Tile_Cover_Kind__Stair__Diamond
        + (32*12),
    Tile_Cover_Kind__Stair__Amethyst__Convex_Corner__South_East        =
        Tile_Cover_Kind__Stair__Amethyst
        + (32*12),
    Tile_Cover_Kind__Stair__Sandstone__Convex_Corner__South_East       =
        Tile_Cover_Kind__Stair__Sandstone
        + (32*12),
    Tile_Cover_Kind__Stair__Stone__Convex_Corner__South_East           =
        Tile_Cover_Kind__Stair__Stone
        + (32*12),
    Tile_Cover_Kind__Stair__Dirt__Convex_Corner__South_East            =
        Tile_Cover_Kind__Stair__Dirt
        + (32*12),
    Tile_Cover_Kind__Stair__Sand__Convex_Corner__South_East            =
        Tile_Cover_Kind__Stair__Sand
        + (32*12),
    Tile_Cover_Kind__Stair__Grass__Convex_Corner__South_East           =
        Tile_Cover_Kind__Stair__Grass
        + (32*12),
    Tile_Cover_Kind__Stair__Steel__Convex_Corner__South_East           =
        Tile_Cover_Kind__Stair__Steel
        + (32*12),
    Tile_Cover_Kind__Stair__Leaves__Convex_Corner__South_East          =
        Tile_Cover_Kind__Stair__Leaves
        + (32*12),
    Tile_Cover_Kind__Stair__Snow__Convex_Corner__South_East            =
        Tile_Cover_Kind__Stair__Snow
        + (32*12),

    Tile_Cover_Kind__Wall = 1 + (32 * 16)                   ,

    Tile_Cover_Kind__Wall__Wood                             = Tile_Cover_Kind__Wall,
    Tile_Cover_Kind__Wall__Stone_Brick                      = Tile_Cover_Kind__Wall + Tile_Kind__Stone_Brick,
    Tile_Cover_Kind__Wall__Gold                             = Tile_Cover_Kind__Wall + Tile_Kind__Gold,
    Tile_Cover_Kind__Wall__Iron                             = Tile_Cover_Kind__Wall + Tile_Kind__Iron,
    Tile_Cover_Kind__Wall__Diamond                          = Tile_Cover_Kind__Wall + Tile_Kind__Diamond,
    Tile_Cover_Kind__Wall__Amethyst                         = Tile_Cover_Kind__Wall + Tile_Kind__Amethyst,
    Tile_Cover_Kind__Wall__Sandstone                        = Tile_Cover_Kind__Wall + Tile_Kind__Sandstone,
    Tile_Cover_Kind__Wall__Stone                            = Tile_Cover_Kind__Wall + Tile_Kind__Stone,
    Tile_Cover_Kind__Wall__Dirt                             = Tile_Cover_Kind__Wall + Tile_Kind__Dirt,
    Tile_Cover_Kind__Wall__Sand                             = Tile_Cover_Kind__Wall + Tile_Kind__Sand,
    Tile_Cover_Kind__Wall__Grass                            = Tile_Cover_Kind__Wall + Tile_Kind__Grass,
    Tile_Cover_Kind__Wall__Steel                            = Tile_Cover_Kind__Wall + Tile_Kind__Steel,

    Tile_Cover_Kind__Crop__A                                = 193,
    Tile_Cover_Kind__Crop_Wheat_A                           = 193 - 32,
    Tile_Cover_Kind__Crop_Corn_A                            ,
    Tile_Cover_Kind__Crop_Onion_A                           ,
    Tile_Cover_Kind__Crop_Tomato_A                          ,
    Tile_Cover_Kind__Crop_Pumpkin_A                         ,
    Tile_Cover_Kind__Crop_Watermelon_A                      ,

    Tile_Cover_Kind__Crop__B                                ,
    Tile_Cover_Kind__Crop_Wheat_B                           ,
    Tile_Cover_Kind__Crop_Corn_B                            ,
    Tile_Cover_Kind__Crop_Onion_B                           ,
    Tile_Cover_Kind__Crop_Tomato_B                          ,
    Tile_Cover_Kind__Crop_Pumpkin_B                         ,
    Tile_Cover_Kind__Crop_Watermelon_B                      ,

    Tile_Cover_Kind__Crop__C                                ,
    Tile_Cover_Kind__Crop_Wheat_C                           ,
    Tile_Cover_Kind__Crop_Corn_C                            ,
    Tile_Cover_Kind__Crop_Onion_C                           ,
    Tile_Cover_Kind__Crop_Tomato_C                          ,
    Tile_Cover_Kind__Crop_Pumpkin_C                         ,
    Tile_Cover_Kind__Crop_Watermelon_C                      ,

    Tile_Cover_Kind__Crop__D                                ,
    Tile_Cover_Kind__Crop__E                                ,
    Tile_Cover_Kind__Crop__F                                ,
    Tile_Cover_Kind__Crop__G                                ,

    Tile_Cover_Kind__Stump                                  ,
    Tile_Cover_Kind__Tree__Trunk                            ,
    Tile_Cover_Kind__Tree__Oak                              ,
    Tile_Cover_Kind__Tree__Pine                             ,

    Tile_Cover_Kind__Table__Bottom__Left                    ,
    Tile_Cover_Kind__Table__Bottom__Middle                  ,
    Tile_Cover_Kind__Table__Bottom__Right                   ,

    Tile_Cover_Kind__Door__Horizontal = 1 + (33 * 16)       ,

    Tile_Cover_Kind__Door__Horizontal__Wood                 = Tile_Cover_Kind__Door__Horizontal,                         
    Tile_Cover_Kind__Door__Horizontal__Stone_Brick          = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Stone_Brick,
    Tile_Cover_Kind__Door__Horizontal__Iron                 = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Gold,
    Tile_Cover_Kind__Door__Horizontal__Gold                 = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Iron,
    Tile_Cover_Kind__Door__Horizontal__Diamond              = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Diamond,
    Tile_Cover_Kind__Door__Horizontal__Amethyst             = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Amethyst,
    Tile_Cover_Kind__Door__Horizontal__Sandstone            = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Sandstone,
    Tile_Cover_Kind__Door__Horizontal__Stone                = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Stone,
    Tile_Cover_Kind__Door__Horizontal__Dirt                 = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Dirt,
    Tile_Cover_Kind__Door__Horizontal__Sand                 = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Sand,
    Tile_Cover_Kind__Door__Horizontal__Grass                = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Grass,
    Tile_Cover_Kind__Door__Horizontal__Steel                = Tile_Cover_Kind__Door__Horizontal + Tile_Kind__Steel,

    Tile_Cover_Kind__Door__Horizontal__Open = 1 + (35 * 16) ,

    Tile_Cover_Kind__Door__Horizontal__Open__Wood           = Tile_Cover_Kind__Door__Horizontal__Open,                         
    Tile_Cover_Kind__Door__Horizontal__Open__Stone_Brick    = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Stone_Brick,
    Tile_Cover_Kind__Door__Horizontal__Open__Iron           = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Gold,
    Tile_Cover_Kind__Door__Horizontal__Open__Gold           = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Iron,
    Tile_Cover_Kind__Door__Horizontal__Open__Diamond        = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Diamond,
    Tile_Cover_Kind__Door__Horizontal__Open__Amethyst       = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Amethyst,
    Tile_Cover_Kind__Door__Horizontal__Open__Sandstone      = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Sandstone,
    Tile_Cover_Kind__Door__Horizontal__Open__Stone          = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Stone,
    Tile_Cover_Kind__Door__Horizontal__Open__Dirt           = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Dirt,
    Tile_Cover_Kind__Door__Horizontal__Open__Sand           = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Sand,
    Tile_Cover_Kind__Door__Horizontal__Open__Grass          = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Grass,
    Tile_Cover_Kind__Door__Horizontal__Open__Steel          = Tile_Cover_Kind__Door__Horizontal__Open + Tile_Kind__Steel,

    Tile_Cover_Kind__Door__Vertical = 1 + (40 * 16)         ,

    Tile_Cover_Kind__Door__Vertical__Wood                   = Tile_Cover_Kind__Door__Vertical,                         
    Tile_Cover_Kind__Door__Vertical__Stone_Brick            = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Stone_Brick,
    Tile_Cover_Kind__Door__Vertical__Gold                   = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Gold,
    Tile_Cover_Kind__Door__Vertical__Iron                   = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Iron,
    Tile_Cover_Kind__Door__Vertical__Diamond                = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Diamond,
    Tile_Cover_Kind__Door__Vertical__Amethyst               = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Amethyst,
    Tile_Cover_Kind__Door__Vertical__Sandstone              = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Sandstone,
    Tile_Cover_Kind__Door__Vertical__Stone                  = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Stone,
    Tile_Cover_Kind__Door__Vertical__Dirt                   = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Dirt,
    Tile_Cover_Kind__Door__Vertical__Sand                   = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Sand,
    Tile_Cover_Kind__Door__Vertical__Grass                  = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Grass,
    Tile_Cover_Kind__Door__Vertical__Steel                  = Tile_Cover_Kind__Door__Vertical + Tile_Kind__Steel,

    Tile_Cover_Kind__Door__Vertical__Open = 1 + (41 * 16)   ,

    Tile_Cover_Kind__Door__Vertical__Open__Wood             = Tile_Cover_Kind__Door__Vertical__Open,
    Tile_Cover_Kind__Door__Vertical__Open__Stone_Brick      = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Stone_Brick,
    Tile_Cover_Kind__Door__Vertical__Open__Gold             = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Gold,
    Tile_Cover_Kind__Door__Vertical__Open__Iron             = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Iron,
    Tile_Cover_Kind__Door__Vertical__Open__Diamond          = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Diamond,
    Tile_Cover_Kind__Door__Vertical__Open__Amethyst         = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Amethyst,
    Tile_Cover_Kind__Door__Vertical__Open__Sandstone        = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Sandstone,
    Tile_Cover_Kind__Door__Vertical__Open__Stone            = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Stone,
    Tile_Cover_Kind__Door__Vertical__Open__Dirt             = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Dirt,
    Tile_Cover_Kind__Door__Vertical__Open__Sand             = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Sand,
    Tile_Cover_Kind__Door__Vertical__Open__Grass            = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Grass,
    Tile_Cover_Kind__Door__Vertical__Open__Steel            = Tile_Cover_Kind__Door__Vertical__Open + Tile_Kind__Steel,

    Tile_Cover_Kind__Cactus__Tall__Top                      ,
    Tile_Cover_Kind__Ore__Large__Stone_1__Top_Right         ,
    Tile_Cover_Kind__Ore__Large__Gold_1__Top_Right          ,
    Tile_Cover_Kind__Ore__Large__Iron_1__Top_Right          ,
    Tile_Cover_Kind__Ore__Large__Diamond_1__Top_Right       ,
    Tile_Cover_Kind__Ore__Large__Amethyst_1__Top_Right      ,
    Tile_Cover_Kind__Ore__Large__Stone_2__Top_Right         ,
    Tile_Cover_Kind__Ore__Large__Gold_2__Top_Right          ,
    Tile_Cover_Kind__Ore__Large__Iron_2__Top_Right          ,
    Tile_Cover_Kind__Ore__Large__Diamond_2__Top_Right       ,
    Tile_Cover_Kind__Ore__Large__Amethyst_2__Top_Right      ,

    Tile_Cover_Kind__Unknown
} Tile_Cover_Kind;

#endif
