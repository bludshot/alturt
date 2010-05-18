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
// cg_ents.c -- present snapshot entities, happens every single frame

#include "cg_local.h"

/* [QUARANTINE] - CG_PositionWeaponOnTag
======================
CG_PositionWeaponOnTag

Changed from CG_PositionEntityOnTag function to prevent backlerp change in animations
======================
*/
void CG_PositionWeaponOnTag( refEntity_t *entity, const refEntity_t *parent, qhandle_t parentModel, char *tagName ) {
  int i;
  orientation_t lerped;

// lerp the tag
  trap_R_LerpTag( &lerped, parentModel, parent->oldframe, parent->frame,
                   1.0 - parent->backlerp, tagName );

// FIXME: allow origin offsets along tag?
  VectorCopy( parent->origin, entity->origin );
  for ( i = 0 ; i < 3 ; i++ ) {
    VectorMA( entity->origin, lerped.origin[i], parent->axis[i], entity->origin );
  }

// had to cast away the const to avoid compiler problems...
  MatrixMultiply( lerped.axis, ((refEntity_t *)parent)->axis, entity->axis );
// entity->backlerp = parent->backlerp;
}

/*
======================
CG_PositionEntityOnTag

Modifies the entities position and axis by the given
tag location
======================
*/
void CG_PositionEntityOnTag( refEntity_t *entity, const refEntity_t *parent,
                                                        qhandle_t parentModel, char *tagName ) {
        int                             i;
        orientation_t   lerped;

        // lerp the tag
        trap_R_LerpTag( &lerped, parentModel, parent->oldframe, parent->frame,
                1.0 - parent->backlerp, tagName );

        // FIXME: allow origin offsets along tag?
        VectorCopy( parent->origin, entity->origin );
        for ( i = 0 ; i < 3 ; i++ ) {
                VectorMA( entity->origin, lerped.origin[i], parent->axis[i], entity->origin );
        }

        // had to cast away the const to avoid compiler problems...
        MatrixMultiply( lerped.axis, ((refEntity_t *)parent)->axis, entity->axis );
        entity->backlerp = parent->backlerp;
}


/*
======================
CG_PositionRotatedEntityOnTag

Modifies the entities position and axis by the given
tag location
======================
*/
void CG_PositionRotatedEntityOnTag( refEntity_t *entity, const refEntity_t *parent,
                                                        qhandle_t parentModel, char *tagName ) {
        int                             i;
        orientation_t   lerped;
        vec3_t                  tempAxis[3];

//AxisClear( entity->axis );
        // lerp the tag
        trap_R_LerpTag( &lerped, parentModel, parent->oldframe, parent->frame,
                1.0 - parent->backlerp, tagName );

        // FIXME: allow origin offsets along tag?
        VectorCopy( parent->origin, entity->origin );
        for ( i = 0 ; i < 3 ; i++ ) {
                VectorMA( entity->origin, lerped.origin[i], parent->axis[i], entity->origin );
        }

        // had to cast away the const to avoid compiler problems...
        MatrixMultiply( entity->axis, lerped.axis, tempAxis );
        MatrixMultiply( tempAxis, ((refEntity_t *)parent)->axis, entity->axis );
}



/*
==========================================================================

FUNCTIONS CALLED EACH FRAME

==========================================================================
*/

/*
======================
CG_SetEntitySoundPosition

Also called by event processing code
======================
*/
void CG_SetEntitySoundPosition( centity_t *cent ) {
        if ( cent->currentState.solid == SOLID_BMODEL ) {
                vec3_t  origin;
                float   *v;

                v = cgs.inlineModelMidpoints[ cent->currentState.modelindex ];
                VectorAdd( cent->lerpOrigin, v, origin );
                trap_S_UpdateEntityPosition( cent->currentState.number, origin );
        } else {
                trap_S_UpdateEntityPosition( cent->currentState.number, cent->lerpOrigin );
        }
}

/*
==================
CG_EntityEffects

Add continuous entity effects, like local entity emission and lighting
==================
*/
static void CG_EntityEffects( centity_t *cent ) {

        // update sound origins
        CG_SetEntitySoundPosition( cent );

        // add loop sound
        if ( cent->currentState.loopSound ) {
                if (cent->currentState.eType != ET_SPEAKER) {
                        trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin,
                                cgs.gameSounds[ cent->currentState.loopSound ] );
                } else {
                        trap_S_AddRealLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin,
                                cgs.gameSounds[ cent->currentState.loopSound ] );
                }
        }


        // constant light glow
        if ( cent->currentState.constantLight ) {
                int             cl;
                int             i, r, g, b;

                cl = cent->currentState.constantLight;
                r = cl & 255;
                g = ( cl >> 8 ) & 255;
                b = ( cl >> 16 ) & 255;
                i = ( ( cl >> 24 ) & 255 ) * 4;
                trap_R_AddLightToScene( cent->lerpOrigin, i, r, g, b );
        }

}


/*
==================
CG_General
==================
*/
static void CG_General( centity_t *cent ) {
        refEntity_t                     ent;
        entityState_t           *s1;

        s1 = &cent->currentState;

        // if set to invisible, skip
        if (!s1->modelindex) {
                return;
        }

        memset (&ent, 0, sizeof(ent));

        // set frame

        ent.frame = s1->frame;
        ent.oldframe = ent.frame;
        ent.backlerp = 0;

        VectorCopy( cent->lerpOrigin, ent.origin);
        VectorCopy( cent->lerpOrigin, ent.oldorigin);

        ent.hModel = cgs.gameModels[s1->modelindex];

        // player model
        if (s1->number == cg.snap->ps.clientNum) {
                ent.renderfx |= RF_THIRD_PERSON;        // only draw from mirrors
        }

        // convert angles to axis
        AnglesToAxis( cent->lerpAngles, ent.axis );

        // add to refresh list
        trap_R_AddRefEntityToScene (&ent);
}

/*
==================
CG_Speaker

Speaker entities can automatically play sounds
==================
*/
static void CG_Speaker( centity_t *cent ) {
        if ( ! cent->currentState.clientNum ) { // FIXME: use something other than clientNum...
                return;         // not auto triggering
        }

        if ( cg.time < cent->miscTime ) {
                return;
        }

        trap_S_StartSound (NULL, cent->currentState.number, CHAN_ITEM, cgs.gameSounds[cent->currentState.eventParm] );

        //      ent->s.frame = ent->wait * 10;
        //      ent->s.clientNum = ent->random * 10;
        cent->miscTime = cg.time + cent->currentState.frame * 100 + cent->currentState.clientNum * 100 * crandom();
}

/*
==================
CG_Item
==================
*/
static void CG_Item( centity_t *cent ) {
  refEntity_t                 ent;
  entityState_t               *es;
  gitem_t                             *item;

  es = &cent->currentState;
  if ( es->modelindex >= bg_numItems ) {
    CG_Error( "Bad item index %i on entity", es->modelindex );
  }

    // if set to invisible, skip
  if ( !es->modelindex || ( es->eFlags & EF_NODRAW ) ) {
    return;
  }

  item = &bg_itemlist[ es->modelindex ];

  //
    // if simpleitems are enable render as sprite and then return
  //
  if ( cg_simpleItems.integer ) //&& item->giType != IT_TEAM )
  {
    memset( &ent, 0, sizeof( ent ) );

    ent.reType = RT_SPRITE;
    VectorCopy( cent->lerpOrigin, ent.origin );
    ent.radius = 14;
    ent.customShader = cg_items[es->modelindex].icon;
    ent.shaderRGBA[0] = 255;
    ent.shaderRGBA[1] = 255;
    ent.shaderRGBA[2] = 255;
    ent.shaderRGBA[3] = 240;
    trap_R_AddRefEntityToScene(&ent);
    return;
  }

  memset( &ent, 0, sizeof( ent ) );

    // the weapons have their origin where they attatch to player
    // models, so we need to offset them or they will rotate
    // eccentricly
  if (item->giType == IT_WEAPON ) {
    ent.hModel = cg_weapons[item->giTag].weaponModel;
    cent->lerpOrigin[2] -= 3; // bring to ground
  }

  else
    ent.hModel = cg_items[es->modelindex].models[0];

    // no model ?
  if ( !ent.hModel )
    return;

  AnglesToAxis( cent->lerpAngles, ent.axis );

  VectorCopy( cent->lerpOrigin, ent.origin);
  VectorCopy( cent->lerpOrigin, ent.oldorigin);

  ent.nonNormalizedAxes = qfalse;

    trap_R_AddRefEntityToScene(&ent);
}
//============================================================================

/*
===============
CG_Missile
===============
*/
static void CG_Missile( centity_t *cent ) {
        refEntity_t                     ent;
        entityState_t           *s1;
        const weaponInfo_t              *weapon;
//      int     col;

        s1 = &cent->currentState;
        if ( s1->weapon > WP_NUM_WEAPONS ) {
                s1->weapon = 0;
        }
        weapon = &cg_weapons[s1->weapon];

        // calculate the axis
        VectorCopy( s1->angles, cent->lerpAngles);


        if ( s1->generic1 == MF_SMOKE )
        {
          vec3_t up, orig;
          localEntity_t *smoke;
          int seed = cent->currentState.frame & ALTURT_SMOKEMASK_RNDNUM;
          int radius = ALTURT_SMOKEPUFF_RADIUS + Q_random(&seed)*8;
          int dummy;

          dummy = (cent->currentState.frame & ALTURT_SMOKEMASK_RIGHT) >> ALTURT_SMOKEMASK_SRIGHT;
          dummy += (cent->currentState.frame & ALTURT_SMOKEMASK_LEFT) >> ALTURT_SMOKEMASK_SLEFT;
          dummy += (cent->currentState.frame & ALTURT_SMOKEMASK_FORWARD) >> ALTURT_SMOKEMASK_SFORWARD;
          dummy += (cent->currentState.frame & ALTURT_SMOKEMASK_BACKWARD) >> ALTURT_SMOKEMASK_SBACKWARD;
          dummy += (cent->currentState.frame & ALTURT_SMOKEMASK_UP) >> ALTURT_SMOKEMASK_SUP;
          radius *= 1.0 + (float)dummy/15.0;

          if ( CG_PointContents( cent->lerpOrigin, -1 ) &  CONTENTS_WATER   ) {

            VectorCopy( cent->lerpOrigin, up );

            up[0] += -10+Q_random(&seed)*20;
            up[1] += -10+Q_random(&seed)*20;
            up[2] += 5+Q_random(&seed)*5;

            CG_BubbleTrail( cent->lerpOrigin , up, 4 );
          }
          else {
            float distance;
            // smoke blend
            distance = Distance( cent->lerpOrigin, cg.refdef.vieworg );

            if ( distance < ( ALTURT_SMOKEBLEND_RANGE * (1.0 + dummy / 15.0 ) ) ) {

                // check the directions for the additional blend effect
              if ( (32 + ((cent->currentState.frame & ALTURT_SMOKEMASK_RIGHT) >> ALTURT_SMOKEMASK_SRIGHT) *
                    (int)(ALTURT_SMOKEBLEND_RANGE / ALTURT_SMOKEMASK_VALUE)) >
                    (cg.refdef.vieworg[1] - cent->lerpOrigin[1])  )
                cg.smokeBlendAlpha = 1.0f - distance/( ALTURT_SMOKEBLEND_RANGE * (1.0 + dummy/15.0));
              else if ( (32 + ((cent->currentState.frame & ALTURT_SMOKEMASK_LEFT) >> ALTURT_SMOKEMASK_SLEFT) *
                         (int)(ALTURT_SMOKEBLEND_RANGE / ALTURT_SMOKEMASK_VALUE)) >
                         ( - cg.refdef.vieworg[1] + cent->lerpOrigin[1])  )
                cg.smokeBlendAlpha = 1.0f - distance/( ALTURT_SMOKEBLEND_RANGE * (1.0 + dummy/15.0));
              else if ( (32 + ((cent->currentState.frame & ALTURT_SMOKEMASK_FORWARD) >> ALTURT_SMOKEMASK_SFORWARD) *
                         (int)(ALTURT_SMOKEBLEND_RANGE / ALTURT_SMOKEMASK_VALUE)) >
                         ( cg.refdef.vieworg[0] - cent->lerpOrigin[0])  )
                cg.smokeBlendAlpha = 1.0f - distance/( ALTURT_SMOKEBLEND_RANGE * (1.0 + dummy/15.0));
              else if ( (32 + ((cent->currentState.frame & ALTURT_SMOKEMASK_BACKWARD) >> ALTURT_SMOKEMASK_SBACKWARD) *
                         (int)(ALTURT_SMOKEBLEND_RANGE / ALTURT_SMOKEMASK_VALUE)) >
                         ( - cg.refdef.vieworg[0] + cent->lerpOrigin[0])  )
                cg.smokeBlendAlpha = 1.0f - distance/( ALTURT_SMOKEBLEND_RANGE * (1.0 + dummy/15.0));
              else if ( (32 + ((cent->currentState.frame & ALTURT_SMOKEMASK_UP) >> ALTURT_SMOKEMASK_SUP) *
                         (int)(ALTURT_SMOKEBLEND_RANGE / ALTURT_SMOKEMASK_VALUE)) >
                         ( cg.refdef.vieworg[2] - cent->lerpOrigin[2])  )
                          cg.smokeBlendAlpha = 1.0f - distance/( ALTURT_SMOKEBLEND_RANGE * (1.0 + dummy/15.0));

              if ( cg.smokeBlendAlpha > 0.8f )
                  cg.smokeBlendAlpha = 0.8f;
            }

            // main smokes
            if ( cent->trailTime < cg.time ) {

                // get the base speed for the smoke
              up[0] = -6.0 + Q_random(&seed)*12;
              up[1] = -6.0 + Q_random(&seed)*12;
              up[2] =  4.0 + Q_random(&seed)*6;

                // modify the speed according to open area stuff
              if (up[0] > 0.0)
                up[0] += Q_random(&seed)*14.0* ((cent->currentState.frame & ALTURT_SMOKEMASK_RIGHT) >> ALTURT_SMOKEMASK_SRIGHT);
              if (up[0] < 0.0)
                up[0] -= Q_random(&seed)*14.0* ((cent->currentState.frame & ALTURT_SMOKEMASK_LEFT) >> ALTURT_SMOKEMASK_SLEFT);

              if (up[1] > 0.0)
                up[1] += Q_random(&seed)*14.0* ((cent->currentState.frame & ALTURT_SMOKEMASK_FORWARD) >> ALTURT_SMOKEMASK_SFORWARD);
              if (up[1] < 0.0)
                up[1] -= Q_random(&seed)*14.0* ((cent->currentState.frame & ALTURT_SMOKEMASK_BACKWARD) >> ALTURT_SMOKEMASK_SBACKWARD);

              if ( up[2] > 0.0 )
                up[2] += Q_random(&seed)*12.0* ((cent->currentState.frame & ALTURT_SMOKEMASK_UP) >> ALTURT_SMOKEMASK_SUP);

              VectorCopy(cent->lerpOrigin, orig);
              orig[2] += 4.0;

              switch ( cgs.clientinfo[ cent->currentState.clientNum ].team  ) {
                case TEAM_RED:
                  smoke = CG_SmokePuff( orig,
                                        up,
                                        radius,
                                        ALTURT_SMOKENADE_R_TEAM_RED,
                                        ALTURT_SMOKENADE_G_TEAM_RED,
                                        ALTURT_SMOKENADE_B_TEAM_RED,
                                        1.0,
                                        ALTURT_SMOKEPUFF_TIME,
                                        cg.time,
                                        0,
                                        LEF_PUFF_DONT_FADE,
                                        cgs.media.smokePuffShader );
                  break;
                case TEAM_BLUE:
                  smoke = CG_SmokePuff( orig,
                                        up,
                                        radius,
                                        ALTURT_SMOKENADE_R_TEAM_BLUE,
                                        ALTURT_SMOKENADE_G_TEAM_BLUE,
                                        ALTURT_SMOKENADE_B_TEAM_BLUE,
                                        1.0,
                                        ALTURT_SMOKEPUFF_TIME,
                                        cg.time,
                                        0,
                                        LEF_PUFF_DONT_FADE,
                                        cgs.media.smokePuffShader );
                  break;
                default:
                  smoke = CG_SmokePuff( orig,
                                        up,
                                        radius,
                                        ALTURT_SMOKENADE_R_DEFAULT,
                                        ALTURT_SMOKENADE_G_DEFAULT,
                                        ALTURT_SMOKENADE_B_DEFAULT,
                                        1.0,
                                        ALTURT_SMOKEPUFF_TIME,
                                        cg.time,
                                        0,
                                        LEF_PUFF_DONT_FADE,
                                        cgs.media.smokePuffShader );
                  break;
              }

              cent->trailTime = cg.time + ALTURT_SMOKENADETIME;
            }
          }
        }




        // add trails
        if ( weapon->missileTrailFunc )
        {
                weapon->missileTrailFunc( cent, weapon );
        }
/*
        if ( cent->currentState.modelindex == TEAM_RED ) {
                col = 1;
        }
        else if ( cent->currentState.modelindex == TEAM_BLUE ) {
                col = 2;
        }
        else {
                col = 0;
        }

        // add dynamic light
        if ( weapon->missileDlight ) {
                trap_R_AddLightToScene(cent->lerpOrigin, weapon->missileDlight,
                        weapon->missileDlightColor[col][0], weapon->missileDlightColor[col][1], weapon->missileDlightColor[col][2] );
        }
*/
        // add dynamic light
        if ( weapon->missileDlight ) {
                trap_R_AddLightToScene(cent->lerpOrigin, weapon->missileDlight,
                        weapon->missileDlightColor[0], weapon->missileDlightColor[1], weapon->missileDlightColor[2] );
        }

        // add missile sound
        if ( weapon->missileSound ) {
                vec3_t  velocity;

                BG_EvaluateTrajectoryDelta( &cent->currentState.pos, cg.time, velocity );

                trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, velocity, weapon->missileSound );
        }

        // create the render entity
        memset (&ent, 0, sizeof(ent));
        VectorCopy( cent->lerpOrigin, ent.origin);
        VectorCopy( cent->lerpOrigin, ent.oldorigin);

        // flicker between two skins
        ent.skinNum = cg.clientFrame & 1;
        ent.hModel = weapon->missileModel;
        ent.renderfx = weapon->missileRenderfx | RF_NOSHADOW;


        // convert direction of travel into axis
        if ( VectorNormalize2( s1->pos.trDelta, ent.axis[0] ) == 0 ) {
                ent.axis[0][2] = 1;
        }

        // spin as it moves
        if ( s1->pos.trType != TR_STATIONARY ) {
                RotateAroundDirection( ent.axis, cg.time / 4 );
        } else {

                {
                        RotateAroundDirection( ent.axis, s1->time );
                }
        }

        // add to refresh list, possibly with quad glow
        CG_AddRefEntityWithPowerups( &ent, s1, TEAM_FREE );
}

/*
===============
CG_Grapple

This is called when the grapple is sitting up against the wall
===============
*/
static void CG_Grapple( centity_t *cent ) {
        refEntity_t                     ent;
        entityState_t           *s1;
        const weaponInfo_t              *weapon;

        s1 = &cent->currentState;
        if ( s1->weapon > WP_NUM_WEAPONS ) {
                s1->weapon = 0;
        }
        weapon = &cg_weapons[s1->weapon];

        // calculate the axis
        VectorCopy( s1->angles, cent->lerpAngles);

#if 0 // FIXME add grapple pull sound here..?
        // add missile sound
        if ( weapon->missileSound ) {
                trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->missileSound );
        }
#endif

        // Will draw cable if needed
        CG_GrappleTrail ( cent, weapon );

        // create the render entity
        memset (&ent, 0, sizeof(ent));
        VectorCopy( cent->lerpOrigin, ent.origin);
        VectorCopy( cent->lerpOrigin, ent.oldorigin);

        // flicker between two skins
        ent.skinNum = cg.clientFrame & 1;
        ent.hModel = weapon->missileModel;
        ent.renderfx = weapon->missileRenderfx | RF_NOSHADOW;

        // convert direction of travel into axis
        if ( VectorNormalize2( s1->pos.trDelta, ent.axis[0] ) == 0 ) {
                ent.axis[0][2] = 1;
        }

        trap_R_AddRefEntityToScene( &ent );
}

/*
===============
CG_Mover
===============
*/
static void CG_Mover( centity_t *cent ) {
        refEntity_t                     ent;
        entityState_t           *s1;

        s1 = &cent->currentState;

        // create the render entity
        memset (&ent, 0, sizeof(ent));
        VectorCopy( cent->lerpOrigin, ent.origin);
        VectorCopy( cent->lerpOrigin, ent.oldorigin);
        AnglesToAxis( cent->lerpAngles, ent.axis );

        ent.renderfx = RF_NOSHADOW;

        // flicker between two skins (FIXME?)
        ent.skinNum = ( cg.time >> 6 ) & 1;

        // get the model, either as a bmodel or a modelindex
        if ( s1->solid == SOLID_BMODEL ) {
                ent.hModel = cgs.inlineDrawModel[s1->modelindex];
        } else {
                ent.hModel = cgs.gameModels[s1->modelindex];
        }

        // add to refresh list
        trap_R_AddRefEntityToScene(&ent);

        // add the secondary model
        if ( s1->modelindex2 ) {
                ent.skinNum = 0;
                ent.hModel = cgs.gameModels[s1->modelindex2];
                trap_R_AddRefEntityToScene(&ent);
        }

}

/*
===============
CG_Beam

Also called as an event
===============
*/
void CG_Beam( centity_t *cent ) {
        refEntity_t                     ent;
        entityState_t           *s1;

        s1 = &cent->currentState;

        // create the render entity
        memset (&ent, 0, sizeof(ent));
        VectorCopy( s1->pos.trBase, ent.origin );
        VectorCopy( s1->origin2, ent.oldorigin );
        AxisClear( ent.axis );
        ent.reType = RT_BEAM;

        ent.renderfx = RF_NOSHADOW;

        // add to refresh list
        trap_R_AddRefEntityToScene(&ent);
}


/*
===============
CG_Portal
===============
*/
static void CG_Portal( centity_t *cent ) {
        refEntity_t                     ent;
        entityState_t                   *s1;

        s1 = &cent->currentState;

        // create the render entity
        memset (&ent, 0, sizeof(ent));
        VectorCopy( cent->lerpOrigin, ent.origin );
        VectorCopy( s1->origin2, ent.oldorigin );
        ByteToDir( s1->eventParm, ent.axis[0] );
        PerpendicularVector( ent.axis[1], ent.axis[0] );

        // negating this tends to get the directions like they want
        // we really should have a camera roll value
        VectorSubtract( vec3_origin, ent.axis[1], ent.axis[1] );

        CrossProduct( ent.axis[0], ent.axis[1], ent.axis[2] );
        ent.reType = RT_PORTALSURFACE;
        ent.oldframe = s1->powerups;
        ent.frame = s1->frame;          // rotation speed
        ent.skinNum = s1->clientNum/256.0 * 360;        // roll offset

        // add to refresh list
        trap_R_AddRefEntityToScene(&ent);
}


/*
=========================
CG_AdjustPositionForMover

Also called by client movement prediction code
=========================
*/
void CG_AdjustPositionForMover( const vec3_t in, int moverNum, int fromTime, int toTime, vec3_t out ) {
        centity_t       *cent;
        vec3_t  oldOrigin, origin, deltaOrigin;
        vec3_t  oldAngles, angles, deltaAngles;

        if ( moverNum <= 0 || moverNum >= ENTITYNUM_MAX_NORMAL ) {
                VectorCopy( in, out );
                return;
        }

        cent = &cg_entities[ moverNum ];
        if ( cent->currentState.eType != ET_MOVER ) {
                VectorCopy( in, out );
                return;
        }

        BG_EvaluateTrajectory( &cent->currentState.pos, fromTime, oldOrigin );
        BG_EvaluateTrajectory( &cent->currentState.apos, fromTime, oldAngles );

        BG_EvaluateTrajectory( &cent->currentState.pos, toTime, origin );
        BG_EvaluateTrajectory( &cent->currentState.apos, toTime, angles );

        VectorSubtract( origin, oldOrigin, deltaOrigin );
        VectorSubtract( angles, oldAngles, deltaAngles );

        VectorAdd( in, deltaOrigin, out );

        // FIXME: origin change when on a rotating object
}


/*
=============================
CG_InterpolateEntityPosition
=============================
*/
static void CG_InterpolateEntityPosition( centity_t *cent ) {
        vec3_t          current, next;
        float           f;

        // it would be an internal error to find an entity that interpolates without
        // a snapshot ahead of the current one
        if ( cg.nextSnap == NULL ) {
                CG_Error( "CG_InterpoateEntityPosition: cg.nextSnap == NULL" );
        }

        f = cg.frameInterpolation;

        // this will linearize a sine or parabolic curve, but it is important
        // to not extrapolate player positions if more recent data is available
        BG_EvaluateTrajectory( &cent->currentState.pos, cg.snap->serverTime, current );
        BG_EvaluateTrajectory( &cent->nextState.pos, cg.nextSnap->serverTime, next );

        cent->lerpOrigin[0] = current[0] + f * ( next[0] - current[0] );
        cent->lerpOrigin[1] = current[1] + f * ( next[1] - current[1] );
        cent->lerpOrigin[2] = current[2] + f * ( next[2] - current[2] );

        BG_EvaluateTrajectory( &cent->currentState.apos, cg.snap->serverTime, current );
        BG_EvaluateTrajectory( &cent->nextState.apos, cg.nextSnap->serverTime, next );

        cent->lerpAngles[0] = LerpAngle( current[0], next[0], f );
        cent->lerpAngles[1] = LerpAngle( current[1], next[1], f );
        cent->lerpAngles[2] = LerpAngle( current[2], next[2], f );

}

/*
===============
CG_CalcEntityLerpPositions

===============
*/
static void CG_CalcEntityLerpPositions( centity_t *cent ) {

        // if this player does not want to see extrapolated players
        if ( !cg_smoothClients.integer ) {
                // make sure the clients use TR_INTERPOLATE
                if ( cent->currentState.number < MAX_CLIENTS ) {
                        cent->currentState.pos.trType = TR_INTERPOLATE;
                        cent->nextState.pos.trType = TR_INTERPOLATE;
                }
        }

        if ( cent->interpolate && cent->currentState.pos.trType == TR_INTERPOLATE ) {
                CG_InterpolateEntityPosition( cent );
                return;
        }

        // first see if we can interpolate between two snaps for
        // linear extrapolated clients
        if ( cent->interpolate && cent->currentState.pos.trType == TR_LINEAR_STOP &&
                                                                                        cent->currentState.number < MAX_CLIENTS) {
                CG_InterpolateEntityPosition( cent );
                return;
        }

        // just use the current frame and evaluate as best we can
        BG_EvaluateTrajectory( &cent->currentState.pos, cg.time, cent->lerpOrigin );
        BG_EvaluateTrajectory( &cent->currentState.apos, cg.time, cent->lerpAngles );

        // adjust for riding a mover if it wasn't rolled into the predicted
        // player state
        if ( cent != &cg.predictedPlayerEntity ) {
                CG_AdjustPositionForMover( cent->lerpOrigin, cent->currentState.groundEntityNum,
                cg.snap->serverTime, cg.time, cent->lerpOrigin );
        }
}

/*
===============
CG_TeamBase
===============
*/
static void CG_TeamBase( centity_t *cent ) {
        refEntity_t model;
#ifdef MISSIONPACK
        vec3_t angles;
        int t, h;
        float c;

        if ( cgs.gametype == GT_CTF || cgs.gametype == GT_BOMB ) {
#else
        if ( cgs.gametype == GT_CTF) {
#endif
                // show the flag base
                memset(&model, 0, sizeof(model));
                model.reType = RT_MODEL;
                VectorCopy( cent->lerpOrigin, model.lightingOrigin );
                VectorCopy( cent->lerpOrigin, model.origin );
                AnglesToAxis( cent->currentState.angles, model.axis );
                if ( cent->currentState.modelindex == TEAM_RED ) {
                        model.hModel = cgs.media.redFlagBaseModel;
                }
                else if ( cent->currentState.modelindex == TEAM_BLUE ) {
                        model.hModel = cgs.media.blueFlagBaseModel;
                }
                else {
                        model.hModel = cgs.media.neutralFlagBaseModel;
                }
                trap_R_AddRefEntityToScene( &model );
        }
#ifdef MISSIONPACK
        else if ( cgs.gametype == GT_BOMB ) {
                // show the obelisk
                memset(&model, 0, sizeof(model));
                model.reType = RT_MODEL;
                VectorCopy( cent->lerpOrigin, model.lightingOrigin );
                VectorCopy( cent->lerpOrigin, model.origin );
                AnglesToAxis( cent->currentState.angles, model.axis );

                model.hModel = cgs.media.overloadBaseModel;
                trap_R_AddRefEntityToScene( &model );
                // if hit
                if ( cent->currentState.frame == 1) {
                        // show hit model
                        // modelindex2 is the health value of the obelisk
                        c = cent->currentState.modelindex2;
                        model.shaderRGBA[0] = 0xff;
                        model.shaderRGBA[1] = c;
                        model.shaderRGBA[2] = c;
                        model.shaderRGBA[3] = 0xff;
                        //
                        model.hModel = cgs.media.overloadEnergyModel;
                        trap_R_AddRefEntityToScene( &model );
                }
                // if respawning
                if ( cent->currentState.frame == 2) {
                        if ( !cent->miscTime ) {
                                cent->miscTime = cg.time;
                        }
                        t = cg.time - cent->miscTime;
                        h = (cg_obeliskRespawnDelay.integer - 5) * 1000;
                        //
                        if (t > h) {
                                c = (float) (t - h) / h;
                                if (c > 1)
                                        c = 1;
                        }
                        else {
                                c = 0;
                        }
                        // show the lights
                        AnglesToAxis( cent->currentState.angles, model.axis );
                        //
                        model.shaderRGBA[0] = c * 0xff;
                        model.shaderRGBA[1] = c * 0xff;
                        model.shaderRGBA[2] = c * 0xff;
                        model.shaderRGBA[3] = c * 0xff;

                        model.hModel = cgs.media.overloadLightsModel;
                        trap_R_AddRefEntityToScene( &model );
                        // show the target
                        if (t > h) {
                                if ( !cent->muzzleFlashTime ) {
                                        trap_S_StartSound (cent->lerpOrigin, ENTITYNUM_NONE, CHAN_BODY,  cgs.media.obeliskRespawnSound);
                                        cent->muzzleFlashTime = 1;
                                }
                                VectorCopy(cent->currentState.angles, angles);
                                angles[YAW] += (float) 16 * acos(1-c) * 180 / M_PI;
                                AnglesToAxis( angles, model.axis );

                                VectorScale( model.axis[0], c, model.axis[0]);
                                VectorScale( model.axis[1], c, model.axis[1]);
                                VectorScale( model.axis[2], c, model.axis[2]);

                                model.shaderRGBA[0] = 0xff;
                                model.shaderRGBA[1] = 0xff;
                                model.shaderRGBA[2] = 0xff;
                                model.shaderRGBA[3] = 0xff;
                                //
                                model.origin[2] += 56;
                                model.hModel = cgs.media.overloadTargetModel;
                                trap_R_AddRefEntityToScene( &model );
                        }
                        else {
                                //FIXME: show animated smoke
                        }
                }
                else {
                        cent->miscTime = 0;
                        cent->muzzleFlashTime = 0;
                        // modelindex2 is the health value of the obelisk
                        c = cent->currentState.modelindex2;
                        model.shaderRGBA[0] = 0xff;
                        model.shaderRGBA[1] = c;
                        model.shaderRGBA[2] = c;
                        model.shaderRGBA[3] = 0xff;
                        // show the lights
                        model.hModel = cgs.media.overloadLightsModel;
                        trap_R_AddRefEntityToScene( &model );
                        // show the target
                        model.origin[2] += 56;
                        model.hModel = cgs.media.overloadTargetModel;
                        trap_R_AddRefEntityToScene( &model );
                }
        }
        else if ( cgs.gametype == GT_BOMB ) {
                // show harvester model
                memset(&model, 0, sizeof(model));
                model.reType = RT_MODEL;
                VectorCopy( cent->lerpOrigin, model.lightingOrigin );
                VectorCopy( cent->lerpOrigin, model.origin );
                AnglesToAxis( cent->currentState.angles, model.axis );

                if ( cent->currentState.modelindex == TEAM_RED ) {
                        model.hModel = cgs.media.harvesterModel;
                        model.customSkin = cgs.media.harvesterRedSkin;
                }
                else if ( cent->currentState.modelindex == TEAM_BLUE ) {
                        model.hModel = cgs.media.harvesterModel;
                        model.customSkin = cgs.media.harvesterBlueSkin;
                }
                else {
                        model.hModel = cgs.media.harvesterNeutralModel;
                        model.customSkin = 0;
                }
                trap_R_AddRefEntityToScene( &model );
        }
#endif
}

/*
===============
CG_AddCEntity

===============
*/
static void CG_AddCEntity( centity_t *cent ) {
        // event-only entities will have been dealt with already
        if ( cent->currentState.eType >= ET_EVENTS ) {
                return;
        }

        // calculate the current origin
        CG_CalcEntityLerpPositions( cent );

        // add automatic effects
        CG_EntityEffects( cent );

        switch ( cent->currentState.eType ) {
        default:
                CG_Error( "Bad entity type: %i\n", cent->currentState.eType );
                break;
        case ET_INVISIBLE:
        case ET_PUSH_TRIGGER:
        case ET_TELEPORT_TRIGGER:
                break;
        case ET_GENERAL:
                CG_General( cent );
                break;
        case ET_PLAYER:
                CG_Player( cent );
                break;
        case ET_ITEM:
                CG_Item( cent );
                break;
        case ET_MISSILE:
                CG_Missile( cent );
                break;
        case ET_MOVER:
                CG_Mover( cent );
                break;
        case ET_BREAKABLE: //Xamis
                CG_Mover( cent );
                break;
        case ET_WALL: //Xamis
                CG_Mover( cent );
                break;
        case ET_BEAM:
                CG_Beam( cent );
                break;
        case ET_PORTAL:
                CG_Portal( cent );
                break;
        case ET_SPEAKER:
                CG_Speaker( cent );
                break;
        case ET_GRAPPLE:
                CG_Grapple( cent );
                break;
        case ET_TEAM:
                CG_TeamBase( cent );
                break;
        }
}

/*
===============
CG_AddPacketEntities

===============
*/
void CG_AddPacketEntities( void ) {
        int                                     num;
        centity_t                       *cent;
        playerState_t           *ps;

        // set cg.frameInterpolation
        if ( cg.nextSnap ) {
                int             delta;

                delta = (cg.nextSnap->serverTime - cg.snap->serverTime);
                if ( delta == 0 ) {
                        cg.frameInterpolation = 0;
                } else {
                        cg.frameInterpolation = (float)( cg.time - cg.snap->serverTime ) / delta;
                }
        } else {
                cg.frameInterpolation = 0;      // actually, it should never be used, because
                                                                        // no entities should be marked as interpolating
        }

        // the auto-rotating items will all have the same axis
        cg.autoAngles[0] = 0;
        cg.autoAngles[1] = ( cg.time & 2047 ) * 360 / 2048.0;
        cg.autoAngles[2] = 0;

        cg.autoAnglesFast[0] = 0;
        cg.autoAnglesFast[1] = ( cg.time & 1023 ) * 360 / 1024.0f;
        cg.autoAnglesFast[2] = 0;

        AnglesToAxis( cg.autoAngles, cg.autoAxis );
        AnglesToAxis( cg.autoAnglesFast, cg.autoAxisFast );

        // generate and add the entity from the playerstate
        ps = &cg.predictedPlayerState;
        BG_PlayerStateToEntityState( ps, &cg.predictedPlayerEntity.currentState, qfalse );
        CG_AddCEntity( &cg.predictedPlayerEntity );

        // lerp the non-predicted value for lightning gun origins
        CG_CalcEntityLerpPositions( &cg_entities[ cg.snap->ps.clientNum ] );

        // add each entity sent over by the server
        for ( num = 0 ; num < cg.snap->numEntities ; num++ ) {
                cent = &cg_entities[ cg.snap->entities[ num ].number ];
                CG_AddCEntity( cent );
        }
}

