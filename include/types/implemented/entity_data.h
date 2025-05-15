#ifndef IMPL_ENTITY_DATA_H
#define IMPL_ENTITY_DATA_H

#include "ag__defines_weak.h"
#include "defines_weak.h"

#define DEFINE_ENTITY_DATA

typedef struct Entity_Data_t {
    Entity_Flags__u32               entity_flags;
    Entity_Kind                     the_kind_of__entity;

    struct {
        Resource_Reserve            hearts;
        Resource_Reserve            energy_orbs;
        Sustenance__u8              primary_sustenance__u8;
        Sustenance__u8              secondary_sustenance__u8;
        Homeostasis_Update_Kind     kind_of_homeostasis__update;
        Homeostasis__i8             homeostasis__i8;
        Timer__u16                  homeostasis__timer_u16;
    };
    struct {
        Identifier__u32             uuid_of__current_container;    
        Identifier__u32             uuid_of__target;
        Vector__3i32F4                goal__3i32F4;
    };
} Entity_Data;

#endif
