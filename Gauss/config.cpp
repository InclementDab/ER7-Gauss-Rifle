class CfgPatches
{
	class CS_Gauss
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Weapons_Firearms","DZ_Weapons_Ammunition","DZ_Weapons_Magazines"};
		magazines[] = {"C3_Gauss_Magazine"};
		ammo[] = {};
	};
};
class Mode_Safe;
class Mode_FullAuto;
class cfgWeapons
{
	class FAL;
	class CS_Gauss: FAL
	{
		scope = 2;
		absorbency = 0.1;
		displayName = "Thing";
		descriptionShort = "";
		model = "\Namalsk_Weapon\Gauss\C3_Gauss.p3d";
		magazines[] = {"C3_Gauss_Magazine"};
		itemSize[] = {8,3};
		repairableWithKits[] = {5,1};
		repairCosts[] = {30,25};
		PPDOFProperties[] = {0,0,0,0,0,0};
		dexterity = 3.0;
		discreteDistance[] = {25,50,100};
		chamberSize = 1;
		chamberableFrom[] = {"Ammo_12gaPellets","Ammo_12gaSlug","Ammo_12gaRubberSlug","Ammo_12gaBeanbag","Ammo_12gaPellets_tracer","Ammo_12gaNeedles","Ammo_new_12gaBuckshot5","Ammo_new_12gaExpressBuckshot6","Ammo_new_12gaBuckshot7","Ammo_new_12gaMagnumBuckshot8","Ammo_new_12gaRip","Ammo_new_12gaAP20","Ammo_new_12ga2Sabot","Ammo_new_12gaFtxCustomLIte","Ammo_new_12gaGrizzly40","Ammo_new_12gaPoleva3","Ammo_new_12gaPoleva6","Ammo_new_12ga50Bmg","Ammo_new_12gaLead","Ammo_new_12gaFlchetteS","Ammo_new_12gaSuperFormance","Ammo_new_12gaCopperSabotPremier","Ammo_new_12gaImbalanced","Ammo_new_12gaImbalancedSlug","Mag_12gaSnaploader_2Rnd"};
		attachments[] = {};
		reloadAction = "ReloadM4";
		modes[] = {"FullAuto"};
		class FullAuto: Mode_FullAuto
		{
			soundSetShot[] = {"ER7_Shot_SoundSet","Mosin_Tail_SoundSet","Mosin_InteriorTail_SoundSet"};
			reloadTime = 0.12;
			recoil = "recoil_m4";
			recoilProne = "recoil_m4_prone";
			dispersion = 0.0015;
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
	class C3_Gauss_Magazine: Mag_AKM_30Rnd
	{
		scope = 2;
		displayName = "AA-12 32Rnd Drum Magazine";
		descriptionShort = "";
		model = "\Namalsk_Weapon\Gauss\C3_Gauss_Magazine.p3d";
		weight = 230;
		itemSize[] = {3,3};
		count = 32;
		ammo = "Bullet_12GaugePellets";
		ammoItems[] = {"Ammo_12gaPellets","Ammo_12gaSlug","Ammo_12gaRubberSlug","Ammo_12gaBeanbag","Ammo_12gaPellets_tracer","Ammo_12gaNeedles","Ammo_new_12gaBuckshot5","Ammo_new_12gaExpressBuckshot6","Ammo_new_12gaBuckshot7","Ammo_new_12gaMagnumBuckshot8","Ammo_new_12gaRip","Ammo_new_12gaAP20","Ammo_new_12ga2Sabot","Ammo_new_12gaFtxCustomLIte","Ammo_new_12gaGrizzly40","Ammo_new_12gaPoleva3","Ammo_new_12gaPoleva6","Ammo_new_12ga50Bmg","Ammo_new_12gaLead","Ammo_new_12gaFlchetteS","Ammo_new_12gaSuperFormance","Ammo_new_12gaCopperSabotPremier","Ammo_new_12gaImbalanced","Ammo_new_12gaImbalancedSlug"};
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