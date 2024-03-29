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
	class ER7_Gauss_Battery: Inventory_Base
    {
        scope = 2;
        displayName = "Railgun Battery";
        descriptionShort = "High capacity Railgun Battery, will fire 9 shots before drained.";
        model = "\Namalsk_Weapon\GaussMk2\Battery\RailBattery.p3d";
        isMeleeWeapon = 1;
        weight = 2600;
        absorbency = 0.8;
        itemSize[] = {1,1};
        stackedUnit = "w";
        quantityBar = 1;
        varQuantityInit = 90;
        varQuantityMin = 0.0;
        varQuantityMax = 90;
        varQuantityDestroyOnMin = 0;
        inventorySlot[] = {"RailgunBattery"};
        rotationFlags = 17;
        class EnergyManager
        {
            hasIcon = 1;
            switchOnAtSpawn = 1;
            isPassiveDevice = 1;
            energyStorageMax = 90; 
            energyAtSpawn = 90;
            convertEnergyToQuantity = 1;
            reduceMaxEnergyByDamageCoef = 1;
            powerSocketsCount = 1;
            compatiblePlugTypes[] = {1};
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
	class Slot_RailgunBattery
	{
		name = "RailgunBattery";
		displayName = "Railgun Battery";
		ghostIcon = "set:gauss_ghost image:ghost";
	};
};