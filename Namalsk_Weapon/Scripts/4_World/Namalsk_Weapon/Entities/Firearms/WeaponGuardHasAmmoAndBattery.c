class WeaponGuardHasAmmoAndBattery extends WeaponGuardHasAmmo
{
	override bool GuardCondition (WeaponEventBase e)
	{
        if (!super.GuardCondition(e))
            return false;

		return m_weapon.GetCompEM().CanWork();
	}
};