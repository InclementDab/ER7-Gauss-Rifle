modded class JMAnimRegister
{
 	override void OnRegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
		super.OnRegisterOneHanded(pType, pBehavior);
		pType.AddItemInHandsProfileIK("ER7_Scope", "dz/anims/workspaces/player/player_main/props/player_main_1h_rangefinder.asi", pBehavior,"dz/anims/anm/player/ik/gear/rangefinder.anm");
	}
};