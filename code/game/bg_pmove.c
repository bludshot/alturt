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
// bg_pmove.c -- both games player movement code
// takes a ps and a usercmd as input and returns a modifed ps

#include "../qcommon/q_shared.h"
#include "bg_public.h"
#include "bg_local.h"
static qboolean PM_WallJump(void);
static qboolean PM_CheckWallJump(void);
qboolean PM_CheckPowerSlide( void );

pmove_t         *pm;
pml_t           pml;


// movement parameters
float   pm_stopspeed = 100.0f;
float   pm_duckScale = 0.45f; // blud
float   pm_swimScale = 0.50f;
float   pm_wadeScale = 0.70f;
float   pm_ladderscale = 0.50f; //Xamis


float   pm_accelerate = 6.0f;
float   pm_airaccelerate = 1.0f;
float   pm_wateraccelerate = 4.0f;
float   pm_flyaccelerate = 8.0f;
float   pm_ladderaccelerate = 4000; //Xamis
float   pm_slideaccelerate = 4000;


float   pm_friction = 5.0f;
float   pm_waterfriction = 1.0f;
float   pm_flightfriction = 3.0f;
float   pm_spectatorfriction = 5.0f;
float   pm_ladderfriction = 4000; //Xamis
float   pm_slidefriction = 0;


int             c_pmove = 0;

//Walljump constants
#define WALLJUMP_BOOST 180 //used in the checkWalljump function, no change to the actual walljump made here.
#define MAX_WALLJUMPS 3 //no explanation needed 
#define WALLJUMP_SPEED 580.0f //used in VectorMA for walljumps, affects player velocity
#define WALLJUMP_MAX_VEL 600 //max velocity during walljumps. I cut this in half, it was 1200 which seems way too high --xamis
#define WALLJUMP_MAX_UP_VEL 240 //cap the upward velocity on a walljump
#define WALLJUMP_UP_VEL_BOOST 0.5f //give the player some upward boost off the wall







#define LEDGEGRABMAXHEIGHT              42
#define LEDGEGRABHEIGHT                 38
#define LEDGEVERTOFFSET                 LEDGEGRABHEIGHT
#define LEDGEGRABMINHEIGHT              28

//max distance you can be from the ledge for ledge grabbing to work
#define LEDGEGRABDISTANCE               20

//min distance you can be from the ledge for ledge grab to work
#define LEDGEGRABMINDISTANCE    4

//distance at which the animation grabs the ledge
#define LEDGEHOROFFSET                  22


float vectoyaw( const vec3_t vec ) {
        float   yaw;

        if (vec[YAW] == 0 && vec[PITCH] == 0) {
                yaw = 0;
        } else {
                if (vec[PITCH]) {
                        yaw = ( atan2( vec[YAW], vec[PITCH]) * 180 / M_PI );
                } else if (vec[YAW] > 0) {
                        yaw = 90;
                } else {
                        yaw = 270;
                }
                if (yaw < 0) {
                        yaw += 360;
                }
        }

        return yaw;
}

void PM_SetPMViewAngle(playerState_t *ps, vec3_t angle, usercmd_t *ucmd)
{
        int                     i;

        for (i=0 ; i<3 ; i++)
        { // set the delta angle
                int             cmdAngle;

                cmdAngle = ANGLE2SHORT(angle[i]);
                ps->delta_angles[i] = cmdAngle - ucmd->angles[i];
        }
        VectorCopy (angle, ps->viewangles);
}

//lets go of a ledge
void BG_LetGoofLedge(playerState_t *ps)
{
        ps->pm_flags &= ~PMF_EDGE;
        ps->torsoTimer = 0;
        ps->legsTimer = 0;
}

qboolean BG_InLedgeMove( int anim )
{
	
        switch ( anim )
        {
        case BOTH_LEDGECLIMB:
                return qtrue;
                break;
        default:
               return qfalse;
               break;
        }

}

void PM_SetVelocityforLedgeMove( playerState_t *ps, int anim )
{
        vec3_t fwdAngles, moveDir;

                        if( pm->ps->torsoTimer > 700 ) 
                        {
                                ps->velocity[0] = 0;
                                ps->velocity[1] = 0;
                                ps->velocity[2] = 40;
                        }
                        else if( pm->ps->torsoTimer > 600 ) 
                        {
                                ps->velocity[0] = 0;
                                ps->velocity[1] = 0;
                                ps->velocity[2] = 140;
                        }
                        else  if( pm->ps->torsoTimer > 500 ) 
                        {
                                ps->velocity[0] = 0;
                                ps->velocity[1] = 0;
                                ps->velocity[2] = 100;
                        }
                        else if( pm->ps->torsoTimer > 400 ) 
                        {
                                ps->velocity[0] = 0;
                                ps->velocity[1] = 0;
                                ps->velocity[2] = 40;
                        }
                        else if( pm->ps->torsoTimer > 120 ) 
                        {
                                ps->velocity[0] = 0;
                                ps->velocity[1] = 0;
                                ps->velocity[2] = 180;
                        }
                        else if( pm->ps->torsoTimer > 90 ) 
                        {
                                ps->velocity[0] = 0;
                                ps->velocity[1] = 0;
                                ps->velocity[2] = 104;
                        }
                        else if(pm->ps->torsoTimer > 0)
                        {
                                ps->velocity[0] = 170;
                                ps->velocity[1] = 170;
                                ps->velocity[2] = 194;
                                VectorSet(fwdAngles, 0, pm->ps->viewangles[YAW], 0);
                                AngleVectors( fwdAngles, moveDir, NULL, NULL );
                                VectorScale(moveDir, 190, moveDir);
                                VectorCopy(moveDir, ps->velocity);
                        }
                        else
                        {
                            BG_LetGoofLedge(ps);
                                VectorClear(ps->velocity);
                        }

}

qboolean LedgeGrabableEntity(int entityNum)
{//indicates if the given entity is an entity that can be ledgegrabbed.
        //bgEntity_t *ent = PM_BGEntForNum(entityNum);
      //  switch(ent->s.eType)
      //  {
      //  case ET_PLAYER:
      //  case ET_ITEM:
       // case ET_MISSILE:
        //                return qfalse;
        //default:
                        return qtrue;
      //  };
}

void PM_GrabWallForClimb( playerState_t *ps )
{
        PM_StartTorsoAnim ( BOTH_LEDGECLIMB );
        PM_StartLegsAnim  ( BOTH_LEDGECLIMB );
        ps->torsoTimer = 800;
        ps->legsTimer = 800;
        ps->weaponTime = 800;
        PM_AddEvent(EV_LEDGEGRAB);
        ps->pm_flags |= PMF_EDGE;
}

//Switch to this animation and keep repeating this animation while updating its timers

void PM_AdjustAngleForLedgeClimb( playerState_t *ps, usercmd_t *ucmd )
{
        if( ps->pm_flags & PMF_EDGE ){
                if(ucmd->forwardmove <= 0)
                        {
                                BG_LetGoofLedge(ps);
                                return;
                        }
                        else
                        {
                PM_SetVelocityforLedgeMove(ps, ps->legsAnim);
                return;
                        }
        }
}

qboolean LedgeTrace( trace_t *trace, vec3_t dir, float *lerpup, float *lerpfwd, float *lerpyaw)
{//scan for for a ledge in the given direction
        vec3_t traceTo, traceFrom, wallangles;
        VectorMA( pm->ps->origin, LEDGEGRABDISTANCE, dir, traceTo );
        VectorCopy(pm->ps->origin, traceFrom);

	if ( CheckLadder() != 0 )
		return qfalse;

        traceFrom[2] += LEDGEGRABMINHEIGHT;
        traceTo[2] += LEDGEGRABMINHEIGHT;

        pm->trace( trace, traceFrom, NULL, NULL, traceTo, pm->ps->clientNum, pm->tracemask );

        if(trace->fraction < 1 && LedgeGrabableEntity(trace->entityNum))
        {//hit a wall, pop into the wall and fire down to find top of wall
                VectorMA(trace->endpos, 0.5, dir, traceTo);

                VectorCopy(traceTo, traceFrom);

                traceFrom[2] += (LEDGEGRABMAXHEIGHT - LEDGEGRABMINHEIGHT);

                pm->trace( trace, traceFrom, NULL, NULL, traceTo, pm->ps->clientNum, pm->tracemask );

                if(trace->fraction == 1.0 || trace->startsolid || !LedgeGrabableEntity(trace->entityNum))
                {
                        return qfalse;
                }
        }

        //check to make sure we found a good top surface and go from there
        vectoangles(trace->plane.normal, wallangles);
        if(wallangles[PITCH] > -20)
        {//no ledge or the ledge is too steep

                return qfalse;
        }
        else
        {
                VectorCopy(trace->endpos, traceTo);
                *lerpup = trace->endpos[2] - pm->ps->origin[2] - LEDGEVERTOFFSET;

                VectorCopy(pm->ps->origin, traceFrom);
                traceTo[2]-= 1;

                traceFrom[2] = traceTo[2];

                pm->trace( trace, traceFrom, NULL, NULL, traceTo, pm->ps->clientNum, MASK_SOLID );
                vectoangles(trace->plane.normal, wallangles);
                if(trace->fraction == 1.0 
                        || wallangles[PITCH] > 20 || wallangles[PITCH] < -20
                        || !LedgeGrabableEntity(trace->entityNum))
                {//no ledge or too steep of a ledge
                        return qfalse;
                }
                
                
                *lerpfwd = Distance(trace->endpos, traceFrom) - LEDGEHOROFFSET;
                *lerpyaw = vectoyaw( trace->plane.normal )+180;
                return qtrue;
        }
}

//check for ledge grab

void PM_CheckGrab(void)
{
        vec3_t checkDir, traceTo, fwdAngles;
        trace_t trace;
        float lerpup = 0;
        float lerpfwd = 0;
        float lerpyaw = 0;
        qboolean skipcmdtrace = qfalse;

      //  if(pm->ps->groundEntityNum != ENTITYNUM_NONE )//&& pm->ps->inAirAnim)
       // {//not in the air don't attempt a ledge grab
     //           return;
     //   }

    
        if(BG_InLedgeMove(pm->ps->legsAnim) || pm->ps->pm_type == PM_SPECTATOR)
        {//already on ledge, a spectator, or in a special jump
                return;
        }

        if(pm->ps->velocity == 0)
                return;//Not moving forward

        //try looking in front of us first
        VectorSet(fwdAngles, 0, pm->ps->viewangles[YAW], 0.0f);
        AngleVectors( fwdAngles, checkDir, NULL, NULL );

        if( !VectorCompare(pm->ps->velocity, vec3_origin) )
        {//player is moving
                if(LedgeTrace(&trace, checkDir, &lerpup, &lerpfwd, &lerpyaw))
                {       
                        skipcmdtrace = qtrue;
                }
        }

        if(!skipcmdtrace)
        { 
                //TRYING to go.
                if(!pm->cmd.forwardmove)
                {//no dice abort
                        return;
                }
                else
                {
                        if ( pm->cmd.forwardmove > 0 )
                        {//already tried this direction.
                                return;
                        }
                        else if ( pm->cmd.forwardmove < 0 )
                        {
                                AngleVectors( fwdAngles, checkDir, NULL, NULL );
                                VectorScale( checkDir, -1, checkDir );
                                VectorNormalize(checkDir);
                        }

                        if(!LedgeTrace(&trace, checkDir, &lerpup, &lerpfwd, &lerpyaw))
                        {//no dice
                                return;
                        }
                }
        }

        VectorCopy(pm->ps->origin, traceTo);
        VectorMA(pm->ps->origin, lerpfwd, checkDir, traceTo);
        traceTo[2] += lerpup;

        //check to see if we can actually latch to that position.
        pm->trace( &trace, pm->ps->origin, pm->mins, pm->maxs, traceTo, pm->ps->clientNum, MASK_PLAYERSOLID );
        if(trace.fraction != 1 || trace.startsolid)
        {  
                return;
        }

        //turn to face wall
        pm->ps->viewangles[YAW] = lerpyaw;
       // PM_SetPMViewAngle(pm->ps, pm->ps->viewangles, &pm->cmd);
        pm->cmd.angles[YAW] = ANGLE2SHORT( pm->ps->viewangles[YAW] ) - pm->ps->delta_angles[YAW];
        pm->ps->weaponTime = 0;       
        pm->cmd.upmove=0;
        VectorCopy(trace.endpos, pm->ps->origin);
        VectorCopy(vec3_origin, pm->ps->velocity);
        PM_GrabWallForClimb(pm->ps);

}
//End of ledgegrab functions

/*
===============
PM_AddEvent

===============
*/
void PM_AddEvent( int newEvent ) {
        BG_AddPredictableEventToPlayerstate( newEvent, 0, pm->ps );
}

/*
===============
PM_AddTouchEnt
===============
*/
void PM_AddTouchEnt( int entityNum ) {
        int             i;

        if ( entityNum == ENTITYNUM_WORLD ) {
                return;
        }
        if ( pm->numtouch == MAXTOUCH ) {
                return;
        }

        // see if it is already added
        for ( i = 0 ; i < pm->numtouch ; i++ ) {
                if ( pm->touchents[ i ] == entityNum ) {
                        return;
                }
        }

        // add it
        pm->touchents[pm->numtouch] = entityNum;
        pm->numtouch++;
}

/*
===================
PM_StartTorsoAnim
===================
*/
void PM_StartTorsoAnim( int anim ) {
        if ( pm->ps->pm_type >= PM_DEAD ) {
                return;
        }
        pm->ps->torsoAnim = ( ( pm->ps->torsoAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT )
                | anim;
}


void PM_StartLegsAnim( int anim ) {
        if ( pm->ps->pm_type >= PM_DEAD ) {
                return;
        }
        if ( pm->ps->legsTimer > 0 ) {
                return;         // a high priority animation is running
        }
        pm->ps->legsAnim = ( ( pm->ps->legsAnim & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT )
                | anim;
}

static void PM_ContinueLegsAnim( int anim ) {
        if ( ( pm->ps->legsAnim & ~ANIM_TOGGLEBIT ) == anim ) {
                return;
        }
        if ( pm->ps->legsTimer > 0 ) {
                return;         // a high priority animation is running
        }
        PM_StartLegsAnim( anim );
}

static void PM_ContinueTorsoAnim( int anim ) {
        if ( ( pm->ps->torsoAnim & ~ANIM_TOGGLEBIT ) == anim ) {
                return;
        }
        if ( pm->ps->torsoTimer > 0 ) {
                return;         // a high priority animation is running
        }
        PM_StartTorsoAnim( anim );
}

static void PM_ForceLegsAnim( int anim ) {
        pm->ps->legsTimer = 0;
        PM_StartLegsAnim( anim );
}

/* 
===================
PM_StartWeaponAnim, PM_ContinueWeaponAnim
===================
*/
void PM_StartWeaponAnim( int anim ) {
  if ( pm->ps->pm_type >= PM_DEAD ) {
    return;
  }

  pm->ps->generic1 = ( ( pm->ps->generic1 & ANIM_TOGGLEBIT ) ^ ANIM_TOGGLEBIT ) | anim;
}

static void PM_ContinueWeaponAnim( int anim ) {
  if ( ( pm->ps->generic1 & ~ANIM_TOGGLEBIT ) == anim ) {
    return;
  }

  PM_StartWeaponAnim( anim );
}
// END
/*
==================
PM_ClipVelocity

Slide off of the impacting surface
==================
*/
void PM_ClipVelocity( vec3_t in, vec3_t normal, vec3_t out, float overbounce ) {
        float   backoff;
        float   change;
        int             i;

        backoff = DotProduct (in, normal);

        if ( backoff < 0 ) {
                backoff *= overbounce;
        } else {
                backoff /= overbounce;
        }

        for ( i=0 ; i<3 ; i++ ) {
                change = normal[i]*backoff;
                out[i] = in[i] - change;
        }
}

/*
=============
CheckLadder Fuction Xamis
=============
*/

int CheckLadder( void )
{
        vec3_t forward,spot;
        vec3_t spot2;
        trace_t trace;
        vec3_t  traceMins;
        vec3_t  traceMaxs;

        if ( pm->cmd.upmove > 0 )
                return 0;
        if ( pm->ps->weaponTime > 0 )
                return 0;
        traceMins[0] = -16;
        traceMins[1] = -16;
        traceMins[2] = -16;

        traceMaxs[0] = 16;
        traceMaxs[1] = 16;
        traceMaxs[2] = 16;


        forward[0] = pml.forward[0];
        forward[1] = pml.forward[1];
        forward[2] = 0;

        VectorNormalize (forward);

        VectorMA (pm->ps->origin, 2 ,forward, spot);

        pm->trace (&trace, pm->ps->origin, pm->mins, pm->maxs, spot,
                    pm->ps->clientNum, MASK_PLAYERSOLID);

        if ( pm->ps->pm_type == PM_DEAD )
                return 0;

        if (pm->ps->pm_flags & PMF_TIME_WATERJUMP)
                return 0;

        if ((trace.fraction < 1) && (trace.surfaceFlags & SURF_LADDER)) {
                if ( pml.groundPlane && pm->cmd.forwardmove <= -15 )
                        return 0;
                return 1;
        }

        VectorClear( spot);

        VectorMA (pm->ps->origin, -5, forward, spot );

        spot[2] -= 25;

        VectorMA( spot, 10, forward, spot2 );

        pm->trace ( &trace, spot,traceMins,traceMaxs, spot2, pm->ps->clientNum, MASK_PLAYERSOLID );

        if ((trace.fraction < 1) && (trace.surfaceFlags & SURF_LADDER)  )
        {
                if ( pml.groundPlane )
                        return -2;
                else
                {
                        return -1;
                }
        }
        return 0;
}


/*
==================
PM_Friction

Handles both ground friction and water friction
==================
*/
static void PM_Friction( void ) {
        vec3_t  vec;
        float   *vel;
        float   speed, newspeed, control;
        float   drop;

        vel = pm->ps->velocity;

        VectorCopy( vel, vec );
        if ( pml.walking ) {
                vec[2] = 0;     // ignore slope movement
        }

        speed = VectorLength(vec);
        if (speed < 1) {
                vel[0] = 0;
                vel[1] = 0;             // allow sinking underwater
                // FIXME: still have z friction underwater?
                return;
        }

        drop = 0;

        // apply ground friction
        if ( pm->waterlevel <= 1 ) {
                if ( pml.walking && !(pml.groundTrace.surfaceFlags & SURF_SLICK) ) {
                        // if getting knocked back, no friction
                        if ( ! (pm->ps->pm_flags & PMF_TIME_KNOCKBACK) ) {
                                control = speed < pm_stopspeed ? pm_stopspeed : speed;
                                drop += control*pm_friction*pml.frametime;
                        }
                }
        }

        // apply water friction even if just wading
        if ( pm->waterlevel ) {
                drop += speed*pm_waterfriction*pm->waterlevel*pml.frametime;
        }

        if ( pm->ps->pm_type == PM_SPECTATOR) {
                drop += speed*pm_spectatorfriction*pml.frametime;
        }
                //apply ladder friction Xamis
        if ( CheckLadder() != 0 )
        {
                drop += speed*pm_ladderfriction*pml.frametime;
        }



        // scale the velocity
        newspeed = speed - drop;
        if (newspeed < 0) {
                newspeed = 0;
        }
        newspeed /= speed;

        vel[0] = vel[0] * newspeed;
        vel[1] = vel[1] * newspeed;
        vel[2] = vel[2] * newspeed;
}


/*
==============
PM_Accelerate

Handles user intended acceleration
==============
*/
static void PM_Accelerate( vec3_t wishdir, float wishspeed, float accel ) {
#if 1
        // q2 style
        int                     i;
        float           addspeed, accelspeed, currentspeed;

        currentspeed = DotProduct (pm->ps->velocity, wishdir);
        addspeed = wishspeed - currentspeed;
        if (addspeed <= 0) {
                return;
        }
        accelspeed = accel*pml.frametime*wishspeed;
        if (accelspeed > addspeed) {
                accelspeed = addspeed;
        }

        for (i=0 ; i<3 ; i++) {
                pm->ps->velocity[i] += accelspeed*wishdir[i];
        }
#else
        // proper way (avoids strafe jump maxspeed bug), but feels bad
        vec3_t          wishVelocity;
        vec3_t          pushDir;
        float           pushLen;
        float           canPush;

        VectorScale( wishdir, wishspeed, wishVelocity );
        VectorSubtract( wishVelocity, pm->ps->velocity, pushDir );
        pushLen = VectorNormalize( pushDir );

        canPush = accel*pml.frametime*wishspeed;
        if (canPush > pushLen) {
                canPush = pushLen;
        }

        VectorMA( pm->ps->velocity, canPush, pushDir, pm->ps->velocity );
#endif
}



/*
============
PM_CmdScale

Returns the scale factor to apply to cmd movements
This allows the clients to use axial -127 to 127 values for all directions
without getting a sqrt(2) distortion in speed.
============
*/
static float PM_CmdScale( usercmd_t *cmd ) {
        int             max;
        float   total;
        float   scale;

        max = abs( cmd->forwardmove );
        if ( abs( cmd->rightmove ) > max ) {
                max = abs( cmd->rightmove );
        }
        if ( abs( cmd->upmove ) > max ) {
                max = abs( cmd->upmove );
        }
        if ( !max ) {
                return 0;
        }

        total = sqrt( cmd->forwardmove * cmd->forwardmove
                + cmd->rightmove * cmd->rightmove + cmd->upmove * cmd->upmove );
        scale = (float)pm->ps->speed * max / ( 127.0 * total );

        return scale;
}


/*
================
PM_SetMovementDir

Determine the rotation of the legs reletive
to the facing dir
================
*/
static void PM_SetMovementDir( void ) {
        if ( pm->cmd.forwardmove || pm->cmd.rightmove ) {
                if ( pm->cmd.rightmove == 0 && pm->cmd.forwardmove > 0 ) {
                        pm->ps->movementDir = 0;
                } else if ( pm->cmd.rightmove < 0 && pm->cmd.forwardmove > 0 ) {
                        pm->ps->movementDir = 1;
                } else if ( pm->cmd.rightmove < 0 && pm->cmd.forwardmove == 0 ) {
                        pm->ps->movementDir = 2;
                } else if ( pm->cmd.rightmove < 0 && pm->cmd.forwardmove < 0 ) {
                        pm->ps->movementDir = 3;
                } else if ( pm->cmd.rightmove == 0 && pm->cmd.forwardmove < 0 ) {
                        pm->ps->movementDir = 4;
                } else if ( pm->cmd.rightmove > 0 && pm->cmd.forwardmove < 0 ) {
                        pm->ps->movementDir = 5;
                } else if ( pm->cmd.rightmove > 0 && pm->cmd.forwardmove == 0 ) {
                        pm->ps->movementDir = 6;
                } else if ( pm->cmd.rightmove > 0 && pm->cmd.forwardmove > 0 ) {
                        pm->ps->movementDir = 7;
                }
        } else {
                // if they aren't actively going directly sideways,
                // change the animation to the diagonal so they
                // don't stop too crooked
                if ( pm->ps->movementDir == 2 ) {
                        pm->ps->movementDir = 1;
                } else if ( pm->ps->movementDir == 6 ) {
                        pm->ps->movementDir = 7;
                }
        }
}



/*
=============
PM_CheckJump
=============
*/
static qboolean PM_CheckJump( void )
{
  vec3_t normal;

  if( pm->ps->groundEntityNum == ENTITYNUM_NONE )
    return qfalse;

  if( pm->ps->pm_flags & PMF_RESPAWNED )
    return qfalse;    // don't allow jump until all buttons are up

  if( pm->cmd.upmove < 10 )
    // not holding jump
    return qfalse;

  // must wait for jump to be released
  if( pm->ps->pm_flags & PMF_JUMP_HELD )
  {
    // clear upmove so cmdscale doesn't lower running speed
    pm->cmd.upmove = 0;
    return qfalse;
  }

  pml.groundPlane = qfalse;   // jumping away
  pml.walking = qfalse;
  pm->ps->pm_flags |= PMF_JUMP_HELD;

  pm->ps->groundEntityNum = ENTITYNUM_NONE;

  // jump away from wall
  VectorSet( normal, 0.0f, 0.0f, 0.9f );

  if( pm->ps->velocity[ 2 ] < 0 )
    pm->ps->velocity[ 2 ] = 0;
  
  
  
  if (pm->ps->pm_flags & PMF_BLEEDING ||  pm->ps->stats[STAT_HEALTH] < 15)
VectorMA( pm->ps->velocity, JUMP_VELOCITY *0.5,
            normal, pm->ps->velocity );
  else
  VectorMA( pm->ps->velocity, JUMP_VELOCITY,
            normal, pm->ps->velocity );
  

  PM_AddEvent( EV_JUMP );

  if( pm->cmd.forwardmove >= 0 )
  {

      PM_ForceLegsAnim( LEGS_JUMP );
    pm->ps->pm_flags &= ~PMF_BACKWARDS_JUMP;
  }
  else
  {
      PM_ForceLegsAnim( LEGS_JUMPB );
    pm->ps->pm_flags |= PMF_BACKWARDS_JUMP;
  }

  return qtrue;
}


/*
=============
PM_CheckWaterJump
=============
*/
static qboolean PM_CheckWaterJump( void ) {
        vec3_t  spot;
        int             cont;
        vec3_t  flatforward;

        if (pm->ps->pm_time) {
                return qfalse;
        }

        // check for water jump
        if ( pm->waterlevel != 2 ) {
                return qfalse;
        }

        flatforward[0] = pml.forward[0];
        flatforward[1] = pml.forward[1];
        flatforward[2] = 0;
        VectorNormalize (flatforward);

        VectorMA (pm->ps->origin, 30, flatforward, spot);
        spot[2] += 4;
        cont = pm->pointcontents (spot, pm->ps->clientNum );
        if ( !(cont & CONTENTS_SOLID) ) {
                return qfalse;
        }

        spot[2] += 16;
        cont = pm->pointcontents (spot, pm->ps->clientNum );
        if ( cont ) {
                return qfalse;
        }

        // jump out of water
        VectorScale (pml.forward, 200, pm->ps->velocity);
        pm->ps->velocity[2] = 350;

        pm->ps->pm_flags |= PMF_TIME_WATERJUMP;
        pm->ps->pm_time = 2000;

        return qtrue;
}


/*
===================
PM_WaterJumpMove

Flying out of the water
===================
*/
static void PM_WaterJumpMove( void ) {
        // waterjump has no control, but falls

// PM_StepSlideMove( qtrue, qfalse );
  PM_StepSlideMove( qtrue );
        pm->ps->velocity[2] -= pm->ps->gravity * pml.frametime;
        if (pm->ps->velocity[2] < 0) {
                // cancel as soon as we are falling down again
                pm->ps->pm_flags &= ~PMF_ALL_TIMES;
                pm->ps->pm_time = 0;
        }
}

/*
===================
PM_WaterMove

===================
*/
static void PM_WaterMove( void ) {
        int             i;
        vec3_t  wishvel;
        float   wishspeed;
        vec3_t  wishdir;
        float   scale;
        float   vel;

        if ( PM_CheckWaterJump() ) {
                PM_WaterJumpMove();
                return;
        }
#if 0
        // jump = head for surface
        if ( pm->cmd.upmove >= 10 ) {
                if (pm->ps->velocity[2] > -300) {
                        if ( pm->watertype == CONTENTS_WATER ) {
                                pm->ps->velocity[2] = 100;
                        } else if (pm->watertype == CONTENTS_SLIME) {
                                pm->ps->velocity[2] = 80;
                        } else {
                                pm->ps->velocity[2] = 50;
                        }
                }
        }
#endif
        PM_Friction ();

        scale = PM_CmdScale( &pm->cmd );
        //
        // user intentions
        //
        if ( !scale ) {
                wishvel[0] = 0;
                wishvel[1] = 0;
                wishvel[2] = -60;               // sink towards bottom
        } else {
                for (i=0 ; i<3 ; i++)
                        wishvel[i] = scale * pml.forward[i]*pm->cmd.forwardmove + scale * pml.right[i]*pm->cmd.rightmove;

                wishvel[2] += scale * pm->cmd.upmove;
        }

        VectorCopy (wishvel, wishdir);
        wishspeed = VectorNormalize(wishdir);

        if ( wishspeed > pm->ps->speed * pm_swimScale ) {
                wishspeed = pm->ps->speed * pm_swimScale;
        }

        PM_Accelerate (wishdir, wishspeed, pm_wateraccelerate);

        // make sure we can go up slopes easily under water
        if ( pml.groundPlane && DotProduct( pm->ps->velocity, pml.groundTrace.plane.normal ) < 0 ) {
                vel = VectorLength(pm->ps->velocity);
                // slide along the ground plane
                PM_ClipVelocity (pm->ps->velocity, pml.groundTrace.plane.normal,
                        pm->ps->velocity, OVERCLIP );

                VectorNormalize(pm->ps->velocity);
                VectorScale(pm->ps->velocity, vel, pm->ps->velocity);
        }

        PM_SlideMove( qfalse );
}





#ifdef MISSIONPACK
/*
===================
PM_InvulnerabilityMove

Only with the invulnerability powerup
===================
*/
/*
static void PM_InvulnerabilityMove( void ) {
        pm->cmd.forwardmove = 0;
        pm->cmd.rightmove = 0;
        pm->cmd.upmove = 0;
        VectorClear(pm->ps->velocity);
}
*/
#endif

/*
===================
PM_FlyMove

Only with the flight powerup
===================
*/
/* //No longer used in Alturt
static void PM_FlyMove( void ) {
        int             i;
        vec3_t  wishvel;
        float   wishspeed;
        vec3_t  wishdir;
        float   scale;

        // normal slowdown
        PM_Friction ();

        scale = PM_CmdScale( &pm->cmd );
        //
        // user intentions
        //
        if ( !scale ) {
                wishvel[0] = 0;
                wishvel[1] = 0;
                wishvel[2] = 0;
        } else {
                for (i=0 ; i<3 ; i++) {
                        wishvel[i] = scale * pml.forward[i]*pm->cmd.forwardmove + scale * pml.right[i]*pm->cmd.rightmove;
                }

                wishvel[2] += scale * pm->cmd.upmove;
        }

        VectorCopy (wishvel, wishdir);
        wishspeed = VectorNormalize(wishdir);

        PM_Accelerate (wishdir, wishspeed, pm_flyaccelerate);
        PM_StepSlideMove( qfalse );
//        PM_StepSlideMove( qfalse, qfalse );
}
*/


/*
===================
PM_AirMove

===================
*/
static void PM_AirMove( void ) {
        int                     i;
        vec3_t          wishvel;
        float           fmove, smove;
        vec3_t          wishdir;
        float           wishspeed;
        float           scale;
        usercmd_t       cmd;

        PM_Friction();

        fmove = pm->cmd.forwardmove;
        smove = pm->cmd.rightmove;

        cmd = pm->cmd;
        scale = PM_CmdScale( &cmd );

        // set the movementDir so clients can rotate the legs for strafing
        PM_SetMovementDir();

        // project moves down to flat plane
      //  pml.forward[2] = 0;
     //   pml.right[2] = 0;
      //  VectorNormalize (pml.forward);
     //   VectorNormalize (pml.right);

        for ( i = 0 ; i < 2 ; i++ ) {
                wishvel[i] = pml.forward[i]*fmove + pml.right[i]*smove;
        }
        wishvel[2] = 0;

        VectorCopy (wishvel, wishdir);
        wishspeed = VectorNormalize(wishdir);
        wishspeed *= scale;

        // not on ground, so little effect on velocity
        PM_Accelerate (wishdir, wishspeed, pm_airaccelerate);

        // we may have a ground plane that is very steep, even
        // though we don't have a groundentity
        // slide along the steep plane
        if ( pml.groundPlane ) {
          pm->ps->pm_flags |= PMF_ONGROUND;
                PM_ClipVelocity (pm->ps->velocity, pml.groundTrace.plane.normal,
                        pm->ps->velocity, OVERCLIP );
        }




#if 0
        //ZOID:  If we are on the grapple, try stair-stepping
        //this allows a player to use the grapple to pull himself
        //over a ledge
        if (pm->ps->pm_flags & PMF_GRAPPLE_PULL)
                PM_StepSlideMove ( qtrue );
        else
                PM_SlideMove ( qtrue );
#endif
          if ( pm->cmd.forwardmove > 0 ) {
                PM_CheckGrab();
          }

    if (PM_CheckWallJump()) {
      if (PM_WallJump()) {
          PM_AddEvent(EV_WALLJUMP);
          pm->ps->stats[STAT_WALLJUMPS]++;
      }
    }

        
        PM_SlideMove ( qtrue );
}

/*
===================
PM_GrappleMove

===================
*/
/*
static void PM_GrappleMove( void ) {
        vec3_t vel, v;
        float vlen;

        VectorScale(pml.forward, -16, v);
        VectorAdd(pm->ps->grapplePoint, v, v);
        VectorSubtract(v, pm->ps->origin, vel);
        vlen = VectorLength(vel);
        VectorNormalize( vel );

        if (vlen <= 100)
                VectorScale(vel, 10 * vlen, vel);
        else
                VectorScale(vel, 800, vel);

        VectorCopy(vel, pm->ps->velocity);

        pml.groundPlane = qfalse;
}
*/
/*
===================
PM_WalkMove

===================
*/
static void PM_WalkMove( void ) {
        int                     i;
        vec3_t          wishvel;
        float           fmove, smove;
        vec3_t          wishdir;
        float           wishspeed;
        float           scale;
        usercmd_t       cmd;
        float           accelerate;
        float           vel;

        pm->ps->stats[STAT_WALLJUMPS] = 0;
        
        if ( pm->waterlevel > 2 && DotProduct( pml.forward, pml.groundTrace.plane.normal ) > 0 ) {
                // begin swimming
                PM_WaterMove();
                return;
        }


        if ( PM_CheckJump () ) {
                // jumped away
                if ( pm->waterlevel > 1 ) {
                        PM_WaterMove();
                } else {
                        PM_AirMove();
                }
                return;
        }
        
;

        PM_Friction ();

        fmove = pm->cmd.forwardmove;
        smove = pm->cmd.rightmove;

        cmd = pm->cmd;
        scale = PM_CmdScale( &cmd );

        // set the movementDir so clients can rotate the legs for strafing
        PM_SetMovementDir();

        // project moves down to flat plane
        pml.forward[2] = 0;
        pml.right[2] = 0;

        // project the forward and right directions onto the ground plane
        PM_ClipVelocity (pml.forward, pml.groundTrace.plane.normal, pml.forward, OVERCLIP );
        PM_ClipVelocity (pml.right, pml.groundTrace.plane.normal, pml.right, OVERCLIP );
        //
        VectorNormalize (pml.forward);
        VectorNormalize (pml.right);

        for ( i = 0 ; i < 3 ; i++ ) {
                wishvel[i] = pml.forward[i]*fmove + pml.right[i]*smove;
        }
        // when going up or down slopes the wish velocity should Not be zero
//      wishvel[2] = 0;

        VectorCopy (wishvel, wishdir);
        wishspeed = VectorNormalize(wishdir);
        wishspeed *= scale;

        // clamp the speed lower if ducking
        if ( pm->ps->pm_flags & PMF_DUCKED ) {
                if ( wishspeed > pm->ps->speed * pm_duckScale ) {
                        wishspeed = pm->ps->speed * pm_duckScale;
                }
        }

        // clamp the speed lower if wading or walking on the bottom
        if ( pm->waterlevel ) {
                float   waterScale;

                waterScale = pm->waterlevel / 3.0;
                waterScale = 1.0 - ( 1.0 - pm_swimScale ) * waterScale;
                if ( wishspeed > pm->ps->speed * waterScale ) {
                        wishspeed = pm->ps->speed * waterScale;
                }
        }

        // when a player gets hit, they temporarily lose
        // full control, which allows them to be moved a bit
        if ( ( pml.groundTrace.surfaceFlags & SURF_SLICK ) || pm->ps->pm_flags & PMF_TIME_KNOCKBACK ) {
                accelerate = pm_airaccelerate;
        } else {
                accelerate = pm_accelerate;
        }

        PM_Accelerate (wishdir, wishspeed, accelerate);

        //Com_Printf("velocity = %1.1f %1.1f %1.1f\n", pm->ps->velocity[0], pm->ps->velocity[1], pm->ps->velocity[2]);
        //Com_Printf("velocity1 = %1.1f\n", VectorLength(pm->ps->velocity));

        if ( ( pml.groundTrace.surfaceFlags & SURF_SLICK ) || pm->ps->pm_flags & PMF_TIME_KNOCKBACK ) {
                pm->ps->velocity[2] -= pm->ps->gravity * pml.frametime;
        } else {
                // don't reset the z velocity for slopes
//              pm->ps->velocity[2] = 0;
        }

        vel = VectorLength(pm->ps->velocity);

        // slide along the ground plane
        PM_ClipVelocity (pm->ps->velocity, pml.groundTrace.plane.normal,
                pm->ps->velocity, OVERCLIP );

        // don't decrease velocity when going up or down a slope
        VectorNormalize(pm->ps->velocity);
        VectorScale(pm->ps->velocity, vel, pm->ps->velocity);

        // don't do anything if standing still
        if (!pm->ps->velocity[0] && !pm->ps->velocity[1]) {
                return;
        }

      // PM_StepSlideMove( qfalse, qfalse );
        PM_StepSlideMove( qfalse );

        //Com_Printf("velocity2 = %1.1f\n", VectorLength(pm->ps->velocity));

}


/*
==============
PM_DeadMove
==============
*/
static void PM_DeadMove( void ) {
        float   forward;

        if ( !pml.walking ) {
                return;
        }

        // extra friction

        forward = VectorLength (pm->ps->velocity);
        forward -= 20;
        if ( forward <= 0 ) {
                VectorClear (pm->ps->velocity);
        } else {
                VectorNormalize (pm->ps->velocity);
                VectorScale (pm->ps->velocity, forward, pm->ps->velocity);
        }
}


/*
===============
PM_NoclipMove
===============
*/
static void PM_NoclipMove( void ) {
        float   speed, drop, friction, control, newspeed;
        int                     i;
        vec3_t          wishvel;
        float           fmove, smove;
        vec3_t          wishdir;
        float           wishspeed;
        float           scale;

        pm->ps->viewheight = DEFAULT_VIEWHEIGHT;

        // friction

        speed = VectorLength (pm->ps->velocity);
        if (speed < 1)
        {
                VectorCopy (vec3_origin, pm->ps->velocity);
        }
        else
        {
                drop = 0;

                friction = pm_friction*1.5;     // extra friction
                control = speed < pm_stopspeed ? pm_stopspeed : speed;
                drop += control*friction*pml.frametime;

                // scale the velocity
                newspeed = speed - drop;
                if (newspeed < 0)
                        newspeed = 0;
                newspeed /= speed;

                VectorScale (pm->ps->velocity, newspeed, pm->ps->velocity);
        }

        // accelerate
        scale = PM_CmdScale( &pm->cmd );

        fmove = pm->cmd.forwardmove;
        smove = pm->cmd.rightmove;

        for (i=0 ; i<3 ; i++)
                wishvel[i] = pml.forward[i]*fmove + pml.right[i]*smove;
        wishvel[2] += pm->cmd.upmove;

        VectorCopy (wishvel, wishdir);
        wishspeed = VectorNormalize(wishdir);
        wishspeed *= scale;

        PM_Accelerate( wishdir, wishspeed, pm_accelerate );

        // move
        VectorMA (pm->ps->origin, pml.frametime, pm->ps->velocity, pm->ps->origin);
}

//============================================================================

/*
================
PM_FootstepForSurface

Returns an event number apropriate for the groundsurface
================
*/
static int PM_FootstepForSurface( void ) {
        if ( pml.groundTrace.surfaceFlags & SURF_NOSTEPS ) {
                return 0;
        }
        if ( pml.groundTrace.surfaceFlags & SURF_METALSTEPS ) {
                return EV_FOOTSTEP_METAL;
        }
         if ( CheckLadder() != 0 ){
                return EV_FOOTSTEP_LADDER;
        }
        return EV_FOOTSTEP;
}


/*
=================
PM_CrashLand

Check for hard landings that generate sound events
=================
*/
static void PM_CrashLand( void ) {
        float           delta;
        float           dist;
        float           vel, acc;
        float           t;
        float           a, b, c, den;

        
        // decide which landing animation to use
        if ( pm->ps->pm_flags & PMF_BACKWARDS_JUMP ) {
                PM_ForceLegsAnim( LEGS_LANDB );
        } else {
                PM_ForceLegsAnim( LEGS_LAND );
        }

        pm->ps->legsTimer = TIMER_LAND;

        // calculate the exact velocity on landing
        dist = pm->ps->origin[2] - pml.previous_origin[2];
        vel = pml.previous_velocity[2];
        acc = -pm->ps->gravity;

        a = acc / 2;
        b = vel;
        c = -dist;

        den =  b * b - 4 * a * c;
        if ( den < 0 ) {
                return;
        }
        t = (-b - sqrt( den ) ) / ( 2 * a );

        delta = vel + t * acc;
        delta = delta*delta * 0.0001;

        /* Xamis -- we don't want this!
        // ducking while falling doubles damage
        if ( pm->ps->pm_flags & PMF_DUCKED ) {
                delta *= 2;
        } */

        // never take falling damage if completely underwater
        if ( pm->waterlevel == 3 ) {
                return;
        }

        // reduce falling damage if there is standing water
        if ( pm->waterlevel == 2 ) {
                delta *= 0.25;
        }
        if ( pm->waterlevel == 1 ) {
                delta *= 0.5;
        }

        if ( delta < 1 ) {
                return;
        }
        //Com_Printf("Delta is %f\n", delta);
        // create a local entity event to play the sound

        // SURF_NODAMAGE is used for bounce pads where you don't ever
        // want to take damage or play a crunch sound
        if ( !(pml.groundTrace.surfaceFlags & SURF_NODAMAGE) )  {
                if ( delta >75 ) {
                        PM_AddEvent( EV_FALL_FAR );
                       
                } else if ( delta > 60 ) {
                        // this is a pain grunt, so don't play it if dead
                        if ( pm->ps->stats[STAT_HEALTH] > 0 ) {
                                PM_AddEvent( EV_FALL_MEDIUM );
                        }
                } else if ( delta > 34 ) {
                        PM_AddEvent( EV_FALL_SHORT );
                } else {
                        PM_AddEvent( PM_FootstepForSurface() );
                }
        }

        // start footstep cycle over
        pm->ps->bobCycle = 0;
}

/*
=============
PM_CheckStuck
=============
*/
/*
void PM_CheckStuck(void) {
        trace_t trace;

        pm->trace (&trace, pm->ps->origin, pm->mins, pm->maxs, pm->ps->origin, pm->ps->clientNum, pm->tracemask);
        if (trace.allsolid) {
                //int shit = qtrue;
        }
}
*/

/*
=============
PM_CorrectAllSolid
=============
*/
static int PM_CorrectAllSolid( trace_t *trace ) {
        int                     i, j, k;
        vec3_t          point;

        if ( pm->debugLevel ) {
                Com_Printf("%i:allsolid\n", c_pmove);
        }

        // jitter around
        for (i = -1; i <= 1; i++) {
                for (j = -1; j <= 1; j++) {
                        for (k = -1; k <= 1; k++) {
                                VectorCopy(pm->ps->origin, point);
                                point[0] += (float) i;
                                point[1] += (float) j;
                                point[2] += (float) k;
                                pm->trace (trace, point, pm->mins, pm->maxs, point, pm->ps->clientNum, pm->tracemask);
                                if ( !trace->allsolid ) {
                                        point[0] = pm->ps->origin[0];
                                        point[1] = pm->ps->origin[1];
                                        point[2] = pm->ps->origin[2] - 0.25;

                                        pm->trace (trace, pm->ps->origin, pm->mins, pm->maxs, point, pm->ps->clientNum, pm->tracemask);
                                        pml.groundTrace = *trace;
                                        return qtrue;
                                }
                        }
                }
        }

        pm->ps->groundEntityNum = ENTITYNUM_NONE;
        pml.groundPlane = qfalse;
        pml.walking = qfalse;

        return qfalse;
}


/*
=============
PM_GroundTraceMissed

The ground trace didn't hit a surface, so we are in freefall
=============
*/
static void PM_GroundTraceMissed( void ) {
        trace_t         trace;
        vec3_t          point;

        if ( pm->ps->groundEntityNum != ENTITYNUM_NONE ) {
                // we just transitioned into freefall
                if ( pm->debugLevel ) {
                        Com_Printf("%i:lift\n", c_pmove);
                }

                // if they aren't in a jumping animation and the ground is a ways away, force into it
                // if we didn't do the trace, the player would be backflipping down staircases
                VectorCopy( pm->ps->origin, point );
                point[2] -= 64;

                pm->trace (&trace, pm->ps->origin, pm->mins, pm->maxs, point, pm->ps->clientNum, pm->tracemask);
                if ( trace.fraction == 1.0 ) {
                        if ( pm->cmd.forwardmove >= 0 ) {
                                PM_ForceLegsAnim( LEGS_JUMP );
                                pm->ps->pm_flags &= ~PMF_BACKWARDS_JUMP;
                        } else {
                                PM_ForceLegsAnim( LEGS_JUMPB );
                                pm->ps->pm_flags |= PMF_BACKWARDS_JUMP;
                        }
                }
        }

        pm->ps->groundEntityNum = ENTITYNUM_NONE;
        pml.groundPlane = qfalse;
        pml.walking = qfalse;
}


/*
=============
PM_GroundTrace
=============
*/
static void PM_GroundTrace( void ) {
        vec3_t          point;
        trace_t         trace;
        vec3_t      refNormal = { 0.0f, 0.0f, 1.0f };
        point[0] = pm->ps->origin[0];
        point[1] = pm->ps->origin[1];
        point[2] = pm->ps->origin[2] - 0.25;

        pm->trace (&trace, pm->ps->origin, pm->mins, pm->maxs, point, pm->ps->clientNum, pm->tracemask);
        pml.groundTrace = trace;

        // do something corrective if the trace starts in a solid...
        if ( trace.allsolid ) {
                if ( !PM_CorrectAllSolid(&trace) )
                        return;
        }
  //make sure that the surfNormal is reset to the ground
        VectorCopy( refNormal, pm->ps->grapplePoint );


        // if the trace didn't hit anything, we are in free fall
        if ( trace.fraction == 1.0 ) {
                PM_GroundTraceMissed();
                pml.groundPlane = qfalse;
                pml.walking = qfalse;
                return;
        }

        // check if getting thrown off the ground
        if ( pm->ps->velocity[2] > 0 && DotProduct( pm->ps->velocity, trace.plane.normal ) > 10 ) {
                if ( pm->debugLevel ) {
                        Com_Printf("%i:kickoff\n", c_pmove);
                }
                // go into jump animation
                if ( pm->cmd.forwardmove >= 0 ) {
                        PM_ForceLegsAnim( LEGS_JUMP );
                        pm->ps->pm_flags &= ~PMF_BACKWARDS_JUMP;
                } else {
                        PM_ForceLegsAnim( LEGS_JUMPB );
                        pm->ps->pm_flags |= PMF_BACKWARDS_JUMP;
                }

                pm->ps->groundEntityNum = ENTITYNUM_NONE;
                pml.groundPlane = qfalse;
                pml.walking = qfalse;
                return;
        }

        // slopes that are too steep will not be considered onground
        if ( trace.plane.normal[2] < MIN_WALK_NORMAL ) {
                if ( pm->debugLevel ) {
                        Com_Printf("%i:steep\n", c_pmove);
                }
                // FIXME: if they can't slide down the slope, let them
                // walk (sharp crevices)
                pm->ps->groundEntityNum = ENTITYNUM_NONE;
                pml.groundPlane = qtrue;
                pml.walking = qfalse;
                return;
        }

        pml.groundPlane = qtrue;
        pml.walking = qtrue;

        // hitting solid ground will end a waterjump
        if (pm->ps->pm_flags & PMF_TIME_WATERJUMP)
        {
                pm->ps->pm_flags &= ~(PMF_TIME_WATERJUMP | PMF_TIME_LAND);
                pm->ps->pm_time = 0;
        }

        if ( pm->ps->groundEntityNum == ENTITYNUM_NONE ) {
                // just hit the ground
                if ( pm->debugLevel ) {
                        Com_Printf("%i:Land\n", c_pmove);
                }

                PM_CrashLand();

                // don't do landing time if we were just going down a slope
                if ( pml.previous_velocity[2] < -200 ) {
                        // don't allow another jump for a little while
                        pm->ps->pm_flags |= PMF_TIME_LAND;
                        pm->ps->pm_time = 250;
                }
        }

        pm->ps->groundEntityNum = trace.entityNum;

        // don't reset the z velocity for slopes
//      pm->ps->velocity[2] = 0;

        PM_AddTouchEnt( trace.entityNum );
}


/*
=============
PM_SetWaterLevel        FIXME: avoid this twice?  certainly if not moving
=============
*/
static void PM_SetWaterLevel( void ) {
        vec3_t          point;
        int                     cont;
        int                     sample1;
        int                     sample2;

        //
        // get waterlevel, accounting for ducking
        //
        pm->waterlevel = 0;
        pm->watertype = 0;

        point[0] = pm->ps->origin[0];
        point[1] = pm->ps->origin[1];
        point[2] = pm->ps->origin[2] + MINS_Z + 1;
        cont = pm->pointcontents( point, pm->ps->clientNum );

        if ( cont & MASK_WATER ) {
                sample2 = pm->ps->viewheight - MINS_Z;
                sample1 = sample2 / 2;

                pm->watertype = cont;
                pm->waterlevel = 1;
                point[2] = pm->ps->origin[2] + MINS_Z + sample1;
                cont = pm->pointcontents (point, pm->ps->clientNum );
                if ( cont & MASK_WATER ) {
                        pm->waterlevel = 2;
                        point[2] = pm->ps->origin[2] + MINS_Z + sample2;
                        cont = pm->pointcontents (point, pm->ps->clientNum );
                        if ( cont & MASK_WATER ){
                                pm->waterlevel = 3;
                        }
                }
        }

}

/*
==============
PM_CheckDuck

Sets mins, maxs, and pm->ps->viewheight
==============
*/
static void PM_CheckDuck (void)
{
        trace_t trace;

        pm->mins[0] = -15;
        pm->mins[1] = -15;

        pm->maxs[0] = 15;
        pm->maxs[1] = 15;

        pm->mins[2] = MINS_Z;

        if (pm->ps->pm_type == PM_DEAD)
        {
                pm->maxs[2] = -8;
                pm->ps->viewheight = DEAD_VIEWHEIGHT;
                return;
        }

        if (pm->cmd.upmove < 0)
        {       // duck
                pm->ps->pm_flags |= PMF_DUCKED;
        }
        else
        {       // stand up if possible
                if (pm->ps->pm_flags & PMF_DUCKED)
                {
                        // try to stand up
                        pm->maxs[2] = PLAYER_STANDHEIGHT; //was 32. blud: need this or your head gets stuck in ceilings when you duck and stand up at low ceilings
                        pm->trace (&trace, pm->ps->origin, pm->mins, pm->maxs, pm->ps->origin, pm->ps->clientNum, pm->tracemask );
                        if (!trace.allsolid)
                                pm->ps->pm_flags &= ~PMF_DUCKED;
                }
        }

        if (pm->ps->pm_flags & PMF_DUCKED)
        {
				//blud fixing player height
                pm->maxs[2] = PLAYER_CROUCHHEIGHT; //was 16
                pm->ps->viewheight = CROUCH_VIEWHEIGHT;
        }
        else
        {


				//blud fixing player height
                pm->maxs[2] = PLAYER_STANDHEIGHT; //was 32
                pm->ps->viewheight = DEFAULT_VIEWHEIGHT;
        }
        
		//Xamis's attempt to stop jumping head through ceilings. But it causes duck height to always be 40!
       // if (pm->ps->pm_flags & ~PMF_ONGROUND ){
       //  pm->maxs[2] = 40;
       //  
       // }
        
        
}



//===================================================================


/*
===============
PM_Footsteps
===============
*/
static void PM_Footsteps( void ) {
        float           bobmove;
        int             xyzspeed;
        int                     old;
        qboolean        footstep;
        footstep = qfalse;


        //
        // calculate speed and cycle to be used for
        // all cyclic walking effects
        //
        pm->xyspeed = sqrt( pm->ps->velocity[0] * pm->ps->velocity[0]
                +  pm->ps->velocity[1] * pm->ps->velocity[1] );

        xyzspeed = sqrt( pm->ps->velocity[0] * pm->ps->velocity[0]
                        +  pm->ps->velocity[1] * pm->ps->velocity[1]
                        +  pm->ps->velocity[2] * pm->ps->velocity[2] );
   if ( CheckLadder() != 0 )     
   {
            pm->ps->pm_flags |= PMF_ONLADDER;
        // moving up or down)
                if ( xyzspeed ) {
                  bobmove = 0.3f;
                  PM_ContinueTorsoAnim ( BOTH_CLIMB );
                  PM_ContinueLegsAnim  ( BOTH_CLIMB );
                        footstep = qtrue; //not sure why this isn't working, need more testing

                }
                else {
                  PM_ContinueTorsoAnim ( BOTH_CLIMB_IDLE );
                  PM_ContinueLegsAnim  ( BOTH_CLIMB_IDLE );

                        footstep = qfalse;
                        return;
                }

        }


        if ( pm->ps->groundEntityNum == ENTITYNUM_NONE &&   CheckLadder() == 0) {


                // airborne leaves position in cycle intact, but doesn't advance
                if ( pm->waterlevel > 1 ) {
                        PM_ContinueLegsAnim( LEGS_SWIM );
                }
                return;
        }

        if ( bg_ps.bg_flags[pm->ps->clientNum] & BGF_POWERSLIDE ) {
          PM_ContinueLegsAnim( LEGS_IDLECR );
          return;
        }

        // if not trying to move
        if ( !pm->cmd.forwardmove && !pm->cmd.rightmove ) {
                if (  pm->xyspeed < 5 ) {
                        pm->ps->bobCycle = 0;   // start at beginning of cycle again
                        if ( pm->ps->pm_flags & PMF_DUCKED ) {
                                PM_ContinueLegsAnim( LEGS_IDLECR );
                        } else {
                                PM_ContinueLegsAnim( LEGS_IDLE );
                        }
                }
                return;
        }


footstep = qfalse;

        if ( pm->ps->pm_flags & PMF_DUCKED ) {
                bobmove = 0;    // dont bob while crouched --Xamis Value was .5

                 if ( pm->ps->pm_flags & PMF_BACKWARDS_RUN ) {
                        PM_ContinueLegsAnim( LEGS_BACKCR );
                }
                else {
                        PM_ContinueLegsAnim( LEGS_WALKCR );
                }
                // ducked characters never play footsteps
        /*
        } else  if ( pm->ps->pm_flags & PMF_BACKWARDS_RUN ) {
                if ( !( pm->cmd.buttons & BUTTON_WALKING ) ) {
                        bobmove = 0.4;  // faster speeds bob faster
                        footstep = qtrue;
                } else {
                        bobmove = 0.3;
                }
                PM_ContinueLegsAnim( LEGS_BACK );
        */
        } else {
                if ( !( pm->cmd.buttons & BUTTON_WALKING ) ) {
                        bobmove = 0.4f; // faster speeds bob faster
                        if ( pm->ps->pm_flags & PMF_BACKWARDS_RUN ) {
                              if ( pm->ps->stats[STAT_DMG_LOC] & ( 1 << LEG_DAMAGE )  ) {
                                PM_ContinueLegsAnim( LEGS_BACKLIMP );
                                }else
                                PM_ContinueLegsAnim( LEGS_BACK );
                        }
                        else {
                              if ( pm->ps->stats[STAT_DMG_LOC] & ( 1 << LEG_DAMAGE )  ) {
                                PM_ContinueLegsAnim( LEGS_LIMP );
                                }else
                                PM_ContinueLegsAnim( LEGS_RUN );
                        }
                        footstep = qtrue;
                } else {
                        bobmove = 0.3f; // walking bobs slow
                        if ( pm->ps->pm_flags & PMF_BACKWARDS_RUN ) {
                             if ( pm->ps->stats[STAT_DMG_LOC] & ( 1 << LEG_DAMAGE )  ) {
                                PM_ContinueLegsAnim( LEGS_BACKLIMP );
                                }else
                                PM_ContinueLegsAnim( LEGS_BACKWALK );
                        }
                        else if ( pm->ps->stats[STAT_DMG_LOC] & ( 1 << LEG_DAMAGE )  ) {
                        PM_ContinueLegsAnim( LEGS_LIMP );
                        } else{
                                PM_ContinueLegsAnim( LEGS_WALK );
                        }
                }
        }



        // check for footstep / splash sounds
        old = pm->ps->bobCycle;
        pm->ps->bobCycle = (int)( old + bobmove * pml.msec ) & 255;

        // if we just crossed a cycle boundary, play an apropriate footstep event
        if ( ( ( old + 64 ) ^ ( pm->ps->bobCycle + 64 ) ) & 128 ) {
                if ( pm->waterlevel == 0 ) {
                        // on ground will only play sounds if running
                        if ( footstep && !pm->noFootsteps ) {
                                PM_AddEvent( PM_FootstepForSurface() );
                        }
                } else if ( pm->waterlevel == 1 ) {
                        // splashing
                        PM_AddEvent( EV_FOOTSPLASH );
                } else if ( pm->waterlevel == 2 ) {
                        // wading / swimming at surface
                        PM_AddEvent( EV_SWIM );
                } else if ( pm->waterlevel == 3 ) {
                        // no sound when completely underwater

                }
        }
}

/*
==============
PM_WaterEvents

Generate sound events for entering and leaving water
==============
*/
static void PM_WaterEvents( void ) {            // FIXME?
        //
        // if just entered a water volume, play a sound
        //
        if (!pml.previous_waterlevel && pm->waterlevel) {
                PM_AddEvent( EV_WATER_TOUCH );
        }

        //
        // if just completely exited a water volume, play a sound
        //
        if (pml.previous_waterlevel && !pm->waterlevel) {
                PM_AddEvent( EV_WATER_LEAVE );
        }

        //
        // check for head just going under water
        //
        if (pml.previous_waterlevel != 3 && pm->waterlevel == 3) {
                PM_AddEvent( EV_WATER_UNDER );
        }

        //
        // check for head just coming out of water
        //
        if (pml.previous_waterlevel == 3 && pm->waterlevel != 3) {
                PM_AddEvent( EV_WATER_CLEAR );
        }
}




/*
===============
PM_BeginWeaponChange
===============
*/
static void PM_BeginWeaponChange( int weapon ) {
  if ( weapon <= WP_NONE || weapon >= WP_NUM_WEAPONS ) {
                return;
        }


        if ( !( BG_HasWeapon( weapon, pm->ps->stats ) ) ) {
        //  Com_Printf("!( BG_HasWeapon( weapon, pm->ps->stats ) )weapon = %i\n", weapon );
          return;
        }

        if ( pm->ps->weaponstate == WEAPON_DROPPING ) {
                return;
        }

       // PM_AddEvent( EV_CHANGE_WEAPON );
        pm->ps->weaponstate = WEAPON_DROPPING;
        pm->ps->weaponTime +=300;
        PM_StartTorsoAnim( TORSO_DROP );
        pm->ps->torsoTimer +=300;
}


/*
===============
PM_FinishWeaponChange
===============
*/
static void PM_FinishWeaponChange( void ) {
        int             weapon;

        weapon = pm->cmd.weapon;
        if ( weapon < WP_NONE || weapon > WP_NUM_WEAPONS ) {
                weapon = WP_NONE;
        }

        if ( !( BG_HasWeapon( weapon, pm->ps->stats ) ) ) {
          return;
        }

       if ( pm->ps->weaponstate == WEAPON_RAISING ) {
                return;
        }
        pm->ps->pm_flags &= ~PMF_GRENADE_ARMED;
        pm->ps->stats[STAT_NADE_FUSE] = 6000;
        //bg_nadeTimer.fuseTime[pm->ps->clientNum] = 6000;
        pm->ps->weapon = weapon;
        pm->ps->weaponstate = WEAPON_RAISING;        
        pm->ps->weaponTime +=300;
        pm->ps->torsoTimer +=300;
       //PM_StartWeaponAnim(WPN_DRAW);
        //pm->ps->weaponTime +=300;
        //pm->ps->torsoTimer +=300;
        PM_StartTorsoAnim( TORSO_RAISE );
        PM_AddEvent( EV_CHANGE_WEAPON );
}


/*
==============
PM_TorsoAnimation

==============
*/
static void PM_TorsoAnimation( void ) {
    
    if (pm->ps->pm_flags & PMF_EDGE)
                return;
    
    
        if ( pm->ps->weaponstate == WEAPON_READY ) {
          if ( pm->ps->weapon == WP_KNIFE || BG_Grenade(pm->ps->weapon) ) {
                        PM_ContinueTorsoAnim( TORSO_STAND2 );
                } else if ( BG_Sidearm(pm->ps->weapon)){
                  PM_StartTorsoAnim( TORSO_STAND_PISTOL );
                }else{
                        PM_ContinueTorsoAnim( TORSO_STAND );
                }
                // QUARANTINE - Weapon Animation
// Should always draw the weapon when it is just ready
               if (BG_Grenade( pm->ps->weapon )|| pm->ps->weapon == WP_HK69){
            //     PM_ContinueWeaponAnim(WPN_READY_FIRE_IDLE);
                   return;
                }else
                if ( (pm->ps->weapon == WP_KNIFE ) 
			&& pm->ps->stats[STAT_MODE]
			&& pm->ps->pm_flags & ~PMF_GRENADE_ARMED ){
                   return; //PM_ContinueWeaponAnim( WPN_IDLE_ALT );
                }else
		if ( (pm->ps->weapon == WP_KNIFE )
                        && pm->ps->stats[STAT_MODE]
                        && pm->ps->pm_flags & PMF_GRENADE_ARMED ){
                   return; //PM_ContinueWeaponAnim( WPN_READY_FIRE_IDLE_ALT );
                }else
                PM_ContinueWeaponAnim( WPN_IDLE );


                return;
        }
}


/*
==================
  ReloadTime for Cmd_Reload  --Xamis
==================
*/
int ReloadTime( int w )        {
  switch ( w ){
    case WP_AK103:
      return 3450;
      break;
    case WP_MP5K:
      return 2570;
      break;
    case WP_UMP45:
      return 2740;
    case WP_M4:
    case WP_LR300:
      return 2530;
      break;
    case WP_G36:
      return 2400;
      break;
    case WP_SPAS:
      return 800;
      break;
    case WP_SR8:
      return 1510;
      break;
    case WP_PSG1:
      return 3000;
      break;
    case WP_DEAGLE:
      return 3300;
      break;
    case WP_BERETTA:
      return 1700;
      break;
    case WP_NEGEV:
      return 285;
      break;
    case WP_HE:
      return 800;
      break;
    default:
      return 3000;
  }

}

int ReloadStartTime( int w )        {
  switch ( w ){
    case WP_SPAS:
      return 100;
      break;
    case WP_NEGEV:
      return 1760;
      break;
    default:
      return 0;
  }

}
int ReloadEndTime( int w )        {
  switch ( w ){
    case WP_SR8:
      return 1500;
      break;
    case WP_SPAS:
      return 800;
      break;
    case WP_NEGEV:
      return 5190;
      break;
    case WP_HE:
      return 500;
      break;
    default:
      return 0;
  }

}

qboolean PM_HasDrawAnimation( int weapon ){
    
     switch( weapon ) {
        default:
            
        case WP_KNIFE:
        case WP_BERETTA:
        case WP_DEAGLE:                                       
        case WP_M4:
            return qtrue;
            break;        
        case WP_MP5K:
        case WP_LR300:
        case WP_G36:
        case WP_SPAS:
        case WP_PSG1:
        case WP_SR8:
        case WP_UMP45:
        case WP_NEGEV:
        case WP_AK103:
        case WP_HK69:
        case WP_HE:
        case WP_SMOKE:
            return qfalse;
        }    
}

/*
==============
PM_Weapon

Generates weapon events and modifes the weapon counter
==============
*/
static int PM_WeaponTime( int weapon, int mode  )
{
        int addTime;
        switch( weapon ) {
        default:
        case WP_KNIFE:
                addTime = 400;
                break;
                case WP_MP5K:
                case WP_M4:
                case WP_LR300:
                        addTime = 122;
                        break;
                case WP_G36:
                        addTime = 130;
                        break;
                case WP_SPAS:
                        addTime = 500;
                        break;
                case WP_PSG1:
                        addTime = 500;
                        break;
                case WP_SR8:
                        addTime = 1000; //Xamis, changed to accomodate bolt animation
                        break;
                case WP_UMP45:
	 if( mode )
	     addTime = 150;
	else
                        addTime = 45;
                        break;
                case WP_DEAGLE:
                        addTime = 140;
                        break;
                case WP_BERETTA:
                        addTime = 100;
                        break;
                case WP_NEGEV:
                case WP_AK103:
                        addTime = 125; //blud changed from 150
                        break;
                case WP_HK69:
                        addTime = 3000;
                        break;
                case WP_HE:
                case WP_SMOKE:
                        addTime = 3000;
                        break;
        }return addTime;
}


void BG_LastKnife(void){
    pm->ps->weaponstate = WEAPON_TONORMAL;
}


qboolean isInBurst( pmove_t *pm ){
     
    
    //Com_Printf("pm->ps->stats[STAT_MODE]  is %i\n ", pm->ps->stats[STAT_MODE]); //xamis debug
    
    if (pm->ps->stats[STAT_MODE] ){
        return qfalse;
    }
    if( !
            (pm->ps->weapon == WP_LR300 ||
            pm->ps->weapon ==WP_M4 ||
            pm->ps->weapon ==WP_G36 ||
            pm->ps->weapon ==WP_AK103 ||
            pm->ps->weapon ==WP_UMP45 ||
            pm->ps->weapon ==WP_MP5K )  ){
        return qfalse;
    }
    
   if(   pm->ps->stats[STAT_BURST_COUNT]  <= 0 ){
       return qfalse;
   }
    
      return qtrue;    
}





qboolean PM_Reload(void){
    
	if( pm->ps->weapon == WP_KNIFE){
		return qfalse;
	}    

    
         if ( pm->ps->pm_flags & PMF_RELOADING ){
           //PM_AddEvent( EV_ZOOM_RESET );
          PM_StartWeaponAnim( WPN_BOLT);
          if ( pm->ps->weapon == WP_SR8)
            pm->ps->weaponTime = 1500;
          if ( pm->ps->weapon == WP_SPAS){
            pm->ps->weaponTime = 200;
            PM_AddEvent(EV_EJECT_CASING);
          }
          pm->ps->pm_flags &= ~PMF_RELOADING;

          return qtrue;
        }
    /*
 Weapon reloading start
 weaponstate == WEAPON_RELOADING_START
 
 */            
        if ( pm->ps->weaponstate == WEAPON_RELOADING_START ) {

              if(pm->ps->weapon == WP_SR8 || 
            pm->ps->weapon == WP_PSG1 || 
            pm->ps->weapon == WP_G36  ){
            PM_AddEvent( EV_ZOOM_RESET );       
            pm->ps->weaponstate =WEAPON_RELOADING_ZOOM_RESET;
            pm->ps->weaponTime = 200;
              }else{
          pm->ps->weaponTime = ReloadStartTime( pm->ps->weapon );
          pm->ps->weaponstate = WEAPON_RELOADING;
          if ( pm->ps->weapon == WP_NEGEV || pm->ps->weapon == WP_SPAS ){
            PM_StartWeaponAnim( WPN_RELOAD_START );

          }
         }            return qtrue;
        }
        
          
         
         
         
       if ( pm->ps->weaponstate == WEAPON_RELOADING_ZOOM_RESET ) {

          pm->ps->weaponTime = 200;
          pm->ps->weaponstate = WEAPON_RELOADING;
            return qtrue;
        }
        
/*
 Weapon reloading
 weaponstate == WEAPON_RELOADING
 
 */
         
            
        if ( pm->ps->weaponstate == WEAPON_RELOADING && pm->ps->weaponTime <= 0 ) {

          pm->ps->weaponTime = ReloadTime( pm->ps->weapon );
          
          if ( pm->ps->weapon == WP_SPAS ){

            bg_weaponlist[pm->ps->weapon].rounds[pm->ps->clientNum]++;
            bg_weaponlist[pm->ps->weapon].numClips[pm->ps->clientNum]--;

          }
          if ( pm->cmd.buttons & BUTTON_RELOAD 
                  && pm->ps->weapon == WP_SPAS 
                  &&  bg_weaponlist[pm->ps->weapon].rounds[pm->ps->clientNum] < 8 
                  &&  bg_weaponlist[pm->ps->weapon].numClips[pm->ps->clientNum] > 0){
          pm->ps->weaponstate = WEAPON_RELOADING;
          }else{
          pm->ps->weaponstate = WEAPON_RELOADING_END;
          }
          
          PM_StartWeaponAnim( WPN_RELOAD );
          pm->ps->stats[STAT_BURST_COUNT]=0;

          if (BG_Sidearm( pm->ps->weapon )){
          PM_StartTorsoAnim(TORSO_RELOAD_PISTOL );
          }else if (!(pm->ps->weapon == WP_SPAS || BG_Grenade( pm->ps->weapon )) ){
          PM_StartTorsoAnim(TORSO_RELOAD_RIFLE );
          }
        }
        
        
/*
 Weapon reloading end
 weaponstate == WEAPON_RELOADING_END
 
 */
                    
        if( pm->ps->weaponstate == WEAPON_RELOADING_END && pm->ps->weaponTime <= 0 ) {
          pm->ps->weaponTime = ReloadEndTime( pm->ps->weapon );
          pm->ps->weaponstate = WEAPON_RELOADING_COMPLETE;
          if (BG_Grenade( pm->ps->weapon)){
            PM_StartWeaponAnim(WPN_READY_FIRE_IDLE);
            return qtrue;
          }
          if ( pm->ps->weapon == WP_NEGEV || pm->ps->weapon == WP_SPAS){
            PM_ContinueWeaponAnim( WPN_RELOAD_END );
          }if ( pm->ps->weapon == WP_SR8 ){
           PM_ContinueWeaponAnim( WPN_BOLT );
          }
        }
        
/*
 Weapon reloading complete
 weaponstate == WEAPON_RELOADING_COMPLETE
 
 */
                            
        
        if( pm->ps->weaponstate == WEAPON_RELOADING_COMPLETE && pm->ps->weaponTime <= 0 ) {
          if (BG_Grenade( pm->ps->weapon)){
            PM_ContinueWeaponAnim(WPN_READY_FIRE_IDLE);
          }
          pm->ps->weaponstate = WEAPON_READY; //If were in finished reloading, we're ready to fire, so set weaponstate
        }
        

       return qfalse;
    
    
}



qboolean PM_Grenade(void){
	
	//i was trying to figure out about the bg_weaponlist numClips 2 0 2 0 0 2 0 0 0 2 mystery:
	//Com_Printf("CLIPS:%i\n", pm->ps->stats[STAT_CLIPS] );
	//	Com_Printf("THISGUNCLIPS:%i\n", bg_weaponlist[pm->ps->weapon].numClips[pm->ps->clientNum] );
	//Com_Printf("HEVAL: %i HEs:%i Client: %i\n", WP_HE, bg_weaponlist[WP_HE].numClips[pm->ps->clientNum], pm->ps->clientNum );

	//if(pm->ps->stats[STAT_CLIPS] <= 0 && BG_Grenade(pm->ps->weapon) ){ <-- used to be this. We added the weaponTime to make sure that the weapon had fully switched first
		//because if it hadn't then STAT_CLIPS would be from the previous gun!
	

        if( pm->ps->weapon == WP_KNIFE){
                return qfalse;
        }


	if(pm->ps->stats[STAT_CLIPS] <= 0 && BG_Grenade(pm->ps->weapon) && pm->ps->weaponTime <=0 ){
         PM_AddEvent( EV_NONADES );
        }

            //check grenade fuse time
        if ( pm->ps->stats[STAT_NADE_FUSE]  > 0 && pm->ps->pm_flags & PMF_GRENADE_ARMED){
          pm->ps->stats[STAT_NADE_FUSE] -= pml.msec; //count down for the fuse
        bg_nadeTimer.fuseTime[pm->ps->clientNum] = pm->ps->stats[STAT_NADE_FUSE]; 
        }else if (  pm->ps->stats[STAT_NADE_FUSE]   <= 0 ){ 
          bg_nadeTimer.fuseTime[pm->ps->clientNum] = 0;
           pm->ps->stats[STAT_NADE_FUSE] = 0;
          if(BG_Grenade(pm->ps->weapon) && pm->ps->pm_flags & PMF_GRENADE_ARMED){ //we held the grenade too long!
            bg_nadeTimer.throwStrength[pm->ps->clientNum]= 0;
            pm->ps->weaponTime = 0;
            PM_AddEvent( EV_FIRE_WEAPON ); //BOOM!
            pm->ps->pm_flags &= ~PMF_GRENADE_ARMED;
            return qtrue;
        }
     }


        if ( bg_nadeTimer.throwStrength[pm->ps->clientNum] < 80000 )
          bg_nadeTimer.throwStrength[pm->ps->clientNum]+= pml.msec;
        if ( bg_nadeTimer.throwStrength[pm->ps->clientNum] > 80000 )
          bg_nadeTimer.throwStrength[pm->ps->clientNum]= 80000;


        return qfalse;    
    
}


qboolean PM_Bandage(void){
    
    
            //If were in the process of bandaging we can't fire  --Xamis
       if ( (pm->ps->weaponstate == WEAPON_DOWN_BANDAGING || pm->ps->weaponstate == WEAPON_DOWN_BANDAGING_OTHER) && pm->ps->weaponTime > 0 ) {

                return qtrue;
        }
        
               if ( pm->ps->weaponstate == WEAPON_DOWN_BANDAGING && pm->ps->weaponTime <= 0 ) {
                   pm->ps->pm_flags &=  ~ PMF_BLEEDING;
                    pm->ps->stats[STAT_DMG_LOC] =0;
                   pm->ps->weaponstate = WEAPON_READY;
        }
        
               if ( pm->ps->weaponstate == WEAPON_DOWN_BANDAGING_OTHER && pm->ps->weaponTime <= 0 ) {
                           pm->ps->weaponstate = WEAPON_READY;
                }
        
       if ( pm->ps->weaponstate == WEAPON_START_BANDAGING ) {
                   pm->ps->weaponTime = 3000;
                   PM_StartTorsoAnim( TORSO_BANDAGE );
                   pm->ps->weaponstate = WEAPON_DOWN_BANDAGING;
                   PM_AddEvent( EV_BANDAGE);
          }
               if ( pm->ps->weaponstate == WEAPON_START_BANDAGING_OTHER) {
                   pm->ps->weaponTime = 2000;
                   PM_StartTorsoAnim( TORSO_BANDAGE );
                   pm->ps->weaponstate = WEAPON_DOWN_BANDAGING_OTHER;
                   PM_AddEvent( EV_BANDAGE);
          }
    
       return qfalse;
}






static void PM_Weapon( void ) {


        if ( pm->ps->pm_flags & PMF_RESPAWNED ) {
                return;
        }
        if ( pm->ps->pm_type == PM_SPECTATOR || pm->ps->pm_type == PM_NOCLIP ) {
                return;
        }
        if ( pm->ps->stats[STAT_HEALTH] <= 0 ) {
                pm->ps->weapon = WP_NONE;
                return;
        }

        if( pm->ps->legsAnim == BOTH_LEDGECLIMB )
		return;

        
    //if player has thrown the last nade in their inventory, remove it.        

        
    // make weapon function
        if ( pm->ps->weaponTime > 0 )
        pm->ps->weaponTime -= pml.msec;
        if ( pm->ps->weaponTime <= 0 )
          pm->ps->weaponTime = 0;
        
        
       if (PM_Grenade())
            return;
        
      // if ( pm->ps->weaponstate == WEAPON_READY_FIRE_ALT && pm->ps->weaponTime > 0 ) {
      //          return;
      //  }

        if( pm->ps->weaponstate ==  WEAPON_FIRING2 && pm->ps->weaponTime > 0){
                           return;
           }
        
        
                
        if( pm->ps->weaponstate ==  WEAPON_FIRING2){
               pm->ps->weaponstate = WEAPON_FIRING;
                           PM_AddEvent( EV_ZOOM_RESET );
                           pm->ps->weaponTime = 200;
                           return;
           }
        
//      if (pm->ps->weapon == WP_KNIFE && ( pm->ps->weaponstate == WEAPON_TOALTERNATE ||pm->ps->weaponstate == WEAPON_TONORMAL)&& pm->ps->weaponTime <= 0)
//           pm->ps->weaponstate = WEAPON_READY;
       
      if ( pm->ps->weaponstate == WEAPON_TOALTERNATE ) {
          pm->ps->weaponTime +=1000;
          PM_StartWeaponAnim( WPN_TOALTERNATE );
          pm->ps->weaponstate = WEAPON_READY;
          return;
          
        }
      
            if ( pm->ps->weaponstate == WEAPON_TONORMAL ) {
          pm->ps->weaponTime += 1000;
          PM_StartWeaponAnim( WPN_TONORMAL );
          pm->ps->weaponstate = WEAPON_READY;
          return;
        }
        
          if ( pm->ps->weaponstate ==WEAPON_READY_FIRE_IDLE_ALT&& pm->ps->weaponTime <= 0 ) {
              if(pm->ps->weapon==WP_KNIFE ){
             PM_ContinueWeaponAnim(WPN_READY_FIRE_IDLE_ALT);
              }
              else{
              PM_StartWeaponAnim(WPN_READY_FIRE_IDLE);    
              }
          }
      

        
        

        
        
       if (PM_Reload() )
           return;
        

        
        if( PM_Bandage())
            return;
        
        

   if ( pm->ps->weaponTime > 0 ) {
                return;
  }                        

if ((pm->cmd.buttons & 1) ) {


           if(pm->ps->weapon==WP_KNIFE && pm->ps->stats[STAT_MODE]  && pm->ps->pm_flags & PMF_GRENADE_ARMED ){
            pm->ps->weaponTime += 50;
            PM_ContinueWeaponAnim(WPN_READY_FIRE_IDLE_ALT);
            return;
          }


           if(BG_Grenade(pm->ps->weapon) && pm->ps->pm_flags & PMF_GRENADE_ARMED ){
                          pm->ps->weaponTime += 50;
            PM_ContinueWeaponAnim(WPN_READY_FIRE_IDLE);
            return;
          }
          

}
        
  

    // check for weapon change
    // can't change if weapon is firing, but can change
    // again if lowering or raising
        if ( pm->ps->weaponstate == WEAPON_READY ) {
                if ( pm->ps->weapon != pm->cmd.weapon) {
                  PM_BeginWeaponChange( pm->ps->weapon );
                        return;
                }
        }

    // change weapon if time
        if ( pm->ps->weaponstate == WEAPON_DROPPING &&  pm->ps->weaponTime <= 0) {
                PM_FinishWeaponChange();
                 return;
        }
            
            
        if ( pm->ps->weaponstate == WEAPON_RAISING &&  pm->ps->weaponTime <= 0 ) {
                pm->ps->weaponstate = WEAPON_READY;
                if ( pm->ps->weapon == WP_KNIFE || BG_Grenade(pm->ps->weapon ) ) {
                  PM_StartTorsoAnim( TORSO_STAND2 );
                } else if ( BG_Sidearm(pm->ps->weapon)){
                  PM_StartTorsoAnim( TORSO_STAND_PISTOL );
                }else{
                  PM_StartTorsoAnim( TORSO_STAND );
                }


                if ( (pm->ps->weapon == WP_KNIFE || pm->ps->weapon == WP_HK69)&& pm->ps->stats[STAT_MODE] ){

                    PM_StartWeaponAnim( WPN_IDLE_ALT );
                }else
                PM_StartWeaponAnim( WPN_IDLE );
                pm->ps->stats[STAT_BURST_COUNT] =0;
                return;
        }
   //    if( pm->ps->eFlags & ~EF_WEAPONS_LOCKED){



//fire not pressed
        if (!(pm->cmd.buttons & 1  )&& !isInBurst(pm) ) {
            bg_weaponlist[0].numClips[pm->ps->clientNum] = 0; //for round increment count for spread/recoil
            pm->ps->stats[STAT_BURST_COUNT]  = 0;
            
          if(BG_Grenade(pm->ps->weapon) && pm->ps->pm_flags & PMF_GRENADE_ARMED){//we let go of fire do we have a grenade armed?
            PM_StartWeaponAnim( WPN_FIRE );
            pm->ps->weaponstate = WEAPON_FIRING;
            pm->ps->weaponTime = 200;
            PM_AddEvent( EV_FIRE_WEAPON );
            PM_StartTorsoAnim( TORSO_ATTACK_GRENADE );
            pm->ps->pm_flags &= ~PMF_GRENADE_ARMED;
            return;
          }else if ( pm->ps->weapon == WP_KNIFE && pm->ps->stats[STAT_MODE]&& pm->ps->pm_flags & PMF_GRENADE_ARMED ){ //fire released, knife throw
            PM_StartWeaponAnim( WPN_FIRE_ALT );
            pm->ps->weaponstate = WEAPON_FIRING;
            pm->ps->weaponTime = PM_WeaponTime(pm->ps->weapon ,pm->ps->stats[STAT_MODE] );
            PM_AddEvent( EV_FIRE_WEAPON );
            PM_StartTorsoAnim( TORSO_ATTACK_GRENADE );
            pm->ps->pm_flags &= ~PMF_GRENADE_ARMED;
            return;
              
          }else    {
                pm->ps->weaponTime = 0;
                pm->ps->weaponstate = WEAPON_READY;

                if (( pm->ps->weapon == WP_KNIFE || pm->ps->weapon == WP_HK69 )&& pm->ps->stats[STAT_MODE] ){
                    PM_StartWeaponAnim( WPN_IDLE_ALT );
                }else
                PM_StartWeaponAnim( WPN_IDLE );

        // fire not pressed so remove single flag, reset burst count and spread count
                if ( pm->ps->pm_flags & PMF_SINGLE_SHOT ){
                        pm->ps->pm_flags &= ~PMF_SINGLE_SHOT;                     
                        bg_weaponlist[0].numClips[pm->ps->clientNum] = 0;
                        pm->ps->stats[STAT_BURST_COUNT] =0;
                }
                return;
          }
        }
      
       // grenade ready to throw animation
        if(BG_Grenade(pm->ps->weapon) && pm->ps->pm_flags & PMF_GRENADE_ARMED ){
                      pm->ps->weaponTime = 50;
          PM_StartWeaponAnim(WPN_READY_FIRE_IDLE);
          return;
        }
        // knife ready to throw animation
        if(pm->ps->weapon == WP_KNIFE && pm->ps->stats[STAT_MODE] && pm->ps->pm_flags & PMF_GRENADE_ARMED ){
          pm->ps->weaponTime = 50;
          PM_StartWeaponAnim(WPN_READY_FIRE_IDLE_ALT);
          return;
        }

    // single shot mode, exit! no more shots while fire held
        if ( pm->ps->pm_flags & PMF_SINGLE_SHOT ) {
                pm->ps->weaponstate = WEAPON_READY;
                pm->ps->weaponTime = 0;
                return;
        }

                                // check for out of ammo
        if ( (pm->ps->stats[STAT_ROUNDS] <= 0 && !BG_Grenade(pm->ps->weapon))
            || (pm->ps->stats[STAT_CLIPS] <= 0 && BG_Grenade(pm->ps->weapon) )) {
            pm->ps->stats[STAT_BURST_COUNT] =0;
          PM_AddEvent( EV_NOAMMO );
          pm->ps->weaponTime = 550;
          pm->ps->weaponstate = WEAPON_READY;
           if ( pm->ps->weapon == WP_HK69 && pm->ps->stats[STAT_MODE] ){
                PM_ContinueWeaponAnim( WPN_FIRE_ALT );
                return;
         }else  
          PM_ContinueWeaponAnim( WPN_IDLE );
          return;
            }
        
        //press fire when holding grenade, grenade not armed yet
            if ( BG_Grenade(pm->ps->weapon) && !(pm->ps->pm_flags & PMF_GRENADE_ARMED)){
              pm->ps->weaponstate =WEAPON_READY_FIRE_IDLE_ALT ; 
              pm->ps->pm_flags |= PMF_GRENADE_ARMED; //pin pulled
              bg_nadeTimer.fuseTime[pm->ps->clientNum] = 6000; //start fuse countdown
              pm->ps->stats[STAT_NADE_FUSE]= 6000; //start fuse countdown
              bg_nadeTimer.throwStrength[pm->ps->clientNum] = 62000; 
              PM_StartWeaponAnim( WPN_READY_FIRE ); //animation. pull pin and pull arm back
              pm->ps->weaponTime = 800;             
              return;
            }
        
        
        // PMF_GRENADE_ARMED used for both grenade and knife throwing. should probably rename  PMF_ARMED or something.
        if (pm->ps->weapon == WP_KNIFE && pm->ps->stats[STAT_MODE] && !(pm->ps->pm_flags & PMF_GRENADE_ARMED)){
              pm->ps->weaponstate =WEAPON_READY_FIRE_IDLE_ALT ; //holding the weapon in the ready to throw position 
              pm->ps->pm_flags |= PMF_GRENADE_ARMED;
              PM_StartWeaponAnim( WPN_READY_FIRE_ALT );
              pm->ps->weaponTime = 800; 
              return;
            }


//start a torso animation to match our weapon animations
        if ( BG_Sidearm(pm->ps->weapon)){
          PM_StartTorsoAnim( TORSO_ATTACK_PISTOL );
        }else if ( pm->ps->weapon == WP_KNIFE){
          PM_StartTorsoAnim( TORSO_ATTACK_KNIFE );
        }else if ( pm->ps->weapon == WP_SPAS){
          PM_StartTorsoAnim( TORSO_ATTACK_PUMPGUN );
        }else{
          PM_StartTorsoAnim( TORSO_ATTACK_RIFLE );
        }

 
			//start the weapon firing animation, first person view 
		         if ( pm->ps->weapon == WP_HK69 && pm->ps->stats[STAT_MODE] ){
         		 PM_StartWeaponAnim( WPN_FIRE_ALT ); //hk long distance mode
        		 }else  PM_StartWeaponAnim( WPN_FIRE ); 


                          pm->ps->weaponstate = WEAPON_FIRING;
                          pm->ps->weaponTime = PM_WeaponTime(pm->ps->weapon, pm->ps->stats[STAT_MODE] );
                          PM_AddEvent( EV_FIRE_WEAPON );//this is the client side effects, sound and muzzle flash 
                          if(bg_weaponlist[ pm->ps->weapon ].weapMode[pm->ps->clientNum] == 0){
                          pm->ps->stats[STAT_BURST_COUNT]++;
                          }
                          bg_weaponlist[0].numClips[pm->ps->clientNum]++; //This is a round count for spread.

                          if (pm->ps->weapon == WP_SR8 || pm->ps->weapon == WP_SPAS ){
                            pm->ps->pm_flags |= PMF_RELOADING;//for the bolt animation after each round.
                            if (pm->ps->weapon == WP_SR8){
                            pm->ps->weaponstate =WEAPON_FIRING2;//this is just for the zoom reset after each shot 
                            pm->ps->weaponTime = 700;//just enough time for the animations
                            }
                          }
			// if the weapon is single shot, or is at the last round of burst, 
			//set a flag to prevent another shot without releasing fire button
                          
                          
                         
                          
                          if ( pm->ps->pm_flags & PMF_SINGLE_MODE
                                || ( pm->ps->stats[STAT_BURST_COUNT] == 3 && isInBurst(pm) )  
                                || pm->ps->weapon == WP_SPAS
                                || pm->ps->weapon == WP_DEAGLE
                                || pm->ps->weapon == WP_BERETTA
                                || pm->ps->weapon == WP_PSG1
                                || pm->ps->weapon == WP_SR8
                                || pm->ps->weapon == WP_KNIFE
                                || pm->ps->weapon == WP_HK69
                                || BG_Grenade(pm->ps->weapon))
                                  {
                                        pm->ps->stats[STAT_BURST_COUNT] =0;
                                          pm->ps->pm_flags |= PMF_SINGLE_SHOT;

                                  }
                          
     //   }

}

/*
================
PM_Animate
================
*/

static void PM_Animate( void ) {
        //if ( pm->cmd.buttons & BUTTON_GESTURE ) {
          //      if ( pm->ps->torsoTimer == 0 ) {
            //            PM_StartTorsoAnim( TORSO_GESTURE );
              //          pm->ps->torsoTimer = TIMER_GESTURE;
                //        PM_AddEvent( EV_TAUNT );
             //   }

       // }
}


/*
================
PM_DropTimers
================
*/
static void PM_DropTimers( void ) {
        // drop misc timing counter
        if ( pm->ps->pm_time ) {
                if ( pml.msec >= pm->ps->pm_time ) {
                        pm->ps->pm_flags &= ~PMF_ALL_TIMES;
                        pm->ps->pm_time = 0;
                } else {
                        pm->ps->pm_time -= pml.msec;
                }
        }

        // drop animation counter
        if ( pm->ps->legsTimer > 0 ) {
                pm->ps->legsTimer -= pml.msec;
                if ( pm->ps->legsTimer < 0 ) {
                        pm->ps->legsTimer = 0;
                }
        }

        if ( pm->ps->torsoTimer > 0 ) {
                pm->ps->torsoTimer -= pml.msec;
                if ( pm->ps->torsoTimer < 0 ) {
                        pm->ps->torsoTimer = 0;
                }
        }


}

/*
================
PM_UpdateViewAngles

This can be used as another entry point when only the viewangles
are being updated isntead of a full move
================
*/
void PM_UpdateViewAngles( playerState_t *ps, const usercmd_t *cmd ) {
        short           temp;
        int             i;

        if ( ps->pm_type == PM_INTERMISSION || ps->pm_type == PM_SPINTERMISSION) {
                return;         // no view changes at all
        }

        if ( ps->pm_type != PM_SPECTATOR && ps->stats[STAT_HEALTH] <= 0 ) {
                return;         // no view changes at all
        }

        // circularly clamp the angles with deltas
        for (i=0 ; i<3 ; i++) {
                temp = cmd->angles[i] + ps->delta_angles[i];
                if ( i == PITCH ) {
                        // don't let the player look up or down more than 90 degrees
                        if ( temp > 16000 ) {
                                ps->delta_angles[i] = 16000 - cmd->angles[i];
                                temp = 16000;
                        } else if ( temp < -16000 ) {
                                ps->delta_angles[i] = -16000 - cmd->angles[i];
                                temp = -16000;
                        }
                }
                ps->viewangles[i] = SHORT2ANGLE(temp);
        }

}


/*
===================
PM_WallMove()

===================
*/
/*
static void PM_WallMove( void ) {
        int i;
        vec3_t wishvel;
        float wishspeed;
        vec3_t wishdir;
        float scale;
        float vel;

        PM_Friction ();

        scale = PM_CmdScale( &pm->cmd );

        if ( pml.groundPlane ) {
                return;
            }


        if ( !scale ) {
                wishvel[0] = 0;
                wishvel[1] = 0;
                wishvel[2] = 0;
        }
        else {
                for (i=0 ; i<3 ; i++)
                        wishvel[i] = scale * pml.forward[i]*pm->cmd.forwardmove +
                                        scale * pml.right[i]*pm->cmd.rightmove;
                wishvel[2] += scale * pm->cmd.upmove;
        }

        VectorCopy (wishvel, wishdir);
        wishspeed = VectorNormalize(wishdir);

        if ( wishspeed > pm->ps->speed * pm_ladderscale ) {
                wishspeed = pm->ps->speed * pm_ladderscale;
        }

        PM_Accelerate (wishdir, wishspeed, pm_ladderaccelerate);


            PM_SlideMove( qfalse ); // move without gravity
}
*/


/*
===================
PM_LadderMove()
still needs work

===================
*/


static void PM_LadderMove( void ) {
        int i;
        vec3_t wishvel;
        float wishspeed;
        vec3_t wishdir;
        float scale;
        float vel;

        PM_Friction ();

    // get user input
        scale = PM_CmdScale( &pm->cmd );

        VectorClear(wishvel);

        for (i=0 ; i<3 ; i++) {
                if ( CheckLadder() == -1 )
                {  
                        if ( i < 2 )
                        {
                                if ( pm->cmd.rightmove )
                                {
                                        wishvel[i] = scale * pml.right[i]*pm->cmd.rightmove;
                                        
                                }
                                else
                                        wishvel[i] = 0; //prevent steering 
                        }       
                }
                else if ( CheckLadder() == -2 )  { // backing down on a ladder --Xamis
                        wishvel[i] = scale * pml.forward[i]*pm->cmd.forwardmove +
                                        scale * pml.right[i]*pm->cmd.rightmove;

                }
                else {
                        wishvel[i] = scale * pml.forward[i]*pm->cmd.forwardmove +
                                        scale * pml.right[i]*pm->cmd.rightmove;
                         if( pm->cmd.rightmove == 0)
                              wishvel[0] = wishvel[1]=0; //prevent steering 
                }

        }

        wishvel[2] = scale * pm->cmd.forwardmove + scale  ;
        
        if( pm->cmd.rightmove != 0){
        wishvel[0] = scale * pml.right[0]*pm->cmd.rightmove;
        wishvel[1] = scale * pml.right[1]*pm->cmd.rightmove;
            
        }
            
         //   

        VectorCopy (wishvel, wishdir);
        wishspeed = VectorNormalize(wishdir);

        if ( wishspeed > pm->ps->speed * pm_ladderscale ) {
                wishspeed = pm->ps->speed * pm_ladderscale;
        }

        PM_Accelerate (wishdir, wishspeed, pm_ladderaccelerate);

        if ( pml.groundPlane && DotProduct( pm->ps->velocity,
            pml.groundTrace.plane.normal ) < 0 ) {
                    vel = VectorLength(pm->ps->velocity);
                    PM_ClipVelocity (pm->ps->velocity, pml.groundTrace.plane.normal,
                                      pm->ps->velocity, OVERCLIP );

                    VectorNormalize(pm->ps->velocity);
                    VectorScale(pm->ps->velocity, vel, pm->ps->velocity);
            }

            PM_SlideMove( qfalse );

}


void PM_PowerSlideMove( void ){
    PM_ClipVelocity (pm->ps->velocity, pml.groundTrace.plane.normal,
                    pm->ps->velocity, OVERCLIP );
    VectorNormalize(pm->ps->velocity);
    VectorScale(pm->ps->velocity, 500, pm->ps->velocity);
}

qboolean PM_CheckPowerSlide( void ){

// if( pm->ps->pm_flags & PMF_DUCKED && pml.groundPlane  && pm->xyspeed > 280  ){

    //Com_Printf( "pm->ps->pm_flags & PMF_DUCKED && pm->xyspeed > 280\n");
  // return qtrue;
  //}else
  return qfalse;
}



/*
================
PmoveSingle

================
*/
void trap_SnapVector( float *v );

void PmoveSingle (pmove_t *pmove) {

        pm = pmove;

        // this counter lets us debug movement problems with a journal
        // by setting a conditional breakpoint fot the previous frame
        c_pmove++;

        // clear results
        pm->numtouch = 0;
        pm->watertype = 0;
        pm->waterlevel = 0;


      //  Com_Printf("(int)pm->xyspeed = %i\n", (int)pm->xyspeed );
      // Com_Printf("pm->ps->stats[STAT_XYSPEED] = %i\n", pm->ps->stats[STAT_XYSPEED] );
        if ( pm->ps->stats[STAT_HEALTH] <= 0 ) {
                pm->tracemask &= ~CONTENTS_BODY;        // corpses can fly through bodies
                pm->ps->pm_flags &= ~ PMF_BLEEDING;
        }

        // make sure walking button is clear if they are running, to avoid
        // proxy no-footsteps cheats
        if ( abs( pm->cmd.forwardmove ) > 64 || abs( pm->cmd.rightmove ) > 64 ) {
                pm->cmd.buttons &= ~BUTTON_WALKING;
        }




        // set the talk balloon flag
        if ( pm->cmd.buttons & BUTTON_TALK ) {
                pm->ps->eFlags |= EF_TALK;
        } else {
                pm->ps->eFlags &= ~EF_TALK;
        }

        // set the firing flag for continuous beam weapons
        if ( !(pm->ps->pm_flags & PMF_RESPAWNED) && pm->ps->pm_type != PM_INTERMISSION
                && ( pm->cmd.buttons & BUTTON_ATTACK ) && pm->ps->ammo[ pm->ps->weapon ] ) {
                pm->ps->eFlags |= EF_FIRING;
        } else {
                pm->ps->eFlags &= ~EF_FIRING;
        }

        // clear the respawned flag if attack and use are cleared
        if ( pm->ps->stats[STAT_HEALTH] > 0 &&
                !( pm->cmd.buttons & (BUTTON_ATTACK | BUTTON_USE_HOLDABLE) ) ) {
                pm->ps->pm_flags &= ~PMF_RESPAWNED;
        }

        
        if( pm->ps->pm_flags & PMF_BLEEDING){
           if(  pmove->cmd.serverTime   % 50 == 0 ){
            PM_AddEvent(EV_BLEED);

           }
        }
        
        if (pm->cmd.buttons & BUTTON_HEAL &&  (pm->ps->pm_flags & PMF_BLEEDING || pm->ps->stats[STAT_DMG_LOC]) 
		&& pm->ps->weaponstate != WEAPON_START_BANDAGING  && pm->ps->weaponstate != WEAPON_DOWN_BANDAGING
		&& pm->ps->weaponstate != WEAPON_DOWN_BANDAGING_OTHER && pm->ps->pm_type != PM_DEAD){
             pm->ps->weaponstate = WEAPON_START_BANDAGING;
             pm->cmd.buttons &= ~BUTTON_HEAL;
        }

        // if talk button is down, dissallow all other input
        // this is to prevent any possible intercept proxy from
        // adding fake talk balloons
        if ( pmove->cmd.buttons & BUTTON_TALK ) {
                // keep the talk button set tho for when the cmd.serverTime > 66 msec
                // and the same cmd is used multiple times in Pmove
                pmove->cmd.buttons = BUTTON_TALK;
                pmove->cmd.forwardmove = 0;
                pmove->cmd.rightmove = 0;
                pmove->cmd.upmove = 0;
        }

        // clear all pmove local vars
        memset (&pml, 0, sizeof(pml));

        // determine the time
        pml.msec = pmove->cmd.serverTime - pm->ps->commandTime;
        if ( pml.msec < 1 ) {
                pml.msec = 1;
        } else if ( pml.msec > 200 ) {
                pml.msec = 200;
        }
        pm->ps->commandTime = pmove->cmd.serverTime;

        // save old org in case we get stuck
        VectorCopy (pm->ps->origin, pml.previous_origin);

        // save old velocity for crashlanding
        VectorCopy (pm->ps->velocity, pml.previous_velocity);

        pml.frametime = pml.msec * 0.001;

        // update the viewangles
        PM_UpdateViewAngles( pm->ps, &pm->cmd );

        AngleVectors (pm->ps->viewangles, pml.forward, pml.right, pml.up);

        if ( pm->cmd.upmove < 10 ) {
                // not holding jump
                pm->ps->pm_flags &= ~PMF_JUMP_HELD;
        }


        // decide if backpedaling animations should be used
        if ( pm->cmd.forwardmove < 0 ) {
                pm->ps->pm_flags |= PMF_BACKWARDS_RUN;
        } else if ( pm->cmd.forwardmove > 0 || ( pm->cmd.forwardmove == 0 && pm->cmd.rightmove ) ) {
                pm->ps->pm_flags &= ~PMF_BACKWARDS_RUN;
        }

        if ( pm->ps->pm_type >= PM_DEAD ) {
                pm->cmd.forwardmove = 0;
                pm->cmd.rightmove = 0;
                pm->cmd.upmove = 0;
        }

   //     if ( pm->ps->pm_type == PM_SPECTATOR ) {
   //             PM_CheckDuck ();
   //             PM_FlyMove ();
   //             PM_DropTimers ();
  //              return;
   //     }

        if ( pm->ps->pm_type == PM_SPECTATOR || pm->ps->pm_type == PM_NOCLIP ) {
                PM_NoclipMove ();
                PM_DropTimers ();
                return;
        }

        if (pm->ps->pm_type == PM_FREEZE) {
                return;         // no movement at all
        }

        if ( pm->ps->pm_type == PM_INTERMISSION || pm->ps->pm_type == PM_SPINTERMISSION) {
                return;         // no movement at all
        }

        // set watertype, and waterlevel
        PM_SetWaterLevel();
        pml.previous_waterlevel = pmove->waterlevel;

        // set mins, maxs, and viewheight
        PM_CheckDuck ();
        //CheckWall();


        // set groundentity
        PM_GroundTrace();

        if ( pm->ps->pm_type == PM_DEAD ) {
                PM_DeadMove ();
                pm->ps->pm_flags &= ~PMF_ONGROUND;
        }

        PM_DropTimers();
        if ( CheckLadder () != 0) {//Xamis
                PM_LadderMove();
                pm->ps->pm_flags &= ~PMF_ONGROUND;
        } else if (pm->ps->pm_flags & PMF_TIME_WATERJUMP) {
                PM_WaterJumpMove();
                pm->ps->pm_flags &= ~PMF_ONGROUND;
        } else if ( pm->waterlevel > 1 ) {
                // swimming
                PM_WaterMove();
                pm->ps->pm_flags &= ~PMF_ONGROUND;
        } else if ( pml.walking ) {
                // walking on ground
                PM_WalkMove();
                pm->ps->pm_flags |= PMF_ONGROUND;
        } else {
                // airborne
                PM_AirMove();
                pm->ps->pm_flags &= ~PMF_ONGROUND;
        }
        PM_Animate();

        // set groundentity, watertype, and waterlevel
        PM_GroundTrace();
        PM_SetWaterLevel();

        // weapons
        if ( CheckLadder () == 0 ){
            
        PM_Weapon();

        pm->ps->pm_flags &= ~ PMF_ONLADDER;
        }
        
        
        

       if ( pm->cmd.forwardmove > 0 ) {
        PM_AdjustAngleForLedgeClimb( pm->ps, &pm->cmd );
       }
        // torso animation
        PM_TorsoAnimation();

        // footstep events / legs animations
        PM_Footsteps();

        // entering / leaving water splashes
        PM_WaterEvents();

        // snap some parts of ps to save network bandwidth
        trap_SnapVector( pm->ps->velocity );
}



void Pmove (pmove_t *pmove) {
        int                     finalTime;

        finalTime = pmove->cmd.serverTime;
        if ( finalTime < pmove->ps->commandTime ) {
                return; // should not happen
        }

        if ( finalTime > pmove->ps->commandTime + 1000 ) {
                pmove->ps->commandTime = finalTime - 1000;
        }

        pmove->ps->pmove_framecount = (pmove->ps->pmove_framecount+1) & ((1<<PS_PMOVEFRAMECOUNTBITS)-1);

        // chop the move up if it is too long, to prevent framerate
        // dependent behavior
        while ( pmove->ps->commandTime != finalTime ) {
                int             msec;

                msec = finalTime - pmove->ps->commandTime;

                if ( pmove->pmove_fixed ) {
                        if ( msec > pmove->pmove_msec ) {
                                msec = pmove->pmove_msec;
                        }
                }
                else {
                        if ( msec > 66 ) {
                                msec = 66;
                        }
                }
                pmove->cmd.serverTime = pmove->ps->commandTime + msec;
                PmoveSingle( pmove );
                if ( pmove->ps->pm_flags & PMF_JUMP_HELD ) {
                        pmove->cmd.upmove = 20;
                }
        }

}


/*
 =============
 PM_CheckWallJump
 =============
 */
static qboolean PM_CheckWallJump(void) {
  if (pm->ps->pm_flags & PMF_RESPAWNED) {
    return qfalse;
  }

  if (pm->cmd.upmove < 10) {
    return qfalse;
  }

  if (pm->waterlevel >= 2) {
    return qfalse;
  }

    if (pm->ps->stats[STAT_WALLJUMPS] > MAX_WALLJUMPS) {
    return qfalse;
  }
  
  if (pm->ps->pm_flags & PMF_JUMP_HELD) {
    pm->cmd.upmove = 0;
    return qfalse;
  }

  //if (pm->ps->stamina < 1000) {
 //   return qfalse;
 // }

  if (pm->cmd.buttons & BUTTON_WALKING) {
    return qfalse;
  }

  if (pm->ps->velocity[2] < WALLJUMP_BOOST * -2) {
    return qfalse;
  }

  return qtrue;
}

/*
 =============
 PM_WallJump
 =============
 */
static qboolean PM_WallJump(void) {
  vec3_t dir, forward, movedir, point;
  vec3_t refNormal = {0.0f, 0.0f, 0.5f};
  float normalFraction = 1.0f;
  float cmdFraction = 1.0f;
  float upFraction = 6.5f;
  trace_t trace;
  vec3_t maxs, mins;
  
        mins[0] = -15;
        mins[1] = -15;

        maxs[0] = 15;
        maxs[1] = 15;

        maxs[2] = 20;
        mins[2] = -20;

  ProjectPointOnPlane(movedir, pml.forward, refNormal);
  VectorNormalize(movedir);

  if (pm->cmd.forwardmove < 0) {
    VectorNegate(movedir, movedir);
  }

  //trace into direction we are moving
  VectorMA(pm->ps->origin, 0.25f, movedir, point);
  pm->trace(&trace, pm->ps->origin, mins, maxs, point, pm->ps->clientNum, pm->tracemask);

  if (trace.fraction < 1.0f && !(trace.surfaceFlags & (SURF_SKY | SURF_SLICK))
      && trace.plane.normal[2] < MIN_WALK_NORMAL) {
    if (!VectorCompare(trace.plane.normal, pm->ps->grapplePoint)) {
      VectorCopy( trace.plane.normal, pm->ps->grapplePoint );
    }
  } else {
    return qfalse;
  }

  pml.groundPlane = qfalse; // jumping away
  pml.walking = qfalse;
  pm->ps->pm_flags |= PMF_JUMP_HELD;

  pm->ps->groundEntityNum = ENTITYNUM_NONE;

  ProjectPointOnPlane(forward, pml.forward, pm->ps->grapplePoint);

  VectorScale( pm->ps->grapplePoint, normalFraction, dir );

  if (pm->cmd.forwardmove > 0)
    VectorMA(dir, cmdFraction, forward, dir);
  else if (pm->cmd.forwardmove < 0)
    VectorMA(dir, -cmdFraction, forward, dir);

  VectorMA(dir, upFraction, refNormal, dir);
  VectorNormalize(dir);

  VectorMA(pm->ps->velocity, WALLJUMP_SPEED, dir, pm->ps->velocity);
  pm->ps->velocity[2] *= WALLJUMP_UP_VEL_BOOST;
  if(pm->ps->velocity[2]  > WALLJUMP_MAX_UP_VEL){
      pm->ps->velocity[2] = WALLJUMP_MAX_UP_VEL;      
  }


  if (VectorLength(pm->ps->velocity) > WALLJUMP_MAX_VEL) {
    VectorNormalize(pm->ps->velocity);
    VectorScale( pm->ps->velocity, WALLJUMP_MAX_VEL, pm->ps->velocity );
  }

      //    PM_AddEvent(EV_WALLJUMP);
      //    pm->ps->stats[STAT_WALLJUMPS]++;
      
  //Com_Printf("pm->ps->velocity[2] is %f\n  pm->ps->stats[STAT_WALLJUMPS] is %i\npm->ps->stats[STAT_STAMINA] is %i\n",
   //        pm->ps->velocity[2],pm->ps->stats[STAT_WALLJUMPS], pm->ps->stats[STAT_STAMINA] );
  
  if (pm->cmd.forwardmove >= 0) {
    PM_ForceLegsAnim(LEGS_JUMP);
    pm->ps->pm_flags &= ~PMF_BACKWARDS_JUMP;
  } else if(pm->cmd.forwardmove < 0) {
    PM_ForceLegsAnim(LEGS_JUMPB);
    pm->ps->pm_flags |= PMF_BACKWARDS_JUMP;
  } else if(pm->cmd.rightmove > 0){
//todo jump right animation
  }else if(pm->cmd.rightmove < 0){
//todo jump left animation
  }
  return qtrue;
}
