modded class EmoteManager
{
	override void CommitSuicide()
	{
		ER7_Gauss weapon;
		WeaponEventBase weapon_event = new WeaponEventTrigger;
		// cast to ER7
		if (Class.CastTo(weapon, m_Player.GetItemInHands())) {
			//TODO : check multiple muzzles for shotguns, eventually
			string ammo;
			float damage;		
			
			if (weapon.CanFire() && weapon.GetCartridgeInfo(0, damage, ammo) && ammo == "Bullet_ER7RFW_Teleport") {
				
				m_Callback.RegisterAnimationEvent("Simulation_End", EmoteConstants.EMOTE_SUICIDE_SIMULATION_END);
				weapon.ProcessWeaponEvent(weapon_event);
				m_Callback.InternalCommand(DayZPlayerConstants.CMD_ACTIONINT_FINISH);
				
				ER7_TeleportObject(m_Player);
				return;
			}
		}

		super.CommitSuicide();
	}
}