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
// cg_weapons.c -- events and effects dealing with weapons
#include "cg_local.h"

/* [QUARANTINE] - Weapon Animations - CG_ParseWeaponAnimFile
==========================
CG_ParseWeaponAnimFile
==========================
*/
static qboolean CG_ParseWeaponAnimFile( const char *filename, weaponInfo_t *weapon ) {
  char *text_p;
  int len;
  int i;
  char *token;
  float fps;
  int skip;
  char text[20000];
  fileHandle_t f;
  animation_t *animations;

  animations = weapon->animations;

// load the file
  len = trap_FS_FOpenFile( filename, &f, FS_READ );
  if ( len <= 0 ) {
    return qfalse;
  }
  if ( len >= sizeof( text ) - 1 ) {
    CG_Printf( "File %s too long\n", filename );
    return qfalse;
  }
  trap_FS_Read( text, len, f );
  text[len] = 0;
  trap_FS_FCloseFile( f );

// parse the text
  text_p = text;
  skip = 0; // quite the compiler warning

// read information for each frame
  for ( i = 0 ; i < MAX_WEAPON_ANIMATIONS ; i++ ) {
    token = COM_Parse( &text_p );
    if ( !token ) break;
    animations[i].firstFrame = atoi( token );
    token = COM_Parse( &text_p );
    if ( !token ) break;
    animations[i].numFrames = atoi( token );
    token = COM_Parse( &text_p );
    if ( !token ) break;
    animations[i].loopFrames = atoi( token );
    token = COM_Parse( &text_p );
    if ( !token ) break;
    fps = atof( token );
    if ( fps == 0 ) fps = 1;
    animations[i].frameLerp = 1000 / fps;
    animations[i].initialLerp = 1000 / fps;
  }
  if ( i != MAX_WEAPON_ANIMATIONS ) {
    CG_Printf( "Error parsing weapon animation file: %s", filename );
    return qfalse;
  }

  return qtrue;
}
// END


/* Weapon Animation  Sounds --Xamis
==========================
CG_ParseWeaponSounds
==========================
*/

static qboolean CG_ParseWeaponSounds( const char *filename, weaponInfo_t *weapon ) {
  char *text_p;
  int len;
  int i;
  char *token;
  char text[20000];
  fileHandle_t f;
  soundList_t   *soundList;
  int j;
  sfxHandle_t tempSound;
 

  j=0; //prevent uninitialized compiler warnings -- Xamis
  tempSound = 0;
  soundList= weapon->sounds;
// load the file
  len = trap_FS_FOpenFile( filename, &f, FS_READ );
  if ( len <= 0 ) {
    return qfalse;
  }
  if ( len >= sizeof( text ) - 1 ) {
    CG_Printf( "File %s too long\n", filename );
    return qfalse;
  }
  trap_FS_Read( text, len, f );
  text[len] = 0;
  trap_FS_FCloseFile( f );

// parse the text
  text_p = text;


// read information for each frame
  for ( i = 0 ; i < 14 ; i++ ) {
     token = COM_Parse( &text_p );
          if ( !token ) break;
	if ( !Q_stricmp( token, "anim" ) ) {
		soundList[i].type =1; 
}
        if ( !Q_stricmp( token, "fire" ) ) {
                soundList[i].type =2;
}
     token =  COM_Parse( &text_p );
               if ( !token ) break;
     if ( soundList[i].type == 1)
     j = atoi(token);
     if ( soundList[i].type == 2){
	if ( !Q_stricmp( token, "inside" ) ) 
		j=1;
	if ( !Q_stricmp( token, "outside" ) )
		j=2;
	if ( !Q_stricmp( token, "water" ) )
		j=3;
                  if ( !Q_stricmp( token, "silenced" ) )
		j=4;
}
     token =  COM_Parse( &text_p );
               if ( !token ) break;
     if (Q_stricmp(token,""))
        tempSound = trap_S_RegisterSound( token, qfalse );
        soundList[i].soundPath = tempSound;
        soundList[i].startFrame = j;

#ifdef DEBUG
   CG_Printf( "Type = %i \t",soundList[i].type );
   CG_Printf( "Startframe = %s \t",soundList[i].startFrame  );
   CG_Printf( "Path = %s \n",soundList[i].soundPath );
#endif
      
}
  if ( i != 14 ) {
    CG_Printf( "Error parsing weapon sound file: %s", filename );
    return qfalse;
  }

  return qtrue;
}
// END




/*
==========================
CG_MachineGunEjectBrass
==========================
*/
static void CG_MachineGunEjectBrass( centity_t *cent ) {
        localEntity_t   *le;
        refEntity_t             *re;
        vec3_t                  velocity, xvelocity;
        vec3_t                  offset, xoffset;
        float                   waterScale = 1.0f;
        vec3_t                  v[3];

        if ( cg_brassTime.integer <= 0 ) {
                return;
        }

        le = CG_AllocLocalEntity();
        re = &le->refEntity;

        velocity[0] = 0;
        velocity[1] = -50 + 40 * crandom();
        velocity[2] = 100 + 50 * crandom();

        le->leType = LE_FRAGMENT;
        le->startTime = cg.time;
        le->endTime = le->startTime + cg_brassTime.integer + ( cg_brassTime.integer / 4 ) * random();

        le->pos.trType = TR_GRAVITY;
        le->pos.trTime = cg.time - (rand()&15);

        AnglesToAxis( cent->lerpAngles, v );

        offset[0] = 8;
        offset[1] = -4;
        offset[2] = 24;

        xoffset[0] = offset[0] * v[0][0] + offset[1] * v[1][0] + offset[2] * v[2][0];
        xoffset[1] = offset[0] * v[0][1] + offset[1] * v[1][1] + offset[2] * v[2][1];
        xoffset[2] = offset[0] * v[0][2] + offset[1] * v[1][2] + offset[2] * v[2][2];
        VectorAdd( cent->lerpOrigin, xoffset, re->origin );

        VectorCopy( re->origin, le->pos.trBase );

        if ( CG_PointContents( re->origin, -1 ) & CONTENTS_WATER ) {
                waterScale = 0.10f;
        }

        xvelocity[0] = velocity[0] * v[0][0] + velocity[1] * v[1][0] + velocity[2] * v[2][0];
        xvelocity[1] = velocity[0] * v[0][1] + velocity[1] * v[1][1] + velocity[2] * v[2][1];
        xvelocity[2] = velocity[0] * v[0][2] + velocity[1] * v[1][2] + velocity[2] * v[2][2];
        VectorScale( xvelocity, waterScale, le->pos.trDelta );

        AxisCopy( axisDefault, re->axis );
        re->hModel = cgs.media.machinegunBrassModel;

        le->bounceFactor = 0.4 * waterScale;

        le->angles.trType = TR_LINEAR;
        le->angles.trTime = cg.time;
        le->angles.trBase[0] = rand()&31;
        le->angles.trBase[1] = rand()&31;
        le->angles.trBase[2] = rand()&31;
        le->angles.trDelta[0] = 2;
        le->angles.trDelta[1] = 1;
        le->angles.trDelta[2] = 0;

        le->leFlags = LEF_TUMBLE;
        le->leBounceSoundType = LEBS_BRASS;
        le->leMarkType = LEMT_NONE;
}

/*
==========================
CG_ShotgunEjectBrass
==========================
*/
static void CG_ShotgunEjectBrass( centity_t *cent ) {
        localEntity_t   *le;
        refEntity_t             *re;
        vec3_t                  velocity, xvelocity;
        vec3_t                  offset, xoffset;
        vec3_t                  v[3];
        int                             i;

        if ( cg_brassTime.integer <= 0 ) {
                return;
        }
//   for ( i = 0; i < 2; i++ )  //Xamis, we only need one shell, not double barrel
    {
                float   waterScale = 1.0f;

                le = CG_AllocLocalEntity();
                re = &le->refEntity;
                i = 0;
                velocity[0] = 60 + 60 * crandom();
                if ( i == 0 ) {
                        velocity[1] = 40 + 10 * crandom();
                } else {
                        velocity[1] = -40 + 10 * crandom();
                }
                velocity[2] = 100 + 50 * crandom();

                le->leType = LE_FRAGMENT;
                le->startTime = cg.time;
                le->endTime = le->startTime + cg_brassTime.integer*3 + cg_brassTime.integer * random();

                le->pos.trType = TR_GRAVITY;
                le->pos.trTime = cg.time;

                AnglesToAxis( cent->lerpAngles, v );

                offset[0] = 8;
                offset[1] = 0;
                offset[2] = 24;

                xoffset[0] = offset[0] * v[0][0] + offset[1] * v[1][0] + offset[2] * v[2][0];
                xoffset[1] = offset[0] * v[0][1] + offset[1] * v[1][1] + offset[2] * v[2][1];
                xoffset[2] = offset[0] * v[0][2] + offset[1] * v[1][2] + offset[2] * v[2][2];
                VectorAdd( cent->lerpOrigin, xoffset, re->origin );
                VectorCopy( re->origin, le->pos.trBase );
                if ( CG_PointContents( re->origin, -1 ) & CONTENTS_WATER ) {
                        waterScale = 0.10f;
                }

                xvelocity[0] = velocity[0] * v[0][0] + velocity[1] * v[1][0] + velocity[2] * v[2][0];
                xvelocity[1] = velocity[0] * v[0][1] + velocity[1] * v[1][1] + velocity[2] * v[2][1];
                xvelocity[2] = velocity[0] * v[0][2] + velocity[1] * v[1][2] + velocity[2] * v[2][2];
                VectorScale( xvelocity, waterScale, le->pos.trDelta );

                AxisCopy( axisDefault, re->axis );
                re->hModel = cgs.media.shotgunBrassModel;
                le->bounceFactor = 0.3f;

                le->angles.trType = TR_LINEAR;
                le->angles.trTime = cg.time;
                le->angles.trBase[0] = rand()&31;
                le->angles.trBase[1] = rand()&31;
                le->angles.trBase[2] = rand()&31;
                le->angles.trDelta[0] = 1;
                le->angles.trDelta[1] = 0.5;
                le->angles.trDelta[2] = 0;

                le->leFlags = LEF_TUMBLE;
                le->leBounceSoundType = LEBS_BRASS;
                le->leMarkType = LEMT_NONE;
        }
}



/*
==========================
CG_RailTrail
==========================
*/
void CG_RailTrail (clientInfo_t *ci, vec3_t start, vec3_t end) {
        vec3_t axis[36], move, move2, next_move, vec, temp;
        float  len;
        int    i, j, skip;

        localEntity_t *le;
        refEntity_t   *re;

#define RADIUS   4
#define ROTATION 1
#define SPACING  5

        start[2] -= 4;

        le = CG_AllocLocalEntity();
        re = &le->refEntity;

        le->leType = LE_FADE_RGB;
        le->startTime = cg.time;
        le->endTime = cg.time + cg_railTrailTime.value;
        le->lifeRate = 1.0 / (le->endTime - le->startTime);

        re->shaderTime = cg.time / 1000.0f;
        re->reType = RT_RAIL_CORE;
        re->customShader = cgs.media.railCoreShader;

        VectorCopy(start, re->origin);
        VectorCopy(end, re->oldorigin);

        re->shaderRGBA[0] = ci->color1[0] * 255;
        re->shaderRGBA[1] = ci->color1[1] * 255;
        re->shaderRGBA[2] = ci->color1[2] * 255;
        re->shaderRGBA[3] = 255;

        le->color[0] = ci->color1[0] * 0.75;
        le->color[1] = ci->color1[1] * 0.75;
        le->color[2] = ci->color1[2] * 0.75;
        le->color[3] = 1.0f;

        AxisClear( re->axis );

        if (cg_oldRail.integer)
        {
                // nudge down a bit so it isn't exactly in center
                re->origin[2] -= 8;
                re->oldorigin[2] -= 8;
                return;
        }

        VectorCopy (start, move);
        VectorSubtract (end, start, vec);
        len = VectorNormalize (vec);
        PerpendicularVector(temp, vec);
        for (i = 0 ; i < 36; i++)
        {
                RotatePointAroundVector(axis[i], vec, temp, i * 10);//banshee 2.4 was 10
        }

        VectorMA(move, 20, vec, move);
        VectorCopy(move, next_move);
        VectorScale (vec, SPACING, vec);

        skip = -1;

        j = 18;
        for (i = 0; i < len; i += SPACING)
        {
                if (i != skip)
                {
                        skip = i + SPACING;
                        le = CG_AllocLocalEntity();
                        re = &le->refEntity;
                        le->leFlags = LEF_PUFF_DONT_SCALE;
                        le->leType = LE_MOVE_SCALE_FADE;
                        le->startTime = cg.time;
                        le->endTime = cg.time + (i>>1) + 600;
                        le->lifeRate = 1.0 / (le->endTime - le->startTime);

                        re->shaderTime = cg.time / 1000.0f;
                        re->reType = RT_SPRITE;
                        re->radius = 1.1f;
                        re->customShader = cgs.media.railRingsShader;

                        re->shaderRGBA[0] = ci->color2[0] * 255;
                        re->shaderRGBA[1] = ci->color2[1] * 255;
                        re->shaderRGBA[2] = ci->color2[2] * 255;
                        re->shaderRGBA[3] = 255;

                        le->color[0] = ci->color2[0] * 0.75;
                        le->color[1] = ci->color2[1] * 0.75;
                        le->color[2] = ci->color2[2] * 0.75;
                        le->color[3] = 1.0f;

                        le->pos.trType = TR_LINEAR;
                        le->pos.trTime = cg.time;

                        VectorCopy( move, move2);
                        VectorMA(move2, RADIUS , axis[j], move2);
                        VectorCopy(move2, le->pos.trBase);

                        le->pos.trDelta[0] = axis[j][0]*6;
                        le->pos.trDelta[1] = axis[j][1]*6;
                        le->pos.trDelta[2] = axis[j][2]*6;
                }

                VectorAdd (move, vec, move);

                j = (j + ROTATION) % 36;
        }
}

/*
==========================
CG_RocketTrail
==========================
*/
static void CG_RocketTrail( centity_t *ent, const weaponInfo_t *wi ) {
        int             step;
        vec3_t  origin, lastPos;
        int             t;
        int             startTime, contents;
        int             lastContents;
        entityState_t   *es;
        vec3_t  up;
        localEntity_t   *smoke;

        if ( cg_noProjectileTrail.integer ) {
                return;
        }

        up[0] = 0;
        up[1] = 0;
        up[2] = 0;

        step = 50;

        es = &ent->currentState;
        startTime = ent->trailTime;
        t = step * ( (startTime + step) / step );

        BG_EvaluateTrajectory( &es->pos, cg.time, origin );
        contents = CG_PointContents( origin, -1 );

        // if object (e.g. grenade) is stationary, don't toss up smoke
        if ( es->pos.trType == TR_STATIONARY ) {
                ent->trailTime = cg.time;
                return;
        }

        BG_EvaluateTrajectory( &es->pos, ent->trailTime, lastPos );
        lastContents = CG_PointContents( lastPos, -1 );

        ent->trailTime = cg.time;

        if ( contents & ( CONTENTS_WATER | CONTENTS_SLIME | CONTENTS_LAVA ) ) {
                if ( contents & lastContents & CONTENTS_WATER ) {
                        CG_BubbleTrail( lastPos, origin, 8 );
                }
                return;
        }

        for ( ; t <= ent->trailTime ; t += step ) {
                BG_EvaluateTrajectory( &es->pos, t, lastPos );

                smoke = CG_SmokePuff( lastPos, up,
                                          wi->trailRadius,
                                          1, 1, 1, 0.33f,
                                          wi->wiTrailTime,
                                          t,
                                          0,
                                          0,
                                          cgs.media.smokePuffShader );
                // use the optimized local entity add
                smoke->leType = LE_SCALE_FADE;
        }

}


/*
==========================
CG_GrappleTrail
==========================
*/
void CG_GrappleTrail( centity_t *ent, const weaponInfo_t *wi ) {
        vec3_t  origin;
        entityState_t   *es;
        vec3_t                  forward, up;
        refEntity_t             beam;

        es = &ent->currentState;

        BG_EvaluateTrajectory( &es->pos, cg.time, origin );
        ent->trailTime = cg.time;

        memset( &beam, 0, sizeof( beam ) );
        //FIXME adjust for muzzle position
        VectorCopy ( cg_entities[ ent->currentState.otherEntityNum ].lerpOrigin, beam.origin );
        beam.origin[2] += 26;
        AngleVectors( cg_entities[ ent->currentState.otherEntityNum ].lerpAngles, forward, NULL, up );
        VectorMA( beam.origin, -6, up, beam.origin );
        VectorCopy( origin, beam.oldorigin );

        if (Distance( beam.origin, beam.oldorigin ) < 64 )
                return; // Don't draw if close

        beam.reType = RT_LIGHTNING;
        beam.customShader = cgs.media.lightningShader;

        AxisClear( beam.axis );
        beam.shaderRGBA[0] = 0xff;
        beam.shaderRGBA[1] = 0xff;
        beam.shaderRGBA[2] = 0xff;
        beam.shaderRGBA[3] = 0xff;
        trap_R_AddRefEntityToScene( &beam );
}

/*
==========================
CG_GrenadeTrail
==========================
*/
static void CG_GrenadeTrail( centity_t *ent, const weaponInfo_t *wi ) {
        CG_RocketTrail( ent, wi );
}


/*
=================
CG_RegisterWeapon

The server says this item is used on this level
=================
*/
void CG_RegisterWeapon( int weaponNum ) {
        weaponInfo_t    *weaponInfo;
        gitem_t                 *item, *ammo;
        char                    path[MAX_QPATH];
        vec3_t                  mins, maxs;
        int                             i;

        weaponInfo = &cg_weapons[weaponNum];

        if ( weaponNum == 0 ) {
                return;
        }

        if ( weaponInfo->registered ) {
                return;
        }

        memset( weaponInfo, 0, sizeof( *weaponInfo ) );
        weaponInfo->registered = qtrue;

        for ( item = bg_itemlist + 1 ; item->classname ; item++ ) {
                if ( item->giType == IT_WEAPON && item->giTag == weaponNum ) {
                        weaponInfo->item = item;
                        break;
                }
        }
        if ( !item->classname ) {
                CG_Error( "Couldn't find weapon %i", weaponNum );
        }
        CG_RegisterItemVisuals( item - bg_itemlist );

        // load cmodel before model so filecache works
        weaponInfo->weaponModel = trap_R_RegisterModel( item->world_model[0] );

        // calc midpoint for rotation
        trap_R_ModelBounds( weaponInfo->weaponModel, mins, maxs );
        for ( i = 0 ; i < 3 ; i++ ) {
                weaponInfo->weaponMidpoint[i] = mins[i] + 0.5 * ( maxs[i] - mins[i] );
        }

        weaponInfo->weaponIcon = trap_R_RegisterShader( item->icon );
        weaponInfo->ammoIcon = trap_R_RegisterShader( bg_weaponlist[ weaponNum ].ammoIcon );

        for ( ammo = bg_itemlist + 1 ; ammo->classname ; ammo++ ) {
                if ( ammo->giType == IT_AMMO && ammo->giTag == weaponNum ) {
                        break;
                }
        }
        if ( ammo->classname && ammo->world_model[0] ) {
                weaponInfo->ammoModel = trap_R_RegisterModel( ammo->world_model[0] );
        }

// Load all weapons animation config files --Xamis
            strcpy( path, item->world_model[0] );
            COM_StripExtension(path, path, sizeof(path));
            strcat( path, ".cfg" );
            if ( !CG_ParseWeaponAnimFile(path, weaponInfo) ) {
              Com_Printf("Failed to load weapon animation file %s\n", path);

            }
// Load all weapons sound config files --Xamis
            strcpy( path, bg_weaponlist[ weaponNum ].modelPath );
            strcat( path, "sound.cfg" );
            if ( !CG_ParseWeaponSounds(path, weaponInfo) ) {
              Com_Printf("Failed to load weapon sound file %s/n", path);
              }


//  All weapons parts for animations in first person view --Xamis

        weaponInfo->flashModel = trap_R_RegisterModel( "models/weapons2/flash/flash.md3" );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_barrel.md3" );
        weaponInfo->barrelModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_hold.md3" );
        weaponInfo->holdsModel = trap_R_RegisterModel( path );


        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_main.md3" );
        weaponInfo->vmainModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_bolt.md3" );
        weaponInfo->vboltModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_trigger.md3" );
        weaponInfo->vtriggerModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_ejector.md3" );
        weaponInfo->vejectorModel = trap_R_RegisterModel( path );


        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_mode.md3" );
        weaponInfo->vmodeModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_clip.md3" );
        weaponInfo->vclipModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_cliprel.md3" );
        weaponInfo->vcliprelModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_flap.md3" );
        weaponInfo->vflapModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_butt.md3" );
        weaponInfo->vbuttModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_cock.md3" );
        weaponInfo->vcockModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_slide.md3" );
        weaponInfo->vslideModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_barrel.md3" );
        weaponInfo->vbarrelModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_sliderel.md3" );
        weaponInfo->vsliderelModel = trap_R_RegisterModel( path );


        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_pin.md3" );
        weaponInfo->vpinModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_ring.md3" );
        weaponInfo->vringModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_box.md3" );
        weaponInfo->vboxModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_flap2.md3" );
        weaponInfo->vflap2Model = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_flap1.md3" );
        weaponInfo->vflap1Model = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_grenade.md3" );
        weaponInfo->vgrenadeModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_shell.md3" );
        weaponInfo->vshellModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_aim.md3" );
        weaponInfo->vaimModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_handle.md3" );
        weaponInfo->vhandleModel = trap_R_RegisterModel( path );

        strcpy( path, item->world_model[0] );
        COM_StripExtension(path, path, sizeof(path));
        strcat( path, "_view_bullet.md3" );
        weaponInfo->vbulletModel = trap_R_RegisterModel( path );

        weaponInfo->vs_shellModel = trap_R_RegisterModel( "models/weapons2/shells/s_shell.md3" );

        weaponInfo->handsModel = trap_R_RegisterModel( "models/weapons2/handskins/hands.md3" );
        weaponInfo->silencerModel = trap_R_RegisterModel( "models/weapons2/M4/M4_silencer.md3" );
        weaponInfo->laserModel = trap_R_RegisterModel( "models/weapons2/M4/M4_laser.md3" );
        if ( !weaponInfo->handsModel ) {
                weaponInfo->handsModel = trap_R_RegisterModel( "models/weapons2/shotgun/shotgun_hand.md3" );
        }

        weaponInfo->loopFireSound = qfalse;

        switch ( weaponNum ) {
        case WP_KNIFE:
                MAKERGB( weaponInfo->flashDlightColor, 0.6f, 0.6f, 1.0f );
                weaponInfo->firingSound = trap_S_RegisterSound( "sound/weapons/knife/slashmiss.wav", qfalse );
                weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/knife/slashmiss.wav", qfalse );
                weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/knife/slashmiss.wav", qfalse );
                break;
                case WP_M4:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/m4/m4.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/m4/m4_sil.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/m4/m4.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
                        break;
                case WP_PSG1:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/psg1/psg1.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/psg1/psg1_sil.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/psg1/psg1.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
                        break;

                case WP_SR8:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/sr8/sr8.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/sr8/sr8.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/sr8/sr8.wav", qfalse );
                       // weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
                        break;

                case WP_AK103:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/ak103/ak103.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/ak103/ak103_sil.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/ak103/ak103.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
                        break;

                case WP_LR300:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/zm300/lr.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/zm300/lr_sil.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/zm300/lr.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
                        break;

                case WP_G36:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/g36/g36.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/g36/g36_sil.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/g36/g36.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
                        break;
                case WP_MP5K:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/mp5k/mp5k.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/ump45/ump45_sil.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/mp5k/mp5k.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;

                        break;
                case WP_UMP45:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/ump45/ump45.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/ump45/ump45_sil.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/ump45/ump45.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
                        break;

                case WP_BERETTA:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/beretta/beretta.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/beretta/beretta_sil.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/beretta/beretta.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
                        break;

                case WP_DEAGLE:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/de/de.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/de/de_sil.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/de/de.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
                        break;
                case WP_SPAS:
                        MAKERGB( weaponInfo->flashDlightColor, 1, 1, 0 );
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/spas/spas.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/spas/spas.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_ShotgunEjectBrass;
                        break;
                case WP_NEGEV:
                        weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/negev/negev.wav", qfalse );
                        weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/negev/negev_sil.wav", qfalse );
                        weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/negev/negev.wav", qfalse );
                        weaponInfo->ejectBrassFunc = CG_MachineGunEjectBrass;
                        break;
        case WP_HK69:
                weaponInfo->missileModel = trap_R_RegisterModel( "models/ammo/grenade1.md3" );
                weaponInfo->missileTrailFunc = CG_GrenadeTrail;
                weaponInfo->wiTrailTime = 700;
                weaponInfo->trailRadius = 32;
                MAKERGB( weaponInfo->flashDlightColor, 1, 0.70f, 0 );
                weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/gl/gl.wav", qfalse );
                weaponInfo->normalSound[0] = trap_S_RegisterSound( "sound/weapons/gl/gl.wav", qfalse );
                weaponInfo->silenceSound[0] = trap_S_RegisterSound( "sound/weapons/gl/gl.wav", qfalse );
                cgs.media.grenadeExplosionShader = trap_R_RegisterShader( "grenadeExplosion" );
                break;
        case WP_HE:
                weaponInfo->missileModel = trap_R_RegisterModel( "models/weapons2/grenade/grenade.MD3" );
                break;
      case WP_SMOKE:
                weaponInfo->missileModel = trap_R_RegisterModel( "models/weapons2/grenade/grenade.MD3" );
                weaponInfo->missileTrailFunc = CG_GrenadeTrail;
                weaponInfo->wiTrailTime = 2000;
                weaponInfo->trailRadius = 232;
                MAKERGB( weaponInfo->flashDlightColor, 1, 0.70f, 0 );
                break;
               

         default:
                MAKERGB( weaponInfo->flashDlightColor, 1, 1, 1 );
                weaponInfo->flashSound[0] = trap_S_RegisterSound( "sound/weapons/ak103/ak103.wav", qfalse );
                break;
        }
}

/*
=================
CG_RegisterItemVisuals

The server says this item is used on this level
=================
*/
void CG_RegisterItemVisuals( int itemNum ) {
        itemInfo_t              *itemInfo;
        gitem_t                 *item;

        if ( itemNum < 0 || itemNum >= bg_numItems ) {
                CG_Error( "CG_RegisterItemVisuals: itemNum %d out of range [0-%d]", itemNum, bg_numItems-1 );
        }

        itemInfo = &cg_items[ itemNum ];
        if ( itemInfo->registered ) {
                return;
        }

        item = &bg_itemlist[ itemNum ];

        memset( itemInfo, 0, sizeof( &itemInfo ) );
        itemInfo->registered = qtrue;

        itemInfo->models[0] = trap_R_RegisterModel( item->world_model[0] );

        itemInfo->icon = trap_R_RegisterShader( item->icon );

        if ( item->giType == IT_WEAPON ) {
                CG_RegisterWeapon( item->giTag );
        }

        //
        // powerups have an accompanying ring or sphere
        //
        if ( item->giType == IT_POWERUP || item->giType == IT_HEALTH ||
                item->giType == IT_ARMOR || item->giType == IT_HOLDABLE ) {
                if ( item->world_model[1] ) {
                        itemInfo->models[1] = trap_R_RegisterModel( item->world_model[1] );
                }
        }
}



/*
========================================================================================

VIEW WEAPON

========================================================================================
*/

/*
=================
CG_MapTorsoToWeaponFrame

=================
*/
static int CG_MapTorsoToWeaponFrame( clientInfo_t *ci, int frame ) {

        // change weapon
        if ( frame >= ci->animations[TORSO_DROP].firstFrame
                && frame < ci->animations[TORSO_DROP].firstFrame + 9 ) {
                return frame - ci->animations[TORSO_DROP].firstFrame + 6;
        }
        
        // stand attack
        if ( frame >= ci->animations[TORSO_ATTACK].firstFrame
                && frame < ci->animations[TORSO_ATTACK].firstFrame + 6 ) {
                return 1 + frame - ci->animations[TORSO_ATTACK].firstFrame;
        }

        // stand attack 2
        if ( frame >= ci->animations[TORSO_ATTACK2].firstFrame
                && frame < ci->animations[TORSO_ATTACK2].firstFrame + 6 ) {
                return 1 + frame - ci->animations[TORSO_ATTACK2].firstFrame;
        }

        return 0;
}


/*
==============
CG_CalculateWeaponPosition
==============
*/
static void CG_CalculateWeaponPosition( vec3_t origin, vec3_t angles ) {
        float   scale;
        int             delta;
        float   fracsin;

        VectorCopy( cg.refdef.vieworg, origin );
        VectorCopy( cg.refdefViewAngles, angles );

        // on odd legs, invert some angles
        if ( cg.bobcycle & 1 ) {
                scale = -cg.xyspeed;
        } else {
                scale = cg.xyspeed;
        }

        // gun angles from bobbing
        angles[ROLL] += scale * cg.bobfracsin * 0.005;
        angles[YAW] += scale * cg.bobfracsin * 0.01;
        angles[PITCH] += cg.xyspeed * cg.bobfracsin * 0.005;

        // drop the weapon when landing
        delta = cg.time - cg.landTime;
        if ( delta < LAND_DEFLECT_TIME ) {
                origin[2] += cg.landChange*0.25 * delta / LAND_DEFLECT_TIME;
        } else if ( delta < LAND_DEFLECT_TIME + LAND_RETURN_TIME ) {
                origin[2] += cg.landChange*0.25 *
                        (LAND_DEFLECT_TIME + LAND_RETURN_TIME - delta) / LAND_RETURN_TIME;
        }

#if 0
        // drop the weapon when stair climbing
        delta = cg.time - cg.stepTime;
        if ( delta < STEP_TIME/2 ) {
                origin[2] -= cg.stepChange*0.25 * delta / (STEP_TIME/2);
        } else if ( delta < STEP_TIME ) {
                origin[2] -= cg.stepChange*0.25 * (STEP_TIME - delta) / (STEP_TIME/2);
        }
#endif

        // idle drift
        scale = cg.xyspeed + 40;
        fracsin = sin( cg.time * 0.001 );
        angles[ROLL] += scale * fracsin * 0.01;
        angles[YAW] += scale * fracsin * 0.01;
        angles[PITCH] += scale * fracsin * 0.01;
}


/*
===============
CG_LightningBolt

Origin will be the exact tag point, which is slightly
different than the muzzle point used for determining hits.
The cent should be the non-predicted cent if it is from the player,
so the endpoint will reflect the simulated strike (lagging the predicted
angle)
===============
*/
static void CG_LightningBolt( centity_t *cent, vec3_t origin ) {
}
/*

static void CG_LightningBolt( centity_t *cent, vec3_t origin ) {
        trace_t         trace;
        refEntity_t             beam;
        vec3_t                  forward;
        vec3_t                  muzzlePoint, endPoint;

        if ( cent->currentState.weapon != WP_LIGHTNING ) {
                return;
        }

        memset( &beam, 0, sizeof( beam ) );

        // find muzzle point for this frame
        VectorCopy( cent->lerpOrigin, muzzlePoint );
        AngleVectors( cent->lerpAngles, forward, NULL, NULL );

        // FIXME: crouch
        muzzlePoint[2] += DEFAULT_VIEWHEIGHT;

        VectorMA( muzzlePoint, 14, forward, muzzlePoint );

        // project forward by the lightning range
        VectorMA( muzzlePoint, LIGHTNING_RANGE, forward, endPoint );

        // see if it hit a wall
        CG_Trace( &trace, muzzlePoint, vec3_origin, vec3_origin, endPoint,
                cent->currentState.number, MASK_SHOT );

        // this is the endpoint
        VectorCopy( trace.endpos, beam.oldorigin );

        // use the provided origin, even though it may be slightly
        // different than the muzzle origin
        VectorCopy( origin, beam.origin );

        beam.reType = RT_LIGHTNING;
        beam.customShader = cgs.media.lightningShader;
        trap_R_AddRefEntityToScene( &beam );

        // add the impact flare if it hit something
        if ( trace.fraction < 1.0 ) {
                vec3_t  angles;
                vec3_t  dir;

                VectorSubtract( beam.oldorigin, beam.origin, dir );
                VectorNormalize( dir );

                memset( &beam, 0, sizeof( beam ) );
                beam.hModel = cgs.media.lightningExplosionModel;

                VectorMA( trace.endpos, -16, dir, beam.origin );

                // make a random orientation
                angles[0] = rand() % 360;
                angles[1] = rand() % 360;
                angles[2] = rand() % 360;
                AnglesToAxis( angles, beam.axis );
                trap_R_AddRefEntityToScene( &beam );
        }
}
*/

/*
========================
CG_AddWeaponWithPowerups
========================
*/
static void CG_AddWeaponWithPowerups( refEntity_t *gun, int powerups ) {
        // add powerup effects


                trap_R_AddRefEntityToScene( gun );
/*
                if ( powerups & ( 1 << PW_BATTLESUIT ) ) {
                        gun->customShader = cgs.media.battleWeaponShader;
                        trap_R_AddRefEntityToScene( gun );
                }
                if ( powerups & ( 1 << PW_QUAD ) ) {
                        gun->customShader = cgs.media.quadWeaponShader;
                        trap_R_AddRefEntityToScene( gun );
} */

}
/*
===============
CG_Tracer
===============
*/
void CG_Tracer( vec3_t source, vec3_t dest, float width, qhandle_t shader, vec4_t rgba ) {
    vec3_t		forward, right;
    polyVert_t	verts[4];
    vec3_t		line;
    float		len, begin, end;
    vec3_t		start, finish;
    //	vec3_t		midpoint;

    // tracer
    VectorSubtract( dest, source, forward );
    len = VectorNormalize( forward );

    // start at least a little ways from the muzzle
    // begin = width * -0.5;
    begin = width * -0.5; // put 1 meter in front of the attacker
    end = len + width * 0.5;

    VectorMA( source, begin, forward, start );
    VectorMA( source, end, forward, finish );
    line[0] = DotProduct( forward, cg.refdef.viewaxis[1] );
    line[1] = DotProduct( forward, cg.refdef.viewaxis[2] );

    VectorScale( cg.refdef.viewaxis[1], line[1], right );
    VectorMA( right, -line[0], cg.refdef.viewaxis[2], right );
    VectorNormalize( right );

    VectorMA( finish, width, right, verts[0].xyz );
    verts[0].st[0] = 0;
    verts[0].st[1] = 1;
    verts[0].modulate[0] = 255 * rgba[0];
    verts[0].modulate[1] = 255 * rgba[1];
    verts[0].modulate[2] = 255 * rgba[2];
    verts[0].modulate[3] = 255 * rgba[3];

    VectorMA( finish, -width, right, verts[1].xyz );
    verts[1].st[0] = 1;
    verts[1].st[1] = 1;
    verts[1].modulate[0] = 255 * rgba[0];
    verts[1].modulate[1] = 255 * rgba[1];
    verts[1].modulate[2] = 255 * rgba[2];
    verts[1].modulate[3] = 255 * rgba[3];

    VectorMA( start, -width, right, verts[2].xyz );
    verts[2].st[0] = 1;
    verts[2].st[1] = 0;
    verts[2].modulate[0] = 255 * rgba[0];
    verts[2].modulate[1] = 255 * rgba[1];
    verts[2].modulate[2] = 255 * rgba[2];
    verts[2].modulate[3] = 255 * rgba[3];

    VectorMA( start, width, right, verts[3].xyz );
    verts[3].st[0] = 0;
    verts[3].st[1] = 0;
    verts[3].modulate[0] = 255 * rgba[0];
    verts[3].modulate[1] = 255 * rgba[1];
    verts[3].modulate[2] = 255 * rgba[2];
    verts[3].modulate[3] = 255 * rgba[3];

    trap_R_AddPolyToScene( shader, 4, verts );

}


/*
======================
CG_CalcMuzzlePoint
======================
*/
static qboolean CG_CalcMuzzlePoint( int entityNum, vec3_t muzzle ) {
        vec3_t          forward;
        centity_t       *cent;
        int                     anim;

        if ( entityNum == cg.snap->ps.clientNum ) {
                VectorCopy( cg.snap->ps.origin, muzzle );
                muzzle[2] += cg.snap->ps.viewheight;
                AngleVectors( cg.snap->ps.viewangles, forward, NULL, NULL );
                VectorMA( muzzle, 14, forward, muzzle );
                return qtrue;
        }

        cent = &cg_entities[entityNum];
        if ( !cent->currentValid ) {
                return qfalse;
        }

        VectorCopy( cent->currentState.pos.trBase, muzzle );

        AngleVectors( cent->currentState.apos.trBase, forward, NULL, NULL );
        anim = cent->currentState.legsAnim & ~ANIM_TOGGLEBIT;
        if ( anim == LEGS_WALKCR || anim == LEGS_IDLECR ) {
                muzzle[2] += CROUCH_VIEWHEIGHT;
        } else {
                muzzle[2] += DEFAULT_VIEWHEIGHT;
        }

        VectorMA( muzzle, 14, forward, muzzle );

        return qtrue;

}

void CG_RenderLaser(centity_t *cent){

        vec3_t forward;
        trace_t		trace;
        vec3_t		muzzlePoint, endPoint;
        refEntity_t		beam;
        qhandle_t laserBeam;
        int	rf;
        int anim;
                    
                    
        memset( &beam, 0, sizeof( beam ) );
        anim = cent->currentState.legsAnim & ~ANIM_TOGGLEBIT;
        rf = 0;

        VectorCopy ( cent->lerpOrigin,muzzlePoint );

            if ( anim == LEGS_WALKCR  || anim == LEGS_BACKCR || anim == LEGS_IDLECR )
               muzzlePoint[2] += CROUCH_VIEWHEIGHT +1;
            else
                muzzlePoint[2] += DEFAULT_VIEWHEIGHT +1;


        AngleVectors( cent->currentState.apos.trBase , forward, NULL, NULL );


        VectorMA( cent->lerpOrigin, 8192*16, forward, endPoint );

        { 
            if ( anim == LEGS_WALKCR  || anim == LEGS_BACKCR || anim == LEGS_IDLECR )
                endPoint[2] += CROUCH_VIEWHEIGHT +1;
            else
                endPoint[2] += DEFAULT_VIEWHEIGHT +1;
        }

        endPoint[0] +=1.6;
        laserBeam = trap_R_RegisterShader( "laserShader" );
        // see if it hit a wall
        CG_Trace( &trace, muzzlePoint, vec3_origin, vec3_origin, endPoint,
                  cent->currentState.number, MASK_SHOT );

        VectorCopy( trace.endpos , endPoint );

        if (! (CG_PointContents( muzzlePoint, cent->currentState.number ) & CONTENTS_SOLID) &&
                !trace.startsolid )
        {

            // add the impact flare if it hit something
            if ( trace.fraction < 1.0 ) {

                beam.customShader = cgs.media.laserShader;
                beam.reType = RT_SPRITE;
                beam.radius = 1;

                beam.renderfx = rf;
                VectorMA( trace.endpos, -1.4, forward, beam.origin );
                 trap_R_AddRefEntityToScene( &beam );
         
      //  CG_Printf( "len is %f\n",len );


            }
        }
            
            
            
            
} 




/*
=============
CG_AddPlayerWeapon

Used for both the view weapon (ps is valid) and the world modelother character models (ps is NULL)
The main player will have this called for BOTH cases, so effects like light and
sound should only be done on the world model case.
=============
*/
void CG_AddPlayerWeapon( refEntity_t *parent, playerState_t *ps, centity_t *cent, int team, const char *modelName, const char *skin) {
	char            *tagname;
	refEntity_t     handsModel;
	refEntity_t     gun; //this is used for thirdperson weapon and firstperson hands model Xamis
	refEntity_t     viewmainModel; //firstperson weapon model
	refEntity_t     holds;
	refEntity_t     flash;
	refEntity_t     silencer;
	refEntity_t     laser;
	refEntity_t     vtrigger;
	refEntity_t     vbolt;
	refEntity_t     vclip;
	refEntity_t     vcliprel;
	refEntity_t     vejector;
	refEntity_t     vflap;
	refEntity_t     vflap1;
	refEntity_t     vflap2;
	refEntity_t     vbutt;
	refEntity_t     veject;
	refEntity_t     vmode;
	refEntity_t     vcock;
	refEntity_t     vbarrel;
	refEntity_t     vpin;
	refEntity_t     vring;
	refEntity_t     vslide;
	refEntity_t     vsliderel;
	refEntity_t     vbox;
	refEntity_t     vhandle;
	refEntity_t     vbullet;
	refEntity_t     vaim;
	refEntity_t     vshell;
	refEntity_t     vgrenade;
	refEntity_t     weaponModel;
        	refEntity_t     PriweaponModel;
                  refEntity_t     SecweaponModel;
                  refEntity_t     SidweaponModel;
	vec3_t          angles;
	weapon_t        weaponNum;
                  weapon_t        PriweaponNum;
                  weapon_t        SecweaponNum;
                  weapon_t        SidweaponNum;
	weaponInfo_t    *weapon;
                  weaponInfo_t    *weapon1;
                  weaponInfo_t    *weapon2;
                  weaponInfo_t    *weapon3;
	centity_t       *nonPredictedCent;
	orientation_t   lerped;
	int             powerups;
	clientInfo_t    *ci;
	//int i;
	qboolean lasersight;
	qboolean silenced;
	qboolean vestOn;	//needed for different torso weapon tag location
 	qboolean        weaponDown;
                  int            anim;

	vestOn = lasersight = silenced = qfalse;

	powerups = cent->currentState.powerups;

	weaponNum = cent->currentState.weapon;
        
                  SidweaponNum = CG_GetSidearm();
                  PriweaponNum = CG_GetPrimary();
                  SecweaponNum = CG_GetWorstSecondary();

                  
	CG_RegisterWeapon( weaponNum );
        	CG_RegisterWeapon( PriweaponNum );
                	CG_RegisterWeapon( SecweaponNum );
                  CG_RegisterWeapon( SidweaponNum );
                  
	weapon = &cg_weapons[weaponNum];
 	weapon1 = &cg_weapons[PriweaponNum];
        	weapon2 = &cg_weapons[SecweaponNum];
                	weapon3 = &cg_weapons[SidweaponNum];
                        
	ci = &cgs.clientinfo[cent->currentState.clientNum];

        
        
                        

	//Determine what items the user has --Xamis
            anim = cent->currentState.torsoAnim & ~ANIM_TOGGLEBIT;

            if ( anim == BOTH_CLIMB ||  anim == BOTH_CLIMB_IDLE || anim == TORSO_BANDAGE ){
                      weaponDown=qtrue;
                  } else
                      weaponDown=qfalse;
        
	if ( powerups & ( 1 << PW_SILENCER )&& !( cg.ItemToggleState & ( 1 << PW_SILENCER )) )
		silenced = qtrue;

	if ( powerups & ( 1 << PW_LASERSIGHT ) )
		lasersight = qtrue;
  

	if ( powerups & ( 1 << PW_VEST ) )
		vestOn = qtrue;


	memset( &handsModel, 0, sizeof( handsModel ) );
	VectorCopy( parent->lightingOrigin, handsModel.lightingOrigin );
	handsModel.shadowPlane = parent->shadowPlane;
	handsModel.renderfx = parent->renderfx;
	handsModel.hModel = weapon->handsModel;


	memset( &viewmainModel, 0, sizeof( viewmainModel ) );
	VectorCopy( parent->lightingOrigin, viewmainModel.lightingOrigin );
	viewmainModel.shadowPlane = parent->shadowPlane;
	viewmainModel.renderfx = parent->renderfx;
	viewmainModel.hModel = weapon->vmainModel;



	// add the hands

	memset( &holds, 0, sizeof( holds ) );
	VectorCopy( parent->lightingOrigin, holds.lightingOrigin );
	holds.customShader = cgs.media.handsBlueSkin;
	holds.shadowPlane = parent->shadowPlane;
	holds.renderfx = parent->renderfx;
	holds.hModel = weapon->holdsModel;

	// add the weapon
	memset( &gun, 0, sizeof( gun ) );
	VectorCopy( parent->lightingOrigin, gun.lightingOrigin );
	gun.shadowPlane = parent->shadowPlane;
	gun.renderfx = parent->renderfx;


	memset( &weaponModel, 0, sizeof( weaponModel ) );
	VectorCopy( parent->lightingOrigin, weaponModel.lightingOrigin );
	weaponModel.shadowPlane = parent->shadowPlane;
	weaponModel.renderfx = parent->renderfx;


	if(!ps)
	{
                                    weapon->handsModel = trap_R_RegisterModel( "models/weapons2/handskins/hands.md3" );
		gun.hModel = weapon->handsModel;
	}

	if(ps)
	{
		gun.hModel = weapon->holdsModel;

		if (cgs.gametype >= GT_TEAM)
		{
			if ( team == TEAM_RED )
			{
				gun.customSkin = cgs.media.handsRedSkin;
			}
			else
			{
				gun.customSkin = cgs.media.handsBlueSkin;
			}
		}
		else //this is a non-team GT
		{
			//need to set their hands skin based on their skin
			if (strcmp(skin, "cyan") == 0){
				gun.customSkin = cgs.media.handsCyanSkin; }
			else if (strcmp(skin, "darkred") == 0){
				gun.customSkin = cgs.media.handsDarkredSkin; }
			else if (strcmp(skin, "default") == 0){
				gun.customSkin = cgs.media.handsDefaultSkin;
				//gun.customSkin = cgs.media.handsBlueSkin; dunno why xamis had this?
				}
			else if (strcmp(skin, "green") == 0){
				gun.customSkin = cgs.media.handsGreenSkin; }
			else if (strcmp(skin, "orange") == 0){
				gun.customSkin = cgs.media.handsOrangeSkin; }
			else if (strcmp(skin, "purple") == 0){
				gun.customSkin = cgs.media.handsPurpleSkin; }
			else if (strcmp(skin, "red") == 0){
				gun.customSkin = cgs.media.handsRedSkin; }
			else if (strcmp(skin, "red2") == 0){
				gun.customSkin = cgs.media.handsRed2Skin; }
			else if (strcmp(skin, "blue") == 0){
				gun.customSkin = cgs.media.handsBlueSkin; }
			else if (strcmp(skin, "blue2") == 0){
				gun.customSkin = cgs.media.handsBlue2Skin; }
			else if (strcmp(skin, "yellow") == 0){
				gun.customSkin = cgs.media.handsYellowSkin; }
			else {
				gun.customSkin = cgs.media.handsDefaultSkin;
				//gun.customSkin = cgs.media.handsBlueSkin; dunno why xamis had this?
				}
		}
	}
	//CG_Printf( "Team Number is %i\n", team );

	if (!gun.hModel)
	{
		return;
	}

        if ( !ps ) {
                // add weapon ready sound
                cent->pe.lightningFiring = qfalse;
                if ( ( cent->currentState.eFlags & EF_FIRING ) && weapon->firingSound ) {
                        // lightning gun and guantlet make a different sound when fire is held down
                        trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->firingSound );
                        cent->pe.lightningFiring = qtrue;
                } else if ( weapon->readySound ) {
                        trap_S_AddLoopingSound( cent->currentState.number, cent->lerpOrigin, vec3_origin, weapon->readySound );
                }
        }




        trap_R_LerpTag(&lerped, parent->hModel, parent->oldframe, parent->frame,
                1.0 - parent->backlerp, "tag_weapon");
        VectorCopy(parent->origin, gun.origin);

        if(!ps){

         // CG_Printf(" team is %i\n", team );

          if(vestOn && ( (team == TEAM_RED && ci->racered > 1) || (team == TEAM_BLUE && ci->raceblue > 1) || (!team && ci->raceblue > 1) )){
            VectorMA(gun.origin, lerped.origin[0]+3.0f, parent->axis[0], gun.origin); // forward/backward
            VectorMA(gun.origin, lerped.origin[1]+1, parent->axis[1], gun.origin); // side to side
            VectorMA(gun.origin, lerped.origin[2]+0.5f, parent->axis[2], gun.origin); // up/down

          }else{
            VectorMA(gun.origin, lerped.origin[0]+0.8f, parent->axis[0], gun.origin);
            VectorMA(gun.origin, lerped.origin[1], parent->axis[1], gun.origin);
            VectorMA(gun.origin, lerped.origin[2], parent->axis[2], gun.origin);


          }
        }

        if(ps){
          VectorMA(gun.origin, lerped.origin[0], parent->axis[0], gun.origin);
          VectorMA(gun.origin, lerped.origin[1]-2, parent->axis[1], gun.origin);
          VectorMA(gun.origin, lerped.origin[2], parent->axis[2], gun.origin);
          AnglesToAxis( angles, gun.axis );
        }

        MatrixMultiply(lerped.axis, ((refEntity_t *)parent)->axis, gun.axis);
        gun.backlerp = parent->backlerp;


if ( !ps ) {

        CG_PositionEntityOnTag( &gun, parent, parent->hModel, "tag_weapon");

}
else {
CG_WeaponAnimation( cent, &gun.oldframe, &gun.frame, &gun.backlerp );
CG_PositionWeaponOnTag( &gun, parent, parent->hModel, "tag_weapon");

} 


       // CG_WeaponAnimation( cent, &gun.oldframe, &gun.frame, &gun.backlerp );
       // CG_PositionEntityOnTag( &gun, parent, parent->hModel, "tag_weapon" );
        CG_AddWeaponWithPowerups( &gun, cent->currentState.powerups );


        if ( !ps ) {
            

          memset( &weaponModel, 0, sizeof( weaponModel ) );
          VectorCopy( parent->lightingOrigin, weaponModel.lightingOrigin );
          weaponModel.shadowPlane = parent->shadowPlane;
          weaponModel.renderfx = parent->renderfx;
          weaponModel.hModel = weapon->weaponModel;
          
if ( weaponDown ) {
       if (  BG_Primary( cent->currentState.weapon))
        CG_PositionEntityOnTag( &weaponModel, parent, parent->hModel, "tag_primary" );
    if (  BG_Secondary(cent->currentState.weapon ))
        CG_PositionEntityOnTag( &weaponModel, parent, parent->hModel, "tag_secondar" );
    if (  BG_Sidearm(cent->currentState.weapon ))
        CG_PositionEntityOnTag( &weaponModel, parent, parent->hModel, "tag_sidearm" );
}else
          CG_PositionEntityOnTag( &weaponModel, &gun, weapon->handsModel, "tag_weapon" );
          CG_AddWeaponWithPowerups( &weaponModel, cent->currentState.powerups );


		  //Putting weaposn on the player's back or holster (weapons they are not currently using)
         if( cent->currentState.number == cg.predictedPlayerState.clientNum){
          if ( PriweaponNum != cent->currentState.weapon ){
          	memset( &PriweaponModel, 0, sizeof( PriweaponModel ) );
	VectorCopy( parent->lightingOrigin, PriweaponModel.lightingOrigin );
	PriweaponModel.shadowPlane = parent->shadowPlane;
	PriweaponModel.renderfx = parent->renderfx;
                  PriweaponModel.hModel = weapon1->weaponModel;
                CG_PositionEntityOnTag( &PriweaponModel, parent, parent->hModel, "tag_primary" );
                CG_AddWeaponWithPowerups( &PriweaponModel, cent->currentState.powerups );
          }
          if ( SecweaponNum != cent->currentState.weapon ){
          	memset( &SecweaponModel, 0, sizeof( SecweaponModel ) );
	VectorCopy( parent->lightingOrigin, SecweaponModel.lightingOrigin );
	SecweaponModel.shadowPlane = parent->shadowPlane;
	SecweaponModel.renderfx = parent->renderfx;
                 SecweaponModel.hModel = weapon2->weaponModel;
                CG_PositionEntityOnTag( &SecweaponModel, parent, parent->hModel, "tag_secondar" );
                CG_AddWeaponWithPowerups( &SecweaponModel, cent->currentState.powerups );
          }
          if ( SidweaponNum != cent->currentState.weapon ){
          	memset( &SidweaponModel, 0, sizeof( SidweaponModel ) );
	VectorCopy( parent->lightingOrigin, SidweaponModel.lightingOrigin );
	SidweaponModel.shadowPlane = parent->shadowPlane;
	SidweaponModel.renderfx = parent->renderfx;
                  SidweaponModel.hModel = weapon3->weaponModel;
                CG_PositionEntityOnTag( &SidweaponModel, parent, parent->hModel, "tag_sidearm" );
                CG_AddWeaponWithPowerups( &SidweaponModel, cent->currentState.powerups );
          }
        }
        }

        if ( ps ) {


          memset( &viewmainModel, 0, sizeof( viewmainModel ) );
          VectorCopy( parent->lightingOrigin, viewmainModel.lightingOrigin );
          viewmainModel.shadowPlane = parent->shadowPlane;
          viewmainModel.renderfx = parent->renderfx;
          viewmainModel.hModel = weapon->vmainModel;
          CG_PositionEntityOnTag( &viewmainModel, &gun, weapon->holdsModel, "tag_main" );

          CG_AddWeaponWithPowerups( &viewmainModel, cent->currentState.powerups );

        }

        if ( ps && weapon->silencerModel && weaponNum != WP_KNIFE
             && weaponNum != WP_HK69 && weaponNum != WP_SPAS
             && weaponNum != WP_HE && weaponNum != WP_SR8
             && weaponNum != WP_SMOKE
             && silenced) {

                memset( &silencer, 0, sizeof( silencer ) );
                VectorCopy( parent->lightingOrigin, silencer.lightingOrigin );
                silencer.shadowPlane = parent->shadowPlane;
                silencer.renderfx = parent->renderfx;
                silencer.hModel = weapon->silencerModel;
                weapon->flashSound[0] = weapon->silenceSound[0];
                CG_PositionEntityOnTag( &silencer, &gun, weapon->holdsModel , "tag_flash" );


                CG_AddWeaponWithPowerups( &silencer, cent->currentState.powerups );
        }else weapon->flashSound[0] = weapon->normalSound[0];

       if ( weapon->laserModel && weaponNum != WP_KNIFE && weaponNum != WP_HK69
             && weaponNum != WP_SPAS && weaponNum != WP_HE && weaponNum != WP_SR8
             && weaponNum != WP_G36 && weaponNum != WP_PSG1 && weaponNum != WP_NEGEV 
            && weaponNum != WP_SMOKE && lasersight && !weaponDown &&  !( cg.ItemToggleState & ( 1 << PW_LASERSIGHT ))) 
                CG_RenderLaser(cent);
        
        if ( ps && weapon->laserModel && weaponNum != WP_KNIFE && weaponNum != WP_HK69
             && weaponNum != WP_SPAS && weaponNum != WP_HE && weaponNum != WP_SR8
             && weaponNum != WP_G36 && weaponNum != WP_PSG1 && weaponNum != WP_NEGEV 
		&& weaponNum != WP_SMOKE && lasersight) {
            

                memset( &laser, 0, sizeof( laser ) );
                VectorCopy( parent->lightingOrigin, laser.lightingOrigin );
                laser.shadowPlane = parent->shadowPlane;
                laser.renderfx = parent->renderfx;
                laser.hModel = weapon->laserModel;
                 if ( weaponNum != WP_AK103)
                CG_PositionEntityOnTag( &laser, &gun, weapon->holdsModel , "tag_laser" );

               CG_AddWeaponWithPowerups( &laser, cent->currentState.powerups );
        }

  if( ps){

        if ( weapon->vtriggerModel) {
          memset( &vtrigger, 0, sizeof( vtrigger ) );
          VectorCopy( parent->lightingOrigin, vtrigger.lightingOrigin );
          vtrigger.shadowPlane = parent->shadowPlane;
          vtrigger.renderfx = parent->renderfx;
          vtrigger.hModel = weapon->vtriggerModel;
          CG_PositionEntityOnTag( &vtrigger, &gun, weapon->holdsModel , "tag_trigger" );
          CG_AddWeaponWithPowerups( &vtrigger, cent->currentState.powerups );
          }

          if ( weapon->vboltModel) {
            memset( &vbolt, 0, sizeof( vbolt ) );
            VectorCopy( parent->lightingOrigin, vbolt.lightingOrigin );
            vbolt.shadowPlane = parent->shadowPlane;
            vbolt.renderfx = parent->renderfx;
            vbolt.hModel = weapon->vboltModel;
            CG_PositionEntityOnTag( &vbolt, &gun, weapon->holdsModel , "tag_bolt" );
            CG_AddWeaponWithPowerups( &vbolt, cent->currentState.powerups );
          }

          if ( weapon->vflapModel) {
            memset( &vflap, 0, sizeof( vflap ) );
            VectorCopy( parent->lightingOrigin, vflap.lightingOrigin );
            vflap.shadowPlane = parent->shadowPlane;
            vflap.renderfx = parent->renderfx;
            vflap.hModel = weapon->vflapModel;
            CG_PositionEntityOnTag( &vflap, &gun, weapon->holdsModel , "tag_flap" );
            CG_AddWeaponWithPowerups( &vflap, cent->currentState.powerups );
          }


        if ( weapon->vflap2Model) {
            memset( &vflap2, 0, sizeof( vflap2 ) );
            VectorCopy( parent->lightingOrigin, vflap2.lightingOrigin );
            vflap2.shadowPlane = parent->shadowPlane;
            vflap2.renderfx = parent->renderfx;
            vflap2.hModel = weapon->vflap2Model;
            CG_PositionEntityOnTag( &vflap2, &gun, weapon->holdsModel , "tag_flap2" );
            CG_AddWeaponWithPowerups( &vflap2, cent->currentState.powerups );
          }

          if ( weapon->vejectorModel) {
            memset( &vejector, 0, sizeof( vejector ) );
            VectorCopy( parent->lightingOrigin, vejector.lightingOrigin );
            vejector.shadowPlane = parent->shadowPlane;
            vejector.renderfx = parent->renderfx;
            vejector.hModel = weapon->vejectorModel;
            CG_PositionEntityOnTag( &vejector, &gun, weapon->holdsModel , "tag_ejector" );
            CG_AddWeaponWithPowerups( &vejector, cent->currentState.powerups );
          }

          if ( weapon->vmodeModel) {
            memset( &vmode, 0, sizeof( vmode ) );
            VectorCopy( parent->lightingOrigin, vmode.lightingOrigin );
            vmode.shadowPlane = parent->shadowPlane;
            vmode.renderfx = parent->renderfx;
            vmode.hModel = weapon->vmodeModel;
            CG_PositionEntityOnTag( &vmode, &gun, weapon->holdsModel , "tag_mode" );
            CG_AddWeaponWithPowerups( &vmode, cent->currentState.powerups );
          }

          if ( weapon->vbuttModel) {
            memset( &vbutt, 0, sizeof( vbutt ) );
            VectorCopy( parent->lightingOrigin, vbutt.lightingOrigin );
            vbutt.shadowPlane = parent->shadowPlane;
            vbutt.renderfx = parent->renderfx;
            vbutt.hModel = weapon->vbuttModel;
            CG_PositionEntityOnTag( &vbutt, &gun, weapon->holdsModel , "tag_butt" );
            CG_AddWeaponWithPowerups( &vbutt, cent->currentState.powerups );
          }

          if ( weapon->vcockModel) {
            memset( &vcock, 0, sizeof( vcock ) );
            VectorCopy( parent->lightingOrigin, vcock.lightingOrigin );
            vcock.shadowPlane = parent->shadowPlane;
            vcock.renderfx = parent->renderfx;
            vcock.hModel = weapon->vcockModel;
            CG_PositionEntityOnTag( &vcock, &gun, weapon->holdsModel , "tag_cock" );
            CG_AddWeaponWithPowerups( &vcock, cent->currentState.powerups );
          }

          if ( weapon->vbarrelModel && weaponNum != WP_KNIFE ) {
            memset( &vbarrel, 0, sizeof( vbarrel ) );
            VectorCopy( parent->lightingOrigin, vbarrel.lightingOrigin );
            vbarrel.shadowPlane = parent->shadowPlane;
            vbarrel.renderfx = parent->renderfx;
            vbarrel.hModel = weapon->vbarrelModel;
            CG_PositionEntityOnTag( &vbarrel, &gun, weapon->holdsModel , "tag_barrel" );
            CG_AddWeaponWithPowerups( &vbarrel, cent->currentState.powerups );
          }

          if ( weapon->vclipModel) {
            memset( &vclip, 0, sizeof( vclip ) );
            VectorCopy( parent->lightingOrigin, vclip.lightingOrigin );
            vclip.shadowPlane = parent->shadowPlane;
            vclip.renderfx = parent->renderfx;
            vclip.hModel = weapon->vclipModel;
            CG_PositionEntityOnTag( &vclip, &gun, weapon->holdsModel , "tag_clip" );
            CG_AddWeaponWithPowerups( &vclip, cent->currentState.powerups );
          }


         if ( weapon->vringModel) {
            memset( &vring, 0, sizeof( vring ) );
            VectorCopy( parent->lightingOrigin, vring.lightingOrigin );
            vring.shadowPlane = parent->shadowPlane;
            vring.renderfx = parent->renderfx;
            vring.hModel = weapon->vringModel;
            CG_PositionEntityOnTag( &vring, &gun, weapon->holdsModel , "tag_ring" );
            CG_AddWeaponWithPowerups( &vring, cent->currentState.powerups );
          }

          if ( weapon->vcliprelModel) {
            memset( &vcliprel, 0, sizeof( vcliprel ) );
            VectorCopy( parent->lightingOrigin, vcliprel.lightingOrigin );
            vcliprel.shadowPlane = parent->shadowPlane;
            vcliprel.renderfx = parent->renderfx;
            vcliprel.hModel = weapon->vcliprelModel;
            CG_PositionEntityOnTag( &vcliprel, &gun, weapon->holdsModel , "tag_cliprel" );
            CG_AddWeaponWithPowerups( &vcliprel, cent->currentState.powerups );
          }

          if ( weapon->vslideModel) {
            memset( &vslide, 0, sizeof( vslide ) );
            VectorCopy( parent->lightingOrigin, vslide.lightingOrigin );
            vslide.shadowPlane = parent->shadowPlane;
            vslide.renderfx = parent->renderfx;
            vslide.hModel = weapon->vslideModel;
            CG_PositionEntityOnTag( &vslide, &gun, weapon->holdsModel , "tag_slide" );
            CG_AddWeaponWithPowerups( &vslide, cent->currentState.powerups );
          }

          if ( weapon->vsliderelModel) {
            memset( &vsliderel, 0, sizeof( vsliderel ) );
            VectorCopy( parent->lightingOrigin, vsliderel.lightingOrigin );
            vsliderel.shadowPlane = parent->shadowPlane;
            vsliderel.renderfx = parent->renderfx;
            vsliderel.hModel = weapon->vsliderelModel;
            CG_PositionEntityOnTag( &vsliderel, &gun, weapon->holdsModel , "tag_sliderel" );
            CG_AddWeaponWithPowerups( &vsliderel, cent->currentState.powerups );
          }

        if ( weapon->vhandleModel) {
            memset( &vhandle, 0, sizeof( vhandle ) );
            VectorCopy( parent->lightingOrigin, vhandle.lightingOrigin );
            vhandle.shadowPlane = parent->shadowPlane;
            vhandle.renderfx = parent->renderfx;
            vhandle.hModel = weapon->vhandleModel;
            CG_PositionEntityOnTag( &vhandle, &gun, weapon->holdsModel , "tag_handle" );
            CG_AddWeaponWithPowerups( &vhandle, cent->currentState.powerups );
          }

          if ( weapon->vboxModel) {
            memset( &vbox, 0, sizeof( vbox ) );
            VectorCopy( parent->lightingOrigin, vbox.lightingOrigin );
            vbox.shadowPlane = parent->shadowPlane;
            vbox.renderfx = parent->renderfx;
            vbox.hModel = weapon->vboxModel;
            CG_PositionEntityOnTag( &vbox, &gun, weapon->holdsModel , "tag_box" );
            CG_AddWeaponWithPowerups( &vbox, cent->currentState.powerups );
          }

          if ( weaponNum == WP_NEGEV) {
            memset( &vbullet, 0, sizeof( vbullet ) );

            VectorCopy( parent->lightingOrigin, vbullet.lightingOrigin );
            vbullet.shadowPlane = parent->shadowPlane;
            vbullet.renderfx = parent->renderfx;
            vbullet.hModel = weapon->vbulletModel;

          {
          int rounds = cg.predictedPlayerState.stats[STAT_ROUNDS];
          int j = 0;

          if ( rounds > 10 )
          rounds = 10;

          rounds--;

          if ( rounds > 0 )
          for ( j=0; j<rounds; j++ )
          {
          tagname = va( "tag_bul0%i", j+1 );

          CG_PositionEntityOnTag( &vbullet, &gun, weapon->holdsModel ,  tagname );
          CG_AddWeaponWithPowerups( &vbullet, cent->currentState.powerups );
  }

  }

          }

          if ( weapon->vaimModel) {

            memset( &vaim, 0, sizeof( vaim ) );
            VectorCopy( parent->lightingOrigin, vaim.lightingOrigin );
            vaim.shadowPlane = parent->shadowPlane;
            vaim.renderfx = parent->renderfx;
            vaim.hModel = weapon->vaimModel;
            CG_PositionEntityOnTag( &vaim, &gun, weapon->holdsModel , "tag_aim" );
            CG_AddWeaponWithPowerups( &vaim, cent->currentState.powerups );
          }

          if ( weapon->vpinModel) {
            memset( &vpin, 0, sizeof( vpin ) );
            VectorCopy( parent->lightingOrigin, vpin.lightingOrigin );
            vpin.shadowPlane = parent->shadowPlane;
            vpin.renderfx = parent->renderfx;
            vpin.hModel = weapon->vpinModel;
            CG_PositionEntityOnTag( &vpin, &gun, weapon->holdsModel , "tag_pin" );
            CG_AddWeaponWithPowerups( &vpin, cent->currentState.powerups );
          }

          if ( weapon->vshellModel) {
            memset( &vshell, 0, sizeof( vshell ) );
            VectorCopy( parent->lightingOrigin, vshell.lightingOrigin );
            vshell.shadowPlane = parent->shadowPlane;
            vshell.renderfx = parent->renderfx;
            vshell.hModel = weapon->vshellModel;
            CG_PositionEntityOnTag( &vshell, &gun, weapon->holdsModel , "tag_shell" );
            CG_AddWeaponWithPowerups( &vshell, cent->currentState.powerups );
          }

          if ( weapon->vgrenadeModel) {
            memset( &vgrenade, 0, sizeof( vgrenade ) );
            VectorCopy( parent->lightingOrigin, vgrenade.lightingOrigin );
            vgrenade.shadowPlane = parent->shadowPlane;
            vgrenade.renderfx = parent->renderfx;
            vgrenade.hModel = weapon->vgrenadeModel;
            CG_PositionEntityOnTag( &vgrenade, &gun, weapon->holdsModel , "tag_grenade" );
            CG_AddWeaponWithPowerups( &vgrenade, cent->currentState.powerups );
          }

          if ( weapon->vejectModel) {
            memset( &veject, 0, sizeof( veject ) );
            VectorCopy( parent->lightingOrigin, veject.lightingOrigin );
            veject.shadowPlane = parent->shadowPlane;
            veject.renderfx = parent->renderfx;
            veject.hModel = weapon->vejectModel;
            CG_PositionEntityOnTag( &veject, &gun, weapon->holdsModel , "tag_eject" );
            CG_AddWeaponWithPowerups( &veject, cent->currentState.powerups );
          }

          if ( weapon->vflap1Model) {
            memset( &vflap1, 0, sizeof( vflap1 ) );
            VectorCopy( parent->lightingOrigin, vflap1.lightingOrigin );
            vflap1.shadowPlane = parent->shadowPlane;
            vflap1.renderfx = parent->renderfx;
            vflap1.hModel = weapon->vflap1Model;
            CG_PositionEntityOnTag( &vflap1, &gun, weapon->holdsModel , "tag_flap1" );
            CG_AddWeaponWithPowerups( &vflap1, cent->currentState.powerups );
          }
  }



        // make sure we aren't looking at cg.predictedPlayerEntity for LG
        nonPredictedCent = &cg_entities[cent->currentState.clientNum];

        // if the index of the nonPredictedCent is not the same as the clientNum
        // then this is a fake player (like on teh single player podiums), so
        // go ahead and use the cent
        if( ( nonPredictedCent - cg_entities ) != cent->currentState.clientNum ) {
                nonPredictedCent = cent;
        }

        // add the flash
          if ( cg.time - cent->muzzleFlashTime > MUZZLE_FLASH_TIME && !cent->pe.railgunFlash
               && weaponNum != WP_KNIFE
               &&!(BG_Grenade(weaponNum))
             ) {
                        return; //removed some stuff, trying to prevent flash on knife, looked real dumb  --Xamis
                }


        memset( &flash, 0, sizeof( flash ) );
        VectorCopy( parent->lightingOrigin, flash.lightingOrigin );
        flash.shadowPlane = parent->shadowPlane;
        flash.renderfx = parent->renderfx;

        flash.hModel = weapon->flashModel;
        if (!flash.hModel) {
                return;
        }
        angles[YAW] = 0;
        angles[PITCH] = 0;
        angles[ROLL] = crandom() * 10;
        AnglesToAxis( angles, flash.axis );

        if (!silenced && weaponNum != WP_KNIFE &&!(BG_Grenade(weaponNum))){
        if (ps )
          CG_PositionRotatedEntityOnTag( &flash, &gun, weapon->holdsModel, "tag_flash");
        else
          CG_PositionRotatedEntityOnTag( &flash, &gun, weapon->weaponModel, "tag_flash");
        trap_R_AddRefEntityToScene( &flash );



        if ( ps || cg.renderingThirdPerson ||
                cent->currentState.number != cg.predictedPlayerState.clientNum ) {
                // add lightning bolt
                //CG_LightningBolt( nonPredictedCent, flash.origin );

                // add rail trail
                //CG_SpawnRailTrail( cent, flash.origin );

                if ( weapon->flashDlightColor[0] || weapon->flashDlightColor[1] || weapon->flashDlightColor[2] ) {
                        trap_R_AddLightToScene( flash.origin, 300 + (rand()&31), weapon->flashDlightColor[0],
                                weapon->flashDlightColor[1], weapon->flashDlightColor[2] );
                }
        }
        }
       
}

/*
==============
CG_AddViewWeapon

Add the weapon, and flash for the player's view
==============
*/

void CG_AddViewWeapon( playerState_t *ps ) {
        refEntity_t     hand;
        centity_t       *cent;
        clientInfo_t    *ci;
        float           fovOffset;
        vec3_t          angles;
        weaponInfo_t    *weapon;
        int             anim;

        if ( ps->persistant[PERS_TEAM] == TEAM_SPECTATOR ) {
                return;
        }
        
        if ( ps->pm_type == PM_INTERMISSION ) {
                return;
        }

        // no gun if in third person view or a camera is active
        //if ( cg.renderingThirdPerson || cg.cameraMode) {
        if ( cg.renderingThirdPerson ) {
                return;
        }
        if ( ps->pm_flags & PMF_ONLADDER ) {
            return;
        }
        
        
        // allow the gun to be completely removed
        if ( !cg_drawGun.integer ) {
                vec3_t          origin;

                if ( cg.predictedPlayerState.eFlags & EF_FIRING ) {
                        // special hack for lightning gun...
                        VectorCopy( cg.refdef.vieworg, origin );
                        VectorMA( origin, -8, cg.refdef.viewaxis[2], origin );
                        CG_LightningBolt( &cg_entities[ps->clientNum], origin );
                }
                return;
        }

        if ( cg.zoomed ) {
                vec3_t          origin;

                if ( cg.predictedPlayerState.eFlags & EF_FIRING ) {
                        // special hack for lightning gun...
                        VectorCopy( cg.refdef.vieworg, origin );
                        VectorMA( origin, -8, cg.refdef.viewaxis[2], origin );
                        CG_LightningBolt( &cg_entities[ps->clientNum], origin );
                }
                return;
        }


        // don't draw if testing a gun model
        if ( cg.testGun ) {
                return;
        }

        // drop gun lower at higher fov
        if ( cg_fov.integer > 110 ) {
            cg_fov.integer=110;
                fovOffset = -0.2 * ( cg_fov.integer - 90 );
        } else {
                fovOffset = 0;
        }

        cent = &cg.predictedPlayerEntity;       // &cg_entities[cg.snap->ps.clientNum];
        anim = cent->currentState.torsoAnim & ~ANIM_TOGGLEBIT;

            if ( anim == TORSO_BANDAGE ){
                return;
                  } 
        
        CG_RegisterWeapon( ps->weapon );
        weapon = &cg_weapons[ ps->weapon ];

        memset (&hand, 0, sizeof(hand));

        // set up gun position
        CG_CalculateWeaponPosition( hand.origin, angles );


        //if smallgun
        if ( cg_gunsize.integer ){
			VectorMA( hand.origin, cg_gun_x.value+6, cg.refdef.viewaxis[0], hand.origin );
			VectorMA( hand.origin, cg_gun_y.value+1.6, cg.refdef.viewaxis[1], hand.origin );//left right
			VectorMA( hand.origin, (cg_gun_z.value+fovOffset)-.25, cg.refdef.viewaxis[2], hand.origin );

			AnglesToAxis( angles, hand.axis );
			//if smallgun
        VectorScale(hand.axis[0], 0.4f, hand.axis[0]);
        VectorScale(hand.axis[1], 0.65f, hand.axis[1]);
        VectorScale(hand.axis[2], 0.67f, hand.axis[2]);
		}else{
            			VectorMA( hand.origin, cg_gun_x.value+4.8, cg.refdef.viewaxis[0], hand.origin );
			VectorMA( hand.origin, cg_gun_y.value+1.2, cg.refdef.viewaxis[1], hand.origin );
			VectorMA( hand.origin, (cg_gun_z.value+fovOffset)+2,cg.refdef.viewaxis[2], hand.origin );
                        AnglesToAxis( angles, hand.axis );
        VectorScale(hand.axis[0], 0.42f, hand.axis[0]);
        VectorScale(hand.axis[1], .7f, hand.axis[1]);
        VectorScale(hand.axis[2], .71f, hand.axis[2]);


			//AnglesToAxis( angles, hand.axis );
		}

		ci = &cgs.clientinfo[ cent->currentState.clientNum ]; //blud moved this up out of the ifelse below, because I need it all the time for my CG_AddPlayerWeapon call (to do with hand skins)
		//blud: I hope this doesn't reduce perfomance or something??? This isn't being done 30 times a second or anything is it? (oh well even if it is that might be fine I have no idea)

		// map torso animations to weapon animations
		if ( cg_gun_frame.integer ) {
			// development tool
			hand.frame = hand.oldframe = cg_gun_frame.integer;
			hand.backlerp = 0;
		} else {
			// get clientinfo for animation map
			//ci = &cgs.clientinfo[ cent->currentState.clientNum ]; //blud I moved this old line to above the if (see comment above)
			hand.frame = CG_MapTorsoToWeaponFrame( ci, cent->pe.torso.frame );
			hand.oldframe = CG_MapTorsoToWeaponFrame( ci, cent->pe.torso.oldFrame );
			hand.backlerp = cent->pe.torso.backlerp;
		}
        weapon->handsModel = trap_R_RegisterModel( "models/weapons2/shotgun/shotgun_hand.md3" );
        hand.hModel = weapon->handsModel;
        hand.renderfx = RF_DEPTHHACK | RF_FIRST_PERSON | RF_MINLIGHT;
        // add everything onto the hand
        CG_AddPlayerWeapon( &hand, ps, &cg.predictedPlayerEntity, ps->persistant[PERS_TEAM], CG_GetPlayerModelName(ci), ci->skin );
}

void CG_ToggleItem_f( void ) {
      
      playerState_t   *ps;
      ps = &cg.snap->ps;
      //CG_AddEvent(EV_TOGGLEITEM);
CG_Printf(" cg.ItemToggleState is %i\n", cg.ItemToggleState);      
 //ItemToggleState
if ( !(cg.ItemToggleState & ( 1 << ps->stats[STAT_SELECTED_ITEM] ))){
cg.ItemToggleState |= ( 1 << ps->stats[STAT_SELECTED_ITEM] );//item on
}else{
cg.ItemToggleState &= ~( 1 << ps->stats[STAT_SELECTED_ITEM] );//item off
}


}
void CG_DrawItemSelect( void ) {
        //int           value;

  gitem_t         *item;
  int             i, x;
  int             bits;
  int             count;
  float       hcolor[4];
  float   *color;
  playerState_t   *ps;
  hcolor[0] = 0.2f;
  hcolor[1] = 0.3f;
  hcolor[2] = 0.8f;
  hcolor[3] = 0.3f;
  ps = &cg.snap->ps;

  color = CG_FadeColor( cg.itemSelectTime, WEAPON_SELECT_TIME );
  if ( !color ) {
    return;
  }
  trap_R_SetColor( color );

  bits = (cg.predictedPlayerEntity.currentState.powerups  );
  count = 0;
  for ( i = 0 ; i < MAX_POWERUPS ; i++ ) {
    if ( bits & ( 1 << i ) ) {
      count++;
    }
  }
  x = 640-ICON_SIZE - count * 24;
  for ( i = 1 ; i < MAX_POWERUPS ; i++ ) {
    if ( !ps->powerups[ i ] ) {
      continue;
    }
  item = BG_FindItemForPowerup( i );
        //value = cg.snap->ps.stats[STAT_SELECTED_ITEM];
  if ( item ) {
         // CG_RegisterItemVisuals( STAT_SELECTED_ITEM );

    CG_FillRect( x, (SCREEN_HEIGHT-ICON_SIZE)/2, ICON_SIZE, ICON_SIZE, hcolor);
    CG_DrawPic( x, (SCREEN_HEIGHT-ICON_SIZE)/2, ICON_SIZE, ICON_SIZE, trap_R_RegisterShader( item->icon ) );
    if( i == ps->stats[STAT_SELECTED_ITEM])
    CG_DrawPic( x, (SCREEN_HEIGHT-ICON_SIZE)/2,ICON_SIZE, ICON_SIZE, cgs.media.selectShader );

  } x += 48;
  }
}

void CG_NextItem_f (void){
  cg.itemSelectTime = cg.time;
  trap_SendConsoleCommand( "next_item" );
}

void CG_PrevItem_f (void){
  cg.itemSelectTime = cg.time;
  trap_SendConsoleCommand( "prev_item" );
}

void CG_ZoomReset_f (void){
 float zoomFov;
centity_t       *cent;
cent = &cg_entities[cg.snap->ps.clientNum];
zoomFov = cg_zoomFov.value;   
if(cg.zoomed  ){
        cent->pe.zoomLevel=0;
        cg.setZoomFov= 1;
        cg.zoomed = qfalse;
  }
}

void CG_ZoomIn_f (void){
float zoomFov;
centity_t       *cent;
cent = &cg_entities[cg.snap->ps.clientNum];
zoomFov = cg_zoomFov.value;

if (cg.predictedPlayerState.weaponstate != WEAPON_READY)
    return;

if (cent->currentState.weapon == WP_SR8 || cent->currentState.weapon == WP_PSG1  ){

if( cent->pe.zoomLevel == 0 ){
        cg.setZoomFov = 33;
        cg.zoomed = qtrue;
        cent->pe.zoomLevel++ ;
}else if( cent->pe.zoomLevel == 1 ){
        cg.setZoomFov = 17;
        cg.zoomed = qtrue;
        cent->pe.zoomLevel++;
} else if( cent->pe.zoomLevel == 2 ){
        cg.setZoomFov = 8;
        cg.zoomed = qtrue;
        cent->pe.zoomLevel++;
} else if ( cent->pe.zoomLevel > 2){
        cent->pe.zoomLevel=0;
        cg.setZoomFov= 1;
        cg.zoomed = qfalse;
}


    }

if (cent->currentState.weapon ==WP_G36 ){

if( cent->pe.zoomLevel == 0 ){
        cg.setZoomFov = 40;
        cg.zoomed = qtrue;
        cent->pe.zoomLevel++ ;
} else if ( cent->pe.zoomLevel > 0){
        cent->pe.zoomLevel=0;
        cg.setZoomFov= 1;
        cg.zoomed = qfalse;
}

    }trap_S_StartSound (NULL, cg.snap->ps.clientNum, CHAN_WEAPON, cgs.media.zoomSound );
}




/*
==============================================================================

WEAPON SELECTION

==============================================================================
*/

/*
===================
CG_DrawWeaponSelect
===================
*/
void CG_DrawWeaponSelect( void ) {
        int             i;
        int             bits;
        int             count;
        int             x, y;
        char    *name;
        float   *color;
        float       hcolor[4];
        float       hcolor2[4];

        hcolor[0] = 0.0f;
        hcolor[1] = 0.0f;
        hcolor[2] = 0.0f;
        hcolor[3] = 0.6f;

        hcolor2[0] = 0.2f;
        hcolor2[1] = 0.3f;
        hcolor2[2] = 0.8f;
        hcolor2[3] = 0.3f;


        // don't display if dead
        if ( cg.predictedPlayerState.stats[STAT_HEALTH] <= 0 ) {
                return;
        }

        color = CG_FadeColor( cg.weaponSelectTime, WEAPON_SELECT_TIME );
        if ( !color ) {
                return;
        }
        trap_R_SetColor( color );
    //    CG_ZoomReset_f();

        // showing weapon select clears pickup item display, but not the blend blob
        cg.itemPickupTime = 0;

        // count the number of weapons owned
       bits = (cg.snap->ps.stats[ STAT_WEAPONS ] | cg.snap->ps.stats[ STAT_WEAPONS_EXT ] << 16 );
        count = 0;
        for ( i = 1 ; i < WP_NUM_WEAPONS ; i++ ) {
          if ( bits & ( 1 << i ) ) {
                        count++;
                }
        }

        x = 290 - count * 20;
        y = 400;

        for ( i = 1 ; i < WP_NUM_WEAPONS ; i++ ) {
          if (!( BG_HasWeapon(i, cg.snap->ps.stats ) )){//( !( bits & ( 1 << i ) ) ) {
                        continue;
                }

                CG_RegisterWeapon( i );



                CG_FillRect( x-10, y-4, 68, 36, hcolor);
                // draw weapon icon
               // CG_DrawPic(x, y, 48, 32, cgs.media.backtileShader );
                CG_DrawPic( x, y, 52, 34, cg_weapons[i].weaponIcon );
                CG_DrawPic( x-10, y-4, 67, 37, cgs.media.selectShader );

                // draw selection marker
                if ( i == cg.weaponSelect ) {
                       // CG_DrawPic( x-4, y-4, 56, 40, cgs.media.selectShader );
                        CG_FillRect( x-10, y-4, 68, 36, hcolor2);

                        if ( cg_weapons[ cg.weaponSelect ].item ) {
                          name = cg_weapons[ cg.weaponSelect ].item->pickup_name;
                          if ( name ) {
                           // CG_DrawSmallStringColor(x-12, y-20, name, color);
                            CG_DrawStringExt( x-10, y-20, name, color, qtrue, qtrue, 8, 10, 0 );

                          }
                        }

                }

                // no ammo cross on top
               // if ( !cg.snap->ps.ammo[ i ] ) {
               //         CG_DrawPic( x, y, 32, 32, cgs.media.noammoShader );
               // }

                x += 72;
        }

        // draw the selected name
        /*
        if ( cg_weapons[ cg.weaponSelect ].item ) {
                name = cg_weapons[ cg.weaponSelect ].item->pickup_name;
                if ( name ) {
                       // w = CG_DrawStrlen( name ) * BIGCHAR_WIDTH;
                  w = CG_DrawStrlen( name ) * SMALLCHAR_WIDTH;
                        x = ( SCREEN_WIDTH - w ) / 2;
                        //CG_DrawBigStringColor(x, y - 22, name, color);
                        CG_DrawSmallStringColor(x, y - 22, name, color);
                }
        }*/

        trap_R_SetColor( NULL );
    

}


/*
===============
CG_WeaponSelectable
===============
*/
static qboolean CG_WeaponSelectable( int i ) {

    if ( ! (BG_HasWeapon( i, cg.snap->ps.stats) ) ) {
        return qfalse;
    }
    return qtrue;
}

/*
===================
CG_OutOfNadesChange

===================
*/
void CG_OutOfNadesChange( centity_t *cent ) {

  int             i;
  entityState_t *ent;
  ent = &cent->currentState;
  cg.weaponSelectTime = cg.time;
 // if (!( BG_Grenade(ent->weapon)) ) {
 //  return;
 // }
  for ( i = MAX_WEAPONS-1 ; i > 0 ; i-- ) {
    if ( CG_WeaponSelectable( i )) {
      cg.weaponSelect = i;
      break;
    }
  }
}



/*
===============
CG_WeaponDropped
Called to force a weapon switch when you drop your current weapon
Xamis
===============
*/
void CG_WeaponDropped( void ) {
        int             i;

        if ( !cg.snap ) {
                return;
        }
        if ( cg.snap->ps.pm_flags & PMF_FOLLOW ) {
                return;
        }

        cg.weaponSelectTime = cg.time;

        CG_ZoomReset_f();

for( i = WP_NUM_WEAPONS-1; i > WP_NONE; i--){

               if (BG_HasWeapon( i, (int*)cg.predictedPlayerState.stats )){
                                cg.weaponSelect =  i;
                         break;
              }
        }

}

/*
===============
CG_NextWeapon_f
===============
*/
void CG_NextWeapon_f( void ) {
        int             i;
        int             original;

        if ( !cg.snap ) {
                return;
        }
        if ( cg.snap->ps.pm_flags & PMF_FOLLOW ) {
                return;
        }

        cg.weaponSelectTime = cg.time;
        original = cg.weaponSelect;
        CG_ZoomReset_f();
        for ( i = 0 ; i < WP_NUM_WEAPONS ; i++ ) {
                cg.weaponSelect++;
                if ( cg.weaponSelect == WP_NUM_WEAPONS ) {
                        cg.weaponSelect = 0;
                }
                if ( cg.weaponSelect == WP_KNIFE ) {
                        continue;               // never cycle to KNIFE
                }
                if ( CG_WeaponSelectable( cg.weaponSelect ) ) {
                        break;
                }
        }
        if ( i == WP_NUM_WEAPONS ) {
                cg.weaponSelect = original;
        }
}

/*
===============
CG_PrevWeapon_f
===============
*/
void CG_PrevWeapon_f( void ) {
        int             i;
        int             original;

        if ( !cg.snap ) {
                return;
        }
        if ( cg.snap->ps.pm_flags & PMF_FOLLOW ) {
                return;
        }

        cg.weaponSelectTime = cg.time;
        original = cg.weaponSelect;
        CG_ZoomReset_f();

        for ( i = 0 ; i < WP_NUM_WEAPONS ; i++ ) {
                cg.weaponSelect--;
                if ( cg.weaponSelect == -1 ) {
                  cg.weaponSelect = WP_NUM_WEAPONS - 1;
                }
                if ( cg.weaponSelect == WP_KNIFE ) {
                        continue;
                }
                if ( CG_WeaponSelectable( cg.weaponSelect ) ) {
                        break;
                }
        }
        if ( i == WP_NUM_WEAPONS ) {
                cg.weaponSelect = original;
        }
}


/*
===============
CG_GetPrimary
===============
*/
int CG_GetPrimary (void)
{
	//just go through each primary and if they have any of them (and they will only
	//have one at most), return it. If they don't, then return them the 'best' secondary
	//that they have (if any)
	if (BG_HasWeapon( WP_M4, cg.snap->ps.stats ))
		return WP_M4;
	else if (BG_HasWeapon( WP_LR300, cg.snap->ps.stats ))
		return WP_LR300;
	else if (BG_HasWeapon( WP_G36, cg.snap->ps.stats ))
		return WP_G36;
	else if (BG_HasWeapon( WP_AK103, cg.snap->ps.stats ))
		return WP_AK103;
	else if (BG_HasWeapon( WP_HK69, cg.snap->ps.stats ))
		return WP_HK69;
	else if (BG_HasWeapon( WP_NEGEV, cg.snap->ps.stats ))
		return WP_NEGEV;
	else if (BG_HasWeapon( WP_PSG1, cg.snap->ps.stats ))
		return WP_PSG1;
	else if (BG_HasWeapon( WP_SR8, cg.snap->ps.stats ))
		return WP_SR8;
	else
		return WP_NONE;
}


/*
====================
CG_GetWorstSecondary
====================
*/
int CG_GetWorstSecondary (void)
{
	//return the 'worst' of the secondaries (they might be holding 2)
	if (BG_HasWeapon( WP_SPAS, cg.predictedPlayerState.stats ))
		return WP_SPAS;
	else if (BG_HasWeapon( WP_MP5K, cg.predictedPlayerState.stats ))
		return WP_MP5K;
	else if (BG_HasWeapon( WP_UMP45, cg.predictedPlayerState.stats ))
		return WP_UMP45;
	else
		return WP_NONE;
}


/*
===================
CG_GetBestSecondary
===================
*/
int CG_GetBestSecondary (void)
{
	//return the 'best' of the secondaries (they might be holding 2)
	if (BG_HasWeapon( WP_UMP45, cg.predictedPlayerState.stats ))
		return WP_UMP45;
	else if (BG_HasWeapon( WP_MP5K, cg.predictedPlayerState.stats ))
		return WP_MP5K;
	else if (BG_HasWeapon( WP_SPAS, cg.predictedPlayerState.stats ))
		return WP_SPAS;
	else
		return WP_NONE;
}


/*
===============
CG_GetSidearm
===============
*/
int CG_GetSidearm (void)
{
	if (BG_HasWeapon( WP_DEAGLE, cg.predictedPlayerState.stats ))
		return WP_DEAGLE;
	else if (BG_HasWeapon( WP_BERETTA, cg.predictedPlayerState.stats ))
		return WP_BERETTA;
	else
		return WP_NONE;
}


/*
===============
CG_WeapToggle_f
new function by blud
===============
*/
void CG_WeapToggle_f( void ) {
	int		i, numArgs, numGoodArgs, arg1bad, WP, WP_B, WP_W, WP_CURR;
	char    arg1[MAX_STRING_TOKENS];
	char    arg2[MAX_STRING_TOKENS];
	char    otherweap[MAX_STRING_TOKENS];
	centity_t	*cent;
          
                  CG_ZoomReset_f();
	
	cent = &cg_entities[cg.snap->ps.clientNum];
	numArgs = 0;
	numGoodArgs = 0;
	arg1bad = 0;

	//this is what they do in CG_Weapon_f, I guess to avoid error if there is no snap
	//and to do nothing if the user is a spectator
	if ( !cg.snap ) {
		return;
	}
	if ( cg.snap->ps.pm_flags & PMF_FOLLOW ) {
		return;
	}

	//grab the args
	trap_Argv( 1, arg1, sizeof( arg1 ) );
	arg2[0] = '\0';
	for ( i = 2; i < trap_Argc(); i++ ) {
		if (i > 2)
			strcat(arg2, " ");
		trap_Argv( i, &arg2[strlen(arg2)], sizeof( arg2 ) - strlen(arg2) );
	}
	
	//blud debug: CG_Printf("ARG1: %s ARG2: %s\n", arg1, arg2);


	//clean up the args and check if they are valid

	if (strlen(arg1) < 1)
	{
		CG_Printf("ut_weaptoggle requires parameters such as primary or secondary\n");
	}
	else
	{
		//arg1 is not empty, we have the first arg
		numArgs++;

		if (strlen(arg2) > 0)
		{
			//we have arg2
			numArgs++;

			//note this arg could have something like "secondary sidearm" in it, 
			//if the user tried to pass 3 args such as "primary secondary sidearm"
			//I was going to trim it here but instead I will just find the 2nd arg
			//to be invalid below and echo that to the user.
		}
	}


	if (numArgs > 0)
	{
		if	(!(strcmp(arg1, "primary")) ||
			!(strcmp(arg1, "secondary")) ||
			!(strcmp(arg1, "sidearm")) ||
			!(strcmp(arg1, "grenade")) ||
			!(strcmp(arg1, "bomb")) ||
			!(strcmp(arg1, "knife")))
		{
			//arg1 is good
			numGoodArgs++;
		}
		else
		{
			//arg1 is bad so we won't be doing anything
			CG_Printf("%s is an invalid parameter to give to ut_weaptoggle\n", arg1);
			arg1bad = 1;
		}
	}
	

	if (numArgs > 1 && !arg1bad)
	{
		if	(!(strcmp(arg2, "primary")) ||
			!(strcmp(arg2, "secondary")) ||
			!(strcmp(arg2, "sidearm")) ||
			!(strcmp(arg2, "grenade")) ||
			!(strcmp(arg2, "bomb")) ||
			!(strcmp(arg2, "knife")))
		{
			//arg2 is good
			numGoodArgs++;
		}
		else
		{
			//arg2 is bad and we essentially throw it out by not incrementing numGoodArgs
			//(So, you can send a bad 2nd arg and ut_weaptoggle will still act on the good first one,
			// but if your first arg is bad and the 2nd one is good, it won't act on the second one!)
			CG_Printf("%s is an invalid parameter to give to ut_weaptoggle\n", arg2);
		}

		//Now I need to throw out duplicate args because they would mess me up
		if (!(strcmp(arg1, arg2)))
		{
			numGoodArgs = 1; // this discards arg2 basically
		}
	}

	cg.weaponSelectTime = cg.time;

	if (numGoodArgs == 1)
	{
		if (!(strcmp(arg1, "primary")))
		{
			WP = CG_GetPrimary();
			if (WP != WP_NONE)
			{
				//give them primary
				cg.weaponSelect = WP;
			}
		}
		if (!(strcmp(arg1, "secondary")))
		{
			WP_B = CG_GetBestSecondary();
			WP_W = CG_GetWorstSecondary();
			
			if (WP_B != WP_W) //if they have 2 secondaries
			{
				if (cent->currentState.weapon != WP_B && cent->currentState.weapon != WP_W)
				{
					//give them worse of the 2 secondaries
					cg.weaponSelect = WP_W;
				}
				else if (cent->currentState.weapon == WP_W)
				{
					//give them better of the 2 secondaries
					cg.weaponSelect = WP_B;
				}
				else if (cent->currentState.weapon == WP_B)
				{
					//give them worse of the 2 secondaries
					cg.weaponSelect = WP_W;
				}
			}
			else if (WP_B == WP_W && WP_B != WP_NONE) //if they have 1 secondary
			{
				//give them the secondary
				cg.weaponSelect = WP_W;
			}
		}
		if (!(strcmp(arg1, "sidearm")))
		{
			WP = CG_GetSidearm();
			if (WP != WP_NONE)
			{
				//give them sidearm slot gun
				cg.weaponSelect = WP;
			}
		}
		if (!(strcmp(arg1, "grenade"))) //special case: There are Smokes and HEs
		{
			if (BG_HasWeapon(WP_SMOKE, (int*)cg.snap->ps.stats) && BG_HasWeapon(WP_HE, (int*)cg.snap->ps.stats))
			{
				if (cent->currentState.weapon != WP_HE && cent->currentState.weapon != WP_SMOKE)
				{
					//give them HE
					cg.weaponSelect = WP_HE;
				}
				else if (cent->currentState.weapon == WP_HE)
				{
					//give them Smoke
					//blud temp disable smoke for alpha 0.01
					//cg.weaponSelect = WP_SMOKE;
				}
				else if (cent->currentState.weapon == WP_SMOKE)
				{
					//give them HE
					cg.weaponSelect = WP_HE;
				}
			}
			else if (BG_HasWeapon(WP_SMOKE, (int*)cg.snap->ps.stats))
			{
				//give smoke
				//blud temp disable smoke for alpha 0.01
				//cg.weaponSelect = WP_SMOKE;
			}
			else if (BG_HasWeapon(WP_HE, (int*)cg.snap->ps.stats))
			{
				//give HE
				cg.weaponSelect = WP_HE;
			}
		}
		if (!(strcmp(arg1, "bomb")))
		{
			//note, weapon system is not done yet, doesn't have more than 16 weapons yet, and weapons
			//are not in the right places (there's no bomb yet)

			//if (BG_HasWeapon(WP_BOMB, (int*)cg.snap->ps.stats))
			//{
				CG_Printf("Sorry, the bomb is not yet implemented\n");
				//give BOMB
				//cg.weaponSelect = WP_BOMB;
			//}
		}
		if (!(strcmp(arg1, "knife")))
		{
			if (BG_HasWeapon(WP_KNIFE, (int*)cg.snap->ps.stats))
				cg.weaponSelect = WP_KNIFE;
			else
				CG_Printf("Where is your knife?\n");
		}
	}
	else if (numGoodArgs == 2)
	{
		int holding = -1;
		WP_CURR = cent->currentState.weapon;

		//see if they are holding one of the weapons in the 2 args
		if (!(strcmp(arg1, "primary")) || !(strcmp(arg2, "primary")))
		{
			WP = CG_GetPrimary();
			if (WP != WP_NONE)
			{
				if (WP_CURR == WP)
					holding = PRIMARY;
			}
		}
		if (!(strcmp(arg1, "secondary")) || !(strcmp(arg2, "secondary")))
		{
			//if I have two secondaries, the worst one will be the secondary here
										//since primary will get them the best one in that case
			WP = CG_GetWorstSecondary();
			if (WP != WP_NONE)
			{
				if (WP_CURR == WP)
					holding = SECONDARY;
			}
		}
		if (!(strcmp(arg1, "sidearm")) || !(strcmp(arg2, "sidearm")))
		{
			WP = CG_GetSidearm();
			if (WP != WP_NONE)
			{
				if (WP_CURR == WP)
					holding = SIDEARM;
			}
		}
		if (!(strcmp(arg1, "grenade")) || !(strcmp(arg2, "grenade")))
		{
			//if they have HE, HE is the grenade regardless if they have smoke or not.
			if (BG_HasWeapon(WP_HE, (int*)cg.snap->ps.stats))
			{
				if (WP_CURR == WP_HE)
					holding = NADE;
			}
			//else if they have Smoke, Smoke is the grenade
			else if (BG_HasWeapon(WP_SMOKE, (int*)cg.snap->ps.stats))
			{
				if (WP_CURR == WP_SMOKE)
					holding = NADE;
			}
		}
		if (!(strcmp(arg1, "bomb")) || !(strcmp(arg2, "bomb")))
		{
			//if (WP_CURR == WP_BOMB)
			//	holding = MISC;
			CG_Printf("Sorry, the bomb is not yet implemented\n");
		}
		if (!(strcmp(arg1, "knife")) || !(strcmp(arg2, "knife")))
		{
			if (WP_CURR == WP_KNIFE)
				holding = MELEE;
		}

		if (holding > -1)
		{
			switch( holding )
			{
				case PRIMARY:	//get the arg out of the 2 args that is not primary
								if (!(strcmp(arg1, "primary")))
								{
									//then arg1 is primary, so we want arg2
									Q_strncpyz( otherweap, arg2, sizeof( otherweap ) );
								}
								else
								{
									//arg2 must be primary, so we want arg1
									Q_strncpyz( otherweap, arg1, sizeof( otherweap ) );
								}
								break;
				
				case SECONDARY:	if (!(strcmp(arg1, "secondary")))
									Q_strncpyz( otherweap, arg2, sizeof( otherweap ) );
								else
									Q_strncpyz( otherweap, arg1, sizeof( otherweap ) );
								break;
				
				case SIDEARM:	if (!(strcmp(arg1, "sidearm")))
									Q_strncpyz( otherweap, arg2, sizeof( otherweap ) );
								else
									Q_strncpyz( otherweap, arg1, sizeof( otherweap ) );
								break;
				
				case NADE:		if (!(strcmp(arg1, "grenade")))
									Q_strncpyz( otherweap, arg2, sizeof( otherweap ) );
								else
									Q_strncpyz( otherweap, arg1, sizeof( otherweap ) );
								break;
				
				case MELEE:		if (!(strcmp(arg1, "knife")))
									Q_strncpyz( otherweap, arg2, sizeof( otherweap ) );
								else
									Q_strncpyz( otherweap, arg1, sizeof( otherweap ) );
								break;
				
				case MISC:		//case isn't happening right now, bomb isn't implemented yet
								break;
				
				default:		//default shouldn't happen
								break;
			}

			//**NOTE: I could probably combine the stuff below with the single arg stuff way above
			//		  into one function

			//get the weapon (or WP_NONE if they don't have it)
			WP = WP_NONE; //just putting this here in case none of these conditions are met, but that should be impossible
			if (!(strcmp(otherweap, "primary")))
			{
				WP = CG_GetPrimary();
			}
			if (!(strcmp(otherweap, "secondary")))
			{
				WP = CG_GetWorstSecondary();
			}
			if (!(strcmp(otherweap, "sidearm")))
			{
				WP = CG_GetSidearm();
			}
			if (!(strcmp(otherweap, "grenade")))
			{
				WP = WP_NONE;
				//but if we have Smoke, overwrite None with Smoke
				if (BG_HasWeapon(WP_SMOKE, (int*)cg.snap->ps.stats))
				{
					//blud temp disable smoke for alpha 0.01
					//WP = WP_SMOKE;
				}
				//but if we have HE, overwrite Smoke with HE
				if (BG_HasWeapon(WP_HE, (int*)cg.snap->ps.stats))
				{
					WP = WP_HE;
				}
			}
			if (!(strcmp(otherweap, "knife")))
			{
				if (BG_HasWeapon(WP_KNIFE, (int*)cg.snap->ps.stats))
				{
					WP = WP_KNIFE;
				}
				else
				{
					WP = WP_NONE;
					CG_Printf("Where is your knife?\n");
				}
			}
			//if (!(strcmp(otherweap, "bomb"))) //no bomb implemented yet
			
			//give them the other weapon if it's not WP_NONE
			if (WP != WP_NONE)
			{
				cg.weaponSelect = WP;
			}
		}
		else //they are not holding one of the arg guns, so give them the first one if they have it, or the 2nd one if they don't, or do nothing if they don't have either
		{
			WP = WP_NONE; //just putting this here in case none of these conditions are met, but that should be impossible
			if (!(strcmp(arg1, "primary")))
			{
				WP = CG_GetPrimary();
			}
			if (!(strcmp(arg1, "secondary")))
			{
				WP = CG_GetWorstSecondary();
			}
			if (!(strcmp(arg1, "sidearm")))
			{
				WP = CG_GetSidearm();
			}
			if (!(strcmp(arg1, "grenade")))
			{
				WP = WP_NONE;
				//but if we have Smoke, overwrite None with Smoke
				if (BG_HasWeapon(WP_SMOKE, (int*)cg.snap->ps.stats))
				{
					//blud temp disable smoke for alpha 0.01
					//WP = WP_SMOKE;
				}
				//but if we have HE, overwrite Smoke with HE
				if (BG_HasWeapon(WP_HE, (int*)cg.snap->ps.stats))
				{
					WP = WP_HE;
				}
			}
			if (!(strcmp(arg1, "knife")))
			{
				if (BG_HasWeapon(WP_KNIFE, (int*)cg.snap->ps.stats))
				{
					WP = WP_KNIFE;
				}
				else
				{
					WP = WP_NONE;
					CG_Printf("Where is your knife?\n");
				}
			}
			if (!(strcmp(arg1, "bomb")))
			{
				//bomb isn't implemented yet so do nothing
				CG_Printf("Sorry, the bomb is not yet implemented\n");
			}

			if (WP != WP_NONE)
			{
				cg.weaponSelect = WP;
			}
			else
			{
				WP = WP_NONE; //just putting this here in case none of these conditions are met, but that should be impossible
				if (!(strcmp(arg2, "primary")))
				{
					WP = CG_GetPrimary();
				}
				if (!(strcmp(arg2, "secondary")))
				{
					WP = CG_GetWorstSecondary();
				}
				if (!(strcmp(arg2, "sidearm")))
				{
					WP = CG_GetSidearm();
				}
				if (!(strcmp(arg2, "grenade")))
				{
					WP = WP_NONE;
					//but if we have Smoke, overwrite None with Smoke
					if (BG_HasWeapon(WP_SMOKE, (int*)cg.snap->ps.stats))
					{
						//blud temp disable smoke for alpha 0.01
						//WP = WP_SMOKE;
					}
					//but if we have HE, overwrite Smoke with HE
					if (BG_HasWeapon(WP_HE, (int*)cg.snap->ps.stats))
					{
						WP = WP_HE;
					}
				}
				if (!(strcmp(arg2, "knife")))
				{
					if (BG_HasWeapon(WP_KNIFE, (int*)cg.snap->ps.stats))
					{
						WP = WP_KNIFE;
					}
					else
					{
						WP = WP_NONE;
						CG_Printf("Where is your knife?\n");
					}
				}
				if (!(strcmp(arg2, "bomb")))
				{
					//bomb isn't implemented yet so do nothing
					CG_Printf("Sorry, the bomb is not yet implemented\n");
				}

				if (WP != WP_NONE)
				{
					cg.weaponSelect = WP;
				}
			}
		}
	}	
}

/*
===============
CG_Weapon_f
===============
*/
void CG_Weapon_f( void ) {
        int             num;
        if ( !cg.snap ) {
                return;
        }
        if ( cg.snap->ps.pm_flags & PMF_FOLLOW ) {
                return;
        }

        num = atoi( CG_Argv( 1 ) );
		
		//blud temp disable smoke for alpha 0.01
		if (num == 16)
			return;

     //   if ( num < 1 || num > MAX_WEAPONS-1 ) {
      //          return;
      //  }

        cg.weaponSelectTime = cg.time;

          if ( ! ( BG_HasWeapon( num, cg.snap->ps.stats ) ) ) {
                return;         // don't have the weapon
        }
        cg.weaponSelect = num;
        CG_ZoomReset_f();
}




/*
===================================================================================================

WEAPON EVENTS

===================================================================================================
*/

/*
================
CG_FireWeapon

Caused by an EV_FIRE_WEAPON event
================
*/
void CG_FireWeapon( centity_t *cent ) {
        entityState_t *ent;
        int                             c;
        weaponInfo_t    *weap;

        ent = &cent->currentState;
        if ( ent->weapon == WP_NONE ) {
                return;
        }
        if ( ent->weapon >= WP_NUM_WEAPONS ) {
          CG_Error( "CG_FireWeapon: ent->weapon >= WP_NUM_WEAPONS" );
                return;
        }
        weap = &cg_weapons[ ent->weapon ];

        // mark the entity as muzzle flashing, so when it is added it will
        // append the flash to the weapon model
        cent->muzzleFlashTime = cg.time;

        // play a sound
        for ( c = 0 ; c < 4 ; c++ ) {
                if ( !weap->flashSound[c] ) {
                        break;
                }
        }
        if ( c > 0 ) {
                c = rand() % c;
                if ( weap->flashSound[c] )
                {
                        trap_S_StartSound( NULL, ent->number, CHAN_WEAPON, weap->flashSound[c] );
                }
        }

        // do brass ejection
        if ( ent->weapon == WP_SR8 )
        if ( ent->weapon != WP_SPAS )
        if ( weap->ejectBrassFunc && cg_brassTime.integer > 0 ) {
                weap->ejectBrassFunc( cent );
        }
}

/*
=================
CG_LaserHitWall

=================
*/
void CG_LaserHitWall( int clientNum, vec3_t origin, vec3_t dir ) {
        qhandle_t               mod;
        qhandle_t               mark;
        qhandle_t               shader;
        sfxHandle_t             sfx;
        float                   radius;
        float                   light;
        vec3_t                  lightColor;
        qboolean                alphaFade;
        qboolean                isSprite;
        int                             duration;

        mark = 0;
        radius = 32;
        sfx = 0;
        mod = 0;
        shader = 0;
        light = 0;
        lightColor[0] = 1;
        lightColor[1] = 1;
        lightColor[2] = 0;

        // set defaults
        isSprite = qfalse;
        duration = 10;

                mod = cgs.media.dishFlashModel;
                shader = cgs.media.grenadeExplosionShader;
                sfx = cgs.media.sfx_rockexp;
                mark = cgs.media.burnMarkShader;
                radius = 64;
                light = 300;
                isSprite = qtrue;

        //
        // impact mark
        //
        	alphaFade = (mark == cgs.media.energyMarkShader);       // plasma fades alpha, all others fade color

                CG_ImpactMark( mark, origin, dir, random()*360, 1,1,1,1, alphaFade, radius, qfalse );

}



/*
=================
CG_MissileHitWall

Caused by an EV_MISSILE_MISS event, or directly by local bullet tracing
=================
*/
void CG_MissileHitWall( int weapon, int clientNum, vec3_t origin, vec3_t dir, impactSound_t soundType ) {
        qhandle_t               mod;
        qhandle_t               mark;
        qhandle_t               shader;
        sfxHandle_t             sfx;
        float                   radius;
        float                   light;
        vec3_t                  lightColor;
        localEntity_t   *le;
        int                             r;
        qboolean                alphaFade;
        qboolean                isSprite;
        int                             duration;

        mark = 0;
        radius = 32;
        sfx = 0;
        mod = 0;
        shader = 0;
        light = 0;
        lightColor[0] = 1;
        lightColor[1] = 1;
        lightColor[2] = 0;

        // set defaults
        isSprite = qfalse;
        duration = 600;

        switch ( weapon ) {
        default:
        case WP_HK69:
                mod = cgs.media.dishFlashModel;
                shader = cgs.media.grenadeExplosionShader;
                sfx = cgs.media.sfx_rockexp;
                mark = cgs.media.burnMarkShader;
                radius = 64;
                light = 300;
                isSprite = qtrue;
                break;
        case WP_SPAS:
                mod = cgs.media.bulletFlashModel;
                shader = cgs.media.bulletExplosionShader;
                mark = cgs.media.bulletMarkShader;
                sfx = 0;
                radius = 4;
                break;
        case WP_KNIFE:
            break;
        case WP_LR300:
        case WP_M4:
                mod = cgs.media.bulletFlashModel;
                shader = cgs.media.bulletExplosionShader;
                mark = cgs.media.bulletMarkShader;

                r = rand() & 3;
                if ( r == 0 ) {
                        sfx = cgs.media.sfx_ric1;
                } else if ( r == 1 ) {
                        sfx = cgs.media.sfx_ric2;
                } else {
                        sfx = cgs.media.sfx_ric3;
                }

                radius = 8;
                break;

        }

        if ( sfx ) {
                trap_S_StartSound( origin, ENTITYNUM_WORLD, CHAN_AUTO, sfx );
        }

        //
        // create the explosion
        //
        if ( mod ) {
                le = CG_MakeExplosion( origin, dir,
                                                           mod, shader,
                                                           duration, isSprite );
                le->light = light;
                VectorCopy( lightColor, le->lightColor );

        }

        //
        // impact mark
        //
        alphaFade = (mark == cgs.media.energyMarkShader);       // plasma fades alpha, all others fade color

        if (weapon != WP_KNIFE)
                CG_ImpactMark( mark, origin, dir, random()*360, 1,1,1,1, alphaFade, radius, qfalse );

}


/*
=================
CG_MissileHitPlayer
=================
*/
void CG_MissileHitPlayer( int weapon, vec3_t origin, vec3_t dir, int entityNum ) {
        CG_Bleed( origin, entityNum );

        // some weapons will make an explosion with the blood, while
        // others will just make the blood
        switch ( weapon ) {
        case WP_HK69:
                CG_MissileHitWall( weapon, 0, origin, dir, IMPACTSOUND_FLESH );
                break;
        default:
                break;
        }
}



/*
============================================================================

SHOTGUN TRACING

============================================================================
*/

/*
================
CG_ShotgunPellet
================
*/
static void CG_ShotgunPellet( vec3_t start, vec3_t end, int skipNum ) {
        trace_t         tr;
        int sourceContentType, destContentType;

        CG_Trace( &tr, start, NULL, NULL, end, skipNum, MASK_SHOT );

        sourceContentType = trap_CM_PointContents( start, 0 );
        destContentType = trap_CM_PointContents( tr.endpos, 0 );

        // FIXME: should probably move this cruft into CG_BubbleTrail
        if ( sourceContentType == destContentType ) {
                if ( sourceContentType & CONTENTS_WATER ) {
                        CG_BubbleTrail( start, tr.endpos, 32 );
                }
        } else if ( sourceContentType & CONTENTS_WATER ) {
                trace_t trace;

                trap_CM_BoxTrace( &trace, end, start, NULL, NULL, 0, CONTENTS_WATER );
                CG_BubbleTrail( start, trace.endpos, 32 );
        } else if ( destContentType & CONTENTS_WATER ) {
                trace_t trace;

                trap_CM_BoxTrace( &trace, start, end, NULL, NULL, 0, CONTENTS_WATER );
                CG_BubbleTrail( tr.endpos, trace.endpos, 32 );
        }

        if (  tr.surfaceFlags & SURF_NOIMPACT ) {
                return;
        }

        if ( cg_entities[tr.entityNum].currentState.eType == ET_PLAYER ) {
                CG_MissileHitPlayer( WP_SPAS, tr.endpos, tr.plane.normal, tr.entityNum );
        } else {
                if ( tr.surfaceFlags & SURF_NOIMPACT ) {
                        // SURF_NOIMPACT will not make a flame puff or a mark
                        return;
                }
                if ( tr.surfaceFlags & SURF_METALSTEPS ) {
                        CG_MissileHitWall( WP_SPAS, 0, tr.endpos, tr.plane.normal, IMPACTSOUND_METAL );
                } else {
                        CG_MissileHitWall( WP_SPAS, 0, tr.endpos, tr.plane.normal, IMPACTSOUND_DEFAULT );
                }
        }
}

/*
================
CG_ShotgunPattern

Perform the same traces the server did to locate the
hit splashes
================
*/
static void CG_ShotgunPattern( vec3_t origin, vec3_t origin2, int seed, int otherEntNum ) {
        int                     i;
        float           r, u;
        vec3_t          end;
        vec3_t          forward, right, up;

        // derive the right and up vectors from the forward vector, because
        // the client won't have any other information
        VectorNormalize2( origin2, forward );
        PerpendicularVector( right, forward );
        CrossProduct( forward, right, up );

        // generate the "random" spread pattern
        for ( i = 0 ; i < DEFAULT_SHOTGUN_COUNT ; i++ ) {
                r = Q_crandom( &seed ) * DEFAULT_SHOTGUN_SPREAD * 16;
                u = Q_crandom( &seed ) * DEFAULT_SHOTGUN_SPREAD * 16;
                VectorMA( origin, 8192 * 16, forward, end);
                VectorMA (end, r, right, end);
                VectorMA (end, u, up, end);

                CG_ShotgunPellet( origin, end, otherEntNum );
        }
}

/*
==============
CG_ShotgunFire
==============
*/
void CG_ShotgunFire( entityState_t *es ) {
        vec3_t  v;
        int             contents;

        VectorSubtract( es->origin2, es->pos.trBase, v );
        VectorNormalize( v );
        VectorScale( v, 32, v );
        VectorAdd( es->pos.trBase, v, v );
        if ( cgs.glconfig.hardwareType != GLHW_RAGEPRO ) {
                // ragepro can't alpha fade, so don't even bother with smoke
                vec3_t                  up;

                contents = trap_CM_PointContents( es->pos.trBase, 0 );
                if ( !( contents & CONTENTS_WATER ) ) {
                        VectorSet( up, 0, 0, 8 );
                        CG_SmokePuff( v, up, 32, 1, 1, 1, 0.33f, 900, cg.time, 0, LEF_PUFF_DONT_SCALE, cgs.media.shotgunSmokePuffShader );
                }
        }
        CG_ShotgunPattern( es->pos.trBase, es->origin2, es->eventParm, es->otherEntityNum );
}

/*
============================================================================

BULLETS

============================================================================
*/



/*
======================
CG_Bullet

Renders bullet effects.
======================
*/
void CG_Bullet( vec3_t end, int sourceEntityNum, vec3_t normal, qboolean flesh, int fleshEntityNum ) {
        trace_t trace;
        int sourceContentType, destContentType;
        vec3_t          start;
            centity_t	*cent;
        
        cent = &cg_entities[sourceEntityNum];
        // if the shooter is currently valid, calc a source point and possibly
        // do trail effects
        if ( sourceEntityNum >= 0 && cg_tracerChance.value > 0 ) {
                if ( CG_CalcMuzzlePoint( sourceEntityNum, start ) ) {
                        sourceContentType = trap_CM_PointContents( start, 0 );
                        destContentType = trap_CM_PointContents( end, 0 );

                        // do a complete bubble trail if necessary
                        if ( ( sourceContentType == destContentType ) && ( sourceContentType & CONTENTS_WATER ) ) {
                                CG_BubbleTrail( start, end, 32 );
                        }
                        // bubble trail from water into air
                        else if ( ( sourceContentType & CONTENTS_WATER ) ) {
                                trap_CM_BoxTrace( &trace, end, start, NULL, NULL, 0, CONTENTS_WATER );
                                CG_BubbleTrail( start, trace.endpos, 32 );
                        }
                        // bubble trail from air into water
                        else if ( ( destContentType & CONTENTS_WATER ) ) {
                                trap_CM_BoxTrace( &trace, start, end, NULL, NULL, 0, CONTENTS_WATER );
                                CG_BubbleTrail( trace.endpos, end, 32 );
                        }

                        // draw a tracer
                        if ( random() < cg_tracerChance.value ) {
//                                CG_Tracer( start, end );
                        }
                }
        }

        // impact splash and mark
        if ( flesh ) {
              //  CG_Bleed( end, fleshEntityNum );
                 CG_PlayerBleed( cent->currentState.clientNum, 25, end, normal );
        } else {
                CG_MissileHitWall( WP_M4, 0, end, normal, IMPACTSOUND_DEFAULT );
        }

}

localEntity_t *CG_SpawnBloodParticle( vec3_t org, vec3_t dir, float speed, float bouncefactor, float radius, float r,float g,float b,float a, qboolean size ) {
    localEntity_t	*le;
    refEntity_t		*re;

    le = CG_AllocLocalEntity();
    re = &le->refEntity;

    VectorCopy( org, le->pos.trBase ); // move to origin vector org
    VectorCopy( org, le->refEntity.origin ); // move to origin vector org
    VectorScale(dir, speed, le->pos.trDelta); // add velocity vector based on speed
    le->pos.trType = TR_GRAVITY;	// movement type
    le->pos.trTime = cg.time;		// set start time of calculation
    le->leType = LE_PARTICLE;		// render as particle
    le->startTime = cg.time;		// start time
    le->endTime = cg.time +20000;	// time it will be removed from the scene
    le->lifeRate = 1.0 / ( le->endTime - le->startTime );
    le->radius = radius; //
    le->color[0] = r;
    le->color[1] = g;
    le->color[2] = b;
    le->color[3] = a;
    le->bounceFactor = bouncefactor;
    le->refEntity.reType = RT_SPRITE;
    //if ( random() < ( 0.25 * 15 ) )
        le->leMarkType = LEMT_BLOOD;
  //  else
     //   le->leMarkType = LEMT_NONE;
    le->leBounceSoundType = 0;
    if (!size)
        le->leFlags = LEF_PUFF_DONT_SCALE;
    le->refEntity.customShader = cgs.media.bloodMark[0];

    return le;

    //	trap_R_AddLightToScene( org, 20, 0.5f, 0.5f, 0.5f );

}

/*
=================
CG_PlayerBleed

Caused by ev_bullet
=================
*/
void CG_PlayerBleed(  int clientNum, int damage, vec3_t origin, vec3_t dir ) {
    //	int				r;
    int			i;//, s;
    vec3_t dir2;

    if (!cg_blood.integer)
        return;



  //  CG_SmokePuff( origin, dir, 5, 1.0f, 0.2f, 0.2f, 0.8f, 750, cg.time-250,cg.time-250,LE_MOVE_SCALE_FADE,cgs.media.smokePuffShader );

    for(i = 0; i < damage; i++)
    {
        {
            VectorCopy( dir, dir2 );

            dir2[0] += -0.50 + random();
            dir2[1] += -0.50 + random();
            dir2[2] -= random();

            CG_SpawnBloodParticle( origin, dir2, 60 + i*3, 0.0f, 3.0f +random()/2.0f, 0.4+random()/10,0.1f,0.1f,1.0f, qtrue );
        }
    }
}


void CG_CreateBleeder( vec3_t origin , int damage, int playerNum ) {
    //	localEntity_t	*le;
    //	refEntity_t		*re;
    //	int a;
    centity_t	*cent;
    vec3_t dir;

    cent = &cg_entities[ playerNum ];

    if (!cent)
        return;

    if (!cg_blood.integer)
        return;

    AngleVectors( cent->lerpAngles, dir, NULL,NULL );

    // add a little random factor
    dir[0] += -0.5 + random();
    dir[1] += -0.5 + random();

    CG_PlayerBleed(  playerNum, damage*2, origin, dir );

}
