class CfgPatches
{
	class AmmoBox_ER7RFW
	{
		units[] = {"AmmoBox_ER7RFW"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Weapons_Magazines","DZ_Weapons_Ammunition"};
		magazines[] = {"Ammo_ER7RFW"};
		ammo[] = {"Bullet_ER7RFW"};
	};
};


class CfgMagazines
{
	class Ammunition_Base;
	class Ammo_ER7RFW: Ammunition_Base
	{
		scope = 2;
		displayName = "ER7 RFW (SN Rounds)";
		descriptionShort = "ER7 RFW SN Rounds are used in the almighty ER7 RFW Gauss Rifle.";
		model = "Namalsk_Weapon\GaussMk2\Ammo\ER7RFW_Ammo.p3d";
		itemSize[] = {1,2};
		rotationFlags = 34;
		weight = 24;
		count = 5;
		ammo = "Bullet_ER7RFW";
	};
};
class cfgAmmoTypes
{
	class Bullet_ER7RFW
	{
		name = "Bullet_ER7RFW";
	};
};
class cfgAmmo
{
	class Bullet_Base;
	class Bullet_ER7RFW: Bullet_Base
	{
		scope = 2;
		lootCategory = "Crafted";
		cartridge = "FxCartridge_9mm";
		model = "\dz\weapons\projectiles\tracer_green.p3d";
		spawnPileType = "Ammo_ER7RFW";
		hit = 11;
		indirectHit = 0;
		indirectHitRange = 0;
		caliber = 0.65000004;
		deflecting = 0;
		visibleFire = 5;
		audibleFire = 9;
		typicalSpeed = 3500;
		airFriction = 0;
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		initSpeed = 3500;
		tracerScale = 2;
		tracerStartTime = 0.075;
		tracerEndTime = 100;
		weight = 0.0149;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0;
			bleedThreshold = 1;
			class Health
			{
				damage = 50000;
			};
			class Blood
			{
				damage = 50000;
			};
			class Shock
			{
				damage = 50000;
			};
		};
		class NoiseHit
		{
			strength = 15;
			type = "shot";
		};
	};
};