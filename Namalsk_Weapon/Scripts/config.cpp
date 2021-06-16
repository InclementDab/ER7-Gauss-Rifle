class CfgPatches
{
	class Namalsk_Weapon_Scripts
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Scripts", "DF_Scripts"};
		magazines[] = {};
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
			"World",
			"Mission"
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
			class missionScriptModule
			{
				files[] =
				{
					"Namalsk_Weapon/Scripts/5_Mission"
				};
			};
		};
	};
};