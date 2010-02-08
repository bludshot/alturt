/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
// cg_info.c -- display information while data is being loading

#include "cg_local.h"
#include "../ui/ui_shared.h"
#define MAX_LOADING_PLAYER_ICONS	16
#define MAX_LOADING_ITEM_ICONS		26

static int			loadingPlayerIconCount;
static int			loadingItemIconCount;
static qhandle_t	loadingPlayerIcons[MAX_LOADING_PLAYER_ICONS];
static qhandle_t	loadingItemIcons[MAX_LOADING_ITEM_ICONS];



/*
======================
CG_LoadingBarInit
======================
*/
void CG_LoadBarInit( void )
{
  cg.loadingbarState = 0;
  cg.loadingbarMax = 0;
}
/*
======================
CG_LoadingBarUpdate
======================
*/

void CG_LoadingBarUpdate( int amount )
{
  cg.loadingbarState += amount;
  trap_UpdateScreen();
}
/*
======================
CG_LoadingBarSetMax
======================
*/
void CG_LoadingBarSetMax( int maximum )
{
  cg.loadingbarMax = maximum;
}
/*
======================
CG_DrawLoadingBar
======================
*/
void CG_DrawLoadingBar( int x, int y, int w, int h )
{
  float real_width = 0;
  vec4_t color;
  real_width = (float)( (float)cg.loadingbarState / (float)cg.loadingbarMax );

  color[0] = 0.6;
  color[1] = 0.6;
  color[2] = 1.0;
  color[3] = 0.3f;

  if ( real_width > 1.0f )
    real_width = 1.0f;

  real_width = real_width * (float)w;
  CG_FillRect( x, y, real_width, h, color );

}



/*
===================
CG_DrawLoadingIcons
===================
*/
/*
static void CG_DrawLoadingIcons( void ) {
	int		n;
	int		x, y;

	for( n = 0; n < loadingPlayerIconCount; n++ ) {
		x = 16 + n * 78;
		y = 324-40;
		CG_DrawPic( x, y, 64, 64, loadingPlayerIcons[n] );
	}

	for( n = 0; n < loadingItemIconCount; n++ ) {
		y = 400-40;
		if( n >= 13 ) {
			y += 40;
		}
		x = 16 + n % 13 * 48;
		CG_DrawPic( x, y, 32, 32, loadingItemIcons[n] );
	}
}
*/

/*
======================
CG_LoadingString

======================
*/
void CG_LoadingString( const char *s ) {
	Q_strncpyz( cg.infoScreenText, s, sizeof( cg.infoScreenText ) );

	trap_UpdateScreen();
}

/*
===================
CG_LoadingItem
===================
*/
void CG_LoadingItem( int itemNum ) {
	gitem_t		*item;

	item = &bg_itemlist[itemNum];

	if ( item->icon && loadingItemIconCount < MAX_LOADING_ITEM_ICONS ) {
		loadingItemIcons[loadingItemIconCount++] = trap_R_RegisterShaderNoMip( item->icon );
	}

	CG_LoadingString( item->pickup_name );
}

/*
===================
CG_LoadingClient
===================
*/
void CG_LoadingClient( int clientNum ) {
	const char		*info;
	char			*skin;
	char			personality[MAX_QPATH];
	char			model[MAX_QPATH];
	char			iconName[MAX_QPATH];
	int				racered; //blud
	int				raceblue; //blud
	int				race; //blud
	int				team; //blud
	const char		*v; //blud
	char			skinToUseForIcon[MAX_QPATH]; //blud

	info = CG_ConfigString( CS_PLAYERS + clientNum );

	if ( loadingPlayerIconCount < MAX_LOADING_PLAYER_ICONS ) {
		Q_strncpyz( model, Info_ValueForKey( info, "model" ), sizeof( model ) );
		skin = Q_strrchr( model, '/' );
		if ( skin ) {
			*skin++ = '\0';
		} else {
			skin = "default";
		}

		//blud set the RIGHT skin and model here
		//The old code is based on the old model/skin paradigm so I need to update it
		//for the new racered raceblue paradigm

		//blud note: later I should probably combine this code with the code in CG_NewClientInfo
		//into a new function and then just call that function here (as well as calling it from
		//CG_NewClientInfo)

		//we now have the correct model and skin for non-team gts.
		//so check if it's a team gt to correct them

		//get info from info (configstring)
		//team
		v = Info_ValueForKey( info, "t" );
		team = atoi( v );
		// racered blud
		v = Info_ValueForKey( info, "rr" );
		racered = atoi( v );
		// raceblue blud
		v = Info_ValueForKey( info, "rb" );
		raceblue = atoi( v );

		if ( cgs.gametype >= GT_TEAM )
		{
			if ( team == TEAM_BLUE )
			{
				race = raceblue;
			}
			else //team is red
			{
				race = racered;
			}


			// set model (just for getting the right icon)
			switch( race )
			{
				case 0:
				case 1:		Q_strncpyz( model, "athena", sizeof( model ) );
							break;
				case 2:
				case 3:		Q_strncpyz( model, "orion", sizeof( model ) );
							break;
				default:	Q_strncpyz( model, "orion", sizeof( model ) );
							break;
			}

			// determine the skin (just for getting the right icon)
			if ( team == TEAM_BLUE )
			{
				if ( race == 0 || race == 2 )
				{
					Q_strncpyz( skinToUseForIcon, "blue", sizeof( skinToUseForIcon ) );
					Q_strncpyz( skinToUseForIcon, "blue", sizeof( skinToUseForIcon ) );
				}
				else if ( race == 1 || race == 3 )
				{
					Q_strncpyz( skinToUseForIcon, "blue2", sizeof( skinToUseForIcon ) );
					Q_strncpyz( skinToUseForIcon, "blue2", sizeof( skinToUseForIcon ) );
				}
				else //default
				{
					Q_strncpyz( skinToUseForIcon, "blue", sizeof( skinToUseForIcon ) );
					Q_strncpyz( skinToUseForIcon, "blue", sizeof( skinToUseForIcon ) );
				}
			}
			else //team is red
			{
				if ( race == 0 || race == 2 )
				{
					Q_strncpyz( skinToUseForIcon, "red", sizeof( skinToUseForIcon ) );
					Q_strncpyz( skinToUseForIcon, "red", sizeof( skinToUseForIcon ) );
				}
				else if ( race == 1 || race == 3 )
				{
					Q_strncpyz( skinToUseForIcon, "red2", sizeof( skinToUseForIcon ) );
					Q_strncpyz( skinToUseForIcon, "red2", sizeof( skinToUseForIcon ) );
				}
				else //default
				{
					Q_strncpyz( skinToUseForIcon, "red", sizeof( skinToUseForIcon ) );
					Q_strncpyz( skinToUseForIcon, "red", sizeof( skinToUseForIcon ) );
				}
			}
		}


		Com_sprintf( iconName, MAX_QPATH, "models/players/%s/icon_%s.tga", model, skinToUseForIcon );

		loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip( iconName );
		if ( !loadingPlayerIcons[loadingPlayerIconCount] ) {
			//Com_sprintf( iconName, MAX_QPATH, "models/players/characters/%s/icon_%s.tga", model, skin ); //blud was
			Com_sprintf( iconName, MAX_QPATH, "models/players/%s/icon_%s.tga", model, skinToUseForIcon ); //blud fixed
			loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip( iconName );
		}
		if ( !loadingPlayerIcons[loadingPlayerIconCount] ) {
			Com_sprintf( iconName, MAX_QPATH, "models/players/%s/icon_%s.tga", DEFAULT_MODEL, "default" );
			loadingPlayerIcons[loadingPlayerIconCount] = trap_R_RegisterShaderNoMip( iconName );
		}
		if ( loadingPlayerIcons[loadingPlayerIconCount] ) {
			loadingPlayerIconCount++;
		}
	}

	Q_strncpyz( personality, Info_ValueForKey( info, "n" ), sizeof(personality) );
	Q_CleanStr( personality );

	if( cgs.gametype == GT_SINGLE_PLAYER ) {
		trap_S_RegisterSound( va( "sound/player/announce/%s.wav", personality ), qtrue );
	}

	CG_LoadingString( personality );
}


/*
====================
CG_DrawInformation

Draw all the status / pacifier stuff during level loading
====================
*/
void CG_DrawInformation( void ) {
	const char	*s;
	const char	*info;
	const char	*sysInfo;
	int			y;
	int			value;
	qhandle_t	levelshot;
	qhandle_t	detail;
	char		buf[1024];

	info = CG_ConfigString( CS_SERVERINFO );
	sysInfo = CG_ConfigString( CS_SYSTEMINFO );

	s = Info_ValueForKey( info, "mapname" );
	levelshot = trap_R_RegisterShaderNoMip( va( "levelshots/%s.tga", s ) );
	if ( !levelshot ) {
		levelshot = trap_R_RegisterShaderNoMip( "menu/art/unknownmap" );
	}
	trap_R_SetColor( NULL );
	CG_DrawPic( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, levelshot );

        detail = trap_R_RegisterShader( "levelShotDetail" );
        CG_DrawPic( 76, 96, 241, 124, detail );
        CG_DrawLoadingBar( 0, 134, SCREEN_WIDTH, 210 );
	// blend a detail texture over it
//blud commenting this out: It makes this ugly weird semi-transparent texture go on top of levelshot
//	detail = trap_R_RegisterShader( "levelShotDetail" );
//	trap_R_DrawStretchPic( 0, 0, cgs.glconfig.vidWidth, cgs.glconfig.vidHeight, 0, 0, 2.5, 2, detail );

	// draw the icons of things as they are loaded
	//CG_DrawLoadingIcons();

	// the first 150 rows are reserved for the client connection
	// screen to write into





	if ( cg.infoScreenText[0] ) {
          CG_DrawStringExt( 12, 140, va("Loading... %s", cg.infoScreenText),
                            colorWhite, qtrue, qtrue, 10, 16, 0 );


		//UI_DrawProportionalString( 80, 128-32, va("Loading... %s", cg.infoScreenText),
                //                           UI_LEFT|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
	} else {


          CG_DrawStringExt( 12, 140, "Awaiting snapshot...",
                            colorWhite, qtrue, qtrue, 10, 16, 0 );
		//UI_DrawProportionalString( 320, 128-32, "Awaiting snapshot...",
		//	UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
	}

	// draw info string information

	y = 360;

	// don't print server lines if playing a local game
	trap_Cvar_VariableStringBuffer( "sv_running", buf, sizeof( buf ) );
	if ( !atoi( buf ) ) {
		// server hostname
		Q_strncpyz(buf, Info_ValueForKey( info, "sv_hostname" ), 1024);
		Q_CleanStr(buf);
                CG_DrawStringExt( 12, y, buf,
                                  colorWhite, qtrue, qtrue, 10, 16, 0 );
		//UI_DrawProportionalString( 12, y, buf,
		//	UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
		y += PROP_HEIGHT;

		// pure server
		s = Info_ValueForKey( sysInfo, "sv_pure" );
		if ( s[0] == '1' ) {
                  CG_DrawStringExt( 12, y,"Pure Server",
                                    colorWhite, qtrue, qtrue, 10, 16, 0 );
		//	UI_DrawProportionalString( 12, y, "Pure Server",
		//		UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
			y += PROP_HEIGHT;
		}

		// server-specific message of the day
		s = CG_ConfigString( CS_MOTD );
		if ( s[0] ) {
                  CG_DrawStringExt( 12, y, s,
                                    colorWhite, qtrue, qtrue, 10, 16, 0 );
			//UI_DrawProportionalString( 12, y, s,
			//	UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
			y += PROP_HEIGHT;
		}

		// some extra space after hostname and motd
		y += 10;
	}

	// map-specific message (long map name)
	s = CG_ConfigString( CS_MESSAGE );
	if ( s[0] ) {
          CG_DrawStringExt( 12, y,s,
                            colorWhite, qtrue, qtrue, 10, 16, 0 );
		//UI_DrawProportionalString( 12, y, s,
		//	UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
		y += PROP_HEIGHT;
	}

	// cheats warning
	s = Info_ValueForKey( sysInfo, "sv_cheats" );
	if ( s[0] == '1' ) {
          CG_DrawStringExt( 12, y,"CHEATS ARE ENABLED",
                            colorWhite, qtrue, qtrue, 10, 16, 0 );
		//UI_DrawProportionalString( 12, y, "CHEATS ARE ENABLED",
		//	UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
		y += PROP_HEIGHT;
	}

	// game type
	switch ( cgs.gametype ) {
	case GT_FFA:
		s = "Free For All";
		break;
	case GT_SINGLE_PLAYER:
		s = "Single Player";
		break;
	case GT_ASN:
		s = "Follow The Leader";
		break;
	case GT_TEAM:
		s = "Team Deathmatch";
		break;
          case GT_TEAMSV:
            s = "Team Survivor";
            break;
	case GT_CTF:
		s = "Capture The Flag";
		break;
	case GT_BOMB:
		s = "BOMB";
		break;
	case GT_CAH:
		s = "Capture and Hold";
		break;
	default:
		s = "Unknown Gametype";
		break;
	}
        CG_DrawStringExt( 12, y,s,
                          colorWhite, qtrue, qtrue, 10, 16, 0 );
	//UI_DrawProportionalString( 12, y, s,
//		UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
	y += PROP_HEIGHT;

	value = atoi( Info_ValueForKey( info, "timelimit" ) );
	if ( value ) {
          CG_DrawStringExt( 12, y,va( "timelimit %i", value ),
                            colorWhite, qtrue, qtrue, 10, 16, 0 );
	//	UI_DrawProportionalString( 12, y, va( "timelimit %i", value ),
	//		UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
		y += PROP_HEIGHT;
	}

	if (cgs.gametype < GT_CTF ) {
		value = atoi( Info_ValueForKey( info, "fraglimit" ) );
		if ( value ) {
                  CG_DrawStringExt( 12, y, va( "fraglimit %i", value ),
                                    colorWhite, qtrue, qtrue, 10, 16, 0 );
			//UI_DrawProportionalString( 12, y, va( "fraglimit %i", value ),
			//	UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
			y += PROP_HEIGHT;
		}
	}

	if (cgs.gametype >= GT_TEAM) {
		value = atoi( Info_ValueForKey( info, "capturelimit" ) );
		if ( value ) {
                  CG_DrawStringExt( 12, y, va( "capturelimit %i", value ),
                                    colorWhite, qtrue, qtrue, 10, 16, 0 );
			//UI_DrawProportionalString( 12, y, va( "capturelimit %i", value ),
			//	UI_CENTER|UI_SMALLFONT|UI_DROPSHADOW, colorWhite );
			y += PROP_HEIGHT;
		}
	}
}

