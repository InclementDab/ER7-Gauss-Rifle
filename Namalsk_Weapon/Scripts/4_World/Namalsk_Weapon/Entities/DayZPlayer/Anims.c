modded class ModItemRegisterCallbacks
{
    override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterOneHanded(pType, pBehavior);
		pType.AddItemInHandsProfileIK("ER7_Scope", "dz/anims/workspaces/player/player_main/props/player_main_1h_rangefinder.asi", pBehavior,"dz/anims/anm/player/ik/gear/rangefinder.anm");
	}
}