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
#include "g_local.h"

#define	MISSILE_PRESTEP_TIME	50



void G_KnifeThink( gentity_t *self ) {
	trace_t trace;
	int mask;

	if(self->clipmask)
		mask = self->clipmask;
	else
		mask = MASK_PLAYERSOLID & ~CONTENTS_BODY;

	trap_Trace(&trace, self->r.currentOrigin, self->r.mins,self->r.maxs, self->s.origin2,
		self->r.ownerNum, mask);

	if(trace.fraction == 1){
		self->s.groundEntityNum = -1;
	}

	if(level.time > self->wait)
		G_FreeEntity(self);

	self->nextthink = level.time + 100;
}


/*
================
G_BounceMissile

================
*/
void G_BounceMissile( gentity_t *ent, trace_t *trace ) {
	vec3_t	velocity;
	float	dot;
	int		hitTime;

	// reflect the velocity on the trace plane
	hitTime = level.previousTime + ( level.time - level.previousTime ) * trace->fraction;
	BG_EvaluateTrajectoryDelta( &ent->s.pos, hitTime, velocity );
	dot = DotProduct( velocity, trace->plane.normal );
	VectorMA( velocity, -2*dot, trace->plane.normal, ent->s.pos.trDelta );

	if ( ent->s.eFlags & EF_BOUNCE_HALF ) {
		VectorScale( ent->s.pos.trDelta, 0.65, ent->s.pos.trDelta );
		// check for stop
		if ( trace->plane.normal[2] > 0.2 && VectorLength( ent->s.pos.trDelta ) < 40 ) {
			G_SetOrigin( ent, trace->endpos );
			return;
		}
	}

	VectorAdd( ent->r.currentOrigin, trace->plane.normal, ent->r.currentOrigin);
	VectorCopy( ent->r.currentOrigin, ent->s.pos.trBase );
	ent->s.pos.trTime = level.time;
}


/*
================
G_ExplodeMissile

Explode a missile without an impact
================
*/
void G_ExplodeMissile( gentity_t *ent ) {
	vec3_t		dir;
	vec3_t		origin;


        if ( !Q_stricmp( ent->classname , "ut_weapon_grenade_smoke" ) ||
              ent->s.weapon == WP_SMOKE ) {

          ent->nextthink = level.time + 100;
          ent->think = G_ExplodeSmokenade;
          ent->s.generic1 = MF_SMOKE;
          ent->r.svFlags |= SVF_BROADCAST;

          return;
              }



	BG_EvaluateTrajectory( &ent->s.pos, level.time, origin );
	SnapVector( origin );
	G_SetOrigin( ent, origin );

	// we don't have a valid direction, so just point straight up
	dir[0] = dir[1] = 0;
	dir[2] = 1;

	ent->s.eType = ET_GENERAL;
	G_AddEvent( ent, EV_MISSILE_MISS, DirToByte( dir ) );

	ent->freeAfterEvent = qtrue;



	// splash damage
	if ( ent->splashDamage ) {
		if( G_RadiusDamage( ent->r.currentOrigin, ent->parent, ent->splashDamage, ent->splashRadius, ent
			, ent->splashMethodOfDeath ) ) {
			g_entities[ent->r.ownerNum].client->accuracy_hits++;
		}
	}

	trap_LinkEntity( ent );
}


#ifdef MISSIONPACK
/*
================
ProximityMine_Explode
================
*/
/*
static void ProximityMine_Explode( gentity_t *mine ) {
	G_ExplodeMissile( mine );
	// if the prox mine has a trigger free it
	if (mine->activator) {
		G_FreeEntity(mine->activator);
		mine->activator = NULL;
	}
}
*/
/*
================
ProximityMine_Die
================
*/
/*
static void ProximityMine_Die( gentity_t *ent, gentity_t *inflictor, gentity_t *attacker, int damage, int mod ) {
	ent->think = ProximityMine_Explode;
	ent->nextthink = level.time + 1;
}
*/
/*
================
ProximityMine_Trigger
================
*/
/*
void ProximityMine_Trigger( gentity_t *trigger, gentity_t *other, trace_t *trace ) {
	vec3_t		v;
	gentity_t	*mine;

	if( !other->client ) {
		return;
	}

	// trigger is a cube, do a distance test now to act as if it's a sphere
	VectorSubtract( trigger->s.pos.trBase, other->s.pos.trBase, v );
	if( VectorLength( v ) > trigger->parent->splashRadius ) {
		return;
	}


	if ( g_gametype.integer >= GT_TEAM ) {
		// don't trigger same team mines
		if (trigger->parent->s.generic1 == other->client->sess.sessionTeam) {
			return;
		}
	}

	// ok, now check for ability to damage so we don't get triggered thru walls, closed doors, etc...
	if( !CanDamage( other, trigger->s.pos.trBase ) ) {
		return;
	}

	// trigger the mine!
	mine = trigger->parent;
	mine->s.loopSound = 0;
	G_AddEvent( mine, EV_PROXIMITY_MINE_TRIGGER, 0 );
	mine->nextthink = level.time + 500;

	G_FreeEntity( trigger );
}
*/
/*
================
ProximityMine_Activate
================
*/
/*
static void ProximityMine_Activate( gentity_t *ent ) {
	gentity_t	*trigger;
	float		r;

	ent->think = ProximityMine_Explode;
	ent->nextthink = level.time + g_proxMineTimeout.integer;

	ent->takedamage = qtrue;
	ent->health = 1;
	ent->die = ProximityMine_Die;

	ent->s.loopSound = G_SoundIndex( "sound/weapons/proxmine/wstbtick.wav" );

	// build the proximity trigger
	trigger = G_Spawn ();

	trigger->classname = "proxmine_trigger";

	r = ent->splashRadius;
	VectorSet( trigger->r.mins, -r, -r, -r );
	VectorSet( trigger->r.maxs, r, r, r );

	G_SetOrigin( trigger, ent->s.pos.trBase );

	trigger->parent = ent;
	trigger->r.contents = CONTENTS_TRIGGER;
	trigger->touch = ProximityMine_Trigger;

	trap_LinkEntity (trigger);

	// set pointer to trigger so the entity can be freed when the mine explodes
	ent->activator = trigger;
}
*/
/*
================
ProximityMine_ExplodeOnPlayer
================
*//*
static void ProximityMine_ExplodeOnPlayer( gentity_t *mine ) {
	gentity_t	*player;

	player = mine->enemy;
	player->client->ps.eFlags &= ~EF_TICKING;

	if ( player->client->invulnerabilityTime > level.time ) {
		G_Damage( player, mine->parent, mine->parent, vec3_origin, mine->s.origin, 1000, DAMAGE_NO_KNOCKBACK, MOD_JUICED );
		player->client->invulnerabilityTime = 0;
		G_TempEntity( player->client->ps.origin, EV_JUICED );
	}
	else {
		G_SetOrigin( mine, player->s.pos.trBase );
		// make sure the explosion gets to the client
		mine->r.svFlags &= ~SVF_NOCLIENT;
		mine->splashMethodOfDeath = MOD_PROXIMITY_MINE;
		G_ExplodeMissile( mine );
	}
}
*/
/*
================
ProximityMine_Player
================
*/
/*
static void ProximityMine_Player( gentity_t *mine, gentity_t *player ) {
	if( mine->s.eFlags & EF_NODRAW ) {
		return;
	}

	G_AddEvent( mine, EV_PROXIMITY_MINE_STICK, 0 );

	if( player->s.eFlags & EF_TICKING ) {
		player->activator->splashDamage += mine->splashDamage;
		player->activator->splashRadius *= 1.50;
		mine->think = G_FreeEntity;
		mine->nextthink = level.time;
		return;
	}

	player->client->ps.eFlags |= EF_TICKING;
	player->activator = mine;

	mine->s.eFlags |= EF_NODRAW;
	mine->r.svFlags |= SVF_NOCLIENT;
	mine->s.pos.trType = TR_LINEAR;
	VectorClear( mine->s.pos.trDelta );

	mine->enemy = player;
	mine->think = ProximityMine_ExplodeOnPlayer;
	if ( player->client->invulnerabilityTime > level.time ) {
		mine->nextthink = level.time + 2 * 1000;
	}
	else {
		mine->nextthink = level.time + 10 * 1000;
	}
}
*/
#endif

/*
================
G_MissileImpact
================
*/
void G_MissileImpact( gentity_t *ent, trace_t *trace ) {
	gentity_t		*other;
	qboolean		hitClient = qfalse;
                  qboolean		hitKnife  = qfalse;
	other = &g_entities[trace->entityNum];
        
        
        	if(other->takedamage)
		hitKnife = qtrue;

	// check for bounce
	if ( Q_stricmp(ent->classname, "knife") &&
		( ent->s.eFlags & ( EF_BOUNCE | EF_BOUNCE_HALF ) ) ) {
		G_BounceMissile( ent, trace );
		G_AddEvent( ent, EV_GRENADE_BOUNCE, 0 );
		return;
	}

	// impact damage
	if (other->takedamage) {
		// FIXME: wrong damage direction?
		if ( ent->damage ) {
			vec3_t	velocity;

			if( LogAccuracyHit( other, &g_entities[ent->r.ownerNum] ) ) {
				g_entities[ent->r.ownerNum].client->accuracy_hits++;
				hitClient = qtrue;
			}
			BG_EvaluateTrajectoryDelta( &ent->s.pos, level.time, velocity );
			if ( VectorLength( velocity ) == 0 ) {
				velocity[2] = 1;	// stepped on a grenade
			}
			G_Damage (other, ent, &g_entities[ent->r.ownerNum], velocity,
				ent->s.origin, ent->damage,
				0, ent->methodOfDeath);
		}
	}



	if (!strcmp(ent->classname, "hook")) {
		gentity_t *nent;
		vec3_t v;

		nent = G_Spawn();
		if ( other->takedamage && other->client ) {

			G_AddEvent( nent, EV_MISSILE_HIT, DirToByte( trace->plane.normal ) );
			nent->s.otherEntityNum = other->s.number;

			ent->enemy = other;

			v[0] = other->r.currentOrigin[0] + (other->r.mins[0] + other->r.maxs[0]) * 0.5;
			v[1] = other->r.currentOrigin[1] + (other->r.mins[1] + other->r.maxs[1]) * 0.5;
			v[2] = other->r.currentOrigin[2] + (other->r.mins[2] + other->r.maxs[2]) * 0.5;

			SnapVectorTowards( v, ent->s.pos.trBase );	// save net bandwidth
		} else {
			VectorCopy(trace->endpos, v);
			G_AddEvent( nent, EV_MISSILE_MISS, DirToByte( trace->plane.normal ) );
			ent->enemy = NULL;
		}

		SnapVectorTowards( v, ent->s.pos.trBase );	// save net bandwidth

		nent->freeAfterEvent = qtrue;
		// change over to a normal entity right at the point of impact
		nent->s.eType = ET_GENERAL;
		ent->s.eType = ET_GRAPPLE;

		G_SetOrigin( ent, v );
		G_SetOrigin( nent, v );

		ent->think = Weapon_HookThink;
		ent->nextthink = level.time + FRAMETIME;

		//ent->parent->client->ps.pm_flags |= PMF_GRAPPLE_PULL;
		//VectorCopy( ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);

		trap_LinkEntity( ent );
		trap_LinkEntity( nent );

		return;
	}
        
        	

	// is it cheaper in bandwidth to just remove this ent and create a new
	// one, rather than changing the missile into the explosion?

	if ( other->takedamage && other->client ) {
		G_AddEvent( ent, EV_MISSILE_HIT, DirToByte( trace->plane.normal ) );
		ent->s.otherEntityNum = other->s.number;
	} else if( trace->surfaceFlags & SURF_METALSTEPS ) {
		G_AddEvent( ent, EV_MISSILE_MISS_METAL, DirToByte( trace->plane.normal ) );
	} else {
		G_AddEvent( ent, EV_MISSILE_MISS, DirToByte( trace->plane.normal ) );
	}

	if(Q_stricmp(ent->classname, "knife")){
		ent->freeAfterEvent = qtrue;
	// change over to a normal entity right at the point of impact
		ent->s.eType = ET_GENERAL;
	} else  if ( !( hitKnife )){

		vec3_t dir;
		gitem_t			*item;

		item = BG_FindItemForWeapon(WP_KNIFE);
                                    ent->s.modelindex = item-bg_itemlist;
		ent->s.modelindex2 = 1;

		ent->item = item;

		ent->s.eType = ET_ITEM;
		ent->s.pos.trType = TR_GRAVITY;
		ent->physicsBounce = 0.01f;
		ent->r.contents = CONTENTS_TRIGGER;

		ent->touch = Touch_Item;
		ent->nextthink = level.time + 100;
		ent->think = G_KnifeThink;
		ent->wait = level.time + 30000;
		ent->flags |= FL_THROWN_ITEM;

		vectoangles(ent->s.pos.trDelta, dir);

		VectorCopy(dir, ent->s.apos.trBase);
		VectorCopy(dir, ent->r.currentAngles);
	}else{
                ent->freeAfterEvent = qtrue;
        // change over to a normal entity right at the point of impact
                ent->s.eType = ET_GENERAL;
	}

	SnapVectorTowards( trace->endpos, ent->s.pos.trBase );	// save net bandwidth

	G_SetOrigin( ent, trace->endpos );

	// splash damage (doesn't apply to person directly hit)
	if ( ent->splashDamage ) {
		if( G_RadiusDamage( trace->endpos, ent->parent, ent->splashDamage, ent->splashRadius,
			other, ent->splashMethodOfDeath ) ) {
			if( !hitClient ) {
				g_entities[ent->r.ownerNum].client->accuracy_hits++;
			}
		}
	}

	trap_LinkEntity( ent );
}



/*
================
G_RunMissile
================
*/

void G_RunMissile( gentity_t *ent ) {
	vec3_t		origin;
	trace_t		tr;
	int			passent;
	gentity_t	*traceEnt;
                  int count = 0;
        
	// get current position
	BG_EvaluateTrajectory( &ent->s.pos, level.time, origin );

	// if this missile bounced off an invulnerability sphere
	if ( ent->target_ent ) {
		passent = ent->target_ent->s.number;
	}

	else {
		// ignore interactions with the missile owner
		passent = ent->r.ownerNum;
	}
        //Loop through in case out missile encounters a func_breakable (glass)
        do  {
	// trace a line from the previous position to the current position
	trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, origin, passent, ent->clipmask );
	traceEnt = &g_entities[ tr.entityNum ];//the entity that resides at the end of our trace
        
        //check to see it a func_breakable ended our trace, if so destroy it.
        if  ( !strcmp(traceEnt->classname, "func_breakable" )){
        G_Damage (traceEnt, ent, ent, NULL, tr.endpos, 1000, 0, MOD_KNIFE);
        trap_UnlinkEntity( traceEnt );//unlink the func_breakable so our trace will continue past it next loop iteration
        count=1; // cause another pass throuhg the loop
        }else
        count =0;// no func_breakable entities this pass, don't trace again
        
        } while ( count );
	if ( tr.startsolid || tr.allsolid ) {
		// make sure the tr.entityNum is set to the entity we're stuck in
		trap_Trace( &tr, ent->r.currentOrigin, ent->r.mins, ent->r.maxs, ent->r.currentOrigin, passent, ent->clipmask );
		tr.fraction = 0;
	}
	else {
		VectorCopy( tr.endpos, ent->r.currentOrigin );
	}

    
	trap_LinkEntity( ent );

	if ( tr.fraction != 1 ) {
		// never explode or bounce on sky
		if ( tr.surfaceFlags & SURF_NOIMPACT ) {
			// If grapple, reset owner
			if (ent->parent && ent->parent->client && ent->parent->client->hook == ent) {
				ent->parent->client->hook = NULL;
			}
			G_FreeEntity( ent );
			return;
		}
		G_MissileImpact( ent, &tr );
		if ( ent->s.eType != ET_MISSILE ) {
			return;		// exploded
		}
	}

	// check think function after bouncing
	G_RunThink( ent );
        

}

/*
=================
throw_grenade
=================
*/
gentity_t *throw_grenade (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*bolt;


	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "ut_weapon_grenade_he";
        bolt->nextthink = level.time + bg_nadeTimer.fuseTime[self->s.number];// level.time + 3000;
        G_Printf("self->s.number = %i\n",self->s.number);
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_HE;
	bolt->s.eFlags = EF_BOUNCE_HALF;
	bolt->r.ownerNum = self->s.number;
	bolt->timestamp = level.time;
	bolt->parent = self;
	bolt->damage = 500;
	bolt->splashDamage = 300;
	bolt->splashRadius = 300;
	bolt->methodOfDeath = MOD_GRENADE;
	bolt->splashMethodOfDeath = MOD_GRENADE_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

        VectorScale( dir, (bg_nadeTimer.throwStrength[self->s.number]/100 ), bolt->s.pos.trDelta );

	bolt->s.pos.trType = TR_GRAVITY;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}



void G_ExplodeSmokenade( gentity_t *ent ) {

    // clear the lower 16 bits (there will be the angle stored)
  ent->s.frame &= SMOKE_FLAGS;

  ent->s.generic1 = MF_SMOKE;
  ent->r.svFlags |= SVF_BROADCAST;

  if (ent->count <= 0) {

    ent->nextthink = level.time + ALTURT_SMOKENADETIME;
    ent->think = G_FreeEntity;
    BG_PlayerTouchesSmoke( 0, ent->parent->client->ps.stats );


  } else {


    if ((ent->count % 10) == 0) {
      trace_t tr;
      vec3_t start, end, dir;

      VectorCopy(ent->r.currentOrigin, start);
      start[2]+=16.0;


            // get a point that's not in any wall
      while ( trap_PointContents( start, ent->s.number ) & CONTENTS_SOLID ) {
        start[2] -= 2.0f;

        if ( start[2] < ent->r.currentOrigin[2] ) {
          start[2] = ent->r.currentOrigin[2];
          break;
        }
      }

            // first clear the old the old directions
      ent->s.frame &= ~SMOKE_FLAGS;

            // check UP
      dir[0] = 0.0;
      dir[1] = 0.0;
      dir[2] = 1.0;
      VectorMA( start, ALTURT_SMOKENADE_DISTANCE, dir, end);

      trap_Trace( &tr, start, NULL, NULL, end, ent->s.number, MASK_SOLID);
      if (tr.fraction > 1.0) tr.fraction = 1.0;
      ent->s.frame |= ((int)(ALTURT_SMOKEMASK_VALUE*tr.fraction)) << ALTURT_SMOKEMASK_SUP;

            // check LEFT
      dir[0] = -1.0;
      dir[1] = 0.0;
      dir[2] = 0.0;
      VectorMA( start, ALTURT_SMOKENADE_DISTANCE, dir, end);

      trap_Trace( &tr, start, NULL, NULL, end, ent->s.number, MASK_SOLID);
      if (tr.fraction > 1.0) tr.fraction = 1.0;
      ent->s.frame |= ((int)(ALTURT_SMOKEMASK_VALUE*tr.fraction)) << ALTURT_SMOKEMASK_SLEFT;

            // check RIGHT
      dir[0] = 1.0;
      dir[1] = 0.0;
      dir[2] = 0.0;
      VectorMA( start, ALTURT_SMOKENADE_DISTANCE, dir, end);

      trap_Trace( &tr, start, NULL, NULL, end, ent->s.number, MASK_SOLID);
      if (tr.fraction > 1.0) tr.fraction = 1.0;
      ent->s.frame |= ((int)(ALTURT_SMOKEMASK_VALUE*tr.fraction)) << ALTURT_SMOKEMASK_SRIGHT;

            // check FORWARD
      dir[0] = 0.0;
      dir[1] = 1.0;
      dir[2] = 0.0;
      VectorMA( start, ALTURT_SMOKENADE_DISTANCE, dir, end);

      trap_Trace( &tr, start, NULL, NULL, end, ent->s.number, MASK_SOLID);
      if (tr.fraction > 1.0) tr.fraction = 1.0;
      ent->s.frame |= ((int)(ALTURT_SMOKEMASK_VALUE*tr.fraction)) << ALTURT_SMOKEMASK_SFORWARD;

            // check BACKWARD
      dir[0] = 0.0;
      dir[1] = -1.0;
      dir[2] = 0.0;
      VectorMA( start, ALTURT_SMOKENADE_DISTANCE, dir, end);

      trap_Trace( &tr, start, NULL, NULL, end, ent->s.number, MASK_SOLID);
      if (tr.fraction > 1.0) tr.fraction = 1.0;
      ent->s.frame |= ((int)(ALTURT_SMOKEMASK_VALUE*tr.fraction)) << ALTURT_SMOKEMASK_SBACKWARD;

            // relink all assault fields
//      assault_link_all( qfalse );

    }

    ent->count--;
    ent->nextthink = level.time + ALTURT_SMOKENADETIME;
    ent->think = G_ExplodeMissile;
  }

    // the same random seed for all players
  ent->s.frame &= ~ALTURT_SMOKEMASK_RNDNUM;
  ent->s.frame |= ((int)(64*random())) & ALTURT_SMOKEMASK_RNDNUM ;

  trap_LinkEntity(ent);
}

/*
=================
fire_smoke
=================
*/
gentity_t *throw_smoke (gentity_t *self, vec3_t start, vec3_t dir) {
  gentity_t   *bolt;

  VectorNormalize (dir);

  bolt = G_Spawn();
  bolt->classname = "ut_weapon_grenade_smoke";
  bolt->nextthink = level.time + 2000;

  bolt->think = G_ExplodeMissile;
  bolt->s.eType = ET_MISSILE;
  bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
  bolt->s.weapon = WP_SMOKE;
  bolt->s.eFlags = EF_BOUNCE_HALF;
  bolt->r.ownerNum = self->s.number;
  bolt->timestamp = level.time;
  bolt->parent = self;
  bolt->methodOfDeath = MOD_GRENADE;
  bolt->splashMethodOfDeath = MOD_GRENADE_SPLASH;
  bolt->clipmask = MASK_SHOT;
  bolt->count = 100;
  bolt->target_ent = NULL;


  VectorScale( dir, 500 , bolt->s.pos.trDelta );

  bolt->s.pos.trType = TR_GRAVITY;
  bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;             // move a bit on the very first frame
  VectorCopy( start, bolt->s.pos.trBase );
  SnapVector( bolt->s.pos.trDelta );                  // save net bandwidth

  VectorCopy (start, bolt->r.currentOrigin);


if( self->client->sess.sessionTeam == TEAM_RED ){
      bolt->team ="red";
}
if( self->client->sess.sessionTeam == TEAM_BLUE ){
    bolt->team ="blue";
}


  return bolt;
}
/*
=================
fire_grenade
=================
*/
gentity_t *fire_grenade (gentity_t *self, vec3_t start, vec3_t dir, int mode) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "grenade";
	bolt->nextthink = level.time + 2500;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_HK69;
	bolt->s.eFlags = EF_BOUNCE_HALF;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 200; //100 blud tweaking damage
	bolt->splashDamage = 200; //100
	bolt->splashRadius = 200; //150
	bolt->methodOfDeath = MOD_GRENADE;
	bolt->splashMethodOfDeath = MOD_GRENADE_SPLASH;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_GRAVITY;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
       // G_Printf("mode is %i\n", mode);
        if(mode)
	VectorScale( dir, 1200, bolt->s.pos.trDelta ); //blud increase distance on GL (by increasing speed (was 700)
        else
                  VectorScale( dir, 700, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}



/*
=================
fire_grapple
=================
*/
//gentity_t *fire_grapple (gentity_t *self, vec3_t start, vec3_t dir) {
/*      gentity_t       *hook;

        VectorNormalize (dir);

        hook = G_Spawn();
        hook->classname = "hook";
        hook->nextthink = level.time + 10000;
        hook->think = Weapon_HookFree;
        hook->s.eType = ET_MISSILE;
        hook->r.svFlags = SVF_USE_CURRENT_ORIGIN;
        hook->s.weapon = WP_GRAPPLING_HOOK;
        hook->r.ownerNum = self->s.number;
        hook->methodOfDeath = MOD_GRAPPLE;
        hook->clipmask = MASK_SHOT;
        hook->parent = self;
        hook->target_ent = NULL;

        hook->s.pos.trType = TR_LINEAR;
        hook->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;         // move a bit on the very first frame
        hook->s.otherEntityNum = self->s.number; // use to match beam in client
        VectorCopy( start, hook->s.pos.trBase );
        VectorScale( dir, 800, hook->s.pos.trDelta );
        SnapVector( hook->s.pos.trDelta );                      // save net bandwidth
        VectorCopy (start, hook->r.currentOrigin);

        self->client->hook = hook;

        return hook;
  */
//} //blud: xamis commented out the contents of the function, now I am commenting out the function itself to stop a warning it throws in the compiler for not returning anything.


void G_Temp(gentity_t *self){
	self->nextthink = level.time + 100;
}

/*
=================
fire_knife
=================
*/
gentity_t *fire_knife (gentity_t *self, vec3_t start, vec3_t dir, int speed) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "knife";
	bolt->nextthink = level.time + 100;
	bolt->think = G_Temp;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_KNIFE;
	bolt->r.ownerNum = self->s.number;
//unlagged - projectile nudge
	// we'll need this for nudging projectiles later
	bolt->s.otherEntityNum = self->s.number;
//unlagged - projectile nudge
	bolt->parent = self;
	bolt->damage = 65 + rand()%30;
	bolt->splashDamage = 0;
	bolt->splashRadius = 0;
	bolt->methodOfDeath = MOD_KNIFE;
	bolt->splashMethodOfDeath = MOD_KNIFE;
	bolt->clipmask = MASK_SHOT;

	if(self->client)
		VectorCopy(self->client->ps.viewangles, bolt->s.angles2);

	bolt->s.pos.trType = TR_GRAVITY;//_LOW;
	bolt->s.pos.trTime = level.time + MISSILE_PRESTEP_TIME; //- MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	VectorScale( dir, speed, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth
	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}


/*
=================
fire_Sentry
=================
*/
gentity_t *fire_sentry( gentity_t *self, vec3_t start, vec3_t dir ) {
	gentity_t	*bolt;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->classname = "rocket";
	bolt->nextthink = level.time + 10000;
	bolt->think = G_ExplodeMissile;
	bolt->s.eType = ET_MISSILE;
	bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	bolt->s.weapon = WP_M4;
	bolt->r.ownerNum = self->s.number;
	bolt->parent = self;
	bolt->damage = 100;
	bolt->splashDamage = 100;
	bolt->splashRadius = 120;
	bolt->clipmask = MASK_SHOT;
	bolt->target_ent = NULL;

	bolt->s.pos.trType = TR_LINEAR;
	bolt->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	VectorCopy( start, bolt->s.pos.trBase );
	VectorScale( dir, 2000, bolt->s.pos.trDelta );
	SnapVector( bolt->s.pos.trDelta );			// save net bandwidth

	VectorCopy (start, bolt->r.currentOrigin);

	return bolt;
}	


