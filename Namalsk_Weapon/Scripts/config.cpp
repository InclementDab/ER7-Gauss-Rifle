class CfgPatches
{
	class Namalsk_Weapon_Scripts
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Weapons_Firearms","DZ_Weapons_Ammunition","DZ_Weapons_Magazines","JM_CF_Scripts","Namalsk_Weapon_GaussMk2"};
		magazines[] = {"A2GaussMk2_Magazine"};
		ammo[] = {};
	};
};

class CfgMods
{
	class Namalsk_Weapon
	{
		name = "ER7 Weapon";
		dir = "Namalsk_Weapon";
		credits = "InclementDab & ChrisPBacon";
		author = "InclementDab & ChrisPBacon";
		type = "mod";
		dependencies[] =
		{
			"Game",
			"World"
		};
		class defs
		{
			class imageSets
			{
				files[] =
				{
					"Namalsk_Weapon/GaussMk2/GUI/imagesets/gauss_ghost.imageset"
				};
			};
			class gameScriptModule
			{
				value="";
				files[] = 
				{
					"Namalsk_Weapon/Scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				files[] =
				{
					"Namalsk_Weapon/Scripts/4_World"
				};
			};
		};
	};
};