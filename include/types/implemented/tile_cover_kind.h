#ifndef IMPL_TILE_COVER_KIND_H
#define IMPL_TILE_COVER_KIND_H

#include "types/implemented/tile_kind.h"

typedef enum Tile_Cover_Kind {
    Tile_Cover_Kind__None = 0                               ,

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
