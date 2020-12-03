modded class WeaponFSM
{
	protected override bool Internal_ValidateAndRepair()
	{
		bool repaired = super.Internal_ValidateAndRepair();
		/*
		WeaponStableState state = WeaponStableState.Cast(m_State);				
		if (state && state.IsRepairEnabled())
		{		
			Weapon_Base weapon = state.m_weapon;
			if (weapon)
			{
				repaired |= ValidateAndRepairHelper(weapon, "BatteryRepair", state.HasBattery(), weapon.HasBattery(), new WeaponEventAttachBattery, new WeaponEventRemoveBattery, state);
			}
		}
		*/
		return repaired;
	}
};