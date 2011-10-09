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
// g_weapon.c
// perform the server side effects of a weapon firing

#include "g_local.h"

static  float   s_quadFactor;
static  vec3_t  forward, right, up;
static  vec3_t  muzzle;

#define NUM_NAILSHOTS 15


void G_FixHitboxes( void ) {
    int i;
    gentity_t *ent;
    gclient_t *client;

    for (i = 0; i < level.maxclients; i++ ) {
        client = &level.clients[i];
        ent = &g_entities[ client - level.clients ];

        if (!client) continue;

        // we only want connected clients
        if ( client->pers.connected != CON_CONNECTED) continue;

        // we only want active players
        if ( client->sess.sessionTeam == TEAM_SPECTATOR ) continue;

        if ( ent->r.maxs[2] == PLAYER_STANDHEIGHT ) ent->r.maxs[2] = 40;
        if ( ent->r.maxs[2] == PLAYER_CROUCHHEIGHT ) ent->r.maxs[2] = 28.5;

    }
}

void G_RestoreHitboxes( void ) {
    int i;
    gentity_t *ent;
    gclient_t *client;

    for (i = 0; i < level.maxclients; i++ ) {
        client = &level.clients[i];
        ent = &g_entities[ client - level.clients ];

        if (!client) continue;

        // we only want connected clients
        if ( client->pers.connected != CON_CONNECTED) continue;

        // we only want active players
        if ( client->sess.sessionTeam == TEAM_SPECTATOR ) continue;

        if ( ent->r.maxs[2] == 40 ) ent->r.maxs[2] = PLAYER_STANDHEIGHT;
        if ( ent->r.maxs[2] == 28.5 ) ent->r.maxs[2] = PLAYER_CROUCHHEIGHT;

    }
}



/*
================
G_BounceProjectile
================
*/
void G_BounceProjectile( vec3_t start, vec3_t impact, vec3_t dir, vec3_t endout ) {
        vec3_t v, newv;
        float dot;

        VectorSubtract( impact, start, v );
        dot = DotProduct( v, dir );
        VectorMA( v, -2*dot, dir, newv );

        VectorNormalize(newv);
        VectorMA(impact, 8192, newv, endout);
}


/*
======================================================================

GAUNTLET

======================================================================
*/

void Weapon_Gauntlet( gentity_t *ent ) {

}

void weapon_knife_fire (gentity_t *ent) {
	gentity_t	*m;

	//forward[2] += 0.1f;

	VectorNormalize( forward );

	m = fire_knife (ent, muzzle, forward, 1500);//1600
//	m->damage *= s_quadFactor;
//	m->splashDamage *= s_quadFactor;

	VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );	// "real" physics
}

/*
===============
CheckGauntletAttack
===============
*/
qboolean CheckGauntletAttack( gentity_t *ent ) {
        trace_t         tr;
        vec3_t          end;
        gentity_t       *tent;
        gentity_t       *traceEnt;
        int                     damage;
        int		weaponstate = ent->client->ps.weaponstate;
        int			weapontime = ent->client->ps.weaponTime;
        // set aiming directions
        
        
                G_Printf("weapontime is %i\n",weapontime);
        
      if ( weaponstate != WEAPON_FIRING && !(ent->client->pers.cmd.buttons & BUTTON_ATTACK))
         return qfalse;
        
                if( weapontime ){

    
        AngleVectors (ent->client->ps.viewangles, forward, right, up);
        CalcMuzzlePoint ( ent, forward, right, up, muzzle );

        VectorMA (muzzle, 15, forward, end);

       G_FixHitboxes();
        trap_Trace (&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
       G_RestoreHitboxes();
        
        if ( tr.surfaceFlags & SURF_NOIMPACT ) {
                return qfalse;
        }

        traceEnt = &g_entities[ tr.entityNum ];

        // send blood impact
        if ( traceEnt->takedamage && traceEnt->client ) {
                tent = G_TempEntity( tr.endpos, EV_MISSILE_HIT );
                tent->s.otherEntityNum = traceEnt->s.number;
                tent->s.eventParm = DirToByte( tr.plane.normal );
                tent->s.weapon = ent->s.weapon;
        }

        if ( !traceEnt->takedamage) {
                return qfalse;
        }
                s_quadFactor = 1;


        damage = 50 * s_quadFactor;
        G_Damage( traceEnt, ent, ent, forward, tr.endpos,
                damage, 0, MOD_GAUNTLET );

        return qtrue;
                }else return qfalse;
}

void CheckBootAttack( gentity_t *ent ) {
        trace_t         tr;
        vec3_t          end;
//        gentity_t       *tent;
        gentity_t       *traceEnt;
        int                     damage;
        int		weaponstate = ent->client->ps.weaponstate;


        
        
      if ( weaponstate == WEAPON_FIRING || (ent->client->pers.cmd.buttons & BUTTON_ATTACK))
         return;
        

       if( ent->client->ps.pm_flags & PMF_ONGROUND){
           return;
       }
    
        if(ent->client->ps.weapon != WP_KNIFE && !BG_Sidearm(ent->client->ps.weapon ) ){
            return;
        }
                
        
        if( ent->client->ps.speed < 300 ){
            return;
        }
        
        AngleVectors (ent->client->ps.viewangles, forward, right, up);
        CalcMuzzlePoint ( ent, forward, right, up, muzzle );

        VectorMA (muzzle, 15, forward, end);

       G_FixHitboxes();
        trap_Trace (&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
       G_RestoreHitboxes();
        
        if ( tr.surfaceFlags & SURF_NOIMPACT ) {
                return;
        }

        traceEnt = &g_entities[ tr.entityNum ];

        // send blood impact
  //      if ( traceEnt->takedamage && traceEnt->client ) {
 //               tent = G_TempEntity( tr.endpos, EV_MISSILE_HIT );
 //               tent->s.otherEntityNum = traceEnt->s.number;
  //              tent->s.eventParm = DirToByte( tr.plane.normal );
  //              tent->s.weapon = ent->s.weapon;
    //    }

        if ( !traceEnt->takedamage) {
                return;
        }
        
        
                s_quadFactor = 1;


        damage = 3 * s_quadFactor;
 //       G_Damage( traceEnt, ent, ent, forward, tr.endpos,
        //        damage, 0, MOD_BOOT );

}

/*
===============
CheckMed
 * 
 *Bandage target.
===============
*/
void CheckMed( gentity_t *ent ) {
        trace_t         tr;
        vec3_t          end;
        gentity_t       *traceEnt;

        // set aiming directions
        AngleVectors (ent->client->ps.viewangles, forward, right, up);
	


        if ( !(ent->client->buttons & BUTTON_HEAL)){
            return;
        }
       if ( ent->client->ps.weaponstate == WEAPON_START_BANDAGING_OTHER || 
               ent->client->ps.weaponstate == WEAPON_DOWN_BANDAGING_OTHER){
            return;
       }
        
        CalcMuzzlePoint ( ent, forward, right, up, muzzle );

        VectorMA (muzzle, 32, forward, end);
       G_FixHitboxes();
        trap_Trace (&tr, muzzle, NULL, NULL, end, ent->s.number, MASK_SHOT);
        G_RestoreHitboxes();
        if ( tr.surfaceFlags & SURF_NOIMPACT ) {
                return;
        }

        traceEnt = &g_entities[ tr.entityNum ];

        if ( !traceEnt->takedamage) {
                return;
        }
        
        if ( traceEnt->client->amtHealed >=50){
            return;
        }

        if ( traceEnt->takedamage && traceEnt->client ) {
            if ( traceEnt->health <100 &&
                    traceEnt->health > 0 &&
                    traceEnt->client->ps.pm_type != PM_DEAD ){
                if(ent->client->ps.powerups[PW_MEDKIT] ){
                        traceEnt->health+=8;
                }else{
                        traceEnt->health+=5;
                }
            }   
            traceEnt->client->ps.pm_flags &=  ~ PMF_BLEEDING;
            ent->client->ps.weaponstate = WEAPON_START_BANDAGING_OTHER;
            traceEnt->client->ps.stats[STAT_DMG_LOC] = 0;
        }



}


/*
======================================================================

MACHINEGUN

======================================================================
*/

/*
======================
SnapVectorTowards

Round a vector to integers for more efficient network
transmission, but make sure that it rounds towards a given point
rather than blindly truncating.  This prevents it from truncating
into a wall.
======================
*/
void SnapVectorTowards( vec3_t v, vec3_t to ) {
        int             i;

        for ( i = 0 ; i < 3 ; i++ ) {
                if ( to[i] <= v[i] ) {
                        v[i] = (int)v[i];
                } else {
                        v[i] = (int)v[i] + 1;
                }
        }
}

#ifdef MISSIONPACK
#define CHAINGUN_SPREAD         600
#endif
#define M4_SPREAD       15
#define LR300_SPREAD       15
#define BERETTA_SPREAD       10
#define AK103_SPREAD       20
#define G36_SPREAD       20
#define PSG1_SPREAD       0
#define SR8_SPREAD       0
#define NEGEV_SPREAD       20
#define UMP45_SPREAD       20
#define MP5K_SPREAD       20
#define MACHINEGUN_SPREAD       20
#define DEAGLE_SPREAD           10


#define MACHINEGUN_DAMAGE       7
#define SR8_DAMAGE       100
#define NEGEV_DAMAGE      15
#define M4_DAMAGE       25 //12
#define AK103_DAMAGE    30 //16
#define LR300_DAMAGE   25 //25
#define BERETTA_DAMAGE   20 //25
#define G36_DAMAGE   22 //25
#define DEAGLE_DAMAGE   40 //25
#define UMP45_DAMAGE   40 //25
#define MP5K_DAMAGE   22 //25




void Apply_Weapon_Kick ( gentity_t *ent, int weapon )
{
    double   kickfact = 0.0;

    double   kickangle = 0.0;


    kickfact = bg_weaponlist[0].numClips[ent->client->ps.clientNum]/6 ;

    if (kickfact > 2.5 )
        kickfact =2.5;

    switch (ent->s.weapon) {
    case WP_BERETTA: kickangle = .2; break;
    case WP_DEAGLE: kickangle = .7; break;

    case WP_AK103: kickangle = .4; break;
    case WP_M4: kickangle = .4; break;
    case WP_LR300: kickangle = .4; break;
    case WP_G36: kickangle = .4; break;


    case WP_SPAS: kickangle = 2; break;
    case WP_MP5K: kickangle = .3; break;
    case WP_UMP45: kickangle = .4; break;

    case WP_PSG1: kickangle = .2; break;
    case WP_SR8: kickangle = 1; break;




    default: kickangle = 0; break;
    }

 
    kickangle += kickfact;
    ent->client->ps.delta_angles[PITCH] -= ANGLE2SHORT( kickangle/4 );
    
    ent->client->ps.delta_angles[PITCH] += ANGLE2SHORT( kickangle/10 );

}




/*
======================================================================

Bullet_Fire

======================================================================
*/

void Bullet_Fire (gentity_t *ent, float spread, int damage, int MOD  ) {
        trace_t         tr;
        vec3_t          end;
        float           r;
        float           u;
        gentity_t       *tent;//,*tent2;
        gentity_t       *traceEnt;
        int                     j, passent, spreadAdjustment;
        gentity_t       *unlinkedEntity[3];
        int                     count =0, unlinked =0;

	//No spread in spam mode!
        if (ent->s.weapon == WP_UMP45 && bg_weaponlist[ ent->s.weapon ].weapMode[ent->client->ps.clientNum] == 0 ){
        spread = 0;

	//only apply weapon kick on the last round of spam mode
        if(bg_weaponlist[0].numClips[ent->client->ps.clientNum] == 3)
            Apply_Weapon_Kick( ent, ent->s.weapon );
        }  else {
        spread += BG_CalcSpread(ent->client->ps) + ((bg_weaponlist[0].numClips[ent->client->ps.clientNum]*10));
         Apply_Weapon_Kick( ent, ent->s.weapon );
        }
        

     //    damage *= s_quadFactor;       
              // G_Printf ("spread = %f\n xyspeed = %f", spread, BG_CalcSpread(ent->client->ps) );
        
      if( ent->client->ps.powerups[ PW_LASERSIGHT ] ){
        spreadAdjustment = 8;
      }else if( ent->client->ps.powerups[ PW_SILENCER ] ){
        spreadAdjustment = 12;
        }else
        spreadAdjustment = 16;
      
      //  G_Printf( "Spread round count is %i\n", bg_weaponlist[0].numClips[ent->client->ps.clientNum] );
        r = random() * M_PI * 2.0f;
        u = sin(r) * crandom() * spread * spreadAdjustment;
        r = cos(r) * crandom() * spread * spreadAdjustment*2;
        VectorMA (muzzle, 8192*16, forward, end);
        VectorMA (end, r, right, end);
        VectorMA (end, u, up, end);
        end[PITCH] += bg_weaponlist[0].numClips[ent->client->ps.clientNum];

        VectorCopy( ent->client->ps.origin, muzzle );
        muzzle[2] += ent->client->ps.viewheight;
  
        passent = ent->s.number;
	//start a loop through the trace section of code to deal with breakable entities             
        do {  
            
                G_FixHitboxes();
                trap_Trace (&tr, muzzle, NULL, NULL, end, passent, MASK_SHOT);
                G_RestoreHitboxes();
                traceEnt = &g_entities[ tr.entityNum ];
                
	//check to see if the trace encounterd a "func_breakable" do damage to it
       if  ( !strcmp(traceEnt->classname, "func_breakable") ){
           if(!(count)){ //is this the first time through?
                                G_Damage( traceEnt, ent, ent, forward, tr.endpos,
                                        damage, 0, MOD_MACHINEGUN);
		//	if(traceEnt->health){
                //        tent2 = G_TempEntity( tr.endpos, EV_BULLET_HIT_GLASS );
                 //       tent2->s.eventParm = DirToByte( tr.plane.normal );
	//		tent2->s.otherEntityNum = ent->s.number;
	//		}
        trap_UnlinkEntity( traceEnt ); //unlink entity to on the next pass through the loop our trace will continue past it.
        unlinkedEntity[unlinked] = traceEnt; //so we can relink out func_breakable entity
        unlinked++;
        count=1; //cause another pass through the loop, because we encountered a func_breakable entity
          }
        }else            
         count =0; //dont make another pass, because we didn't encounter a func_breakable
        } while ( count );
                
	//relink any func_breakable entities
        for ( j= 0 ; j < unlinked ; j++ ) {
                trap_LinkEntity( unlinkedEntity[j] );
        }
        
        if ( tr.surfaceFlags & SURF_NOIMPACT ) {
                        return;
                }




                // snap the endpos to integers, but nudged towards the line
                SnapVectorTowards( tr.endpos, muzzle );

                // send bullet impact
                if ( traceEnt->takedamage && traceEnt->client ) {
                        tent = G_TempEntity( tr.endpos, EV_BULLET_HIT_FLESH );
                        tent->s.eventParm = traceEnt->s.number;
                        if( LogAccuracyHit( traceEnt, ent ) ) {
                                ent->client->accuracy_hits++;
                        }
                } else {
                        tent = G_TempEntity( tr.endpos, EV_BULLET_HIT_WALL );
                        tent->s.eventParm = DirToByte( tr.plane.normal );
                }
                tent->s.otherEntityNum = ent->s.number;

                if ( traceEnt->takedamage) {
                                G_Damage( traceEnt, ent, ent, forward, tr.endpos,
                                        damage, 0, MOD);
                }
                //break;
       // }
}




/*
======================================================================

SHOTGUN

======================================================================
*/

// DEFAULT_SHOTGUN_SPREAD and DEFAULT_SHOTGUN_COUNT     are in bg_public.h, because
// client predicts same spreads
#define DEFAULT_SHOTGUN_DAMAGE  20

qboolean ShotgunPellet( vec3_t start, vec3_t end, gentity_t *ent ) {
        trace_t         tr;
        int                     j, damage, i, passent;
        gentity_t       *traceEnt;//, *tent2;
#ifdef MISSIONPACK
        vec3_t          impactpoint, bouncedir;
#endif
        vec3_t          tr_start, tr_end;
        gentity_t       *unlinkedEntity[3];
        int                     count =0, unlinked =0;
        passent = ent->s.number;
        VectorCopy( start, tr_start );
        VectorCopy( end, tr_end );


        damage = DEFAULT_SHOTGUN_DAMAGE * s_quadFactor;
        for (i = 0; i < 10; i++) {

 do {
                       G_FixHitboxes();
                trap_Trace (&tr, tr_start, NULL, NULL, tr_end, passent, MASK_SHOT);
                G_RestoreHitboxes();
                
                traceEnt = &g_entities[ tr.entityNum ];
     if  ( !strcmp(traceEnt->classname, "func_breakable") ){
           if(!(count)){ //is this the first time through?
                                G_Damage( traceEnt, ent, ent, forward, tr.endpos,
                                        damage, 0, MOD_MACHINEGUN);
                  //      if(traceEnt->health){
                  //      tent2 = G_TempEntity( tr.endpos, EV_BULLET_HIT_GLASS );
                 //       tent2->s.eventParm = DirToByte( tr.plane.normal );
                //        tent2->s.otherEntityNum = ent->s.number;
                //        }
        trap_UnlinkEntity( traceEnt ); //unlink entity to on the next pass through the loop our trace will continue past it.
        unlinkedEntity[unlinked] = traceEnt; //so we can relink out func_breakable entity
        unlinked++;
        count=1; //cause another pass through the loop, because we encountered a func_breakable entity
          }
        }else
         count =0; //dont make another pass, because we didn't encounter a func_breakable
        } while ( count );

        //relink any func_breakable entities
        for ( j= 0 ; j < unlinked ; j++ ) {
                trap_LinkEntity( unlinkedEntity[j] );
        }

                // send bullet impact
                if (  tr.surfaceFlags & SURF_NOIMPACT ) {
                        return qfalse;
                }

                if ( traceEnt->takedamage) {
#ifdef MISSIONPACK
                        if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
                                if (G_InvulnerabilityEffect( traceEnt, forward, tr.endpos, impactpoint, bouncedir )) {
                                        G_BounceProjectile( tr_start, impactpoint, bouncedir, tr_end );
                                        VectorCopy( impactpoint, tr_start );
                                        // the player can hit him/herself with the bounced rail
                                        passent = ENTITYNUM_NONE;
                                }
                                else {
                                        VectorCopy( tr.endpos, tr_start );
                                        passent = traceEnt->s.number;
                                }
                                continue;
                        }
                        else {
                                G_Damage( traceEnt, ent, ent, forward, tr.endpos,
                                        damage, 0, MOD_SHOTGUN);
                                if( LogAccuracyHit( traceEnt, ent ) ) {
                                        return qtrue;
                                }
                        }
#else
                        G_Damage( traceEnt, ent, ent, forward, tr.endpos,       damage, 0, MOD_SHOTGUN);
                                if( LogAccuracyHit( traceEnt, ent ) ) {
                                        return qtrue;
                                }
#endif
                }
                return qfalse;
        }
        return qfalse;
}

// this should match CG_ShotgunPattern
void ShotgunPattern( vec3_t origin, vec3_t origin2, int seed, gentity_t *ent ) {
        int                     i;
        float           r, u;
        vec3_t          end;
        vec3_t          forward, right, up;
        int                     oldScore;
        qboolean        hitClient = qfalse;

        // derive the right and up vectors from the forward vector, because
        // the client won't have any other information
        VectorNormalize2( origin2, forward );
        PerpendicularVector( right, forward );
        CrossProduct( forward, right, up );

        oldScore = ent->client->ps.persistant[PERS_SCORE];

        // generate the "random" spread pattern
        for ( i = 0 ; i < DEFAULT_SHOTGUN_COUNT ; i++ ) {
                r = Q_crandom( &seed ) * DEFAULT_SHOTGUN_SPREAD * 16;
                u = Q_crandom( &seed ) * DEFAULT_SHOTGUN_SPREAD * 16;
                VectorMA( origin, 8192 * 16, forward, end);
                VectorMA (end, r, right, end);
                VectorMA (end, u, up, end);
                if( ShotgunPellet( origin, end, ent ) && !hitClient ) {
                        hitClient = qtrue;
                        ent->client->accuracy_hits++;
                }
        }
}


void weapon_supershotgun_fire (gentity_t *ent) {
        gentity_t               *tent;

        // send shotgun blast
        tent = G_TempEntity( muzzle, EV_SHOTGUN );
        VectorScale( forward, 4096, tent->s.origin2 );
        SnapVector( tent->s.origin2 );
        tent->s.eventParm = rand() & 255;               // seed for spread pattern
        tent->s.otherEntityNum = ent->s.number;

        ShotgunPattern( tent->s.pos.trBase, tent->s.origin2, tent->s.eventParm, ent );
}


/*
======================================================================

GRENADES

======================================================================
*/

void weapon_grenadelauncher_fire (gentity_t *ent, int mode ) {
        gentity_t       *m;

        // extra vertical velocity
        forward[2] += 0.2f;
        VectorNormalize( forward );

        m = fire_grenade (ent, muzzle, forward, mode);
        m->damage *= s_quadFactor;
        m->splashDamage *= s_quadFactor;

        VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );      // "real" physics
}

//Xamis
void weapon_smoke_throw (gentity_t *ent) {
  gentity_t       *m;
  vec3_t start;

  VectorCopy(ent->s.pos.trBase, start);

  start[2] += ent->client->ps.viewheight+8.0f;

  forward[2] += 0.1f;

  VectorNormalize( forward );

  m = throw_smoke(ent, start, forward);
        //m->damage *= s_quadFactor;
        //m->splashDamage *= s_quadFactor;
//      VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );      // "real" physics

}


void weapon_grenade_throw (gentity_t *ent) {
        gentity_t       *m;
        vec3_t start;

        VectorCopy(ent->s.pos.trBase, start);

        start[2] += ent->client->ps.viewheight+8.0f;

        forward[2] += 0.1f;

        VectorNormalize( forward );

        m = throw_grenade (ent, start, forward);
        //m->damage *= s_quadFactor;
        //m->splashDamage *= s_quadFactor;
//      VectorAdd( m->s.pos.trDelta, ent->client->ps.velocity, m->s.pos.trDelta );      // "real" physics

}


void weapon_grenade_arm( gentity_t *self ){

  gentity_t     *bolt;

  bolt = G_Spawn();
  bolt->classname = "ut_weapon_grenade_he";
  bolt->nextthink = level.time + 3000;
  bolt->think = G_ExplodeMissile;
  bolt->s.eType = ET_MISSILE;
  bolt->r.svFlags = SVF_USE_CURRENT_ORIGIN;
  bolt->s.weapon = WP_HE;
  bolt->s.eFlags = EF_BOUNCE_HALF;
  bolt->r.ownerNum = self->s.number;
  bolt->timestamp = level.time;
  bolt->parent = self;
  bolt->damage = 100;
  bolt->splashDamage = 100;
  bolt->splashRadius = 150;
  bolt->methodOfDeath = MOD_GRENADE;
  bolt->splashMethodOfDeath = MOD_GRENADE_SPLASH;
  bolt->clipmask = MASK_SHOT;
  bolt->target_ent = NULL;
}
/*
=================
weapon_railgun_fire
=================
*/
#define MAX_RAIL_HITS   4
void weapon_railgun_fire (gentity_t *ent) {
        vec3_t          end;
#ifdef MISSIONPACK
        vec3_t impactpoint, bouncedir;
#endif
        trace_t         trace;
        gentity_t       *tent;
        gentity_t       *traceEnt;
        int                     damage;
        int                     i;
        int                     hits;
        int                     unlinked;
        int                     passent;
        gentity_t       *unlinkedEntities[MAX_RAIL_HITS];

        damage = 100 * s_quadFactor;

        VectorMA (muzzle, 8192, forward, end);

        // trace only against the solids, so the railgun will go through people
        unlinked = 0;
        hits = 0;
        passent = ent->s.number;
        do {
                trap_Trace (&trace, muzzle, NULL, NULL, end, passent, MASK_SHOT );
                if ( trace.entityNum >= ENTITYNUM_MAX_NORMAL ) {
                        break;
                }
                traceEnt = &g_entities[ trace.entityNum ];
                if ( traceEnt->takedamage ) {
#ifdef MISSIONPACK
                        if ( traceEnt->client && traceEnt->client->invulnerabilityTime > level.time ) {
                                if ( G_InvulnerabilityEffect( traceEnt, forward, trace.endpos, impactpoint, bouncedir ) ) {
                                        G_BounceProjectile( muzzle, impactpoint, bouncedir, end );
                                        // snap the endpos to integers to save net bandwidth, but nudged towards the line
                                        SnapVectorTowards( trace.endpos, muzzle );
                                        // send railgun beam effect
                                        tent = G_TempEntity( trace.endpos, EV_RAILTRAIL );
                                        // set player number for custom colors on the railtrail
                                        tent->s.clientNum = ent->s.clientNum;
                                        VectorCopy( muzzle, tent->s.origin2 );
                                        // move origin a bit to come closer to the drawn gun muzzle
                                        VectorMA( tent->s.origin2, 4, right, tent->s.origin2 );
                                        VectorMA( tent->s.origin2, -1, up, tent->s.origin2 );
                                        tent->s.eventParm = 255;        // don't make the explosion at the end
                                        //
                                        VectorCopy( impactpoint, muzzle );
                                        // the player can hit him/herself with the bounced rail
                                        passent = ENTITYNUM_NONE;
                                }
                        }
                        else {
                                if( LogAccuracyHit( traceEnt, ent ) ) {
                                        hits++;
                                }
                                G_Damage (traceEnt, ent, ent, forward, trace.endpos, damage, 0, MOD_RAILGUN);
                        }
#else
                                if( LogAccuracyHit( traceEnt, ent ) ) {
                                        hits++;
                                }
                                G_Damage (traceEnt, ent, ent, forward, trace.endpos, damage, 0, MOD_RAILGUN);
#endif
                }
                if ( trace.contents & CONTENTS_SOLID ) {
                        break;          // we hit something solid enough to stop the beam
                }
                // unlink this entity, so the next trace will go past it
                trap_UnlinkEntity( traceEnt );
                unlinkedEntities[unlinked] = traceEnt;
                unlinked++;
        } while ( unlinked < MAX_RAIL_HITS );

        // link back in any entities we unlinked
        for ( i = 0 ; i < unlinked ; i++ ) {
                trap_LinkEntity( unlinkedEntities[i] );
        }

        // the final trace endpos will be the terminal point of the rail trail

        // snap the endpos to integers to save net bandwidth, but nudged towards the line
        SnapVectorTowards( trace.endpos, muzzle );

        // send railgun beam effect
        tent = G_TempEntity( trace.endpos, EV_RAILTRAIL );

        // set player number for custom colors on the railtrail
        tent->s.clientNum = ent->s.clientNum;

        VectorCopy( muzzle, tent->s.origin2 );
        // move origin a bit to come closer to the drawn gun muzzle
        VectorMA( tent->s.origin2, 4, right, tent->s.origin2 );
        VectorMA( tent->s.origin2, -1, up, tent->s.origin2 );

        // no explosion at end if SURF_NOIMPACT, but still make the trail
        if ( trace.surfaceFlags & SURF_NOIMPACT ) {
                tent->s.eventParm = 255;        // don't make the explosion at the end
        } else {
                tent->s.eventParm = DirToByte( trace.plane.normal );
        }
        tent->s.clientNum = ent->s.clientNum;

        // give the shooter a reward sound if they have made two railgun hits in a row
        if ( hits == 0 ) {
                // complete miss
                ent->client->accurateCount = 0;
        } else {
                // check for "impressive" reward sound
                ent->client->accurateCount += hits;
                if ( ent->client->accurateCount >= 2 ) {
                        ent->client->accurateCount -= 2;
                        ent->client->ps.persistant[PERS_IMPRESSIVE_COUNT]++;
                        // add the sprite over the player's head
                        ent->client->ps.eFlags &= ~( EF_AWARD_EXCELLENT | EF_AWARD_GAUNTLET | EF_AWARD_ASSIST | EF_AWARD_DEFEND | EF_AWARD_CAP );
                       // ent->client->ps.eFlags |= EF_AWARD_IMPRESSIVE;
                        ent->client->rewardTime = level.time + REWARD_SPRITE_TIME;
                }
                ent->client->accuracy_hits++;
        }

}


/*
======================================================================

GRAPPLING HOOK

======================================================================
*/

void Weapon_GrapplingHook_Fire (gentity_t *ent)
{
        if (!ent->client->fireHeld && !ent->client->hook)
                //fire_grapple (ent, muzzle, forward);
                //blud commenting out call to fire_grapple() because
                //fire_grapple() function is now commented out because
                //it was throwing a warning I didn't want to see.



        ent->client->fireHeld = qtrue;
}

void Weapon_HookFree (gentity_t *ent)
{
        ent->parent->client->hook = NULL;
//      ent->parent->client->ps.pm_flags &= ~PMF_GRAPPLE_PULL;
        G_FreeEntity( ent );
}

void Weapon_HookThink (gentity_t *ent)
{
        if (ent->enemy) {
                vec3_t v, oldorigin;

                VectorCopy(ent->r.currentOrigin, oldorigin);
                v[0] = ent->enemy->r.currentOrigin[0] + (ent->enemy->r.mins[0] + ent->enemy->r.maxs[0]) * 0.5;
                v[1] = ent->enemy->r.currentOrigin[1] + (ent->enemy->r.mins[1] + ent->enemy->r.maxs[1]) * 0.5;
                v[2] = ent->enemy->r.currentOrigin[2] + (ent->enemy->r.mins[2] + ent->enemy->r.maxs[2]) * 0.5;
                SnapVectorTowards( v, oldorigin );      // save net bandwidth

                G_SetOrigin( ent, v );
        }

        VectorCopy( ent->r.currentOrigin, ent->parent->client->ps.grapplePoint);
}

/*
------------------------------------------------------------------------------------------------------------------------

Weapon_KnifeSlash

------------------------------------------------------------------------------------------------------------------------
*/

void Weapon_KnifeSlash( gentity_t *ent ) {
        trace_t         tr;
        vec3_t          end;

        gentity_t       *traceEnt, *tent;
        int                     damage, i, passent;

        damage = 25 * s_quadFactor;

        passent = ent->s.number;
        for (i = 0; i < 10; i++) {
                VectorMA( muzzle, 40, forward, end );

                trap_Trace( &tr, muzzle, NULL, NULL, end, passent, MASK_SHOT );

                if ( tr.entityNum == ENTITYNUM_NONE ) {
                        return;
                }

                traceEnt = &g_entities[ tr.entityNum ];

                if ( traceEnt->takedamage) {
                                G_Damage( traceEnt, ent, ent, forward, tr.endpos,
                                        damage, 0, MOD_KNIFE);
                }

                if ( traceEnt->takedamage && traceEnt->client ) {
                        tent = G_TempEntity( tr.endpos, EV_MISSILE_HIT );
                        tent->s.otherEntityNum = traceEnt->s.number;
                        tent->s.eventParm = DirToByte( tr.plane.normal );
                        tent->s.weapon = ent->s.weapon;
                        if( LogAccuracyHit( traceEnt, ent ) ) {
                                ent->client->accuracy_hits++;
                        }
                }// else if ( !( tr.surfaceFlags & SURF_NOIMPACT ) ) {
                   //     tent = G_TempEntity( tr.endpos, EV_MISSILE_MISS );
                  //      tent->s.eventParm = DirToByte( tr.plane.normal );
              //  }

                break;
        }
}

//======================================================================


/*
===============
LogAccuracyHit
===============
*/
qboolean LogAccuracyHit( gentity_t *target, gentity_t *attacker ) {
        if( !target->takedamage ) {
                return qfalse;
        }

        if ( target == attacker ) {
                return qfalse;
        }

        if( !target->client ) {
                return qfalse;
        }

        if( !attacker->client ) {
                return qfalse;
        }

        if( target->client->ps.stats[STAT_HEALTH] <= 0 ) {
                return qfalse;
        }

        if ( OnSameTeam( target, attacker ) ) {
                return qfalse;
        }

        return qtrue;
}


/*
===============
CalcMuzzlePoint

set muzzle location relative to pivoting eye
===============
*/
void CalcMuzzlePoint ( gentity_t *ent, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint ) {
        VectorCopy( ent->s.pos.trBase, muzzlePoint );
        muzzlePoint[2] += ent->client->ps.viewheight;
        VectorMA( muzzlePoint, 14, forward, muzzlePoint );
        // snap to integer coordinates for more efficient network bandwidth usage
        SnapVector( muzzlePoint );
}

/*
===============
CalcMuzzlePointOrigin

set muzzle location relative to pivoting eye
===============
*/
void CalcMuzzlePointOrigin ( gentity_t *ent, vec3_t origin, vec3_t forward, vec3_t right, vec3_t up, vec3_t muzzlePoint ) {
        VectorCopy( ent->s.pos.trBase, muzzlePoint );
        muzzlePoint[2] += ent->client->ps.viewheight;
        VectorMA( muzzlePoint, 14, forward, muzzlePoint );
        // snap to integer coordinates for more efficient network bandwidth usage
        SnapVector( muzzlePoint );
}

int getDefaultItem(int slot)
{
	int defaultItem;

	switch (slot)
	{
		case GEAR_SLOT_SIDEARM:
			defaultItem = WP_DEAGLE;
			break;
		case GEAR_SLOT_PRIMARY:
			defaultItem = WP_LR300;
			break;
		case GEAR_SLOT_SECONDARY:
			defaultItem = WP_NONE;
			break;
		case GEAR_SLOT_GRENADE:
			defaultItem = WP_NONE;
			break;
		case GEAR_SLOT_ITEM_1:
			defaultItem = PW_VEST;
			break;
		case GEAR_SLOT_ITEM_2:
			defaultItem = WP_NONE;
			break;
		case GEAR_SLOT_ITEM_3:
			defaultItem = WP_NONE;
			break;
		default:
			defaultItem = WP_NONE;
			break;
	}

	return defaultItem;
}

qboolean isGoodItem(int itemNum, char primaryWeapon, char secondaryWeapon, char grenade, int slot)
{
	qboolean returnValue;

	switch (slot)
	{
		case GEAR_SLOT_SIDEARM:
			returnValue = isSidearm(itemNum);
			break;
		case GEAR_SLOT_PRIMARY:
			returnValue = isPrimary(itemNum);
			break;
		case GEAR_SLOT_SECONDARY:
			returnValue = isSecondary(itemNum) && primaryWeapon != GEAR_NEGEV && GearToWPPW(primaryWeapon) != itemNum;
			break;
		case GEAR_SLOT_GRENADE:
			returnValue = isGrenade(itemNum);
			break;
		case GEAR_SLOT_ITEM_1:
			//it just has to be any valid item
			returnValue = isItem(itemNum);
			break;
		case GEAR_SLOT_ITEM_2:
			//has to be a valid item and they cannot have more than one of secondary and grenade
			returnValue = isItem(itemNum) && (!isSecondary(GearToWPPW(secondaryWeapon)) || !isSecondary(GearToWPPW(grenade)));
			break;
		case GEAR_SLOT_ITEM_3:
			//has to be a valid item and they cannot have any secondary or grenade
			returnValue = isItem(itemNum) && !isSecondary(GearToWPPW(secondaryWeapon)) && !isSecondary(GearToWPPW(grenade));
			break;
		default:
			returnValue = qfalse;
			break;
	}

	return returnValue;
}


//blud: Converts gear cvar slot char values to WP or PW numbers
int GearToWPPW(char itemChar)
{
	int WPPWnum;

	switch (itemChar)
	{
		case GEAR_NONE:
			WPPWnum = WP_NONE;
			break;
		case GEAR_BERETTA:
			WPPWnum = WP_BERETTA;
			break;
		case GEAR_DEAGLE:
			WPPWnum = WP_DEAGLE;
			break;
		case GEAR_SPAS12:
			WPPWnum = WP_SPAS;
			break;
		case GEAR_MP5K:
			WPPWnum = WP_MP5K;
			break;
		case GEAR_UMP45:
			WPPWnum = WP_UMP45;
			break;
		case GEAR_HK69:
			WPPWnum = WP_HK69;
			break;
		case GEAR_LR:
			WPPWnum = WP_LR300;
			break;
		case GEAR_G36:
			WPPWnum = WP_G36;
			break;
		case GEAR_PSG1:
			WPPWnum = WP_PSG1;
			break;
		case GEAR_GRENADE_HE:
			WPPWnum = WP_HE;
			break;
		case GEAR_GRENADE_SMOKE:
			WPPWnum = WP_SMOKE;
			break;
		case GEAR_VEST:
			WPPWnum = PW_VEST;
			break;
		case GEAR_NVG:
			WPPWnum = PW_NVG;
			break;
		case GEAR_MEDKIT:
			WPPWnum = PW_MEDKIT;
			break;
		case GEAR_SILENCER:
			WPPWnum = PW_SILENCER;
			break;
		case GEAR_LASER:
			WPPWnum = PW_LASERSIGHT;
			break;
		case GEAR_HELMET:
			WPPWnum = PW_HELMET;
			break;
		case GEAR_AMMO:
			WPPWnum = PW_AMMO;
			break;
		case GEAR_SR8:
			WPPWnum = WP_SR8;
			break;
		case GEAR_AK103:
			WPPWnum = WP_AK103;
			break;
		case GEAR_NEGEV:
			WPPWnum = WP_NEGEV;
			break;
		case GEAR_M4:
			WPPWnum = WP_M4;
			break;
		default:
			//should never happen. Just going to set it to none
			WPPWnum = WP_NONE;
			break;
	}

	return WPPWnum;

}

/*
==================
ClipCount

returns # of clips for weapon w
(actually magazines not clips :p )
==================
*/
int ClipCount( int w ) {
	int numClips;

	//I think we should move all the properties for the weapons to constants in one place?
	//(and then use those constants here instead of hardcoded numbers)

	switch (w)
	{
		case WP_NONE:
                        numClips = 0;
                        break;
		case WP_KNIFE:
			numClips = 0;
			break;
		case WP_BERETTA:
		case WP_DEAGLE:
			numClips = 3;
			break;
		case WP_MP5K:
		case WP_UMP45:
			numClips = 3;
			break;
		case WP_SPAS:
			numClips = 16;
			break;
		case WP_M4:
		case WP_LR300:
		case WP_G36:
		case WP_AK103:
			numClips = 3;
			break;
		case WP_PSG1:
			numClips = 3;
			break;
		case WP_SR8:
			numClips = 3;
			break;
		case WP_NEGEV:
			numClips = 1;
			break;
		case WP_HK69:
			numClips = 5;
			break;
		case WP_HE:
		case WP_SMOKE:
			numClips = 2;
			break;
		default:
			numClips = 1;
			break;
	}

	return numClips;
}


/*
==================
RoundCount

returns # of rounds per clip for weapon w
==================
*/
int RoundCount( int w )
{
	int numRounds;

	switch ( w )
	{
		case WP_NONE:
                        numRounds = 0;
                        break;
		case WP_KNIFE:
			numRounds = 5;
			break;
		case WP_BERETTA:
			numRounds = 15;
			break;
		case WP_DEAGLE:
			numRounds = 7;
			break;
		case WP_MP5K:
		case WP_UMP45:
			numRounds = 30;
			break;
		case WP_SPAS:
			numRounds = 8;
			break;
		case WP_M4:
		case WP_LR300:
		case WP_G36:
		case WP_AK103:
			numRounds = 30;
			break;
		case WP_PSG1:
			numRounds = 10;
			break;
		case WP_SR8:
			numRounds = 5;
			break;
		case WP_NEGEV:
			numRounds = 80;
			break;
		case WP_HK69:
			numRounds = 1;
			break;
		case WP_HE:
		case WP_SMOKE:
			numRounds = 0;
			break;
		default:
			numRounds = 2;
			break;
	}

	return numRounds;
}




qboolean G_WeaponHasModes ( int weaponNumber){

switch (weaponNumber){
	case WP_KNIFE:
	case WP_UMP45:
	case WP_MP5K:
	case WP_M4:
	case WP_LR300:
	case WP_G36:
	case WP_HK69:
	case WP_AK103:
	return qtrue;
	default:
	return qfalse;
	}
}

void Set_Mode(gentity_t *ent){
  


  char                    weapmodes_saves[WP_NUM_WEAPONS];//xamis
  
  
  

Q_strncpyz( weapmodes_saves, ent->client->weaponModeChar , sizeof( weapmodes_saves ) );
 //weapmodes_saves = va("%016d", ent->client->ps.powerups[PW_WEAPMODES]) ;

   switch (weapmodes_saves[ent->client->ps.weapon] ){
    case '0':
  bg_weaponlist[ ent->client->ps.weapon ].weapMode[ent->client->ps.clientNum]
      = ent->client->ps.stats[STAT_MODE]
      = ent->client->weaponMode[ ent->client->ps.weapon ]
      = 0;
      ent->client->ps.pm_flags &= ~PMF_SINGLE_MODE;
  break;
    case '1':
         if ( ent->client->ps.weapon == WP_MP5K || ent->client->ps.weapon == WP_UMP45 ){
      bg_weaponlist[ ent->client->ps.weapon ].weapMode[ent->client->ps.clientNum]
          = ent->client->ps.stats[STAT_MODE]
          = ent->client->weaponMode[ ent->client->ps.weapon ]
          = 2;
         }else{
      bg_weaponlist[ ent->client->ps.weapon ].weapMode[ent->client->ps.clientNum]
          = ent->client->ps.stats[STAT_MODE]
          = ent->client->weaponMode[ ent->client->ps.weapon ]
          = 1;
      ent->client->ps.pm_flags |= PMF_SINGLE_MODE;
         }
      break;
    case '2':
      bg_weaponlist[ ent->client->ps.weapon ].weapMode[ent->client->ps.clientNum]
          = ent->client->ps.stats[STAT_MODE]
          = ent->client->weaponMode[ ent->client->ps.weapon ]
          = 2;
      ent->client->ps.pm_flags &= ~PMF_SINGLE_MODE;
      break;
  }
}

void Change_Mode(gentity_t *ent){

  int             index;  
  char                    weapmodes_saves[WP_NUM_WEAPONS];//xamis
  index = ent - g_entities;

 if( !G_WeaponHasModes( ent->client->ps.weapon ))
	return;
 ent->client->modechangeTime = level.time + 3000;
 ent->client->modeChanged =qtrue;

Q_strncpyz( weapmodes_saves, ent->client->weaponModeChar , sizeof( weapmodes_saves ) );
 
 if (ent->client->ps.weapon == WP_KNIFE && bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum] <2  )
     return;

  ent->client->weaponMode[ ent->client->ps.weapon ] ++;

  if ( ent->client->weaponMode[ ent->client->ps.weapon ] > 2  || ent->client->weaponMode[ ent->client->ps.weapon ] < 0 ) //modes cannot go above 2  or below 0
    ent->client->weaponMode[ ent->client->ps.weapon ] =0; 
 
 if ( ent->client->ps.weapon == WP_MP5K || ent->client->ps.weapon == WP_UMP45 || ent->client->ps.weapon ==WP_KNIFE  || ent->client->ps.weapon ==WP_HK69 ){
   if (ent->client->weaponMode[ ent->client->ps.weapon ] == 1 )
     ent->client->weaponMode[ ent->client->ps.weapon ]++;
 }


 bg_weaponlist[ ent->client->ps.weapon ].weapMode[ent->client->ps.clientNum] = ent->client->ps.stats[STAT_MODE]= ent->client->weaponMode[ ent->client->ps.weapon ];

 switch (ent->client->weaponMode[ ent->client->ps.weapon ]){


   case 0:
        weapmodes_saves[ent->client->ps.weapon]= '0';
        ent->client->ps.pm_flags &= ~PMF_SINGLE_MODE;
        if(ent->client->ps.weapon==WP_KNIFE ||ent->client->ps.weapon==WP_HK69 ){
            ent->client->ps.pm_flags |= PMF_SINGLE_MODE;
        ent->client->ps.weaponstate = WEAPON_TONORMAL;
        }
        break;
   case 1:
        if ( ent->client->ps.weapon == WP_MP5K || ent->client->ps.weapon == WP_UMP45 ){
     weapmodes_saves[ent->client->ps.weapon]= '2';
        }else{
      weapmodes_saves[ent->client->ps.weapon]= '1';
     ent->client->ps.pm_flags |= PMF_SINGLE_MODE;
        }
     break;
    case 2:
      weapmodes_saves[ent->client->ps.weapon]= '2';
      ent->client->ps.pm_flags &= ~PMF_SINGLE_MODE;
      if(ent->client->ps.weapon==WP_KNIFE ||ent->client->ps.weapon==WP_HK69 ){

      ent->client->ps.pm_flags |= PMF_SINGLE_MODE;
      ent->client->ps.weaponstate = WEAPON_TOALTERNATE;
      }
      break;
    default:
      weapmodes_saves[ent->client->ps.weapon]= '2';

     }
Q_strncpyz( ent->client->weaponModeChar,  weapmodes_saves, sizeof( ent->client->weaponModeChar ) );
//ent->client->ps.powerups[PW_WEAPMODES]= atoi(weapmodes_saves);
}



/*
==================
  Cmd_Reload
==================
*/
void Cmd_Reload( gentity_t *ent )       {


  int amt;
  int ammotoadd;

  amt = RoundCount(ent->client->ps.weapon);
  ammotoadd = amt;
  
  if (bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum]  == amt)
      return;

  if (BG_Grenade(ent->client->ps.weapon))
    return;
  
  // G_AddEvent(ent,EV_ZOOM_RESET,0);
  

  if ( bg_weaponlist[ent->client->ps.weapon].numClips[ent->client->ps.clientNum] == 0 || ent->client->ps.weapon == WP_KNIFE ) return;
  if (ent->client->ps.weapon == WP_SPAS && bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum] > 7 ){
    return;
  }
  if (ent->client->ps.weapon == WP_SPAS && bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum] <= 7 ){
    if (ent->client->ps.weaponTime >0 ) return;
    ent->client->ps.weaponstate = WEAPON_RELOADING_START;
    return;
  }

  ent->client->ps.weaponstate = WEAPON_RELOADING_START;
  if (bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum] > 0)  {
    ammotoadd -= bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum];
  }


    if ( bg_weaponlist[ent->client->ps.weapon].numClips[ent->client->ps.clientNum] > 0)   {
    bg_weaponlist[ent->client->ps.weapon].numClips[ent->client->ps.clientNum]--;

  }

  bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum] += ammotoadd;

}


/*
===============
FireWeapon
===============
*/
void FireWeapon( gentity_t *ent ) {


  if ( bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum] != -1
       ||!(BG_Grenade(ent->client->ps.weapon)) ) {
              if(  ent->s.weapon != WP_KNIFE ) {
    bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum]--;
              }
  }
  if (BG_Grenade(ent->client->ps.weapon))
        bg_weaponlist[ent->client->ps.weapon].numClips[ent->client->ps.clientNum]--;

  if ( (BG_Grenade(ent->client->ps.weapon))
        && bg_weaponlist[ent->client->ps.weapon].numClips[ent->client->ps.clientNum] <= 0){


    //bg_inventory.sort[ent->client->ps.clientNum][NADE] = WP_NONE;

        }
        s_quadFactor = 1;

        // track shots taken for accuracy tracking.  Grapple is not a weapon and gauntet is just not tracked
        if(  ent->s.weapon == WP_KNIFE ) {
          //  G_Printf("weapon is a knife");
        }

        // set aiming directions
        AngleVectors (ent->client->ps.viewangles, forward, right, up);

        CalcMuzzlePointOrigin ( ent, ent->client->oldOrigin, forward, right, up, muzzle );

        // fire the specific weapon
        switch( ent->s.weapon ) {
        case WP_KNIFE:
                if(ent->client->ps.stats[STAT_MODE]&& bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum] >1){
	       weapon_knife_fire( ent );
                 bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum]--;
                 if ( bg_weaponlist[ent->client->ps.weapon].rounds[ent->client->ps.clientNum] ==1){
                  BG_LastKnife();
                    bg_weaponlist[ ent->client->ps.weapon ].weapMode[ent->client->ps.clientNum]
                        = ent->client->ps.stats[STAT_MODE]
                        = ent->client->weaponMode[ ent->client->ps.weapon ]
                        = 0;
                        ent->client->ps.pm_flags &= ~PMF_SINGLE_MODE;
                //
                 }
                }else
                    Weapon_KnifeSlash( ent  );
         
                break;
                case WP_SPAS:
                        weapon_supershotgun_fire( ent );
        case WP_M4:
                        Bullet_Fire( ent, M4_SPREAD, M4_DAMAGE, MOD_M4 );
                break;
                case WP_MP5K:
                        Bullet_Fire( ent, MP5K_SPREAD, MP5K_DAMAGE, MOD_MP5K );
                        break;
                case WP_UMP45:
                  Bullet_Fire( ent, UMP45_SPREAD, UMP45_DAMAGE ,MOD_UMP45 );
                        break;
                case WP_PSG1:
                        Bullet_Fire( ent, PSG1_SPREAD, MACHINEGUN_DAMAGE, MOD_PSG1 );
                        break;
                case WP_SR8:
                        Bullet_Fire( ent, SR8_SPREAD, SR8_DAMAGE, MOD_SR8 );
                        break;
                case WP_G36:
                        Bullet_Fire( ent, G36_SPREAD, G36_DAMAGE, MOD_G36 );
                        break;
                case WP_LR300:
                  Bullet_Fire( ent, LR300_SPREAD, LR300_DAMAGE, MOD_LR300 );
                        break;
                case WP_AK103:
                        Bullet_Fire( ent, AK103_SPREAD, AK103_DAMAGE, MOD_AK103 );
                        break;
                case WP_NEGEV:
                        Bullet_Fire( ent, NEGEV_SPREAD, NEGEV_DAMAGE, MOD_NEGEV );
                        break;
                case WP_DEAGLE:
                        Bullet_Fire( ent, DEAGLE_SPREAD, DEAGLE_DAMAGE, MOD_DEAGLE );
                        break;
                case WP_BERETTA:
                        Bullet_Fire( ent, BERETTA_SPREAD, BERETTA_DAMAGE, MOD_BERETTA );
                        break;
        case WP_HK69:
                        weapon_grenadelauncher_fire( ent, ent->client->ps.stats[STAT_MODE]  );
                        break;
                case WP_HE:
                        //weapon_grenade_arm( ent );
                        weapon_grenade_throw( ent );
                        break;
                case WP_SMOKE:
                        weapon_smoke_throw( ent );
                        break;
        default:
// FIXME                G_Error( "Bad ent->s.weapon" );
                break;
        }
}


#ifdef MISSIONPACK

/*
===============
KamikazeRadiusDamage
===============
*/
static void KamikazeRadiusDamage( vec3_t origin, gentity_t *attacker, float damage, float radius ) {
        float           dist;
        gentity_t       *ent;
        int                     entityList[MAX_GENTITIES];
        int                     numListedEntities;
        vec3_t          mins, maxs;
        vec3_t          v;
        vec3_t          dir;
        int                     i, e;

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

                if (!ent->takedamage) {
                        continue;
                }

                // dont hit things we have already hit
                if( ent->kamikazeTime > level.time ) {
                        continue;
                }

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

//              if( CanDamage (ent, origin) ) {
                        VectorSubtract (ent->r.currentOrigin, origin, dir);
                        // push the center of mass higher than the origin so players
                        // get knocked into the air more
                        dir[2] += 24;
                        G_Damage( ent, NULL, attacker, dir, origin, damage, DAMAGE_RADIUS|DAMAGE_NO_TEAM_PROTECTION, MOD_KAMIKAZE );
                        ent->kamikazeTime = level.time + 3000;
//              }
        }
}

/*
===============
KamikazeShockWave
===============
*/
static void KamikazeShockWave( vec3_t origin, gentity_t *attacker, float damage, float push, float radius ) {
        float           dist;
        gentity_t       *ent;
        int                     entityList[MAX_GENTITIES];
        int                     numListedEntities;
        vec3_t          mins, maxs;
        vec3_t          v;
        vec3_t          dir;
        int                     i, e;

        if ( radius < 1 )
                radius = 1;

        for ( i = 0 ; i < 3 ; i++ ) {
                mins[i] = origin[i] - radius;
                maxs[i] = origin[i] + radius;
        }

        numListedEntities = trap_EntitiesInBox( mins, maxs, entityList, MAX_GENTITIES );

        for ( e = 0 ; e < numListedEntities ; e++ ) {
                ent = &g_entities[entityList[ e ]];

                // dont hit things we have already hit
                if( ent->kamikazeShockTime > level.time ) {
                        continue;
                }

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

//              if( CanDamage (ent, origin) ) {
                        VectorSubtract (ent->r.currentOrigin, origin, dir);
                        dir[2] += 24;
                        G_Damage( ent, NULL, attacker, dir, origin, damage, DAMAGE_RADIUS|DAMAGE_NO_TEAM_PROTECTION, MOD_KAMIKAZE );
                        //
                        dir[2] = 0;
                        VectorNormalize(dir);
                        if ( ent->client ) {
                                ent->client->ps.velocity[0] = dir[0] * push;
                                ent->client->ps.velocity[1] = dir[1] * push;
                                ent->client->ps.velocity[2] = 100;
                        }
                        ent->kamikazeShockTime = level.time + 3000;
//              }
        }
}

/*
===============
KamikazeDamage
===============
*/
static void KamikazeDamage( gentity_t *self ) {
        int i;
        float t;
        gentity_t *ent;
        vec3_t newangles;

        self->count += 100;

        if (self->count >= KAMI_SHOCKWAVE_STARTTIME) {
                // shockwave push back
                t = self->count - KAMI_SHOCKWAVE_STARTTIME;
                KamikazeShockWave(self->s.pos.trBase, self->activator, 25, 400, (int) (float) t * KAMI_SHOCKWAVE_MAXRADIUS / (KAMI_SHOCKWAVE_ENDTIME - KAMI_SHOCKWAVE_STARTTIME) );
        }
        //
        if (self->count >= KAMI_EXPLODE_STARTTIME) {
                // do our damage
                t = self->count - KAMI_EXPLODE_STARTTIME;
                KamikazeRadiusDamage( self->s.pos.trBase, self->activator, 400, (int) (float) t * KAMI_BOOMSPHERE_MAXRADIUS / (KAMI_IMPLODE_STARTTIME - KAMI_EXPLODE_STARTTIME) );
        }

        // either cycle or kill self
        if( self->count >= KAMI_SHOCKWAVE_ENDTIME ) {
                G_FreeEntity( self );
                return;
        }
        self->nextthink = level.time + 100;

        // add earth quake effect
        newangles[0] = crandom() * 2;
        newangles[1] = crandom() * 2;
        newangles[2] = 0;
        for (i = 0; i < MAX_CLIENTS; i++)
        {
                ent = &g_entities[i];
                if (!ent->inuse)
                        continue;
                if (!ent->client)
                        continue;

                if (ent->client->ps.groundEntityNum != ENTITYNUM_NONE) {
                        ent->client->ps.velocity[0] += crandom() * 120;
                        ent->client->ps.velocity[1] += crandom() * 120;
                        ent->client->ps.velocity[2] = 30 + random() * 25;
                }

                ent->client->ps.delta_angles[0] += ANGLE2SHORT(newangles[0] - self->movedir[0]);
                ent->client->ps.delta_angles[1] += ANGLE2SHORT(newangles[1] - self->movedir[1]);
                ent->client->ps.delta_angles[2] += ANGLE2SHORT(newangles[2] - self->movedir[2]);
        }
        VectorCopy(newangles, self->movedir);
}

/*
===============
G_StartKamikaze
===============
*/
void G_StartKamikaze( gentity_t *ent ) {
        gentity_t       *explosion;
        gentity_t       *te;
        vec3_t          snapped;

        // start up the explosion logic
        explosion = G_Spawn();

        explosion->s.eType = ET_EVENTS + EV_KAMIKAZE;
        explosion->eventTime = level.time;

        if ( ent->client ) {
                VectorCopy( ent->s.pos.trBase, snapped );
        }
        else {
                VectorCopy( ent->activator->s.pos.trBase, snapped );
        }
        SnapVector( snapped );          // save network bandwidth
        G_SetOrigin( explosion, snapped );

        explosion->classname = "kamikaze";
        explosion->s.pos.trType = TR_STATIONARY;

        explosion->kamikazeTime = level.time;

        explosion->think = KamikazeDamage;
        explosion->nextthink = level.time + 100;
        explosion->count = 0;
        VectorClear(explosion->movedir);

        trap_LinkEntity( explosion );

        if (ent->client) {
                //
                explosion->activator = ent;
                //
                ent->s.eFlags &= ~EF_KAMIKAZE;
                // nuke the guy that used it
                G_Damage( ent, ent, ent, NULL, NULL, 100000, DAMAGE_NO_PROTECTION, MOD_KAMIKAZE );
        }
        else {
                if ( !strcmp(ent->activator->classname, "bodyque") ) {
                        explosion->activator = &g_entities[ent->activator->r.ownerNum];
                }
                else {
                        explosion->activator = ent->activator;
                }
        }

        // play global sound at all clients
        te = G_TempEntity(snapped, EV_GLOBAL_TEAM_SOUND );
        te->r.svFlags |= SVF_BROADCAST;
        te->s.eventParm = GTS_KAMIKAZE;
}
#endif


/*
=======================
sentry code. for spawning and seting the spawn location of sentrys
=======================
*/
#define RANGE 500
#define HARC 90  // left/right fire arc
#define DARC 45 // how far the gun will depress
#define UARC 45 // how far the gun will elevate


qboolean checktarget(gentity_t *firer,gentity_t *target){
vec3_t          distance;
trace_t         trace;
int             angle;

/*
returns qfalse if the target is not valid. returns qtrue if it is
*/

if( target->client->sess.sessionTeam == TEAM_RED ){
    target->team ="red";
}
if( target->client->sess.sessionTeam == TEAM_BLUE ){
    target->team ="blue";
}

if (!target) // Do we have a target?
        return qfalse;
if (!target->inuse) // Does the target still exist?
        return qfalse;
if (target==firer) // is the target us?
        return qfalse;
if( (target->client->ps.powerups[PW_REDFLAG] || target->client->ps.powerups[PW_BLUEFLAG] )){
    
}else
if (!(strcmp(firer->team, target->team ))) //are we on the same team?
     return qfalse;

if(!target->client) // is the target a bot or player?
        return qfalse;
if (target==firer->parent) // is the target the person that created the turret?
        return qfalse;
if (OnSameTeam(firer->parent, target)) // is the target one of us?
        return qfalse;

if (target->health<0) // is the target still alive?
        return qfalse;

VectorSubtract(target->r.currentOrigin,firer->r.currentOrigin,distance);
if (VectorLength(distance)>RANGE) // is the target within range?
        return qfalse;

trap_Trace (&trace, firer->s.pos.trBase, NULL, NULL, target->s.pos.trBase, firer->s.number, MASK_SHOT );
if ( trace.contents & CONTENTS_SOLID ) // can we see the target?
        return qfalse;
/*
The last two checks are done last as they require more processing power than the others.
this order is just better from a proccesing load perspective
*/

        vectoangles (distance,distance);
        VectorSubtract(firer->centerpoint,distance,distance);
        angle=abs((int)distance[1]);
        while (angle>=360)
        {
        angle-=360;
        }
        if ((angle>=HARC) && (angle<=(360-HARC)))
                return qfalse;
        angle=abs((int)distance[0]);
        while (angle>=360)
        {
        angle-=360;
        }
        if ((angle>UARC) && (angle<(360-DARC)))
                return qfalse;

return qtrue;
}


void sentry_findenemy( gentity_t *ent){
        gentity_t *target;

        target = g_entities;

        for (; target < &g_entities[level.num_entities]; target++)
        {
                if(!checktarget(ent,target))
                        continue;
                ent->enemy=target;
                return;
        }

        ent->enemy=NULL;
}


void sentry_trackenemy( gentity_t *ent){

vec3_t dir;
VectorSubtract(ent->enemy->r.currentOrigin,ent->r.currentOrigin,dir);
VectorNormalize(dir);
VectorCopy(dir,ent->turloc);
vectoangles(dir,dir);
VectorCopy( dir,ent->s.apos.trBase );
trap_LinkEntity (ent);

}

void sentry_fireonenemy( gentity_t *ent){

fire_sentry( ent->parent, ent->r.currentOrigin, ent->turloc );
G_AddEvent( ent, EV_FIRE_WEAPON, 0 );
ent->count=level.time+200; //time between shots
}


void sentry_think( gentity_t *ent){

ent->nextthink=level.time+10;

if (!checktarget(ent,ent->enemy))
        sentry_findenemy(ent);
if(!ent->enemy)
        return;

sentry_trackenemy(ent);
if (ent->count<level.time)
        sentry_fireonenemy(ent);
}


/*QUAKED ut_mrsentry (1 .5 0) (-16 -16 -24) (16 16 32)
Spawn location for the CTF Spawn Room Sentry Cannon.

-------- KEYS --------
team : Team that Mr. Sentry belongs to. Will eliminate opposing team members within range (SEE NOTES). ("red" or "blue")
angle : Inital and idle angle for the sentry. Generally point this at or near the Spawn Room doors for highest effectiveness.
gametype : gametypes to have Mr. Sentry appear in, list types in this format: 01234

-------- NOTES --------
Mr. Sentry is designed to be used in conjunction with CTF Spawn Rooms (see the Notes on the func_door entity) to prevent enemy team players from surviving if they enter the opposing team's spawn room. Even though the properly set up doors will generally prevent this, Mr. Sentry also has one other function. It will kill any Flag Carrier that enters it's range no matter what team that player is on. This will prevent players from grabbing the flag and retreating the the complete safety of their Spawn Room and waiting out the rest of the map time with the flag.

For the anti-flag-camp feature to work properly, the entire spawn room must be enclosed with a 'nodrop' (a brush with the 'nodrop' texture on all sides). If this brush (or group of brushes) isn't placed, then Mr. Sentry will kill the Flag Carrier, and the flag will remain at that location, which is bad.
*/

void createsentrygun(gentity_t *ent){
        gentity_t *sentry;      // The object to hold the sentrys details.


        ent->clipmask = CONTENTS_SOLID | CONTENTS_PLAYERCLIP;
        ent->r.contents = CONTENTS_SOLID;
        ent->s.pos.trType = TR_STATIONARY;
        sentry=G_Spawn();
        sentry->team=ent->team; //set team to either red of blue
        sentry->eventTime=200;
        sentry->s.weapon=WP_SR8;//just set weapon for sound 
        sentry->classname="ut_mrsentry";     
        sentry->s.modelindex = G_ModelIndex("models/mrsentry/mrsentrybarrel.md3");
        sentry->model = "models/mrsentry/mrsentrybarrel.md3";
        sentry->s.modelindex2 = G_ModelIndex("models/mrsentry/mrsentrybarrel.md3");
        sentry->think=sentry_think;
        sentry->nextthink=level.time+100;
        G_SetOrigin( sentry, ent->r.currentOrigin );
        VectorCopy(ent->s.angles,sentry->s.apos.trBase);//set starting and idle angle from mapobject
        VectorCopy(sentry->s.apos.trBase,sentry->centerpoint);
        trap_LinkEntity (sentry);
        
        
}



void SP_Spawnsentry( gentity_t *ent ){
gentity_t       *base;



        base=G_Spawn();
        base->team=ent->team; //set team to either red of blue, pulled from mapobject
        base->s.modelindex = G_ModelIndex("models/mrsentry/mrsentrybase.md3");
        base->model = "models/mrsentry/mrsentrybase.md3";
        base->s.modelindex2 = G_ModelIndex("models/mrsentry/mrsentrybase.md3");
        G_SetOrigin( base, ent->r.currentOrigin ); // sets where the sentry is
        base->s.apos.trBase[1] = ent->s.angles[1];//set starting and idle angle from mapobject
      //  base->think=createsentrygun;
   //     base->nextthink=level.time+1000;
  //      base->think=sentry_think;
  //      base->nextthink=level.time+100;

        trap_LinkEntity (base);
        createsentrygun( ent);
}

