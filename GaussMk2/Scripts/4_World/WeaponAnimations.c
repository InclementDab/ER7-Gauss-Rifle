modded class ModItemRegisterCallbacks
{
    override void RegisterFireArms(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterFireArms( pType, pBehavior )        
        pType.AddItemInHandsProfileIK("ER7_Gauss_Base", "Namalsk_Weapon/GaussMk2/Animations/ER7_Gauss.asi", pBehavior, "dz/anims/anm/player/ik/weapons/fn_fal.anm",  "dz/anims/anm/player/reloads/fnfal/w_fnfal_states.anm");
    }    
};   