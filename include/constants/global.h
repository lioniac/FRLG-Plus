#ifndef GUARD_CONSTANTS_GLOBAL_H
#define GUARD_CONSTANTS_GLOBAL_H

#define ITEM_NAME_LENGTH 14
#define POKEMON_NAME_LENGTH 10
#define OT_NAME_LENGTH 7
#define MOVE_NAME_LENGTH 12

#define VERSION_SAPPHIRE    1
#define VERSION_RUBY        2
#define VERSION_EMERALD     3
#define VERSION_FIRE_RED    4
#define VERSION_LEAF_GREEN  5
#define VERSION_GAMECUBE    15

#define LANGUAGE_JAPANESE   1
#define LANGUAGE_ENGLISH    2
#define LANGUAGE_FRENCH     3
#define LANGUAGE_ITALIAN    4
#define LANGUAGE_GERMAN     5
    // 6 goes unused but the theory is it was meant to be Korean
#define LANGUAGE_SPANISH    7

#define GAME_LANGUAGE (LANGUAGE_ENGLISH)

#define PC_ITEMS_COUNT      30
#define BAG_ITEMS_COUNT     47
#define BAG_KEYITEMS_COUNT  36
#define BAG_POKEBALLS_COUNT 13
#define BAG_TMHM_COUNT      58
#define BAG_BERRIES_COUNT   43
#define BAG_MEDICINE_COUNT  40
#define BAG_HELD_ITEMS_COUNT 52
#define OBJECT_EVENT_TEMPLATES_COUNT 64

#define QUEST_LOG_SCENE_COUNT 4

#define NUM_TOWER_CHALLENGE_TYPES 4

#define MALE   0
#define FEMALE 1
#define GENDER_COUNT 2

#define BARD_SONG_LENGTH       6
#define NUM_STORYTELLER_TALES  4
#define NUM_TRADER_ITEMS       4

#define OPTIONS_BUTTON_MODE_HELP         0
#define OPTIONS_BUTTON_MODE_LR           1
#define OPTIONS_BUTTON_MODE_L_EQUALS_A   2

#define OPTIONS_TEXT_SPEED_SLOW  0
#define OPTIONS_TEXT_SPEED_MID   1
#define OPTIONS_TEXT_SPEED_FAST  2
#define OPTIONS_TEXT_SPEED_INSTANT  3

#define OPTIONS_SOUND_MONO    0
#define OPTIONS_SOUND_STEREO  1

#define OPTIONS_BATTLE_STYLE_PREDICT  0
#define OPTIONS_BATTLE_STYLE_SHIFT  1
#define OPTIONS_BATTLE_STYLE_SET    2

#define POCKET_ITEMS        1
#define POCKET_MEDICINE     2
#define POCKET_KEY_ITEMS    3
#define POCKET_HELD_ITEMS   4
#define POCKET_POKE_BALLS   5
#define POCKET_TM_CASE      6
#define POCKET_BERRY_POUCH  7

#define NUM_BAG_POCKETS 7

#define MAX_MON_MOVES 4

#define TRAINER_ID_LENGTH 4
#define PARTY_SIZE 6
#define MULTI_PARTY_SIZE (PARTY_SIZE / 2)

#define DIR_NONE        0
#define DIR_SOUTH       1
#define DIR_NORTH       2
#define DIR_WEST        3
#define DIR_EAST        4
#define DIR_SOUTHWEST   5
#define DIR_SOUTHEAST   6
#define DIR_NORTHWEST   7
#define DIR_NORTHEAST   8

#define DIFFICULTY_NORMAL    0
#define DIFFICULTY_CHALLENGE 1
#define DIFFICULTY_EASY      2

#define IV_CALC_NORMAL 0
#define IV_CALC_PERFECT 1
#define IV_CALC_ZERO 2

#define EV_CALC_NORMAL 0
#define EV_CALC_ZERO 1

#define EASY_CHAT_BATTLE_WORDS_COUNT 6
#define FRONTIER_PARTY_SIZE         3
#define FRONTIER_DOUBLES_PARTY_SIZE 4
#define FRONTIER_MULTI_PARTY_SIZE   2
#define MAX_FRONTIER_PARTY_SIZE     FRONTIER_DOUBLES_PARTY_SIZE

// Number of facilities for Ranking Hall.
// 7 facilities for single mode + tower double mode + tower multi mode.
// Excludes link modes. See RANKING_HALL_* in include/constants/battle_frontier.h
#define HALL_FACILITIES_COUNT 9
// Received via record mixing, 1 for each player other than yourself
#define HALL_RECORDS_COUNT 3

// Battle Frontier level modes.
#define FRONTIER_LVL_50         0
#define FRONTIER_LVL_OPEN       1
#define FRONTIER_LVL_MODE_COUNT 2
#define FRONTIER_LVL_TENT       FRONTIER_LVL_MODE_COUNT // Special usage for indicating Battle Tent

// Battle Frontier level modes.
#define FRONTIER_LVL_50         0
#define FRONTIER_LVL_OPEN       1
#define FRONTIER_LVL_MODE_COUNT 2
#define FRONTIER_LVL_TENT       FRONTIER_LVL_MODE_COUNT // Special usage for indicating Battle Tent

#define APPRENTICE_COUNT 4
#define APPRENTICE_MAX_QUESTIONS 9
#define PYRAMID_BAG_ITEMS_COUNT 10

#endif //GUARD_CONSTANTS_GLOBAL_H
