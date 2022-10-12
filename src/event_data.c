#include "global.h"
#include "event_data.h"
#include "item_menu.h"
#include "quest_log.h"
#include "constants/maps.h"
#include "constants/map_groups.h"
#include "constants/region_map_sections.h"

static bool8 IsFlagOrVarStoredInQuestLog(u16 idx, u8 a1);

EWRAM_DATA u16 gSpecialVar_0x8000 = 0;
EWRAM_DATA u16 gSpecialVar_0x8001 = 0;
EWRAM_DATA u16 gSpecialVar_0x8002 = 0;
EWRAM_DATA u16 gSpecialVar_0x8003 = 0;
EWRAM_DATA u16 gSpecialVar_0x8004 = 0;
EWRAM_DATA u16 gSpecialVar_0x8005 = 0;
EWRAM_DATA u16 gSpecialVar_0x8006 = 0;
EWRAM_DATA u16 gSpecialVar_0x8007 = 0;
EWRAM_DATA u16 gSpecialVar_0x8008 = 0;
EWRAM_DATA u16 gSpecialVar_0x8009 = 0;
EWRAM_DATA u16 gSpecialVar_0x800A = 0;
EWRAM_DATA u16 gSpecialVar_0x800B = 0;
EWRAM_DATA u16 gSpecialVar_Result = 0;
EWRAM_DATA u16 gSpecialVar_LastTalked = 0;
EWRAM_DATA u16 gSpecialVar_Facing = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxId = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxPos = 0;
EWRAM_DATA u16 gSpecialVar_TextColor = 0;
EWRAM_DATA u16 gSpecialVar_PrevTextColor = 0;
EWRAM_DATA u16 gSpecialVar_0x8014 = 0;
EWRAM_DATA u8 sSpecialFlags[SPECIAL_FLAGS_COUNT] = {};

#define NUM_DAILY_FLAGS   (DAILY_FLAGS_END - DAILY_FLAGS_START + 1)
#define DAILY_FLAGS_SIZE  (NUM_DAILY_FLAGS / 8)

u16 gLastQuestLogStoredFlagOrVarIdx;

extern u16 *const gSpecialVars[];
extern u8 NuzlockeLUT[];

void InitEventData(void)
{
    memset(gSaveBlock1Ptr->flags, 0, NUM_FLAG_BYTES);
    memset(gSaveBlock1Ptr->vars, 0, VARS_COUNT * 2);
    memset(sSpecialFlags, 0, SPECIAL_FLAGS_COUNT);
}

void ClearTempFieldEventData(void)
{
    memset(gSaveBlock1Ptr->flags, 0, 4);
    memset(gSaveBlock1Ptr->vars, 0, 16 * 2);
    FlagClear(FLAG_SYS_WHITE_FLUTE_ACTIVE);
    FlagClear(FLAG_SYS_BLACK_FLUTE_ACTIVE);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_SPECIAL_WILD_BATTLE);
    FlagClear(FLAG_SYS_CTRL_OBJ_DELETE);
    FlagClear(FLAG_SYS_INFORMED_OF_LOCAL_WIRELESS_PLAYER);
}

void sub_806E168(void)
{
    u16 *ptr = GetVarPointer(VAR_0x403C);
    gSaveBlock2Ptr->pokedex.nationalMagic = 0;
    *ptr = 0;
    FlagClear(FLAG_0x838);
}

void ClearDailyFlags(void)
{
    memset(gSaveBlock1Ptr->flags + (DAILY_FLAGS_START / 8), 0, DAILY_FLAGS_SIZE);
}

void sub_806E190(void)
{
    u16 *ptr = GetVarPointer(VAR_0x403C);
    gSaveBlock2Ptr->pokedex.nationalMagic = 0xDA;
    *ptr = 0x0302;
    FlagSet(FLAG_0x838);
}

bool32 sub_806E1C0(void)
{
    if (gSaveBlock2Ptr->pokedex.nationalMagic != 0xDA)
        return FALSE;
    if (VarGet(VAR_0x403C) != 0x0302)
        return FALSE;
    if (!FlagGet(FLAG_0x838))
        return FALSE;
    return TRUE;
}

void sub_806E204(void)
{
    u16 *ptr = GetVarPointer(VAR_0x404E);
    gSaveBlock2Ptr->pokedex.unknown2 = 0;
    *ptr = 0;
    FlagClear(FLAG_SYS_NATIONAL_DEX);
}

void EnableNationalPokedex(void)
{
    u16 *ptr = GetVarPointer(VAR_0x404E);
    gSaveBlock2Ptr->pokedex.unknown2 = 0xB9;
    *ptr = 0x6258;
    FlagSet(FLAG_SYS_NATIONAL_DEX);
}

bool32 IsNationalPokedexEnabled(void)
{
    /*  //These must be enabled to allow linking to Colo & XD, and
        //will be enabled when the player gets the Pokedex.
    if (gSaveBlock2Ptr->pokedex.unknown2 != 0xB9)
        return FALSE;
    if (VarGet(VAR_0x404E) != 0x6258)
        return FALSE;
    */
    if (!FlagGet(FLAG_SYS_NATIONAL_DEX))
        return FALSE;
    return TRUE;
}

void DisableMysteryGift(void)
{
    FlagClear(FLAG_SYS_MYSTERY_GIFT_ENABLED);
}

void EnableMysteryGift(void)
{
    FlagSet(FLAG_SYS_MYSTERY_GIFT_ENABLED);
}

bool32 IsMysteryGiftEnabled(void)
{
    return FlagGet(FLAG_SYS_MYSTERY_GIFT_ENABLED);
}

void ResetMysteryEventFlags(void)
{
    FlagClear(FLAG_MYSTERY_EVENT_DONE);
    FlagClear(FLAG_0x3D9);
    FlagClear(FLAG_0x3DA);
    FlagClear(FLAG_0x3DB);
    FlagClear(FLAG_0x3DC);
    FlagClear(FLAG_0x3DD);
    FlagClear(FLAG_0x3DE);
    FlagClear(FLAG_0x3DF);
    FlagClear(FLAG_0x3E0);
    FlagClear(FLAG_0x3E1);
    FlagClear(FLAG_0x3E2);
    FlagClear(FLAG_0x3E3);
    FlagClear(FLAG_0x3E4);
    FlagClear(FLAG_0x3E5);
    FlagClear(FLAG_0x3E6);
    FlagClear(FLAG_0x3E7);
}

void ResetMysteryEventVars(void)
{
    VarSet(VAR_EVENT_PICHU_SLOT, 0);
    VarSet(VAR_0x40B6, 0);
    VarSet(VAR_0x40B7, 0);
    VarSet(VAR_0x40B8, 0);
    VarSet(VAR_0x40B9, 0);
    VarSet(VAR_0x40BA, 0);
    VarSet(VAR_0x40BB, 0);
    VarSet(VAR_0x40BC, 0);
    VarSet(VAR_ALTERING_CAVE_WILD_SET, 0);
}

void DisableResetRTC(void)
{
    VarSet(VAR_0x4032, 0);
    FlagClear(FLAG_SYS_RESET_RTC_ENABLE);
}

void EnableResetRTC(void)
{
    VarSet(VAR_0x4032, 0x0920);
    FlagSet(FLAG_SYS_RESET_RTC_ENABLE);
}

bool32 CanResetRTC(void)
{
    if (!FlagGet(FLAG_SYS_RESET_RTC_ENABLE))
        return FALSE;
    if (VarGet(VAR_0x4032) != 0x0920)
        return FALSE;
    return TRUE;
}

u16 *GetVarPointer(u16 idx)
{
    u16 *ptr;
    if (idx < VARS_START)
        return NULL;
    if (idx < SPECIAL_VARS_START)
    {
        switch (gQuestLogPlaybackState)
        {
        case 0:
        default:
            break;
        case 1:
            ptr = QuestLogGetFlagOrVarPtr(FALSE, idx);
            if (ptr != NULL)
                gSaveBlock1Ptr->vars[idx - VARS_START] = *ptr;
            break;
        case 2:
            if (IsFlagOrVarStoredInQuestLog(idx - VARS_START, TRUE) == TRUE)
            {
                gLastQuestLogStoredFlagOrVarIdx = idx - VARS_START;
                QuestLogSetFlagOrVar(FALSE, idx, gSaveBlock1Ptr->vars[idx - VARS_START]);
            }
            break;
        }
        return &gSaveBlock1Ptr->vars[idx - VARS_START];
    }
    return gSpecialVars[idx - SPECIAL_VARS_START];
}

static bool8 IsFlagOrVarStoredInQuestLog(u16 idx, bool8 isVar)
{
    if (!isVar)
    {
        if (idx < STORY_FLAGS_START)
            return FALSE;
        if (idx >= SYS_FLAGS && idx < PERMA_SYS_FLAGS_START)
            return FALSE;
    }
    else
    {
        if (idx < VAR_ICE_STEP_COUNT - VARS_START)
            return FALSE;
        if (idx >= VAR_MAP_SCENE_PALLET_TOWN_OAK - VARS_START && idx < VAR_PORTHOLE - VARS_START)
            return FALSE;
    }
    return TRUE;
}

u16 VarGet(u16 idx)
{
    u16 *ptr = GetVarPointer(idx);
    if (ptr == NULL)
        return idx;
    return *ptr;
}

bool8 VarSet(u16 idx, u16 val)
{
    u16 *ptr = GetVarPointer(idx);
    if (ptr == NULL)
        return FALSE;
    *ptr = val;
    return TRUE;
}

u8 VarGetObjectEventGraphicsId(u8 idx)
{
    return VarGet(VAR_OBJ_GFX_ID_0 + idx);
}

u8 *GetFlagAddr(u16 idx)
{
    u8 *ptr;
    if (idx == 0)
        return NULL;
    if (idx < SPECIAL_FLAGS_START)
    {
        switch (gQuestLogPlaybackState)
        {
        case 0:
        default:
            break;
        case 1:
            ptr = QuestLogGetFlagOrVarPtr(TRUE, idx);
            if (ptr != NULL)
                gSaveBlock1Ptr->flags[idx >> 3] = *ptr;
            break;
        case 2:
            if (IsFlagOrVarStoredInQuestLog(idx, FALSE) == TRUE)
            {
                gLastQuestLogStoredFlagOrVarIdx = idx;
                QuestLogSetFlagOrVar(TRUE, idx, gSaveBlock1Ptr->flags[idx / 8]);
            }
            break;
        }
        return &gSaveBlock1Ptr->flags[idx / 8];
    }
    return &sSpecialFlags[(idx - SPECIAL_FLAGS_START) / 8];
}

bool8 FlagSet(u16 idx)
{
    u8 *ptr = GetFlagAddr(idx);
    if (ptr != NULL)
        *ptr |= 1 << (idx & 7);
    return FALSE;
}

bool8 FlagClear(u16 idx)
{
    u8 *ptr = GetFlagAddr(idx);
    if (ptr != NULL)
        *ptr &= ~(1 << (idx & 7));
    return FALSE;
}

bool8 FlagGet(u16 idx)
{
    u8 *ptr = GetFlagAddr(idx);
    if (ptr == NULL)
        return FALSE;
    if (!(*ptr & 1 << (idx & 7)))
        return FALSE;
    return TRUE;
}

void ResetSpecialVars(void)
{
    gSpecialVar_0x8000 = 0;
    gSpecialVar_0x8001 = 0;
    gSpecialVar_0x8002 = 0;
    gSpecialVar_0x8003 = 0;
    gSpecialVar_0x8004 = 0;
    gSpecialVar_0x8005 = 0;
    gSpecialVar_0x8006 = 0;
    gSpecialVar_0x8007 = 0;
    gSpecialVar_0x8008 = 0;
    gSpecialVar_0x8009 = 0;
    gSpecialVar_0x800A = 0;
    gSpecialVar_0x800B = 0;
    gSpecialVar_Facing = 0;
    gSpecialVar_Result = 0;
    gSpecialVar_ItemId = 0;
    gSpecialVar_LastTalked = 0;
    gSpecialVar_MonBoxId = 0;
    gSpecialVar_MonBoxPos = 0;
    gSpecialVar_TextColor = 0;
    gSpecialVar_PrevTextColor = 0;
    gSpecialVar_0x8014 = 0;
}

u8 NuzlockeFlagSet(u8 mapsec)
{
    u8 id = NuzlockeLUT[mapsec];
    if(!FlagGet(FLAG_SYS_POKEDEX_GET))
    {   //don't start keeping track until has Pokedex
        return 1;
    }
    if(id == 0x27) //Safari Zone
    {
        if(gSaveBlock1Ptr->location.mapNum == MAP_NUM(SAFARI_ZONE_EAST))
        {
            FlagSet(FLAG_NUZLOCKE_SAFARI_EAST);
            return 0;
        }
        else if(gSaveBlock1Ptr->location.mapNum == MAP_NUM(SAFARI_ZONE_NORTH))
        {
            FlagSet(FLAG_NUZLOCKE_SAFARI_NORTH);
            return 0;
        }
        else if(gSaveBlock1Ptr->location.mapNum == MAP_NUM(SAFARI_ZONE_WEST))
        {
            FlagSet(FLAG_NUZLOCKE_SAFARI_WEST);
            return 0;
        }
        else if(gSaveBlock1Ptr->location.mapNum == MAP_NUM(SAFARI_ZONE_NORTH_WEST))
        {
            FlagSet(FLAG_NUZLOCKE_SAFARI_NORTH_WEST);
            return 0;
        }
        else if(gSaveBlock1Ptr->location.mapNum == MAP_NUM(SAFARI_ZONE_NORTH_EAST))
        {
            FlagSet(FLAG_NUZLOCKE_SAFARI_NORTH_EAST);
            return 0;
        }
        else
        {
            FlagSet(NUZLOCKE_FLAGS_START + (id - 1)); //base Safari Zone flag
            return 0;
        }
        return 0;
    }
    if(id != 0)
        FlagSet(NUZLOCKE_FLAGS_START + (id - 1));
    return 0;
}

u8 NuzlockeFlagClear(u8 mapsec)
{   //can't handle additional Safari Zone flags
    u8 id = NuzlockeLUT[mapsec];
    if(id != 0)
        FlagClear(NUZLOCKE_FLAGS_START + (id - 1));
    return 0;
}

u8 NuzlockeFlagGet(u8 mapsec)
{
    u8 id = NuzlockeLUT[mapsec];
    if(id == 0x27) //Safari Zone
    {
        if(gSaveBlock1Ptr->location.mapNum == MAP_NUM(SAFARI_ZONE_EAST))
        {
            return FlagGet(FLAG_NUZLOCKE_SAFARI_EAST);
        }
        else if(gSaveBlock1Ptr->location.mapNum == MAP_NUM(SAFARI_ZONE_NORTH))
        {
            return FlagGet(FLAG_NUZLOCKE_SAFARI_NORTH);
        }
        else if(gSaveBlock1Ptr->location.mapNum == MAP_NUM(SAFARI_ZONE_WEST))
        {
            return FlagGet(FLAG_NUZLOCKE_SAFARI_WEST);
        }
        else if(gSaveBlock1Ptr->location.mapNum == MAP_NUM(SAFARI_ZONE_NORTH_WEST))
        {
            return FlagGet(FLAG_NUZLOCKE_SAFARI_NORTH_WEST);
        }
        else if(gSaveBlock1Ptr->location.mapNum == MAP_NUM(SAFARI_ZONE_NORTH_EAST))
        {
            return FlagGet(FLAG_NUZLOCKE_SAFARI_NORTH_EAST);
        }
        else
        {
            return FlagGet(NUZLOCKE_FLAGS_START + (id - 1)); //base Safari Zone flag
        }
        return 0;
    }
    if(id != 0)
        return FlagGet(NUZLOCKE_FLAGS_START + (id - 1));
    return FALSE;
}

bool8 CheckMasterTrainerFlag(u16 flag)
{
    u8 index = flag / 8; //get byte in array
    u8 bit = flag % 8;   //get bit in byte
    u8 mask = 1 << bit;

    return (gSaveBlock1Ptr->masterTrainerFlags[index] & mask) != 0;
}

bool8 SetMasterTrainerFlag(u16 flag)
{
    u8 index = flag / 8; //get byte in array
    u8 bit = flag % 8;   //get bit in byte
    u8 mask = 1 << bit;

    gSaveBlock1Ptr->masterTrainerFlags[index] |= mask;
}

bool8 ClearMasterTrainerFlag(u16 flag)
{
    u8 index = flag / 8; //get byte in array
    u8 bit = flag % 8;   //get bit in byte
    u8 mask = 1 << bit;

    gSaveBlock1Ptr->masterTrainerFlags[index] &= ~mask;
}