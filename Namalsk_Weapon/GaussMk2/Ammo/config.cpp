class CfgPatches
{
	class AmmoBox_ER7RFW
	{
		units[] = {"AmmoBox_ER7RFW"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Weapons_Ammunition"};
		magazines[] = {"Ammo_ER7RFW", "Ammo_ER7RFW_Teleport"};
		ammo[] = {"Bullet_ER7RFW", "Bullet_ER7RFW_Teleport"};
	};
};


class CfgMagazines
{
	class Ammunition_Base;
	class Ammo_ER7RFW: Ammunition_Base
	{
		scope = 2;
		displayName = "ER7 RFW (SN Rounds)";
		descriptionShort = "ER7 RFW SN Rounds are a high velocity Railgun Projectile for use in the ER7 RFW Gauss Rifle.";
		model = "Namalsk_Weapon\GaussMk2\Ammo\ER7RFW_Ammo.p3d";
		itemSize[] = {2,1};
		rotationFlags = 34;
		weight = 24;
		count = 5;
		ammo = "Bullet_ER7RFW";
	};

	class Ammo_ER7RFW_Teleport: Ammunition_Base
	{
		scope = 2;
		displayName = "ER7 RFW (Teleportation Rounds)";
		descriptionShort = "ER7 RFW Teleportation Rounds are an experimental technology for the ER7 Gauss Rifle. The round contains a small piece of NAC Orbalist technology in the tip, that once exposed at high impact, teleports the target to a random destination. Not for use with children under 12";
		model = "Namalsk_Weapon\GaussMk2\Ammo\ER7RFW_Ammo.p3d";
		itemSize[] = {2,1};
		rotationFlags = 34;
		weight = 24;
		count = 5;
		ammo = "Bullet_ER7RFW_Teleport";
	};
};

class CfgAmmoTypes
{
	class Bullet_ER7RFW
	{
		name = "Bullet_ER7RFW";
	};

	class Bullet_ER7RFW_Teleport
	{
		name = "Bullet_ER7RFW_Teleport";
	};
};

class Entity;
class CfgAmmo
{
	class ER7BulletSimulation: Entity {};

	class Bullet_Base;
	class Bullet_ER7RFW: Bullet_Base
	{
		scope = 2;
		lootCategory = "Crafted";
		cartridge = "FxCartridge_9mm";
		model = "\dz\weapons\projectiles\tracer_red.p3d";
		spawnPileType = "Ammo_ER7RFW";
		hit = 11;
		indirectHit = 0;
		indirectHitRange = 0;
		caliber = 1;
		deflecting = 0;
		visibleFire = 5;
		audibleFire = 9;
		typicalSpeed = 3500;
		airFriction = 0;
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		initSpeed = 3500;
		tracerScale = 2;
		tracerStartTime = 0;
		tracerEndTime = 100;
		weight = 0.0149;
		simulationStep = 0.05;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0;
			bleedThreshold = 1;
			class Health
			{
				damage = 6000;
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

	class Bullet_ER7RFW_Teleport: Bullet_ER7RFW
	{
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0;
			bleedThreshold = 1;
			class Health
			{
				damage = 10;
			};
			class Blood
			{
				damage = 10;
			};
			class Shock
			{
				damage = 10;
			};
		};
	};
};