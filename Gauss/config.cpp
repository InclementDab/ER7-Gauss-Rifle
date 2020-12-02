class CfgPatches
{
	class ER7_Gauss
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Weapons_Firearms","DZ_Weapons_Ammunition","DZ_Weapons_Magazines"};
		magazines[] = {"ER7_Gauss_Magazine"};
		ammo[] = {};
	};
};
class Mode_Safe;
class Mode_SemiAuto;
class cfgWeapons
{
	class FAL;
	class ER7_Gauss: FAL
	{
		scope = 2;
		absorbency = 0.1;
		displayName = "EFW ER7 MK2";
		descriptionShort = "Alien gun go pew pew.";
		model = "\Namalsk_Weapon\Gauss\C3_Gauss.p3d";
		magazines[] = {"ER7_Gauss_Magazine"};
		itemSize[] = {8,3};
		repairableWithKits[] = {5,1};
		repairCosts[] = {30,25};
		PPDOFProperties[] = {0,0,0,0,0,0};
		dexterity = 3.0;
		discreteDistance[] = {25,50,100};
		chamberSize = 1;
		attachments[] = {"weaponOptics","weaponOpticsHunting","RailgunBattery"};
		chamberableFrom[] = {"Ammo_ER7RFW"};
		reloadAction = "ReloadM4";
		modes[] = {"SemiAuto"};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[] = {"ER7_Shot_SoundSet","FNFAL_Tail_SoundSet","FNFAL_InteriorTail_SoundSet"};
			reloadTime = 0.425;
			recoil = "recoil_AKM";
			recoilProne = "recoil_AKM_prone";
			dispersion = 0.00075;
			magazineSlot = "magazine";
		};
		class Particles
		{
			class OnFire
			{
				class SmokeCloud
				{
					overrideParticle = "weapon_shot_winded_smoke";
				};
				class MuzzleFlash
				{
					overrideParticle = "weapon_shot_ump45_01";
					ignoreIfSuppressed = 1;
					illuminateWorld = 1;
				};
				class ChamberSmoke
				{
					overrideParticle = "weapon_shot_chamber_smoke";
					overridePoint = "Nabojnicestart";
					overrideDirectionPoint = "Nabojniceend";
				};
				class ChamberSmokeRaise
				{
					overrideParticle = "weapon_shot_chamber_smoke_raise";
					overridePoint = "Nabojnicestart";
				};
			};
			class OnOverheating
			{
				maxOverheatingValue = 30;
				shotsToStartOverheating = 10;
				overheatingDecayInterval = 1;
				class SmokingBarrel
				{
					overrideParticle = "smoking_barrel_small";
					positionOffset[] = {0.1,0,0};
					onlyWithinHealthLabel[] = {0,1};
				};
				class SmokingBarrelDamaged
				{
					overrideParticle = "smoking_barrel";
					positionOffset[] = {0.1,0,0};
					onlyWithinHealthLabel[] = {2,4};
				};
				class SmokingBarrelBadlyDamaged
				{
					overridePoint = "Nabojnicestart";
					overrideParticle = "smoking_barrel_small";
					onlyWithinHealthLabel[] = {3,4};
				};
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 500;
					healthLevels[] = {{1,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0,{}}};
				};
			};
		};
	};
};
class CfgMagazines
{
	class Ammunition_Base;
	class Mag_AKM_30Rnd;
	class ER7_Gauss_Magazine: Mag_AKM_30Rnd
	{
		scope = 2;
		displayName = "EFW ER7 Magazine";
		descriptionShort = "";
		model = "\Namalsk_Weapon\Gauss\C3_Gauss_Magazine.p3d";
		weight = 230;
		itemSize[] = {2,2};
		count = 4;
		ammo = "Bullet_ER7RFW";
		ammoItems[] = {"Ammo_ER7RFW"};
		isMeleeWeapon = 0;
		tracersEvery = 1;
	};
};


class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyC3_Gauss_Magazine: ProxyAttachment
	{
		scope = 2;
		inventorySlot = "magazine";
		model = "\Namalsk_Weapon\Gauss\C3_Gauss_Magazine.p3d";
	};
};



class HouseNoDestruct;
class CfgVehicles 
{
	class vfx_gauss_thunderboltnorm: HouseNoDestruct
    {
        model = "\dz\data\data\blesk1.p3d";
    };
    class vfx_gauss_thunderboltheavy: HouseNoDestruct
    {
        model = "\dz\data\data\blesk2.p3d";
    };
};


class cfgSlots
{
	class Slot_RailgunBattery
	{
		name = "RailgunBattery";
		displayName = "RailgunBattery";
		ghostIcon = "Battery9V";
	};
};