class CfgPatches
{
	class Namalsk_Weapon_Energy_Cell
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
        displayName = "ER7 Energy Battery";
        descriptionShort = "Experimental compact nuclear cell. Stores enough energy to fire the ER7 Gauss Rifle 3 times in relatively quick sucession.";
        model = "\Namalsk_Weapon\GaussMk2\Battery\ER7_Energy_Cell.p3d";
        isMeleeWeapon = 1;
        weight = 1200;
        absorbency = 0.8;
        itemSize[] = {2,1};
        stackedUnit = "w";
        quantityBar = 1;
        varQuantityInit = 90;
        varQuantityMin = 0.0;
        varQuantityMax = 90;
        varQuantityDestroyOnMin = 0;
        inventorySlot[] = {"ER7_Gauss_Battery"};
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
        class DamageSystem
        {
            class GlobalHealth
            {
                class Health
                {
                    hitpoints = 20;
                    healthLevels[] = 
                    {{1.0,{"Namalsk_Weapon\GaussMk2\Battery\Data\Energy_Cell.rvmat"}},
                    {0.7,{"Namalsk_Weapon\GaussMk2\Battery\Data\Energy_Cell.rvmat"}},
                    {0.5,{"Namalsk_Weapon\GaussMk2\Battery\Data\Energy_Cell_damage.rvmat"}},
                    {0.3,{"Namalsk_Weapon\GaussMk2\Battery\Data\Energy_Cell_damage.rvmat"}},
                    {0.0,{"Namalsk_Weapon\GaussMk2\Battery\Data\Energy_Cell_destruct.rvmat"}}};
                };
            };
        };
    };
};

class CfgSlots
{
	class Slot_ER7_Gauss_Battery
	{
		name = "ER7_Gauss_Battery";
		displayName = "ER7 Energy Cell";
		ghostIcon = "set:gauss_ghost image:ghost";
	};
};