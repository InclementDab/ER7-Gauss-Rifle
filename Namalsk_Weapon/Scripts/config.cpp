class CfgPatches
{
	class Namalsk_Weapon_Scripts
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Weapons_Firearms","DZ_Weapons_Ammunition","DZ_Weapons_Magazines"};
		magazines[] = {"A2GaussMk2_Magazine"};
		ammo[] = {};
	};
};

class CfgMods
{
	class Namalsk_Weapon
	{
		name = "ER7 Scripts";
		dir = "Namalsk_Weapon";
		credits = "InclementDab & ChrisPBacon";
		author = "InclementDab & ChrisPBacon";
		type = "mod";
		dependencies[] =
		{
			"World"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[] = 
				{
					"Namalsk_Weapon/Scripts/4_World"
				};
			};
		};
	};
};