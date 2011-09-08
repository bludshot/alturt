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

// g_client.c -- client functions that don't happen every frame

static vec3_t   playerMins = {-15, -15, -24};
static vec3_t   playerMaxs = {15, 15, 32};

//blud trying to fix player height. UH - This doesn't seem to do anything!
//static vec3_t   playerMins = {-15, -15, -24};
//static vec3_t   playerMaxs = {15, 15, 44};


/*QUAKED info_player_deathmatch (1 0 1) (-16 -16 -24) (16 16 32) initial
potential spawning position for deathmatch games.
The first time a player enters the game, they will be at an 'initial' spot.
Targets will be fired when someone spawns in on them.
"nobots" will prevent bots from using this spot.
"nohumans" will prevent non-bots from using this spot.
*/
void SP_info_player_deathmatch( gentity_t *ent ) {
        int             i;

        G_SpawnInt( "nobots", "0", &i);
        if ( i ) {
                ent->flags |= FL_NO_BOTS;
        }
        G_SpawnInt( "nohumans", "0", &i );
        if ( i ) {
                ent->flags |= FL_NO_HUMANS;
        }
}

/*QUAKED info_ut_spawn (1 .5 0) (-16 -16 -24) (16 16 32) initial
potential spawning position for Urban Terror.

-------- KEYS --------
team : team that this spawn belongs to ("red" or "blue")
group : this spawn groups with others of same groupID. A team chooses spawns from a certain group.
g_gametype : a list of gametypes on which to use this spawn eg: "4, 5, 6"

-------- NOTES --------
Urban Terror gametype mappings are:
Free For All 0
Single Player 1
Team Deathmatch 3
Team Survivor 4
Assasins 5
Capture And Hold 6
Capture The Flag 7
Bomb 8

You'd use the groups key in maps if you wanted to make sure a team will spawn together in a certain location,
so you might take 8 spawn points, give them all gametypes of "3,4,5,6,7" (all teamplays) and then assign all
the eight a group id of "1" then you might do another eight and make their group id all "2". UT will choose a
"group" at the begining of a round and spawn all members of "team" there. Normally you'd have at few groups
of spawns so you could have lots of potential team starting positions.
*/
void SP_info_ut_spawn( gentity_t *ent ) {

}



/*QUAKED info_player_start (1 0 0) (-16 -16 -24) (16 16 32)
equivelant to info_player_deathmatch
*/
void SP_info_player_start(gentity_t *ent) {
        ent->classname = "info_player_deathmatch";
        SP_info_player_deathmatch( ent );
}

/*QUAKED info_player_intermission (1 0 1) (-16 -16 -24) (16 16 32)
The intermission will be viewed from this point.  Target an info_notnull for the view direction.
*/
void SP_info_player_intermission( gentity_t *ent ) {

}



/*
=======================================================================

  SelectSpawnPoint

=======================================================================
*/

/*
================
SpotWouldTelefrag

================
*/
qboolean SpotWouldTelefrag( gentity_t *spot ) {
        int                     i, num;
        int                     touch[MAX_GENTITIES];
        gentity_t       *hit;
        vec3_t          mins, maxs;

        VectorAdd( spot->s.origin, playerMins, mins );
        VectorAdd( spot->s.origin, playerMaxs, maxs );
        num = trap_EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

        for (i=0 ; i<num ; i++) {
                hit = &g_entities[touch[i]];
                //if ( hit->client && hit->client->ps.stats[STAT_HEALTH] > 0 ) {
                if ( hit->client) {
                        return qtrue;
                }

        }

        return qfalse;
}

/*
================
SelectNearestDeathmatchSpawnPoint

Find the spot that we DON'T want to use
================
*/
#define MAX_SPAWN_POINTS        128
gentity_t *SelectNearestDeathmatchSpawnPoint( vec3_t from ) {
        gentity_t       *spot;
        vec3_t          delta;
        float           dist, nearestDist;
        gentity_t       *nearestSpot;

        nearestDist = 999999;
        nearestSpot = NULL;
        spot = NULL;

        while ((spot = G_Find (spot, FOFS(classname), "info_player_deathmatch")) != NULL) {

                VectorSubtract( spot->s.origin, from, delta );
                dist = VectorLength( delta );
                if ( dist < nearestDist ) {
                        nearestDist = dist;
                        nearestSpot = spot;
                }
        }

        return nearestSpot;
}


/*
================
SelectRandomDeathmatchSpawnPoint

go to a random point that doesn't telefrag
================
*/
#define MAX_SPAWN_POINTS        128
gentity_t *SelectRandomDeathmatchSpawnPoint(qboolean isbot) {
        gentity_t       *spot;
        int                     count;
        int                     selection;
        gentity_t       *spots[MAX_SPAWN_POINTS];

        count = 0;
        spot = NULL;

        while((spot = G_Find (spot, FOFS(classname), "info_player_deathmatch")) != NULL && count < MAX_SPAWN_POINTS)
        {
                if(SpotWouldTelefrag(spot))
                        continue;

                if(((spot->flags & FL_NO_BOTS) && isbot) ||
                   ((spot->flags & FL_NO_HUMANS) && !isbot))
                {
                        // spot is not for this human/bot player
                        continue;
                }

                spots[count] = spot;
                count++;
        }

        if ( !count ) { // no spots that won't telefrag
                return G_Find( NULL, FOFS(classname), "info_player_deathmatch");
        }

        selection = rand() % count;
        return spots[ selection ];
}

/*
===========
SelectRandomFurthestSpawnPoint

Chooses a player start, deathmatch start, etc
============
*/
gentity_t *SelectRandomFurthestSpawnPoint ( vec3_t avoidPoint, vec3_t origin, vec3_t angles, qboolean isbot ) {
        gentity_t       *spot;
        vec3_t          delta;
        float           dist;
        float           list_dist[MAX_SPAWN_POINTS];
        gentity_t       *list_spot[MAX_SPAWN_POINTS];
        int                     numSpots, rnd, i, j;

        numSpots = 0;
        spot = NULL;

        while((spot = G_Find (spot, FOFS(classname), "info_player_deathmatch")) != NULL)
        {
                if(SpotWouldTelefrag(spot))
                        continue;

                if(((spot->flags & FL_NO_BOTS) && isbot) ||
                   ((spot->flags & FL_NO_HUMANS) && !isbot))
                {
                        // spot is not for this human/bot player
                        continue;
                }

                VectorSubtract( spot->s.origin, avoidPoint, delta );
                dist = VectorLength( delta );

                for (i = 0; i < numSpots; i++)
                {
                        if(dist > list_dist[i])
                        {
                                if (numSpots >= MAX_SPAWN_POINTS)
                                        numSpots = MAX_SPAWN_POINTS - 1;

                                for(j = numSpots; j > i; j--)
                                {
                                        list_dist[j] = list_dist[j-1];
                                        list_spot[j] = list_spot[j-1];
                                }

                                list_dist[i] = dist;
                                list_spot[i] = spot;

                                numSpots++;
                                break;
                        }
                }

                if(i >= numSpots && numSpots < MAX_SPAWN_POINTS)
                {
                        list_dist[numSpots] = dist;
                        list_spot[numSpots] = spot;
                        numSpots++;
                }
        }

        if(!numSpots)
        {
                spot = G_Find(NULL, FOFS(classname), "info_player_deathmatch");

                if (!spot)
                        G_Error( "Couldn't find a spawn point" );

                VectorCopy (spot->s.origin, origin);
                origin[2] += 9;
                VectorCopy (spot->s.angles, angles);
                return spot;
        }

        // select a random spot from the spawn points furthest away
        rnd = random() * (numSpots / 2);

        VectorCopy (list_spot[rnd]->s.origin, origin);
        origin[2] += 9;
        VectorCopy (list_spot[rnd]->s.angles, angles);

        return list_spot[rnd];
}

/*
===========
SelectSpawnPoint

Chooses a player start, deathmatch start, etc
============
*/
gentity_t *SelectSpawnPoint ( vec3_t avoidPoint, vec3_t origin, vec3_t angles, qboolean isbot ) {
        return SelectRandomFurthestSpawnPoint( avoidPoint, origin, angles, isbot );

        /*
        gentity_t       *spot;
        gentity_t       *nearestSpot;

        nearestSpot = SelectNearestDeathmatchSpawnPoint( avoidPoint );

        spot = SelectRandomDeathmatchSpawnPoint ( );
        if ( spot == nearestSpot ) {
                // roll again if it would be real close to point of death
                spot = SelectRandomDeathmatchSpawnPoint ( );
                if ( spot == nearestSpot ) {
                        // last try
                        spot = SelectRandomDeathmatchSpawnPoint ( );
                }
        }

        // find a single player start spot
        if (!spot) {
                G_Error( "Couldn't find a spawn point" );
        }

        VectorCopy (spot->s.origin, origin);
        origin[2] += 9;
        VectorCopy (spot->s.angles, angles);

        return spot;
        */
}

/*
===========
SelectInitialSpawnPoint

Try to find a spawn point marked 'initial', otherwise
use normal spawn selection.
============
*/
gentity_t *SelectInitialSpawnPoint( vec3_t origin, vec3_t angles, qboolean isbot ) {
        gentity_t       *spot;

        spot = NULL;

        while ((spot = G_Find (spot, FOFS(classname), "info_player_deathmatch")) != NULL)
        {
                if(((spot->flags & FL_NO_BOTS) && isbot) ||
                   ((spot->flags & FL_NO_HUMANS) && !isbot))
                {
                        continue;
                }

                if((spot->spawnflags & 0x01))
                        break;
        }

        if (!spot || SpotWouldTelefrag(spot))
                return SelectSpawnPoint(vec3_origin, origin, angles, isbot);

        VectorCopy (spot->s.origin, origin);
        origin[2] += 9;
        VectorCopy (spot->s.angles, angles);

        return spot;
}

/*
===========
SelectSpectatorSpawnPoint

============
*/
gentity_t *SelectSpectatorSpawnPoint( vec3_t origin, vec3_t angles ) {
        FindIntermissionPoint();

        VectorCopy( level.intermission_origin, origin );
        VectorCopy( level.intermission_angle, angles );

        return NULL;
}

/*
=======================================================================

BODYQUE

=======================================================================
*/

/*
===============
InitBodyQue
===============
*/
void InitBodyQue (void) {
        int             i;
        gentity_t       *ent;

        level.bodyQueIndex = 0;
        for (i=0; i<BODY_QUEUE_SIZE ; i++) {
                ent = G_Spawn();
                ent->classname = "bodyque";
                ent->neverFree = qtrue;
                level.bodyQue[i] = ent;
        }
}

/*
=============
BodySink

After sitting around for five seconds, fall into the ground and dissapear
=============
*/
void BodySink( gentity_t *ent ) {
        if ( level.time - ent->timestamp > 6500 ) {
                // the body ques are never actually freed, they are just unlinked
                trap_UnlinkEntity( ent );
                ent->physicsObject = qfalse;
                return;
        }
        ent->nextthink = level.time + 100;
        ent->s.pos.trBase[2] -= 1;
}

/*
=============
CopyToBodyQue

A player is respawning, so make an entity that looks
just like the existing corpse to leave behind.
=============
*/
void CopyToBodyQue( gentity_t *ent ) {
#ifdef MISSIONPACK
        gentity_t       *e;
        int i;
#endif
        gentity_t               *body;
        int                     contents;

        trap_UnlinkEntity (ent);

        // if client is in a nodrop area, don't leave the body
        contents = trap_PointContents( ent->s.origin, -1 );
        if ( contents & CONTENTS_NODROP ) {
                return;
        }

        // grab a body que and cycle to the next one
        body = level.bodyQue[ level.bodyQueIndex ];
        level.bodyQueIndex = (level.bodyQueIndex + 1) % BODY_QUEUE_SIZE;

        trap_UnlinkEntity (body);

        body->s = ent->s;
        body->s.eFlags = EF_DEAD;               // clear EF_TALK, etc
#ifdef MISSIONPACK
        if ( ent->s.eFlags & EF_KAMIKAZE ) {
                body->s.eFlags |= EF_KAMIKAZE;

                // check if there is a kamikaze timer around for this owner
                for (i = 0; i < MAX_GENTITIES; i++) {
                        e = &g_entities[i];
                        if (!e->inuse)
                                continue;
                        if (e->activator != ent)
                                continue;
                        if (strcmp(e->classname, "kamikaze timer"))
                                continue;
                        e->activator = body;
                        break;
                }
        }
#endif
        body->s.powerups = 0;   // clear powerups
        body->s.loopSound = 0;  // clear lava burning
        body->s.number = body - g_entities;
        body->timestamp = level.time;
        body->physicsObject = qtrue;
        body->physicsBounce = 0;                // don't bounce
        if ( body->s.groundEntityNum == ENTITYNUM_NONE ) {
                body->s.pos.trType = TR_GRAVITY;
                body->s.pos.trTime = level.time;
                VectorCopy( ent->client->ps.velocity, body->s.pos.trDelta );
        } else {
                body->s.pos.trType = TR_STATIONARY;
        }
        body->s.event = 0;

        // change the animation to the last-frame only, so the sequence
        // doesn't repeat anew for the body
        switch ( body->s.legsAnim & ~ANIM_TOGGLEBIT ) {
        case BOTH_DEATH1:
        case BOTH_DEAD1:
                body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD1;
                break;
        case BOTH_DEATH2:
        case BOTH_DEAD2:
                body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD2;
                break;
        case BOTH_DEATH3:
        case BOTH_DEAD3:
        default:
                body->s.torsoAnim = body->s.legsAnim = BOTH_DEAD3;
                break;
        }

        body->r.svFlags = ent->r.svFlags;
        VectorCopy (ent->r.mins, body->r.mins);
        VectorCopy (ent->r.maxs, body->r.maxs);
        VectorCopy (ent->r.absmin, body->r.absmin);
        VectorCopy (ent->r.absmax, body->r.absmax);

        body->clipmask = CONTENTS_SOLID | CONTENTS_PLAYERCLIP;
        body->r.contents = CONTENTS_CORPSE;
        body->r.ownerNum = ent->s.number;

        body->nextthink = level.time + 5000;
        body->think = BodySink;

        body->die = body_die;

        // don't take more damage if already gibbed
        if ( ent->health <= GIB_HEALTH ) {
                body->takedamage = qfalse;
        } else {
                body->takedamage = qtrue;
        }


        VectorCopy ( body->s.pos.trBase, body->r.currentOrigin );
        trap_LinkEntity (body);
}

//======================================================================


/*
==================
SetClientViewAngle

==================
*/
void SetClientViewAngle( gentity_t *ent, vec3_t angle ) {
        int                     i;

        // set the delta angle
        for (i=0 ; i<3 ; i++) {
                int             cmdAngle;

                cmdAngle = ANGLE2SHORT(angle[i]);
                ent->client->ps.delta_angles[i] = cmdAngle - ent->client->pers.cmd.angles[i];
        }
        VectorCopy( angle, ent->s.angles );
        VectorCopy (ent->s.angles, ent->client->ps.viewangles);
}

/*
================
respawn
================
*/
void respawn( gentity_t *ent ) {
        gentity_t       *tent;

        CopyToBodyQue (ent);
        ClientSpawn(ent);

        // add a teleportation effect
        tent = G_TempEntity( ent->client->ps.origin, EV_PLAYER_TELEPORT_IN );
        tent->s.clientNum = ent->s.clientNum;
}

/*
================
TeamCount

Returns number of players on a team
================
*/
team_t TeamCount( int ignoreClientNum, int team ) {
        int             i;
        int             count = 0;

        for ( i = 0 ; i < level.maxclients ; i++ ) {
                if ( i == ignoreClientNum ) {
                        continue;
                }
                if ( level.clients[i].pers.connected == CON_DISCONNECTED ) {
                        continue;
                }
                if ( level.clients[i].sess.sessionTeam == team ) {
                        count++;
                }
        }

        return count;
}

/*
================
TeamLeader

Returns the client number of the team leader
================
*/
int TeamLeader( int team ) {
        int             i;

        for ( i = 0 ; i < level.maxclients ; i++ ) {
                if ( level.clients[i].pers.connected == CON_DISCONNECTED ) {
                        continue;
                }
                if ( level.clients[i].sess.sessionTeam == team ) {
                        if ( level.clients[i].sess.teamLeader )
                                return i;
                }
        }

        return -1;
}


/*
================
PickTeam

================
*/
team_t PickTeam( int ignoreClientNum ) {
        int             counts[TEAM_NUM_TEAMS];

        counts[TEAM_BLUE] = TeamCount( ignoreClientNum, TEAM_BLUE );
        counts[TEAM_RED] = TeamCount( ignoreClientNum, TEAM_RED );

        if ( counts[TEAM_BLUE] > counts[TEAM_RED] ) {
                return TEAM_RED;
        }
        if ( counts[TEAM_RED] > counts[TEAM_BLUE] ) {
                return TEAM_BLUE;
        }
        // equal team count, so join the team with the lowest score
        if ( level.teamScores[TEAM_BLUE] > level.teamScores[TEAM_RED] ) {
                return TEAM_RED;
        }
        return TEAM_BLUE;
}

/*
===========
ForceClientSkin

Forces a client's skin (for teamplay)
===========
*/
/*
static void ForceClientSkin( gclient_t *client, char *model, const char *skin ) {
        char *p;

        if ((p = Q_strrchr(model, '/')) != 0) {
                *p = 0;
        }

        Q_strcat(model, MAX_QPATH, "/");
        Q_strcat(model, MAX_QPATH, skin);
}
*/

/*
===========
ClientCheckName
============
*/
static void ClientCleanName(const char *in, char *out, int outSize)
{
        int outpos = 0, colorlessLen = 0, spaces = 0;

        // discard leading spaces
        for(; *in == ' '; in++);

        for(; *in && outpos < outSize - 1; in++)
        {
                out[outpos] = *in;

                if(*in == ' ')
                {
                        // don't allow too many consecutive spaces
                        if(spaces > 2)
                                continue;

                        spaces++;
                }
                else if(outpos > 0 && out[outpos - 1] == Q_COLOR_ESCAPE)
                {
                        if(Q_IsColorString(&out[outpos - 1]))
                        {
                                colorlessLen--;

                                if(ColorIndex(*in) == 0)
                                {
                                        // Disallow color black in names to prevent players
                                        // from getting advantage playing in front of black backgrounds
                                        outpos--;
                                        continue;
                                }
                        }
                        else
                        {
                                spaces = 0;
                                colorlessLen++;
                        }
                }
                else
                {
                        spaces = 0;
                        colorlessLen++;
                }

                outpos++;
        }

        out[outpos] = '\0';

        // don't allow empty names
        if( *out == '\0' || colorlessLen == 0)
                Q_strncpyz(out, "UnnamedPlayer", outSize );
}


/*
===========
ClientUserInfoChanged

Called from ClientConnect when the player first connects and
directly by the server system when the player updates a userinfo variable.

The game can override any of the settings and call trap_SetUserinfo
if desired.
============
*/
void ClientUserinfoChanged( int clientNum ) {
        gentity_t *ent;
        int		teamTask, teamLeader, team, health;
        int		racered, raceblue; //blud
        char                    gear[MAX_QPATH];//xamis
        char                    weapmodes_save[MAX_QPATH];//xamis
        char    *s;
        char    skin[MAX_QPATH]; //blud
        char    model[MAX_QPATH];
        char    headModel[MAX_QPATH];
        char    oldname[MAX_STRING_CHARS];
        gclient_t       *client;
        char    c1[MAX_INFO_STRING];
        char    c2[MAX_INFO_STRING];
        char    redTeam[MAX_INFO_STRING];
        char    blueTeam[MAX_INFO_STRING];
        char    userinfo[MAX_INFO_STRING];
        char    guid[MAX_INFO_STRING];

        //trap_SendServerCommand( -1, "print \"ClientUserinfoChanged.\n\"" ); //blud debug

        ent = g_entities + clientNum;
        client = ent->client;

        trap_GetUserinfo( clientNum, userinfo, sizeof( userinfo ) );

        // check for malformed or illegal info strings
        if ( !Info_Validate(userinfo) ) {
                strcpy (userinfo, "\\name\\badinfo");
        }

        // check for local client
        s = Info_ValueForKey( userinfo, "ip" );
        if ( !strcmp( s, "localhost" ) ) {
                client->pers.localClient = qtrue;
        }

        // check the item prediction
        s = Info_ValueForKey( userinfo, "cg_predictItems" );
        if ( !atoi( s ) ) {
                client->pers.predictItemPickup = qfalse;
        } else {
                client->pers.predictItemPickup = qtrue;
        }


        // set name
        Q_strncpyz ( oldname, client->pers.netname, sizeof( oldname ) );
        s = Info_ValueForKey (userinfo, "name");
        ClientCleanName( s, client->pers.netname, sizeof(client->pers.netname) );

        if ( client->sess.sessionTeam == TEAM_SPECTATOR ) {
                if ( client->sess.spectatorState == SPECTATOR_SCOREBOARD ) {
                        Q_strncpyz( client->pers.netname, "scoreboard", sizeof(client->pers.netname) );
                }
        }

        if ( client->pers.connected == CON_CONNECTED ) {
                if ( strcmp( oldname, client->pers.netname ) ) {
                        trap_SendServerCommand( -1, va("print \"%s" S_COLOR_WHITE " renamed to %s\n\"", oldname,
                                client->pers.netname) );
                }
        }

        // set max health

        health = atoi( Info_ValueForKey( userinfo, "handicap" ) );
        client->pers.maxHealth = health;
        client->pers.maxStamina = client->pers.maxHealth *9; //Xamis
        if ( client->pers.maxHealth < 1 || client->pers.maxHealth > 100 ) {
                client->pers.maxHealth = 100;
        }


				//blud: I will always do this, but if it's a team GT I will just ignore model elsewhere where it actually gets set/changed
                Q_strncpyz( model, Info_ValueForKey (userinfo, "model"), sizeof( model ) );


        //blud adding skin cvar for non-team gametypes
        //and racered raceblue cvars for team gametypes
        // racered and raceblue (0, 1, 2, 3)
        racered = atoi(Info_ValueForKey(userinfo, "racered"));
        raceblue = atoi(Info_ValueForKey(userinfo, "raceblue"));
        Q_strncpyz( skin, Info_ValueForKey (userinfo, "skin"), sizeof( skin ) );
        Q_strncpyz( gear, Info_ValueForKey (userinfo, "gear"), sizeof( gear ) );
        Q_strncpyz( weapmodes_save, Info_ValueForKey (userinfo, "weapmodes_save"), sizeof( weapmodes_save ) );

		// bots set their team a few frames later
        if (g_gametype.integer >= GT_TEAM && g_entities[clientNum].r.svFlags & SVF_BOT) {
                s = Info_ValueForKey( userinfo, "team" );
                if ( !Q_stricmp( s, "red" ) || !Q_stricmp( s, "r" ) ) {
                        team = TEAM_RED;
                } else if ( !Q_stricmp( s, "blue" ) || !Q_stricmp( s, "b" ) ) {
                        team = TEAM_BLUE;
                } else {
                        // pick the team with the least number of players
                        team = PickTeam( clientNum );
                }
        }
        else {
                team = client->sess.sessionTeam;
        }


#ifdef MISSIONPACK
        if (g_gametype.integer >= GT_TEAM) {
                client->pers.teamInfo = qtrue;
        } else {
                s = Info_ValueForKey( userinfo, "teamoverlay" );
                if ( ! *s || atoi( s ) != 0 ) {
                        client->pers.teamInfo = qtrue;
                } else {
                        client->pers.teamInfo = qfalse;
                }
        }
#else
        // teamInfo
        s = Info_ValueForKey( userinfo, "teamoverlay" );
        if ( ! *s || atoi( s ) != 0 ) {
                client->pers.teamInfo = qtrue;
        } else {
                client->pers.teamInfo = qfalse;
        }
#endif
        /*
        s = Info_ValueForKey( userinfo, "cg_pmove_fixed" );
        if ( !*s || atoi( s ) == 0 ) {
                client->pers.pmoveFixed = qfalse;
        }
        else {
                client->pers.pmoveFixed = qtrue;
        }
        */

        // team task (0 = none, 1 = offence, 2 = defence)
        teamTask = atoi(Info_ValueForKey(userinfo, "teamtask"));
        // team Leader (1 = leader, 0 is normal player)
        teamLeader = client->sess.teamLeader;

        // colors
        strcpy(c1, Info_ValueForKey( userinfo, "color1" ));
        strcpy(c2, Info_ValueForKey( userinfo, "color2" ));

        strcpy(redTeam, Info_ValueForKey( userinfo, "g_redteam" ));
        strcpy(blueTeam, Info_ValueForKey( userinfo, "g_blueteam" ));
        strcpy(guid, Info_ValueForKey(userinfo, "cl_guid"));

        //blud updated these to include rr rb skin
        // send over a subset of the userinfo keys so other clients can
        // print scoreboards, display models, and play custom sounds
        if (ent->r.svFlags & SVF_BOT)
        {
                s = va("n\\%s\\t\\%i\\model\\%s\\hmodel\\%s\\rr\\%d\\rb\\%d\\skin\\%s\\c1\\%s\\c2\\%s\\hc\\%i\\w\\%i\\l\\%i\\skill\\%s\\gear\\%s\\tt\\%d\\tl\\%d\\weapmodes\\%s",
                        client->pers.netname, team, model, headModel, racered, raceblue, skin, c1, c2,
                        client->pers.maxHealth, client->sess.wins, client->sess.losses,
                        Info_ValueForKey( userinfo, "skill" ),gear, teamTask, teamLeader,weapmodes_save );
        }
        else
        {
                s = va("n\\%s\\guid\\%s\\t\\%i\\model\\%s\\hmodel\\%s\\rr\\%d\\rb\\%d\\skin\\%s\\g_redteam\\%s\\g_blueteam\\%s\\c1\\%s\\c2\\%s\\hc\\%i\\w\\%i\\l\\%i\\gear\\%s\\tt\\%d\\tl\\%d\\weapmodes\\%s",
                        client->pers.netname, guid, client->sess.sessionTeam, model, headModel, racered, raceblue, skin, redTeam, blueTeam, c1, c2,
                        client->pers.maxHealth, client->sess.wins, client->sess.losses,gear, teamTask, teamLeader,weapmodes_save);
        }

     
        
        trap_SetConfigstring( CS_PLAYERS+clientNum, s );

        // this is not the userinfo, more like the configstring actually
        G_LogPrintf( "ClientUserinfoChanged: %i %s\n", clientNum, s );
        
//if ( client->loadoutEnabled  )
    //    G_PlayerLoadout( ent );
}


/*
===========
ClientConnect

Called when a player begins connecting to the server.
Called again for every map change or tournement restart.

The session information will be valid after exit.

Return NULL if the client should be allowed, otherwise return
a string with the reason for denial.

Otherwise, the client will be sent the current gamestate
and will eventually get to ClientBegin.

firstTime will be qtrue the very first time a client connects
to the server machine, but qfalse on map changes and tournement
restarts.
============
*/
char *ClientConnect( int clientNum, qboolean firstTime, qboolean isBot ) {
        char            *value;
//      char            *areabits;
        gclient_t       *client;
        char            userinfo[MAX_INFO_STRING];
        gentity_t       *ent;

        ent = &g_entities[ clientNum ];

        trap_GetUserinfo( clientNum, userinfo, sizeof( userinfo ) );

        // IP filtering
        // https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=500
        // recommanding PB based IP / GUID banning, the builtin system is pretty limited
        // check to see if they are on the banned IP list
        value = Info_ValueForKey (userinfo, "ip");
        if ( G_FilterPacket( value ) ) {
                return "You are banned from this server.";
        }

  // we don't check password for bots and local client
  // NOTE: local client <-> "ip" "localhost"
  //   this means this client is not running in our current process
        if ( !isBot && (strcmp(value, "localhost") != 0)) {
                // check for a password
                value = Info_ValueForKey (userinfo, "password");
                if ( g_password.string[0] && Q_stricmp( g_password.string, "none" ) &&
                        strcmp( g_password.string, value) != 0) {
                        return "Invalid password";
                }
        }

        // they can connect
        ent->client = level.clients + clientNum;
        client = ent->client;

//      areabits = client->areabits;

        memset( client, 0, sizeof(*client) );

        client->pers.connected = CON_CONNECTING;

        // read or initialize the session data
        if ( firstTime || level.newSession ) {
                G_InitSessionData( client, userinfo );
        }
        G_ReadSessionData( client );

        if( isBot ) {
                ent->r.svFlags |= SVF_BOT;
                ent->inuse = qtrue;
                if( !G_BotConnect( clientNum, !firstTime ) ) {
                        return "BotConnectfailed";
                }
        }

        // get and distribute relevent paramters
        G_LogPrintf( "ClientConnect: %i\n", clientNum );
        ClientUserinfoChanged( clientNum );

        // don't do the "xxx connected" messages if they were caried over from previous level
        if ( firstTime ) {
                trap_SendServerCommand( -1, va("print \"%s" S_COLOR_WHITE " connected\n\"", client->pers.netname) );
        }

        if ( g_gametype.integer >= GT_TEAM &&
                client->sess.sessionTeam != TEAM_SPECTATOR ) {
                BroadcastTeamChange( client, -1 );
        }

        // count current clients and rank for scoreboard
        CalculateRanks();

        // for statistics
//      client->areabits = areabits;
//      if ( !client->areabits )
//              client->areabits = G_Alloc( (trap_AAS_PointReachabilityAreaIndex( NULL ) + 7) / 8 );

        return NULL;
}

/*
===========
ClientBegin

called when a client has finished connecting, and is ready
to be placed into the level.  This will happen every level load,
and on transition between teams, but doesn't happen on respawns
============
*/
void ClientBegin( int clientNum ) {
        gentity_t       *ent;
        gclient_t       *client;
        gentity_t       *tent;
        int                     flags;

        ent = g_entities + clientNum;

        client = level.clients + clientNum;

        if ( ent->r.linked ) {
                trap_UnlinkEntity( ent );
        }
        G_InitGentity( ent );
        ent->touch = 0;
        ent->pain = 0;
        ent->client = client;

        client->pers.connected = CON_CONNECTED;
        client->pers.enterTime = level.time;
        client->pers.teamState.state = TEAM_BEGIN;

        // save eflags around this, because changing teams will
        // cause this to happen with a valid entity, and we
        // want to make sure the teleport bit is set right
        // so the viewpoint doesn't interpolate through the
        // world to the new position
        flags = client->ps.eFlags;
        memset( &client->ps, 0, sizeof( client->ps ) );
        client->ps.eFlags = flags;

        // locate ent at a spawn point
        ClientSpawn( ent );

        if ( client->sess.sessionTeam != TEAM_SPECTATOR ) {
                // send event
                tent = G_TempEntity( ent->client->ps.origin, EV_PLAYER_TELEPORT_IN );
                tent->s.clientNum = ent->s.clientNum;

                if ( g_gametype.integer != GT_ASN  ) {
                        trap_SendServerCommand( -1, va("print \"%s" S_COLOR_WHITE " entered the game\n\"", client->pers.netname) );
                }
        }
        G_LogPrintf( "ClientBegin: %i\n", clientNum );

        // count current clients and rank for scoreboard
        CalculateRanks();
}


void G_PlayerLoadout( gentity_t *ent ){
	int			index;
	int			i;
	gclient_t	*client;
	char		userinfo[MAX_INFO_STRING];
	char		gear[MAX_QPATH];
	int			inventoryItemSlot;
	int			WPPWnum;
	int			extraAmmoMultiplier;
	int			len;

	extraAmmoMultiplier = 1;


	//get the client number and the value of their gear cvar

	index = ent - g_entities;
	trap_GetUserinfo( index, userinfo, sizeof(userinfo) );
	client = ent->client;
	Q_strncpyz( gear, Info_ValueForKey (userinfo, "gear"), sizeof( gear ) );
	client->ps.clientNum = index;

	BG_ClearWeapons( ent->client->ps.stats );

        
        if( ent->r.svFlags & SVF_BOT){
            gear[0] ='G';
            gear[1] ='L';
                    gear[2] ='I';
                    gear[3] ='A';
                    gear[4] ='R';
                    gear[5] ='W';
                gear[6] ='A';                    
        }
	//Make sure gear string is the correct length so that later we aren't trying to read chars that aren't even there.
	len = strlen(gear);

	if (len < GEAR_SLOT_MAX)
	{
		//append characters onto the gear cvar to make it the right length
		for (i = len; i < GEAR_SLOT_MAX; i++)
		{
			gear[i] = GEAR_NONE;
		}

		gear[GEAR_SLOT_MAX] = '\0';
	}
	else if (len > GEAR_SLOT_MAX)
	{
		//truncate the gear cvar
		gear[GEAR_SLOT_MAX] = '\0';
	}

	//Items - give items before weapons since pw_ammo affects number of clips
	inventoryItemSlot = 0;
	for( i = GEAR_SLOT_ITEM_1; i < GEAR_SLOT_MAX; i++ ) 
	{
		WPPWnum = GearToWPPW(gear[i]);

		if (!isGoodItem(WPPWnum, gear[GEAR_SLOT_PRIMARY], gear[GEAR_SLOT_SECONDARY], gear[GEAR_SLOT_GRENADE], i))
		{
			bg_inventory.item[ent->client->ps.clientNum][inventoryItemSlot] = getDefaultItem(i);
		}
		else
		{
			bg_inventory.item[ent->client->ps.clientNum][inventoryItemSlot] = WPPWnum;
			if (WPPWnum == PW_AMMO )
			{
				extraAmmoMultiplier = 2;
			}
		}

		inventoryItemSlot++;
	}

	//knife isn't part of gear, you just always get it
	BG_PackWeapon( WP_KNIFE , ent->client->ps.stats );
	bg_weaponlist[WP_KNIFE].rounds[ ent->client->ps.clientNum]= RoundCount(WP_KNIFE);
	bg_weaponlist[WP_KNIFE].numClips[ ent->client->ps.clientNum] = ClipCount(WP_KNIFE);
	bg_inventory.sort[ent->client->ps.clientNum][MELEE] = WP_KNIFE;

	//Give them all their weapons
	for( i = GEAR_SLOT_SIDEARM; i <= GEAR_SLOT_GRENADE; i++ )
	{
		WPPWnum = GearToWPPW(gear[i]);

		if (!isGoodItem(WPPWnum, gear[GEAR_SLOT_PRIMARY], gear[GEAR_SLOT_SECONDARY], gear[GEAR_SLOT_GRENADE], i))
		{
			WPPWnum = getDefaultItem(i);
		}

		BG_PackWeapon( WPPWnum , ent->client->ps.stats );
		bg_weaponlist[WPPWnum].rounds[ ent->client->ps.clientNum]= RoundCount(WPPWnum);
		bg_weaponlist[WPPWnum].numClips[ent->client->ps.clientNum] = ClipCount(WPPWnum) * extraAmmoMultiplier;
		bg_inventory.sort[ent->client->ps.clientNum][i+1] = WPPWnum; //the g weapon slot numbers are 1 lower than the gear slot numbers. Maybe we should change MELEE to -1 sometime...
	}


	//G_Printf("gear string 4:%c 5:%c 6:%c\n", gear.string[4],gear.string[5],gear.string[6]); //xamis debug

	//I'm wondering if right here I should set the client's gear cvar if it was invalid at all?
	//I know I don't really need to, but I think I want to?...

	//Switch the player's gun to the best one they have
	if ( bg_inventory.sort[ent->client->ps.clientNum][PRIMARY])
		client->ps.weapon = bg_inventory.sort[ent->client->ps.clientNum][PRIMARY];
	else if ( bg_inventory.sort[ent->client->ps.clientNum][SECONDARY])
		client->ps.weapon = bg_inventory.sort[ent->client->ps.clientNum][SECONDARY];
	else if ( bg_inventory.sort[ent->client->ps.clientNum][SIDEARM])
		client->ps.weapon = bg_inventory.sort[ent->client->ps.clientNum][SIDEARM];
	else
		client->ps.weapon = bg_inventory.sort[ent->client->ps.clientNum][MELEE];

	//G_AddEvent(ent, EV_WEAPON_DROPPED, 0);

}


/*
===========
ClientSpawn

Called every time a client is placed fresh in the world:
after the first ClientBegin, and after each respawn
Initializes all non-persistant parts of playerState
============
*/
void ClientSpawn(gentity_t *ent) {
        int             index;
        vec3_t  spawn_origin, spawn_angles;
        gclient_t       *client;
        int             i;
        clientPersistant_t      saved;
        clientSession_t         savedSess;
        int             persistant[MAX_PERSISTANT];
        gentity_t       *spawnPoint;
        int             flags;
        int             savedPing;
//      char    *savedAreaBits;
        int             accuracy_hits, accuracy_shots;
        int             eventSequence;
        char    userinfo[MAX_INFO_STRING];
        char    gear[MAX_QPATH];

        index = ent - g_entities;
        client = ent->client;

        VectorClear(spawn_origin);
        

        // find a spawn point
        // do it before setting health back up, so farthest
        // ranging doesn't count this client
        if ( client->sess.sessionTeam == TEAM_SPECTATOR ) {
                spawnPoint = SelectSpectatorSpawnPoint (
                                                spawn_origin, spawn_angles);
        } else if (g_gametype.integer >= GT_TEAM ) {
                // all base oriented team games use the CTF spawn points

            spawnPoint = SelectCTFSpawnPoint (
                                                client->sess.sessionTeam,
                                                client->pers.teamState.state,
                                                spawn_origin, spawn_angles,
                                                !!(ent->r.svFlags & SVF_BOT));
        }
        else
        {
                // the first spawn should be at a good looking spot
                if ( !client->pers.initialSpawn && client->pers.localClient )
                {
                        client->pers.initialSpawn = qtrue;
                        spawnPoint = SelectInitialSpawnPoint(spawn_origin, spawn_angles,
                                                             !!(ent->r.svFlags & SVF_BOT));
                }
                else
                {
                        // don't spawn near existing origin if possible
                        spawnPoint = SelectSpawnPoint (
                                client->ps.origin,
                                spawn_origin, spawn_angles, !!(ent->r.svFlags & SVF_BOT));
                }
        }
        client->pers.teamState.state = TEAM_ACTIVE;

        // always clear the kamikaze flag
        ent->s.eFlags &= ~EF_KAMIKAZE;

        // toggle the teleport bit so the client knows to not lerp
        // and never clear the voted flag
        flags = ent->client->ps.eFlags & (EF_TELEPORT_BIT | EF_VOTED | EF_TEAMVOTED);
        flags ^= EF_TELEPORT_BIT;

        // clear everything but the persistant data

        saved = client->pers;
        savedSess = client->sess;
        savedPing = client->ps.ping;
//      savedAreaBits = client->areabits;
        accuracy_hits = client->accuracy_hits;
        accuracy_shots = client->accuracy_shots;
        for ( i = 0 ; i < MAX_PERSISTANT ; i++ ) {
                persistant[i] = client->ps.persistant[i];
        }
        eventSequence = client->ps.eventSequence;

        Com_Memset (client, 0, sizeof(*client));

        client->pers = saved;
        client->sess = savedSess;
        client->ps.ping = savedPing;
//      client->areabits = savedAreaBits;
        client->accuracy_hits = accuracy_hits;
        client->accuracy_shots = accuracy_shots;
        client->lastkilled_client = -1;

        for ( i = 0 ; i < MAX_PERSISTANT ; i++ ) {
                client->ps.persistant[i] = persistant[i];
        }
        client->ps.eventSequence = eventSequence;
        // increment the spawncount so the client will detect the respawn
        client->ps.persistant[PERS_SPAWN_COUNT]++;
        client->ps.persistant[PERS_TEAM] = client->sess.sessionTeam;

        client->airOutTime = level.time + 12000;

        trap_GetUserinfo( index, userinfo, sizeof(userinfo) );
        // set max health
        client->pers.maxHealth = atoi( Info_ValueForKey( userinfo, "handicap" ) );
        if ( client->pers.maxHealth < 1 || client->pers.maxHealth > 100 ) {
                client->pers.maxHealth = 100;
                client->pers.maxStamina = 900; //Xamis

        }
        // clear entity values

        client->ps.eFlags = flags;

        ent->s.groundEntityNum = ENTITYNUM_NONE;
        ent->client = &level.clients[index];
        ent->takedamage = qtrue;
        ent->inuse = qtrue;
        ent->classname = "player";
        ent->r.contents = CONTENTS_BODY;
        ent->clipmask = MASK_PLAYERSOLID;
        ent->die = player_die;
        ent->waterlevel = 0;
        ent->watertype = 0;
        ent->flags = 0;

        VectorCopy (playerMins, ent->r.mins);
        VectorCopy (playerMaxs, ent->r.maxs);
        Q_strncpyz( gear, Info_ValueForKey (userinfo, "gear"), sizeof( gear ) );
        client->ps.clientNum = index;
       // client->loadoutEnabled = qtrue;

	//Load all values for player loadout and add it to inventory --Xamis
 	G_PlayerLoadout( ent );
        

	VectorSet( ent->client->ps.grapplePoint, 0.0f, 0.0f, 1.0f );
        // health will count down towards max_health
        ent->health = client->ps.stats[STAT_HEALTH]= STAT_MAX_HEALTH;// removed + 25 Xamis
        ent->stamina = client->ps.stats[STAT_STAMINA] = STAT_MAX_STAMINA;
          bg_weaponlist[0].rounds[client->ps.clientNum]=0; //Round count for burst mode.
          bg_weaponlist[0].numClips[client->ps.clientNum]=0; //Round count for spread.

        G_SetOrigin( ent, spawn_origin );
        VectorCopy( spawn_origin, client->ps.origin );

        // the respawned flag will be cleared after the attack and jump keys come up
        client->ps.pm_flags |= PMF_RESPAWNED;

        trap_GetUsercmd( client - level.clients, &ent->client->pers.cmd );
        SetClientViewAngle( ent, spawn_angles );

        if ( ent->client->sess.sessionTeam == TEAM_SPECTATOR ) {

        } else {
                G_KillBox( ent );
                trap_LinkEntity (ent);

                // force the base weapon up
                client->ps.weapon = WP_KNIFE;
                client->ps.weaponstate = WEAPON_READY;

        }

        // don't allow full run speed for a bit
        client->ps.pm_flags |= PMF_TIME_KNOCKBACK;
        client->ps.pm_time = 100;

        client->respawnTime = level.time;
        client->inactivityTime = level.time + g_inactivity.integer * 1000;
        client->latched_buttons = 0;

        
        // set default animations
        client->ps.torsoAnim = TORSO_STAND;
        client->ps.legsAnim = LEGS_IDLE;

        if ( level.intermissiontime ) {
                MoveClientToIntermission( ent );
        } else {
                // fire the targets of the spawn point
                G_UseTargets( spawnPoint, ent );

                // select the highest weapon number available, after any
                // spawn given items have fired

                if ( bg_inventory.sort[ent->client->ps.clientNum][PRIMARY])
                  client->ps.weapon = bg_inventory.sort[ent->client->ps.clientNum][PRIMARY];
                else if ( bg_inventory.sort[ent->client->ps.clientNum][SECONDARY])
                  client->ps.weapon = bg_inventory.sort[ent->client->ps.clientNum][SECONDARY];
                else if ( bg_inventory.sort[ent->client->ps.clientNum][SIDEARM])
                  client->ps.weapon = bg_inventory.sort[ent->client->ps.clientNum][SIDEARM];
                else
                  client->ps.weapon = bg_inventory.sort[ent->client->ps.clientNum][MELEE];

        }

        // run a client frame to drop exactly to the floor,
        // initialize animations and other things
        client->ps.commandTime = level.time - 100;
        ent->client->pers.cmd.serverTime = level.time;
        ClientThink( ent-g_entities );

        // positively link the client, even if the command times are weird
        if ( ent->client->sess.sessionTeam != TEAM_SPECTATOR ) {
                BG_PlayerStateToEntityState( &client->ps, &ent->s, qtrue );
                VectorCopy( ent->client->ps.origin, ent->r.currentOrigin );
                trap_LinkEntity( ent );
        }
	// Call Set_Mode to make sure the current weapons mode is synchronized between server and client. --Xamis
        Set_Mode(ent);
        // run the presend to set anything else
        ClientEndFrame( ent );

        // clear entity state values
        BG_PlayerStateToEntityState( &client->ps, &ent->s, qtrue );




}


/*
===========
ClientDisconnect

Called when a player drops from the server.
Will not be called between levels.

This should NOT be called directly by any game logic,
call trap_DropClient(), which will call this and do
server system housekeeping.
============
*/
void ClientDisconnect( int clientNum ) {
        gentity_t       *ent;
        gentity_t       *tent;
        int                     i;

        // cleanup if we are kicking a bot that
        // hasn't spawned yet
        G_RemoveQueuedBotBegin( clientNum );

        ent = g_entities + clientNum;
        if ( !ent->client ) {
                return;
        }

        // stop any following clients
        for ( i = 0 ; i < level.maxclients ; i++ ) {
                if ( level.clients[i].sess.sessionTeam == TEAM_SPECTATOR
                        && level.clients[i].sess.spectatorState == SPECTATOR_FOLLOW
                        && level.clients[i].sess.spectatorClient == clientNum ) {
                        StopFollowing( &g_entities[i] );
                }
        }

        // send effect if they were completely connected
        if ( ent->client->pers.connected == CON_CONNECTED
                && ent->client->sess.sessionTeam != TEAM_SPECTATOR ) {
                tent = G_TempEntity( ent->client->ps.origin, EV_PLAYER_TELEPORT_OUT );
                tent->s.clientNum = ent->s.clientNum;

                // They don't get to take powerups with them!
                // Especially important for stuff like CTF flags
                TossClientItems( ent );
#ifdef MISSIONPACK
                TossClientPersistantPowerups( ent );
                if( g_gametype.integer == GT_BOMB ) {
                        TossClientCubes( ent );
                }
#endif

        }

        G_LogPrintf( "ClientDisconnect: %i\n", clientNum );

        // if we are playing in tourney mode and losing, give a win to the other player
        if ( (g_gametype.integer == GT_ASN )
                && !level.intermissiontime
                && !level.warmupTime && level.sortedClients[1] == clientNum ) {
                level.clients[ level.sortedClients[0] ].sess.wins++;
                ClientUserinfoChanged( level.sortedClients[0] );
        }

        if( g_gametype.integer == GT_ASN &&
                ent->client->sess.sessionTeam == TEAM_FREE &&
                level.intermissiontime ) {

                trap_SendConsoleCommand( EXEC_APPEND, "map_restart 0\n" );
                level.restarted = qtrue;
                level.changemap = NULL;
                level.intermissiontime = 0;
        }

        trap_UnlinkEntity (ent);
        ent->s.modelindex = 0;
        ent->inuse = qfalse;
        ent->classname = "disconnected";
        ent->client->pers.connected = CON_DISCONNECTED;
        ent->client->ps.persistant[PERS_TEAM] = TEAM_FREE;
        ent->client->sess.sessionTeam = TEAM_FREE;

        trap_SetConfigstring( CS_PLAYERS + clientNum, "");

        CalculateRanks();

        if ( ent->r.svFlags & SVF_BOT ) {
                BotAIShutdownClient( clientNum, qfalse );
        }
}



#define rndnum(y,z) ((random()*((z)-((y)+1)))+(y))

qboolean randomPlayers[MAX_CLIENTS];

gentity_t *G_RandomPlayer( int ignoreClientNum, team_t team ) {
    int         i;
    int currvip = -1;

    // look for players which have a clientnumber bigger than the ignoreclientnum
    for ( i = ignoreClientNum+1 ; i < level.maxclients ; i++ ) {

        if ( level.clients[i].pers.connected != CON_CONNECTED ) continue;
        if ( level.clients[i].sess.sessionTeam != team ) continue;
        if ( level.clients[i].sess.waiting ) continue;
//        if ( level.clients[i].pers.lockedPlayer > 0 ) continue;

        currvip = i;

        break;

    }

    // look for players which have a clientnumber smaller than the ignoreclientnum
    if ( currvip < 0 ) for ( i = 0 ; i <= ignoreClientNum ; i++ ) {
            if ( level.clients[i].pers.connected != CON_CONNECTED ) continue;
            if ( level.clients[i].sess.sessionTeam != team ) continue;
            if ( level.clients[i].sess.waiting ) continue;
  //          if ( level.clients[i].pers.lockedPlayer > 0 ) continue;

            currvip = i;

            break;
        }

    // return our new VIP if we have it
    if ( currvip >= 0 ) return &g_entities[ level.clients[currvip].ps.clientNum ];

    // if we have not found a new VIP, return the old one
    if (ignoreClientNum >= 0 && ignoreClientNum < level.maxclients)
        return &g_entities[ level.clients[ignoreClientNum].ps.clientNum ];
    else
        return NULL;
}

//gentity_t *G_RandomPlayer( int ignoreClientNum, team_t team );

static int lastbmbplayer = -1;

void G_GiveBombToTeam( team_t team ) {
    gentity_t *bmbplayer;

//    if ( g_overrideGoals.integer )
//        return qtrue;

    if ( team != TEAM_RED ) {
        G_Error("G_GiveBombsToTeam. Unallowed team.\n");
    }

    if (level.bombs[team] <= 0) return;// qtrue;

    bmbplayer = G_RandomPlayer(lastbmbplayer, team);

    if ( bmbplayer) {
        // give the player the bomb
        BG_PackWeapon( WP_BOMB, bmbplayer->client->ps.stats );
        // notify everyone via radio message about the bomb
        //NS_BotRadioMsg( bmbplayer, "bgot" );
        // remember this player
        lastbmbplayer = bmbplayer->s.clientNum;

        G_LogPrintf("[%i] \"%s\" has the bomb\n",
                    bmbplayer->s.clientNum, bmbplayer->client->pers.netname);
    }// else {
     //   return qfalse;
   // }

  //  return qtrue;
}

