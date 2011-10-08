/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.
Copyright (C) 2009-2011 Brian Labbie and Dave Richardson.

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
// g_combat.c

#include "g_local.h"


/*
==============

LOCATIONAL DAMAGE

==============
*/
qboolean pointinback (gentity_t *self, vec3_t point)
{
  vec3_t      vec;
  float       dot;
  vec3_t      forward;

  if ( !self->client )
    return qfalse;

  AngleVectors (self->client->ps.viewangles, forward, NULL, NULL);
  VectorSubtract (point, self->r.currentOrigin, vec);
  VectorNormalize (vec);
  dot = DotProduct (vec, forward);

  if (dot < 0.3)
    return qtrue;
  return qfalse;
}
qboolean pointinfront (gentity_t *self, vec3_t point, float mod)
{
  vec3_t      vec;
  float       dot;
  vec3_t      forward;

  if ( !self->client )
    return qfalse;

  AngleVectors (self->client->ps.viewangles, forward, NULL, NULL);
  VectorCopy(self->r.currentOrigin, vec);
  vec[2]+=mod;
  VectorSubtract (point, vec, vec);
  VectorNormalize (vec);
  dot = DotProduct (vec, forward);

  if (dot < 0.3)
    return qfalse;
  return qtrue;
}
qboolean pointabove (gentity_t *self, vec3_t point)
{
  vec3_t      vec;
  float       dot;
  vec3_t      up;

  if ( !self->client )
    return qfalse;

  AngleVectors (self->client->ps.viewangles, NULL, NULL, up);
  VectorSubtract (point, self->r.currentOrigin, vec);
  VectorNormalize (vec);
  dot = DotProduct (vec, up);

  if (dot > 0.3)
    return qtrue;
  return qfalse;
}
qboolean pointbelow (gentity_t *self, vec3_t point)
{
  vec3_t      vec;
  float       dot;
  vec3_t      up;

  if ( !self->client )
    return qfalse;

  AngleVectors (self->client->ps.viewangles, NULL, NULL, up);
  VectorSubtract (point, self->r.currentOrigin, vec);
  VectorNormalize (vec);
  dot = DotProduct (vec, up);

  if (dot < -0.3)
    return qtrue;
  return qfalse;
}
qboolean inback (gentity_t *self, vec3_t point, float mod)
{
  vec3_t      vec;
  float       dot;
  vec3_t      forward;

  AngleVectors (self->s.angles, forward, NULL, NULL);
  VectorCopy(self->r.currentOrigin, vec);
  vec[2]+=mod;
  VectorSubtract (point, vec, vec);
  VectorNormalize (vec);
  dot = DotProduct (vec, forward);

  if (dot < -0.3)
    return qtrue;
  return qfalse;
}
/*
=================
GetLocationalDamage
=================
*/


int CheckLocationDamage ( gentity_t *targ, vec3_t point, int mod) {
  vec3_t bulletPath;
  vec3_t bulletAngle;

  float clientHeight;
  float clientFeetZ;
  float clientRotation;
  float bulletHeight;
  int bulletRotation;
  int impactRotation;
  int inback = 0;

  float headMod = 7.8f;
  float chestMod = 22.0f;
  float stomachMod = 14.0f;

  if ( targ->client && ( targ->client->ps.pm_flags & PMF_DUCKED ) )
  {
    headMod = 18.96f;
    chestMod = 31.16f;
    stomachMod = 26.19f; // where the stomach begins
  }


    // Point[2] is the REAL world Z. We want Z relative to the clients feet

    // Where the feet are at
  clientFeetZ  = targ->r.currentOrigin[2] + targ->r.mins[2];
    // How tall the client is
  clientHeight = targ->r.maxs[2] - targ->r.mins[2];
    // Where the bullet struck
  bulletHeight = point[2] - clientFeetZ;

    // Get a vector aiming from the client to the bullet hit
  VectorSubtract(targ->r.currentOrigin, point, bulletPath);
    // Convert it into PITCH, ROLL, YAW
  vectoangles(bulletPath, bulletAngle);

  clientRotation = targ->client->ps.viewangles[YAW];
  bulletRotation = bulletAngle[YAW];

  impactRotation = abs(clientRotation-bulletRotation);

  impactRotation += 45; // just to make it easier to work with
  impactRotation = impactRotation % 360; // Keep it in the 0-359 range

  if (impactRotation < 90)
    inback = 1;
  else if (impactRotation < 180)
    inback = 2;
  else if (impactRotation < 270)
    inback = 0;
  else if (impactRotation < 360)
    inback = 3;

  if (/*g_debugDamage.integer ==*/ 0) G_Printf("Bulletheight: %f || Clientheight: %f || mod: %i\n", bulletHeight, clientHeight, mod);

    // The upper body never changes height, just distance from the feet
  if ( (bulletHeight > clientHeight - headMod) ) {
    /*if (g_debugDamage.integer == 1)G_Printf("Headshot\n");*/ 
    return LOC_HEAD;
  } else if ( (bulletHeight > clientHeight - headMod ) && (inback == 0) ) {
/*    if (g_debugDamage.integer == 1) G_Printf("Faceshot\n");*/
    return  LOC_FACE;
  } else if ( (bulletHeight > clientHeight ) ) {
/*    if (g_debugDamage.integer == 1) G_Printf("Headshot\n");*/
    return LOC_HEAD;
  } else if ( (bulletHeight > clientHeight - stomachMod) && (inback == 0) ) {
/*    if (g_debugDamage.integer == 1) G_Printf("Chestshot\n");*/
    return LOC_CHEST;
  } else if ( (bulletHeight > clientHeight - stomachMod) && (inback == 2) ) {
/*    if (g_debugDamage.integer == 1) G_Printf("Rightarmshot\n");*/
    return LOC_RIGHTARM;
  } else if ( (bulletHeight > clientHeight - stomachMod) && (inback == 3) ) {
/*    if (g_debugDamage.integer == 1) G_Printf("Leftarmshot\n");*/
    return LOC_LEFTARM;
  } else if ( (bulletHeight > clientHeight - chestMod) && (inback == 1) ) {
/*    if (g_debugDamage.integer == 1) G_Printf("Backshot\n");*/
    return LOC_BACK;
  } else if ( (bulletHeight > clientHeight - chestMod) ) {
/*    if (g_debugDamage.integer == 1)G_Printf("Stomachshot\n");*/ 
    return LOC_STOMACH;
  } else if ( inback == 2 || inback == 0) {
/*    if (g_debugDamage.integer == 1) G_Printf("Rightlegshot\n");*/
    return LOC_RIGHTLEG;
  } else {
/*    if (g_debugDamage.integer == 1) G_Printf("Leftlegshot\n");*/
    return LOC_LEFTLEG;
  }

}



/*
============
ScorePlum
============
*/
void ScorePlum( gentity_t *ent, vec3_t origin, int score ) {
	gentity_t *plum;

	plum = G_TempEntity( origin, EV_SCOREPLUM );
	// only send this temp entity to a single client
	plum->r.svFlags |= SVF_SINGLECLIENT;
	plum->r.singleClient = ent->s.number;
	//
	plum->s.otherEntityNum = ent->s.number;
	plum->s.time = score;
}

/*
============
AddScore

Adds score to both the client and his team
============
*/
void AddScore( gentity_t *ent, vec3_t origin, int score ) {
	if ( !ent->client ) {
		return;
	}
	// no scoring during pre-match warmup
	if ( level.warmupTime ) {
		return;
	}
	// show score plum
	ScorePlum(ent, origin, score);
	//
	ent->client->ps.persistant[PERS_SCORE] += score;
	if ( g_gametype.integer == GT_TEAM )
		level.teamScores[ ent->client->ps.persistant[PERS_TEAM] ] += score;
	CalculateRanks();
}

/*
=================
TossClientItems

Toss the weapon and powerups for the killed player
=================
*/
void TossClientItems( gentity_t *self ) {
	gitem_t		*item;
        gitem_t         *item1;
        gitem_t         *item2;
        gitem_t         *item3;
	int			weapon;
        int                     weapon1;
        int                     weapon2;
        int                     weapon3;
	float		angle;
	int			i;
	gentity_t	*drop;
        int ammo = 0;

	//drop the weapon if not a gauntlet or machinegun
        weapon = bg_inventory.sort[self->client->ps.clientNum][PRIMARY];
        weapon1 = bg_inventory.sort[self->client->ps.clientNum][SECONDARY];
        weapon2 = bg_inventory.sort[self->client->ps.clientNum][NADE];
        weapon3 = bg_inventory.sort[self->client->ps.clientNum][SIDEARM];


	// make a special check to see if they are changing to a new
	// weapon that isn't the mg or gauntlet.  Without this, a client
	// can pick up a weapon, be killed, and not drop the weapon because
	// their weapon change hasn't completed yet and they are still holding the MG.

        if ( weapon && bg_weaponlist[weapon].rounds[self->client->ps.clientNum] ) {
		// find the item type for this weapon
		item = BG_FindItemForWeapon( weapon );
                bg_inventory.sort[self->client->ps.clientNum][PRIMARY] = WP_NONE;
                ammo =bg_weaponlist[weapon].rounds[self->client->ps.clientNum]
                    + bg_weaponlist[weapon].numClips[self->client->ps.clientNum]
                    * RoundCount(weapon);
		// spawn the item
                Drop_Weapon(self, item, random()*360, ammo, 0, 0 );
	}

        if ( weapon1 && bg_weaponlist[weapon1].rounds[self->client->ps.clientNum] ) {
                // find the item type for this weapon
          item1 = BG_FindItemForWeapon( weapon1 );
          bg_inventory.sort[self->client->ps.clientNum][SECONDARY] = WP_NONE;
          ammo =bg_weaponlist[weapon1].rounds[self->client->ps.clientNum]
              + bg_weaponlist[weapon1].numClips[self->client->ps.clientNum]
              * RoundCount(weapon1);
                // spawn the item
          Drop_Weapon(self, item1, random()*360, ammo, 25, 25 );
        }

        if ( weapon2 && bg_weaponlist[weapon2].numClips[self->client->ps.clientNum] ) {
                // find the item type for this weapon
          item2 = BG_FindItemForWeapon( weapon2 );
          bg_inventory.sort[self->client->ps.clientNum][NADE] = WP_NONE;
          ammo =bg_weaponlist[weapon2].rounds[self->client->ps.clientNum]
              + bg_weaponlist[weapon2].numClips[self->client->ps.clientNum]
              * RoundCount(weapon2);
                // spawn the item
          Drop_Weapon(self, item2, random()*360, ammo ,-25, -25 );
        }

        if ( weapon3 && bg_weaponlist[weapon3].rounds[self->client->ps.clientNum]) {
                // find the item type for this weapon
          item3 = BG_FindItemForWeapon( weapon3 );
          bg_inventory.sort[self->client->ps.clientNum][SIDEARM] = WP_NONE;
          ammo =bg_weaponlist[weapon3].rounds[self->client->ps.clientNum]
              + bg_weaponlist[weapon3].numClips[self->client->ps.clientNum]
              * RoundCount(weapon3);
                // spawn the item
          Drop_Weapon(self, item3, random()*360, ammo, 25, -25 );
        }
     //   G_Printf("%i rounds of ammo dropped\n", ammo);
		//blud note: I commented out unused vars for this block at top of function.
	// drop all the powerups if not in teamplay
       
	if ( g_gametype.integer != GT_TEAM ) {
		angle = 45;
		for ( i = 2 ; i < PW_NUM_POWERUPS ; i++ ) {
			if ( self->client->ps.powerups[ i ] > 0 ) {
				item = BG_FindItemForPowerup( i );
				if ( !item ) {
					continue;
				}
                                if( i == PW_REDFLAG|| i == PW_BLUEFLAG){
				drop = Drop_Item( self, item, random()*360 );
				// decide how many seconds it has left
				drop->count = ( self->client->ps.powerups[ i ]);
				if ( drop->count < 1 ) {
					drop->count = 1;
				}
				angle += 45;
                                                                }
			}
		}
        }
        
        for ( i = 2; i < PW_NUM_POWERUPS; i++){
        self->client->ps.powerups[ i ] = 0;

        }
        for ( i = 0; i < 3; i++){
          bg_inventory.item[self->client->ps.clientNum][i] = 0;
        }

}




#ifdef MISSIONPACK


/*
=================
TossClientCubes
=================
*/
extern gentity_t	*neutralObelisk;

void TossClientCubes( gentity_t *self ) {
	gitem_t		*item;
	gentity_t	*drop;
	vec3_t		velocity;
	vec3_t		angles;
	vec3_t		origin;

	self->client->ps.generic1 = 0;

	// this should never happen but we should never
	// get the server to crash due to skull being spawned in
	if (!G_EntitiesFree()) {
		return;
	}

	if( self->client->sess.sessionTeam == TEAM_RED ) {
		item = BG_FindItem( "Red Cube" );
	}
	else {
		item = BG_FindItem( "Blue Cube" );
	}

	angles[YAW] = (float)(level.time % 360);
	angles[PITCH] = 0;	// always forward
	angles[ROLL] = 0;

	AngleVectors( angles, velocity, NULL, NULL );
	VectorScale( velocity, 150, velocity );
	velocity[2] += 200 + crandom() * 50;

	if( neutralObelisk ) {
		VectorCopy( neutralObelisk->s.pos.trBase, origin );
		origin[2] += 44;
	} else {
		VectorClear( origin ) ;
	}

	drop = LaunchItem( item, origin, velocity );

	drop->nextthink = level.time + g_cubeTimeout.integer * 1000;
	drop->think = G_FreeEntity;
	drop->spawnflags = self->client->sess.sessionTeam;
}


/*
=================
TossClientPersistantPowerups
=================
*/
void TossClientPersistantPowerups( gentity_t *ent ) {
	gentity_t	*powerup;

	if( !ent->client ) {
		return;
	}

	if( !ent->client->persistantPowerup ) {
		return;
	}

	powerup = ent->client->persistantPowerup;

	powerup->r.svFlags &= ~SVF_NOCLIENT;
	powerup->s.eFlags &= ~EF_NODRAW;
	powerup->r.contents = CONTENTS_TRIGGER;
	trap_LinkEntity( powerup );

//	ent->client->ps.stats[STAT_PERSISTANT_POWERUP] = 0;
	ent->client->persistantPowerup = NULL;
}
#endif


/*
==================
LookAtKiller
==================
*/
void LookAtKiller( gentity_t *self, gentity_t *inflictor, gentity_t *attacker ) {
	vec3_t		dir;
	vec3_t		angles;

	if ( attacker && attacker != self ) {
		VectorSubtract (attacker->s.pos.trBase, self->s.pos.trBase, dir);
	} else if ( inflictor && inflictor != self ) {
		VectorSubtract (inflictor->s.pos.trBase, self->s.pos.trBase, dir);
	} else {
		self->client->ps.stats[STAT_DEAD_YAW] = self->s.angles[YAW];
		return;
	}

	self->client->ps.stats[STAT_DEAD_YAW] = vectoyaw ( dir );

	angles[YAW] = vectoyaw ( dir );
	angles[PITCH] = 0;
	angles[ROLL] = 0;
}

/*
==================
GibEntity
==================
*/
void GibEntity( gentity_t *self, int killer ) {
	gentity_t *ent;
	int i;

	//if this entity still has kamikaze
	if (self->s.eFlags & EF_KAMIKAZE) {
		// check if there is a kamikaze timer around for this owner
		for (i = 0; i < MAX_GENTITIES; i++) {
			ent = &g_entities[i];
			if (!ent->inuse)
				continue;
			if (ent->activator != self)
				continue;
			if (strcmp(ent->classname, "kamikaze timer"))
				continue;
			G_FreeEntity(ent);
			break;
		}
	}
	G_AddEvent( self, EV_GIB_PLAYER, killer );
	self->takedamage = qfalse;
	self->s.eType = ET_INVISIBLE;
	self->r.contents = 0;
}

/*
==================
body_die
==================
*/
void body_die( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath ) {
	if ( self->health > GIB_HEALTH ) {
		return;
	}
	if ( !g_blood.integer ) {
		self->health = GIB_HEALTH+1;
		return;
	}

	GibEntity( self, 0 );
}


// these are just for logging, the client prints its own messages
char	*modNames[] = {
	"MOD_UNKNOWN",
        	"MOD_KNIFE",
	"MOD_DEAGLE",
	"MOD_BERETTA",
	"MOD_MP5K",
	"MOD_UMP45",
	"MOD_M4",
	"MOD_LR300",
	"MOD_AK103",
	"MOD_G36",
	"MOD_NEGEV",
	"MOD_SR8",
	"MOD_PSG1",
	"MOD_SHOTGUN",
	"MOD_GAUNTLET",
	"MOD_MACHINEGUN",
	"MOD_GRENADE",
	"MOD_GRENADE_SPLASH",
	"MOD_ROCKET",
	"MOD_ROCKET_SPLASH",
	"MOD_PLASMA",
	"MOD_PLASMA_SPLASH",
	"MOD_RAILGUN",
	"MOD_LIGHTNING",
	"MOD_BFG",
	"MOD_BFG_SPLASH",
	"MOD_WATER",
	"MOD_SLIME",
	"MOD_LAVA",
	"MOD_CRUSH",
	"MOD_TELEFRAG",
	"MOD_FALLING",
	"MOD_SUICIDE",
 	"MOD_BLED",       
	"MOD_TARGET_LASER",
	"MOD_TRIGGER_HURT",
#ifdef MISSIONPACK
	"MOD_NAIL",
	"MOD_CHAINGUN",
	"MOD_PROXIMITY_MINE",
	"MOD_KAMIKAZE",
	"MOD_JUICED",
#endif
	"MOD_GRAPPLE"
};

#ifdef MISSIONPACK
/*
==================
Kamikaze_DeathActivate
==================
*/
void Kamikaze_DeathActivate( gentity_t *ent ) {
	G_StartKamikaze(ent);
	G_FreeEntity(ent);
}

/*
==================
Kamikaze_DeathTimer
==================
*/
void Kamikaze_DeathTimer( gentity_t *self ) {
	gentity_t *ent;

	ent = G_Spawn();
	ent->classname = "kamikaze timer";
	VectorCopy(self->s.pos.trBase, ent->s.pos.trBase);
	ent->r.svFlags |= SVF_NOCLIENT;
	ent->think = Kamikaze_DeathActivate;
	ent->nextthink = level.time + 5 * 1000;

	ent->activator = self;
}

#endif

/*
==================
CheckAlmostCapture
==================
*/
void CheckAlmostCapture( gentity_t *self, gentity_t *attacker ) {
	gentity_t	*ent;
	vec3_t		dir;
	char		*classname;

	// if this player was carrying a flag
	if ( self->client->ps.powerups[PW_REDFLAG] ||
		self->client->ps.powerups[PW_BLUEFLAG] ||
		self->client->ps.powerups[PW_NEUTRALFLAG] ) {
		// get the goal flag this player should have been going for
		if ( g_gametype.integer == GT_CTF ) {
			if ( self->client->sess.sessionTeam == TEAM_BLUE ) {
				classname = "team_CTF_blueflag";
			}
			else {
				classname = "team_CTF_redflag";
			}
		}
		else {
			if ( self->client->sess.sessionTeam == TEAM_BLUE ) {
				classname = "team_CTF_redflag";
			}
			else {
				classname = "team_CTF_blueflag";
			}
		}
		ent = NULL;
		do
		{
			ent = G_Find(ent, FOFS(classname), classname);
		} while (ent && (ent->flags & FL_DROPPED_ITEM));
		// if we found the destination flag and it's not picked up
		if (ent && !(ent->r.svFlags & SVF_NOCLIENT) ) {
			// if the player was *very* close
			VectorSubtract( self->client->ps.origin, ent->s.origin, dir );
			if ( VectorLength(dir) < 200 ) {
				self->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				if ( attacker->client ) {
					attacker->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				}
			}
		}
	}
}

/*
==================
CheckAlmostScored
==================
*/
void CheckAlmostScored( gentity_t *self, gentity_t *attacker ) {
	gentity_t	*ent;
	vec3_t		dir;
	char		*classname;

	// if the player was carrying cubes
	if ( self->client->ps.generic1 ) {
		if ( self->client->sess.sessionTeam == TEAM_BLUE ) {
			classname = "team_redobelisk";
		}
		else {
			classname = "team_blueobelisk";
		}
		ent = G_Find(NULL, FOFS(classname), classname);
		// if we found the destination obelisk
		if ( ent ) {
			// if the player was *very* close
			VectorSubtract( self->client->ps.origin, ent->s.origin, dir );
			if ( VectorLength(dir) < 200 ) {
				self->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				if ( attacker->client ) {
					attacker->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_HOLYSHIT;
				}
			}
		}
	}
}

/*
==================
player_die
==================
*/
void player_die( gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int meansOfDeath ) {
	gentity_t	*ent;
	int			anim;
	int			contents;
	int			killer;
	int			i;
	char		*killerName, *obit;
        vec3_t                          tmpOrigin;

	if ( self->client->ps.pm_type == PM_DEAD ) {
		return;
	}

	if ( level.intermissiontime ) {
		return;
	}

	// check for an almost capture
	CheckAlmostCapture( self, attacker );
	// check for a player that almost brought in cubes
	CheckAlmostScored( self, attacker );

	if (self->client && self->client->hook) {
		Weapon_HookFree(self->client->hook);
	}
#ifdef MISSIONPACK
	if ((self->client->ps.eFlags & EF_TICKING) && self->activator) {
		self->client->ps.eFlags &= ~EF_TICKING;
		self->activator->think = G_FreeEntity;
		self->activator->nextthink = level.time;
	}
#endif
	self->client->ps.pm_type = PM_DEAD;

	if ( attacker ) {
		killer = attacker->s.number;
		if ( attacker->client ) {
			killerName = attacker->client->pers.netname;
		} else {
			killerName = "<non-client>";
		}
	} else {
		killer = ENTITYNUM_WORLD;
		killerName = "<world>";
	}

	if ( killer < 0 || killer >= MAX_CLIENTS ) {
		killer = ENTITYNUM_WORLD;
		killerName = "<world>";
	}

	if ( meansOfDeath < 0 || meansOfDeath >= sizeof( modNames ) / sizeof( modNames[0] ) ) {
		obit = "<bad obituary>";
	} else {
		obit = modNames[meansOfDeath];
	}

	G_LogPrintf("Kill: %i %i %i: %s killed %s by %s\n",
		killer, self->s.number, meansOfDeath, killerName,
		self->client->pers.netname, obit );

	// broadcast the death event to everyone
	ent = G_TempEntity( self->r.currentOrigin, EV_OBITUARY );
	ent->s.eventParm = meansOfDeath;
	ent->s.otherEntityNum = self->s.number;
	ent->s.otherEntityNum2 = killer;
	ent->r.svFlags = SVF_BROADCAST;	// send to everyone

	self->enemy = attacker;

	self->client->ps.persistant[PERS_KILLED]++;

	if (attacker && attacker->client) {
		attacker->client->lastkilled_client = self->s.number;

		if ( attacker == self || OnSameTeam (self, attacker ) ) {
			AddScore( attacker, self->r.currentOrigin, -1 );
		} else {
			AddScore( attacker, self->r.currentOrigin, 1 );

			if( meansOfDeath == MOD_GAUNTLET ) {

				// play humiliation on player
				attacker->client->ps.persistant[PERS_GAUNTLET_FRAG_COUNT]++;

				// add the sprite over the player's head
				attacker->client->ps.eFlags &= ~( EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND | EF_AWARD_CAP );
				attacker->client->ps.eFlags |= EF_AWARD_GAUNTLET;
				attacker->client->rewardTime = level.time + REWARD_SPRITE_TIME;

				// also play humiliation on target
				self->client->ps.persistant[PERS_PLAYEREVENTS] ^= PLAYEREVENT_GAUNTLETREWARD;
			}

			// check for two kills in a short amount of time
			// if this is close enough to the last kill, give a reward sound
			if ( level.time - attacker->client->lastKillTime < CARNAGE_REWARD_TIME ) {
				// play excellent on player
				attacker->client->ps.persistant[PERS_EXCELLENT_COUNT]++;

				// add the sprite over the player's head
				attacker->client->ps.eFlags &= ~(EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND | EF_AWARD_CAP );
				attacker->client->ps.eFlags |= EF_AWARD_EXCELLENT;
				attacker->client->rewardTime = level.time + REWARD_SPRITE_TIME;
			}
			attacker->client->lastKillTime = level.time;

		}
	} else {
		AddScore( self, self->r.currentOrigin, -1 );
	}

	// Add team bonuses
	Team_FragBonuses(self, inflictor, attacker);
/*  Don't want any of this   --Xamis
	// if I committed suicide, the flag does not fall, it returns.
	if (meansOfDeath == MOD_SUICIDE) {
		if ( self->client->ps.powerups[PW_NEUTRALFLAG] ) {		// only happens in One Flag CTF
			Team_ReturnFlag( TEAM_FREE );
			self->client->ps.powerups[PW_NEUTRALFLAG] = 0;
		}
		else if ( self->client->ps.powerups[PW_REDFLAG] ) {		// only happens in standard CTF
			Team_ReturnFlag( TEAM_RED );
			self->client->ps.powerups[PW_REDFLAG] = 0;
		}
		else if ( self->client->ps.powerups[PW_BLUEFLAG] ) {	// only happens in standard CTF
			Team_ReturnFlag( TEAM_BLUE );
			self->client->ps.powerups[PW_BLUEFLAG] = 0;
		}
	}
 */

	// if client is in a nodrop area, don't drop anything (but return CTF flags!)
                   VectorCopy(  self->r.currentOrigin, tmpOrigin);
                   tmpOrigin[2]-=25;
	contents = trap_PointContents( tmpOrigin, -1 );
	if ( !( contents & CONTENTS_NODROP )) {
		TossClientItems( self );
	}
	else {
                                     G_Printf("CONTENTS_NODROP\n ");
		if ( self->client->ps.powerups[PW_NEUTRALFLAG] ) {		// only happens in One Flag CTF
			Team_ReturnFlag( TEAM_FREE );
		}
		else if ( self->client->ps.powerups[PW_REDFLAG] ) {		// only happens in standard CTF
			Team_ReturnFlag( TEAM_RED );
		}
		else if ( self->client->ps.powerups[PW_BLUEFLAG] ) {	// only happens in standard CTF
			Team_ReturnFlag( TEAM_BLUE );
		}
	}
#ifdef MISSIONPACK
	TossClientPersistantPowerups( self );
	if( g_gametype.integer == GT_BOMB ) {
		TossClientCubes( self );
	}
#endif

	Cmd_Score_f( self );		// show scores
	// send updated scores to any clients that are following this one,
	// or they would get stale scoreboards
	for ( i = 0 ; i < level.maxclients ; i++ ) {
		gclient_t	*client;

		client = &level.clients[i];
		if ( client->pers.connected != CON_CONNECTED ) {
			continue;
		}
		if ( client->sess.sessionTeam != TEAM_SPECTATOR ) {
			continue;
		}
		if ( client->sess.spectatorClient == self->s.number ) {
			Cmd_Score_f( g_entities + i );
		}
	}

	self->takedamage = qtrue;	// can still be gibbed

	self->s.weapon = WP_NONE;
	self->s.powerups = 0;
	self->r.contents = CONTENTS_CORPSE;

	self->s.angles[0] = 0;
	self->s.angles[2] = 0;
	LookAtKiller (self, inflictor, attacker);

	VectorCopy( self->s.angles, self->client->ps.viewangles );

	self->s.loopSound = 0;

	self->r.maxs[2] = -8;

	// don't allow respawn until the death anim is done
	// g_forcerespawn may force spawning at some later time
	self->client->respawnTime = level.time + 1700;

	// remove powerups
	memset( self->client->ps.powerups, 0, sizeof(self->client->ps.powerups) );

	// never gib in a nodrop
	if ( 0/*(self->health <= GIB_HEALTH && !(contents & CONTENTS_NODROP) && g_blood.integer) || meansOfDeath == MOD_SUICIDE*/) {
		// gib death
		GibEntity( self, killer );
	} else {
		// normal death
		static int i;

		switch ( i ) {
		case 0:
			anim = BOTH_DEATH1;
			break;
		case 1:
			anim = BOTH_DEATH2;
			break;
		case 2:
		default:
			anim = BOTH_DEATH3;
			break;
		}

		// for the no-blood option, we need to prevent the health
		// from going to gib level
		if ( self->health <= GIB_HEALTH ) {
			self->health = GIB_HEALTH+1;
		}

		self->client->ps.legsAnim =
			( ( self->client->ps.legsAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | anim;
		self->client->ps.torsoAnim =
			( ( self->client->ps.torsoAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | anim;

		G_AddEvent( self, EV_DEATH1 + i, killer );

		// the body can still be gibbed
		self->die = body_die;

		// globally cycle through the different death animations
		i = ( i + 1 ) % 3;

#ifdef MISSIONPACK
		if (self->s.eFlags & EF_KAMIKAZE) {
			Kamikaze_DeathTimer( self );
		}
#endif
	}

	trap_LinkEntity (self);

}


/*
================
CheckArmor
================
*/
int CheckArmor (gentity_t *ent, int damage, int dflags)
{
/*	gclient_t	*client;
	int			save;
	int			count;

	if (!damage)
		return 0;

	client = ent->client;

	if (!client)
		return 0;

	if (dflags & DAMAGE_NO_ARMOR)
		return 0;

	// armor
	count = client->ps.stats[STAT_ARMOR];
	save = ceil( damage * ARMOR_PROTECTION );
	if (save >= count)
		save = count;

	if (!save)
		return 0;

	client->ps.stats[STAT_ARMOR] -= save;
*/
	return 0;
}

/*
================
RaySphereIntersections
================
*/
int RaySphereIntersections( vec3_t origin, float radius, vec3_t point, vec3_t dir, vec3_t intersections[2] ) {
	float b, c, d, t;

	//	| origin - (point + t * dir) | = radius
	//	a = dir[0]^2 + dir[1]^2 + dir[2]^2;
	//	b = 2 * (dir[0] * (point[0] - origin[0]) + dir[1] * (point[1] - origin[1]) + dir[2] * (point[2] - origin[2]));
	//	c = (point[0] - origin[0])^2 + (point[1] - origin[1])^2 + (point[2] - origin[2])^2 - radius^2;

	// normalize dir so a = 1
	VectorNormalize(dir);
	b = 2 * (dir[0] * (point[0] - origin[0]) + dir[1] * (point[1] - origin[1]) + dir[2] * (point[2] - origin[2]));
	c = (point[0] - origin[0]) * (point[0] - origin[0]) +
		(point[1] - origin[1]) * (point[1] - origin[1]) +
		(point[2] - origin[2]) * (point[2] - origin[2]) -
		radius * radius;

	d = b * b - 4 * c;
	if (d > 0) {
		t = (- b + sqrt(d)) / 2;
		VectorMA(point, t, dir, intersections[0]);
		t = (- b - sqrt(d)) / 2;
		VectorMA(point, t, dir, intersections[1]);
		return 2;
	}
	else if (d == 0) {
		t = (- b ) / 2;
		VectorMA(point, t, dir, intersections[0]);
		return 1;
	}
	return 0;
}


/*
================
G_InvulnerabilityEffect
================
*/
int G_InvulnerabilityEffect( gentity_t *targ, vec3_t dir, vec3_t point, vec3_t impactpoint, vec3_t bouncedir ) {
	gentity_t	*impact;
	vec3_t		intersections[2], vec;
	int			n;

	if ( !targ->client ) {
		return qfalse;
	}
	VectorCopy(dir, vec);
	VectorInverse(vec);
	// sphere model radius = 42 units
	n = RaySphereIntersections( targ->client->ps.origin, 42, point, vec, intersections);
	if (n > 0) {
		impact = G_TempEntity( targ->client->ps.origin, EV_INVUL_IMPACT );
		VectorSubtract(intersections[0], targ->client->ps.origin, vec);
		vectoangles(vec, impact->s.angles);
		impact->s.angles[0] += 90;
		if (impact->s.angles[0] > 360)
			impact->s.angles[0] -= 360;
		if ( impactpoint ) {
			VectorCopy( intersections[0], impactpoint );
		}
		if ( bouncedir ) {
			VectorCopy( vec, bouncedir );
			VectorNormalize( bouncedir );
		}
		return qtrue;
	}
	else {
		return qfalse;
	}
}


qboolean HasPowerup( gentity_t *ent, int powerup )
{
  if (!ent)
    return qfalse;
  if (!ent->client)
    return qfalse;


  if (ent->client->ps.powerups[powerup] > 0 )
    return qtrue;


  return qfalse;
}


/*
============
T_Damage

targ		entity that is being damaged
inflictor	entity that is causing the damage
attacker	entity that caused the inflictor to damage targ
	example: targ=monster, inflictor=rocket, attacker=player

dir			direction of the attack for knockback
point		point at which the damage is being inflicted, used for headshots
damage		amount of damage being inflicted
knockback	force to be applied against targ as a result of the damage

inflictor, attacker, dir, and point can be NULL for environmental effects

dflags		these flags are used to control how T_Damage works
	DAMAGE_RADIUS			damage was indirect (from a nearby explosion)
	DAMAGE_NO_ARMOR			armor does not protect from this damage
	DAMAGE_NO_KNOCKBACK		do not affect velocity, just view angles
	DAMAGE_NO_PROTECTION	kills godmode, armor, everything
============
*/
void G_Damage( gentity_t *targ, gentity_t *inflictor, gentity_t *attacker,
			   vec3_t dir, vec3_t point, int damage, int dflags, int mod ) {
	gclient_t	*client;
	int			take;
	int			save;
	int			asave;
	int			knockback;
	int			max;
        int                     dummy;
        int                 HitLocation = LOC_NULL;
        qboolean    bleeding = qfalse;
        qboolean    headblown = qfalse;
//        qboolean    spray_blood = qfalse;
        float               through_vest = 1;

#ifdef MISSIONPACK
	//vec3_t		bouncedir, impactpoint; //blud commented out to stop unused variable warning
#endif

	if (!targ->takedamage) {
          return;
	}
    if ( GameState == STATE_OPEN && (g_gametype.integer == GT_BOMB|| g_gametype.integer == GT_TEAMSV )&& targ->client )
          return;

	// the intermission has allready been qualified for, so don't
	// allow any extra scoring
	if ( level.intermissionQueued ) {
          return;
	}
	if ( !inflictor ) {
		inflictor = &g_entities[ENTITYNUM_WORLD];
	}
	if ( !attacker ) {
		attacker = &g_entities[ENTITYNUM_WORLD];
	}
		// Xamis
	if ( targ->s.eType == ET_BREAKABLE ) {
		targ->health -= damage;
		G_BreakGlass( targ, point );
                return;
	}
        take = damage;
        if ( mod == MOD_FALLING ) {
        // add damage to both legs...
          targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << LEG_DAMAGE );
        // remove stamina
          dummy = take*2;
          if (targ->client->ps.stats[STAT_STAMINA] < dummy) {
            dummy -= targ->client->ps.stats[STAT_STAMINA];
            targ->client->ps.stats[STAT_STAMINA] = 0;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << LEG_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << CHEST_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << ARM_DAMAGE );
            take += dummy;
          } else {
            targ->client->ps.stats[STAT_STAMINA] -= dummy;
          }


        } else if ( targ->client &&
                    ( attacker && attacker->client ) &&
                        point ) {

        // if dead - ignore
                      if ( targ->r.contents == CONTENTS_CORPSE )
                        return;

                      if ( attacker->client->ps.weapon == WP_SR8 )
                        through_vest = 1;
                      else if ( HasPowerup(targ, PW_VEST ) )
                        through_vest = 0;
                      else if ( !HasPowerup( targ, PW_VEST ) )
                        through_vest = 0;
                      
                     

        // get the hit location
                    //  G_Printf("getting Hitlocation\n");
                      HitLocation = CheckLocationDamage( targ,point, mod );
                   //   G_Printf("got Hitlocation: %i\n", HitLocation);

        // if nothing was hit, return
                     if (HitLocation == LOC_NULL ) return;

        // extra handling for grenades
                      if (dflags & DAMAGE_RADIUS) {
                        if (HitLocation == LOC_FACE) {
                     //     spray_blood = qtrue;
                          take *= 2;
                         // armorhit = 2;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << HEAD_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << CHEST_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << ARM_DAMAGE );
                        } else if (HitLocation == LOC_HEAD) {
                         // spray_blood = qtrue;
                          if (HasPowerup( targ, PW_HELMET )&& attacker->client->ps.weapon != WP_SR8 ) take *= 1;
                          else take *= 2;
                        //  armorhit = 2;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << HEAD_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << ARM_DAMAGE );
                        } else {
                // we traced chest, back, stomach, arms or legs. We assume there is
                // no partial cover. damage will be distributed to the damage areas.
                          if (HasPowerup( targ, PW_VEST ) ) take *= 0.7;
                          else take *= 1;
//                          armorhit = 1;
 //                         spray_blood = qtrue;
                          if ( (random() < 0.4) || HasPowerup(targ, PW_VEST) ) bleeding = qfalse;
                          else bleeding = qtrue;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << LEG_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << CHEST_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << ARM_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << HEAD_DAMAGE );
                        }

            // here goes the calculation for bullets / melee
                      } else switch ( HitLocation ){

                        case LOC_FACE:
                          take *= 10;
                          if ( (take > targ->health) )  {
                            headblown = qtrue;
                            take = 999;
                            if(! (dflags & DAMAGE_RADIUS) )
                              G_Printf(NULL, S_COLOR_RED"%ss face was blown away by %s!\n", targ->client->pers.netname, attacker->client->pers.netname);
                          }
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << HEAD_DAMAGE );
                          break;
                        case LOC_HEAD:
                          if (HasPowerup(targ, PW_HELMET && attacker->client->ps.weapon != WP_SR8)) take *= 4;
                          else take *= 8;
                          if ( (take > targ->health)) {
                            headblown = qtrue;
                            take = 999;
                            //if(! (dflags & DAMAGE_RADIUS) )
                              //PrintMsg(NULL, S_COLOR_RED"%ss took a shot in the head from %s!\n", targ->client->pers.netname, attacker->client->pers.netname);
                          }
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << HEAD_DAMAGE );
                          break;
                        case LOC_CHEST:
                          take *= 2.5;
                          if ( HasPowerup(targ, PW_VEST) ) bleeding = qfalse;
                          else bleeding = qtrue;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << CHEST_DAMAGE );
                          break;
                        case LOC_BACK:
                          take *= 2.0;
                          if (  HasPowerup(targ, PW_VEST) ) bleeding = qfalse;
                          else bleeding = qtrue;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << CHEST_DAMAGE );
                          break;
                        case LOC_STOMACH:
                          take *= 2.5;
                          if ( HasPowerup(targ, PW_VEST) ) bleeding = qfalse;
                          else bleeding = qtrue;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << CHEST_DAMAGE );
                          break;
                        case LOC_RIGHTARM:
                          take *= 1.63;
                          if ( random() < 0.6 ) bleeding = qfalse;
                          else bleeding = qtrue;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << ARM_DAMAGE );
                          break;
                        case LOC_LEFTARM:
                          take *= 1.63;
                          if ( random() < 0.6 ) bleeding = qfalse;
                          else bleeding = qtrue;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << ARM_DAMAGE );
                          break;
                        case LOC_RIGHTLEG:
                          take *= 1.75;
                         bleeding = qtrue;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << LEG_DAMAGE );
                          break;
                        case LOC_LEFTLEG:
                          take *= 1.75;
                          bleeding = qtrue;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << LEG_DAMAGE );
                          break;
                      }
                      


        // if a grenade hit was encountered, remove stamina
                           if(dflags & DAMAGE_RADIUS) {
                             dummy = take*4;
                             if ( targ->client->ps.stats[STAT_STAMINA] > dummy )
                               targ->client->ps.stats[STAT_STAMINA] -= dummy;
                             else {
                               dummy -= targ->client->ps.stats[STAT_STAMINA];
                               targ->client->ps.stats[STAT_STAMINA] = 0;
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << LEG_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << CHEST_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << ARM_DAMAGE );
            targ->client->ps.stats[STAT_DMG_LOC] |= ( 1 << HEAD_DAMAGE );
                               take += dummy;
                             }
                           }

	// reduce damage by the attacker's handicap value
	// unless they are rocket jumping
	if ( attacker->client && attacker != targ ) {
		max = STAT_MAX_HEALTH;
		damage = damage * max / 100;
	}

	client = targ->client;

	if ( client ) {
		if ( client->noclip ) {
			return;
		}
	}

	if ( !dir ) {
		dflags |= DAMAGE_NO_KNOCKBACK;
	} else {
		VectorNormalize(dir);
	}

	knockback = damage;
	if ( knockback > 100 ) {
		knockback = 100;
	}
	if ( targ->flags & FL_NO_KNOCKBACK ) {
		knockback = 0;
	}
	if ( dflags & DAMAGE_NO_KNOCKBACK ) {
		knockback = 0;
	}

        
            //    if(mod == MOD_BOOT){
             //             knockback*=20;
             //             bleeding = qfalse;
             //        }
        
	// figure momentum add, even if the damage won't be taken
	if ( knockback && targ->client ) {
		vec3_t	kvel;
		float	mass;

		mass = 200;

		VectorScale (dir, g_knockback.value * (float)knockback / mass, kvel);
		VectorAdd (targ->client->ps.velocity, kvel, targ->client->ps.velocity);

		// set the timer so that the other client can't cancel
		// out the movement immediately
		if ( !targ->client->ps.pm_time ) {
			int		t;

			t = knockback * 2;
			if ( t < 50 ) {
				t = 50;
			}
			if ( t > 200 ) {
				t = 200;
			}
			targ->client->ps.pm_time = t;
			targ->client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
		}
	}

	// check for completely getting out of the damage
	if ( !(dflags & DAMAGE_NO_PROTECTION) ) {

		// if TF_NO_FRIENDLY_FIRE is set, don't do damage to the target
		// if the attacker was on the same team
		if ( targ != attacker && OnSameTeam (targ, attacker)  ) {
			if ( !g_friendlyFire.integer ) {
                          return;
			}
		}
		// check for godmode
		if ( targ->flags & FL_GODMODE ) {
                                         targ->client->ps.stats[STAT_DMG_LOC]=0;
                                         return ;
		}
	}
                                if ( targ->r.svFlags & SVF_BOT ){
                                         targ->client->ps.stats[STAT_DMG_LOC]=0;
                                        }

	// add to the attacker's hit counter (if the target isn't a general entity like a prox mine)
	if ( attacker->client && client
			&& targ != attacker && targ->health > 0
			&& targ->s.eType != ET_MISSILE
			&& targ->s.eType != ET_GENERAL) {
		if ( OnSameTeam( targ, attacker ) ) {
			attacker->client->ps.persistant[PERS_HITS]--;
		} else {
			attacker->client->ps.persistant[PERS_HITS]++;
		}
		attacker->client->ps.persistant[PERS_ATTACKEE_ARMOR] = (targ->health<<8)|(0);
	}

	// always give half damage if hurting self
	// calculated after knockback, so rocket jumping works


        //Remove this --Xamis
/*
	if ( targ == attacker) {
		damage *= 0.5;
	}
*/

	if ( damage < 1 ) {
		damage = 1;
	}
	take = damage;
	save = 0;

	// save some from armor
	asave = CheckArmor (targ, take, dflags);
	take -= asave;

		//G_Printf( "%i: client:%i health:%i damage:%i armor:%i\n", level.time, targ->s.number,
		//	targ->health, take, asave );

	// add to the damage inflicted on a player this frame
	// the total will be turned into screen blends and view angle kicks
	// at the end of the frame
	if ( client ) {
		if ( attacker ) {
			client->ps.persistant[PERS_ATTACKER] = attacker->s.number;
		} else {
			client->ps.persistant[PERS_ATTACKER] = ENTITYNUM_WORLD;
		}
		client->damage_armor += asave;
		client->damage_blood += take;
		client->damage_knockback += knockback;
		if ( dir ) {
			VectorCopy ( dir, client->damage_from );
			client->damage_fromWorld = qfalse;
		} else {
			VectorCopy ( targ->r.currentOrigin, client->damage_from );
			client->damage_fromWorld = qtrue;
		}
	}

	// See if it's the player hurting the emeny flag carrier
	if( g_gametype.integer == GT_CTF) {
		Team_CheckHurtCarrier(targ, attacker);
	}

	if (targ->client) {
		// set the last client who damaged the target
		targ->client->lasthurt_client = attacker->s.number;
		targ->client->lasthurt_mod = mod;
	}
   }
        
                  if(bleeding && !(targ->r.svFlags & SVF_BOT) ){
                      targ->client->ps.pm_flags |= PMF_BLEEDING;
                     // G_Printf("bleeding true\n");
                      }
	// do the damage
	if (take) {
		targ->health = targ->health - take;
		if ( targ->client ) {
			targ->client->ps.stats[STAT_HEALTH] = targ->health;
			targ->client->ps.stats[STAT_STAMINA] = targ->health; //Xamis
		}

		if ( targ->health <= 0 ) {
			if ( targ->client )
				targ->flags |= FL_NO_KNOCKBACK;

			if (targ->health < -999)
				targ->health = -999;

			targ->enemy = attacker;
			targ->die (targ, inflictor, attacker, take, mod);
		} else if ( targ->pain ) {
			targ->pain (targ, attacker, take);
		}
	}


}






/*
============
CanDamage

Returns qtrue if the inflictor can directly damage the target.  Used for
explosions and melee attacks.
============
*/
qboolean CanDamage(gentity_t *targ, vec3_t origin) {
	vec3_t	dest;
	trace_t	tr;
	vec3_t	midpoint;

	// use the midpoint of the bounds instead of the origin, because
	// bmodels may have their origin is 0,0,0
	VectorAdd (targ->r.absmin, targ->r.absmax, midpoint);
	VectorScale (midpoint, 0.5, midpoint);

	VectorCopy (midpoint, dest);
	trap_Trace ( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0 || tr.entityNum == targ->s.number)
		return qtrue;

	// this should probably check in the plane of projection,
	// rather than in world coordinate, and also include Z
	VectorCopy (midpoint, dest);
	dest[0] += 15.0;
	dest[1] += 15.0;
	trap_Trace ( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	VectorCopy (midpoint, dest);
	dest[0] += 15.0;
	dest[1] -= 15.0;
	trap_Trace ( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	VectorCopy (midpoint, dest);
	dest[0] -= 15.0;
	dest[1] += 15.0;
	trap_Trace ( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;

	VectorCopy (midpoint, dest);
	dest[0] -= 15.0;
	dest[1] -= 15.0;
	trap_Trace ( &tr, origin, vec3_origin, vec3_origin, dest, ENTITYNUM_NONE, MASK_SOLID);
	if (tr.fraction == 1.0)
		return qtrue;


	return qfalse;
}


/*
============
G_RadiusDamage
============
*/
qboolean G_RadiusDamage ( vec3_t origin, gentity_t *attacker, float damage, float radius,
					 gentity_t *ignore, int mod) {
	float		points, dist;
	gentity_t	*ent;
	int			entityList[MAX_GENTITIES];
	int			numListedEntities;
	vec3_t		mins, maxs;
	vec3_t		v;
	vec3_t		dir;
	int			i, e;
	qboolean	hitClient = qfalse;

	if ( radius < 1 ) {
		radius = 1;
	}

	for ( i = 0 ; i < 3 ; i++ ) {
		mins[i] = origin[i] - radius;
		maxs[i] = origin[i] + radius;
	}

	numListedEntities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

	for ( e = 0 ; e < numListedEntities ; e++ ) {
		ent = &g_entities[entityList[ e ]];

		if (ent == ignore)
			continue;
		if (!ent->takedamage)
			continue;

		// find the distance from the edge of the bounding box
		for ( i = 0 ; i < 3 ; i++ ) {
			if ( origin[i] < ent->r.absmin[i] ) {
				v[i] = ent->r.absmin[i] - origin[i];
			} else if ( origin[i] > ent->r.absmax[i] ) {
				v[i] = origin[i] - ent->r.absmax[i];
			} else {
				v[i] = 0;
			}
		}

		dist = VectorLength( v );
		if ( dist >= radius ) {
			continue;
		}

		points = damage * ( 1.0 - dist / radius );

		if( CanDamage (ent, origin) ) {
			if( LogAccuracyHit( ent, attacker ) ) {
				hitClient = qtrue;
			}
			VectorSubtract (ent->r.currentOrigin, origin, dir);
			// push the center of mass higher than the origin so players
			// get knocked into the air more
			dir[2] += 24;
			G_Damage (ent, NULL, attacker, dir, origin, (int)points, DAMAGE_RADIUS, mod);
		}
	}

	return hitClient;
}
