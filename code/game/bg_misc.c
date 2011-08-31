/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.
Copyright (C) 2009-2010 Brian Labbie and Dave Richardson.

http://sourceforge.net/projects/alturt/

This file is part of Alturt source code.

Alturt source code is free software: you can redistribute it
and/or modify it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

Alturt source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with Alturt source code.  If not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/
//
// bg_misc.c -- both games misc functions, all completely stateless

#include "../qcommon/q_shared.h"
#include "bg_public.h"
#define CGender "models/players/orion/helmet.md3"

bg_misc_t bg_ps; //flags

nadeInfo_t bg_nadeTimer;

wp_sort_t bg_inventory;

wpinfo_t bg_weaponlist[] ={
  {  //WP_NONE, //0 Used for misc counts, rounds are for burst count.
    "",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
    ""
  },
  { //WP_KNIFE, //1
    "icons/ammo/kbar",
    {0}, //weapMode
    {-1},
    {5},
            "models/weapons2/knife/"
  },
  {// WP_BERETTA, //2
    "icons/ammo/beretta",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
    "models/weapons2/beretta/"
  },
  { //WP_DEAGLE, //3
    "icons/ammo/deserteagle",
    {0}, //weapMode
    {0},               // numClips ammo that fits in the weapon
    {0},             // rounds
    "models/weapons2/deserteagle/"
  },
  { //WP_MP5K, //4
    "icons/ammo/mp5k",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
            "models/weapons2/mp5k/"

  },
  { //WP_SPAS, //5
    "icons/ammo/spas12",
    {0}, //weapMode
    {0},               // numClips ammo that fits in the weapon
    {0},             // rounds
        "models/weapons2/spas12/"
  },
  { //WP_UMP45, //6
    "icons/ammo/ump45",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
    "models/weapons2/ump45/"

  },
  { //WP_M4, //7
    "icons/ammo/m4",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
    "models/weapons2/m4/"

  },
  { //WP_LR300, //8
    "icons/ammo/lr",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
    "models/weapons2/zm300/"

  },
  { //WP_G36, //9
    "icons/ammo/g36",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
        "models/weapons2/g36/"
  },
  { //WP_AK103, //10
    "icons/ammo/ak103",
    {0}, //weapMode
    {0},              // numClips ammo that fits in the weapon
    {0},             // rounds
            "models/weapons2/ak103/"

  },
  { //WP_HK69, //11
    "icons/ammo/hk69",
    {0}, //weapMode
    {0},               // numClips ammo that fits in the weapon
    {0},             // rounds
    "models/weapons2/hk69/"

  },
  { //WP_NEGEV, //12
    "icons/ammo/negev",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
    "models/weapons2/negev/"

  },
  { //WP_PSG1, //13
    "icons/ammo/psg1",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
    "models/weapons2/psg1/"

  },
  { //WP_SR8, //14
    "icons/ammo/sr8",
    {0}, //weapMode
    {0},               // numClips ammo that fits in the weapon
    {0},             // rounds
    "models/weapons2/sr8/"

  },
  { //WP_HE,
    "icons/ammo/grenade_he",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
        "models/weapons2/grenade/"
  },
  { //WP_SMOKE,
    "icons/ammo/grenade_smoke",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0},             // rounds
    "models/weapons2/grenade/"

  },
  { //WP_NUM_WEAPONS,
    "",
    {0}, //weapMode
    {0},                // numClips ammo that fits in the weapon
    {0}             // rounds

  }

};

/*QUAKED item_***** ( 0 0 0 ) (-16 -16 -16) (16 16 16) suspended
DO NOT USE THIS CLASS, IT JUST HOLDS GENERAL INFORMATION.
The suspended flag will allow items to hang in the air, otherwise they are dropped to the next surface.

If an item is the target of another entity, it will not spawn in until fired.

An item fires all of its targets when it is picked up.  If the toucher can't carry it, the targets won't be fired.

"notfree" if set to 1, don't spawn in free for all games
"notteam" if set to 1, don't spawn in team games
"notsingle" if set to 1, don't spawn in single player games
"wait"  override the default wait before respawning.  -1 = never respawn automatically, which can be used with targeted spawning.
"random" random number of plus or minus seconds varied from the respawn time
"count" override quantity or duration on most items.
*/

gitem_t bg_itemlist[] =
{
        {
                NULL,
                NULL,
                { NULL,
                NULL,
                NULL, NULL} ,
/* icon */              NULL,
/* pickup */    NULL,
                0,
                0,
                0,
/* precache */ "",
/* sounds */ ""
        },      // leave index 0 alone

        //
        // ARMOR
        //

/*QUAKED item_armor_shard (.3 .3 1) (-16 -16 -16) (16 16 16) suspended  1
*/
        {
                "item_armor_shard",
                "sound/misc/ar1_pkup.wav",
                { "models/powerups/armor/shard.md3",
                "models/powerups/armor/shard_sphere.md3",
                NULL, NULL} ,
/* icon */              "icons/iconr_shard",
/* pickup */    "Armor Shard",
                5,
                IT_ARMOR,
                0,
/* precache */ "",
/* sounds */ ""
        },

/*QUAKED item_armor_combat (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   2
*/
        {
                "item_armor_combat",
                "sound/misc/ar2_pkup.wav",
        { "models/powerups/armor/armor_yel.md3",
                NULL, NULL, NULL},
/* icon */              "icons/iconr_yellow",
/* pickup */    "Armor",
                50,
                IT_ARMOR,
                0,
/* precache */ "",
/* sounds */ ""
        },

/*QUAKED item_armor_body (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   3
*/
        {
                "item_armor_body",
                "sound/misc/ar2_pkup.wav",
        { "models/powerups/armor/armor_red.md3",
                NULL, NULL, NULL},
/* icon */              "icons/iconr_red",
/* pickup */    "Heavy Armor",
                100,
                IT_ARMOR,
                0,
/* precache */ "",
/* sounds */ ""
        },

        //
        // health
        //
/*QUAKED item_health_small (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   4
*/
        {
                "item_health_small",
                "sound/items/s_health.wav",
        { "models/powerups/health/small_cross.md3",
                "models/powerups/health/small_sphere.md3",
                NULL, NULL },
/* icon */              "icons/iconh_green",
/* pickup */    "5 Health",
                5,
                IT_HEALTH,
                0,
/* precache */ "",
/* sounds */ ""
        },

/*QUAKED item_health (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   5
*/
        {
                "item_health",
                "sound/items/n_health.wav",
        { "models/powerups/health/medium_cross.md3",
                "models/powerups/health/medium_sphere.md3",
                NULL, NULL },
/* icon */              "icons/iconh_yellow",
/* pickup */    "25 Health",
                25,
                IT_HEALTH,
                0,
/* precache */ "",
/* sounds */ ""
        },

/*QUAKED item_health_large (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   6
*/
        {
                "item_health_large",
                "sound/items/l_health.wav",
        { "models/powerups/health/large_cross.md3",
                "models/powerups/health/large_sphere.md3",
                NULL, NULL },
/* icon */              "icons/iconh_red",
/* pickup */    "50 Health",
                50,
                IT_HEALTH,
                0,
/* precache */ "",
/* sounds */ ""
        },

/*QUAKED item_health_mega (.3 .3 1) (-16 -16 -16) (16 16 16) suspended    7
*/
        {
                "item_health_mega",
                "sound/items/m_health.wav",
        { "models/powerups/health/mega_cross.md3",
                "models/powerups/health/mega_sphere.md3",
                NULL, NULL },
/* icon */              "icons/iconh_mega",
/* pickup */    "Mega Health",
                100,
                IT_HEALTH,
                0,
/* precache */ "",
/* sounds */ ""
        },


        //
        // WEAPONS
        //




/*QUAKED ut_weapon_g36 (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)    8
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_g36",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/g36/g36.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/g36",
/* pickup */    "H&K G36",
                40,
  IT_WEAPON,
  WP_G36,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_spas12 (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)   9
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_spas12",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/spas12/spas12.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/spas12",
/* pickup */    "Franchi SPAS-12",
                40,
  IT_WEAPON,
  WP_SPAS,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_beretta (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)    10
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_beretta",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/beretta/beretta.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/beretta",
/* pickup */    "Beretta 92g",
                40,
  IT_WEAPON,
  WP_BERETTA,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_grenade_he (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)   11
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_grenade_he",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/grenade/grenade.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/grenade_he",
/* pickup */    "HE Grenades",
                40,
  IT_WEAPON,
  WP_HE,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_knife (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)    12
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_knife",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/knife/knife.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/knife",
/* pickup */    "knife",
                40,
  IT_WEAPON,
  WP_KNIFE,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_ak103 (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)    13
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_ak103",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/ak103/ak103.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/ak103",
/* pickup */    "AK-103",
                40,
  IT_WEAPON,
  WP_AK103,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_mp5k (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)   14
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_mp5k",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/mp5k/mp5k.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/mp5k",
/* pickup */    "H&K MP5K",
                40,
  IT_WEAPON,
  WP_MP5K,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_deagle (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)   15
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_deagle",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/deserteagle/deagle.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/deserteagle",
/* pickup */    "Desert Eagle",
                40,
  IT_WEAPON,
  WP_DEAGLE,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_grenade_smoke (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)    16
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_grenade_smoke",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/grenade/grenade.md3",
  NULL, NULL, NULL},
 /* icon */             "icons/weapons/grenade_smoke",
 /* pickup */   "Smoke Grenades",
                40,
  IT_WEAPON,
  WP_SMOKE,
 /* precache */ "",
 /* sounds */ ""
 },
/*QUAKED ut_weapon_lr (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)   17
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_lr",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/zm300/lr.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/lr",
/* pickup */    "ZM LR300",
                40,
  IT_WEAPON,
  WP_LR300,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_ump45 (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)    18
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_ump45",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/ump45/ump45.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/ump45",
/* pickup */    "H&K UMP45",
                40,
  IT_WEAPON,
  WP_UMP45,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_hk69 (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)   19
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_hk69",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/hk69/hk69.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/hk69",
/* pickup */    "hk69",
                40,
  IT_WEAPON,
  WP_HK69,
/* precache */ "",
/* sounds */ "sound/weapons/grenade/hgrenb1a.wav sound/weapons/grenade/hgrenb2a.wav"
 },
/*QUAKED ut_weapon_psg1 (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)   20
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_psg1",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/psg1/psg1.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/psg1",
/* pickup */    "psg1",
                40,
  IT_WEAPON,
  WP_PSG1,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_sr8 (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)  21
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_sr8",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/sr8/sr8.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/sr8",
/* pickup */    "Remmington SR 8",
                40,
  IT_WEAPON,
  WP_SR8,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_negev (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)  22
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_negev",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/negev/negev.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/negev",
/* pickup */    "negev",
                40,
  IT_WEAPON,
  WP_NEGEV,
/* precache */ "",
/* sounds */ ""
 },
/*QUAKED ut_weapon_m4 (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)  23
 -------- KEYS --------
 count: sets the amount of ammo given to the player when picked up (default 0).
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 -------- Notes --------
 A count has to be set in order for ammo to be in the weapon when picked up
 the count system is very weird and I am unable to figure out how it works,
 but here are some usefull numbers
 count of 30   = 30 bullets 0 clips
 count of 500  = 30 bullets 1 clip
 count of 1000 = 30 bullets 2 clips
*/
 {
         "ut_weapon_m4",
  "sound/misc/w_pkup.wav",
  { "models/weapons2/m4/m4.md3",
  NULL, NULL, NULL},
/* icon */              "icons/weapons/m4",
/* pickup */    "M4 Carbine",
                40,
  IT_WEAPON,
  WP_M4,
/* precache */ "",
/* sounds */ ""
 },


/*QUAKED weapon_grapplinghook (.3 .3 1) (-16 -16 -16) (16 16 16) suspended
*/
//      {
//              "weapon_grapplinghook",
//              "sound/misc/w_pkup.wav",
//        { "models/weapons2/grapple/grapple.md3",
//              NULL, NULL, NULL},
/* icon */      //      "icons/iconw_grapple",
/* pickup *///  "Grappling Hook",
//              0,
//              IT_WEAPON,
//              WP_GRAPPLING_HOOK,
/* precache */// "",
/* sounds */// ""
//      },

        //
        // AMMO ITEMS
        //

/*QUAKED ammo_shells (.3 .3 1) (-16 -16 -16) (16 16 16) suspended  24
*/
        {
                "ammo_shells",
                "sound/misc/am_pkup.wav",
        { "models/powerups/ammo/shotgunam.md3",
                NULL, NULL, NULL},
/* icon */              "icons/ammo/spas12", //blud was icons/icona_shotgun
/* pickup */    "Shells",
                10,
                IT_AMMO,
                WP_SPAS,
/* precache */ "",
/* sounds */ ""
        },

/*QUAKED ammo_bullets (.3 .3 1) (-16 -16 -16) (16 16 16) suspended  25
*/
        {
                "ammo_bullets",
                "sound/misc/am_pkup.wav",
        { "models/powerups/ammo/machinegunam.md3",
                NULL, NULL, NULL},
/* icon */              "icons/ammo/m4", //blud was icons/icona_machinegun
/* pickup */    "Bullets",
                50,
                IT_AMMO,
                WP_M4,
/* precache */ "",
/* sounds */ ""
        },

/*QUAKED ammo_grenades (.3 .3 1) (-16 -16 -16) (16 16 16) suspended  26
*/
        {
                "ammo_grenades",
                "sound/misc/am_pkup.wav",
        { "models/powerups/ammo/grenadeam.md3",
                NULL, NULL, NULL},
/* icon */              "icons/ammo/hk69",
/* pickup */    "Grenades",
                5,
                IT_AMMO,
                WP_HK69,
/* precache */ "",
/* sounds */ ""
        },
        //
        //Equipment Items
        //

 /*QUAKED ut_item_silencer (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)  27
 -------- KEYS --------
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
 */

/*QUAKED ut_item_nvg (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)
 -------- KEYS --------
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
*/

/*QUAKED ut_item_vest (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)
 -------- KEYS --------
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
*/

/*QUAKED ut_item_laser (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)  28
 -------- KEYS --------
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
*/

/*QUAKED ut_item_medkit (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
*/

/*QUAKED ut_item_helmet (0.3 0.9 0.4)(-5 -5 -5) (5 5 5)  29
 -------- KEYS --------
 gametype : Specifies gametypes for the weapon to be in in. If this key is not used, the weapon will be in all gametypes. List types in this format: 01234
 -------- SPAWNFLAGS --------
 spawnflags : set to 1 to make suspended so the item will spawn where it was placed in map and won't drop to the floor. (default 0)
*/
        //
        // HOLDABLE ITEMS
        //

/*QUAKED holdable_medkit (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   31
*/
        {
                "holdable_medkit",
                "sound/items/holdable.wav",
        {
                "models/powerups/holdable/medkit.md3",
                "models/powerups/holdable/medkit_sphere.md3",
                NULL, NULL},
/* icon */              "icons/medkit",
/* pickup */    "Medkit",
                60,
                IT_HOLDABLE,
                HI_MEDKIT,
/* precache */ "",
/* sounds */ "sound/items/use_medkit.wav"
        },

        //
        // POWERUP ITEMS
        //

        /*QUAKED item_quad (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   32
        */
        {
          "ut_item_vest",
          "sound/misc/w_pkup.wav",
          { "models/players/athena/vest.md3",
          "models/players/orion/vest.md3",
          NULL, NULL },
/* icon */              "icons/items/vest",
/* pickup */    "Kevlar Vest",
                30,
                IT_POWERUP,
                PW_VEST,
/* precache */ "",
/* sounds */ "sound/items/damage2.wav sound/items/damage3.wav"
        },

/*QUAKED item_enviro (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   33
*/
        {
          "ut_item_helmet",
          "sound/misc/w_pkup.wav",
          { "models/players/orion/helmet.md3",
          NULL, NULL, NULL},
/* icon */              "icons/items/helmet",
/* pickup */    "Helmet",
                60,
                IT_POWERUP,
                PW_HELMET,
/* precache */ "",
/* sounds */ "sound/items/airout.wav sound/items/protect3.wav"
        },

/*QUAKED item_haste (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   34
*/
        {
          "ut_item_laser",
          "sound/misc/w_pkup.wav",
          { "models/weapons2/m4/m4_laser.md3",
          NULL, NULL, NULL},
/* icon */              "icons/items/laser",
/* pickup */    "Laser Sight",
                60,
                IT_POWERUP,
                PW_LASERSIGHT,
/* precache */ "",
/* sounds */ ""
        },

/*QUAKED item_invis (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   35
*/
        {
          "ut_item_silencer",
          "sound/misc/w_pkup.wav",
          { "models/weapons2/m4/m4_silencer.md3",
          NULL, NULL, NULL},
/* icon */              "icons/items/silencer",
/* pickup */    "Silencer",
                60,
                IT_POWERUP,
                PW_SILENCER,
/* precache */ "",
/* sounds */ ""
        },

/*QUAKED item_regen (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   36
*/
        {
          "item_regen",
          "sound/items/regeneration.wav",
          { "models/powerups/instant/regen.md3",
          "models/powerups/instant/regen_ring.md3",
          NULL, NULL },
/* icon */              "icons/regen",
/* pickup */    "Ammo",
                30,
                IT_POWERUP,
                PW_AMMO,
/* precache */ "",
/* sounds */ "sound/items/regen.wav"
        },

/*QUAKED item_flight (.3 .3 1) (-16 -16 -16) (16 16 16) suspended   37
*/
        {
          "item_flight",
          "sound/items/flight.wav",
          { "models/powerups/instant/flight.md3",
          "models/powerups/instant/flight_ring.md3",
          NULL, NULL },
/* icon */              "icons/flight",
/* pickup */    "nvg",
                60,
                IT_POWERUP,
                PW_NVG,
/* precache */ "",
/* sounds */ "sound/items/flight.wav"
        },



/*QUAKED team_CTF_redflag (1 0 0) (-16 -16 -16) (16 16 16)   38
Only in CTF games
*/
        {
                "team_CTF_redflag",
                NULL,
        { "models/flags/r_flag.md3",
                NULL, NULL, NULL },
/* icon */              "icons/iconf_red1",
/* pickup */    "Red Flag",
                0,
                IT_TEAM,
                PW_REDFLAG,
/* precache */ "",
/* sounds */ ""
        },

/*QUAKED team_CTF_blueflag (0 0 1) (-16 -16 -16) (16 16 16)   39
Only in CTF games
*/
        {
                "team_CTF_blueflag",
                NULL,
        { "models/flags/b_flag.md3",
                NULL, NULL, NULL },
/* icon */              "icons/iconf_blu1",
/* pickup */    "Blue Flag",
                0,
                IT_TEAM,
                PW_BLUEFLAG,
/* precache */ "",
/* sounds */ ""
        },



        // end of list marker
        {NULL}
};

int             bg_numItems = sizeof(bg_itemlist) / sizeof(bg_itemlist[0]) - 1;


/*
==============
BG_FindItemForPowerup
==============
*/
gitem_t *BG_FindItemForPowerup( powerup_t pw ) {
        int             i;

        for ( i = 0 ; i < bg_numItems ; i++ ) {
                if ( (bg_itemlist[i].giType == IT_POWERUP ||
                                        bg_itemlist[i].giType == IT_TEAM ||
                                        bg_itemlist[i].giType == IT_PERSISTANT_POWERUP) &&
                        bg_itemlist[i].giTag == pw ) {
                        return &bg_itemlist[i];
                }
        }

        return NULL;
}


/*
==============
BG_FindItemForHoldable
==============
*/
gitem_t *BG_FindItemForHoldable( holdable_t pw ) {
        int             i;

        for ( i = 0 ; i < bg_numItems ; i++ ) {
                if ( bg_itemlist[i].giType == IT_HOLDABLE && bg_itemlist[i].giTag == pw ) {
                        return &bg_itemlist[i];
                }
        }

        Com_Error( ERR_DROP, "HoldableItem not found" );

        return NULL;
}






/*
===============
BG_FindItemForWeapon

===============
*/
gitem_t *BG_FindItemForWeapon( weapon_t weapon ) {
        gitem_t *it;

        for ( it = bg_itemlist + 1 ; it->classname ; it++) {
                if ( it->giType == IT_WEAPON && it->giTag == weapon ) {
                        return it;
                }
        }

        Com_Error( ERR_DROP, "Couldn't find item for weapon %i", weapon);
        return NULL;
}

/*
===============
BG_FindItem

===============
*/
gitem_t *BG_FindItem( const char *pickupName ) {
        gitem_t *it;

        for ( it = bg_itemlist + 1 ; it->classname ; it++ ) {
                if ( !Q_stricmp( it->pickup_name, pickupName ) )
                        return it;
        }

        return NULL;
}

/*
============
BG_PlayerTouchesItem

Items can be picked up without actually touching their physical bounds to make
grabbing them easier
============
*/
qboolean        BG_PlayerTouchesItem( playerState_t *ps, entityState_t *item, int atTime ) {
        vec3_t          origin;

        BG_EvaluateTrajectory( &item->pos, atTime, origin );

        // we are ignoring ducked differences here
        if ( ps->origin[0] - origin[0] > 44
                || ps->origin[0] - origin[0] < -50
                || ps->origin[1] - origin[1] > 36
                || ps->origin[1] - origin[1] < -36
                || ps->origin[2] - origin[2] > 36
                || ps->origin[2] - origin[2] < -36 ) {
                return qfalse;
        }

        return qtrue;
}



/*
================
BG_CanItemBeGrabbed

Returns false if the item should not be picked up.
This needs to be the same for client side prediction and server use.
================
*/
qboolean BG_CanItemBeGrabbed( int gametype, const entityState_t *ent, const playerState_t *ps ) {
        gitem_t *item;
//int i;

        if ( ent->modelindex < 1 || ent->modelindex >= bg_numItems ) {
          Com_Error( ERR_DROP, "BG_CanItemBeGrabbed: index %i out of range", ent->modelindex );
        }

        item = &bg_itemlist[ent->modelindex];
        
//Com_Printf("!(BG_HasSidearm ( ps ) = %i \n", !(BG_HasSidearm ( ps ) ));
//Com_Printf("bg_inventory.sort[ps->clientNum][SIDEARM] = %i & \t", bg_inventory.sort[ps->clientNum][SIDEARM]);
//Com_Printf("item->giTag = %d\n", item->giTag );
//Com_Printf("BG_Sidearm( item->giTag )  = %i\n", BG_Sidearm( item->giTag ) );

        switch( item->giType ) {
        case IT_WEAPON:

// Xamis
          if( ps->weaponTime > 0)
            return qfalse;
          if (item->giTag == WP_KNIFE){
              if (  bg_weaponlist[item->giTag].rounds[ ps->clientNum] < 5 ){
                    return qtrue;
           }else
           return qfalse;
}
            if ( BG_Sidearm( item->giTag )  ){
                if (bg_inventory.sort[ps->clientNum][SIDEARM] == item->giTag)                                                    
             return qtrue; //same as weapon in inventory, add as ammo --Xamis
                 if (bg_inventory.sort[ps->clientNum][SIDEARM]){
                  return qfalse;  
                 }
            }else if ( BG_Secondary( item->giTag )  ){
              if (bg_inventory.sort[ps->clientNum][SECONDARY] == item->giTag){
                return qtrue; //same as weapon in inventory, add as ammo --Xamis
              }
              if (bg_inventory.sort[ps->clientNum][PRIMARY] ==WP_NEGEV ){
                        return qfalse; 
              } 
	if (bg_inventory.sort[ps->clientNum][PRIMARY]){
                        if ((bg_inventory.sort[ps->clientNum][SECONDARY]))
                        return qfalse; 
              } 
            }else if (BG_Primary( item->giTag )){
              if (bg_inventory.sort[ps->clientNum][PRIMARY] == item->giTag){
                return qtrue; //same as weapon in inventory, add as ammo --Xamis
              }
              if (bg_inventory.sort[ps->clientNum][PRIMARY]){
                return qfalse;//do not have a primary --Xamis
              }
            }else if ( BG_Grenade(item->giTag) ) {
              if (  bg_weaponlist[item->giTag].numClips[ ps->clientNum] < 2 )
                    return qtrue;
           }else
           return qfalse;

// end


        case IT_AMMO:
            if(item->giTag == WP_KNIFE){
                return qfalse;
            }
          if ( bg_weaponlist[ item->giTag].numClips[ ps->clientNum] >= 6 ) {
                        return qfalse;          // can't hold any more
                }
                return qtrue;

        case IT_ARMOR:
#ifdef MISSIONPACK
          //      if( bg_itemlist[ps->stats[STAT_PERSISTANT_POWERUP]].giTag == PW_SCOUT ) {
           //             return qfalse;
           //     }

                // we also clamp armor to the maxhealth for handicapping
           //     if( bg_itemlist[ps->stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
          //              upperBound = ps->stats[STAT_MAX_HEALTH];
           //     }
          //      else {
            //            upperBound = ps->stats[STAT_MAX_HEALTH] * 2;
            //    }

            //    if ( ps->stats[STAT_ARMOR] >= upperBound ) {
             //           return qfalse;
           //     }
#else
//                if ( ps->stats[STAT_ARMOR] >= ps->stats[STAT_MAX_HEALTH] * 2 ) {
//                        return qfalse;
//                }
#endif
                return qtrue;

        case IT_HEALTH:
                // small and mega healths will go over the max, otherwise
                // don't pick up if already at max
#ifdef MISSIONPACK
             //   if( bg_itemlist[ps->stats[STAT_PERSISTANT_POWERUP]].giTag == PW_GUARD ) {
             //           upperBound = ps->stats[STAT_MAX_HEALTH];
              //  }
             //   else
#endif
                if ( item->quantity == 5 || item->quantity == 100 ) {
                        if ( ps->stats[STAT_HEALTH] >= STAT_MAX_HEALTH * 2 ) {
                                return qfalse;
                        }
                        return qtrue;
                }

                if ( ps->stats[STAT_HEALTH] >= STAT_MAX_HEALTH ) {
                        return qfalse;
                }
                return qtrue;

        case IT_POWERUP:
return qtrue;
             // powerups are always picked up

#ifdef MISSIONPACK
        case IT_PERSISTANT_POWERUP:
                // can only hold one item at a time
//                if ( ps->stats[STAT_PERSISTANT_POWERUP] ) {
//                        return qfalse;
               // }

                // check team only
                if( ( ent->generic1 & 2 ) && ( ps->persistant[PERS_TEAM] != TEAM_RED ) ) {
                        return qfalse;
                }
                if( ( ent->generic1 & 4 ) && ( ps->persistant[PERS_TEAM] != TEAM_BLUE ) ) {
                        return qfalse;
                }

                return qfalse;
#endif

        case IT_TEAM: // team items, such as flags
#ifdef MISSIONPACK
                if( gametype == GT_BOMB ) {
                        // neutral flag can always be picked up
                        if( item->giTag == PW_NEUTRALFLAG ) {
                                return qtrue;
                        }
                        if (ps->persistant[PERS_TEAM] == TEAM_RED) {
                                if (item->giTag == PW_BLUEFLAG  && ps->powerups[PW_NEUTRALFLAG] ) {
                                        return qtrue;
                                }
                        } else if (ps->persistant[PERS_TEAM] == TEAM_BLUE) {
                                if (item->giTag == PW_REDFLAG  && ps->powerups[PW_NEUTRALFLAG] ) {
                                        return qtrue;
                                }
                        }
                }
#endif
                if( gametype == GT_CTF ) {
                        // ent->modelindex2 is non-zero on items if they are dropped
                        // we need to know this because we can pick up our dropped flag (and return it)
                        // but we can't pick up our flag at base
                        if (ps->persistant[PERS_TEAM] == TEAM_RED) {
                                if (item->giTag == PW_BLUEFLAG ||
                                        (item->giTag == PW_REDFLAG && ent->modelindex2) ||
                                        (item->giTag == PW_REDFLAG && ps->powerups[PW_BLUEFLAG]) )
                                        return qtrue;
                        } else if (ps->persistant[PERS_TEAM] == TEAM_BLUE) {
                                if (item->giTag == PW_REDFLAG ||
                                        (item->giTag == PW_BLUEFLAG && ent->modelindex2) ||
                                        (item->giTag == PW_BLUEFLAG && ps->powerups[PW_REDFLAG]) )
                                        return qtrue;
                        }
                }

#ifdef MISSIONPACK
                if( gametype == GT_BOMB ) {
                        return qtrue;
                }
#endif
                return qfalse;

        case IT_HOLDABLE:
                // can only hold one item at a time
//                if ( ps->stats[STAT_HOLDABLE_ITEM] ) {
                        return qfalse;
//                }
              //  return qtrue;

        case IT_BAD:
            Com_Error( ERR_DROP, "BG_CanItemBeGrabbed: IT_BAD" );
        default:
#ifndef Q3_VM
#ifndef NDEBUG
          Com_Printf("BG_CanItemBeGrabbed: unknown enum %d\n", item->giType );
#endif
#endif
         break;
        }

        return qfalse;
}

//======================================================================

/*
================
BG_EvaluateTrajectory

================
*/
void BG_EvaluateTrajectory( const trajectory_t *tr, int atTime, vec3_t result ) {
        float           deltaTime;
        float           phase;

        switch( tr->trType ) {
        case TR_STATIONARY:
        case TR_INTERPOLATE:
                VectorCopy( tr->trBase, result );
                break;
        case TR_LINEAR:
                deltaTime = ( atTime - tr->trTime ) * 0.001;    // milliseconds to seconds
                VectorMA( tr->trBase, deltaTime, tr->trDelta, result );
                break;
        case TR_SINE:
                deltaTime = ( atTime - tr->trTime ) / (float) tr->trDuration;
                phase = sin( deltaTime * M_PI * 2 );
                VectorMA( tr->trBase, phase, tr->trDelta, result );
                break;
        case TR_LINEAR_STOP:
                if ( atTime > tr->trTime + tr->trDuration ) {
                        atTime = tr->trTime + tr->trDuration;
                }
                deltaTime = ( atTime - tr->trTime ) * 0.001;    // milliseconds to seconds
                if ( deltaTime < 0 ) {
                        deltaTime = 0;
                }
                VectorMA( tr->trBase, deltaTime, tr->trDelta, result );
                break;
        case TR_GRAVITY:
                deltaTime = ( atTime - tr->trTime ) * 0.001;    // milliseconds to seconds
                VectorMA( tr->trBase, deltaTime, tr->trDelta, result );
                result[2] -= 0.5 * DEFAULT_GRAVITY * deltaTime * deltaTime;             // FIXME: local gravity...
                break;
        default:
                Com_Error( ERR_DROP, "BG_EvaluateTrajectory: unknown trType: %i", tr->trTime );
                break;
        }
}

/*
================
BG_EvaluateTrajectoryDelta

For determining velocity at a given time
================
*/
void BG_EvaluateTrajectoryDelta( const trajectory_t *tr, int atTime, vec3_t result ) {
        float   deltaTime;
        float   phase;

        switch( tr->trType ) {
        case TR_STATIONARY:
        case TR_INTERPOLATE:
                VectorClear( result );
                break;
        case TR_LINEAR:
                VectorCopy( tr->trDelta, result );
                break;
        case TR_SINE:
                deltaTime = ( atTime - tr->trTime ) / (float) tr->trDuration;
                phase = cos( deltaTime * M_PI * 2 );    // derivative of sin = cos
                phase *= 0.5;
                VectorScale( tr->trDelta, phase, result );
                break;
        case TR_LINEAR_STOP:
                if ( atTime > tr->trTime + tr->trDuration ) {
                        VectorClear( result );
                        return;
                }
                VectorCopy( tr->trDelta, result );
                break;
        case TR_GRAVITY:
                deltaTime = ( atTime - tr->trTime ) * 0.001;    // milliseconds to seconds
                VectorCopy( tr->trDelta, result );
                result[2] -= DEFAULT_GRAVITY * deltaTime;               // FIXME: local gravity...
                break;
        default:
                Com_Error( ERR_DROP, "BG_EvaluateTrajectoryDelta: unknown trType: %i", tr->trTime );
                break;
        }
}

char *eventnames[] = {
        "EV_NONE",
        "EV_BANDAGE",
        "EV_FOOTSTEP",
        "EV_FOOTSTEP_METAL",
        "EV_FOOTSTEP_LADDER",
        "EV_FOOTSPLASH",
        "EV_FOOTWADE",
        "EV_SWIM",

        "EV_STEP_4",
        "EV_STEP_8",
        "EV_STEP_12",
        "EV_STEP_16",


        "EV_FALL_SHORT",
        "EV_FALL_MEDIUM",
        "EV_FALL_FAR",

        "EV_JUMP_PAD",                  // boing sound at origin", jump sound on player

        "EV_JUMP",
        "EV_BLEED",
        "EV_WATER_TOUCH",       // foot touches
        "EV_WATER_LEAVE",       // foot leaves
        "EV_WATER_UNDER",       // head touches
        "EV_WATER_CLEAR",       // head leaves

        "EV_ITEM_PICKUP",                       // normal item pickups are predictable
        "EV_GLOBAL_ITEM_PICKUP",        // powerup / team sounds are broadcast to everyone

        "EV_NOAMMO",
        "EV_NONADES",
        "EV_POWERSLIDE",
        "EV_CHANGE_WEAPON",
        "EV_FIRE_WEAPON",
        "EV_ZOOM_RESET",

        "EV_USE_ITEM0",
        "EV_USE_ITEM1",
        "EV_USE_ITEM2",
        "EV_USE_ITEM3",
        "EV_USE_ITEM4",
        "EV_USE_ITEM5",
        "EV_USE_ITEM6",
        "EV_USE_ITEM7",
        "EV_USE_ITEM8",
        "EV_USE_ITEM9",
        "EV_USE_ITEM10",
        "EV_USE_ITEM11",
        "EV_USE_ITEM12",
        "EV_USE_ITEM13",
        "EV_USE_ITEM14",
        "EV_USE_ITEM15",

        "EV_ITEM_RESPAWN",
        "EV_ITEM_POP",
        "EV_PLAYER_TELEPORT_IN",
        "EV_PLAYER_TELEPORT_OUT",

        "EV_GRENADE_BOUNCE",            // eventParm will be the soundindex

        "EV_GENERAL_SOUND",
        "EV_GLOBAL_SOUND",              // no attenuation
        "EV_GLOBAL_TEAM_SOUND",

        "EV_BULLET_HIT_FLESH",
        "EV_BULLET_HIT_WALL",

        "EV_MISSILE_HIT",
        "EV_MISSILE_MISS",
        "EV_MISSILE_MISS_METAL",
        "EV_RAILTRAIL",
        "EV_SHOTGUN",
        "EV_BULLET",                            // otherEntity is the shooter

        "EV_PAIN",
        "EV_DEATH1",
        "EV_DEATH2",
        "EV_DEATH3",
        "EV_OBITUARY",

        "EV_POWERUP_SILENCER",
        "EV_POWERUP_BATTLESUIT",
        "EV_POWERUP_REGEN",

        "EV_GIB_PLAYER",                        // gib a previously living player
        "EV_SCOREPLUM",                 // score plum

//#ifdef MISSIONPACK
        "EV_PROXIMITY_MINE_STICK",
        "EV_PROXIMITY_MINE_TRIGGER",
        "EV_KAMIKAZE",                  // kamikaze explodes
        "EV_OBELISKEXPLODE",            // obelisk explodes
        "EV_INVUL_IMPACT",              // invulnerability sphere impact
        "EV_JUICED",                            // invulnerability juiced effect
        "EV_LIGHTNINGBOLT",             // lightning bolt bounced of invulnerability sphere
//#endif

        "EV_DEBUG_LINE",
        "EV_STOPLOOPINGSOUND",
        "EV_TAUNT"

};

/*
===============
BG_AddPredictableEventToPlayerstate

Handles the sequence numbers
===============
*/

void    trap_Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize );

void BG_AddPredictableEventToPlayerstate( int newEvent, int eventParm, playerState_t *ps ) {

#ifdef _DEBUG
        {
                char buf[256];
                trap_Cvar_VariableStringBuffer("showevents", buf, sizeof(buf));
                if ( atof(buf) != 0 ) {
#ifdef QAGAME
                        Com_Printf(" game event svt %5d -> %5d: num = %20s parm %d\n", ps->pmove_framecount/*ps->commandTime*/, ps->eventSequence, eventnames[newEvent], eventParm);
#else
                        Com_Printf("Cgame event svt %5d -> %5d: num = %20s parm %d\n", ps->pmove_framecount/*ps->commandTime*/, ps->eventSequence, eventnames[newEvent], eventParm);
#endif
                }
        }
#endif
        ps->events[ps->eventSequence & (MAX_PS_EVENTS-1)] = newEvent;
        ps->eventParms[ps->eventSequence & (MAX_PS_EVENTS-1)] = eventParm;
        ps->eventSequence++;
}

/*
========================
BG_TouchJumpPad
========================
*/
void BG_TouchJumpPad( playerState_t *ps, entityState_t *jumppad ) {
        vec3_t  angles;
        float p;
        int effectNum;

        // spectators don't use jump pads
        if ( ps->pm_type != PM_NORMAL ) {
                return;
        }

        // if we didn't hit this same jumppad the previous frame
        // then don't play the event sound again if we are in a fat trigger
        if ( ps->jumppad_ent != jumppad->number ) {

                vectoangles( jumppad->origin2, angles);
                p = fabs( AngleNormalize180( angles[PITCH] ) );
                if( p < 45 ) {
                        effectNum = 0;
                } else {
                        effectNum = 1;
                }
                BG_AddPredictableEventToPlayerstate( EV_JUMP_PAD, effectNum, ps );
        }
        // remember hitting this jumppad this frame
        ps->jumppad_ent = jumppad->number;
        ps->jumppad_frame = ps->pmove_framecount;
        // give the player the velocity from the jumppad
        VectorCopy( jumppad->origin2, ps->velocity );
}

/*
========================
BG_PlayerStateToEntityState

This is done after each set of usercmd_t on the server,
and after local prediction on the client
========================
*/
void BG_PlayerStateToEntityState( playerState_t *ps, entityState_t *s, qboolean snap ) {
        int             i;

        if ( ps->pm_type == PM_INTERMISSION || ps->pm_type == PM_SPECTATOR ) {
                s->eType = ET_INVISIBLE;
        } else if ( ps->stats[STAT_HEALTH] <= GIB_HEALTH ) {
                s->eType = ET_INVISIBLE;
        } else {
                s->eType = ET_PLAYER;
        }

        s->number = ps->clientNum;

        s->pos.trType = TR_INTERPOLATE;
        VectorCopy( ps->origin, s->pos.trBase );
        if ( snap ) {
                SnapVector( s->pos.trBase );
        }
        // set the trDelta for flag direction
        VectorCopy( ps->velocity, s->pos.trDelta );

        s->apos.trType = TR_INTERPOLATE;
        VectorCopy( ps->viewangles, s->apos.trBase );
        if ( snap ) {
                SnapVector( s->apos.trBase );
        }

        s->angles2[YAW] = ps->movementDir;
        s->legsAnim = ps->legsAnim;
        s->torsoAnim = ps->torsoAnim;
        s->clientNum = ps->clientNum;           // ET_PLAYER looks here instead of at number
                                                                                // so corpses can also reference the proper config
        s->eFlags = ps->eFlags;
        if ( ps->stats[STAT_HEALTH] <= 0 ) {
                s->eFlags |= EF_DEAD;
        } else {
                s->eFlags &= ~EF_DEAD;
        }

        if ( ps->externalEvent ) {
                s->event = ps->externalEvent;
                s->eventParm = ps->externalEventParm;
        } else if ( ps->entityEventSequence < ps->eventSequence ) {
                int             seq;

                if ( ps->entityEventSequence < ps->eventSequence - MAX_PS_EVENTS) {
                        ps->entityEventSequence = ps->eventSequence - MAX_PS_EVENTS;
                }
                seq = ps->entityEventSequence & (MAX_PS_EVENTS-1);
                s->event = ps->events[ seq ] | ( ( ps->entityEventSequence & 3 ) << 8 );
                s->eventParm = ps->eventParms[ seq ];
                ps->entityEventSequence++;
        }

        s->weapon = ps->weapon;
        s->groundEntityNum = ps->groundEntityNum;

        s->powerups = 0;
        for ( i = 0 ; i < MAX_POWERUPS ; i++ ) {
                if ( ps->powerups[ i ] ) {
                        s->powerups |= 1 << i;
                }
        }
  // have to get the surfNormal through somehow...
        VectorCopy( ps->grapplePoint, s->angles2 );

        s->loopSound = ps->loopSound;
        s->generic1 = ps->generic1;
}

/*
========================
BG_PlayerStateToEntityStateExtraPolate

This is done after each set of usercmd_t on the server,
and after local prediction on the client
========================
*/
void BG_PlayerStateToEntityStateExtraPolate( playerState_t *ps, entityState_t *s, int time, qboolean snap ) {
        int             i;

        if ( ps->pm_type == PM_INTERMISSION || ps->pm_type == PM_SPECTATOR ) {
                s->eType = ET_INVISIBLE;
        } else if ( ps->stats[STAT_HEALTH] <= GIB_HEALTH ) {
                s->eType = ET_INVISIBLE;
        } else {
                s->eType = ET_PLAYER;
        }

        s->number = ps->clientNum;

        s->pos.trType = TR_LINEAR_STOP;
        VectorCopy( ps->origin, s->pos.trBase );
        if ( snap ) {
                SnapVector( s->pos.trBase );
        }
        // set the trDelta for flag direction and linear prediction
        VectorCopy( ps->velocity, s->pos.trDelta );
        // set the time for linear prediction
        s->pos.trTime = time;
        // set maximum extra polation time
        s->pos.trDuration = 50; // 1000 / sv_fps (default = 20)

        s->apos.trType = TR_INTERPOLATE;
        VectorCopy( ps->viewangles, s->apos.trBase );
        if ( snap ) {
                SnapVector( s->apos.trBase );
        }

        s->angles2[YAW] = ps->movementDir;
        s->legsAnim = ps->legsAnim;
        s->torsoAnim = ps->torsoAnim;
        s->clientNum = ps->clientNum;           // ET_PLAYER looks here instead of at number
                                                                                // so corpses can also reference the proper config
        s->eFlags = ps->eFlags;
        if ( ps->stats[STAT_HEALTH] <= 0 ) {
                s->eFlags |= EF_DEAD;
        } else {
                s->eFlags &= ~EF_DEAD;
        }

        if ( ps->externalEvent ) {
                s->event = ps->externalEvent;
                s->eventParm = ps->externalEventParm;
        } else if ( ps->entityEventSequence < ps->eventSequence ) {
                int             seq;

                if ( ps->entityEventSequence < ps->eventSequence - MAX_PS_EVENTS) {
                        ps->entityEventSequence = ps->eventSequence - MAX_PS_EVENTS;
                }
                seq = ps->entityEventSequence & (MAX_PS_EVENTS-1);
                s->event = ps->events[ seq ] | ( ( ps->entityEventSequence & 3 ) << 8 );
                s->eventParm = ps->eventParms[ seq ];
                ps->entityEventSequence++;
        }

        s->weapon = ps->weapon;
        s->groundEntityNum = ps->groundEntityNum;

        s->powerups = 0;
        for ( i = 0 ; i < MAX_POWERUPS ; i++ ) {
                if ( ps->powerups[ i ] ) {
                        s->powerups |= 1 << i;
                }
        }

        s->loopSound = ps->loopSound;
        s->generic1 = ps->generic1;
}


void   BG_PlayerTouchesSmoke( int num, int stats[ ]){
//  stats[ STAT_SMOKE ] = num;
}

qboolean BG_PlayerInSmoke( int stats[ ] ){
//  if ( stats[ STAT_SMOKE ] == 1 ) return qtrue;
        return qfalse;

}

void BG_SelectItem( int item, int stats[ ] )
{
  stats[STAT_SELECTED_ITEM]=item;
}

// loadout related  -prototype in bg_public.h --xamis


void BG_PackWeapon( int weapon, int stats[ ] )
{
  unsigned int  weaponList;
  
    // create one big list with from our 2
  weaponList = (unsigned int)stats[ STAT_WEAPONS ] | ((unsigned int)stats[ STAT_WEAPONS_EXT ] << 16 );
    // add that bit to our "bigger list"
  weaponList |= ( 1 << weapon );
    // statweapons 1 is the lower half part ( 0-15)
  stats[ STAT_WEAPONS ] = weaponList & 0x0000FFFF;
    // weapons2 is the upper part ( 17-31 )
  stats[ STAT_WEAPONS_EXT ] = ( weaponList & 0xFFFF0000 ) >> 16;
}

void BG_ClearWeapons( int stats[ ] )
{
  stats[ STAT_WEAPONS ] = stats[ STAT_WEAPONS_EXT ] = 0;
}

void BG_RemoveWeapon( int weapon, int stats[ ] )
{
  int  weaponList;
  int  i;

    // create the big list
  weaponList = (unsigned int)stats[ STAT_WEAPONS ] | ( (unsigned int)stats[ STAT_WEAPONS_EXT ] << 16 );

  BG_ClearWeapons( stats );

  for ( i = 0; i < WP_NUM_WEAPONS; i++ )
  {
    if ( weaponList & ( 1 << i ) && i != weapon )
    {
      BG_PackWeapon( i, stats );
    }
  }
}

/*
=====================
BG_HasWeapon
=====================
*/

qboolean BG_HasWeapon( int weapon, int stats[ ] )
{
	if (weapon == WP_NONE)
	{
		//you can't actually "have" WP_NONE
		return qfalse;
	}

    if (weapon < MAX_WEAPONS ){
     // Com_Printf( "weapon = %i (unsigned int)stats[STAT_WEAPONS] & (1 << weapon) = %i\n", weapon,  (unsigned int)stats[STAT_WEAPONS] & (1 << weapon));
      return (unsigned int)stats[STAT_WEAPONS] & (1 << weapon);
    }
  //  Com_Printf( "weapon - 16 = %i (unsigned int)stats[STAT_WEAPONS_EXT] & (1 << weapon) = %i\n",(weapon - 16),(unsigned int) stats[STAT_WEAPONS_EXT] & ( 1 << (weapon - 16) ));
    return (unsigned int) stats[STAT_WEAPONS_EXT] & ( 1 << (weapon - 16) );

}




/*
================
BG_HasPistol

================
*/

qboolean BG_HasSidearm (const  playerState_t *ps ) {
    if (BG_HasWeapon(WP_DEAGLE , (int*)ps->stats ) ||     
    BG_HasWeapon(WP_BERETTA , (int*)ps->stats ) )
     return qtrue;

    return qfalse;
}

/*
================
BG_HasPrimary

================
*/

qboolean BG_HasPrimary  (const  playerState_t *ps ) {
    if (BG_HasWeapon(WP_AK103 , (int*)ps->stats ) )
        return qtrue;
    if (BG_HasWeapon(WP_M4 , (int*)ps->stats ) )
        return qtrue;
    if (BG_HasWeapon(WP_PSG1 , (int*)ps->stats ) )
        return qtrue;
            if (BG_HasWeapon(WP_SR8 , (int*)ps->stats ) )
        return qtrue;
    if (BG_HasWeapon(WP_G36 , (int*)ps->stats ) )
        return qtrue;
    if (BG_HasWeapon(WP_LR300 , (int*)ps->stats ) )
        return qtrue;
            if (BG_HasWeapon(WP_NEGEV , (int*)ps->stats ) )
        return qtrue;

    return qfalse;
}

/*
================
BG_HasSecondary

================
*/

qboolean BG_HasSecondary (const  playerState_t *ps ) {
    if (BG_HasWeapon(WP_MP5K , (int*)ps->stats ) )
        return qtrue;
    if (BG_HasWeapon(WP_UMP45 , (int*)ps->stats ) )
        return qtrue;
    if (BG_HasWeapon(WP_SPAS , (int*)ps->stats ) )
        return qtrue;

    return qfalse;
}



/*
=====================
BG_GetPrimary
=====================
*/

int             BG_GetPrimary( int stats [ ] )
{
    int i;

    for ( i=WP_NUM_WEAPONS-1;i>WP_NONE;i--)
    {
        if ( BG_HasWeapon( i, stats ) )
        {
            if ( BG_Primary( i ) )
                return i;
        }
    }
    return WP_NONE;
}


/*
=====================
BG_GetSecondary
=====================
*/
int             BG_GetSecondary( int stats [ ] )
{
    int i;

    for ( i=WP_NUM_WEAPONS-1;i>WP_NONE;i--)
    {
          if ( BG_HasWeapon( i, stats ) )
        {
            if ( BG_Secondary( i ) )
                return i;
        }
    }
    return WP_NONE;
}





/*
================
BG_Melee

can use this to implement more melee weapons
================
*/
qboolean BG_Melee ( int weapon ) {
    switch (weapon) {
    case WP_KNIFE:
        return qtrue;
    default:
        return qfalse;
    }
}

/*
================
BG_Sidearm


================
*/
qboolean BG_Sidearm( int weapon ) {
    switch (weapon) {
    case WP_BERETTA:
    case WP_DEAGLE:
        return qtrue;
    default:
        return qfalse;
    }
}

/*
================
BG_Primary


================
*/

qboolean BG_Primary ( int weapon ) {
    switch (weapon) {
    case WP_AK103:
    case WP_M4:
    case WP_PSG1:
    case WP_SR8:
    case WP_G36:
    case WP_LR300:
    case WP_NEGEV:
        return qtrue;
    default:
        return qfalse;
    }
}
/*
================
BG_Secondary


================
*/

qboolean BG_Secondary ( int weapon) {
    switch (weapon) {
    case WP_MP5K:
    case WP_UMP45:
        case WP_SPAS:
        return qtrue;
    default:
        return qfalse;
    }
}

/*
================
BG_Grenade

================
*/


qboolean BG_Grenade ( int weapon ) {
    switch (weapon) {
    case WP_SMOKE:
    case WP_HE:
        return qtrue;
    default:
        return qfalse;
    }
}



/*
===============
BG_GetClientNormal

Get the normal for the surface the client is walking on
===============
*/
void BG_GetClientNormal( const playerState_t *ps, vec3_t normal )
{
    VectorSet( normal, 0.0f, 0.0f, 1.0f );
}



int BG_CalcSpread( playerState_t ps ) {
  float spd = sqrt( ps.velocity[0]*ps.velocity[0] +
      ps.velocity[1]*ps.velocity[1] +
      ps.velocity[2]*ps.velocity[2]);

  if ( (ps.velocity[2] > 2.0 ||
        ps.velocity[2] < -2.0 ) &&
        (spd >= 5.0) &&
        ps.groundEntityNum == ENTITYNUM_NONE) return SPREAD_JUMPING;

  if (spd < 5.0 )
    return SPREAD_STANDING;

  if (ps.pm_flags & PMF_DUCKED)
    return SPREAD_CROUCHING;

  if ( spd < 139.0 )
    return SPREAD_WALKING;

  if ( (spd >= 220.0) &&(spd < 280.0) )
    return SPREAD_RUNNING;

  if (spd >= 280.0)
  return SPREAD_SPRINTING;

  return 50;
}

