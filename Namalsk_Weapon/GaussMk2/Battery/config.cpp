class CfgPatches
{
	class Namalsk_Weapon_RailBattery
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Weapons_Firearms","DZ_Weapons_Ammunition","DZ_Weapons_Magazines"};
		magazines[] = {};
		ammo[] = {};
	};
};

class Inventory_Base;
class CfgVehicles
{
	class ER7_Energy_Cell: Inventory_Base
    {
        scope = 2;
        displayName = "ER7 Energy Cell";
        descriptionShort = "Experimental compact nuclear cell. (Can create and store enough energy to fire 3 times in relatively quick sucession. The cell will recharge completly over time).";
        model = "\Namalsk_Weapon\GaussMk2\Battery\ER7_Energy_Cell.p3d";
        isMeleeWeapon = 1;
        weight = 1200;
        absorbency = 0.8;
        itemSize[] = {2,1};
        stackedUnit = "w";
        quantityBar = 1;
        varQuantityInit = 30;
        varQuantityMin = 0.0;
        varQuantityMax = 30;
        varQuantityDestroyOnMin = 0;
        inventorySlot[] = {"ER7_Energy_Cell"};
        rotationFlags = 17;
        class EnergyManager
        {
            hasIcon = 1;
            switchOnAtSpawn = 1;
            isPassiveDevice = 1;
            energyStorageMax = 30; 
            energyAtSpawn = 30;
            convertEnergyToQuantity = 1;
            reduceMaxEnergyByDamageCoef = 1;
            powerSocketsCount = 1;
            compatiblePlugTypes[] = {1};
            energyUsagePerSecond = -1.0;
        };
        class AnimationSources
        {
            class cover
            {
                source = "user";
                animPeriod = 0.5;
                initPhase = 1;
            };
        };
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 20;
                    healthLevels[] = 
                    {{1.0,{"Namalsk_Weapon\GaussMk2\Battery\Data\RailBattery.rvmat"}},
                    {0.7,{"Namalsk_Weapon\GaussMk2\Battery\Data\RailBattery.rvmat"}},
                    {0.5,{"Namalsk_Weapon\GaussMk2\Battery\Data\RailBattery_damage.rvmat"}},
                    {0.3,{"Namalsk_Weapon\GaussMk2\Battery\Data\RailBattery_damage.rvmat"}},
                    {0.0,{"Namalsk_Weapon\GaussMk2\Battery\Data\RailBattery_destruct.rvmat"}}};
                };
            };
        };
    };
};

class CfgSlots
{
	class ER7_Energy_Cell
	{
		name = "ER7_Energy_Cell";
		displayName = "ER7 Energy Cell";
		ghostIcon = "set:gauss_ghost image:ghost";
	};
};