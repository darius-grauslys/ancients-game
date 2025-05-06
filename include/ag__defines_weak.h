#ifndef AG__DEFINES_WEAK_H
#define AG__DEFINES_WEAK_H

#include "defines_weak.h"
#include "types/implemented/item_kind.h"

typedef uint8_t Humanoid_Flags;
#define HUMANOID_FLAG__IS_UNDEAD                BIT(0)
#define HUMANOID_FLAG__HAS_DIVINE_PROVIDENCE    BIT(1)

#define ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF 32

typedef uint8_t Resource_Symbol__u8;
typedef uint8_t Heart__u8;
typedef uint8_t Energy_Orb__u8;

typedef struct Resource_Reserve_t {
    Resource_Symbol__u8 resource_symbols
        [ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF];
    ///
    /// Used for entities who has more than
    /// ENTITY_RESOURCE_SYMBOL_MAX_QUANTITY_OF
    /// of a resource.
    ///
    /// This overflow cannot be modified. ie it
    /// cannot be poisoned, etc.
    ///
    /// This is primarily used for Ancients only.
    ///
    Quantity__u16 resource_overflow;
    Quantity__u16 max_quantity_of__resource_overflow;
    Quantity__u8 max_quantity_of__resource_symbols;
} Resource_Reserve;

typedef uint8_t Hearts_Damaging_Flags;
#define HEARTS_DAMAGING_FLAGS__NONE 0
#define HEARTS_DAMAGING_FLAG__IS_POISONING \
    BIT(0)
#define HEARTS_DAMAGING_FLAG__IS_ORDER \
    BIT(1)
#define HEARTS_DAMAGING_FLAG__IS_CHAOS \
    BIT(2)
#define HEARTS_DAMAGING_FLAG__IS_CURSING \
    BIT(3)
#define HEARTS_DAMAGING_FLAG__IS_BLUDGEONING \
    BIT(4)
#define HEARTS_DAMAGING_FLAG__IS_SLASHING \
    BIT(5)
#define HEARTS_DAMAGING_FLAG__IS_PIERCING \
    BIT(6)
typedef struct Hearts_Damaging_Specifier_t {
    Quantity__u16 quantity_of__damage;
    Hearts_Damaging_Flags hearts_damaging__flags;
} Hearts_Damaging_Specifier;

#define HEARTS_HEALING_FLAG__IS_ANTIDOTE \
    BIT(0)
#define HEARTS_HEALING_FLAG__IS_IMMORTALIZING \
    BIT(1)
typedef uint8_t Hearts_Healing_Flags;
typedef struct Hearts_Healing_Specifier_t {
    Quantity__u16 quantity_of__healing;
    Hearts_Healing_Flags hearts_healing__flags;
} Hearts_Healing_Specifier;

#define ENERGY_DAMAGING_FLAG__IS_POISONING \
    BIT(0)
#define ENERGY_DAMAGING_FLAG__IS_ORDER \
    BIT(1)
#define ENERGY_DAMAGING_FLAG__IS_CHAOS \
    BIT(2)
typedef uint8_t Energy_Damaging_Flags;
typedef struct Energy_Damaging_Specifier_t {
    Quantity__u16 quantity_of__damage;
    Energy_Damaging_Flags energy_damaging__flags;
} Energy_Damaging_Specifier;

#define ENERGY_HEALING_FLAG__IS_ANTIDOTE \
    BIT(0)
#define ENERGY_HEALING_FLAG__IS_DEMONIZING \
    BIT(1)
typedef uint8_t Energy_Healing_Flags;
typedef struct Energy_Healing_Specifier_t {
    Quantity__u16 quantity_of__healing;
    Energy_Damaging_Flags energy_healing__flags;
} Energy_Healing_Specifier;

typedef int8_t Homeostasis__i8;
#define HOMEOSTASIS_MAX_QUANTITY_OF MASK(7)
#define HOMEOSTASIS_MIN_QUANTITY_OF (int8_t)BIT(7)

#define HOMEOSTASIS__EXTREME_BURNING 110
#define HOMEOSTASIS__BURNING 80
#define HOMEOSTASIS__HOT 40
#define HOMEOSTASIS__NEUTRAL 0
#define HOMEOSTASIS__COLD -40
#define HOMEOSTASIS__FREEZING -80
#define HOMEOSTASIS__EXTREME_FREEZING -110

#define HOMEOSTASIS__SOULFUL -100
#define HOMEOSTASIS__FLEETING_SOUL -50
#define HOMEOSTASIS__SOULLESS 0
#define HOMEOSTASIS__LICHLING 120
#define HOMEOSTASIS__LICH 128

typedef uint8_t Sustenance__u8;
#define SUSTENANCE_MAX_QUANTITY_OF (uint8_t)MASK(8)
#define SUSTENANCE_MIN_QUANTITY_OF 0

#define SUSTENANCE__BLOATED 240
#define SUSTENANCE__FULL 234
#define SUSTENANCE__SATISFIED 206
#define SUSTENANCE__WELL 178
#define SUSTENANCE__INDIFFERENT 150
#define SUSTENANCE__WANTING 122
#define SUSTENANCE__NEEDING 84
#define SUSTENANCE__DESPERATE 56
#define SUSTENANCE__DYING 28

#define RESOURCE_SYMBOL__EMPTY 0
#define RESOURCE_SYMBOL__LOCKED ((uint8_t)-1)

typedef enum Heart_Kind {
    Heart_Kind__Empty = RESOURCE_SYMBOL__EMPTY,
    Heart_Kind__Half_Normal,
    Heart_Kind__Full_Normal,
    Heart_Kind__Half_Poison,
    Heart_Kind__Full_Poison,
    Heart_Kind__Normal_Poison,
    Heart_Kind__Half_Immortal,
    Heart_Kind__Full_Immortal,
    Heart_Kind__Immortal_Normal,
    Heart_Kind__Immortal_Poison,
    Heart_Kind__Locked = RESOURCE_SYMBOL__LOCKED
} Heart_Kind;

typedef enum Health_State {
    Health_State__None = 0,
    Health_State__Normal,
    Health_State__Hurt,
    Health_State__Injured,
    Health_State__Dying,
    Health_State__Dead,     // health == 0
    Health_State__Unknown = (uint8_t)(-1)
} Health_State;

typedef enum Energy_Orb_Kind {
    Energy_Orb_Kind__Empty = RESOURCE_SYMBOL__EMPTY,
    Energy_Orb_Kind__Half_Normal,
    Energy_Orb_Kind__Full_Normal,
    Energy_Orb_Kind__Half_Poison,
    Energy_Orb_Kind__Full_Poison,
    Energy_Orb_Kind__Normal_Poison,
    Energy_Orb_Kind__Half_Demonic,
    Energy_Orb_Kind__Full_Demonic,
    Energy_Orb_Kind__Demonic_Normal,
    Energy_Orb_Kind__Demonic_Poison,
    Energy_Orb_Kind__Locked = RESOURCE_SYMBOL__LOCKED
} Energy_Orb_Kind;

typedef enum Energy_State {
    Energy_State__None = 0,
    Energy_State__Normal,
    Energy_State__Tired,
    Energy_State__Exhausted,
    Energy_State__Exerted,      // energy == 0
    Energy_State__Unknown = (uint8_t)(-1)
} Energy_State;

typedef enum Homeostasis_State {
    Homeostasis_State__None = 0,
    Homeostasis_State__Extreme_Burning,
    Homeostasis_State__Burning,
    Homeostasis_State__Hot,
    Homeostasis_State__Neutral,
    Homeostasis_State__Cold,
    Homeostasis_State__Freezing,
    Homeostasis_State__Extreme_Freezing,
    Homeostasis_State__Divine_Providence,
    Homeostasis_State__Soulfull,
    Homeostasis_State__Fleeting_Soul,
    Homeostasis_State__Soulless,
    Homeostasis_State__Lichling,
    Homeostasis_State__Lich,
    Homeostasis_State__Unknown = -1
} Homeostasis_State;

typedef enum Homeostasis_Update_Kind {
    Homeostasis_Update_Kind__None = 0,
    Homeostasis_Update_Kind__Increasing,
    Homeostasis_Update_Kind__Decreasing,
    Homeostasis_Update_Kind__Unknown = -1
} Homeostasis_Update_Kind;

typedef enum Sustenance_Kind {
    Sustenance_Kind__None = 0,
    Sustenance_Kind__Primary = 1,
    Sustenance_Kind__Secondary = 2,
    Sustenance_Kind__Hunger = 1,    // primary
    Sustenance_Kind__Thirst = 2,    // secondary
    Sustenance_Kind__Sanity = 1,    // primary
    Sustenance_Kind__Blood = 2,     // secondary
    Sustenance_Kind__Unknown = (uint8_t)(-1)
} Sustenance_Kind;

typedef enum Sustenance_State {
    Sustenance_State__None = 0,
    Sustenance_State__Bloated,
    Sustenance_State__Full,
    Sustenance_State__Satisifed,
    Sustenance_State__Well,
    Sustenance_State__Indifferent,
    Sustenance_State__Wanting,
    Sustenance_State__Needing,
    Sustenance_State__Desperate,
    Sustenance_State__Dying,
    Sustenance_State__Unknown = (uint8_t)(-1)
} Sustenance_State;

#endif
