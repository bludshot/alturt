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

#define INVENTORY_NONE				0
//armor
#define INVENTORY_ARMOR				1
//weapons
#define INVENTORY_KNIFE			4
#define INVENTORY_BERETTA			5
#define INVENTORY_DEAGLE		6
#define INVENTORY_SPAS          	7
#define INVENTORY_UMP45         	8
#define INVENTORY_MP5K			9
#define INVENTORY_G36			10
#define INVENTORY_LR300			11
#define INVENTORY_M4			12
#define INVENTORY_AK103		13
#define INVENTORY_PSG1			14
#define INVENTORY_SR8		15
#define INVENTORY_HE			16
#define INVENTORY_HK69                    17
#define INVENTORY_SMOKE			18
#define INVENTORY_BULLETS			19
#define INVENTORY_GRENADES			20
#define INVENTORY_SHELLS				21


//powerups
#define INVENTORY_HEALTH			22
#define INVENTORY_SILENCER		23
#define INVENTORY_MEDKIT			24
#define INVENTORY_NVG			25
#define INVENTORY_LASERSIGHT			26

#define INVENTORY_REDFLAG			45
#define INVENTORY_BLUEFLAG			46
#define INVENTORY_NEUTRALFLAG		47
#define INVENTORY_REDCUBE			48
#define INVENTORY_BLUECUBE			49
//enemy stuff
#define ENEMY_HORIZONTAL_DIST		200
#define ENEMY_HEIGHT				201
#define NUM_VISIBLE_ENEMIES			202
#define NUM_VISIBLE_TEAMMATES		203

// if running the mission pack
#ifdef MISSIONPACK

//#error "running mission pack"

#endif

//item numbers (make sure they are in sync with bg_itemlist in bg_misc.c)
#define MODELINDEX_ARMORSHARD		1
#define MODELINDEX_ARMORCOMBAT		2
#define MODELINDEX_ARMORBODY		3
#define MODELINDEX_HEALTHSMALL		4
#define MODELINDEX_HEALTH			5
#define MODELINDEX_HEALTHLARGE		6
#define MODELINDEX_HEALTHMEGA		7

#define MODELINDEX_G36			8
#define MODELINDEX_SHOTGUN			9
#define MODELINDEX_BERETTA		10
#define MODELINDEX_GRENADEHE    	11
#define MODELINDEX_KNIFE        	12
#define MODELINDEX_AK103		13
#define MODELINDEX_MP5K			14
#define MODELINDEX_DEAGLE		15
#define MODELINDEX_GRENADE_SMOKE			16
#define MODELINDEX_LR300	17
#define MODELINDEX_UMP45			18
#define MODELINDEX_HK69			19
#define MODELINDEX_PSG1			20
#define MODELINDEX_SR8			21
#define MODELINDEX_NEGEV	22
#define MODELINDEX_M4			23


#define MODELINDEX_SHELLS			24
#define MODELINDEX_BULLETS			25
#define MODELINDEX_GRENADES		26
#define MODELINDEX_MEDKIT			27
#define MODELINDEX_VEST				28
#define MODELINDEX_PW_HELMET        	29
#define MODELINDEX_PW_LASERSIGHT		30
#define MODELINDEX_PW_SILENCER  		31
#define MODELINDEX_PW_AMMO      		32
#define MODELINDEX_PW_NVG			33

#define MODELINDEX_REDFLAG			34
#define MODELINDEX_BLUEFLAG			35


//
#define WEAPONINDEX_KNIFE			1
#define WEAPONINDEX_BERETTA			2
#define WEAPONINDEX_DEAGLE				3
#define WEAPONINDEX_MP5K	4
#define WEAPONINDEX_SPAS		5
#define WEAPONINDEX_UMP45			6
#define WEAPONINDEX_M4				7
#define WEAPONINDEX_LR300			8
#define WEAPONINDEX_G36				9
#define WEAPONINDEX_AK103		10
#define WEAPONINDEX_HK69				11
#define WEAPONINDEX_NEGEV		12
#define WEAPONINDEX_PSG1			13
#define WEAPONINDEX_SR8                        14
#define WEAPONINDEX_HE                        15
//#define WEAPONINDEX_SMOKE                        16
