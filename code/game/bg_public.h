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
// bg_public.h -- definitions shared by both the server game and client game modules

// because games can change separately from the main system version, we need a
// second version that must match between game and cgame

//note from blud: the original code (in this io code) is:
//#define       GAME_VERSION    BASEGAME
//So I guess it pulls the value of the constant BASEGAME which is set someplace else
//but why would we want to do that? That seems like something you'd want to do for
//when making a full game and have your mod be like the same folder as your base game
//so it's not what we want to do in alturt. Instead we do:
#define GAME_VERSION            "alturt-alpha0001"
//version plan is: alturt-alpha0001, alturt-alpha0002, etc, alturt-beta001, alturt-beta002, etc,
//alturt-01, (alturt-011), alturt-02, etc, alturt-09, alturt-10, alturt-11, etc.
//ie: you need the leading 0 so that version 1 and version 10 can be differentiated.

#define XAMISDB //blud: I moved this from q_shared.h

//blud: defining new Alturt buttons and re-defining old q3 buttons to new values
//for Alturt. (note: the old q3 buttons are defined in qcommon/q_shared.h, but 
//everywhere in cgame and game that q_shared.h is included, bg_public.h is included 
//after it so these defines will override the old ones) [and we're supposed to do this
//here, not in qcommon/q_shared.h since that's not part of the mod code, it's part of 
//the engine code basically.
#define BUTTON_WP_MODE		8
#define BUTTON_RELOAD		32
#define BUTTON_USE			128
#define BUTTON_SPRINTING	256

#undef	BUTTON_AFFIRMATIVE
#define BUTTON_HEAL	64

#undef	BUTTON_GUARDBASE
#define BUTTON_GUARDBASE	4096

#undef	BUTTON_GESTURE
#define BUTTON_GESTURE		8192

#undef	BUTTON_GETFLAG
#define BUTTON_GETFLAG		16384



#define DEFAULT_GRAVITY         800
#define GIB_HEALTH                      -40
#define ARMOR_PROTECTION        0.66

#define MAX_ITEMS                       256

#define RANK_TIED_FLAG          0x4000

#define DEFAULT_SHOTGUN_SPREAD  700
#define DEFAULT_SHOTGUN_COUNT   11

#define ITEM_RADIUS                     15              // item sizes are needed for client side pickup detection

#define LIGHTNING_RANGE         768

#define SCORE_NOT_PRESENT       -9999   // for the CS_SCORES[12] when only one player is present

#define VOTE_TIME                       30000   // 30 seconds before vote times out

#define MINS_Z                          -20
#define DEFAULT_VIEWHEIGHT      38 //blud, was 26
#define CROUCH_VIEWHEIGHT       20 //blud, was 12
#define DEAD_VIEWHEIGHT         -16
#define PLAYER_STANDHEIGHT		45 //blud new constant
#define PLAYER_CROUCHHEIGHT		24 //blud new constant

//
// config strings are a general means of communicating variable length strings
// from the server to all connected clients.
//

// CS_SERVERINFO and CS_SYSTEMINFO are defined in q_shared.h
#define CS_MUSIC                                2
#define CS_MESSAGE                              3               // from the map worldspawn's message field
#define CS_MOTD                                 4               // g_motd string for server message of the day
#define CS_WARMUP                               5               // server time when the match will be restarted
#define CS_SCORES1                              6
#define CS_SCORES2                              7
#define CS_VOTE_TIME                    8
#define CS_VOTE_STRING                  9
#define CS_VOTE_YES                             10
#define CS_VOTE_NO                              11

#define CS_TEAMVOTE_TIME                12
#define CS_TEAMVOTE_STRING              14
#define CS_TEAMVOTE_YES                 16
#define CS_TEAMVOTE_NO                  18

#define CS_GAME_VERSION                 20
#define CS_LEVEL_START_TIME             21              // so the timer only shows the current level
#define CS_INTERMISSION                 22              // when 1, fraglimit/timelimit has been hit and intermission will start in a second or two
#define CS_FLAGSTATUS                   23              // string indicating flag status in CTF
#define CS_SHADERSTATE                  24
#define CS_BOTINFO                              25

#define CS_ITEMS                                27              // string of 0's and 1's that tell which items are present

#define CS_MODELS                               32
#define CS_SOUNDS                               (CS_MODELS+MAX_MODELS)
#define CS_PLAYERS                              (CS_SOUNDS+MAX_SOUNDS)
#define CS_LOCATIONS                    (CS_PLAYERS+MAX_CLIENTS)
#define CS_PARTICLES                    (CS_LOCATIONS+MAX_LOCATIONS)

#define CS_MAX                                  (CS_PARTICLES+MAX_LOCATIONS)

#if (CS_MAX) > MAX_CONFIGSTRINGS
#error overflow: (CS_MAX) > MAX_CONFIGSTRINGS
#endif

typedef enum {
        GT_FFA,                         // free for all
        GT_SINGLE_PLAYER,       // single player ffa
        GT_TOURNAMENT,

        //-- team games go after this --
        GT_TEAM,                        // team deathmatch
        GT_TEAMSV,
        GT_ASN,
        GT_CAH,
        GT_CTF,                         // capture the flag
        GT_BOMB,
        GT_MAX_GAME_TYPE
} gametype_t;

typedef enum { GENDER_MALE, GENDER_FEMALE, GENDER_NEUTER } gender_t;

/*
===================================================================================

PMOVE MODULE

The pmove code takes a player_state_t and a usercmd_t and generates a new player_state_t
and some other output data.  Used for local prediction on the client game and true
movement on the server game.
===================================================================================
*/

typedef enum {
        PM_NORMAL,              // can accelerate and turn
        PM_NOCLIP,              // noclip movement
        PM_SPECTATOR,   // still run into walls
        PM_DEAD,                // no acceleration or turning, but free falling
        PM_FREEZE,              // stuck in place with no control
        PM_INTERMISSION,        // no movement or status bar
        PM_SPINTERMISSION       // no movement or status bar
} pmtype_t;

typedef enum {
        WEAPON_READY,
        WEAPON_RAISING,
        WEAPON_DROPPING,
        WEAPON_FIRING,
    WEAPON_FIRING2,
    WEAPON_RELOADING,
    WEAPON_RELOADING_START,
    WEAPON_RELOADING_END,
    WEAPON_RELOADING_COMPLETE,
    WEAPON_ARMING,
    WEAPON_ARMED,
    WEAPON_DROPPED,
    WEAPON_TOALTERNATE,
    WEAPON_TONORMAL,
    WEAPON_IDLE_ALT,
    WEAPON_READY_FIRE_ALT,
    WEAPON_READY_FIRE_IDLE_ALT,
    WEAPON_START_BANDAGING,                
    WEAPON_DOWN_BANDAGING,
                
} weaponstate_t;


typedef enum {
    WM_NONE,
    WM_BURST,
    WM_SINGLE,
            
     WM_ZOOM
} weaponmode_t;

// pmove->pm_flags
#define PMF_DUCKED                      1
#define PMF_JUMP_HELD           2
#define PMF_SINGLE_SHOT         4
#define PMF_BACKWARDS_JUMP      8               // go into backwards land
#define PMF_BACKWARDS_RUN       16              // coast down to backwards run
#define PMF_TIME_LAND           32              // pm_time is time before rejump
#define PMF_TIME_KNOCKBACK      64              // pm_time is an air-accelerate only time
#define PMF_TIME_WATERJUMP      256             // pm_time is waterjump
#define PMF_RESPAWNED           512             // clear after attack and jump buttons come up
#define PMF_ONGROUND           1024    //
#define PMF_SINGLE_MODE         2048    // pull towards grapple location
#define PMF_FOLLOW              4096    // spectate following another player
#define PMF_RELOADING           8192    // spectate as a scoreboard
#define PMF_GRENADE_ARMED       16384
#define PMF_BLEEDING       32768
#define PMF_ONLADDER    65536



#define PMF_ALL_TIMES   (PMF_TIME_WATERJUMP|PMF_TIME_LAND|PMF_TIME_KNOCKBACK)


#define BGF_POWERSLIDE                      1


#define MAXTOUCH        32
typedef struct {
        // state (in / out)
        playerState_t   *ps;

        // command (in)
        usercmd_t       cmd;
        int                     tracemask;                      // collide against these types of surfaces
        int                     debugLevel;                     // if set, diagnostic output will be printed
        qboolean        noFootsteps;            // if the game is setup for no footsteps by the server
        qboolean        gauntletHit;            // true if a gauntlet attack would actually hit something

        int                     framecount;

        // results (out)
        int                     numtouch;
        int                     touchents[MAXTOUCH];

        vec3_t          mins, maxs;                     // bounding box size

        int                     watertype;
        int                     waterlevel;
        float           xyspeed;
        int             crouchSlideTime;
        int             groundentity;
        // for fixed msec Pmove
        int                     pmove_fixed;
        int                     pmove_msec;

        // callbacks to test the world
        // these will be different functions during game and cgame
        void            (*trace)( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask );
        int                     (*pointcontents)( const vec3_t point, int passEntityNum );
} pmove_t;

// if a full pmove isn't done on the client, you can just update the angles
void PM_UpdateViewAngles( playerState_t *ps, const usercmd_t *cmd );
void Pmove (pmove_t *pmove);

typedef struct {
 int bg_flags[MAX_CLIENTS];
}bg_misc_t;


//===================================================================================


// player_state->stats[] indexes
// NOTE: may not have more than 16
typedef enum {
        STAT_HEALTH,
        STAT_STAMINA, //Xamis
        STAT_MODE,//Xamis
        STAT_ROUNDS,//Xamis
        STAT_CLIPS,//Xamis

        STAT_WEAPONS,   //Xamis                                // 16 bit fields
        STAT_WEAPONS_EXT,//Xamis

        STAT_DEAD_YAW,                                  // look this direction when dead (FIXME: get rid of?)
        STAT_CLIENTS_READY,                             // bit mask of clients wishing to exit the intermission (FIXME: configstring?)
        STAT_SELECTED_ITEM,//Xamis
        STAT_XYSPEED,//Xamis


        STAT_ARM_DAMAGE,   //Xamis                         // arm damage
        STAT_LEG_DAMAGE,  //Xamis                          // player walks slower when he got some legdamage,
        STAT_CHEST_DAMAGE,  //Xamis                        // chest damage
      //  STAT_STOMACH_DAMAGE, //Xamis                       // stomach damage
        STAT_HEAD_DAMAGE,//Xamis



} statIndex_t;


// loadout related  -located in bg_misc.c --xamis
qboolean BG_Melee( int weapon );
qboolean BG_Sidearm( int weapon );
qboolean BG_Primary ( int weapon );
qboolean BG_Secondary ( int weapon );
qboolean BG_Grenade( int weapon );
qboolean BG_HasWeapon( int weapon, int stats[ ] );
qboolean BG_HasSidearm (const  playerState_t *ps );
qboolean BG_HasPrimary (const  playerState_t *ps );
qboolean BG_HasSecondary (const  playerState_t *ps );
//int BG_WeaponModes( int weapon ) ;



// player_state->persistant[] indexes
// these fields are the only part of player_state that isn't
// cleared on respawn
// NOTE: may not have more than 16
typedef enum {
        PERS_SCORE,                                             // !!! MUST NOT CHANGE, SERVER AND GAME BOTH REFERENCE !!!
        PERS_HITS,                                              // total points damage inflicted so damage beeps can sound on change
        PERS_RANK,                                              // player rank or team rank
        PERS_TEAM,                                              // player team
        PERS_SPAWN_COUNT,                               // incremented every respawn
        PERS_PLAYEREVENTS,                              // 16 bits that can be flipped for events
        PERS_ATTACKER,                                  // clientnum of last damage inflicter
        PERS_ATTACKEE_ARMOR,                    // health/armor of last person we attacked
        PERS_KILLED,                                    // count of the number of times you died
        // player awards tracking
        PERS_IMPRESSIVE_COUNT,                  // two railgun hits in a row
        PERS_EXCELLENT_COUNT,                   // two successive kills in a short amount of time
        PERS_DEFEND_COUNT,                              // defend awards
        PERS_ASSIST_COUNT,                              // assist awards
        PERS_GAUNTLET_FRAG_COUNT,               // kills with the guantlet
        PERS_CAPTURES                                   // captures
} persEnum_t;


// entityState_t->eFlags
#define EF_DEAD                         0x00000001              // don't draw a foe marker over players with EF_DEAD
#ifdef MISSIONPACK
#define EF_TICKING                      0x00000002              // used to make players play the prox mine ticking sound
#endif
#define EF_TELEPORT_BIT         0x00000004              // toggled every time the origin abruptly changes
#define EF_AWARD_EXCELLENT      0x00000008              // draw an excellent sprite
#define EF_PLAYER_EVENT         0x00000010
#define EF_BOUNCE                       0x00000010              // for missiles
#define EF_BOUNCE_HALF          0x00000020              // for missiles
#define EF_AWARD_GAUNTLET       0x00000040              // draw a gauntlet sprite
#define EF_NODRAW                       0x00000080              // may have an event, but no model (unspawned items)
#define EF_FIRING                       0x00000100              // for lightning gun
#define EF_KAMIKAZE                     0x00000200
#define EF_MOVER_STOP           0x00000400              // will push otherwise
#define EF_AWARD_CAP            0x00000800              // draw the capture sprite
#define EF_TALK                         0x00001000              // draw a talk balloon
#define EF_CONNECTION           0x00002000              // draw a connection trouble sprite
#define EF_VOTED                        0x00004000              // already cast a vote
#define EF_AWARD_IMPRESSIVE     0x00008000              // draw an impressive sprite
#define EF_AWARD_DEFEND         0x00010000              // draw a defend sprite
#define EF_AWARD_ASSIST         0x00020000              // draw a assist sprite
#define EF_AWARD_DENIED         0x00040000              // denied
#define EF_TEAMVOTED            0x00080000              // already cast a team vote

// NOTE: may not have more than 16
typedef enum {
        PW_NONE,

        PW_REDFLAG,
        PW_BLUEFLAG,
        PW_NEUTRALFLAG,

        PW_VEST,
        PW_HELMET,

        PW_SILENCER,
        PW_LASERSIGHT,
        PW_AMMO,
        PW_NVG,

        PW_NUM_POWERUPS

} powerup_t;

typedef enum {
        HI_NONE,
        HI_MEDKIT,
        HI_NUM_HOLDABLE
} holdable_t;


typedef enum {
        WP_NONE, //0

 WP_KNIFE, //1

 WP_BERETTA, //2
 WP_DEAGLE, //3

 WP_MP5K, //4
 WP_SPAS, //5
 WP_UMP45, //6
 WP_M4, //7
 WP_LR300, //8
 WP_G36, //9
 WP_AK103, //10
 WP_HK69, //11
 WP_NEGEV, //12
 WP_PSG1, //13
 WP_SR8, //14

 WP_HE, //15
 WP_SMOKE, //16


 WP_NUM_WEAPONS
} weapon_t;

typedef enum {

  MF_NONE,

  MF_SMOKE
} missleFunc_t;

// reward sounds (stored in ps->persistant[PERS_PLAYEREVENTS])
#define PLAYEREVENT_DENIEDREWARD                0x0001
#define PLAYEREVENT_GAUNTLETREWARD              0x0002
#define PLAYEREVENT_HOLYSHIT                    0x0004

// entityState_t->event values
// entity events are for effects that take place reletive
// to an existing entities origin.  Very network efficient.

// two bits at the top of the entityState->event field
// will be incremented with each change in the event so
// that an identical event started twice in a row can
// be distinguished.  And off the value with ~EV_EVENT_BITS
// to retrieve the actual event number
#define EV_EVENT_BIT1           0x00000100
#define EV_EVENT_BIT2           0x00000200
#define EV_EVENT_BITS           (EV_EVENT_BIT1|EV_EVENT_BIT2)

#define EVENT_VALID_MSEC        300

typedef enum {
        EV_NONE,

        EV_BANDAGE,
        EV_FOOTSTEP,
        EV_FOOTSTEP_METAL,
        EV_FOOTSPLASH,
        EV_FOOTSTEP_LADDER, //Xamis
        EV_FOOTWADE,
        EV_SWIM,

        EV_STEP_4,
        EV_STEP_8,
        EV_STEP_12,
        EV_STEP_16,

        EV_FALL_SHORT,
        EV_FALL_MEDIUM,
        EV_FALL_FAR,

        EV_JUMP_PAD,                    // boing sound at origin, jump sound on player

        EV_JUMP,
        EV_BLEED,
        EV_WATER_TOUCH, // foot touches
        EV_WATER_LEAVE, // foot leaves
        EV_WATER_UNDER, // head touches
        EV_WATER_CLEAR, // head leaves

        EV_ITEM_PICKUP,                 // normal item pickups are predictable
        EV_GLOBAL_ITEM_PICKUP,  // powerup / team sounds are broadcast to everyone

        EV_NOAMMO,
        EV_NONADES,
        EV_POWERSLIDE,
        EV_CHANGE_WEAPON,
        EV_FIRE_WEAPON,
        EV_ZOOM_RESET,
        EV_EJECT_CASING,

        EV_USE_ITEM0,
        EV_USE_ITEM1,
        EV_USE_ITEM2,
        EV_USE_ITEM3,
        EV_USE_ITEM4,
        EV_USE_ITEM5,
        EV_USE_ITEM6,
        EV_USE_ITEM7,
        EV_USE_ITEM8,
        EV_USE_ITEM9,
        EV_USE_ITEM10,
        EV_USE_ITEM11,
        EV_USE_ITEM12,
        EV_USE_ITEM13,
        EV_USE_ITEM14,
        EV_USE_ITEM15,

        EV_ITEM_RESPAWN,
        EV_ITEM_POP,
        EV_PLAYER_TELEPORT_IN,
        EV_PLAYER_TELEPORT_OUT,

        EV_GRENADE_BOUNCE,              // eventParm will be the soundindex

        EV_GENERAL_SOUND,
        EV_GLOBAL_SOUND,                // no attenuation
        EV_GLOBAL_TEAM_SOUND,

        EV_BULLET_HIT_FLESH,
        EV_BULLET_HIT_WALL,

        EV_MISSILE_HIT,
        EV_MISSILE_MISS,
        EV_MISSILE_MISS_METAL,
        EV_RAILTRAIL,
        EV_SHOTGUN,
        EV_BULLET,                              // otherEntity is the shooter

        EV_PAIN,
        EV_DEATH1,
        EV_DEATH2,
        EV_DEATH3,
        EV_OBITUARY,

        EV_POWERUP_QUAD,
        EV_POWERUP_BATTLESUIT,
        EV_POWERUP_REGEN,

        EV_GIB_PLAYER,                  // gib a previously living player
        EV_BREAK_GLASS,                 //Xamis
        EV_SCOREPLUM,                   // score plum

//#ifdef MISSIONPACK
        EV_PROXIMITY_MINE_STICK,
        EV_PROXIMITY_MINE_TRIGGER,
        EV_KAMIKAZE,                    // kamikaze explodes
        EV_OBELISKEXPLODE,              // obelisk explodes
        EV_OBELISKPAIN,                 // obelisk is in pain
        EV_INVUL_IMPACT,                // invulnerability sphere impact
        EV_JUICED,                              // invulnerability juiced effect
        EV_LIGHTNINGBOLT,               // lightning bolt bounced of invulnerability sphere
//#endif

        EV_DEBUG_LINE,
        EV_STOPLOOPINGSOUND,
        EV_TAUNT,
        EV_TAUNT_YES,
        EV_TAUNT_NO,
        EV_TAUNT_FOLLOWME,
        EV_TAUNT_GETFLAG,
        EV_TAUNT_GUARDBASE,
        EV_TAUNT_PATROL,


} entity_event_t;


typedef enum {
        GTS_RED_CAPTURE,
        GTS_BLUE_CAPTURE,
        GTS_RED_RETURN,
        GTS_BLUE_RETURN,
        GTS_RED_TAKEN,
        GTS_BLUE_TAKEN,
        GTS_REDOBELISK_ATTACKED,
        GTS_BLUEOBELISK_ATTACKED,
        GTS_REDTEAM_SCORED,
        GTS_BLUETEAM_SCORED,
        GTS_REDTEAM_TOOK_LEAD,
        GTS_BLUETEAM_TOOK_LEAD,
        GTS_TEAMS_ARE_TIED,
        GTS_KAMIKAZE
} global_team_sound_t;

// animations
typedef enum {
        BOTH_DEATH1,
        BOTH_DEAD1,
        BOTH_DEATH2,
        BOTH_DEAD2,
        BOTH_DEATH3,
        BOTH_DEAD3,
        BOTH_CLIMB,
        BOTH_CLIMB_IDLE,

        TORSO_GESTURE,

        TORSO_ATTACK,
        TORSO_ATTACK2,

        TORSO_DROP,
        TORSO_RAISE,

        TORSO_STAND,
        TORSO_STAND2,

        LEGS_WALKCR,
        LEGS_WALK,
        LEGS_RUN,
        LEGS_BACK,
        LEGS_SWIM,
        LEGS_LIMP,
        LEGS_BACKLIMP,	

        LEGS_JUMP,
        LEGS_LAND,

        LEGS_JUMPB,
        LEGS_LANDB,

        LEGS_IDLE,
        LEGS_IDLECR,

        LEGS_TURN,
 //Xamis pistol
        TORSO_ATTACK_PISTOL,
        TORSO_STAND_PISTOL,
        TORSO_RUN_ATTACK_PISTOL,

        TORSO_RELOAD_PISTOL,
        TORSO_RELOAD_RIFLE,
        TORSO_ATTACK_RIFLE,
        TORSO_ATTACK_PUMPGUN,
        TORSO_ATTACK_GRENADE,
        TORSO_ATTACK_KNIFE,
        TORSO_BANDAGE,
        TORSO_GETFLAG,
        TORSO_GUARDBASE,
        TORSO_PATROL,
        TORSO_FOLLOWME,
        TORSO_AFFIRMATIVE,
        TORSO_NEGATIVE,


        MAX_ANIMATIONS,

        LEGS_BACKCR,
        LEGS_BACKWALK,
        FLAG_RUN,
        FLAG_STAND,
        FLAG_STAND2RUN,

        MAX_TOTALANIMATIONS
} animNumber_t;

typedef enum {
  WPN_DRAW,
  WPN_IDLE,
  WPN_READY_FIRE,
  WPN_FIRE,
  WPN_READY_FIRE_IDLE,
  WPN_RELOAD,
  WPN_BOLT,
  WPN_RELOAD_START,
  WPN_RELOAD_END,
  WPN_FIRE_ALT,
  WPN_TOALTERNATE,
  WPN_TONORMAL,
  WPN_IDLE_ALT,
  WPN_READY_FIRE_ALT,
  WPN_READY_FIRE_IDLE_ALT,
          
          
          
  MAX_WEAPON_ANIMATIONS
} wpAnimNumber_t;



typedef struct animation_s {
        int             firstFrame;
        int             numFrames;
        int             loopFrames;                     // 0 to numFrames
        int             frameLerp;                      // msec between frames
        int             initialLerp;            // msec to get to first frame
        int             reversed;                       // true if animation is reversed
        int             flipflop;                       // true if animation should flipflop back to base
} animation_t;

typedef struct soundList_s {  //Added to deal with reload sounds --Xamis
        int          type;
        int          startFrame;
        sfxHandle_t  soundPath;  
} soundList_t;


typedef struct nadeInfo_s{
int fuseTime[MAX_CLIENTS];
int throwStrength[MAX_CLIENTS];
} nadeInfo_t;

// flip the togglebit every time an animation
// changes so a restart of the same anim can be detected
#define ANIM_TOGGLEBIT          128


typedef enum {
        TEAM_FREE,
        TEAM_RED,
        TEAM_BLUE,
        RED,
        BLUE,
        TEAM_SPECTATOR,

        TEAM_NUM_TEAMS
} team_t;

// Time between location updates
#define TEAM_LOCATION_UPDATE_TIME               1000

// How many players on the overlay
#define TEAM_MAXOVERLAY         32

//team task
typedef enum {
        TEAMTASK_NONE,
        TEAMTASK_OFFENSE,
        TEAMTASK_DEFENSE,
        TEAMTASK_PATROL,
        TEAMTASK_FOLLOW,
        TEAMTASK_RETRIEVE,
        TEAMTASK_ESCORT,
        TEAMTASK_CAMP
} teamtask_t;

// means of death
typedef enum {
        MOD_UNKNOWN,
        MOD_KNIFE,
        MOD_SHOTGUN,
        MOD_GAUNTLET,
        MOD_MACHINEGUN,
        MOD_GRENADE,
        MOD_GRENADE_SPLASH,
        MOD_ROCKET,
        MOD_ROCKET_SPLASH,
        MOD_PLASMA,
        MOD_PLASMA_SPLASH,
        MOD_RAILGUN,
        MOD_LIGHTNING,
        MOD_BFG,
        MOD_BFG_SPLASH,
        MOD_WATER,
        MOD_SLIME,
        MOD_LAVA,
        MOD_CRUSH,
        MOD_TELEFRAG,
        MOD_FALLING,
        MOD_SUICIDE,
        MOD_BLED,
        MOD_TARGET_LASER,
        MOD_TRIGGER_HURT,
#ifdef MISSIONPACK
        MOD_NAIL,
        MOD_CHAINGUN,
        MOD_PROXIMITY_MINE,
        MOD_KAMIKAZE,
        MOD_JUICED,
#endif
        MOD_GRAPPLE
} meansOfDeath_t;


//---------------------------------------------------------

// gitem_t->type
typedef enum {
        IT_BAD,
        IT_WEAPON,                              // EFX: rotate + upscale + minlight
        IT_AMMO,                                // EFX: rotate
        IT_ARMOR,                               // EFX: rotate + minlight
        IT_HEALTH,                              // EFX: static external sphere + rotating internal
        IT_POWERUP,                             // instant on, timer based
                                                        // EFX: rotate + external ring that rotates
        IT_HOLDABLE,                    // single use, holdable item
                                                        // EFX: rotate + bob
        IT_PERSISTANT_POWERUP,
        IT_TEAM
} itemType_t;

#define MAX_ITEM_MODELS 4

typedef struct gitem_s {
        char            *classname;     // spawning name
        char            *pickup_sound;
        char            *world_model[MAX_ITEM_MODELS];

        char            *icon;
        char            *pickup_name;   // for printing on pickup

        int                     quantity;               // for ammo how much, or duration of powerup
        itemType_t  giType;                     // IT_* flags

        int                     giTag;

        char            *precaches;             // string of all models and images this item will use
        char            *sounds;                // string of all sounds this item will use
} gitem_t;

//xamis
#define MELEE                   0
#define SIDEARM                 1
#define PRIMARY                 2
#define SECONDARY               3
#define NADE                    4
#define MISC                    5
#define INVENTORYITEMS  6
//Xamis ammo system to deal with max_weapons limit
typedef struct wpinfo_s {
  char            *ammoIcon;
  int             weapMode[MAX_CLIENTS];
  int             numClips[MAX_CLIENTS];
  int             rounds[MAX_CLIENTS];
  char          *modelPath;
} wpinfo_t;


typedef struct spasinfo_s {
int roundCount[MAX_CLIENTS];
} spasinfo_t;


typedef struct wp_sort_s{
int sort[MAX_CLIENTS][INVENTORYITEMS];
int item[MAX_CLIENTS][3];
} wp_sort_t;

// included in both the game dll and the client
extern  wpinfo_t bg_weaponlist[];
extern  bg_misc_t bg_ps;
extern  wp_sort_t bg_inventory;
extern  nadeInfo_t bg_nadeTimer;
extern  gitem_t bg_itemlist[];
extern  int     bg_numItems;

gitem_t *BG_FindItem( const char *pickupName );
gitem_t *BG_FindItemForWeapon( weapon_t weapon );
gitem_t *BG_FindItemForPowerup( powerup_t pw );
gitem_t *BG_FindItemForHoldable( holdable_t pw );
#define ITEM_INDEX(x) ((x)-bg_itemlist)

qboolean        BG_CanItemBeGrabbed( int gametype, const entityState_t *ent, const playerState_t *ps );


// g_dmflags->integer flags
#define DF_NO_FALLING                   8
#define DF_FIXED_FOV                    16
#define DF_NO_FOOTSTEPS                 32

// content masks
#define MASK_ALL                                (-1)
#define MASK_SOLID                              (CONTENTS_SOLID)
#define MASK_PLAYERSOLID                (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_BODY)
#define MASK_DEADSOLID                  (CONTENTS_SOLID|CONTENTS_PLAYERCLIP)
#define MASK_WATER                              (CONTENTS_WATER|CONTENTS_LAVA|CONTENTS_SLIME)
#define MASK_OPAQUE                             (CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA)
#define MASK_SHOT                               (CONTENTS_SOLID|CONTENTS_BODY|CONTENTS_CORPSE)


//
// entityState_t->eType
//
typedef enum {
        ET_GENERAL,
        ET_PLAYER,
        ET_ITEM,
        ET_MISSILE,
        ET_MOVER,
        ET_BEAM,
        ET_PORTAL,
        ET_SPEAKER,
        ET_PUSH_TRIGGER,
        ET_TELEPORT_TRIGGER,
        ET_INVISIBLE,
        ET_GRAPPLE,                             // grapple hooked on wall
        ET_TEAM,
        ET_BREAKABLE,                   //XAMIS
        ET_WALL,                                //XAMIS
        ET_DOOR,                                //XAMIS
        ET_EVENTS                               // any of the EV_* events can be added freestanding
                                                        // by setting eType to ET_EVENTS + eventNum
                                                        // this avoids having to set eFlags and eventNum
} entityType_t;



void    BG_EvaluateTrajectory( const trajectory_t *tr, int atTime, vec3_t result );
void    BG_EvaluateTrajectoryDelta( const trajectory_t *tr, int atTime, vec3_t result );

void    BG_AddPredictableEventToPlayerstate( int newEvent, int eventParm, playerState_t *ps );

void    BG_TouchJumpPad( playerState_t *ps, entityState_t *jumppad );

void    BG_PlayerStateToEntityState( playerState_t *ps, entityState_t *s, qboolean snap );
void    BG_PlayerStateToEntityStateExtraPolate( playerState_t *ps, entityState_t *s, int time, qboolean snap );

qboolean        BG_PlayerTouchesItem( playerState_t *ps, entityState_t *item, int atTime );

void        BG_PlayerTouchesSmoke(int num, int stats[] );
qboolean  BG_PlayerInSmoke ( int stats[]);

void      BG_GetClientNormal( const playerState_t *ps, vec3_t normal );
int       BG_CalcSpread( playerState_t ps );
int       RoundCount( int w );
void      BG_PackWeapon( int weapon, int stats[ ] );
void      BG_RemoveWeapon( int weapon, int stats[ ] );
void       BG_LastKnife(void);

#define ARENAS_PER_TIER         4
#define MAX_ARENAS                      1024
#define MAX_ARENAS_TEXT         8192

#define MAX_BOTS                        1024
#define MAX_BOTS_TEXT           8192


// Kamikaze

// 1st shockwave times
#define KAMI_SHOCKWAVE_STARTTIME                0
#define KAMI_SHOCKWAVEFADE_STARTTIME    1500
#define KAMI_SHOCKWAVE_ENDTIME                  2000
// explosion/implosion times
#define KAMI_EXPLODE_STARTTIME                  250
#define KAMI_IMPLODE_STARTTIME                  2000
#define KAMI_IMPLODE_ENDTIME                    2250
// 2nd shockwave times
#define KAMI_SHOCKWAVE2_STARTTIME               2000
#define KAMI_SHOCKWAVE2FADE_STARTTIME   2500
#define KAMI_SHOCKWAVE2_ENDTIME                 3000
// radius of the models without scaling
#define KAMI_SHOCKWAVEMODEL_RADIUS              88
#define KAMI_BOOMSPHEREMODEL_RADIUS             72
// maximum radius of the models during the effect
#define KAMI_SHOCKWAVE_MAXRADIUS                1320
#define KAMI_BOOMSPHERE_MAXRADIUS               720
#define KAMI_SHOCKWAVE2_MAXRADIUS               704



//ALTURT STUFF



#define SPREAD_JUMPING 190.0;
#define SPREAD_STANDING 15.0
#define SPREAD_CROUCHING 0.0
#define SPREAD_WALKING 50.0
#define SPREAD_RUNNING 90.0
#define SPREAD_SPRINTING 120.0


#define ALTURT_SMOKENADETIME 120 // time the smoke nade will spawn smoke for each numbr
#define ALTURT_SMOKEPUFF_NUMBER 100 // number of smokepuffs to spawn from serverside
#define ALTURT_SMOKEBLEND_RANGE 96.0f // range of the blend effect clientside
#define ALTURT_SMOKEPUFF_TIME 5500 // duration of a single smokepuff clientside
#define ALTURT_SMOKEPUFF_RADIUS 256.0 // radius of a single smokepuff clientside
#define ALTURT_SMOKENADE_DISTANCE 420 // how far the smokepuffs can flow

// color of the smoke
#define ALTURT_SMOKENADE_R_DEFAULT 0.30f
#define ALTURT_SMOKENADE_G_DEFAULT 0.30f
#define ALTURT_SMOKENADE_B_DEFAULT 0.30f

#define ALTURT_SMOKENADE_R_TEAM_RED 1.00f
#define ALTURT_SMOKENADE_G_TEAM_RED 0.40f
#define ALTURT_SMOKENADE_B_TEAM_RED 0.20f

#define ALTURT_SMOKENADE_R_TEAM_BLUE 0.20f
#define ALTURT_SMOKENADE_G_TEAM_BLUE 0.40f
#define ALTURT_SMOKENADE_B_TEAM_BLUE 1.00f

// bitmasks
#define ALTURT_SMOKEMASK_UP        0x0000c000
#define ALTURT_SMOKEMASK_FORWARD   0x00003000
#define ALTURT_SMOKEMASK_BACKWARD  0x00000c00
#define ALTURT_SMOKEMASK_LEFT      0x00000300
#define ALTURT_SMOKEMASK_RIGHT     0x000000c0
#define ALTURT_SMOKEMASK_FLAGS     0x0000ffc0
#define ALTURT_SMOKEMASK_RNDNUM    0x0000003f
#define ALTURT_SMOKEMASK_SUP       14
#define ALTURT_SMOKEMASK_SFORWARD  12
#define ALTURT_SMOKEMASK_SBACKWARD 10
#define ALTURT_SMOKEMASK_SLEFT     8
#define ALTURT_SMOKEMASK_SRIGHT    6
#define ALTURT_SMOKEMASK_VALUE     0x3
#define SMOKE_FLAGS     0x0000ffc0


#define STAT_MAX_HEALTH 100

#define STAT_MAX_STAMINA 900
