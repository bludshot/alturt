Alturt alpha 0.01

(Alternate Urt Source Code Project)
by BludShoT and Xamis

http://sourceforge.net/projects/alturt/


ReadMe Contents:
* PURPOSE
* LEGAL STUFF
* INSTALLATION INSTRUCTIONS
* REPORTING BUGS
* KNOWN ISSUES
* VERSION HISTORY
* CREDITS AND THANKS
* PERMISSIONS AND OPEN SOURCE



================================
PURPOSE

The Alternate Urt Source Code Project attempts to implement an opensource version of Urt. So that mod authors can create mods under ioUrbanTerror. This software is in no way associated with Frozen Sand/Silicon Ice Development.

While it does run as a mod, Alturt is not intended to be an end user mod, but rather open source mod code that people can use to make actual mods for end users to play. Furthermore this is only an early alpha version that is only intended for testing, not making other mods yet.



================================
LEGAL STUFF

The makers of Alturt accept no responsibility for any damage or 
injuries resulting from use of this software. You download and install 
this software at your own risk.

If you install it wrong and mess up your stuff, that's your fault.

For those interested in using Alturt as a base for making more mods,
please read the PERMISSIONS AND OPEN SOURCE section.

Alturt is released under the AGPLv3. See aglp.txt for license.


================================
INSTALLATION INSTRUCTIONS

Unzip alturt_alpha001.zip in your ioUrbanTerror *engine* folder, NOT in your q3ut4 mod folder! So if your ioUrbanTerror is in C:\games\urbanterror\, then your q3ut4 mod folder is at C:\games\urbanterror\q3ut4\ and you will unzip alturt_alpha001.zip to C:\games\urbanterror\

You can make a shortcut on your desktop to ioUrbanTerror.exe and then alter its target to say ioUrbanTerror.exe +set fs_game alturt (if you don't run it with +set fs_game alturt then you'll just be running normal urt, not Alturt) 

When you join an Alturt server the game will automatically load the Alturt mod (assuming you have it installed) even if you only launched normal vanilla Urban Terror.

Alturt is intended for use with ioUrbanTerror and therefore does not work properly with Quake 3.


================================
REPORTING BUGS

Please report any bugs you find to bludshot@gmail.com


================================
KNOWN ISSUES

There are many known issues. This is an early alpha, intended primarily for testing to expose bugs and to gather information from testers about which features are most important to be worked on next.


================================
VERSION HISTORY

Alpha 0.01

First verion of Alturt.
Many features have been added to the original ioq3 code, including code for:
- animating weapons
- toggling weapons, weapon dropping, weapon/gear system
- sprinting
- health bar
- stamina
- powersliding
- walljumping (early WIP)
- speedometer
- HUD ammo count and weapon select
- reloading and ammo count system
- weapon firing modes
- spawn points (incomplete)
- doors (rotating doors)
- race/skin/model system
- ladders
- breakable glass
- smoke nades (currently disabled)
- HE nades

Also, new multi-colored player and hand skins for non-team gametypes (FFA)


================================
CREDITS AND THANKS

BludShoT for the initial code getting the q3 mod code to run as a mod under UrT.

Xamis for the initial features he coded and brought to Alturt.

BludShoT and Xamis for combining that code, and then continuing to work on adding
features.

Open Arena (and Q3Min, but mostly Open Arena) for various graphics and sounds 
to replace missing Q3A/TA stuff.

Alturt may (and in some cases does) contain some code (either copied from or just our own new code that we made but learned how to do by looking at code) from: Tremulous, Navy Seals: Covert Ops, Smokin Guns, Open Arena, and Q3 modding tutorial web pages. [We sometimes document it, but other time it's just bits and pieces and it becomes hard to remember or keep track of, but suffice it to say: Thank you for your open source code!]


Thanks to:
- Frozen Sand for Urban Terror, since obviously a mod for Urban Terror
wouldn't be too useful without Urban Terror.

- Id Software for Quake 3 and Team Arena

- ioquake3

- The guys at quake3world.com programming forums, like misantropia and AnthonyJ

- all the folks who ever posted a Q3 mod coding tutorial online, including: Code 3 Arena, Wilka, jazz, QuakeStyle, inolen, and everyone else. (We try to credit the tuts, but sometimes by the time we've figured out and applied the knowledge we got from a tut here and there it's hard to remember where we learned it or used it.)

- Other open source mods and games such as Tremulous, Smokin Guns, Navy Seals: Covert Ops, Open Arena, and Warsow that we sometimes learn things from

- the people who made Q3 Model Tool, Quake Video Maker, GTK Radiant

- Teknix for server donation

- God

- anybody I forgot to thank


================================
PERMISSIONS AND OPEN SOURCE

You MAY make new mods based on this mod. Everything in this mod*, including the source code, graphics and sounds, are free and open source. (*But remember, this mod does NOT include any of the files in the Urban Terror game that Alturt happens to reference or display when you play it. Urban Terror is copyright Frozen Sand.) Alturt is released under AGPLv3. Any mods you make from it are subject to the AGPLv3 license and so must also in turn be open source, even if they are server-side only and only run on your own server! Anything you do to the code must be shared with the world.

The AGPLv3 license applies to everything in Alturt, including all of the assets and text files, configs, shaders, scripts and art and sound assets.

To comply with AGPLv3, we have added the command "sourceurl", which any client can type into their console and the server will echo to them the url where they can find the source code to download. The sourceurl command is also bound to the P key by default.

The source code for Alturt can be downloaded here: http://sourceforge.net/projects/alturt/  The layered "source files" for some of the skins are available there too. The rest of Alturt (in the normal playable download) contains the rest of the graphics, and sounds, many of which are also "source" files that you may use or alter for your mod.


If you use Alturt code in your mod or game, you must follow these rules:

- Obey the AGPLv3 License which Alturt is distributed under. This covers all of the files in Alturt, not just the code. So if you use any of the graphics or shaders or any other file to edit and redistribute in your mod or game then those files and your changes or additions are open source and can be used freely by others. The AGPLv3 also covers server-side only mods.

- to comply with AGPLv3, you must update the "sourceurl" command so that it echos a download link to your new source code (or you may satisfy the requirement I am referring to in some other way)

- Do not release altered client-server versions of the mod (with new skins or other assets) if you haven't A: also compiled and included your own qvm's, replacing the ones that come with Alturt, and B: altered the constants GAME_VERSION (in bg_public.h) and GAMEVERSION (in g_local.h).  In other words, you are free to make your own real mod from this mod, but you are not free to just screw up this mod.

- If you make a mod, your mod must reside in its own fs_game folder, different than /alturt/ so as not to conflict with Alturt.



Now this is not an Alturt rule, but just a reminder to potential modders:

- If you are using Alturt to make a mod that will run under the game Urban Terror, please respect Urban Terror's license(s) and copyright(s). For example, you cannot just take their models or skin tga files and edit them and redistribute them with your mod. Remember that when run under Urban Terror, Alturt's source code merely references some Urban Terror asset files, just like how Rocket Arena 3 references Quake 3 Arena files. But that doesn't make those assets part of Rocket Arena 3, nor does it do that in the case of Alturt. Alturt is completely open source, but Urban Terror is not. Don't confuse the two when making your mod.



*** If you are going to make a mod from Alturt, please let us know, we'd love to hear about it *** 
