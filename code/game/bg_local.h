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
// bg_local.h -- local definitions for the bg (both games) files

#define	MIN_WALK_NORMAL	0.7f		// can't walk on very steep slopes

#define	STEPSIZE		16

#define	JUMP_VELOCITY	350.0f //Xamis -> blud (was 320)

#define	TIMER_LAND		130
#define	TIMER_GESTURE	(34*66+50)

#define	OVERCLIP		1.001f

// all of the locals will be zeroed before each
// pmove, just to make damn sure we don't have
// any differences when running on client or server
typedef struct {
	vec3_t		forward, right, up;
	float		frametime;

	int			msec;

	qboolean	walking;
	qboolean	groundPlane;
	trace_t		groundTrace;

	float		impactSpeed;

	vec3_t		previous_origin;
	vec3_t		previous_velocity;
	int		previous_waterlevel;


	qboolean ladder; 	//Xamis
	vec3_t 		origin;          // Xamis
	vec3_t 		velocity;        // Xamis
	cplane_t 	groundplane;	 // Xamis

	float maxPlayerSpeed;// Xamis
	float maxWalkSpeed;// Xamis
	float maxCrouchedSpeed;// Xamis
	float jumpPlayerSpeed;// Xamis
	float dashPlayerSpeed;// Xamis
        qboolean        sliding;



	vec3_t 		flatforward;
	int 		groundsurfFlags;
	int		groundcontents;
	float 		forwardPush, sidePush, upPush;


} pml_t;

extern	pmove_t		*pm;
extern	pml_t		pml;

// movement parameters
extern	float	pm_stopspeed;
extern	float	pm_duckScale;
extern	float	pm_swimScale;
extern	float	pm_wadeScale;

extern	float	pm_accelerate;
extern	float	pm_airaccelerate;
extern	float	pm_wateraccelerate;
extern	float	pm_flyaccelerate;

extern	float	pm_friction;
extern	float	pm_waterfriction;
extern	float	pm_flightfriction;

extern	int		c_pmove;

void PM_ClipVelocity( vec3_t in, vec3_t normal, vec3_t out, float overbounce );
void PM_AddTouchEnt( int entityNum );
void PM_AddEvent( int newEvent );


qboolean	PM_SlideMove( qboolean gravity );

void		PM_StepSlideMove( qboolean gravity );
void PM_StartWeaponAnim( int anim );
void PM_StartTorsoAnim( int anim );
void PM_StartLegsAnim( int anim ) ;
void PM_AdjustAngleForLedgeClimb( playerState_t *ps, usercmd_t *ucmd );
int CheckLadder( void );



