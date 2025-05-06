#ifndef ITEM_DATA_H
#define ITEM_DATA_H

#include "ag__defines_weak.h"

#define DEFINE_ITEM_DATA

typedef void (*m_Item_Use_Handler)(
        Item *p_this_item,
        Game *p_game,
        Entity *p_entity__using_this__item);

typedef enum Item_Usage_Mode {
    Item_Mode__None = 0,
    Item_Mode__Equipable,
    Item_Mode__Buildable,
    Item_Mode__Consumable,
    Item_Mode__Unknown
} Item_Usage_Mode;

typedef enum Entity_Armor_Kind {
    Entity_Armor_Kind__None,
    Entity_Armor_Kind__Cloth,
    Entity_Armor_Kind__Iron,
    Entity_Armor_Kind__Steel,
    Entity_Armor_Kind__Gold,
} Entity_Armor_Kind;

typedef enum Entity_Armor_Modification_Kind {
    Entity_Armor_Modification_Kind__None,
    Entity_Armor_Modification_Kind__Rusted,
    Entity_Armor_Modification_Kind__Diamond,
    Entity_Armor_Modification_Kind__Amethyst
} Entity_Armor_Modification_Kind;

typedef enum Entity_Equipment_Slot_Kind {
    Entity_Equipment_Slot_Kind__Armor,
    Entity_Equipment_Slot_Kind__Main_Hand,
    Entity_Equipment_Slot_Kind__Off_Hand,
    Entity_Equipment_Slot_Kind__Consumable_1,
    Entity_Equipment_Slot_Kind__Consumable_2,
    Entity_Equipment_Slot_Kind__Consumable_3
} Entity_Equipment_Slot_Kind;

typedef struct Equip_Properties_t {
    Entity_Armor_Kind                  
        the_kind_of_armor__this_armor_is;
    Entity_Armor_Modification_Kind     
        the_kind_of_modification__this_armor_has;
} Equip_Properties;

typedef struct Weapon_Properties_t {

} Weapon_Properties;

typedef struct Item_Data_t {
    union {
        struct {
            m_Item_Use_Handler m_item_use_handler__primary;
            m_Item_Use_Handler m_item_use_handler__secondary;
        };
        struct {
            m_Item_Use_Handler m_item_use_handler__unequip;
            m_Item_Use_Handler m_item_use_handler__equip;
        };
        struct {
            m_Item_Use_Handler m_item_use_handler__consume__primary;
            m_Item_Use_Handler m_item_use_handler__consume__secondary;
        };
    };
    union {
        Equip_Properties equip_properties;
        Weapon_Properties weapon_properties;
    };
    Quantity__u32 durability__u32;
    Quantity__u32 durability__max__u32;
    Quantity__u8 hardness__u8;
    Item_Usage_Mode usage_mode_of__item;
} Item_Data;

#endif
